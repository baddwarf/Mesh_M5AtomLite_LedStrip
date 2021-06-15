/*
*
* Hardware : M5 Atom Lite
* Fonction : led strip
*
*
*/

//#include "M5Atom.h"
#include "Button.h"
#include "painlessMesh.h"
#include "meshEventRules.h"
#include <FastLED.h>


// LEDS
#define STRIP_LED_COUNT 72
#define STRIP_PIN 26
#define STATUS_LED_COUNT 1
#define STATUS_LED_PIN 27
// MESH
#define MESH_ROOT false
#define MESH_PREFIX "homeMesh"
#define MESH_PASSWORD "MeshP4Ssw0rd"
#define MESH_PORT 5555
// BUTTON
Button atomBtn = Button(39, true, 10);
// LEDS
CRGB ledStrip[STRIP_LED_COUNT];
CRGB statusLed[STATUS_LED_COUNT];
CRGB rainbow[6] = {CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::Green, CRGB::Blue, CRGB::Purple};
uint8_t colorIndex;
uint8_t stripIndex;
bool ledStatus;
// MESH
Scheduler userScheduler;
painlessMesh mesh;
bool meshConnected;
uint32_t meshRootNode;
//meshRuleList rules;

void setup() 
{
  
  //M5.begin();
  Serial.begin(115200);
  // LED init
  Serial.println("[INIT] FastLED");
  FastLED.addLeds<NEOPIXEL, STATUS_LED_PIN>(statusLed, STATUS_LED_COUNT);
  FastLED.addLeds<SK6812, STRIP_PIN, GRB>(ledStrip, STRIP_LED_COUNT);
  FastLED.clear();
  FastLED.setBrightness(10);
  stripIndex = 1;
  statusLed[0] = CRGB::DarkGreen;
  FastLED.show();
  Serial.println("[INIT] Mesh");
  // MESH init
  meshConnected = false;
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  Serial.println("[INIT] Mesh node id " + String(mesh.getNodeId()));
  // setup callback functions
  mesh.onReceive(&meshReceiveCallback);
  mesh.onNewConnection(&meshNewConnectionCallback);
  mesh.onChangedConnections(&meshChangedConnectionCallback);
  mesh.onNodeTimeAdjusted(&meshNodeTimeAdjustedCallback);
  // LED test
  RGBLoop();
  ledStatus = true;
  setAll(255, 255, 255);
  //theaterChaseRainbow(100);
  //sablier();
  //RunningLights(255,0,255,100);
  /*
  for (int i = 0; i < 50; i++)
    SnowSparkle(0,0,128,500,1000);
    */
  Serial.println("[INIT] Done");
  //CylonBounce(80,0,0,3,50,250);
}

void loop() {
  /*
  delay(250);
  Serial.println("Strip index: " + String(stripIndex));
  for (int i = 0; i < stripIndex; i++)
  {
    ledStrip[i] = CRGB::White;
  }
  stripIndex++;
  if (stripIndex == 72)
    stripIndex = 0;
  FastLED.show();
  */
  atomBtn.read();
  if (atomBtn.wasPressed())
  {
    if (ledStatus)
      whiteLedOff();
      else
      whiteLedOn();
  }
  //  Serial.println("Button pressed");
  mesh.update();
  //M5.update(); //check M5 button or touch status
}
