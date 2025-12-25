void setup() {
  for(int i = 3; i <= 12; i++) pinMode(i, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  pinMode(13, INPUT_PULLUP);

}

int cols[] = {A0, A1, A2};
int greenRows[] = {12, 11, 10, 9, 8};
int redRows[] = {7, 6, 5, 4, 3};

// 5x3 letter patterns: 1=red, 2=green, 3=orange, 0=off
byte patterns[][5][3] = {
  // RED
  {{1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}},
  // GREEN
  {{2,2,2}, {2,2,2}, {2,2,2}, {2,2,2}, {2,2,2}},
};

void displayPattern(byte pattern[5][3]) {
  for(int frame = 0; frame < 50; frame++) {
    for(int c = 0; c < 3; c++) {
      for(int r = 0; r < 5; r++) {
        if(pattern[r][c] == 1 || pattern[r][c] == 3) digitalWrite(redRows[r], HIGH);
        if(pattern[r][c] == 2 || pattern[r][c] == 3) digitalWrite(greenRows[r], HIGH);
        digitalWrite(cols[c], LOW);
      }
      delayMicroseconds(400);
      for(int i = 3; i <= 12; i++) digitalWrite(i, LOW);
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
    }
  }
}

bool is_red = true;

void loop() {
  if (is_red) {
    displayPattern(patterns[0]);
  } else {
    displayPattern(patterns[1]);
  }

  if (digitalRead(13) == LOW) {
    is_red = !is_red;
    delay(1000);
  }
  delay(50);
}