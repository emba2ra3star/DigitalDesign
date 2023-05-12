#include "pitches.h"

int melody[] = {
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4
};


int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4
};

void setup() {

}

void loop() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    int noteDuration = 1000 / noteDurations[i];
    tone(10, melody[i], noteDuration);
    if(melody[i]==NOTE_C3) digitalWrite(2, HIGH);
    else if(melody[i]==NOTE_D3) digitalWrite(3, HIGH);
    else if(melody[i]==NOTE_E3) digitalWrite(4, HIGH);
    else if(melody[i]==NOTE_F3) digitalWrite(5, HIGH);
    else if(melody[i]==NOTE_G3) digitalWrite(6, HIGH);
    else if(melody[i]==NOTE_A3) digitalWrite(7, HIGH);
    else if(melody[i]==NOTE_B3) digitalWrite(8, HIGH);
    else if(melody[i]==NOTE_C4) digitalWrite(9, HIGH);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(10);
  }
  delay(1000);
}



