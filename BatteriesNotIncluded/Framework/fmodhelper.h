#ifndef __FMODHELPER_H__
#define __FMODHELPER_H__


#include "fmod.hpp"
#include "fmod_errors.h"
#include "fmod_common.h"
#include <iostream>
#include <SDL.h>
#include <cassert>


class FMODHelper
{
public:
	FMODHelper();
	~FMODHelper();

	void update();
	void initialiseSounds();
	void playBackgroundMusic(int sound);
	void initBackgroundMusic();
	void playSoundEffect(int sound);
	void releaseSounds();
	void adjustVolume(float volume);
	void releaseSFX();

	FMOD::System *systemFMOD = NULL;
	FMOD::Sound      *sound1, *sound2, *sound3, *sound4;
	FMOD::Channel    *channel1, *channel2, *channel3;
	FMOD_RESULT result;
	bool playing = false;

private:


	static FMODHelper* fm_instance;


};




#endif // !__FMODHELPER_H__
