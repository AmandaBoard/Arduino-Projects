int a = 0; 
int b = 1;
int c = 2;
int d = 3;
int e = 4;
int f = 5;
int g = 6;
int h = 7;

//set up left digit and right digit pins
//if low then will light up right/left
int rightSide = 9;
int leftSide = 8;

const int rows[] = {7,0,1,3};
const int cols[] = {2,4,5,6};

const int KeyPad[4][4] = { {1, 2, 3, 10},
                           {4, 5, 6, 20},
                           {7, 8, 9, 30},
                           {50, 0, 60, 40} };

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
  return ;
}

void DisplayNothing(){
  digitalWrite(h, HIGH);

}

void Display0(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
}

void Display1(){
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}

void Display2(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(d, HIGH);
}

void Display3(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
}

void Display4(){
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}

void Display5(){
  digitalWrite(a, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
}

void Display6(){
  digitalWrite(a, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void Display7(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}

void Display8(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void Display9(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void DisplayA(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  
}

void DisplayNum(int n){
  switch(n){
    case -1: ClearDisplay(); break;
    case 0: Display0(); break;
    case 1: Display1(); break;
    case 2: Display2(); break;
    case 3: Display3(); break;
    case 4: Display4(); break;
    case 5: Display5(); break;
    case 6: Display6(); break;
    case 7: Display7(); break;
    case 8: Display8(); break;
    case 9: Display9(); break;
    case 10: DisplayA(); break;
    case 99: DisplayNothing(); break;
  }
}

void LeftDisplay(){
  digitalWrite(rightSide, HIGH);
  digitalWrite(leftSide, LOW);
}

void RightDisplay(){
  digitalWrite(rightSide, LOW);
  digitalWrite(leftSide, HIGH);
}

void ClearDisplay(){
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(h, LOW);
}

void display(int val, char base, char blank){
  int b = 1;
  if(base == 0){
    b = 10;
  } else if (base == 1){
    b = 16;
  }
  int left = (val / b);
  int right = (val % b);
  int increment = 0;

  //clear display
  ClearDisplay();

  while(increment < 5000){
    if( left == 0 && blank == 0){
      LeftDisplay();
      ClearDisplay();
      RightDisplay();
      DisplayNum(right);
      ClearDisplay();
    } else {
      LeftDisplay();
      DisplayNum(left);
      ClearDisplay();
      RightDisplay();
      DisplayNum(right);
      ClearDisplay();
    }
    increment++;
  }
}

void setup(){
  pinMode(13, OUTPUT);

  //set pins as output and high
  pinMode(rightSide, OUTPUT);
  pinMode(leftSide, OUTPUT);
  digitalWrite(rightSide, 1);
  digitalWrite(leftSide, 1);

  for(int i = 0; i < 4; i++){
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], 1);

    //set cols as pullup
    pinMode(cols[i], INPUT_PULLUP);
    digitalWrite(cols[i], 1);
  }
}

void loop(){
  int press = ScanKeypad();
  if(press != 99){
    //set 7 seg display
    for(int s = 0; s <= 7; s++){
      pinMode(s, OUTPUT);
    }

    //display input
    display(press, 0, 0);

    //multiplex to high
    digitalWrite(rightSide, 1);
    digitalWrite(leftSide, 1);


    for(int i = 0; i < 4; i++){
      //rows to output
      pinMode(rows[i], OUTPUT);
      digitalWrite(rows[i], 1);
      //set cols internal pullup
      pinMode(cols[i], INPUT_PULLUP);
      digitalWrite(cols[i], 1);
    }
  }
}


