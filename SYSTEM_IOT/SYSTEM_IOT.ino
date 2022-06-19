
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

    //CAPTEUR 1
#define PIN_TRIGGER_1 2
#define PIN_ECHO_1 4

    //CAPTEUR 2
#define PIN_TRIGGER_2 0
#define PIN_ECHO_2 16

     //CAPTEUR 3

#define PIN_TRIGGER_3 5
#define PIN_ECHO_3 17

    //CAPTEUR 4

#define PIN_TRIGGER_4 12
#define PIN_ECHO_4 13

    //CAPTEUR 5

#define PIN_TRIGGER_5 14
#define PIN_ECHO_5 27

long dure_signal, distance_signal_1, distance_signal_2, distance_signal_3, distance_signal_4, distance_signal_5;

int httpResponseCode;

String serverPath;

// DEFINITION DES IDENTIFIANTS DE CONNEXION WIFI
//const char* ssid = "ETECH CENTER";
//const char* password = "abc1234#";

const char* ssid = "TECNO SPARK 6";
const char* password = "a2234567";


//String serverName = "https://solar-space-572494.postman.co/me/apis";
//String serverName = "localhost:4000/graphql";
String serverName = "https://secure-beach-35873.herokuapp.com/places/9rFmlH0KV2NJGBD43Dbh";


//les variables suivantes
//sont des longueurs non signées car le temps, mesuré en
// millisecondes, deviendra rapidement un nombre plus
//grand que celui qui peut être stocké dans un int.
unsigned long lastTime = 0;

String libre ;


unsigned long timerDelay = 5000; // 5 secondes

void setup() {
          Serial.begin(9600);
        
          pinMode(PIN_TRIGGER_1, OUTPUT);
          pinMode(PIN_ECHO_1, INPUT );
          
          pinMode(PIN_TRIGGER_2, OUTPUT);
          pinMode(PIN_ECHO_2, INPUT );
          
          pinMode(PIN_TRIGGER_3, OUTPUT);
          pinMode(PIN_ECHO_3, INPUT );
          
          pinMode(PIN_TRIGGER_4, OUTPUT);
          pinMode(PIN_ECHO_4, INPUT );
          
          pinMode(PIN_TRIGGER_5, OUTPUT);
          pinMode(PIN_ECHO_5, INPUT );
        
          //CONNEXION WIFI
          WiFi.begin(ssid, password);
          Serial.println("Connection");
          while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
          }
          Serial.println("");
          Serial.print("Connecté au réseau WiFi avec adresse IP : ");
          Serial.println(WiFi.localIP());
        
          Serial.println("il faudra attendre 5 secondes avant de publier la première lecture.");
}

void loop() {
  
  
        Serial.println("DEBUT LOOP");
          mesureDistance_1(); // appel de la fontion qui mesure la distance
        
          mesureDistance_2(); // appel de la fontion qui mesure la distance
        
          mesureDistance_3(); // appel de la fontion qui mesure la distance
        
          mesureDistance_4(); // appel de la fontion qui mesure la distance
        
          mesureDistance_5(); // appel de la fontion qui mesure la distance
        
          //Envoyer une requête HTTP DE MISE A JOUR TOUTES les 10 minutes
          //if (((millis() - lastTime) > timerDelay) && (WiFi.status() == WL_CONNECTED)) {
            //Vérifier l'état de la connexion Wi-Fi
            if (WiFi.status() == WL_CONNECTED) {
        
              WiFiClient client;
        
              //ENVOI DE LA REQUETTE HTTP DE MISE A JOUR "PATSCH"
              
              if (distance_signal_1 < 20) {
                
                  HTTPClient http;
              
                   Serial.println("requette executé PLACE_1 OCCUPÉ......");
                   
                             // DOMAINE""""""""""""""""""""""""""""""""""""""""""""
                      http.begin("https://secure-beach-35873.herokuapp.com/places/267YyS0ky5sOAyH3ktt4");
                      
                           // SPECIFICATION DU TYPE DE CONTENU EN-TETE (JSON)
              
                      http.addHeader("Content-Type", "application/json");
        
                       libre = "OCCUPÉ";
                
                        StaticJsonDocument<20> tempDocument;
                      tempDocument["libre"] = libre;
                      char buffer[20];
                      serializeJson(tempDocument, buffer);
                      http.PATCH(buffer);
                      http.end();
                  
                      
                  Serial.print("code de reponse HTTP : ");
                  Serial.println(httpResponseCode);
            
                      //delay(500); // attendre 5 seconde
              }
              else {
                
                  HTTPClient http;
              
                   Serial.println("requette executé OLACE_1 LIBRE......");
                   
                             // DOMAINE""""""""""""""""""""""""""""""""""""""""""""
                      http.begin("https://secure-beach-35873.herokuapp.com/places/267YyS0ky5sOAyH3ktt4");
                              // SPECIFICATION DU TYPE DE CONTENU EN-TETE (JSON)
                      http.addHeader("Content-Type", "application/json");
        
                       libre = "LIBRE";
                       
                        StaticJsonDocument<20> tempDocument;
                      tempDocument["libre"] = libre;
                      char buffer[20];
                      serializeJson(tempDocument, buffer);
                      http.PATCH(buffer);
                      http.end();
                  
                      
                  Serial.print("code de reponse HTTP : ");
                  Serial.println(httpResponseCode);
            
                      //delay(500); // attendre 5 seconde
            
              }

               //ENVOI DE LA REQUETTE HTTP DE MISE A JOUR "PATSCH"
              
              if (distance_signal_2 < 20) {
                
                  HTTPClient http;
              
                   Serial.println("requette executé PLACE_2.... OCCUPÉ......2");
                   
                             // DOMAINE""""""""""""""""""""""""""""""""""""""""""""
                      http.begin("https://secure-beach-35873.herokuapp.com/place/7jVknK0t5Ivc0VkvtZT9");
                      
                           // SPECIFICATION DU TYPE DE CONTENU EN-TETE (JSON)
              
                      http.addHeader("Content-Type", "application/json");
        
                       libre = "OCCUPÉ";
                
                        StaticJsonDocument<20> tempDocument;
                      tempDocument["libre"] = libre;
                      char buffer[20];
                      serializeJson(tempDocument, buffer);
                      http.PATCH(buffer);
                      http.end();
                  
                      //delay(500); // attendre 5 seconde
              }
              else {
                
                  HTTPClient http;
              
                   Serial.println("requette executé LIBRE......1");
                   
                             // DOMAINE""""""""""""""""""""""""""""""""""""""""""""
                      http.begin("https://secure-beach-35873.herokuapp.com/place/7jVknK0t5Ivc0VkvtZT9");
                              // SPECIFICATION DU TYPE DE CONTENU EN-TETE (JSON)
                      http.addHeader("Content-Type", "application/json");
        
                       libre = "LIBRE";
                       
                        StaticJsonDocument<20> tempDocument;
                      tempDocument["libre"] = libre;
                      char buffer[20];
                      serializeJson(tempDocument, buffer);
                      http.PATCH(buffer);
                      http.end();
                  
                      //delay(500); // attendre 5 seconde
            
              }

               //ENVOI DE LA REQUETTE HTTP DE MISE A JOUR "PATSCH"
              
              if (distance_signal_3 < 20) {
                
                  HTTPClient http;
              
                   Serial.println("requette executé OCCUPÉ......1");
                   
                             // DOMAINE""""""""""""""""""""""""""""""""""""""""""""
                      http.begin("https://secure-beach-35873.herokuapp.com/place/9rFmlH0KV2NJGBD43Dbh");
                      
                           // SPECIFICATION DU TYPE DE CONTENU EN-TETE (JSON)
              
                      http.addHeader("Content-Type", "application/json");
        
                       libre = "OCCUPÉ";
                
                        StaticJsonDocument<20> tempDocument;
                      tempDocument["libre"] = libre;
                      char buffer[20];
                      serializeJson(tempDocument, buffer);
                      http.PATCH(buffer);
                      http.end();
                  
                      //delay(500); // attendre 5 seconde
              }
              else {
                
                  HTTPClient http;
              
                   Serial.println("requette executé LIBRE......1");
                   
                             // DOMAINE""""""""""""""""""""""""""""""""""""""""""""
                      http.begin("https://secure-beach-35873.herokuapp.com/place/9rFmlH0KV2NJGBD43Dbh");
                              // SPECIFICATION DU TYPE DE CONTENU EN-TETE (JSON)
                      http.addHeader("Content-Type", "application/json");
        
                       libre = "LIBRE";
                       
                        StaticJsonDocument<20> tempDocument;
                      tempDocument["libre"] = libre;
                      char buffer[20];
                      serializeJson(tempDocument, buffer);
                      http.PATCH(buffer);
                      http.end();
                  
                      //delay(500); // attendre 5 seconde
            
              }

               //ENVOI DE LA REQUETTE HTTP DE MISE A JOUR "PATSCH"
              
              if (distance_signal_4 < 20) {
                
                  HTTPClient http;
              
                   Serial.println("requette executé OCCUPÉ......1");
                   
                             // DOMAINE""""""""""""""""""""""""""""""""""""""""""""
                      http.begin("https://secure-beach-35873.herokuapp.com/place/cWLP3t1tKYW5PdvPOMsX");
                      
                           // SPECIFICATION DU TYPE DE CONTENU EN-TETE (JSON)
              
                      http.addHeader("Content-Type", "application/json");
        
                       libre = "OCCUPÉ";
                
                        StaticJsonDocument<20> tempDocument;
                      tempDocument["libre"] = libre;
                      char buffer[20];
                      serializeJson(tempDocument, buffer);
                      http.PATCH(buffer);
                      http.end();
                  
                      //delay(500); // attendre 5 seconde
              }
              else {
                
                  HTTPClient http;
              
                   Serial.println("requette executé LIBRE......1");
                   
                             // DOMAINE""""""""""""""""""""""""""""""""""""""""""""
                      http.begin("https://secure-beach-35873.herokuapp.com/place/cWLP3t1tKYW5PdvPOMsX");
                              // SPECIFICATION DU TYPE DE CONTENU EN-TETE (JSON)
                      http.addHeader("Content-Type", "application/json");
        
                       libre = "LIBRE";
                       
                        StaticJsonDocument<20> tempDocument;
                      tempDocument["libre"] = libre;
                      char buffer[20];
                      serializeJson(tempDocument, buffer);
                      http.PATCH(buffer);
                      http.end();
                  
                      //delay(500); // attendre 5 seconde
            
              }

               //ENVOI DE LA REQUETTE HTTP DE MISE A JOUR "PATSCH"
              
              if (distance_signal_5 < 20) {
                
                  HTTPClient http;
              
                   Serial.println("requette executé OCCUPÉ......1");
                   
                             // DOMAINE""""""""""""""""""""""""""""""""""""""""""""
                      http.begin("https://secure-beach-35873.herokuapp.com/place/zK9NQnYHgfrU3ifwJn3r");
                      
                           // SPECIFICATION DU TYPE DE CONTENU EN-TETE (JSON)
              
                      http.addHeader("Content-Type", "application/json");
        
                       libre = "OCCUPÉ";
                
                        StaticJsonDocument<20> tempDocument;
                      tempDocument["libre"] = libre;
                      char buffer[20];
                      serializeJson(tempDocument, buffer);
                      http.PATCH(buffer);
                      http.end();
                  
                      //delay(500); // attendre 5 seconde
              }
              else {
                
                  HTTPClient http;
              
                   Serial.println("requette executé LIBRE......1");
                   
                             // DOMAINE""""""""""""""""""""""""""""""""""""""""""""
                      http.begin("https://secure-beach-35873.herokuapp.com/place/zK9NQnYHgfrU3ifwJn3r");
                              // SPECIFICATION DU TYPE DE CONTENU EN-TETE (JSON)
                      http.addHeader("Content-Type", "application/json");
        
                       libre = "LIBRE";
                       
                        StaticJsonDocument<20> tempDocument;
                      tempDocument["libre"] = libre;
                      char buffer[20];
                      serializeJson(tempDocument, buffer);
                      http.PATCH(buffer);
                      http.end();
                  
                      //delay(500); // attendre 5 seconde
            
              }
                  
         
            }
            else {
              Serial.println("Wi-Fi déconnecté");
            }
           // lastTime = millis();
          //}
        
          Serial.println("FIN LOOP");
}


void mesureDistance_1() {
  digitalWrite( PIN_TRIGGER_1 , LOW);
  delayMicroseconds(2); // on patiente 2 microsecode pourque le capteur soit bien à 0
  digitalWrite( PIN_TRIGGER_1 , HIGH);  // on envoi un signal de 10 microseconde (debut)  ****EMISSION ULTRASONNIC****
  delayMicroseconds(10);              // on envoi un signal de 10 microseconde
  digitalWrite( PIN_TRIGGER_1 , LOW);   // on envoi un signal de 10 microseconde (fin)
  dure_signal = pulseIn(PIN_ECHO_1, HIGH);  // ici on capte la pulsation ****RECEPTION ULTRASONNIC****
  //Serial.print(dure_signal);
  distance_signal_1 = dure_signal / 58 ;
  //Serial.print(distance_signal);
}

void mesureDistance_2() {
  digitalWrite( PIN_TRIGGER_2 , LOW);
  delayMicroseconds(2); // on patiente 2 microsecode pourque le capteur soit bien à 0
  digitalWrite( PIN_TRIGGER_2 , HIGH);  // on envoi un signal de 10 microseconde (debut)  ****EMISSION ULTRASONNIC****
  delayMicroseconds(10);              // on envoi un signal de 10 microseconde
  digitalWrite( PIN_TRIGGER_2 , LOW);   // on envoi un signal de 10 microseconde (fin)
  dure_signal = pulseIn(PIN_ECHO_2, HIGH);  // ici on capte la pulsation ****RECEPTION ULTRASONNIC****
  //Serial.print(dure_signal);
  distance_signal_2 = dure_signal / 58 ;
  //Serial.print(distance_signal);
}

void mesureDistance_3() {
  digitalWrite( PIN_TRIGGER_3 , LOW);
  delayMicroseconds(2); // on patiente 2 microsecode pourque le capteur soit bien à 0
  digitalWrite( PIN_TRIGGER_3 , HIGH);  // on envoi un signal de 10 microseconde (debut)  ****EMISSION ULTRASONNIC****
  delayMicroseconds(10);              // on envoi un signal de 10 microseconde
  digitalWrite( PIN_TRIGGER_3 , LOW);   // on envoi un signal de 10 microseconde (fin)
  dure_signal = pulseIn(PIN_ECHO_3, HIGH);  // ici on capte la pulsation ****RECEPTION ULTRASONNIC****
  //Serial.print(dure_signal);
  distance_signal_3 = dure_signal / 58 ;
  //Serial.print(distance_signal);
}

void mesureDistance_4() {
  digitalWrite( PIN_TRIGGER_4 , LOW);
  delayMicroseconds(2); // on patiente 2 microsecode pourque le capteur soit bien à 0
  digitalWrite( PIN_TRIGGER_4 , HIGH);  // on envoi un signal de 10 microseconde (debut)  ****EMISSION ULTRASONNIC****
  delayMicroseconds(10);              // on envoi un signal de 10 microseconde
  digitalWrite( PIN_TRIGGER_4 , LOW);   // on envoi un signal de 10 microseconde (fin)
  dure_signal = pulseIn(PIN_ECHO_4, HIGH);  // ici on capte la pulsation ****RECEPTION ULTRASONNIC****
  //Serial.print(dure_signal);
  distance_signal_4 = dure_signal / 58 ;
  //Serial.print(distance_signal);
}

void mesureDistance_5() {
  digitalWrite( PIN_TRIGGER_5 , LOW);
  delayMicroseconds(2); // on patiente 2 microsecode pourque le capteur soit bien à 0
  digitalWrite( PIN_TRIGGER_5 , HIGH);  // on envoi un signal de 10 microseconde (debut)  ****EMISSION ULTRASONNIC****
  delayMicroseconds(10);              // on envoi un signal de 10 microseconde
  digitalWrite( PIN_TRIGGER_5 , LOW);   // on envoi un signal de 10 microseconde (fin)
  dure_signal = pulseIn(PIN_ECHO_5, HIGH);  // ici on capte la pulsation ****RECEPTION ULTRASONNIC****
  //Serial.print(dure_signal);
  distance_signal_5 = dure_signal / 58 ;
  //Serial.print(distance_signal);
}
