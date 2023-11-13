#include "sumo.h"

void setup() {
  initSumo();

  /* INIT CODE START */



  /* INIT CODE END */
}

void tacticZero() {
  /* TACTIC 0 CODE START */

  /* EXAMPLE START */
  while(isFrontFree()){
    goForward();
  }
  move(0,0);
  delay(500);

  turnLeft();
  while(isFrontFree()){
    goForward();
  }
  move(0,0);
  delay(2000);
  /* EXAMPLE END */
  
  /* TACTIC 0 CODE END */
}

void tacticOne() {
  /* TACTIC 1 CODE START */

  goForward();
  
  /* TACTIC 1 CODE END */  
}

void tacticTwo() {
  /* TACTIC 2 CODE START */



  /* TACTIC 2 CODE END */
}

void tacticThree() {
  /* TACTIC 3 CODE START */

  

  /* TACTIC 3 CODE END */
}

void loop() {
  // Check if start button has been pressed
  if(isGameRunning()) {
    // Execute tactic when game is running
    switch (getTactic()) {
      case TACTIC_0:
        tacticZero();
        break;
      case TACTIC_1:
        tacticOne();
        break;
      case TACTIC_2:
        tacticTwo();
        break;
      case TACTIC_3:
        tacticThree();
        break;
    }
  }
  else {
    // Stop and print sensor data to serial console
    move(0, 0);
    debugPrint();
  }
}

