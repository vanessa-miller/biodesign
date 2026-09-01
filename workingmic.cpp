#include <Audio.h>

const int ledPin = LED_BUILTIN;   // pin 13
int soundThreshold = 1500;

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
    if (counter % 2 == 0) {          // only report every 2nd buffer → half the output rate
      Serial.print("Amplitude:");
      Serial.println(maxAmplitude);
    }

    digitalWrite(ledPin, (maxAmplitude > soundThreshold) ? HIGH : LOW);
  }
}
