void setup() {
  for(int i = 3; i <= 12; i++) pinMode(i, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
}

int cols[] = {A0, A1, A2};
int greenRows[] = {12, 11, 10, 9, 8};
int redRows[] = {7, 6, 5, 4, 3};

// 5x3 letter patterns: 1=red, 2=green, 0=off
byte letters[][5][3] = {
  // S
  {{1,1,1}, {1,0,0}, {1,1,1}, {0,0,1}, {1,1,1}},
  // O
  {{2,2,2}, {2,0,2}, {2,0,2}, {2,0,2}, {2,2,2}},
  // C
  {{1,1,1}, {1,0,0}, {1,0,0}, {1,0,0}, {1,1,1}},
  // R
  {{2,2,2}, {2,0,2}, {2,2,0}, {2,0,2}, {2,0,2}},
  // A
  {{1,1,1}, {1,0,1}, {1,1,1}, {1,0,1}, {1,0,1}},
  // T
  {{2,2,2}, {0,2,0}, {0,2,0}, {0,2,0}, {0,2,0}},
  // I
  {{1,1,1}, {0,1,0}, {0,1,0}, {0,1,0}, {1,1,1}},
  // C
  {{2,2,2}, {2,0,0}, {2,0,0}, {2,0,0}, {2,2,2}},
  // A
  {{1,1,1}, {1,0,1}, {1,1,1}, {1,0,1}, {1,0,1}}
};

void displayLetter(byte letter[5][3]) {
  for(int frame = 0; frame < 50; frame++) {
    for(int c = 0; c < 3; c++) {
      for(int r = 0; r < 5; r++) {
        if(letter[r][c] == 1) digitalWrite(redRows[r], HIGH);
        if(letter[r][c] == 2) digitalWrite(greenRows[r], HIGH);
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

void loop() {
  for(int i = 0; i < 9; i++) {
    for (int j = 0; j < 20; j++) {
      displayLetter(letters[i]);
      delay(5);
    }
  }
}