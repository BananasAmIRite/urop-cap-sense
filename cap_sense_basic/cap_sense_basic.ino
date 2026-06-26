#define SEND_PIN 5
#define RECV_PIN 4

void setup() {
  // put your setup code here, to run once:
  // while (!Serial); 

  Serial.begin(115200);
  Serial.println("Resistive Sensing");  

  pinMode(SEND_PIN, OUTPUT); 
  pinMode(RECV_PIN, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(SEND_PIN, HIGH); 

  Serial.print("0,");
  Serial.print("4095,");
  Serial.println(analogRead(RECV_PIN)); 


  // unsigned long time = measureTimeToRiseSampled(30); 

  // Serial.println(time); 



  // delay(10); 

}

unsigned long measureTimeToRiseSampled(int numSamples) {
  unsigned long tot = 0; 
  for (int i = 0; i < numSamples; i++) {
    tot += measureTimeToRise(); 
  }

  return tot / numSamples; 
}


unsigned long measureTimeToRise() {

  // reset pin states
  digitalWrite(SEND_PIN, LOW); // set send pin to low
  // ensure receive pin is also low
  pinMode(RECV_PIN, OUTPUT); 
  digitalWrite(RECV_PIN, LOW); 
  delayMicroseconds(10); 
  // config receive pin back to input state
  pinMode(RECV_PIN, INPUT); 

  // conduct test now, write send pin to HIGH and measure time
  digitalWrite(SEND_PIN, HIGH); 
  unsigned long startTime1 = micros(); 

  while (digitalRead(RECV_PIN) == LOW) {}

  unsigned long endTime1 = micros(); 

  unsigned long measuredTime1 = endTime1 - startTime1; 

  // charge receive pin to HIGH, and conduct the experiment in reverse (HIGH -> LOW)
  pinMode(RECV_PIN, OUTPUT); 
  digitalWrite(RECV_PIN, HIGH); 
  delayMicroseconds(10);
  // config receive pin back to input
  pinMode(RECV_PIN, INPUT); 

  digitalWrite(SEND_PIN, LOW); 
  unsigned long startTime2 = micros(); 

  while (digitalRead(RECV_PIN) == HIGH) {}
  unsigned long endTime2 = micros(); 

  unsigned long measuredTime2 = endTime2 - startTime2; 

  return measuredTime2 + measuredTime1; 
}