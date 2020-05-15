float kp = 0.3;
float ki = 0.02;
float kd = 0.02;

const byte interruptPinA = 2;
const byte interruptPinB = 3;
int status = 0;
volatile int EncoderCount = 0;


const byte MOTOR_PWM_PIN = 6;
const byte MOTOR_PIN_1 = 7;
const byte MOTOR_PIN_2 = 8;

const byte ledPin = 13;
int ledState = HIGH;
long preLed = 0;
long ledInterval = 500;

const byte btn1 = 5;
const byte btn2 = 4;

int motorstage = 0;

volatile unsigned long count = 0;
unsigned long previousCount = 0;

unsigned long Time;
unsigned long previousTime= 0;

int deltaT;
volatile float setRPM=0;
volatile float currentRPM,commandRPM;
volatile float error,previousError = 0,iError = 0,dError;

String incoming;
String setpoint_str;
int setpoint;
  
void aCH_Callback()
{
  bool bCH_value = digitalRead(interruptPinB);
  if(bCH_value == false)
  {
    status=1; //cw
  	EncoderCount--;
  }
} 

//CW direction
void bCH_Callback()
{
  bool aCH_value = digitalRead(interruptPinA);
  if(aCH_value == false)
  {
    status = 2; //ccw
  	EncoderCount++;
  }
}

void setSpeed(int speed)
{
  //ccw => forward
  if(speed > 0)
  {
    if(speed > 255)
    {
      speed = 255;
    }
    digitalWrite(MOTOR_PIN_1,HIGH);
    digitalWrite(MOTOR_PIN_2,LOW);
    analogWrite(MOTOR_PWM_PIN,abs(speed));
  }
  //cw => backard
  else{
    if(speed < -255)
    {
      speed = -255;
    }
    digitalWrite(MOTOR_PIN_1,LOW);
    digitalWrite(MOTOR_PIN_2,HIGH);
    analogWrite(MOTOR_PWM_PIN,abs(speed));
    
  }
}

void toggleLed(){
  ledState = (ledState == HIGH)? LOW : HIGH;
  digitalWrite(ledPin,ledState);
}

void setup()
{
  Serial.begin(9600);
  
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(ledPin,OUTPUT);
  
  pinMode(interruptPinA, INPUT_PULLUP);
  pinMode(interruptPinB, INPUT_PULLUP);
  
  pinMode(btn1,INPUT);
  pinMode(btn2,INPUT);
  
  attachInterrupt(digitalPinToInterrupt(interruptPinA),aCH_Callback, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPinB),bCH_Callback, RISING);
  setSpeed(1);
  
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 12499; //Prescaler = 64
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11 | 1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
  
}
void loop()
{ 
  int cw = digitalRead(btn1);
  int ccw = digitalRead(btn2);
  unsigned long curLed = millis();
  
  
  switch (motorstage){
    case 0:
    	setSpeed(-255);
    	if (ccw == LOW){
          motorstage = 1;
    	}
    case 1:
    	setSpeed(255);
    	if (cw == LOW){
          motorstage = 0;
    	} 
  }
  
  if ( (curLed - preLed) > ledInterval){
    toggleLed();
    preLed = curLed;
  }
  
  Serial.println(motorstage);

  
  if (Serial.available()) 
  {
    char inByte = Serial.read();
    if (inByte == 's' && incoming.length() == 0){
      incoming += inByte;
    }
    
    if (inByte =='-' && incoming.length() == 1){
      incoming += inByte;
    }
    
    if(('0'<= inByte) && (inByte <= '9')){
      incoming += inByte;
    }
    Serial.println(incoming);
    if( inByte == 'n'){
      if( incoming[0] == 's' && incoming[1] == '-'){
        setpoint_str += '-';
        for (int i=0, n = incoming.length() ; i < n ; i++){
          if( ('0'<= incoming[i]) && (incoming[i] <= '9')){
            setpoint_str += incoming[i];
          }             
        }
        Serial.println(setpoint_str);
      }
      if( incoming[0] == 's' && incoming[1] != '-' ){
        for (int i=0, n = incoming.length() ; i < n ; i++){
          if( ('0'<= incoming[i]) && (incoming[i] <= '9')){
            setpoint_str += incoming[i];
          }
        }
      }
      int setpoint_map = setpoint_str.toInt();
      setpoint = map(setpoint_map,-100,100,-255,255);
      if ( setpoint > 255){
        setpoint = 255;
      }
      if ( setpoint < -255){
        setpoint = -255;
      }
      incoming = "";
      setpoint_str = "";
    }
    setRPM = setpoint;
  }
}

ISR(TIMER1_COMPA_vect) {
  count++;
}
