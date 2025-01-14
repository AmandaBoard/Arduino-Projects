#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2); //set up the display
const int switchPin = 6; //input
int switchState = 0; // track current switch value
int previousState = 0; //track switch statement has been
int response;

void setup() {
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT_PULLUP);

  //note display can only print 16 chars per line (i believe)
  lcd.print("Ask the");
  lcd.setCursor(0,1);
  lcd.print("Magic Display!");
}

void loop() {
  switchState = digitalRead(switchPin);
  if(switchState != previousState){
    if(switchState == LOW){
      response = random(27);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Fate predicts:");
      lcd.setCursor(0,1);

      switch(response){
        case 0: lcd.print("Yes."); break;
        case 1: lcd.print("Surely."); break;
        case 2: lcd.print("You wish."); break;
        case 3: lcd.print("Never."); break;
        case 4: lcd.print("Ask Again."); break;
        case 5: lcd.print("Doubtful."); break;
        case 6: lcd.print("Maybe."); break;
        case 7: lcd.print("big nope."); break;
        case 8: lcd.print("No."); break;
        case 9: lcd.print("Order Pizza."); break;
        case 10: lcd.print("Taco Bell?"); break;
        case 11: lcd.print("Perchance."); break;
        case 12: lcd.print("If you want."); break;
        case 13: lcd.print("Likely."); break;
        case 14: lcd.print("Not likely."); break;
        case 15: lcd.print("Foolish Request."); break;
        case 16: lcd.print("Wait for it."); break;
        case 17: lcd.print("Not good."); break;
        case 18: lcd.print("Possibly."); break;
        case 19: lcd.print("Why not?"); break;
        case 20: lcd.print("You're cooked."); break;
        case 21: lcd.print("2 Wishes Left."); break;
        case 22: lcd.print("I don't know."); break;
        case 23: lcd.print("Tread carefully."); break;
        case 24: lcd.print("To be or..."); break;
        case 25: lcd.print("...not to be."); break;
        case 26: lcd.print("You again?"); break;
        case 27: lcd.print("Try Again."); break;
      }
    }
  }
  previousState = switchState;
  
}
