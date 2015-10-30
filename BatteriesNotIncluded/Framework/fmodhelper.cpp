
#include "fmodhelper.h"
#include <cmath>







FMODHelper::FMODHelper()
{
	initialiseSounds();
}

FMODHelper::~FMODHelper()
{
	releaseSounds();
}


void 
FMODHelper::initialiseSounds(){



	result = FMOD::System_Create(&systemFMOD);      // Create the main system object.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

		exit(-1);
	}


	result = systemFMOD->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}


	 

	result = systemFMOD->createSound("assets\\opening.wav", FMOD_DEFAULT, 0, &sound1);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = systemFMOD->createSound("assets\\battle.wav", FMOD_DEFAULT, 0, &sound2);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = systemFMOD->createSound("assets\\Bang1.wav", FMOD_DEFAULT, 0, &sound3);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = systemFMOD->createSound("assets\\step1.wav", FMOD_DEFAULT, 0, &sound4);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	
	channel3->setVolume(0.001);
	initBackgroundMusic();

}

void 
FMODHelper::playBackgroundMusic(int sound){

	if (sound == 1){
		channel1->setPaused(false);
		channel2->setPaused(true);
	}
	if (sound == 2) {
		channel2->setPaused(false);
		channel1->setPaused(true);
	}
	
}

void
FMODHelper::initBackgroundMusic(){

	result = sound1->setMode(FMOD_LOOP_NORMAL);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}


	result = systemFMOD->playSound(sound1, 0, true, &channel1);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = sound2->setMode(FMOD_LOOP_NORMAL);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}


	result = systemFMOD->playSound(sound2, 0, true, &channel2);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	


}

void
FMODHelper::adjustVolume(float volume)
{
	channel1->setVolume(volume);
	channel2->setVolume(volume);
	
}


void
FMODHelper::playSoundEffect(int sound){

	//currently these will break games as there is no sound3 and sound4 initialised
	
	if (sound == 1){
		result = sound3->setMode(FMOD_LOOP_OFF);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}

		result = systemFMOD->playSound(sound3, 0, false, &channel3);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}

	}
	if (sound == 2){
		result = sound4->setMode(FMOD_LOOP_OFF);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}

		result = systemFMOD->playSound(sound4, 0, false, &channel3);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}
	}

}

void FMODHelper::releaseSounds(){
	result = sound1->release();
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = sound2->release();
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = sound3->release();
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = sound4->release();
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

}


void 
FMODHelper::update()
{
	systemFMOD->update();

	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

}

void
FMODHelper::releaseSFX()
{
	result = sound3->release();
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = sound4->release();
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}