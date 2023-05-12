#include "pitches.h"
#define BUTTON 6

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


void setup() {
  pinMode(6, INPUT_PULLUP);  
  Serial.begin(9600);
}

byte previousState=1, presentState=1, Number=0;
void loop() {
  presentState=digitalRead(BUTTON);
  if(presentState == 1 && previousState == 0){
    Number++;
    if(Number > 1){
      Number = 0;  
    }
  }
  Serial.println(Number);

  while(Number==0 && presentState!=0) {
    for (int i = 0; i < 8; i++) {
      int rtime = 1000 / noteDurations1[i];
      tone(8, melody1[i], rtime);

      int pauseBetweenNotes = rtime * 1.30;
      delay(pauseBetweenNotes);
      
      noTone(8);
      presentState=digitalRead(BUTTON);if(presentState==0) break;
    }
  }

  while(Number==1 && presentState!=0) {
    for (int i = 0; i < 13; i++) {
    
      int rtime = 1000 / noteDurations2[i];
      tone(8, melody2[i], rtime);

      int pauseBetweenNotes = rtime * 1.30;
      delay(pauseBetweenNotes);

      noTone(8);
      presentState=digitalRead(BUTTON);if(presentState==0)break;
    }
    
  }


  
  delay(500);
  previousState=presentState;
}
