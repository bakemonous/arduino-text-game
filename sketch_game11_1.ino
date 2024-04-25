#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27,16,2);
/* 
   text game
             */
const int buttonPinYES = 2;
const int buttonPinNO = 8;
int buttonStateYES = 0;
int buttonStateNO = 0;
int buttonState = 0;

int rebirth = 1;//max 3(game loop)
int path=1;
int stage=0;
int checkpoint=1;
int id=0;
int access=1;

int n1=0;
int n2=0;
int n3=0;
int time1=0;

const int zummer1=6;
const int zummer2=5;
const int zummer3=4;
const int zummer4=11;
int CurrentZummer;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
const long interval1 = 5000;
const long interval2 = 1000; 
const long interval3 = 10000;

int NOTE_D5=587;
int NOTE_G5=784;
int NOTE_F5=698;
int NOTE_E5=659;
int NOTE_C5=523;
int NOTE_B4=494;
int NOTE_A4=440;
int NOTE_G4=392;
int NOTE_F4=349;
int NOTE_E4=330;
int NOTE_D4=294;
int thisNote;
int noteDurations =8;
unsigned long previousMillisMusic = 0;
int noteDurationMusic = 1000 / noteDurations;
const long intervalMusic = noteDurationMusic * 1.30; 
int melody[] = {
  0,//0 every 8 - 1 second
  0,//1
  0,//2
  0,//3
  NOTE_G4,//4
  NOTE_A4,//5
  NOTE_C5,//6
  NOTE_A4,//7
  NOTE_E5,NOTE_C5,NOTE_F4,//8,9,10-2 second
  0,//11
  0,//12
  NOTE_E5,NOTE_C5,NOTE_F4,//13,14,15
  0,//16
  0,//17
  NOTE_D5,NOTE_B4,NOTE_G4,//18,19,20
  0,//21
  0,//22-3 second
  0,//23
  0,//24
  0,//25
  NOTE_G4,//26
  NOTE_A4,//27
  NOTE_B4,//28
  NOTE_G4,//29
  NOTE_D5,NOTE_B4,NOTE_E4,//30,31,32-4 second
  0,//33
  0,//34
  NOTE_D5,NOTE_B4,NOTE_E4,//35,36,37
  0,//38
  0,//39
  NOTE_C5,NOTE_A4,NOTE_F4,//40,41,42
  0,//43
  0,//44-5 second
  NOTE_B4,//45
  NOTE_A4,//46
  0,//47
  NOTE_A4,//48
  NOTE_B4,//49
  NOTE_C5,//50
  NOTE_A4,//51
  NOTE_C5,NOTE_F4,//52,53,54-6 second
  0,//55
  0,//56
  0,//57
  NOTE_D5,//58
  0,//59
  NOTE_B4,NOTE_G4,NOTE_D4,//60,61,62
  0,//63
  0,//64-7 second
  0,//65
  NOTE_G4,//66
  0,//67
  0,//68
  0,//69
  NOTE_G4,//70
  0,//71
  NOTE_D5,NOTE_B4,NOTE_E4,//72,73,74-8 second
  0,//75
  0,//76
  0,//77
  NOTE_C5,NOTE_G4,NOTE_E4,//78,79,80
  0,//81
  0,//82
  0,//83
  NOTE_A4,//84-9 second
  0,//85
  0,//86
  0,//87
  NOTE_G4,//88
  NOTE_A4,//89
  NOTE_C5,//90
  NOTE_A4,//91
  NOTE_E5,NOTE_F4,//92,93-10 second
  0,//94
  0,//95
  NOTE_E5,NOTE_C5,NOTE_A4,NOTE_E4,//96,97,98,99
  0,//100
  0,//101
  NOTE_D5,NOTE_B4,NOTE_G4,//102,103,104
  0,//105
  0,//106-11 second
  0,//107
  0,//108
  0,//109
  NOTE_G4,//110
  NOTE_A4,//111
  NOTE_B4,//112
  NOTE_G4,//113
  NOTE_D5,NOTE_G5,//114,115-12 second
  0,//116
  0,//117
  0,//118
  NOTE_B4,//119
  0,//120
  NOTE_C5,NOTE_A4,NOTE_E4,//121,122,123
  0,//124
  0,//125-13 second
  NOTE_B4,//126
  NOTE_A4,//127
  0,//128
  NOTE_A4,//129
  NOTE_B4,//130
  NOTE_C5,//131
  NOTE_A4,//132
  NOTE_C5,NOTE_E4,//133,134-14 second
  0,//135
  0,//136
  0,//137
  NOTE_D5,//138
  0,//139
  NOTE_B4,NOTE_G4,NOTE_E4,//140,141,142
  0,//143
  0,//144-15 second
  NOTE_A4,//145
  NOTE_G4,//146
  0,//147
  0,//148
  0,//149
  NOTE_G4,//150
  0,//151
  NOTE_D5,NOTE_B4,NOTE_F4,//152,153,154-16 second
  0,//155
  0,//156
  0,//157
  NOTE_C5,NOTE_A4,NOTE_F4,//158,159,160
  }; 
  
void setup() {
   Serial.begin(9600);
   LCD.init();                      
   LCD.backlight(); 
   pinMode(buttonPinYES, INPUT_PULLUP);
   pinMode(buttonPinNO, INPUT_PULLUP);
}


void loop() {
      int buttonStateYES = digitalRead(buttonPinYES);
   int buttonStateNO = digitalRead(buttonPinNO);
   if ( buttonStateYES==LOW and buttonStateNO==LOW){
    buttonState=3;
    if (buttonState==3){
     n1=n1+1;
     n2=0;
     n3=0;
     buttonState=0;
    }
      if (n1>5){
           buttonState=3;
      }
    previousMillis2 = 1;
   } else if (buttonStateYES==LOW) {
     buttonState=2;
         if (buttonState==2){
     n2=n2+1;
     n1=0;
     n3=0;
     buttonState=0;
         }
      if (n2>5){
           buttonState=2;
      }
         previousMillis2 = 1;
   } else if (buttonStateNO==LOW) {
     buttonState=1;
         if (buttonState==1){
     n3=n3+1;
     n2=0;
     n1=0;
     buttonState=0;
         }
      if (n3>5){
           buttonState=1;
      }
         previousMillis2 = 1;
   } else{
   }
   Serial.println(buttonState);
      if(millis() - previousMillisMusic > intervalMusic) {
      previousMillisMusic = millis(); 
      music();
   }
      if(previousMillis3==0 and stage==3){
         previousMillis3 = millis();
   }
       if(millis() - previousMillis3 > interval3 and stage==3){
        SecondQuestion();
    }
       if (path==10 or path==11 or path==12) {
        stage=3;
        buttonState=0;
        }
      if( millis() - previousMillis2 > interval2  and stage==2 and previousMillis2!=0) {
      FirstAnswer1();
   }
                 if(previousMillis2==1 and stage==2 and buttonState!=0 ){
         previousMillis2 = millis();
   }
      if(previousMillis1==0 and stage==1){
         previousMillis1 = millis();
   }
   if(millis() - previousMillis1 > interval1 and stage==1) {
      firstQuestion(); 
   }
   if(stage==0){
       Introduction();
   }
   
}
void Introduction (){
    LCD.setCursor(0,0);
    LCD.print ("HI, I answering");//в распоряжении не 8, а 16 символов на строку!!!
    LCD.setCursor(0,1);
    LCD.print ("      you      ");
    stage=1;
    buttonState=0;
}
void firstQuestion(){   
  if (rebirth==1 and stage==1 and path==1){
    /*if (time1==0){
    LCD.setCursor(0,0);
    LCD.print ("HI, I answering");//в распоряжении не 8, а 16 символов на строку!!!
    LCD.setCursor(0,1);
    LCD.print ("      you      ");
    }*/
    if (time1==0){
    LCD.setCursor(0,0);
    LCD.print ("nine + ten = ? ");//"nine + ten = ? "
    LCD.setCursor(0,1);
    LCD.print ("19-yes or 21-no");//"19-yes or 21-no"
    stage =2;
    }
    buttonState=0;
  }
}
void FirstAnswer1(){
  if (rebirth==1 and stage==2 and path==1){
      if (buttonState==3){
        LCD.setCursor(0,0);
        LCD.print ("       EH?     ");
        LCD.setCursor(0,1);
        LCD.print ("     NEXT...   ");
        path=10;
      }
      else if (buttonState==2){
        LCD.setCursor(0,0);
        LCD.print ("       NO      ");
        LCD.setCursor(0,1);
        LCD.print ("      NEXT     ");
        path=11;
      }
      else if (buttonState==1){
        LCD.setCursor(0,0);
        LCD.print ("      GUD      ");
        LCD.setCursor(0,1);
        LCD.print ("      NEXT     ");
        path=12;
      }
   }
   buttonState=0;
}
void SecondQuestion(){
    if (stage==3 ){
        LCD.setCursor(0,0);
        LCD.print ("  okok, do you  ");
        LCD.setCursor(0,1);
        LCD.print ("  like abidas?  ");
        buttonState=0;
    }
}
void music(){
    CurrentZummer=0;
    if (thisNote==161){
      thisNote=0;
    }
    int noteDuration = 1000 / noteDurations;
    if (thisNote==9 or thisNote==14 or thisNote==19 or thisNote==31 or thisNote==36 or thisNote==41 or thisNote==53 or thisNote==61 or 
    thisNote==73 or thisNote==79 or thisNote==93 or thisNote==97 or thisNote==103 or thisNote==115 or thisNote==122 or thisNote==134 or 
    thisNote==141 or thisNote==153 or thisNote==159){
      tone(zummer2, melody[thisNote], noteDuration);
      CurrentZummer=2;
    }
    else if (thisNote==10 or thisNote==15 or thisNote==20 or thisNote==32 or thisNote==37 or thisNote==42 or thisNote==54 or thisNote==62 or
    thisNote==74 or thisNote==80 or thisNote==98 or thisNote==104 or thisNote==123 or thisNote==134 or thisNote==142 or thisNote==154 or
    thisNote==160){
      tone(zummer3, melody[thisNote], noteDuration);
      CurrentZummer=3;
    }
    else if (thisNote==99){
      tone(zummer4, melody[thisNote], noteDuration);
      CurrentZummer=4;
    }
    else{
      tone(zummer1, melody[thisNote], noteDuration);
      CurrentZummer=1;
    }
    thisNote++;
  //  Serial.print("thisNote - " + thisNote +", zummer is - " + CurrentZummer + ".";
  }
