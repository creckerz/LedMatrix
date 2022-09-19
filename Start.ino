//------------------------------------------------------Library's------------------------------------------------------
#include <WS2812Serial.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <IRremote.h>
//------------------------------------------------------/Library's------------------------------------------------------

//------------------------------------------------------Declaration------------------------------------------------------
//        --Matrix--
const int pin = 5;                                                          //WS2812B Data Pin || Usable pins on Teensy 3.2:    1, 5, 8, 10, 31   (overclock to 120 MHz for pin 8)
const int matrix_height = 16;                                               //Height of matrix
const int matrix_width = 16;                                                //Width of matrix
const int numled = matrix_height * matrix_width;                            //Calculated number of LEDs in matrix

byte drawingMemory[numled*3];                                               //3 bytes per LED
DMAMEM byte displayMemory[numled*12];                                       //12 bytes per LED
WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

//        --Colors--
int brightnes = 13;
volatile int colorpicker = 0;                                               //Interrupt variables for color control
volatile int colorMode = 0;
#define allColorModes 5
#define ColorCount 3
int colors[ColorCount][matrix_width];                                    //2D Array, holds n(column) RGB Hexcodes
int rgbs[ColorCount][6]{
  {
    0,0,255,255, 0, 0                                                   //R,G,B R,G,B
  },
  {
    255,0,255, 255, 255, 0
  },
  {
    255,255,0, 5, 5, 255
  }
};

//        --Display Mode--
volatile int Mode = 0; 
#define AllModes 3

//        --Audio/FFT--
#define ADC_INPUT_PIN   A1                                                  //Audio Signal Input Pin
float scale = 128.0;                                                        //FFT data is very low, multiply with scale to fill height of matrix
float level[matrix_height];                                                 //holds FFT data
int shown[matrix_height];                                                   //holds matrix data

AudioInputAnalog         input(ADC_INPUT_PIN);                              //Audio Signal Input Setup
AudioAnalyzeFFT1024      fft;                                               //Create FFT object (256Bands)
AudioConnection          audioConnection(input, 0, fft, 0);                 //Connect Audio Input with FFT

//        --Snake Parameters--
bool snakeStarted = false;
int arraySize = 2;
int snakeLength = 2;
int snakePos[254][3];
int snakeHeadTail [2][2];
IntervalTimer TimerMoveSnake;
bool dirR = false, dirL = false, dirD = false, dirU = false;
int seed[2];

//        --Remote--
int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);  
decode_results results;

//------------------------------------------------------/Declaration------------------------------------------------------

//--------------------------------------------------------setup()---------------------------------------------------------
void setup() {
  generateColors();
  pinMode(17, INPUT);                                                       //Setup button on pin 17
  attachInterrupt(9, colorPickerNext, FALLING);                            //Trigger interrupt on negativ flank of button, call colorPickerNext(ISR)
  attachInterrupt(10, colorModeNext, FALLING);
  attachInterrupt(11, ModePickerNext, FALLING);
  attachInterrupt(12, lightDimmer, FALLING);
  
  irrecv.enableIRIn();     
  
  AudioMemory(12);                                                          //AudioLibrary needs memory to run
  
  leds.begin();                                                             //start matrix
  leds.show();                                                              
}
//--------------------------------------------------------/setup()--------------------------------------------------------


void generateColors(){
  for(int i = 0; i < ColorCount; i++){
      createFade(rgbs[i][0] / brightnes, rgbs[i][1] / brightnes, rgbs[i][2] / brightnes, rgbs[i][3] / brightnes, rgbs[i][4] / brightnes, rgbs[i][5] / brightnes, i);
  }
}

void replaceRGB(int ROne, int GOne, int BOne, int RTwo, int GTwo, int BTwo, int arrayPlace){
  rgbs[arrayPlace][0] = ROne;
  rgbs[arrayPlace][1] = GOne;
  rgbs[arrayPlace][2] = BOne;
  rgbs[arrayPlace][3] = RTwo;
  rgbs[arrayPlace][4] = GTwo;
  rgbs[arrayPlace][5] = BTwo;
}
//-------------------------------------------------createFade()/ISR--------------------------------------------------
void createFade(int ROne, int GOne, int BOne, int RTwo, int GTwo, int BTwo, int arrayPlace){

  float Rdiff = (RTwo - ROne)/14;  float Gdiff = (GTwo - GOne)/14;  float Bdiff = (BTwo - BOne)/14; //Differenz berechnen
  for(int i = 0; i < 16; i++){
    colors[arrayPlace][i] = createRGB((ROne + i * Rdiff), (GOne + i * Gdiff), (BOne + i * Bdiff));
  }
}

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}
//-------------------------------------------------createFade()/ISR--------------------------------------------------
