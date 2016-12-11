////////////////////////////////////////////////////////////////
//nakedsoftware.org, spi@oifii.org or stephane.poirier@oifii.org
//
//
//2012june28, creation for building beats
//
//
//nakedsoftware.org, spi@oifii.org or stephane.poirier@oifii.org
////////////////////////////////////////////////////////////////
#include "stdafx.h"

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
#include "spiws_WavSet.h"
#include "spiws_Instrument.h"
#include "spiws_InstrumentSet.h"

#include "spiws_partition.h"
#include "spiws_partitionset.h"

#include "spiws_WavSet.h"

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
	int nShowCmd = false;
	ShellExecuteA(NULL, "open", "begin.bat", "", NULL, nShowCmd);


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



	/*
	//////////////////////////////////////////////////////////////////////////
	//populate InstrumentSet according to input folder (folder of sound files)
	//////////////////////////////////////////////////////////////////////////
	InstrumentSet* pInstrumentSet=new InstrumentSet;
	if(pInstrumentSet)
	{
		pInstrumentSet->Populate(wavfolder);
	}
	else
	{
		assert(false);
		cout << "exiting, instrumentset could not be allocated" << endl;
		goto error;
	}
	*/
	///////////////////////////////////////////
	//populate InstrumentSet manually from name
	///////////////////////////////////////////
	/*
	int iInstNameArraySize = 5;
	const char* pInstNameArray[] = {"piano","piano", "piano", "piano", "piano"};
	//const char* pInstNameArray[] = {"piano","guitar", "bass", "violin", "drumkit"};
	//const char* pInstNameArray[] = {"piano","guitar", "piano", "guitar", "piano"};
	//const char* pInstNameArray[] = {"piano","guitar", "otherinstruments", "drumkit", "drumkit"};
	//const char* pInstNameArray[] = {"africa","africa", "africa", "africa", "africa"};
	InstrumentSet* pInstrumentSet=new InstrumentSet;
	if(pInstrumentSet)
	{
		for(int i=0; i<iInstNameArraySize; i++)
		{
			//create each instrument individually
			Instrument* pInstrument = new Instrument;
			if(pInstrument)
			{
				//piano
				if(pInstrument->CreateFromName(pInstNameArray[i]))
				{
					//pInstrument->Play(&outputParameters, INSTRUMENT_WAVSETINSEQUENCE);
					pInstrument->Play(&outputParameters, INSTRUMENT_WAVSETALLATONCE);
					pInstrumentSet->instrumentvector.push_back(pInstrument);
				}
				else
				{
					cout << "exiting, instrument could not be created" << endl;
					goto error;
				}
			}
			else
			{
				cout << "exiting, instrument could not be allocated" << endl;
				goto error;
			}
		}
	}
	else
	{
		assert(false);
		cout << "exiting, instrumentset could not be allocated" << endl;
		goto error;
	}
	*/
	/*
	/////////////////////////////////////////////
	//populate InstrumentSet manually from filter
	/////////////////////////////////////////////
	//int iInstNameArraySize = 3;
	//const char* pInstNameArray[] = {"wavfolder_a_celloensemble.txt","wavfolder_a-d-e_celloensemble.txt", "wavfolder_c-f-g_celloensemble.txt"};
	//int iInstNameArraySize = 5;
	//const char* pInstNameArray[] = {"wavfolder_world-africanshakerskit.txt","wavfolder_world-bongokit.txt", "wavfolder_world-congakit.txt", "wavfolder_world-djembekit.txt", "wavfolder_world-kora.txt"};
	int iInstNameArraySize = 2;
	const char* pInstNameArray[] = {"wavfolder_synth-synthdrums-New Rave Kit Samples.txt", "wavfolder_synth-synthdrums-April Fools Kit Samples.txt"};
	InstrumentSet* pInstrumentSet=new InstrumentSet;
	if(pInstrumentSet)
	{
		for(int i=0; i<iInstNameArraySize; i++)
		{
			//create each instrument individually
			Instrument* pInstrument = new Instrument;
			if(pInstrument)
			{
				//piano
				if(pInstrument->CreateFromWavFilenamesFilter(pInstNameArray[i]))
				{
					//pInstrument->Play(&outputParameters, INSTRUMENT_WAVSETINSEQUENCE);
					pInstrument->Play(&outputParameters, INSTRUMENT_WAVSETALLATONCE);
					pInstrumentSet->instrumentvector.push_back(pInstrument);
				}
				else
				{
					cout << "exiting, instrument could not be created" << endl;
					goto error;
				}
			}
			else
			{
				cout << "exiting, instrument could not be allocated" << endl;
				goto error;
			}
		}
	}
	else
	{
		assert(false);
		cout << "exiting, instrumentset could not be allocated" << endl;
		goto error;
	}
	*/


	//////////////////
	//test zone, begin
	//////////////////
	/*
	///////////////////////////////////
	//play all notes of all instruments
	///////////////////////////////////
	//int numberofinstrumentsinplayback=3;
	int numberofinstrumentsinplayback=1; //one instrument at a time
	pInstrumentSet->Play(&outputParameters, fSecondsPlay, numberofinstrumentsinplayback); //each instrument will play its loaded samples sequentially
	*/
	
	/////////////////////////////
	//spread n sinusoidal samples
	/////////////////////////////
	/*
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(1.0);
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(30);
	pSilentWavSet->SpreadSample(4, pTempWavSet,24); //default duration and distance
	pSilentWavSet->Play(&outputParameters);
	delete pTempWavSet;
	delete pSilentWavSet;
	*/
	
	/*
	////////////////////////////////////////////////////////////
	//spread sinusoidal sample patterned like "1000110011001100"
	////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(10); //10sec
	pSilentWavSet->SpreadSample("1000110011001100", pTempWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
	pSilentWavSet->Play(&outputParameters);
	delete pTempWavSet;
	delete pSilentWavSet;
	*/

	/*
	//////////////////////////////////////////////////////////////////
	//spread instrument sample patterned like "1000110011001100", once
	//////////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		pAnInstrument = pInstrumentSet->GetInstrumentRandomly(); //assuming 
		assert(pAnInstrument);
		pAWavSet = pAnInstrument->GetWavSetRandomly();
		assert(pAWavSet);
	}
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(30); //30sec
	//pSilentWavSet->SpreadSample("1000110011001100", pTempWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
	pSilentWavSet->SpreadSample("1000110011001100", pAWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
	//pSilentWavSet->LoopSample(pAWavSet, -1.0, -1.0, 15.0); //from second 15, loop sample once
	pSilentWavSet->LoopSample(pAWavSet, 15.0, 0.25, 15.0); //from second 15, loop sample during 15 seconds
	pSilentWavSet->Play(&outputParameters);
	if(pTempWavSet) delete pTempWavSet;
	if(pSilentWavSet) delete pSilentWavSet;
	goto exit;
	*/
	/*
	////////////////////////////////////////////////////////////////////
	//spread instrument sample patterned like "1000110011001100", looped
	////////////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		pAnInstrument = pInstrumentSet->GetInstrumentRandomly(); //assuming 
		assert(pAnInstrument);
		pAWavSet = pAnInstrument->GetWavSetRandomly();
		assert(pAWavSet);
	}
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(30); //30sec
	WavSet* pLoopWavSet = new WavSet;
	pLoopWavSet->CreateSilence(4); //4sec
	//pSilentWavSet->SpreadSample("1000110011001100", pTempWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
	pLoopWavSet->SpreadSample("1000110011001100", pAWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
	pSilentWavSet->LoopSample(pLoopWavSet, 30.0, -1.0, 0.0); //from second 0, loop sample during 30 seconds
	pSilentWavSet->Play(&outputParameters);
	if(pTempWavSet) delete pTempWavSet;
	if(pSilentWavSet) delete pSilentWavSet;
	goto exit;
	*/
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//for each instrument, pick random wavset, spread wavset patterned like "1000110011001100", looped pattern and play
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(30); //30sec
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		vector<Instrument*>::iterator it;
		for(it=pInstrumentSet->instrumentvector.begin();it<pInstrumentSet->instrumentvector.end();it++)
		{
			cout << endl;
			pAnInstrument = *it;
			assert(pAnInstrument);
			cout << "instrument name: " << pAnInstrument->instrumentname << endl;
			pAWavSet = pAnInstrument->GetWavSetRandomly();
			cout << "sound filename: " << pAWavSet->GetName() << endl;
			assert(pAWavSet);

			WavSet* pLoopWavSet = new WavSet;
			pLoopWavSet->CreateSilence(4); //4sec
			//pSilentWavSet->SpreadSample("1000110011001100", pTempWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
			pLoopWavSet->SpreadSample("1000110011001100", pAWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
			pSilentWavSet->LoopSample(pLoopWavSet, 30.0, -1.0, 0.0); //from second 0, loop sample during 30 seconds
			pSilentWavSet->Play(&outputParameters);
			delete pLoopWavSet;
		}
	}
	if(pTempWavSet) delete pTempWavSet;
	if(pSilentWavSet) delete pSilentWavSet;
	goto exit;
	*/
	
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//for each instrument, pick random wavset, spread wavset patterned like "9000220022002200", looped pattern and play
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	WavSet* pSilentWavSet = new WavSet;
	pSilentWavSet->CreateSilence(128); //30sec
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		vector<Instrument*>::iterator it;
		for(it=pInstrumentSet->instrumentvector.begin();it<pInstrumentSet->instrumentvector.end();it++)
		{
			cout << endl;
			pAnInstrument = *it;
			assert(pAnInstrument);
			cout << "instrument name: " << pAnInstrument->instrumentname << endl;
			//pAWavSet = pAnInstrument->GetWavSetRandomly();
			//assert(pAWavSet);
			cout << "sound filename: " << "as a function of supplied pattern" << endl;

			WavSet* pLoopWavSet = new WavSet;
			pLoopWavSet->CreateSilence(16); //4sec
			//pSilentWavSet->SpreadSample("1000110011001100", pTempWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
			//pLoopWavSet->SpreadSamples("0003000200040005", pAnInstrument, 4, 0.5, 0.0); //pattern over 4 sec, sample duration 0.5sec and with pattern offset of 0sec 
			pLoopWavSet->SpreadSamples("9000220022002200400022002200220070002200220022001000220022002200", pAnInstrument, 16, 0.5, 0.0); //pattern over 4 sec, sample duration 0.5sec and with pattern offset of 0sec 
			pSilentWavSet->LoopSample(pLoopWavSet, 128.0, -1.0, 0.0); //from second 0, loop sample during 30 seconds
			pSilentWavSet->Play(&outputParameters);
			delete pLoopWavSet;
		}
	}
	if(pTempWavSet) delete pTempWavSet;
	if(pSilentWavSet) delete pSilentWavSet;
	goto exit;
	*/

	/*
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//for each instrument, pick random wavset, spread wavset patterned like "9000220022002200", looped pattern and play
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	WavSet* pTempWavSet = new WavSet;
	pTempWavSet->CreateSin(0.25);
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		vector<Instrument*>::iterator it;
		for(it=pInstrumentSet->instrumentvector.begin();it<pInstrumentSet->instrumentvector.end();it++)
		{
			WavSet* pSilentWavSet = new WavSet;
			pSilentWavSet->CreateSilence(32); //32sec
			if(pSilentWavSet) 
			{
				cout << endl;
				pAnInstrument = *it;
				assert(pAnInstrument);
				cout << "instrument name: " << pAnInstrument->instrumentname << endl;
				//pAWavSet = pAnInstrument->GetWavSetRandomly();
				//assert(pAWavSet);
				cout << "sound files name: " << "" << endl;

				WavSet* pLoopWavSet = new WavSet;
				pLoopWavSet->CreateSilence(16); //4sec
				//pSilentWavSet->SpreadSample("1000110011001100", pTempWavSet, 4, 0.25, 0.0); //pattern over 4 sec, sample duration 0.25sec and with pattern offset of 0sec 
				pLoopWavSet->SpreadSamples("9000220022002200400022002200220070002200220022001000220022002200", pAnInstrument, 16, 0.25, 0.0); //pattern over 4 sec, sample duration 0.5sec and with pattern offset of 0sec 
				pSilentWavSet->LoopSample(pLoopWavSet, 32.0, -1.0, 0.0); //from second 0, loop sample during 30 seconds
				pSilentWavSet->Play(&outputParameters);
				delete pLoopWavSet;
				delete pSilentWavSet;
			}
		}
	}
	if(pTempWavSet) delete pTempWavSet;
	//goto exit;
	*/
	/*
	Instrument* pAnInstrument = NULL;
	WavSet* pAWavSet = NULL;
	if(pInstrumentSet && pInstrumentSet->HasOneInstrument()) 
	{
		vector<Instrument*>::iterator it;
		for(it=pInstrumentSet->instrumentvector.begin();it<pInstrumentSet->instrumentvector.end();it++)
		{
			string mystring = (*it)->GetWavSetPatternCodes();
			string mystring2= (*it)->GetWavSetPatternNotes();

			WavSet* pSilentWavSet = new WavSet;
			pSilentWavSet->CreateSilence(32); //32sec
			if(pSilentWavSet) 
			{
				cout << endl;
				pAnInstrument = *it;
				assert(pAnInstrument);
				cout << "instrument name: " << pAnInstrument->instrumentname << endl;
				//pAWavSet = pAnInstrument->GetWavSetRandomly();
				//assert(pAWavSet);
				cout << "sound files name: " << "" << endl;

				WavSet* pLoopWavSet = new WavSet;
				pLoopWavSet->CreateSilence(16); //16sec
				pLoopWavSet->SpreadSamples("3000220022002200300022002200220030002200220022001000220022002200", pAnInstrument, 16, 0.25, 0.0); //pattern over 4 sec, sample duration 0.5sec and with pattern offset of 0sec 
				pSilentWavSet->LoopSample(pLoopWavSet, 32.0, -1.0, 0.0); //from second 0, loop sample during 30 seconds
				pSilentWavSet->Play(&outputParameters);
				delete pLoopWavSet;
				delete pSilentWavSet;
			}
		}
	}
	*/
	////////////////
	//test zone, end
	////////////////


	string path = "C:\\Program Files (x86)\\Native Instruments\\Sample Libraries\\Kontakt 3 Library\\Synth\\Z - Samples\\Synth Drums Samples\\New Rave Kit Samples\\";
	WavSet* pWavSet1 = new WavSet;
	pWavSet1->ReadWavFile((path+"combipass.wav").c_str());
	WavSet* pWavSet2 = new WavSet;
	pWavSet2->ReadWavFile((path+"contusion.wav").c_str());
	WavSet* pWavSet3 = new WavSet;
	pWavSet3->ReadWavFile((path+"harmful.wav").c_str());
	WavSet* pWavSet4 = new WavSet;
	pWavSet4->ReadWavFile((path+"inhaledbees.wav").c_str());
	WavSet* pWavSet5 = new WavSet;
	pWavSet5->ReadWavFile((path+"kickcranial_01.wav").c_str());
	WavSet* pWavSet6 = new WavSet;
	pWavSet6->ReadWavFile((path+"kickcranial_02.wav").c_str());
	WavSet* pWavSet7 = new WavSet;
	pWavSet7->ReadWavFile((path+"kickcranial_03.wav").c_str());
	WavSet* pWavSet8 = new WavSet;
	pWavSet8->ReadWavFile((path+"smellslikeafreshkitty.wav").c_str());
	WavSet* pWavSet9 = new WavSet;
	pWavSet9->ReadWavFile((path+"volligkomplett.wav").c_str());

	WavSet* pWavSet11 = new WavSet;
	pWavSet11->ReadWavFile((path+"internaljugular.wav").c_str());

	string path2 = "C:\\Program Files (x86)\\Native Instruments\\Sample Libraries\\Kontakt 3 Library\\World\\Z - Samples\\Djembe Kit Samples\\";
	WavSet* pWavSet12 = new WavSet;
	pWavSet12->ReadWavFile((path2+"DJK_SLP_OPN_LRr_03.wav").c_str());

	if(pWavSet1->numChannels==1) pWavSet1->Resample44100monoTo44100stereo();
	if(pWavSet2->numChannels==1) pWavSet2->Resample44100monoTo44100stereo();
	if(pWavSet3->numChannels==1) pWavSet3->Resample44100monoTo44100stereo();
	if(pWavSet4->numChannels==1) pWavSet4->Resample44100monoTo44100stereo();
	if(pWavSet5->numChannels==1) pWavSet5->Resample44100monoTo44100stereo();
	if(pWavSet6->numChannels==1) pWavSet6->Resample44100monoTo44100stereo();
	if(pWavSet7->numChannels==1) pWavSet7->Resample44100monoTo44100stereo();
	if(pWavSet8->numChannels==1) pWavSet8->Resample44100monoTo44100stereo();
	if(pWavSet9->numChannels==1) pWavSet9->Resample44100monoTo44100stereo();
	if(pWavSet11->numChannels==1) pWavSet11->Resample44100monoTo44100stereo();
	if(pWavSet12->numChannels==1) pWavSet12->Resample44100monoTo44100stereo();
	/*
	pWavSet1->Play(&outputParameters);
	pWavSet2->Play(&outputParameters);
	pWavSet3->Play(&outputParameters);
	pWavSet4->Play(&outputParameters);
	pWavSet5->Play(&outputParameters);
	pWavSet6->Play(&outputParameters);
	pWavSet7->Play(&outputParameters);
	pWavSet8->Play(&outputParameters);
	pWavSet9->Play(&outputParameters);
	pWavSet11->Play(&outputParameters);
	pWavSet12->Play(&outputParameters);
	*/

	//int patternduration_s = 4; //4 sec
	int patternduration_s = 2; //2 sec
	//int patternduration_s = 1; //1 sec

	int loopduration_s=32; //32 sec
	//int loopduration_s=16; //16 sec
	//int loopduration_s=8; //8 sec
	//int loopduration_s=4; //8 sec

	//float amplitude = 1.0;
	float amplitude = 0.5;


	WavSet* pWavSetLoop1 = new WavSet;
	pWavSetLoop1->CreateSilence(patternduration_s); //patternduration_s sec
	pWavSetLoop1->SpreadSample("1000000000000000100000000000000010000000000000001000000000000000", pWavSet2, patternduration_s, 0.25, 0.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop1->SpreadSample("0000000000000000000000000000000000000000000000000000000000000000", pWavSet2, patternduration_s, 0.25, 0.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop1->Play(&outputParameters);

	WavSet* pWavSetLoop2 = new WavSet;
	pWavSetLoop2->CreateSilence(patternduration_s); //patternduration_s sec
	pWavSetLoop2->SpreadSample("1000100011000000100010001100000010001000110000001000100011000000", pWavSet11, patternduration_s, 0.25, 0.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop2->Play(&outputParameters);

	WavSet* pWavSetLoop3 = new WavSet;
	pWavSetLoop3->CreateSilence(patternduration_s); //patternduration_s sec
	pWavSetLoop3->SpreadSample("0000000000000000000001000100010000000000000000100000100000000000", pWavSet12, patternduration_s, 0.25, 0.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop3->Play(&outputParameters);

	WavSet* pWavSetLoopMixTemp = new WavSet;
	pWavSetLoopMixTemp->Mix(amplitude, pWavSetLoop1, amplitude, pWavSetLoop2);
	WavSet* pWavSetLoopMix = new WavSet;
	pWavSetLoopMix->Mix(amplitude, pWavSetLoopMixTemp, amplitude, pWavSetLoop3);

	WavSet* pWavSetMain1 = new WavSet;
	pWavSetMain1->CreateSilence(loopduration_s); //loopduration_s sec
	pWavSetMain1->LoopSample(pWavSetLoopMix, loopduration_s, -1.0, 0.0); //from second 0, loop sample during loopduration_s seconds
	//pWavSetMain1->Play(&outputParameters);




	delete pWavSetLoop1;
	delete pWavSetLoopMixTemp;
	delete pWavSetLoopMix;

	pWavSetLoop1 = new WavSet;
	pWavSetLoop1->CreateSilence(patternduration_s); //patternduration_s sec
	pWavSetLoop1->SpreadSample("1000000000000000100000000000000010000000000000001000000000000000", pWavSet3, patternduration_s, 0.25, 0.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop1->SpreadSample("0000000000000000000000000000000000000000000000000000000000000000", pWavSet2, patternduration_s, 0.25, 0.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop1->Play(&outputParameters);

	pWavSetLoopMixTemp = new WavSet;
	pWavSetLoopMixTemp->Mix(amplitude, pWavSetLoop1, amplitude, pWavSetLoop2);
	pWavSetLoopMix = new WavSet;
	pWavSetLoopMix->Mix(amplitude, pWavSetLoopMixTemp, amplitude, pWavSetLoop3);

	WavSet* pWavSetMain2 = new WavSet;
	pWavSetMain2->CreateSilence(loopduration_s); //loopduration_s sec
	pWavSetMain2->LoopSample(pWavSetLoopMix, loopduration_s, -1.0, 0.0); //from second 0, loop sample during loopduration_s seconds

	pWavSetMain1->Concatenate(pWavSetMain2);




	delete pWavSetLoop1;
	delete pWavSetLoopMixTemp;
	delete pWavSetLoopMix;
	delete pWavSetMain2;

	pWavSetLoop1 = new WavSet;
	pWavSetLoop1->CreateSilence(patternduration_s); //patternduration_s sec
	pWavSetLoop1->SpreadSample("1000000000000000100000000000000010000000000000001000000000000000", pWavSet4, patternduration_s, 0.25, 0.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop1->SpreadSample("0000000000000000000000000000000000000000000000000000000000000000", pWavSet2, patternduration_s, 0.25, 0.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop1->Play(&outputParameters);

	pWavSetLoopMix = new WavSet;
	pWavSetLoopMix->Mix(amplitude, pWavSetLoop1, amplitude, pWavSetLoop2);

	pWavSetMain2 = new WavSet;
	pWavSetMain2->CreateSilence(loopduration_s); //loopduration_s sec
	pWavSetMain2->LoopSample(pWavSetLoopMix, loopduration_s, -1.0, 0.0); //from second 0, loop sample during loopduration_s seconds

	pWavSetMain1->Concatenate(pWavSetMain2);




	delete pWavSetLoop1;
	delete pWavSetLoopMix;
	delete pWavSetMain2;

	pWavSetLoop1 = new WavSet;
	pWavSetLoop1->CreateSilence(patternduration_s); //patternduration_s sec
	pWavSetLoop1->SpreadSample("1000000000000000100000000000000010000000000000001000000000000000", pWavSet5, patternduration_s, 0.25, 0.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop1->SpreadSample("0000000000000000000000000000000000000000000000000000000000000000", pWavSet2, patternduration_s, 0.25, 0.0); //pattern over 2 sec, sample duration 0.25sec and with pattern offset of 0sec
	//pWavSetLoop1->Play(&outputParameters);

	pWavSetLoopMix = new WavSet;
	pWavSetLoopMix->Mix(amplitude, pWavSetLoop1, amplitude, pWavSetLoop2);

	pWavSetMain2 = new WavSet;
	pWavSetMain2->CreateSilence(loopduration_s); //loopduration_s sec
	pWavSetMain2->LoopSample(pWavSetLoopMix, loopduration_s, -1.0, 0.0); //from second 0, loop sample during loopduration_s seconds

	pWavSetMain1->Concatenate(pWavSetMain2);




	pWavSetMain1->Play(&outputParameters);

	delete pWavSetLoop1;
	delete pWavSetLoop2;
	delete pWavSetLoop3;
	delete pWavSetLoopMix;
	delete pWavSetMain1;
	delete pWavSetMain2;


	delete pWavSet1;
	delete pWavSet2;
	delete pWavSet3;
	delete pWavSet4;
	delete pWavSet5;
	delete pWavSet6;
	delete pWavSet7;
	delete pWavSet8;
	delete pWavSet9;

	delete pWavSet11;
	delete pWavSet12;

	/////////////////////
	//terminate portaudio
	/////////////////////
	Pa_Terminate();
	//if(pInstrumentSet) delete pInstrumentSet;
	printf("Exiting!\n"); fflush(stdout);

	nShowCmd = false;
	ShellExecuteA(NULL, "open", "end.bat", "", NULL, nShowCmd);
	return 0;
}

