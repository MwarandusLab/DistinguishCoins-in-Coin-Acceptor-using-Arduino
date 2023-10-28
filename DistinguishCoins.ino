const int coinPin = 9;  // Digital pin to which the coin acceptor is connected
unsigned long lastPulseTime = 0;
unsigned long pulseWidth = 0;

void setup() {
  Serial.begin(9600);
  pinMode(coinPin, INPUT_PULLUP);
}

void loop() {
  // Read the coin acceptor's output
  int coinState = digitalRead(coinPin);
  unsigned long currentTime = millis();

  // Check for a falling edge (coin insertion)
  if (coinState == LOW && currentTime - lastPulseTime > 50) {
    pulseWidth = 0; // Reset pulse width

    // Measure the pulse width
    while (coinState == LOW) {
      currentTime = millis();
      coinState = digitalRead(coinPin);
    }

    pulseWidth = currentTime - lastPulseTime;

    // Distinguish between coin types based on pulse width
    if (pulseWidth < 1000) {
      Serial.println("Coin type A detected."); // Coin type with a pulse width closer to 200 ms
    } else {
      Serial.println("Coin type B detected."); // Coin type with a pulse width above 2000 ms
    }

    lastPulseTime = currentTime;
  }

  // Add a small delay to avoid false detections
  delay(10);
}
