/********************************
 * Libraries included
 *******************************/
#include <Ethernet.h>
#include <SPI.h>
#include <UbidotsEthernet.h>

/********************************
 * Constants and objects
 *******************************/
/* Assigns the Ubidots parameters */
char const * TOKEN = "A1E-3B4BhI4ayzq5ZASIRgXjIqPuQnmMG5"; // Assign your Ubidots TOKEN
char const * VARIABLE_LABEL_1 = "temperature"; // Assign the unique variable label to send the data

/* Enter a MAC address for your controller below */
/* Newer Ethernet shields have a MAC address printed on a sticker on the shield */
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x8A, 0x52 };

/* Set the static IP address to use if the DHCP fails to assign */
//IPAddress ip(192, 168, 69, 150);

/* initialize the instance */
Ubidots client("A1E-3B4BhI4ayzq5ZASIRgXjIqPuQnmMG5");

float tempK=0, tempC=0, tempF=0;

/********************************
 * Main Functions
 *******************************/

void setup()
{
  Serial.begin(9600);    //Setup serial to 9600 bps
  //Start Connection Check
  
  //client.setDebug(true);// uncomment this line to visualize the debug message
  /* start the Ethernet connection */
  Serial.print(F("Starting ethernet..."));
  if (!Ethernet.begin(mac)) 
  {
    Serial.println(F("failed"));
  } else 
  {
    Serial.println(Ethernet.localIP());
  }
  /* Give the Ethernet shield a second to initialize */
  delay(2000);
  Serial.println(F("Ready"));
  //finish connection check
}
 
void loop()
{
        //start temp
        tempK = analogRead(A3) * 0.004882812 * 100;    //Read temperature in Kelvins first
        tempC = tempK - 273.15;    //Convert from Kelvin to Celsius
        tempF = ((tempK) * 9 / 5) - 459.67;    //Convert from Kelvin to Fahrenheit
         
        //Print all the values to Serial
        //Serial.print("Kelvin: "); Serial.println(tempK);
        Serial.print("Celsius: "); Serial.println(tempC);
        //Serial.print("Fahrenheit: "); Serial.println(tempF);
        //finish temp

       /* Sensors readings */
        float value_1 = analogRead(A3)* 0.004882812 * 100 - 273.15;
        /* Sending values to Ubidots */
        client.add(VARIABLE_LABEL_1, value_1);
        client.sendAll();
       delay(5000); 
}
