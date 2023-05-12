#include "pitches.h"

#define BOTTON 2
#define BUZZER 13

struct song {
  int melody[30];
  int noteDurations[30];
  int len;
};


struct song songs[2];
int LED[4];

void setup() {

songs[0].melody[0] = NOTE_C6;
songs[0].melody[1] = NOTE_A5;
songs[0].melody[2] = NOTE_C6;
songs[0].melody[3] = NOTE_A5;
songs[0].melody[4] = NOTE_C6;
songs[0].melody[5] = NOTE_A5;
songs[0].melody[6] = NOTE_C6;
songs[0].melody[7] = NOTE_G5;
songs[0].melody[8] = NOTE_E5;
songs[0].melody[9] = NOTE_E5;

songs[0].noteDurations[0] = 4;
songs[0].noteDurations[1] = 4;
songs[0].noteDurations[2] = 4;
songs[0].noteDurations[3] = 4;
songs[0].noteDurations[4] = 8;
songs[0].noteDurations[5] = 8;
songs[0].noteDurations[6] = 8;
songs[0].noteDurations[7] = 8;
songs[0].noteDurations[8] = 8;
songs[0].noteDurations[9] = 8;

songs[0].len = 10;

songs[1].melody[0] = NOTE_C6;
songs[1].melody[1] = NOTE_A5;
songs[1].melody[2] = NOTE_C6;
songs[1].melody[3] = NOTE_E6;
songs[1].melody[4] = NOTE_E6;
songs[1].melody[5] = 0;
songs[1].melody[6] = NOTE_G6;
songs[1].melody[7] = NOTE_E6;
songs[1].melody[8] = NOTE_C6;
songs[1].melody[9] = NOTE_A5;
songs[1].melody[10] = NOTE_A5;

songs[1].noteDurations[0] = 4;
songs[1].noteDurations[1] = 4;
songs[1].noteDurations[2] = 8;
songs[1].noteDurations[3] = 8;
songs[1].noteDurations[4] = 4;
songs[1].noteDurations[5] = 16;
songs[1].noteDurations[6] = 8;
songs[1].noteDurations[7] = 8;
songs[1].noteDurations[8] = 4;
songs[1].noteDurations[9] = 8;
songs[1].noteDurations[10] = 8;

songs[1].len = 11;

  pinMode(BOTTON, INPUT_PULLUP);

  LED[0] = 3;
  LED[1] = 5;
  LED[2] = 7;
  LED[3] = 9;
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
  
}

byte preState = 1, nowState = 1, trackID = 0;

void loop() {

  checkBotton();
  
  for (int thisNote = 0; thisNote < songs[trackID].len; thisNote++) {

    checkBotton();
    int noteDuration = 1000 / songs[trackID].noteDurations[thisNote];
    tone(BUZZER, songs[trackID].melody[thisNote], noteDuration);

    int id = 0;
    if(songs[trackID].melody[thisNote] == NOTE_A5) {id = 0;};
    if(songs[trackID].melody[thisNote] == NOTE_C6) {id = 1;};
    if(songs[trackID].melody[thisNote] == NOTE_E5) {id = 2;};
    if(songs[trackID].melody[thisNote] == NOTE_G5) {id = 3;};
    digitalWrite(LED[id],1);
    
    checkBotton();
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER);
    digitalWrite(LED[id],0);
  }
  


  for (int i = 0; i < 100; i++) {
    checkBotton();
    delay(10);
  }
  
}

void checkBotton() {
  nowState = digitalRead(BOTTON);

  if(nowState == 0 && preState == 1) {
    trackID ++;
    if(trackID == 2) {
      trackID = 0;
    }
  }
  preState = nowState;
}
