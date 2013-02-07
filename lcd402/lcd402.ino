#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte smileyp, wobblep;
byte xp=0;
byte smiley[3][8] = {
{
  B00000,
  B10001,
  B00000,
  B00000,
  B00000,
  B01110,
  B10001,
},
{
  B00000,
  B10001,
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
},
{
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
},
};

byte wobble[2][8] = {
{
  B00000,
  B00000,
  B00000,
  B01000,
  B10101,
  B00010,
  B00000,
},
{
  B00000,
  B00000,
  B00000,
  B00010,
  B10101,
  B01000,
  B00000,
},
};

byte box[4][8] = {
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
},
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
},
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
},
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
},
};

void setPixel(int x, int y) {
  int p = 0;
  x = (x+xp)%11;
  if(x<=5 and y<=7) {
    p = 0;
  } else if (x>5 and y<=7) {
    p = 1;
    x -= 6;
  } else if (x<=5 and y<=15) {
    p = 2;
    y -= 8;
  } else if (x<=10 and y<=15) {
    p = 3;
    x -= 6;
    y -= 8;
  } else {
    return;
  }
  box[p][y] |= 1<<(4-x);
}

void line(int x0, int y0, int x1, int y1) {
 
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    setPixel(x0,y0);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(40, 2);
  lcd.clear();
  lcd.setCursor(0,0);
/*  lcd.print("Thanks Hacklab Turku! ");
  lcd.write((byte)2);
  lcd.write((byte)3);
  lcd.setCursor(0,1);
  lcd.print("Whee!                 ");
  lcd.write((byte)4);
  lcd.write((byte)5);

  lcd.write(" ");
  lcd.write((byte)1);
  lcd.write("o");
  lcd.write((byte)1);
  lcd.write(" ");
  lcd.write((byte)0);

  lcd.createChar(0, smiley[0]);
  lcd.setCursor(0, 1);
*/
  for(int i=0;i<40;i++) {
    int p = i%2;
    if(p==0) {
      lcd.write((byte)2);
    } else if(p==1) {
      lcd.write((byte)3);
    } else if(p==2) {
      lcd.write(" ");
    }
  }
  for(int i=0;i<40;i++) {
    int p = i%2;
    if(p==0) {
      lcd.write((byte)4);
    } else if(p==1) {
      lcd.write((byte)5);
    } else if(p==2) {
      lcd.write(" ");
    }
  }
}

float t=0.0;

void star() {
  memset(box,0,sizeof(box));
  int x0 = (cos(t)+1.0)*5;
  int y0 = (sin(t)+1.0)*5+3;
  int x1 = (cos(t+3.14)+1.0)*5;
  int y1 = (sin(t+3.14)+1.0)*5+3;
  line(x0,y0,x1,y1);

   x0 = (cos(t+3.14/2.0)+1.0)*5;
   y0 = (sin(t+3.14/2.0)+1.0)*5+3;
   x1 = (cos(t+3.14/2.0+3.14)+1.0)*5;
   y1 = (sin(t+3.14/2.0+3.14)+1.0)*5+3;
  line(x0,y0,x1,y1);

  t += 0.2;
  xp+=1;
  if(xp>11) xp=0;
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
//  lcd.autoscroll();
//  lcd.print(millis());

  delay(20);
  lcd.createChar(0, smiley[smileyp++]);
  lcd.createChar(1, wobble[wobblep++]);
  if (smileyp >= (sizeof(smiley)/8) )
    smileyp=0;
  if (wobblep >= (sizeof(wobble)/8) )
    wobblep=0;
  
//  line(10,0,0,15);
  star();

  lcd.createChar(2,box[0]);
  lcd.createChar(3,box[1]);
  lcd.createChar(4,box[2]);
  lcd.createChar(5,box[3]);
}
