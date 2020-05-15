
int sensorValue = 0;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  sensorValue = analogRead(A0);
  digitalWrite(13, HIGH);
  delay(sensorValue); 
  digitalWrite(13, LOW);
  delay(sensorValue); 
}
