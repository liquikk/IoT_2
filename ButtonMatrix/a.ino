const int row_count = 2;
const int column_count = 2;
const int key_d = 1;
const int key_h = 3;
const int key_up = 2;
const int key_0 = 0;
int rowPins [] = {A1, A0};
int columnPins [] = {2, 3};

int keyStatus [ row_count ][ column_count ] = { };
String keyMap[ row_count ][ column_count ] = { 
    { "1 row, 1 column", "1 row, 2 column" },
    { "2 row, 1 column", "2 row, 2 column" }
};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < row_count; i++) {
    for (int j = 0; j < column_count; j++) {
      keyStatus [ i ][ j ] = key_0;
    }
  }

  for (int i = 0; i < column_count; i++) {
    pinMode(columnPins [i], INPUT_PULLUP);
  }

  for (int i = 0; i < row_count; i++) {
    pinMode(rowPins [i], INPUT);
  }
}

void loop() {
  for (int i = 0; i < row_count; i++) {
    pinMode(rowPins [i], OUTPUT);
    digitalWrite(rowPins [i], LOW);
    for (int j = 0; j < column_count; j++) {
      int sensorVal = digitalRead(columnPins [j]);
        if (sensorVal == LOW && keyStatus[i][j] == key_0) {
          Serial.println(keyMap[i][j]);  
          Serial.println("key down");  
          keyStatus[i][j] = key_d;
        } if (sensorVal == LOW && keyStatus[i][j] == key_d) {
          Serial.println(keyMap[i][j]);  
          Serial.println("key holding");
          keyStatus[i][j] = key_h;
        } else if (sensorVal == HIGH && (keyStatus[i][j] == key_d || keyStatus[i][j] == key_h)) {
          keyStatus[i][j] = key_up;
          Serial.println(keyMap[i][j]);  
          Serial.println("key up");  
        } else if (sensorVal == HIGH && keyStatus[i][j] == key_up) {
          keyStatus[i][j] = key_0;
          Serial.println(keyMap[i][j]);  
          Serial.println("key free");  
        } 
    }
    pinMode(rowPins [i], INPUT);
  }
}