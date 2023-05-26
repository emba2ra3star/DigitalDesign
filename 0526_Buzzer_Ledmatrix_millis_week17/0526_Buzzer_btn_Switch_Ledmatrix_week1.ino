#include "pitches.h"
#define BTN 2
//可變電阻是3
//8*8LED 接腳
#define ROW1 13
#define ROW2 12
#define ROW3 8
#define ROW4 A1
#define ROW5 7
#define ROW6 A4
#define ROW7 A5
#define ROW8 10
#define COL1 A0
#define COL2 4
#define COL3 A2
#define COL4 5
#define COL5 9
#define COL6 A3
#define COL7 11
#define COL8 6

//LED
const int row[] = {
  ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8
};
const int col[] = {
  COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8
};
byte scan[8][8] = {
  {1,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,1}
};
byte circle[8][8] = {
  {1,1,0,0,0,0,1,1},
  {1,0,1,1,1,1,0,1},
  {0,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,0},
  {1,0,1,1,1,1,0,1},
  {1,1,0,0,0,0,1,1}
};
byte T[8][8] = {
  {1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,1,1},
  {1,1,1,0,1,1,1,1},
  {1,1,1,0,1,1,1,1},
  {1,1,1,0,1,1,1,1},
  {1,1,1,0,1,1,1,1},
  {1,1,1,0,1,1,1,1},
  {1,1,1,1,1,1,1,1}
};
void showPattern(byte matrix[8][8]){
  for(byte i = 0; i < 8; i++){
    for(byte j = 0; j < 8; j++){
      digitalWrite(row[j], 1 - scan[i][j]);
      digitalWrite(col[j], 1 - matrix[i][j]);
      }
    for(byte j = 0; j < 8; j++){
    digitalWrite(row[j], HIGH);
    digitalWrite(col[j], LOW);
    }
  }
}


//buzzer
int melody1[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int melody2[] = {
  NOTE_G3, NOTE_E3, NOTE_E3, NOTE_F3, NOTE_D3, 0, NOTE_D3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_G3, NOTE_G3
};


int noteDurations1[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int noteDurations2[] = {
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
};

unsigned long currentT=0,previT=0,intervalT=0;




void setup() {
  for (byte i = 0; i <= sizeof(row); i++) {pinMode(row[i], OUTPUT);}
  for (byte i = 0; i <= sizeof(col); i++) {pinMode(col[i], OUTPUT);}
  pinMode(BTN, INPUT_PULLUP); 
  Serial.begin(9600);

}
byte pvS = 1, prS = 1, Number = 0;

void loop() {
  currentT = millis();  
  prS=digitalRead(BTN);
  if(prS == 1 && pvS == 0){
    Number++;
    if(Number > 1){
      Number = 0;  
    }
  }
  Serial.println(Number);

  //可變電阻
  int sensorV = analogRead(3);
  Serial.println(sensorV);
  delay(1); 

  //LED
  // if (Number == 0){
  //   showPattern(circle);
  // }
  // else if (Number == 1){
  //   showPattern(T);
  // }
 
  //蜂鳴器
  if(currentT - previT >= intervalT){
    intervalT = 1000;
    while(Number==0 && prS!=0) {
      for (int i = 0; i < 8; i++) {
        showPattern(circle);  //LED

        int rtime = 1000 / noteDurations1[i];
        tone(3, melody1[i], rtime);

        for (int i=0;i<rtime;i++) showPattern(circle);
        //delay(pauseBetweenNotes);
          
        noTone(3);
        prS=digitalRead(BTN);if(prS==0) break;  
      }  
    }
    while(Number==1 && prS!=0) {
      for (int i = 0; i < 13; i++) {
        showPattern(T); //LED
        int rtime = 1000 / noteDurations2[i];
        tone(3, melody2[i], rtime);

        for (int i=0;i<rtime;i++) showPattern(T);

        noTone(3);
        prS=digitalRead(BTN);if(prS==0) break;   
        
      }
    }  
    previT = currentT;
  }
  
  pvS=prS;
}
