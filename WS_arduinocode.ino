//HTTPCLIENT-
#include <stdlib.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
//For PressureSensor-
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

WiFiServer server(80); // Setting the Server Port

HTTPClient http;

int i=0;

//For Temp-Humidity Sensor-

DHT dht;// DHT11 Object
 float ht=0;
  float tt=0;
  float dp;

//For Rain Sensor-
int nRainIn = A0;
int nRainDigitalIn = 2;
int nRainVal;
boolean bIsRaining = false;
int isR=0;
boolean raincheck=true;
int t_rv=0;
int t_p=0;
float alt=0;
String strRaining;




Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

/* Function to send data to database online. */
String SendData(float temperature,float humidity,float dewpoint, int isRaining, int rainval, float pressure, float altitude)
{
  String  httpurl;
  server.begin(); // Tells the server to begin listening for incoming connections.
  
  httpurl="http://35.164.75.44/datareceive.php?";   
  httpurl+="temperature=";
  httpurl+=String(temperature);
  httpurl+="&";
  httpurl+="humidity=";
  httpurl+=String(humidity);
  httpurl+="&";
  httpurl+="pressure=";
  httpurl+=String(pressure);
  httpurl+="&";
  httpurl+="dewpoint=";
  httpurl+=String(dewpoint);
  httpurl+="&";
  httpurl+="altitude=";
  httpurl+=String(altitude);
  httpurl+="&";
  httpurl+="israining=";
  httpurl+=String(isRaining);
  httpurl+="&";
  httpurl+="rainval=";
  httpurl+=String(rainval);
  
  http.begin(httpurl);
  http.GET();
  
  String result=http.getString();
  http.end();

  if(result=="1")
 {
  Serial.println("Data Sent to Database");
 }
 else
 {
  Serial.println("Data Not Sent to Database");
 }
  
  //return result;
}


void setup() {
  Serial.begin(9600);
  Serial.println();

  //Initialise Rain sensor
  pinMode(2,INPUT);
 
  //check bmp180
   if(!bmp.begin()) {
   Serial.print("Failed to read from BMP sensor!!");
   while(1);
  }

  //setup dht
 Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  dht.setup(D3); // data pin 3 for dht11

   WiFi.disconnect(); // To disconnect any previously connected WIFI/Access Point.
  delay(1000); // Delay before connecting again to WIFI/Access Point.

  /*
   * SSID: Your WIFI SSID (e.g. "mywifi")
   * PASSWORD: Your WIFI Password (e.g. "mywifipswd")
   */
  WiFi.begin("Razor","abc456"); // To start the WIFI connection.
 

  Serial.print("\n\nConnecting");
  while (!(WiFi.status() == WL_CONNECTED))
  {
    /* To check whether wifi is connected or not. 
     * If NOT, The while loop will continue trying to connect to the WIFI/Access Point with a delay.
     * If YES, The while loop will end.
     */
    delay(300);
    Serial.print(".");
    i++;
    if(i>50)
    {
      i=0;
      break;
    }
  }
  
  if(WiFi.status()==WL_CONNECTED)
  {
    Serial.println("\nConnected");
  }
  else
  {
    Serial.print("Not Connected: ");
    Serial.println("Please check WiFi is ON & Press Reset on NodeMCU");
  }
}



void loop() {
  Serial.println();

  //DHT11 Sensor for Temperature and Humidity-
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

   if(humidity!=ht || temperature!=tt )
   {
    Serial.print("Status=");
  Serial.println(dht.getStatusString());
  Serial.print("Humidity=\t");
  Serial.print(humidity, 1);
  Serial.println("%");
  Serial.print("Temperature=\t");
  Serial.print(temperature, 1);
  Serial.print("*C \t ");
  Serial.print(dht.toFahrenheit(temperature), 1);
   Serial.println("*F");
   
float gamma = log(humidity/100) + ((17.62*temperature) / (243.5+temperature));
dp = 243.5*gamma / (17.62-gamma);

Serial.print("Dew point:        ");
Serial.print(dp);
Serial.print(" *C ");
Serial.println();
ht=humidity ;
tt=temperature;
   }

//Raindrop and moisture sensor-
  nRainVal = analogRead(nRainIn);
  bIsRaining = !(digitalRead(nRainDigitalIn));
  
  if(bIsRaining){
    strRaining = "YES";
    isR=1;
  }
  else{
    strRaining = "NO";
    isR=0;
  }

if(raincheck != bIsRaining || t_rv != nRainVal)
{ 
  Serial.print("Raining?: ");
  Serial.print(strRaining);  
  Serial.print("\t Moisture Level: ");
  Serial.println(nRainVal);
  raincheck = bIsRaining;
  t_rv=nRainVal;
}



  //BMP180 Sensor-
   sensors_event_t event;
   bmp.getEvent(&event);

if(t_p!=event.pressure)
{
  t_p=event.pressure;
  Serial.print("Pressure:         ");
  Serial.print(event.pressure);
  Serial.println(" hPa");

  float t;
  bmp.getTemperature(&t);

  if(t!=tt)
  {
    Serial.print("Temperature:      ");
    Serial.print(t);
    Serial.println(" degrees Celcius ");
  }

  float seaLevelPressure = 1010;
  Serial.print("Altitude:         "); 
  Serial.print(bmp.pressureToAltitude(seaLevelPressure,event.pressure)); 
  Serial.println(" m");
  alt=bmp.pressureToAltitude(seaLevelPressure,event.pressure);
}

  SendData(tt,ht,dp,isR,t_rv,t_p,alt);
 
  delay(15000);
}
