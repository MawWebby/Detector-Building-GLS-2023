// MAIN INITIALIZATION CODE
// School Information to Identify Device
String schoolname = "Greenwood Laboratory School";
String schoolteamname = "Bluejays";

float sensoroffset = 10;              // Voltage Offset of Analog Readings
signed long int timemeasurement = 0;  // Variable to Differentiate Different Readings

// Initialize Digital Pins to Use for LEDs
int redledpin = 7;
int blueledpin = 8;
int greenledpin = 9;

// Min-Max of LED Range to Turn On
float redledmin = 30;      // Red LED Minimum Weight to Turn On
float redledmax = 200;     // Red LED Maximum Weight to Turn Off
float blueledmin = 200;    // Blue LED Minimum Weight to Turn On
float blueledmax = 600;    // Blue LED Maximum Weight to Turn Off
float greenledmin = 600;   // Green LED Minimum Weight to Turn On
float greenledmax = 1000;  // Green LED Maximum Weight to Turn Off


// LOOP TO RUN AT DEVICE START
void setup() {
  Serial.begin(115200);          // Set the Serial baudrate to 115200
  pinMode(PIN_A0, INPUT);        // Analog Voltage Input
  pinMode(redledpin, OUTPUT);    // Red LED Pin
  pinMode(blueledpin, OUTPUT);   // Blue LED Pin
  pinMode(greenledpin, OUTPUT);  // Green LED Pin

  // Print School Identification Information
  Serial.println(schoolname);
  Serial.println(schoolteamname);
}

// LOOP TO REPEAT
void loop() {

  delay(10);
  float raw0 = analogRead(PIN_A0);  // Take 1st Measurement
  delay(10);                        // Wait 10ms
  float raw1 = analogRead(PIN_A0);  // Take 2st Measurement
  delay(10);                        // Wait 10ms
  float raw2 = analogRead(PIN_A0);  // Take 3st Measurement
  delay(10);                        // Wait 10ms
  float raw3 = analogRead(PIN_A0);  // Take 4st Measurement
  delay(10);                        // Wait 10ms
  float raw4 = analogRead(PIN_A0);  // Take 5st Measurement
  delay(10);                        // Wait 10ms
  float raw5 = analogRead(PIN_A0);  // Take 6st Measurement
  delay(10);                        // Wait 10ms
  float raw6 = analogRead(PIN_A0);  // Take 7st Measurement
  delay(10);                        // Wait 10ms
  float totalraw = raw0 + raw1 + raw2 + raw3 + raw4 + raw5 + raw6;
  // Add all 7 Measurements to one variable
  delay(10);                                                                                    // Wait 10ms
  float averageraw = totalraw / 7;                                                              // Find the Average of the 7 Variables
  float voltage = averageraw / 200;                                                             // Divide the 5mV Increments by 200 to get Voltage
  delay(10);                                                                                    // Wait 10ms
  float usedforcalculation1 = averageraw - 440;                                                 // Add X-Offset to the Calculation
  delay(10);                                                                                    // Wait 10ms
  float usedforcalculation2 = usedforcalculation1 * usedforcalculation1 * usedforcalculation1;  // Cube the raw input of voltage for First part of equation.
  float weight = usedforcalculation2 / 170000;                                                  // Divide by 170000 for equation
  if (weight < 0) {
    weight = 0;  // If result is less than 0, change variable to be equal to 0.
  }

  timemeasurement = timemeasurement + 1;  // Increase Measurement Number
  Serial.println();                       // Print Empty Line to Separate Measurements

  if (weight > redledmin) {
    if (weight < redledmax) {
      digitalWrite(redledpin, HIGH);  // Turn Red LED ON
    } else {
      digitalWrite(redledpin, LOW);  // Turn Red LED OFF
    }
  } else {
    digitalWrite(redledpin, LOW);  // Turn Red LED OFF
  }

  if (weight > blueledmin) {
    if (weight < blueledmax) {
      digitalWrite(blueledpin, HIGH);  // Turn Blue LED ON
    } else {
      digitalWrite(blueledpin, LOW);  // Turn Blue LED OFF
    }
  } else {
    digitalWrite(blueledpin, LOW);  // Turn Blue LED OFF
  }

  if (weight > greenledmin) {
    if (weight < greenledmax) {
      digitalWrite(greenledpin, HIGH);  // Turn Green LED ON
    } else {
      digitalWrite(greenledpin, LOW);  // Turn Green LED OFF
    }
  } else {
    digitalWrite(greenledpin, LOW);  // Turn Green LED OFF
  }
  Serial.print("Time Number = ");
  Serial.print(timemeasurement);  // Print Time Measurement
  Serial.print("; Voltage = ");   // Print Label
  Serial.print(voltage);          // Print Voltage Output
  Serial.print(" mV; Mass = ");   // Print Label for Voltage
  Serial.print(weight);           // Print Weight in Grams
  Serial.println(" grams");       // Print Label for Grams
  delay(10);
}
