
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

void sayLine(const char* voice, const char* line) {
	printf("%s\n", voice);
	espeak_SetVoiceByName(voice);
	espeak_SetSynthCallback(SynthCallback);
	espeak_ERROR err = espeak_Synth(line, 20, 0, POS_CHARACTER, 0, espeakCHARS_UTF8, NULL, NULL);
}

int main() {
	initStream();

	int sr = espeak_Initialize(AUDIO_OUTPUT_SYNCHRONOUS, 0, "C:\\Users\\karma\\projects\\eSpeakTest\\eSpeakTest", 0);
	printf("sample rate: %i\n\n\n", sr);

	//sayLine("mk", "I regret to inform you that my systems are maa aa aalfunctioning.");
	sayLine("croak", "Why the hell did I take this job.  I could be a bank machine.");

	////good ones
	//sayLine("default", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("en-us", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("klatt", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("m1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("m4", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("vi", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("en-wm", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("as", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("croak", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("f1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("f2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("f4", "Hello passengers. Welcome to the starship enterprise.");

	////fun
	//sayLine("whisper", "I've got a secret.");

	////broken
	//sayLine("da", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("fr-be", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("hu", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mk", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("jbo", "Hello passengers. Welcome to the starship enterprise.");


	//ALL
	//sayLine("de", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("default", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("en-us", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("es-la", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("fr", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("pt", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("croak", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("f1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("f2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("f3", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("f4", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("f5", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("klatt", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("klatt2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("klatt3", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("klatt4", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("m1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("m2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("m3", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("m4", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("m5", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("m6", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("m7", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("whisper", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("whisperf", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("fa", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("fa-pin", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("hi", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("hy", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("hy-west", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("id", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ka", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("kn", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ku", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ml", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ms", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ne", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("pa", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ta", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("tr", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("vi", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("vi-hue", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("vi-sgn", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("zh", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("zh-yue", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("an", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("bg", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("bs", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ca", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("cs", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("cy", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("da", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("el", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("es", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("et", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("fi", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("fr-be", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ga", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("hr", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("hu", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("is", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("it", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("lt", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("lv", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mk", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("nl", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("no", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("pl", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("pt-pt", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ro", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ru", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("sk", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("sq", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("sr", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("sv", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-af1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-af1-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-br1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-br3", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-br4", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-cr1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-cz2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-de2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-de3", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-de4", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-de4-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-de5", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-de5-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-de6", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-de6-grc", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-de7", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-ee1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-en1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-es1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-es2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-fr1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-fr1-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-fr4", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-fr4-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-gr2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-gr2-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-hu1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-hu1-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-ic1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-id1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-ir1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-ir2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-it3", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-it4", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-la1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-mx1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-mx2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-nl2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-nl2-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-pl1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-pl1-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-pt1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-ro1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-ro1-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-sw1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-sw1-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-sw2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-sw2-en", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-tr1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-tr2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-us1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-us2", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-us3", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("mb-vz1", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("af", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("en-n", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("en-rp", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("en-sc", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("en-wi", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("en-wm", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("eo", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("grc", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("jbo", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("la", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("lfn", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("sw", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("am", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("as", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("az", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("bn", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("eu", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("gd", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("gu", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("kl", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ko", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("nci", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("or", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("pap", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("si", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("sl", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("te", "Hello passengers. Welcome to the starship enterprise.");
	//sayLine("ur", "Hello passengers. Welcome to the starship enterprise.");

	printf("\n\n\n");

	espeak_Terminate();
	closeStream();
}
