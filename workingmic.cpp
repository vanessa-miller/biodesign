#include <Audio.h>

const int ledPin = LED_BUILTIN;
int soundThreshold = 1500;

const int plotEvery = 8;   // plot 1 out of every N buffers — raise for slower plot

AudioInputI2S     i2sIn;
AudioRecordQueue  queue1;
AudioConnection patchCord1(i2sIn, 0, queue1, 0);

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);
  delay(1000);
  AudioMemory(8);
  queue1.begin();
  Serial.println("Ready");
}

void loop() {
  static int counter = 0;

  if (queue1.available() >= 1) {
    int16_t *data = queue1.readBuffer();
    int maxAmplitude = 0;
    for (int i = 0; i < 128; i++) {
      int sampleAbs = abs(data[i]);
      if (sampleAbs > maxAmplitude) maxAmplitude = sampleAbs;
    }
    queue1.freeBuffer();

    counter++;
    if (counter >= plotEvery) {
      counter = 0;
      Serial.print("Amplitude:");
      Serial.println(maxAmplitude);
    }

    digitalWrite(ledPin, (maxAmplitude > soundThreshold) ? HIGH : LOW);
  }
}
