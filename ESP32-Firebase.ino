#include <Arduino.h>
#include <stdio.h>
#include <string>
#include <FirebaseESP32.h>
#include <wifi.h>


FirebaseData firebaseData;
FirebaseJson json;

#define WIFI_SSID "AndroidAPA9EA"
#define WIFI_PASSWORD "djea2642"
#define FIREBASE_HOST "frbasewebapprlcrowdsolutions20.firebaseio.com"
#define FIREBASE_AUTH "ia4dsTciYNUb6ghqrVkvMhJBf9yJK70B7mwMVK9R"

//Declarations//
char Indata[27];
char NodeID[] = "Teststring";

char *p = Indata;

char NodeTemp[32];
char NodeDoor[32];
char NodeLight[32];
char NodeBattery[32];
char NodeNoise[32];

// int Temperature;
// int DoorState;
// int Light;
// int Battery;
// int Noise;
int DataInfo[] = {00, 0, 0, 00, 00};

int i, j;

bool DataAvailable = false;
const int Index = 25;
char Temp[Index];

//End declarations//

void setup() {

  Serial.begin(9600);
  Serial.println("");
  Serial.print("Connecting to Wi-Fi");

  //Connect wifi while not connected.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //input SSID og passord
  Firebase.reconnectWiFi(true);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  // + Timeout ved for lang tid, "Prøv igjen"
  //Output success, testing purposes.

  Serial.println("");
  Serial.print("Connection established, ");
  Serial.print("Connected to IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
  delay(100);
  Serial.println("Connecting to Firebase.");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  // Firebase Innlogging, etterfulgt av antal forsøk ved error, og maks error i queue.

  Firebase.setMaxRetry(firebaseData, 3);
  Firebase.setMaxErrorQueue(firebaseData, 10);


  // Firebase.enableClassicRequest(firebaseData, true);
  // Benyttes dersom vi trenger get og delete-funksjoner senere (Mest sannsynlig ikke).
  // + setDeviceTime() henter tid fra serveren. bruke RTC, eller hente tid hver gang man sender?

  Serial2.begin(9600);
  Serial.println("Serial2 Initiated");
}

void CheckData(){
  if (Serial2.available()){
    DataAvailable = true;
  }
  else
  {
    DataAvailable = false;
  }
  
}

void GetData(){

  
  if (Serial2.available() > 0){

    Serial2.readBytesUntil('@', Temp, Index);
    strcpy(Indata, Temp);
  }
  Serial.println(Indata);

}



//Funksjon for å splitte innkommende data i rette grupper, for å så skrive rett Firebase-addresse for infoen.
void SplitData(){
char * token = strtok(Indata, ":");
strcpy(NodeID, token);

for (i=0; i<=4; i++){
token = strtok(NULL, ":");
DataInfo[i] = atoi(token);
}

  strcpy(NodeTemp, strcat(NodeID, "/Temp")); 
  strcpy(NodeDoor, strcat(NodeID, "/Door"));
  strcpy(NodeLight, strcat(NodeID, "/Light"));
  strcpy(NodeBattery, strcat(NodeID, "/Battery"));
  strcpy(NodeNoise, strcat(NodeID, "/Noise"));
}

void loop(){
  CheckData();
if (DataAvailable == true){
  GetData();

}
SplitData();

for (i=0; i<=4; i++){
    if (Firebase.setInt(firebaseData, NodeTemp, DataInfo[i])) {
      Serial.println("Temp sent");
}
else {
           Serial.println("Feilet!");
        Serial.println("Feilkode: " + firebaseData.errorReason());
        delay(50);
    
}
DataAvailable = false;
}
}
