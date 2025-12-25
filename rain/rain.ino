void setup() {
  for(int i = 3; i <= 12; i++) pinMode(i, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  randomSeed(analogRead(A3));
}

int cols[] = {A0, A1, A2};
int greenRows[] = {12, 11, 10, 9, 8};
int redRows[] = {7, 6, 5, 4, 3};
int drops[3] = {-1, -1, -1};  // current row for each column, -1 = no drop
int drop_colors[3] = {0, 0, 0};  // current row for each column, -1 = no drop

void loop() {
  // Spawn new drops randomly
  for(int c = 0; c < 3; c++) {
    if(drops[c] == -1 && random(0, 100) < 30) {
      drops[c] = 0;
      if (rand() % 2 == 0) {
        drop_colors[c] = 0;
      } else {
        drop_colors[c] = 1;
      }
    }
  }
  
  // Display current frame (scan fast)
  for(int scan = 0; scan < 50; scan++) {
    for(int r = 0; r < 5; r++) {
      for(int c = 0; c < 3; c++) {
        if(drops[c] == r) {
          if (drop_colors[c] == 0) {
            digitalWrite(greenRows[r], HIGH);
          } else {
            digitalWrite(redRows[r], HIGH);
          }
          digitalWrite(cols[c], LOW);
        }
      }
      delayMicroseconds(400);
      for(int i = 3; i <= 12; i++) digitalWrite(i, LOW);
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
    }
  }
  
  // Move drops down
  for(int c = 0; c < 3; c++) {
    if(drops[c] >= 0) {
      drops[c]++;
      if(drops[c] >= 5) drops[c] = -1;
    }
  }
}