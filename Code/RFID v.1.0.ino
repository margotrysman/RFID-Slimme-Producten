
//add libraries
#include <SPI.h> //library used to communicate with SPI devices, like the RFID scanner
//#include <MFRC522.h> //library used to work specifically with RFID readers

#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>

//#define RST_PIN 9  //pin where RST > RFID is connected
//#define SS_PIN 10  //pin where SPI SS > RFID is connected

//MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance using the necessary pins
//byte accesUID2[7] = { 0x04, 0x27, 0x17, 0xE2, 0x3D, 0x75, 0x80 }; //create array consisting of bytes, with a starting value (each starting with 0x signifying them as individual bytes)
PN532_SPI pn532spi(SPI, 10);   // SS pin
NfcAdapter nfc = NfcAdapter(pn532spi);
bool cardCorrect = false; //create a bool variable showing if the card is the correct one or not
String validUID = "04 2C 77 EA 3D 75 80";

void setup() {
  Serial.begin(115200);  // Initialize serial communications with the PC    
  Serial.println("start");
  /*SPI.begin();                        // Initiate SPI bus
  mfrc522.PCD_Init();                 // Initiate MFRC522
  delay(4);                           // Optional delay during startup
  mfrc522.PCD_DumpVersionToSerial(); */ // Dumps some info on the PCD and MFRC522 Card Reader, like version
  nfc.begin();
  Serial.println(F("Ready to scan")); //additional feedback to show if setup was succesfull
}

void loop() {

if (!nfc.tagPresent())
    {
        return;
    }

    Serial.println("New Card Found"); //if a new card is presented, it gives feedback

    NfcTag tag = nfc.read();

    String tagUid = tag.getUidString(); //Get UID from the card read

    Serial.print("UID: "); //Print UID for reference (during coding)
    Serial.println(tagUid);

    if (tagUid == validUID)
    {
        Serial.println("Correct card!"); //if UID is correct, print it
        cardCorrect = true;
    }
    else
    {
        Serial.println("Wrong card");
        cardCorrect = false;
    }

    /*Serial.print("cardCorrect = ");
    Serial.println(cardCorrect);*/

    delay(1000);
}
