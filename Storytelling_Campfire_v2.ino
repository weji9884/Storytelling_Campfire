#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define fsrpinA 2
#define fsrpinB 3
#define fsrpinC 4
#define fsrpinD 5
#define fsrpinE 6
#define fsrpinF 7

#define PIN 8
const int trigPin = 9;
const int echoPin = 10;

float duration, distance;
bool Auntold = true;
bool Buntold = true;
bool Cuntold = true;
bool Duntold = true;
bool Euntold = true;
bool Funtold = true;


const int buzzer = 11; //buzzer to arduino pin 8

//  The overall fire brightness
//  (this can affect both color levels and power consumption)
int brightness = 128;

//Define variable to store sensor readings:
int fsrreadingA; //Variable to store FSR value A
int fsrreadingB; //Variable to store FSR value B
int fsrreadingC; //Variable to store FSR value C
int fsrreadingD; //Variable to store FSR value D
int fsrreadingE; //Variable to store FSR value E
int fsrreadingF; //Variable to store FSR value F


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(brightness);
  strip.show(); // Initialize all pixels to 'off'
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 8 as an output
  Serial.begin(9600);
}


void loop() {
//  fire();
  motion();
}

void nofire(){
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
  delay(100);
}

void fire(){
  // for the flame code https://codebender.cc/sketch:271084#Neopixel%20Flames.ino
  //  Uncomment one of these RGB (Red, Green, Blue) values to
  //  set the base color of the flame.  The color will flickr
  //  based on the initial base color
  
  //  Regular (orange) flame:
    int r = 226, g = 121, b = 35;

  //  Purple flame:
  //  int r = 158, g = 8, b = 148;

  //  Green flame:
  //int r = 74, g = 150, b = 12;

  //  Flicker, based on our initial RGB values
  for (int i = 0; i < strip.numPixels(); i++) {
    int flicker = random(0,55);
    int r1 = r - flicker;
    int g1 = g - flicker;
    int b1 = b - flicker;
    if(g1 < 0) g1 = 0;
    if(r1 < 0) r1 = 0;
    if(b1 < 0) b1 = 0;
    strip.setPixelColor(i, r1, g1, b1);
  }
  strip.show();

  //  Adjust the delay here, if you'd like.  Right now, it randomizes the 
  //  color switch delay to give a sense of realism
  delay(random(10, 113));
}

void motion(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(50);
  if(distance >= 40 || distance <= 5){
    Serial.println(" no motion detected");
    nofire();
  }else{
    Serial.println(" incoming");
    fire();
    seat();
  }
}

void seat(){
  // Read the FSR pin and store the output as fsrreading:
  fsrreadingA = digitalRead(fsrpinA);
  fsrreadingB = digitalRead(fsrpinB);
  fsrreadingC = digitalRead(fsrpinC);
  fsrreadingD = digitalRead(fsrpinD);
  fsrreadingE = digitalRead(fsrpinE);
  fsrreadingF = digitalRead(fsrpinF);

  // Print the fsrreading in the serial monitor:
  // Print the string "Analog reading = ".
  Serial.print("Ditial reading = ");
  // Print the fsrreading:
  Serial.print(fsrreadingA);
  Serial.print("  ||  ");
  Serial.print(fsrreadingB);
  Serial.print("  ||  ");
  Serial.print(fsrreadingC);
  Serial.print("  ||  ");
  Serial.print(fsrreadingD);
  Serial.print("  ||  ");
  Serial.print(fsrreadingE);
  Serial.print("  ||  ");
  Serial.println(fsrreadingF);

//  printf("%d, %d, %d, %d, %d, %d", fsrreadingA, fsrreadingB, fsrreadingC, fsrreadingD, fsrreadingE, fsrreadingF);

  if (fsrreadingA == 1 && Auntold){
    Serial.println(" #1 Seat on");
    story(1); 
    Auntold = false; // end the story, so the story only play once
  }  if (fsrreadingB == 1 && Buntold){
    Serial.println(" #2 Seat on");
    story(2);
    Buntold = false;
  }  if (fsrreadingC == 1 && Cuntold){
    Serial.println(" #3 Seat on");
    story(3);
    Cuntold = false;
  }  if (fsrreadingD == 1 && Duntold){
    Serial.println(" #4 Seat on");
    story(4);
    Duntold = false;
  }  if (fsrreadingE == 1 && Euntold){
    Serial.println(" #5 Seat on");
    story(5);
    Euntold = false;
  }  if (fsrreadingF == 1 && Funtold){
    Serial.println(" #6 Seat on");
    story(6);
    Funtold = false;
  } 
  else{
    Serial.println("  Empty");
  }
  if (fsrreadingA == 0 && fsrreadingB == 0 && fsrreadingC == 0 && 
  fsrreadingD == 0 && fsrreadingE == 0 && fsrreadingF == 0) {
    Auntold = Buntold = Cuntold = Duntold = Euntold = Funtold = true; // reset the story 
  }
}

void story(int x){ // this is a test function for the logic and the circuit
  if (x == 1) {
    for (int i = 0; i < 10; i++) {
      tone(buzzer, 100); // Send 1KHz sound signal...
      delay(100);        // ...for .5 sec
      noTone(buzzer);     // Stop sound...
      delay(50);        // ...for .5 sec
    }
  } if (x == 2) {
      for (int i = 0; i < 10; i++) {
        tone(buzzer, 300); 
        delay(100);       
        noTone(buzzer);     
        delay(50);        
      }
  } if (x == 3) {
      for (int i = 0; i < 10; i++) {
        tone(buzzer, 500); 
        delay(100);       
        noTone(buzzer);     
        delay(50);        
      }
  } if (x == 4) {
      for (int i = 0; i < 10; i++) {
        tone(buzzer, 700); 
        delay(100);       
        noTone(buzzer);     
        delay(50);        
      }
  } if (x == 5) {
      for (int i = 0; i < 10; i++) {
        tone(buzzer, 900); 
        delay(100);       
        noTone(buzzer);     
        delay(50);        
      }
  } if (x == 6) {
      for (int i = 0; i < 10; i++) {
        tone(buzzer, 1100); 
        delay(100);       
        noTone(buzzer);     
        delay(50);        
      }
  }
}
