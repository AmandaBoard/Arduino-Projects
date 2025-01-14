int a = 0;
int b = 1;
int c = 2;
int d = 3;
int e = 4;
int f = 5;
int g = 6;
int h = 7;

// Potentiometer connected to analog pin A0
const int potPin = A0;


void displayP(){
  digitalWrite(h, HIGH);
}

void display1(){
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}

void display2(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(d, HIGH);
}

void display3(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
}

void display4(){
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}

void display5(){
  digitalWrite(a, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
}

void display6(){
  digitalWrite(a, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void display7(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}

void display8(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void display9(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void display0(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
}

void displayA(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void displayB(){
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void displayC(){
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(g, HIGH);
}

void displayD(){
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(g, HIGH);
}

void displayE(){
  digitalWrite(a, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void displayF(){
  digitalWrite(a, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void clearDisplay(){
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(h, LOW);
}

int digR = 8; // Making this low lights up right digit
int digL = 9; // Making this low lights up left digit

void setup() {
  // Set up the potentiometer pin
  pinMode(potPin, INPUT);

  // Set up 7-segment display pins as output
  for (int j = 0; j < 8; j++) {
    pinMode(j, OUTPUT);
  }

  // Set up the pins controlling multiplexing
  pinMode(digR, OUTPUT);
  pinMode(digL, OUTPUT);
}

void loop() {
  // Read the potentiometer value
  int potValue = analogRead(potPin);
  // Convert to a 0-255 range for hexadecimal display
  int percentage = map(potValue, 0, 1023, 0, 255);

  // Display the value
  //displayNum(percentage, 16);
  display(percentage, 1, 1);
}

void display(int value, char base, char blanking){
  int b = 1;
  if (base == 0){
    b = 10;
  } else if (base == 1){
    b=16;
  }

  int left = value/b;
  int right = value%b;
  int lp = 0;
  while (lp<5000){
    if (left == 0 && blanking == 0){
      //send displayL nothing. technically don't need below 2 lines but they help match timing
      displayL();
      clearDisplay();
      displayR();
      chooseNum(right);
      clearDisplay();
    } else {
      displayL();
      chooseNum(left);
      clearDisplay();
      displayR();
      chooseNum(right);
      clearDisplay();
    }
    lp++;
  }
}

void displayNum(int x, int b){
  int left = x / b;
  int right = x % b;
  int lp = 0;
  while (lp < 5000){
    if (left == 0) {
      // If the left digit is 0, only display the right digit
      displayL();
      clearDisplay();
      displayR();
      chooseNum(right);
      clearDisplay();
    } else {
      // Display both digits
      displayL();
      chooseNum(left);
      clearDisplay();
      displayR();
      chooseNum(right);
      clearDisplay();
    }
    lp++;
  }
}

void chooseNum(int x){
  switch (x) {
    case 0: display0(); break;
    case 1: display1(); break;
    case 2: display2(); break;
    case 3: display3(); break;
    case 4: display4(); break;
    case 5: display5(); break;
    case 6: display6(); break;
    case 7: display7(); break;
    case 8: display8(); break;
    case 9: display9(); break;
    case 10: displayA(); break;
    case 11: displayB(); break;
    case 12: displayC(); break;
    case 13: displayD(); break;
    case 14: displayE(); break;
    case 15: displayF(); break;
  }
}

void displayL(){
  digitalWrite(digR, HIGH);
  digitalWrite(digL, LOW);
}

void displayR(){
  digitalWrite(digR, LOW);
  digitalWrite(digL, HIGH);
}
