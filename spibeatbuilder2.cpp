////////////////////////////////////////////////////////////////
//nakedsoftware.org, spi@oifii.org or stephane.poirier@oifii.org
//
//
//2012june28, creation for building beats
//
//
//nakedsoftware.org, spi@oifii.org or stephane.poirier@oifii.org
////////////////////////////////////////////////////////////////

#include <string>
#include <fstream>
#include <vector>

#include <iostream>
#include <sstream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"

#define BUFF_SIZE	2048


#include <ctime>
#include "WavSet.h"
#include "Instrument.h"
#include "InstrumentSet.h"

#include "partition.h"
#include "partitionset.h"

#include "WavSet.h"

#include <assert.h>
#include <windows.h>



// Select sample format
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif



//////////////////////////////////////////
//main
//////////////////////////////////////////
int main(int argc, char *argv[]);
int main(int argc, char *argv[])
{
    PaStreamParameters outputParameters;
    PaStream* stream;
    PaError err;

	////////////////////////
	// initialize port audio 
	////////////////////////
    err = Pa_Initialize();
    if( err != paNoError )
	{
		fprintf(stderr,"Error: Initialization failed.\n");
		Pa_Terminate();
		fprintf( stderr, "An error occured while using the portaudio stream\n" );
		fprintf( stderr, "Error number: %d\n", err );
		fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
		return -1;
	}

	outputParameters.device = Pa_GetDefaultOutputDevice(); // default output device 
	if (outputParameters.device == paNoDevice) 
	{
		fprintf(stderr,"Error: No default output device.\n");
		Pa_Terminate();
		fprintf( stderr, "An error occured while using the portaudio stream\n" );
		fprintf( stderr, "Error number: %d\n", err );
		fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
		return -1;
	}
	outputParameters.channelCount = 2;//pWavSet->numChannels;
	outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;


	//////////////////////////
	//initialize random number
	//////////////////////////
	srand((unsigned)time(0));





	string path = "D:\\oifii-org\\httpdocs\\ns-org\\nsd\\ar\\cp\\audio_spi\\spibeatbuilder\\";
	WavSet* pWavSet1 = new WavSet;
	pWavSet1->ReadWavFile((path+"testbeat9_11.wav").c_str());
	WavSet* pWavSet2 = new WavSet;
	pWavSet2->ReadWavFile((path+"testbeat9_12.wav").c_str());
	WavSet* pWavSet3 = new WavSet;
	pWavSet3->ReadWavFile((path+"testbeat9_21.wav").c_str());
	WavSet* pWavSet4 = new WavSet;
	pWavSet4->ReadWavFile((path+"testbeat9_31.wav").c_str());

	WavSet* pWavSet11 = new WavSet;
	pWavSet11->ReadWavFile((path+"internaljugular.wav").c_str());

	string path2 = "C:\\Program Files (x86)\\Native Instruments\\Sample Libraries\\Kontakt 3 Library\\World\\Z - Samples\\Djembe Kit Samples\\";
	WavSet* pWavSet12 = new WavSet;
	pWavSet12->ReadWavFile((path2+"DJK_SLP_OPN_LRr_03.wav").c_str());


	//float patternduration_s = 3; //3 sec
	//float patternduration_s = 2.5; //2.5 sec
	float patternduration_s = 2.75; //2.75 sec

	//float loopduration_s=4*patternduration_s; //4 loops
	float loopduration_s=20*patternduration_s; //20 loops

	float amplitude = 1.0;
	//float amplitude = 0.5;


	WavSet* pWavSetLoop1 = new WavSet;
	pWavSetLoop1->CreateSilence(patternduration_s); //patternduration_s sec
	//pWavSetLoop1->SpreadSample("10000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000", pWavSet1, patternduration_s, 0.5, 0.0, 1.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	pWavSetLoop1->SpreadSample("10000000000000001000000000000000000000000000000000000000000000001000000000001000100000000000000000000000000000000000000000000000", pWavSet1, patternduration_s, 0.5, 0.0, 1.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop1->Play(&outputParameters);

	WavSet* pWavSetLoop2 = new WavSet;
	pWavSetLoop2->CreateSilence(patternduration_s); //patternduration_s sec
	//pWavSetLoop2->SpreadSample("10000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000", pWavSet3, patternduration_s, 0.5, 0.0, 1.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	pWavSetLoop2->SpreadSample("00000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000", pWavSet3, patternduration_s, 0.5, 0.0, 1.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop2->Play(&outputParameters);

	WavSet* pWavSetLoop3 = new WavSet;
	pWavSetLoop3->CreateSilence(patternduration_s); //patternduration_s sec
	//pWavSetLoop3->SpreadSample("10000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000", pWavSet3, patternduration_s, 0.5, 0.0, 1.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	pWavSetLoop3->SpreadSample("00000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000001000000000", pWavSet4, patternduration_s, 0.5, 0.0, 1.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop3->Play(&outputParameters);

	WavSet* pWavSetLoopMixTemp = new WavSet;
	pWavSetLoopMixTemp->Mix(amplitude, pWavSetLoop1, amplitude, pWavSetLoop2);
	WavSet* pWavSetLoopMix = new WavSet;
	pWavSetLoopMix->Mix(amplitude, pWavSetLoopMixTemp, amplitude, pWavSetLoop3);

	WavSet* pWavSetMain1 = new WavSet;
	pWavSetMain1->CreateSilence(loopduration_s); //loopduration_s sec
	pWavSetMain1->LoopSample(pWavSetLoopMix, loopduration_s, -1.0, 0.0); //from second 0, loop sample during loopduration_s seconds
	//pWavSetMain1->Play(&outputParameters);








	pWavSetMain1->Play(&outputParameters);

	delete pWavSetLoop1;
	delete pWavSetLoop2;
	delete pWavSetLoop3;
	delete pWavSetLoopMixTemp;
	delete pWavSetLoopMix;
	delete pWavSetMain1;


	delete pWavSet1;
	delete pWavSet2;
	delete pWavSet3;
	delete pWavSet4;

	delete pWavSet11;
	delete pWavSet12;

	/////////////////////
	//terminate portaudio
	/////////////////////
	Pa_Terminate();
	//if(pInstrumentSet) delete pInstrumentSet;
	printf("Exiting!\n"); fflush(stdout);
	return 0;
}

