/*
 * ce fichier permet de creer sur un esp32 un server web qui permetra de 
 * commender (allumer ou eteindre) la led au pin 2 de l'esp32
 * via une page web. 
 * 
 * comment obtenir cette page web?
 *      1) connecter l'esp32 à votre machine via un cable USB
 *      2) activer un point d'acces wifi (sur votr telephone par example)
 *          et rassurer vous d'avoir une connexion internet a ce poit d'acces
 *      3) televercer ce code
 *      4) ouvrer le moniteur serie ( ouitils > moniteur serie) et veriffier
 *          que vous ete bien au moniteur serie 9600
 *      5) recopier l'addresse IP de l'esp32 qui s'affiche dans  n'importe 
 *         quel navigateur connecté au point d'cces spécifier en 2)
 *         
 *         BONNE EXPERIMENTATION !!!!
 */

#include <WiFi.h>
#include <WebServer.h> //appel de la librairie server

//const char* ssid = "ETECH CENTER";
//const char* password = "abc1234#";
const char* ssid = "TECNO SPARK 6";
const char* password = "a2234567";
WebServer server(80); // creation de l'objet serveur (ecoute sur le port par défaut)

#define PIN_TRIGGER 2 
#define PIN_ECHO 4 
long dure_signal , distance_signal;
//bool etatPlace = 0;
//char texteEtatPlace[2][10] = {"OCCUPÉE!","LIBRE!"};

/*
const int led = 2;
bool etatLed = 0;
char texteEtatLed[2][10] = {"ÉTEINTE!", "ALLUMÉ!"};
*/



            
/*
              void handleOn()
              {
                etatLed = 1;
                digitalWrite(led, HIGH);
                server.sendHeader("Location", "/");
                server.send(303);
              }

              void handleOff()
              {
                etatLed = 0;
                digitalWrite(led, LOW);
                server.sendHeader("Location", "/");
                server.send(303); 
              }
*/

/*
              void handleOn()
              {
                etatPlace = 1;
                
                server.sendHeader("Location", "/");
                server.send(303);
              }

              void handleOff()
              {
                etatPlace = 0;
                
                server.sendHeader("Location", "/");
                server.send(303); 
              }
*/
   
   // la fonction suivante est appellée si on veut faire appel a une page qui n'existe pas
              void handleNotFound()
              {
                    server.send(404, "text/plain", "404: Not found !");
              }


void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO,INPUT );
  delay(1000);
  Serial.println("\n");

  WiFi.begin(ssid, password);
  Serial.print("TENTATIVE DE CONNEXION...");

  while(WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(100);
    }

    Serial.println("\n");
    Serial.println("    CONNEXION ETABLIE !");
    Serial.print("Adresse IP : ");
    Serial.println( WiFi.localIP());

    //configuration de server
    server.on("/", handleRoot);
    //server.on("/on", handleOn); //pour activer le server
    //server.on("/off", handleOff); // pour desactiver le server
    
    // server.on("/", handleOn); //pour activer le server
    // server.on("/", handleOff); // pour desactiver le server
    server.onNotFound(handleNotFound);
    server.begin();                       // demarage du seerver
    
    Serial.println("    SERVER WEB ACTIF !");

}


void handleRoot()
              {
                
                
                String page = "<!DOCTYPE html>";
                page += "<html lang='fr'>";
                page += "    <head>";
                page += "       <title>Serveur ESP32</title>";
                page += "       <link rel='stylesheet' href='https://www.w3schools.com/w3css/4/w3.css'>";
                page += "       <meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1' charset='UTF-8'/>";
                page += "    </head>";
                
                page += "    <body>";
                page += "        <div class='w3-card w3-black w3-padding-small w3-jumbo w3-center'>";
               // page += "            <p>ÉTAT LED :"; page += texteEtatLed[etatLed]; page += "</p>";

               //page += "            <p>ÉTAT PLACE :";  page += texteEtatPlace[etatPlace]; page += "</p>";

mesureDistance(); // appel de la fontion qui mesure la distance
  
               if( distance_signal < 20){
                 page += "              <p>ÉTAT PLACE :</p>"; page += "<p> <input type='text' value=' OCCUPÉE ' readonly></p>";
                
                }else if(distance_signal >= 20){
                  page += "              <p>ÉTAT PLACE :</p>"; page += "<p> <input type='text' value=' LIBRE ' readonly></p>";
                 
                 }  


                page += "        </div>";

               /* 
                page += "        <div class='w3-bar'>";
                page += "             <a href='/on' class='w3-bar-item w3-button w3-border w3-jumbo' style='width: 50%;'>ON</a>";
                page += "             <a href='/off' class='w3-bar-item w3-button w3-border w3-jumbo' style='width: 50%;'>OFF</a>";
                page += "        </div>";
               */

             /*
                page += "        <div class='w3-center w3-padding-16'>";
                page += "            <h2>Serveur du SMART PARKING</h2>";
                page += "            <h3><p>Ce serveur est hébergé sur un ESP32</p></h3>";
               // page += "            <i>Créé dans le cadre de l'UE-PROJET par <h1>SIELINOU NOUBISSIE ERIC ROMUALD</h1> <br/> <h1>FOKO BRICE</h1> <br/> <h1>VALERE</h1> <br/> <h1>SAID MOPAIN</h1> <br/>: lol!!!!  </i>";
                page += "        </div>";
              */  
                page += "    </body>";
                
                page += "</html>";

                server.setContentLength(page.length()); // cette ligne permet de specifier la longueur de la page(html) avant de l'envoyer au server (ceci facilite la tache au server et le rend donc plus rapide)
                server.send(200, "text/html", page); // envoi de la page
              }

          
 void loop() {
                 
  server.handleClient(); //cette ligne tres puissante gerre le client qui se connecte a l'esp32 via un server web
 handleRoot();

    delay(3000);
  
}
   



void mesureDistance(){
  digitalWrite( PIN_TRIGGER , LOW);
  delayMicroseconds(2); // on patiente 2 microsecode pourque le capteur soit bien à 0
  digitalWrite( PIN_TRIGGER , HIGH);  // on envoi un signal de 10 microseconde (debut)  ****EMISSION ULTRASONNIC****
  delayMicroseconds(10);              // on envoi un signal de 10 microseconde
  digitalWrite( PIN_TRIGGER , LOW);   // on envoi un signal de 10 microseconde (fin)
  dure_signal = pulseIn(PIN_ECHO, HIGH);  // ici on capte la pulsation ****RECEPTION ULTRASONNIC****
  //Serial.print(dure_signal);
  distance_signal = dure_signal / 58 ;
  
  Serial.println(distance_signal);
}
