void setup() {
  for(int i = 3; i <= 12; i++) pinMode(i, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
}

int cols[] = {A0, A1, A2};
int greenRows[] = {12, 11, 10, 9, 8};
int redRows[] = {7, 6, 5, 4, 3};

// Snake path around perimeter
int path[][2] = {
  {0,0}, {0,1}, {0,2}, {1,2}, {2,2}, {3,2}, {4,2},
  {4,1}, {4,0}, {3,0}, {2,0}, {1,0}
};
int pathLen = 12;
int headPos = 0;
int tailLen = 4;

void loop() {
  // Display snake (scan rapidly)
  for(int scan = 0; scan < 40; scan++) {
    for(int i = 0; i < tailLen; i++) {
      int pos = (headPos - i + pathLen) % pathLen;
      int r = path[pos][0];
      int c = path[pos][1];
      
      if(i == 0) {  // head is red
        digitalWrite(redRows[r], HIGH);
      } else {  // body is green
        digitalWrite(greenRows[r], HIGH);
      }
      digitalWrite(cols[c], LOW);
      delayMicroseconds(300);
      
      for(int j = 3; j <= 12; j++) digitalWrite(j, LOW);
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
    }
  }
  
  headPos = (headPos + 1) % pathLen;
}