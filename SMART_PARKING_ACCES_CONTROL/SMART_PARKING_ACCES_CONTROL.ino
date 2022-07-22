#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

#define AccesFlag_PIN 2
#define Gate_PIN 3
#define Max_Acces 3

byte Count_acces=0;
byte CodeVerif=0;
byte Code_Acces[4]={0×20, 0×23, 0×2B};

MFRC522 rfid(SS_PIN, RST_PIN); // instance de class

//initiallisation du tableau d'exposition des nouveau NUID
byte nuidPICC[4];


void setup() {
  // put your setup code here, to run once:
//init RS232
Serial.begin();

//init SPI bus
SPI.begin();

//init MFRC522
rfid.PCD_init();

//init LEDs
pinMode(AccesFlag_PIN, OUTPUT);
pinMode(Gate_PIN, OUTPUT);

digitalWrite(AccesFlag_PIN, LOW);
digitalWrite(Gate_PIN, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
// initialliser la boucle si aucun badge n'est present
if(!rfid.PICC_IsNewCardPresent())
  return;
  
// verifier la presence d'un nouveau badge
if(!rfid.PICC_RealdCardSerial();
  return;

// AFFICHAGE
Serial.println(F("UN BADGE EST DETECTÉ"));

// ENREGISTRER L'ID DU BADGE (4 octets)
for(byte i = 0; i < 4; i++){
  nuidPICC[i] = rfid.uid.uidByte[i];
  }

// VERIFICATION DU CODE
CodeVerif = GetAccesStarte(Code_Acces, nuidPICC);
if(CodeVerif != 1){
  Count_acces += 1;

  if(Count_acces == Max_Acces){
    // DEPASSEMENT DES TENTATIVES (CLIGNOTTEMENT INFINI)
    while(1){
      digitalWrite(AccesFlag_PIN, HIGH);
      delay(200);
      digitalWrite(AccesFlag_PIN, LOW);
      delay(200);
      //AFFICHAGE
      Serial.println("ALARME!!!");
      }
    }

    else{
      // AFFICHAGE
      Serial.println("CODE ÉRRONÉ");

      //UN SEUL CLIGNOTTEMENT : CODE ÉRRONÉ
      digitalWrite(AccesFlag_PIN, HIGH);
      delay(1000);
      digitalWrite(AccesFlag_PIN, LOW);
      }
  }

  else{
    //AFFICHAGE
    Serial.println("OUVERTURE DE LA PORTE");

    //OUVERTURE DE LA PORTE ET INSTALLATION
    digitalWrite(Gate_PIN, HIGH);
    delay(3000);
    digitalWrite(Gate_PIN, LOW);
    Count_acces = 0;
    }

    //AFFICHAGE DE L'IDENTIFIANT
    Serial.println("L'UID DU TAG EST :");
    for(byte i = 0; i < 4; i++){
      Serial.print(nuidPICC[i], HEX);
      Serial.print(" ");
      }
      Serial.println();

      //Re-init RFID
      rfid.PICC_HaltA(); // Halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
}

byte GetAccesStarte(byte *CodeAcces.byte *NewCode){
  byte StarteAcces = 0;
  if((CodeAcces[0] == NewCode[0]) && (CodeAcces[1] == NewCode[1]) && (CodeAcces[2] == NewCode[2]) && (CodeAcces[3] == NewCode[3])) 
    return StarteAcces = 1;
  else
    return StarteAcces = 0;
  }

}
