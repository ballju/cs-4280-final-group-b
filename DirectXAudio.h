//	DirectXAudio.h
//  Brett Eames
//	4/18/2009
//-----------------------------------------------------------------------------
//Defines an Audio Class using DirectX 9.0 (Novemeber 2008) release
//uses the XACT 3 sound engine with hardcoded wave bank file "Wave Bank.xwb"
//and hardcoded sound bank file "Sound Bank.xsb"
//-----------------------------------------------------------------------------

#pragma once

#ifndef __DIRECTXAUDIO_H__
#define __DIRECTXAUDIO_H__

#define _WIN32_WINNT 0x0400     //Allows CoInitializeEx command
#include <xact3.h>
#include <iostream>				//for cerr

using namespace std;			//for cerr


class CDirectXAudio
{
	private:
		IXACT3Engine* pEngine;				//pointer to the instanc of the XACT 3 sound engine
		IXACT3WaveBank* pWaveBank;			//pointer to the wave bank loaded into memory
		IXACT3SoundBank* pSoundBank;		//pointer to the sound bank loaded into memory

		VOID* pbWaveBank; // Handle to memory mapped wave bank data
		VOID* pbSoundBank; // Pointer to sound bank data.(not memory mapped) 

		void LoadWaveBank(LPCSTR filename);		//function to load wave bank into memory
	    void LoadSoundBank(LPCSTR filename);	//function to load sound bank into memory

	public:
		XACTINDEX iExplode;					//xact index to the cue defined for the Explode noise
		XACTINDEX iChimes;					//xact index to the cue defined for the chime noise (not used)
		XACTINDEX iAmbient;					//xact index to the cue defined for the background noise
	    XACTINDEX iGameover;                //xact index to the cue defined for the background noise
        XACTINDEX iNuke;
		XACTINDEX iWilhelm;
		XACTINDEX iJets;

		CDirectXAudio();						//default constructor
	   ~CDirectXAudio();					//destructor
	   void Kill();							//function to correctly release resources and shut down sound engine
	   void InitSound(LPCSTR cue, XACTINDEX& sound);	//funciton to initialize a sound (not used)
	   void PlaySoundDX(XACTINDEX& sound);				//function to Play a sound using that sounds cue
	   void StopSoundDX(XACTINDEX& sound);				//function to Stop a sound playing using it's sound cue index
	   void Update();						//function to call the soundengine work loop	  
};

#endif