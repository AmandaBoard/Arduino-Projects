//Defining Pins

int buttonPin = 10;
int ledPin = 13;
int segmentPins[7] = {0,1,2,3,4,5,6};

void setup(){
  //set button pin as input
  pinMode(buttonPin, INPUT);
  
  //set 7 seg display to output
  for(int i = 0; i < 8; i++){
    pinMode(segmentPins[i], OUTPUT);
     //turn off 7 seg display
    digitalWrite(segmentPins[i], LOW);
  }


}