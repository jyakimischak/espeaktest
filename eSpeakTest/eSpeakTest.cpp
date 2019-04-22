

#include <espeak/speak_lib.h>
#include<stdlib.h>
#include<Windows.h>
#include<portaudio.h>


const int NUM_CHANNELS = 1;
const int PA_SAMPLE_TYPE = paInt16;
const int SAMPLE_RATE = 22050;
const int FRAMES_PER_BUFFER = 10;
PaStreamParameters inputParameters;
PaStreamParameters outputParameters;
PaStream* stream;
//const int* sampleBlock;
void* sampleBlock[2];
PaError err;

void initStream() {
	/* -- initialize PortAudio -- */
	err = Pa_Initialize();
	if (err != paNoError) {
		printf("error");
		return;
	}
	/* -- setup input and output -- */
	inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
	inputParameters.channelCount = NUM_CHANNELS;
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;
	outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
	outputParameters.channelCount = NUM_CHANNELS;
	outputParameters.sampleFormat = PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	/* -- setup stream -- */
	err = Pa_OpenStream(
		&stream,
		&inputParameters,
		&outputParameters,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,      /* we won't output out of range samples so don't bother clipping them */
		NULL, /* no callback, use blocking API */
		NULL); /* no callback, so no callback userData */
	if (err != paNoError) {
		printf("error");
		return;
	}
	/* -- start stream -- */
	err = Pa_StartStream(stream);
	if (err != paNoError) {
		printf("error");
		return;
	}
}

void closeStream() {
	err = Pa_StopStream(stream);
	if (err != paNoError) {
		printf("error");
		return;
	}
	/* -- don't forget to cleanup! -- */
	err = Pa_CloseStream(stream);
	if (err != paNoError) {
		printf("error");
		return;
	}
	Pa_Terminate();
}

int SynthCallback(short* wav, int numsamples, espeak_EVENT* events) {
	err = Pa_WriteStream(stream, wav, numsamples);
	if (err) {
		printf("error: %i", err);
		return 0;
	}
	return 0;
}

int main() {
	initStream();

	int sr = espeak_Initialize(AUDIO_OUTPUT_SYNCHRONOUS, 0, "C:\\Users\\karma\\projects\\eSpeakTest\\eSpeakTest", 0);
	printf("sample rate: %i\n", sr);
	espeak_SetSynthCallback(SynthCallback);
	espeak_ERROR err = espeak_Synth("Hello world", 20, 0, POS_CHARACTER, 0, espeakCHARS_UTF8, NULL, NULL);
	printf("return code: %i\n", (int)err);
	espeak_Terminate();

	closeStream();
}


























////---------------------------------------------------- DEBUG ----------------------------------------------------
////Play a test sound
//void paTest() {
//
//	const int NUM_CHANNELS = 1;
//	const int PA_SAMPLE_TYPE = paInt16;
//	const int SAMPLE_RATE = 2000;
//	const int FRAMES_PER_BUFFER = 10;
//
//	PaStreamParameters inputParameters;
//	PaStreamParameters outputParameters;
//	PaStream* stream;
//	//const int* sampleBlock;
//	void* sampleBlock[2];
//
//	/* -- initialize PortAudio -- */
//	PaError err = Pa_Initialize();
//	if (err != paNoError) {
//		printf("error");
//		return;
//	}
//	/* -- setup input and output -- */
//	inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
//	inputParameters.channelCount = NUM_CHANNELS;
//	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
//	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency;
//	inputParameters.hostApiSpecificStreamInfo = NULL;
//	outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
//	outputParameters.channelCount = NUM_CHANNELS;
//	outputParameters.sampleFormat = PA_SAMPLE_TYPE;
//	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
//	outputParameters.hostApiSpecificStreamInfo = NULL;
//	/* -- setup stream -- */
//	err = Pa_OpenStream(
//		&stream,
//		&inputParameters,
//		&outputParameters,
//		SAMPLE_RATE,
//		FRAMES_PER_BUFFER,
//		paClipOff,      /* we won't output out of range samples so don't bother clipping them */
//		NULL, /* no callback, use blocking API */
//		NULL); /* no callback, so no callback userData */
//	if (err != paNoError) {
//		printf("error");
//		return;
//	}
//	/* -- start stream -- */
//	err = Pa_StartStream(stream);
//	if (err != paNoError) {
//		printf("error");
//		return;
//	}
//	printf("Wire on. Will run one minute.\n"); fflush(stdout);
//	/* -- Here's the loop where we pass data from input to output -- */
//	for (int i = 0; i < (60 * SAMPLE_RATE) / FRAMES_PER_BUFFER; ++i)
//	{
//		err = Pa_WriteStream(stream, sampleBlock, FRAMES_PER_BUFFER);
//		if (err) {
//			printf("error");
//			return;
//		}
//		//err = Pa_ReadStream(stream, sampleBlock, FRAMES_PER_BUFFER);
//		//if (err) {
//		//	printf("error");
//		//	return;
//		//}
//	}
//	/* -- Now we stop the stream -- */
//	err = Pa_StopStream(stream);
//	if (err != paNoError) {
//		printf("error");
//		return;
//	}
//	/* -- don't forget to cleanup! -- */
//	err = Pa_CloseStream(stream);
//	if (err != paNoError) {
//		printf("error");
//		return;
//	}
//	Pa_Terminate();
//}
//
////---------------------------------------------------- DEBUG ----------------------------------------------------
//int SynthCallback(short* wav, int numsamples, espeak_EVENT* events) {
//
//	const int NUM_CHANNELS = 1;
//	const int PA_SAMPLE_TYPE = paInt16;
//	const int SAMPLE_RATE = 22050;
//	const int FRAMES_PER_BUFFER = 10;
//
//	PaStreamParameters inputParameters;
//	PaStreamParameters outputParameters;
//	PaStream* stream;
//	//const int* sampleBlock;
//	void* sampleBlock[2];
//
//	/* -- initialize PortAudio -- */
//	PaError err = Pa_Initialize();
//	if (err != paNoError) {
//		printf("error");
//		return 0;
//	}
//	/* -- setup input and output -- */
//	inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
//	inputParameters.channelCount = NUM_CHANNELS;
//	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
//	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency;
//	inputParameters.hostApiSpecificStreamInfo = NULL;
//	outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
//	outputParameters.channelCount = NUM_CHANNELS;
//	outputParameters.sampleFormat = PA_SAMPLE_TYPE;
//	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
//	outputParameters.hostApiSpecificStreamInfo = NULL;
//	/* -- setup stream -- */
//	err = Pa_OpenStream(
//		&stream,
//		&inputParameters,
//		&outputParameters,
//		SAMPLE_RATE,
//		FRAMES_PER_BUFFER,
//		paClipOff,      /* we won't output out of range samples so don't bother clipping them */
//		NULL, /* no callback, use blocking API */
//		NULL); /* no callback, so no callback userData */
//	if (err != paNoError) {
//		printf("error");
//		return 0;
//	}
//	/* -- start stream -- */
//	err = Pa_StartStream(stream);
//	if (err != paNoError) {
//		printf("error");
//		return 0;
//	}
//
//	err = Pa_WriteStream(stream, wav, numsamples);
//	if (err) {
//		printf("error: %i", err);
//		return 0;
//	}
//
//
//	/* -- Now we stop the stream -- */
//	err = Pa_StopStream(stream);
//	if (err != paNoError) {
//		printf("error");
//		return 0;
//	}
//	/* -- don't forget to cleanup! -- */
//	err = Pa_CloseStream(stream);
//	if (err != paNoError) {
//		printf("error");
//		return 0;
//	}
//	Pa_Terminate();
//	return 0;
//}
//
//
//
////int SynthCallback(short* wav, int numsamples, espeak_EVENT* events) {
////	printf("num samples: %i\n", numsamples);
////	return 0;
////}
//int main()
//{
//	//paTest();
//	//return 0;
//
//	int sr = espeak_Initialize(AUDIO_OUTPUT_SYNCHRONOUS, 0, "C:\\Users\\karma\\projects\\eSpeakTest\\eSpeakTest", 0);
//	printf("sample rate: %i\n", sr);
//	espeak_SetSynthCallback(SynthCallback);
//	espeak_ERROR err = espeak_Synth("hello, hello", 20, 0, POS_CHARACTER, 0, espeakCHARS_UTF8, NULL, NULL);
//	printf("return code: %i\n", (int)err);
//	espeak_Terminate();
//}





























///*
//   TITLE: Simple C/C++ Program showing use of speak_lib.h
//   AUTHOR:Dhananjay Singh
//   LICENSE: GPLv2
//*/
//#include <string.h>
//#include <malloc.h>
//#include <espeak/speak_lib.h>
//
//
//
//espeak_POSITION_TYPE position_type;
//espeak_AUDIO_OUTPUT output;
//char path[] = { "C:\\Users\\karma\\projects\\eSpeakTest\\eSpeakTest" };
//int Buflength = 500, Options = 0;
//void* user_data;
//t_espeak_callback* SynthCallback;
//espeak_PARAMETER Parm;
//
///*
//   FROM speak_lib.h :
//
//   output: the audio data can either be played by eSpeak or passed back by the SynthCallback function.
//
//   Buflength:  The length in mS of sound buffers passed to the SynthCallback function.
//
//   options: bit 0: 1=allow espeakEVENT_PHONEME events.
//
//   path: The directory which contains the espeak-data directory, or NULL for the default location.
//
//   espeak_Initialize() Returns: sample rate in Hz, or -1 (EE_INTERNAL_ERROR).
//*/
//
//char Voice[] = { "lt+klatt2" };
///*
//	Voice: Refer to speak_lib.h
//*/
//
//char text[30] = { "Labas. Šauk. Laikas. Taika" };
//unsigned int Size, position = 0, end_position = 0, flags = espeakCHARS_AUTO, * unique_identifier;
//
///*
//   text: The text to be spoken, terminated by a zero character. It may be either 8-bit characters,
//	  wide characters (wchar_t), or UTF8 encoding.  Which of these is determined by the "flags"
//	  parameter.
//
//   Size: Equal to (or greatrer than) the size of the text data, in bytes.  This is used in order
//	  to allocate internal storage space for the text.  This value is not used for
//	  AUDIO_OUTPUT_SYNCHRONOUS mode.
//
//   position:  The position in the text where speaking starts. Zero indicates speak from the
//	  start of the text.
//
//   position_type:  Determines whether "position" is a number of characters, words, or sentences.
//	  Values:
//
//   end_position:  If set, this gives a character position at which speaking will stop.  A value
//	  of zero indicates no end position.
//
//   flags:  These may be OR'd together:
//	  Type of character codes, one of:
//		 espeakCHARS_UTF8     UTF8 encoding
//		 espeakCHARS_8BIT     The 8 bit ISO-8859 character set for the particular language.
//		 espeakCHARS_AUTO     8 bit or UTF8  (this is the default)
//		 espeakCHARS_WCHAR    Wide characters (wchar_t)
//
//	  espeakSSML   Elements within < > are treated as SSML elements, or if not recognised are ignored.
//
//	  espeakPHONEMES  Text within [[ ]] is treated as phonemes codes (in espeak's Hirshenbaum encoding).
//
//	  espeakENDPAUSE  If set then a sentence pause is added at the end of the text.  If not set then
//		 this pause is suppressed.
//
//   unique_identifier: message identifier; helpful for identifying later
//	 data supplied to the callback.
//
//   user_data: pointer which will be passed to the callback function.
//
//   espeak_Synth() Returns: EE_OK: operation achieved
//						   EE_BUFFER_FULL: the command can not be buffered;
//						   you may try after a while to call the function again.
//						   EE_INTERNAL_ERROR.
//*/
//
//
//
//
//
//int main(int argc, char* argv[])
//{
//	output = AUDIO_OUTPUT_PLAYBACK;
//	int I, Run = 1, L;
//	espeak_Initialize(output, Buflength, path, Options);
//	//espeak_SetVoiceByName(Voice);
//	const char* langNativeString = "lt"; //Default to US English
//	espeak_VOICE voice;
//	memset(&voice, 0, sizeof(espeak_VOICE)); // Zero out the voice first
//	voice.languages = langNativeString;
//	voice.name = "klatt";
//	voice.variant = 2;
//	voice.gender = 1;
//	espeak_SetVoiceByProperties(&voice);
//	Size = strlen(text) + 1;
//	printf("Saying  '%s'", text);
//	espeak_Synth(text, Size, position, position_type, end_position, flags,
//		unique_identifier, user_data);
//	espeak_Synchronize();
//	printf("\n:Done\n");
//	return 0;
//}



//#include <iostream>
//
//#include <string.h>
//#include <malloc.h>
//#include <espeak/speak_lib.h>
//
//
//
//espeak_POSITION_TYPE position_type;
//espeak_AUDIO_OUTPUT output;
//char path[] = { "C:\\Users\\karma\\projects\\eSpeakTest\\eSpeakTest" };
//int Buflength = 500, Options = 0;
//void* user_data;
//t_espeak_callback* SynthCallback;
//espeak_PARAMETER Parm;
//
//
//
////char Voice[] = {"lt+klatt2"};
//char Voice[] = { "English" };
//
//char text[30] = { "this is a english test" };
//unsigned int Size, position = 0, end_position = 0, flags = espeakCHARS_AUTO, * unique_identifier;
//
//
//
//
//int main(int argc, char* argv[])
//{
//	output = AUDIO_OUTPUT_PLAYBACK;
//	int I, Run = 1, L;
//	espeak_Initialize(output, Buflength, path, Options);
//	espeak_SetVoiceByName(Voice);
//	//const char *langNativeString = "lt"; //Default to US English
//	const char* langNativeString = "en"; //Default to US English
//	espeak_VOICE voice;
//	memset(&voice, 0, sizeof(espeak_VOICE)); // Zero out the voice first
//	voice.languages = langNativeString;
//	//voice.name = "klatt";
//	voice.name = "US";
//	voice.variant = 2;
//	voice.gender = 1;
//	//espeak_SetVoiceByProperties(&voice);
//	Size = strlen(text) + 1;
//	printf("Saying  '%s'", text);
//
//	espeak_Synth(text, Size, position, position_type, end_position, flags,
//		unique_identifier, user_data);
//
//
//
//	espeak_Synchronize();
//	printf("\n:Done\n");
//	return 0;
//}









//// eSpeakTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//
//#include <iostream>
//#include <espeak/speak_lib.h>
//
//int main()
//{
//    std::cout << "Hello World!\n"; 
//
//	espeak_ListVoices(NULL);
//}
//
//// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
//// Debug program: F5 or Debug > Start Debugging menu
//
//// Tips for Getting Started: 
////   1. Use the Solution Explorer window to add/manage files
////   2. Use the Team Explorer window to connect to source control
////   3. Use the Output window to see build output and other messages
////   4. Use the Error List window to view errors
////   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
////   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
