#include<WiFi.h>
#include<HTTPClient.h>
#include<ArduinoJson.h>
#include <Stepper.h>


const int stepsPerRevolution = 2048;
const char* ssid="iPhone di Era";
const char* password="erestina";
const char* city;
const char* weather_txt;

#define APIKEY "0526d8ca2a784a2ca17131537222912"
#define LOCATION "Italy/Trent"  //can be changed
#define HOST "api.weatherapi.com"
#define PATH "/v1/current.json"

#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17


static char resp_buffer[4096];
WiFiClient client;

Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
   


  while( WiFi.status()!= WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if(client.connect(HOST, 80)){
      Serial.println("Connected to server");  
    }else{
      Serial.println("Connection failed");    
    }

  myStepper.setSpeed(5);
  makeReq();
}

void makeReq(){
  if(client.connected()){
      client.println("GET " PATH "?key=" APIKEY "&q=" LOCATION " HTTP/1.1");
      client.println("Host: " HOST);      
      client.println("Connection: close");
      client.println();

    while(!client.available()){
      Serial.println("Waiting for client");
    }
    while(client.available()){
      char status[32] = {0};
      client.readBytesUntil('\r', status, sizeof(status));
      if (strcmp(status, "HTTP/1.1 200 OK") != 0){
        Serial.print(F("Unexpected response: "));
        Serial.println(status);
        return;
      }

  // Skip HTTP headers
      char endOfHeaders[] = "\r\n\r\n";
      if (!client.find(endOfHeaders)){
        Serial.println(F("Invalid response"));
        return;
      }

      DynamicJsonDocument doc(4096);
      DeserializationError error = deserializeJson(doc, client);
      
      if(!error){
        city=doc["location"]["name"];
        weather_txt=doc["current"]["condition"]["text"];
        Serial.println(city);
        Serial.println(weather_txt);
      }else{
        Serial.print("Error in decoding:  ");
        Serial.println(error.c_str());  
      }
    }
    
  }
}

void loop() {
  if((WiFi.status()== WL_CONNECTED)){
    
  }else{
    Serial.println("Connection lost");
  }
  
  if (strcmp(weather_txt, "Sunny") == 0){
      Serial.println("clockwise");
      myStepper.step(stepsPerRevolution);

  }
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);

  
  delay(30000);
}
