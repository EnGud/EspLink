#include <stdio.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
// + #include <time.h>

FirebaseData firebaseData;
FirebaseJson json;

#define WIFI_SSID "AndroidAPA9EA"
#define WIFI_PASSWORD "djea2642"
#define FIREBASE_HOST "frbasewebapprlcrowdsolutions20.firebaseio.com"
#define FIREBASE_AUTH "ia4dsTciYNUb6ghqrVkvMhJBf9yJK70B7mwMVK9R"
#define RXD2 16
#define TXD2 17

//Declarations
int Info = 20;
String Dataplassering;
char Inndata[32];
char Destination[16];






void setup() {


  Serial.begin(115200);
  Serial.println("");
  Serial.print("Kobler til nettverk");
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //input SSID og passord
  Firebase.reconnectWiFi(true);

while(WiFi.status() != WL_CONNECTED){
  Serial.print(".");
  delay(300);
}
// + Timeout ved for lang tid, "Prøv igjen"
Serial.println("");
Serial.print("Tilkobling vellykket, ");
Serial.print("Koblet til IP: ");
Serial.println(WiFi.localIP());
Serial.println("");
delay(100);
Serial.print("Kobler til Firebase.");

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.reconnectWiFi(true);
  // Firebase Innlogging, etterfulgt av antal forsøk ved error, og maks error i queue.

Firebase.setMaxRetry(firebaseData, 3);
Firebase.setMaxErrorQueue(firebaseData, 10);

 
// Firebase.enableClassicRequest(firebaseData, true);
// Benyttes dersom vi trenger get og delete-funksjoner senere (Mest sannsynlig ikke).
// + setDeviceTime() henter tid fra serveren. bruke RTC, eller hente tid hver gang man sender?

  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));

//if (Firebase.pushInt(firebaseData, path, Info))
//{
//  Serial.println("Data sent");
//  Dataplassering = firebaseData.dataPath();
//  Serial.println(Dataplassering);
//  delay(10*100);}
}



void loop(){
int Info = random(10, 35);
RandTestFull();
String path = Destination;
int Inndata = rand()%30 +1;

  while (Serial2.available()) {
    Serial.print(char(Serial2.read()));
Inndata = Serial2.read();
  }
  
if (Firebase.setInt(firebaseData, path, Inndata))
{
  Serial.println("Data sent");
  delay(5000);
}
else
{
  Serial.println("Feilet!");
  Serial.println("Feilkode: " + firebaseData.errorReason());
  delay(5000);
}

}
 
void RandTestFull(){
int Num = rand()%3;
  delay(1000);
  switch(Num){
    case  0:
    strcpy(Destination, "1pck5CC382xF");
    break;
    
    case 1:
    strcpy(Destination, "2pKK4mEn8Dx0");
    break;
    
    case 2:
    strcpy(Destination, "TestSetting");
    break;
}
}
//Manglende kode/Idéer
//Sleep-status
//Wait For Recieved bit
//Noden må sende dataen, samt en unik ID til CC, ID-en benyttes for å lagre dataen i rett database i Firebase.
