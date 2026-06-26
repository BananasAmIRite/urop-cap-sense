#define ALPHA (1-0.013)



void setup() {
  Serial.begin(256000); 
  // put your setup code here, to run once:
// OC2B is hardwired to Digital Pin 3 on the Arduino UNO
  pinMode(3, OUTPUT);     
  // pinMode(A4, INPUT_PULLUP);  
  pinMode(A4, INPUT); 
  pinMode(A5, INPUT); 


  // // Clear current timer configurations
  // TCCR2A = 0;
  // TCCR2B = 0;

  // // Set Fast PWM Mode 7 (WGM22=1, WGM21=1, WGM20=1)
  // // Non-inverting PWM on Pin 3 (COM2B1=1)
  // TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  
  // // Set prescaler to 128 (CS22=1, CS21=0, CS20=1) and WGM22=1
  // TCCR2B = _BV(WGM22) | _BV(CS22) | _BV(CS20);

  // // Set TOP value for ~801.28 Hz
  // OCR2A = 155; 

  // // Set Compare Match for exactly 75% duty cycle
  // OCR2B = 116;

  //Set frequency to 4MHz, 25% duty cycle
  TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20);
  OCR2A = 3;
  OCR2B = 0;

  // analogReference(INTERNAL);         //change reference to 1.1V

  
}

// int previous_value = -1; 


const int NUM_FRAMES = 100;  // Change 'n' here. 15 is a great starting point for touch sensors.
int readings[NUM_FRAMES];   // The array to store our past readings
int readIndex = 0;          // Which slot in the array we are currently writing to
long total = 0;             // The running sum of all numbers in the array

// --- THE FILTER FUNCTION ---
int getSmoothedValue(int newReading) {
  // 1. Subtract the oldest reading from the total
  total = total - readings[readIndex];
  
  // 2. Overwrite the oldest reading with the new one
  readings[readIndex] = newReading;
  
  // 3. Add the new reading to the total
  total = total + readings[readIndex];
  
  // 4. Move to the next position in the array
  readIndex = readIndex + 1;
  
  // 5. If we reach the end of the array, loop back to the beginning
  if (readIndex >= NUM_FRAMES) {
    readIndex = 0;
  }
  
  // 6. Calculate and return the average
  return total / NUM_FRAMES;
}

int n = 0; 

// deviation accumulation
long deviationSum = 0;
int deviationCount = 0;
unsigned long windowStart = 0;
const int WINDOW_MS = 40;

void loop() {

  // int current_value = analogRead(A4); 

  // if (previous_value == -1) {
  //   previous_value = current_value; 
  // }

  // float filtered_value = (ALPHA * current_value) + ((1 - ALPHA) * previous_value);
  // // put your main code here, to run repeatedly:
  // Serial.println(filtered_value); 
  // // Serial.println(pulseIn(A4, HIGH)); 
  // // delayMicroseconds(1); 

  // previous_value = current_value;  

  // Read the raw, noisy voltage
  int raw = analogRead(A4); 
  analogRead(A4); 
  int raw2 = analogRead(A5); 
  
  // // Pass it through our filter
  // int avg = getSmoothedValue(raw); 

  // int deviation = abs(raw - avg);

  // deviationSum += deviation;
  // deviationCount++;

  // if (millis() - windowStart > WINDOW_MS) {

  //   int amplitude = deviationSum / deviationCount;

  //   Serial.println(amplitude);

  //   deviationSum = 0;
  //   deviationCount = 0;

  //   windowStart = millis();
  // }
  
  // // Print both to the Serial Plotter to see the difference!
  // // Serial.print("Raw:");
  // // Serial.print(rawValue);
  // // Serial.print(",");
  // // Serial.print("Smoothed:");
  // Serial.println(smoothedValue);
  // if (n == 1) {
    // Serial.print("0,");

    // Serial.print("Mn:0,");
    // Serial.print("Mx:30,");

    // --- 2. ACTUAL DATA ---
    // Serial.print("R:");
    float t = micros()/1000000.0;
    Serial.print(t, 6);
    Serial.print(",");
    Serial.print(raw);
      Serial.print(",");
    Serial.println(raw2);

    // Serial.print(",");
    // Serial.print(raw2);
    // Serial.print(",");
    // Serial.print("Touched:"); 
    // Serial.print(avg > 25); 
    // Serial.print("Deviation:");
    // Serial.print(deviation);
    // Serial.print(",");
    // Serial.print("a:");
    // Serial.println(avg); // Make sure the LAST item uses println()

  //   n = 0; 
  // }

  // n += 1; 

  // delayMicroseconds(10); 



// delay(50);

}


// #define ALPHA (1-0.013)

// const int RX_PIN = A4;

// // ===== BASELINE MOVING AVERAGE =====
// const int NUM_FRAMES = 100;
// int readings[NUM_FRAMES];
// int readIndex = 0;
// long total = 0;

// // ===== DEVIATION MOVING AVERAGE =====
// const int DEV_FRAMES = 100;
// int devReadings[DEV_FRAMES];
// int devIndex = 0;
// long devTotal = 0;

// int n = 0;

// // --- BASELINE FILTER ---
// int getSmoothedValue(int newReading) {

//   total -= readings[readIndex];
//   readings[readIndex] = newReading;
//   total += readings[readIndex];

//   readIndex++;
//   if (readIndex >= NUM_FRAMES) {
//     readIndex = 0;
//   }

//   return total / NUM_FRAMES;
// }

// // --- DEVIATION FILTER ---
// int getDeviationAverage(int newDeviation) {

//   devTotal -= devReadings[devIndex];
//   devReadings[devIndex] = newDeviation;
//   devTotal += devReadings[devIndex];

//   devIndex++;
//   if (devIndex >= DEV_FRAMES) {
//     devIndex = 0;
//   }

//   return devTotal / DEV_FRAMES;
// }

// void setup() {

//   Serial.begin(115200);

//   pinMode(3, OUTPUT);
//   pinMode(A4, INPUT);

  
//   // // // Clear current timer configurations
//   // TCCR2A = 0;
//   // TCCR2B = 0;

//   // // Set Fast PWM Mode 7 (WGM22=1, WGM21=1, WGM20=1)
//   // // Non-inverting PWM on Pin 3 (COM2B1=1)
//   // TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  
//   // // Set prescaler to 128 (CS22=1, CS21=0, CS20=1) and WGM22=1
//   // TCCR2B = _BV(WGM22) | _BV(CS22) | _BV(CS20);

//   // // Set TOP value for ~801.28 Hz
//   // OCR2A = 155; 

//   // // Set Compare Match for exactly 75% duty cycle
//   // OCR2B = 116;

//   //Set frequency to 4MHz, 25% duty cycle
//   // TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
//   // TCCR2B = _BV(WGM22) | _BV(CS20);
//   // OCR2A = 3;
//   // OCR2B = 0;

//   analogReference(INTERNAL);

// // void setup() {
// //   Serial.begin(115200); 
// //   // put your setup code here, to run once:
// // // OC2B is hardwired to Digital Pin 3 on the Arduino UNO
// //   pinMode(3, OUTPUT);     
// //   // pinMode(A4, INPUT_PULLUP);  
// //   pinMode(A4, INPUT); 


  
//   // initialize arrays
//   for (int i = 0; i < NUM_FRAMES; i++) readings[i] = 0;
//   for (int i = 0; i < DEV_FRAMES; i++) devReadings[i] = 0;
// }

// void loop() {

//   int raw = analogRead(RX_PIN);

//   int avg = getSmoothedValue(raw);

//   int deviation = abs(raw - avg);

//   int amplitude = getDeviationAverage(deviation);

//   // optional serial plotter output
//   if (n == 1) {

//     Serial.print("Min:0,");
//     Serial.print("Max:1023,");

//     Serial.print("Raw:");
//     Serial.print(raw);
//     Serial.print(",");

//     Serial.print("Deviation:");
//     Serial.print(deviation);
//     Serial.print(",");

//     Serial.print("Amplitude:");
//     Serial.print(amplitude);
//     Serial.print(",");

//     Serial.print("Smoothed:");
//     Serial.println(avg);

//     n = 0;
//   }

//   n++;

//   // delayMicroseconds(10);
// }