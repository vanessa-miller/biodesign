#include <Audio.h>
#include <Wire.h>

AudioInputI2S     i2sIn;
AudioRecordQueue  queue1;
AudioConnection   patchCord1(i2sIn, 0, queue1, 0); // left channel

void setup() {
  Serial.begin(115200);
  while (!Serial);
  AudioMemory(8);
  queue1.begin();
}

void loop() {
  if (queue1.available() >= 1) {
    int16_t *data = queue1.readBuffer();
    for (int i = 0; i < 128; i++) {
      if (data[i] != 0) Serial.println(data[i]);
    }
    queue1.freeBuffer();
  }
}
