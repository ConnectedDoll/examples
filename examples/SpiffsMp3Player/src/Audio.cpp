#include "Audio.h"

Audio::Audio() {
}

Audio::~Audio() {

}

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void Audio::MDCallback(void *cbData, const char *type, bool isUnicode, const char *string) {
  const char *ptr = reinterpret_cast<const char *>(cbData);
  (void) isUnicode; // Punt this ball for now
  // Note that the type and string may be in PROGMEM, so copy them to RAM for printf
  char s1[32], s2[64];
  strncpy_P(s1, type, sizeof(s1));
  s1[sizeof(s1)-1]=0;
  strncpy_P(s2, string, sizeof(s2));
  s2[sizeof(s2)-1]=0;
  Serial.printf("METADATA(%s) '%s' = '%s'\n", ptr, s1, s2);
  Serial.flush();
}

// Called when there's a warning or error (like a buffer underflow or decode hiccup)
void Audio::StatusCallback(void *cbData, int code, const char *string) {
  const char *ptr = reinterpret_cast<const char *>(cbData);
  // Note that the string may be in PROGMEM, so copy it to RAM for printf
  char s1[64];
  strncpy_P(s1, string, sizeof(s1));
  s1[sizeof(s1)-1]=0;
  Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
  Serial.flush();
}

void Audio::begin(int bclkPin, int wclkPin, int doutPin) {
  // out = new AudioOutputI2SNoDAC();
  
  out = new AudioOutputI2S();
  out->SetPinout(bclkPin, wclkPin, doutPin);
  out->SetOutputModeMono(true);
}

// 音量設定
void Audio::setGain(float volume) {
  out->SetGain(volume);
}

// http stream での MP3 再生
bool Audio::play(const char* url) {
  Serial.println("play");
  streamFile = new AudioFileSourceICYStream(url);
  buff = new AudioFileSourceBuffer(streamFile, 2048);
  mp3 = new AudioGeneratorMP3();
  return mp3->begin(buff, out);
}


// SPIFFS ファイルの MP3 再生
bool Audio::playFile(const char* path) {
  Serial.println("play");
  SPIFFS.begin();
  file = new AudioFileSourceSPIFFS(path);
  id3 = new AudioFileSourceID3(file);
  mp3 = new AudioGeneratorMP3();
  return mp3->begin(id3, out);
}

void  Audio::stop() {
  if (mp3 == nullptr) return;
  if (mp3->isRunning()) {
    mp3->stop();
  }
}


bool Audio::isRunning() {
  return mp3->isRunning();
}

void Audio::loop() {
  if (mp3 == nullptr) return;
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  }
}