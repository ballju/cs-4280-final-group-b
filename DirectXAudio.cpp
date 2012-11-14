//	DirectXAudio.cpp
//	Brett Eames
//	4/18/2009
//-----------------------------------------------------------------------------
//Defines the functions declared in DirectXAudio.h
//-----------------------------------------------------------------------------

#include "DirectXAudio.h"


CDirectXAudio::CDirectXAudio()			//constructor for DirectXAudio class
{

	//call the CoInitializeEx method to initialize a seperate thread for the sound engine to use
	//if this call succeeds
    if( SUCCEEDED( CoInitializeEx(NULL, COINIT_MULTITHREADED) ) )
    {
		//call the XACT3CreateEnigne method to create a new instance of the sound engine with pointer pEngine
		//if that call fails or the pointer is not initialized show an error message
        if( FAILED(XACT3CreateEngine( 0, &pEngine )) || pEngine == NULL)
         cerr << "XACT Engine Failed to be created" << endl;
    }
    else		//if CoInitializeEx failes
    {
       cerr << "CoInitialize Failed!" << endl;		//show an error message
    }

    XACT_RUNTIME_PARAMETERS xrParams;			//create a XACT parameters struct variable

    memset(&xrParams, 0, sizeof(xrParams));		//call memset to write "0" to the entire struct xrParams
												//0 is the default value for most XACT engine parameters

    xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT ; //set the lookAheadTime parameter to the typical value (250);

	//call the Initialize method with the struct xrParam to initialize the sound engine
	//if the initialization fails
    if(FAILED(pEngine->Initialize(&xrParams)))
	{
		cerr << "XACT Engine Failed to be Initialized" << endl;		//show error message
	}
        

    LoadWaveBank(".\\Win\\Wave Bank.xwb");		//call loadwavebank to load the wave bank file
    LoadSoundBank(".\\Win\\Sound Bank.xsb");	//call loadsoundbank to load the sound bank file
 
	// Get the sound cue index from the sound bank
    iExplode = pSoundBank->GetCueIndex( "explode" );
    iChimes = pSoundBank->GetCueIndex( "chimes" );
    iAmbient = pSoundBank->GetCueIndex( "ambient" );
	iGameover = pSoundBank->GetCueIndex("gameover");
	iNuke = pSoundBank->GetCueIndex("nuke");
	iWilhelm = pSoundBank->GetCueIndex("wilhelm");
}


CDirectXAudio::~CDirectXAudio()			//default contstructor
{   
}

void CDirectXAudio::Update()			//call the sound engine dowork function
{
   if( pEngine )						//if pEngine pointer is not NULL
      pEngine->DoWork();				//call the dowork function
}

void CDirectXAudio::LoadWaveBank(LPCSTR filename)		//function to load the wave bank given the path "filename"
{

    DWORD dwFileSize;				//double word to hold the size of the file being read
    HANDLE hMapFile;				//handle to the memory mapped file
    HANDLE hFile;					//handle to the file being read from disk

	//call the createfile function to create a file structure in the file table
	//returns a handle pointing to the file
    hFile = CreateFile( filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	//if the file handle is valid
    if( hFile != INVALID_HANDLE_VALUE )		
    {
        dwFileSize = GetFileSize( hFile, NULL );	//call getFileSize to set dwFileSize to the size of the file
        if( dwFileSize != -1 )						//if the file has a valid size
        {
			//call CreateFileMapping to create a memory mapped file in memory
            hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
			//if the handle to the memory mapped file is valid
            if( hMapFile )
            {
				//call the mapVeiwofFile function to map the file into the processes momory space
				//set pbWaveBank to point to the start of the memory mapped location
                pbWaveBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );    
				//if pbWaveBank is a valid pointer
                if( pbWaveBank ) 
                {
					//Call CreateInMemroyWaveBank to link the memory mapped file to the sound engine
					//the sound engine will now keep track of the memory mapped file with the pointer pWaveBank
					//the handles created are no longer nessacary
					//if the CreateInMomoryWaveBank function fails
                    if(FAILED(pEngine->CreateInMemoryWaveBank( pbWaveBank, dwFileSize, 0, 0, &pWaveBank )))
					cerr << "Wave Bank Failed to be created" << endl;			//show error message   
                }                
                CloseHandle( hMapFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
            }
        }
        CloseHandle( hFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
    }
}

void CDirectXAudio::LoadSoundBank(LPCSTR filename)			//Function to load the sound bank into memory given the path filename
{
    DWORD dwFileSize;			//Double word used to hold the size of the file to be read in
    DWORD dwBytesRead;			//double word used to hold the number of bytes read
    HANDLE hFile;				//handle to the file to be opened

    //because sound bank is so small memory mapping won't be used

	//call the createfile function to create a file structure in the file table
	//returns a handle pointing to the file
    hFile = CreateFile( filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	//if the file handle is valid
    if( hFile != INVALID_HANDLE_VALUE )
    {
        dwFileSize = GetFileSize( hFile, NULL );		//call getFileSize to set dwFileSize to the size of the file
        if( dwFileSize != -1 )							//if the file has a valid size
        {
            pbSoundBank = new BYTE[dwFileSize];			// Allocate enough space to hold the file
			//if pbSoundBank has a valid pointer
            if( pbSoundBank ) 
            {
				//call the readfile function to read the file from memory into the buffer pointed to by pbSoundBank
				//if readfile doesn't return false
                if( 0 != ReadFile(hFile, pbSoundBank, dwFileSize, &dwBytesRead, NULL) )
                {
					//call the CreateSoundBank function to load the Soundbank into the engine
					//the sound engine now keeps track of the sound bank with the pointer pSoundBank
					//the file handle is no longer nessecary
					//if the createSoundBank funciton fails
                    if(FAILED(pEngine->CreateSoundBank( pbSoundBank, dwFileSize, 0, 0, &pSoundBank ))) 
					cerr << "XACT Engine Failed to be created" << endl;		//show error message
                }
            }                
        }
        CloseHandle( hFile );	//close the file handle
    }
}

void CDirectXAudio::InitSound(LPCSTR cue, XACTINDEX& sound)	//function to get a sound index from the "friendly" cue name
{
    sound = pSoundBank->GetCueIndex( cue );		//call teh GetCueIndex to get the XACTINDEX from the cue name
}

void CDirectXAudio::PlaySoundDX(XACTINDEX& sound)		//fucniton to play a sound given a cue index
{
    pSoundBank->Play( sound, 0, 0, NULL );				//call the play sound function on the sound bank object
}

void CDirectXAudio::StopSoundDX(XACTINDEX& sound)
{
	pSoundBank->Stop(sound, 0);
}

void CDirectXAudio::Kill()			//function to shut down the sound engine and release all the memory resources used by it
{
    if( pEngine )					//if the pEngine is a valid pointer
    {		
        pEngine->ShutDown();		//call the ShutDown Function
        pEngine->Release();			//call the Release function
    }

    if( pbSoundBank )				//if pbSoundBank still points to a location in memory
	{
        delete[] pbSoundBank;		//delete the contents stored there
	}
    pbSoundBank = NULL;				//set pbSoundBank to null

    if( pbWaveBank )				//if pbWavebank still points to a location in memory
	{
        UnmapViewOfFile( pbWaveBank );	//unmap the file loaded there
	}	
    pbWaveBank = NULL;				//set pbWavebank to null

    CoUninitialize();				//call CoUninitialize to shut down the other thread the sound engine was using
}