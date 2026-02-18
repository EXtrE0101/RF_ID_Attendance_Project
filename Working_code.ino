#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

#define GREEN_LED 4
#define RED_LED 5
#define BUZZER 6

MFRC522 rfid(SS_PIN, RST_PIN);

// Add your student cards here
String studentUIDs[] = {
  "43A79B2C",
  "12AB34CD",
  "98FF21A4"
};

String studentNames[] = {
  "Rahul",
  "Aman",
  "Priya"
};

int totalStudents = 3;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("Attendance System Ready...");
}

void loop() {

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  String uidString = "";

  for (byte i = 0; i < rfid.uid.size; i++) {
    uidString += String(rfid.uid.uidByte[i], HEX);
  }

  uidString.toUpperCase();

  Serial.print("Scanned UID: ");
  Serial.println(uidString);

  bool found = false;

  for (int i = 0; i < totalStudents; i++) {

    if (uidString == studentUIDs[i]) {

      Serial.print(studentNames[i]);
      Serial.println(" - Present ✅");

      digitalWrite(GREEN_LED, HIGH);

      // Sweet melody
      tone(BUZZER, 523); delay(150);
      tone(BUZZER, 659); delay(150);
      tone(BUZZER, 784); delay(150);
      noTone(BUZZER);

      found = true;
      break;
    }
  }

  if (!found) {

    Serial.println("Unknown Card ❌");

    digitalWrite(RED_LED, HIGH);

    tone(BUZZER, 200);
    delay(800);
    noTone(BUZZER);
  }

  delay(2000);
}
