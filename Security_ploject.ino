
int doorButton = 7;
int resetButton = 8;
int redLED = 2;
int greenLED = 3;
int buzzer = 6;
int ldrPin = A0;

bool alarmActive = false;

void setup() {
  pinMode(doorButton, INPUT);
  pinMode(resetButton, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  Serial.println("MONITORING ACTIVE");
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  
  if (ldrValue > 600 && !alarmActive) {
    Serial.println("NIGHT MODE ON");
    digitalWrite(greenLED, HIGH);
    delay(500);
    digitalWrite(greenLED, LOW);
    delay(500);
  } 
  else if (!alarmActive) {
    digitalWrite(greenLED, HIGH);
  }

  if (digitalRead(doorButton) == HIGH && !alarmActive) {
    alarmActive = true;
    Serial.println("INTRUDER DETECTED");

    for (int i = 0; i < 10; i++) {
      digitalWrite(redLED, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(redLED, LOW);
      digitalWrite(buzzer, LOW);
      delay(200);
    }

    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenLED, LOW);
  }

  if (digitalRead(resetButton) == HIGH) {
    alarmActive = false;

    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenLED, HIGH);

    Serial.println("SYSTEM RESET");
    Serial.println("MONITORING ACTIVE");

    delay(500);
  }
}
