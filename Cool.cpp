#include <Audio.h>

const int ledPin = LED_BUILTIN;
const int soundThreshold = 2000; // tune this if needed for your mic level

AudioInputI2S     i2sIn;
AudioRecordQueue  queue1;
AudioConnection patchCord1(i2sIn, 1, queue1, 0); // try channel 1

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
      int sampleAbs = abs(data[i]);
      if (sampleAbs > maxAmplitude) {
        maxAmplitude = sampleAbs;
      }
    }

    queue1.freeBuffer();

    Serial.println(maxAmplitude); // ALWAYS print, for calibration

    bool soundDetected = (maxAmplitude > soundThreshold);
    digitalWrite(ledPin, soundDetected ? HIGH : LOW);
  }
}
