#define pwmA 3 //left
#define breakA 9
#define dirA 12
#define pwmB 11 //right
#define breakB 8
#define dirB 13

#define sensMidR 1
#define sensMidL 2
#define sensSideL 4
#define sensSideR 5

#define BLACK 255; //test what is the black of the line
#define WHITE 0; //check what is the white value

int sensorValue_MidR = analogRead(sensMidR);
int sensorValue_MidL = analogRead(sensMidL);
int sensorValue_SideR = analogRead(sensSidR);
int sensorValue_SideL = analogRead(sensSideL);

void setup() {
  
  Serial.begin (9600);
  pinMode (pwmA , OUTPUT);
  pinMode (breakA , OUTPUT);
  pinMode (dirA , OUTPUT);
  pinMode (pwmB , OUTPUT);
  pinMode (breakB , OUTPUT);
  pinMode (dirB , OUTPUT);

  pinMode (sensMidR, INPUT);
  pinMode (sensSideR, INPUT);
  pinMode (sensMidL, INPUT);
  pinMode (sensSideL, INPUT);
}


void loop () {
  
}


void readSensor()
{
  while (sensorValue_MidR == BLACK || sensorValue_MidL == BLACK)
  { 
    adjustTurn(); //its a small adjustment so the robot stays in line
    
    if (sensorValue_MidR == WHITE || sensorValue_MidL == WHITE)
    {
      goForward(); //just go forward
    }
  }
  
  while (sensorValue_SideR == BLACK || sensorValue_SideL == BLACK)
  {
    sharpTurn(); //when the edge sensors detect the line the motors will make a sharp turn still going forward until one of the middle sensor read again
  }
  
  if (sensorValue_SideR == BLACK && sensorValue_SideL == BLACK)
  {
    stopFunction();
  }
  
  if (sensorValue_MidR == BLACK && sensorValue_MidL == BLACK)
  {
    breakFunction();
  }
}

void adjustTurn
{
  //forward @ Channel A left side
  digitalWrite(dirB, HIGH); 
  digitalWrite(breakB, HIGH);  
  analogWrite(pwmB, sensorValueMidL);   //if turn is left read sensorValue right

  //forward @ ChannelB right side
  digitalWrite( dirA  , HIGH);  
  digitalWrite( breakA , HIGH);  
  analogWrite( pwmA, sensorValueMidR); //if turn is right read sensroValue left
}
