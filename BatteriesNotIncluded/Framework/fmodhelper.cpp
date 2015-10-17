
#include "fmodhelper.h"


FMOD::System *systemFMOD = NULL;
FMOD::Sound      *sound1, *sound2, *sound3, *sound4;
FMOD::Channel    *channel1, *channel2, *channel3;
FMOD_RESULT result;




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
FMODHelper::playSoundEffect(int sound){

	//currently these will break games as there is no sound3 and sound4 initialised
	if (sound == 1){
				result = systemFMOD->playSound(sound3, 0, false, &channel3);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}

	}
	if (sound == 2){
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

}