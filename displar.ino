#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

const int ledPin = 8;
int ringHour = 12;     // Example scheduled hour
int ringMinute = 15;   // Example scheduled minute

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();

  if (now.hour() == ringHour && now.minute() == ringMinute && now.second() == 0) {
    Serial.println("💡 LED sequence started!");
    digitalWrite(ledPin, HIGH);
    delay(6000);  // First light ON 6s
    digitalWrite(ledPin, LOW);
    delay(4000);  // Pause 4s
    digitalWrite(ledPin, HIGH);
    delay(5000);  // Confirmation light ON 5s
    digitalWrite(ledPin, LOW);
    Serial.println("✅ Sequence complete!");
    delay(60000); // Prevent repeat within same minute
  }
}
