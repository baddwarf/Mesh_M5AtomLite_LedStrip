void showStrip()
{
  FastLED.show();
}


byte * Wheel(byte WheelPos) {
  static byte c[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

// Set a LED color (not yet visible)
void setPixel(int Pixel, byte red, byte green, byte blue) {
   ledStrip[Pixel].r = red;
   ledStrip[Pixel].g = green;
   ledStrip[Pixel].b = blue;
}

// Set all LEDs to a given color and apply it (visible)
void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < STRIP_LED_COUNT; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void whiteLedOn()
{
  statusLed[0] = CRGB::DarkGreen;
  setAll(255, 255, 255);
  ledStatus = true;
  meshSendEvent(meshRootNode, DEVTYPE_LEDSTRIP, EVTCLASS_LEDSTRIP_ON, "");
}

void whiteLedOff()
{
  statusLed[0] = CRGB::DarkRed;
  setAll(0, 0, 0);
  ledStatus = false;
  meshSendEvent(meshRootNode, DEVTYPE_LEDSTRIP, EVTCLASS_LEDSTRIP_OFF, "");
}

void RGBLoop()
{
  for(int j = 0; j < 3; j++ ) {
    // Fade IN
    for(int k = 0; k < 256; k++) {
      switch(j) {
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) {
      switch(j) {
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < STRIP_LED_COUNT-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = STRIP_LED_COUNT-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
 
  delay(ReturnDelay);
}

void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAll(red,green,blue);
 
  int Pixel = random(STRIP_LED_COUNT);
  setPixel(Pixel,0xff,0xff,0xff);
  showStrip();
  delay(SparkleDelay);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
 
  for(int i=0; i<STRIP_LED_COUNT*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<STRIP_LED_COUNT; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
     
      showStrip();
      delay(WaveDelay);
  }
}

void sablier()
{
  uint dropped;
  uint pos;

  dropped = 0;

  for (int i = 0; i < STRIP_LED_COUNT; i++)
  {
    // move srpite to end
    for (int j = 0; j < (STRIP_LED_COUNT - dropped); j++)
    {
      Serial.println("sablier-" + String(i) + ":" + String(j));
      setPixel(j, 255, 255, 255);
      showStrip();
      setPixel(j, 0, 0, 0);
      delay(25);
    }
    dropped++;
    // fill dropped pixels
    
    for (int k = (STRIP_LED_COUNT - dropped - 1); k < (STRIP_LED_COUNT - 1); k++)
    {
      setPixel(k, 255, 255, 255);
    }
    
  }

}

void theaterChaseRainbow(int SpeedDelay) {
  byte *c;
 
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < STRIP_LED_COUNT; i=i+3) {
          c = Wheel( (i+j) % 255);
          setPixel(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        showStrip();
       
        delay(SpeedDelay);
       
        for (int i=0; i < STRIP_LED_COUNT; i=i+3) {
          setPixel(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}