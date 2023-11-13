#include "Arduino.h"
#include "Sumo.h"

// PWM
#define PIN_ENA		6
#define PIN_ENB		3

// Digital
#define PIN_IN1		4
#define PIN_IN2		5
#define PIN_IN3		2
#define PIN_IN4		7
#define PIN_BTN	 10
#define PIN_SW1  11
#define PIN_SW2  12

// Analog
#define PIN_DISTRIGHT	 0
#define PIN_DISTLEFT	 1
#define PIN_LINEFRONT	 2
#define PIN_LINEBACK	 3

// Local variables
static bool gameRunning;
static int prevBtnState;
static Tactic_t gameTactic;

void initSumo(void) {
	// Configure pins
	pinMode(PIN_ENA, OUTPUT);
	pinMode(PIN_IN1, OUTPUT);
	pinMode(PIN_IN2, OUTPUT);
	pinMode(PIN_IN3, OUTPUT);
	pinMode(PIN_IN4, OUTPUT);
	pinMode(PIN_ENB, OUTPUT);
	pinMode(PIN_BTN, INPUT_PULLUP);
	pinMode(PIN_SW1, INPUT_PULLUP);
	pinMode(PIN_SW2, INPUT_PULLUP);
	pinMode(PIN_DISTRIGHT, INPUT);
	pinMode(PIN_DISTLEFT, INPUT);
	
	// Configure serial
	Serial.begin(9600);
	
	gameRunning = false;
  
	prevBtnState = digitalRead(PIN_BTN);
}


// Get the selected tactic (two switches).
Tactic_t getTactic(void) {
  // Do not change tactic during game
  if(gameRunning) {
    return gameTactic;
  }
  
  return (digitalRead(PIN_SW1) << 1) | digitalRead(PIN_SW2);
}

// Get distance front
bool isFrontFree(void) {
  int limit = 700;
  return leftDistance() > limit && rightDistance() > limit;
}

// Get distance from left IR sensor.
int leftDistance(void) {
  return 1023 - analogRead(PIN_DISTLEFT);
}

// Get distance from right IR sensor.
int rightDistance(void) {
  return 1023 - analogRead(PIN_DISTRIGHT);
}


bool isBlackDetectedFront(void) {
  return analogRead(PIN_LINEFRONT) > 300;
}


bool isBlackDetectedBack(void) {
  return analogRead(PIN_LINEBACK) > 300;
}

// Block execution until the game is started with the push button.
bool isGameRunning(void) {
  // Look for rising flank on button
  if(prevBtnState == LOW && digitalRead(PIN_BTN) == HIGH) {
    // Lock tactic for this game
    gameTactic = getTactic();

    // Toggle running
    gameRunning = gameRunning ? false : true;
  }
  prevBtnState = digitalRead(PIN_BTN);

  return gameRunning;
}

// Rotate left and right wheels [-255, 255].
void move(int Left, int Right) {
  analogWrite(PIN_ENA, abs(Left));
  analogWrite(PIN_ENB, abs(Right));

  if (Left < 0) {
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, HIGH);
  } else {
    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, LOW);
  }
  if (Right < 0) {
    digitalWrite(PIN_IN3, HIGH);
    digitalWrite(PIN_IN4, LOW);
  } else {
    digitalWrite(PIN_IN3, LOW);
    digitalWrite(PIN_IN4, HIGH);
  }
}

void goForward(void){
  move(205,200);
}

void turnLeft(void){
  move(-255,255);
  delay(165);
  move(0,0);
  delay(500);
}

void turnRight(void){
  move(240,-255);
  delay(165);
  move(0,0);
  delay(500);
}

// Print all sensor values to the serial port
void debugPrint() {
  String str = "Button=";
  str += digitalRead(PIN_BTN);
  str += ", Tactic=";
  str += getTactic();
  str += ", BlackDetectedFront=";
  str += isBlackDetectedFront();
  str += ", BlackDetectedBack=";
  str += isBlackDetectedBack();
  str += ", LeftDistance=";
  str += leftDistance();
  str += ", RightDistance=";
  str += rightDistance();
  Serial.println(str);
}
