#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

String student1 = "43A79B2C";   // Replace with real UID
String student2 = "12AB34CD";   // Replace with real UID

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Attendance System Ready...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  String uidString = "";

  for (byte i = 0; i < rfid.uid.size; i++) {
    uidString += String(rfid.uid.uidByte[i], HEX);
  }

  uidString.toUpperCase();

  Serial.print("Card UID: ");
  Serial.println(uidString);

  if (uidString == student1) {
    Serial.println("Student 1 - Present");
  }
  else if (uidString == student2) {
    Serial.println("Student 2 - Present");
  }
  else {
    Serial.println("Unknown Card");
  }

  delay(2000); // Prevent multiple scans
}
