int incomingByte = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.println("Hello World");
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 55){
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
    }
    Serial.print("I recieved: ");
    Serial.println(incomingByte, DEC);
  }
}

