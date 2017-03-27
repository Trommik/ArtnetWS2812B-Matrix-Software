/*
 Name:		ArtnetWS2812B.ino
 Created:	24.03.2017 16:56:20
 Author:	Thomas
*/

#include "Adafruit_NeoPixel.h" // Neopixel Libary for WS2812B 

#include "ESP8266WiFi.h" // ESP8266 Core Functions
#include "ArtnetWifi.h" // Artnet Libary

//Led settings
#define NUM_LEDS 290
#define DATA_PIN 14

#define START_UNIVERSE 0 // universe which starts with pixel 0 
#define CHANNELS  NUM_LEDS * 3 // Total number of channels you want to receive (1 led = 3 channels)
#define MAX_UNIVERSES ((CHANNELS / 512) + ((CHANNELS % 512) ? 1 : 0))

bool universesReceived[MAX_UNIVERSES];
bool sendFrame = 1;
int previousDataLength = 0;

//Wifi settings
const char* ssid = "Speedport Schwark 2,4 GHz";
const char* password = "4858035152347806";

ArtnetWifi artnet; // Initialize the artnet libary
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800); // Initialize the led strip

// connect to wifi and returns true if successful or false if not
boolean ConnectWifi(void) {

	boolean state = true;
	int i = 0;

	WiFi.mode(WIFI_STA);

	WiFi.begin(ssid, password);
	Serial.println("");
	Serial.println("Connecting to WiFi");

	// Wait for connection
	Serial.print("Connecting");
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
		if (i > 20) {
			state = false;
			break;
		}
		i++;
	}
	if (state) {
		Serial.println("");
		Serial.print("Connected to ");
		Serial.println(ssid);
		Serial.print("IP address: ");
		Serial.println(WiFi.localIP());
		strip.setPixelColor(0, strip.Color(0, 255, 0)); // set buffer pixel to green for OK WiFi connection 
		strip.show();
	}
	else {
		Serial.println("");
		Serial.println("Connection failed.");
		strip.setPixelColor(0, strip.Color(255, 0, 0)); // set buffer pixel to red for FAILED WiFi connection 
		strip.show();
	}

	return state;
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
	sendFrame = 1;

	// Store which universe has got in
	if (universe - START_UNIVERSE < MAX_UNIVERSES)
		universesReceived[universe] = 1;

	for (int i = START_UNIVERSE; i < MAX_UNIVERSES; i++)
	{
		if (universesReceived[i] == 0)
		{
			sendFrame = 0;
			break;
		}
	}

	// read universe and put into the right part of the display buffer
	for (int i = 0; i < length / 3; i++)
	{
		int led = i + (universe - START_UNIVERSE) * (previousDataLength / 3);
		if (led < NUM_LEDS)
			strip.setPixelColor(led+1, data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
	}
	previousDataLength = length;

	if (sendFrame)
	{
		strip.show(); // show strip
		memset(universesReceived, 0, MAX_UNIVERSES); // Reset universeReceived to 0
	}
}

void setup()
{
	Serial.begin(115200); // Init Serial at 115200 Baud

	strip.begin(); // Init strip
	strip.setPixelColor(0, strip.Color(0, 0, 255)); // set buffer pixel to blue for INIT WiFi connection 
	strip.show(); // Show strip

	ConnectWifi(); // Connect to WiFi

	artnet.setArtDmxCallback(onDmxFrame); // this will be called for each artnet packet received
	artnet.begin(); // Init artnet libary
}

void loop()
{
	artnet.read(); // Read artnet
}
