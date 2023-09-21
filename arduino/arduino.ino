void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  long min, sec;
  Serial.println("Enter a time to wait for example: <5:00>");
  while (1) {
    char serialInput[1000] = {0};
    while (Serial.available() == 0);
    //readString is slow
    Serial.readString().toCharArray(serialInput, 1000);

    int rc = sscanf(serialInput, "%ld:%ld", &min, &sec);
    Serial.print("Got: ");
    Serial.println(serialInput);
    if (rc != 2) {
      continue;
    }

    long waitTime = 1000 * (min*60 + sec);
    Serial.print("Milliseconds=");
    Serial.println(waitTime);

    long startTime = millis();
    long prevSecond = startTime;
    long counter = 0;

    while (1) {
      long curentTime = millis();
      if (curentTime - startTime >= waitTime || Serial.available()) break;
      if (curentTime - prevSecond > 1000) {
        Serial.print("Time Left=");
        Serial.println( (waitTime/1000) - ++counter);
        prevSecond = curentTime;
      }
    }

  }
}