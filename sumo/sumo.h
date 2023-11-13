#ifndef SUMO_H_
#define SUMO_H_

// Enum for tactics
typedef enum {
	TACTIC_0 = 0,
	TACTIC_1,
	TACTIC_2,
	TACTIC_3,
  NUMBER_OF_TACTICS
} Tactic_t;

// Init function, setup pin configuration.
// MUST BE CALLED BEFORE USING ANDY OTHER FUNCTION IN THIS LIBRARY
void initSumo(void);


// Function returning the currently selected tactic.
// The tactic will not change during an active game
//
// Return: Tactic_t enum from TACTIC_0 to TACTIC_1
Tactic_t getTactic(void);


bool isFrontFree(void);

// Get distance from the right IR-sensor.
//
// Return:  positive integer increasing with greater distance
//          to nearest object
int rightDistance(void);


// Get distance from the left IR-sensor. 
//
// Return:  positive integer increasing with greater distance
//          to nearest object
int leftDistance(void);



bool isBlackDetectedFront(void);

bool isBlackDetectedBack(void);


// Get status if the start game switch has been pressed.
// This value vill toggle on each time the button is released
//
// Return:  toggling between true and false on each press
bool isGameRunning(void);


// Activate left and right motors in forward or reverse direction.
// valid values are -255 to 255 with a positive value moving forward
// and a negative moving in reverse
//
// Left:    Speed of left motor [-255 255]
// Right:   Speed of right motor [-255 255]
void move(int Left, int Right);

void goForward(void);
void turnLeft(void);
void turnRight(void);


// Print all sensor values to the serial port. Can be read using
// the serial monitor in the Arduiono environment.
void debugPrint(void);

#endif /* SUMO_H_ */
