#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 9

#define EN_A 2
#define EN_B 3

int count = 0;

bool EN_curA = false; 
bool EN_curB = false; 
bool EN_preA = false; 
bool EN_preB = false; 

void EN_dir(bool dir){
  if(dir) {
    count++;
    Serial.println("Count = " + String(count) + " Direction: clockwise");
  }
  else {
    count--;
    Serial.println("Count = " + String(count) + " Direction: counter-clockwise");
  }
}

void EN_Check(){ // Call when encoder rotating 
    EN_curA = !digitalRead(EN_A);
    EN_curB = !digitalRead(EN_B);
    if(EN_curA&&EN_curB){
        if(EN_preA&&!EN_preB) EN_dir(1);
        else if(!EN_preA&&EN_preB) EN_dir(0);
    }
    EN_preA = EN_curA;
    EN_preB = EN_curB;
}

void setup(){
  pinMode(MOTOR_D1_PIN, OUTPUT);
  pinMode(MOTOR_D2_PIN, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(EN_A, INPUT_PULLUP);
  pinMode(EN_B, INPUT_PULLUP);
 
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(EN_A), EN_Check, FALLING);
   attachInterrupt(digitalPinToInterrupt(EN_B), EN_Check, FALLING);
}

void speed(int speed){
  if((0<=speed) && (speed<=255)){
    digitalWrite(MOTOR_D1_PIN, HIGH);
    digitalWrite(MOTOR_D2_PIN, LOW);
    analogWrite(MOTOR_PWM_PIN, speed);
  }else if((-255<=speed) && (speed<0)){
    digitalWrite(MOTOR_D1_PIN, LOW);
    digitalWrite(MOTOR_D2_PIN, HIGH);
    analogWrite(MOTOR_PWM_PIN, -speed);
  }
}

void loop(){
  speed(1);
  delay(1000);
  speed(2);
  delay(1000);
  speed(-1);
  delay(1000);
  speed(-2);
  delay(1000);
}