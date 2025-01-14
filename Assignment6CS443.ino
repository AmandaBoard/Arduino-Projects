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

const int startButton = 11;
int startTimer = 0;
volatile int wholeSeconds = 0;
volatile int tenthSeconds = 0;
volatile int quartSeconds = 0;


int buttonState = HIGH;
int lastButtonState = HIGH;
int lastDebounceTime = 0;


void DisplayNothing()
{
  digitalWrite(h, HIGH);
}

void Display0()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
}

void Display1()
{
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}

void Display2()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(d, HIGH);
}

void Display3()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
}

void Display4()
{
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}

void Display5()
{
  digitalWrite(a, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
}

void Display6()
{
  digitalWrite(a, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void Display7()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}

void Display8()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void Display9()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void DisplayDecimal(){
  digitalWrite(h, HIGH);
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
    case 10: DisplayDecimal(); break;
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

//checks if value given needs a decimal
void display(int val, int decimal, int check)
{
  int leftNum;
  int rightNum;
  int b = 1;
  if(check == 0)
  {
    leftNum = val / 10;
    rightNum = val % 10;
  } else 
  {
    rightNum = val;
  }

  //clear display
  LeftDisplay();
  ClearDisplay();
  RightDisplay();
  ClearDisplay();


    //less than 10, display regular value to 1.1-9.9. 
    if( decimal == 1 && check == 0)
    {
      LeftDisplay();
      DisplayNum(leftNum);
      DisplayNum(10);
      ClearDisplay();
      RightDisplay();
      DisplayNum(rightNum);
      ClearDisplay();

    // only display decimal on the left
    } else if(decimal == 1 && check == 1)
    {
      LeftDisplay();
      DisplayNum(10);
      ClearDisplay();
      RightDisplay();
      DisplayNum(rightNum);
      ClearDisplay();

      // no decimal
    } else 
    {
      LeftDisplay();
      DisplayNum(leftNum);
      ClearDisplay();
      RightDisplay();
      DisplayNum(rightNum);
      DisplayNum(10);
      ClearDisplay();
    }
}

void setup(){
  //set up 7 seg display and pins 8/9 to multiplex
  for(int i = 0; i < 10; i++)
  {
    pinMode(i, OUTPUT);
  }

  //set up button as input
  pinMode(startButton, INPUT);

  //set timers and interrupts, timer A/B
  TCCR1A = 0;
  OCR1A = 25000;
  TCCR1B = 0;
  OCR1B = 62500;

  //prescalar and enabling interrupt for compareA and compareB timer 1 interrupt
  TCCR1B |= B00000011;
  TIMSK1 = B00000110;

  while(digitalRead(startButton) == 1)
  {
    //wait for input
  }

  //check for bounces
  volatile int ten = tenthSeconds;
  int t = 0;
  while(t < 2)
  {
    if(tenthSeconds > ten)
    {
      t++;
    }
    ten = tenthSeconds;
  }
  display(0,1,0);
}


//timer 1 - compA update the fequency and set tenths/seconds
ISR(TIMER1_COMPA_vect)
{
  OCR1A += 25000;
  if(tenthSeconds == 9)
  {
    wholeSeconds += 1;
  }
  tenthSeconds = ((tenthSeconds + 1) % 10);
}

//timer 1 - compB update the frequency and set quartseconds
ISR(TIMER1_COMPB_vect)
{
  OCR1B += 62500;
  quartSeconds = ((quartSeconds + 1) % 4);
}

int time;
void loop(){
  if(startTimer == 1)
  {
    //show regular time
    if(wholeSeconds < 10)
    {
      display(((wholeSeconds * 10) + tenthSeconds), 1, 0);    
    }
    else
    {
      if(quartSeconds % 2 == 0)
      {
        display(wholeSeconds, 0,0);
        time = tenthSeconds;
      }
      else 
      {
        display(time, 1, 1);
      }
    }
  }
  //show 0
  else 
  {
    display(0,1,0);
  }

  //read in button press 
  int reading = digitalRead(startButton);
  if(reading != lastButtonState)
  {
    lastDebounceTime = tenthSeconds;
    int count = 0;
    while(count < 1)
    {
      if(tenthSeconds >= lastDebounceTime)
      {
        count++;
      }
      //maintain display throughout
      display(wholeSeconds, 0, 0);
    }
    //update based on reading
    reading = digitalRead(startButton);
    if(reading == LOW)
    {
      buttonState = reading;
      if(buttonState == 0)
      {
        //reset when button is hit again
        wholeSeconds = 0;
        tenthSeconds = 0;
        startTimer = !startTimer;
      }
    }
  }
  lastButtonState = reading;
}


