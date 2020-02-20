#include <WiFi.h>
#include <FirebaseESP32.h>
#include <time.h>

FirebaseData firebaseData;
FirebaseJson json;

#define WIFI_SSID "AndroidAPA9EA"
#define WIFI_PASSWORD "djea2642"
#define FIREBASE_HOST "frbasewebapprlcrowdsolutions20.firebaseio.com"
#define FIREBASE_AUTH "ia4dsTciYNUb6ghqrVkvMhJBf9yJK70B7mwMVK9R"


String path = "/Test";
int Info = 20;
String Dataplassering;


void setup() {


  Serial.begin(115200);
  
  Serial.print("Kobler til nettverk");
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //input SSID og passord
  Firebase.reconnectWiFi(true);

while(WiFi.status() != WL_CONNECTED){
  Serial.print(".");
  delay(300);
}


Serial.println("Tilkobling vellykket, ");
Serial.print("Koblet til IP: ");
Serial.println(WiFi.localIP());
Serial.println();

Serial.println();
Serial.print("Kobler til Firebase.");

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.reconnectWiFi(true);
  // Firebase Innlogging, etterfulgt av antal forsøk ved error, og maks error i queue.

Firebase.setMaxRetry(firebaseData, 3);
Firebase.setMaxErrorQueue(firebaseData, 10);

 
// Firebase.enableClassicRequest(firebaseData, true);
// Benyttes dersom vi trenger get og delete-funksjoner senere (Mest sannsynlig ikke).
//setDeviceTime() henter tid fra serveren. bruke RTC, eller hente tid hver gang man sender?


if (Firebase.pushInt(firebaseData, path + "/Arnes", Info))
{
  Serial.println("Data sent");
  Dataplassering = firebaseData.dataPath();
  Serial.println(Dataplassering);
  delay(10*100);}
}








void loop(){
int Info = random(10, 35);
String path = "/Test";

if (Firebase.setInt(firebaseData, path + "/Arnes", Info))
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
  




//Manglende kode/Idéer
//Sleep-status
//Wait For Recieved bit
//Noden må sende dataen, samt en unik ID til CC, ID-en benyttes for å lagre dataen i rett database i Firebase.
