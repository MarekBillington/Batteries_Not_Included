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

	void initialiseSounds();
	void playBackgroundMusic(int sound);
	void initBackgroundMusic();
	void playSoundEffect(int sound);
	void releaseSounds();
	void adjustVolume(float volume);

private:


	static FMODHelper* fm_instance;


};




#endif // !__FMODHELPER_H__
