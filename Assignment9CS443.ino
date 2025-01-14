#include <Servo.h>

int led = HIGH;
const int red = 12;
const int yellow = 11;
const int green = 10;
const int servo = 9;
Servo servoMotor;

const int rows[] = {7,0,1,3};
const int cols[] = {2,4,5,6};

const int KeyPad[4][4] = { {1, 2, 3, 10},
                           {4, 5, 6, 20},
                           {7, 8, 9, 30},
                           {50, 0, 60, 40} };




int password[4] = {0,2,0,3};
int guess[4];

//0 = unlocked, 1=locked
int currentPosition;

//0 = unlocked-green, 1 = yellow, 2 = locked-red
int state;
int checkPass;

//button debouncing 
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100;
int reading;

int ScanKeypad(){
  for(int r = 0; r < 4; r++){
    //rows are output and low
    pinMode(rows[r], OUTPUT);
    digitalWrite(rows[r], 0);

    //check cols
    for(int c = 0; c < 4; c++){
    reading = digitalRead(cols[c]);

    //debounce buttons
    if(reading == 0){
      lastDebounceTime = millis();
      while((millis() - lastDebounceTime) < debounceDelay){
      }

      reading = digitalRead(cols[c]);
      if(reading == 0){
        //set rows as input
        digitalWrite(rows[r], 1);
        pinMode(rows[r], INPUT_PULLUP);
        digitalWrite(rows[r], 1);
        //return value
        return KeyPad[r][c];
      }
    }
  }
  //rows to high
  digitalWrite(rows[r], 1);
  pinMode(rows[r], INPUT_PULLUP);
  digitalWrite(rows[r], 1);
  }
  return 99;
}


void setup() {
  //LEDs
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(13, OUTPUT); 

  //keypad
  for(int i = 0; i < 4; i++){
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], 1);

    //set cols as pullup
    pinMode(cols[i], INPUT_PULLUP);
    digitalWrite(cols[i], 1);
  }

  //servo
  servoMotor.attach(servo);

  //setup starting position for servo (unlocked green = on)
  currentPosition = 0;
  state = 0;
  servoMotor.write(0);
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
}

void loop() {
  int press = ScanKeypad();
  if(press == 99){
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  
  //check if locked, then if input is being recieved
  if(state == 2){
    if(press >= 0 && press < 10){
      state = 1;
      digitalWrite(yellow, HIGH);
      digitalWrite(green, LOW);
      digitalWrite(red, LOW);
      checkPass = 0;
    }
  }
  //check if yellow / currently guessing the password
  if(state == 1){
    if(checkPass < 4 && press != 99){
      guess[checkPass] = press;
      //increment password guess attempts to 4
      checkPass += 1;
    }
    int wrong = 0;
    //once 4 inputs have been recieved, check if password is right
    if(checkPass == 4){
      for(int i = 0; i < 4; i++){
        if(guess[i] != password[i]){
          wrong = 1;
        }
      }
      //lock if bad password (Wrong = 1)
      if(wrong){
        state = 2;
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);
        digitalWrite(red, HIGH);
        delay(10);
      } else {
        //correct guess
        state = 0;
        currentPosition = 0;
        digitalWrite(yellow, LOW);
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        servoMotor.write(0);
        delay(10);
      }
    }
  }
  //if it is currently unlocked - check for A input (10) then lock if A is pressed
  else if(state == 0){
    if(press == 10){
      state = 2;
      currentPosition = 1;
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      servoMotor.write(180);
      delay(10);
    }
  }
  }
}
