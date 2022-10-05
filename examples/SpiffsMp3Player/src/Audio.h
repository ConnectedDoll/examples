#ifndef __AUDIO_H_
#define __AUDIO_H_

#include <Arduino.h>
#include <I2S.h>

// cd lib
// git clone git@github.com:earlephilhower/ESP8266Audio.git

#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

#include "AudioOutputI2SNoDAC.h"
#include <SPIFFS.h>
#include "AudioFileSourceSPIFFS.h"
#include "AudioFileSourceID3.h"

class Audio {
public:
    Audio();
    ~Audio();
    void begin(int bclkPin, int wclkPin, int doutPin);
    bool play(const char* url);
    void stop();
    void setGain(float volume);
    void loop();
    bool isRunning();
    
    bool playFile(const char* file);
private:
    static void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string);
    static void StatusCallback(void *cbData, int code, const char *string);

    AudioOutputI2S *out;
    AudioGeneratorMP3 *mp3;
    AudioFileSourceICYStream *streamFile;
    AudioFileSourceBuffer *buff;

    AudioFileSourceSPIFFS *file;
    AudioFileSourceID3 *id3;
};

#endif // __AUDIO_H_