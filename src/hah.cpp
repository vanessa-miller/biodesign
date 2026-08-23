#include <Audio.h>

const int ledPin = LED_BUILTIN;
const int soundThreshold = 2000; // tune this if needed for your mic level

AudioInputI2S     i2sIn;
AudioRecordQueue  queue1;
AudioConnection   patchCord1(i2sIn, 0, queue1, 0); // left channel

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  AudioMemory(8);
  queue1.begin();

  Serial.println("Microphone audio trigger ready");
}

void loop() {
  if (queue1.available() >= 1) {
    int16_t *data = queue1.readBuffer();
    int maxAmplitude = 0;

    for (int i = 0; i < 128; i++) {
      int sample = data[i];
      int sampleAbs = abs(sample);
      if (sampleAbs > maxAmplitude) {
        maxAmplitude = sampleAbs;
      }
    }

    queue1.freeBuffer();

    bool soundDetected = (maxAmplitude > soundThreshold);
    digitalWrite(ledPin, soundDetected ? HIGH : LOW);

    if (soundDetected) {
      Serial.print("Sound detected! Peak amplitude: ");
      Serial.println(maxAmplitude);
    }
  }
}