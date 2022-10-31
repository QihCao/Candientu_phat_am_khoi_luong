
#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

#define DOUT 4
#define CLK 5
HX711 scale;
 
int rbutton = 8; // this button will be used to reset the scale to 0.
float weight;
int nang;
#define button 7//điều  khiển nút bấm khi muốn cân đọc khối lượng

int tg = 800;
int n,t,c,d;//hàng nghìn, trăm, chục, đơn vị
int tempn, tempt, tempc;//các biến tạm

float calibration_factor = 417361;//447238; //413361 //hệ số hiệu chỉnh loadcell 5kg
 
void setup() 
{
  pinMode(button,INPUT_PULLUP);
  delay(700);
  scale.begin(DOUT, CLK);
  Serial.begin(9600);
  pinMode(rbutton, INPUT_PULLUP); 
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
 
  long zero_factor = scale.read_average(); //Get a baseline reading
  
  lcd.init();                    
  lcd.backlight(); 
 
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial, true, false)) 
  {  
    while(true){
      delay(0);
    } 
   }
   myDFPlayer.volume(25); //thiết lập volume cho loa
   myDFPlayer.play(1);//phát bài nhạc khi khởi động cân
   delay(5000); 
}
  
void loop() 
{
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
 
  weight = scale.get_units(5);
  nang = weight * 1000; //đổi đơn vị kg sang g

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KHOI");
  lcd.setCursor(8, 0);
  lcd.print(weight);
  lcd.setCursor(14,0);
  lcd.print("KG");
  lcd.setCursor(0, 1);
  lcd.print("LUONG");
  lcd.setCursor(8, 1);
  lcd.print(nang);
  lcd.setCursor(14, 1);
  lcd.print("G");
  
 /* if(nang > 0 ){
  doc_can_nang();
  delay(1000);
  }*/
  delay(500);
 
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" KG");
  Serial.println();

   if(digitalRead(button)==LOW )//ấn nút thì kết quả sẽ được đọc
   {
   doc_can_nang();
   delay(1000);
  }
  else{
    
  }
  
}


void doc_can_nang(){
  //phân tích kết quả thành hàng nghìn, trăm, chục, đơn vị
  tempn = nang%1000;
  n = (nang - tempn)/1000;
  tempt = tempn%100;
  t = (tempn - tempt)/100;
  tempc = tempt%10;
  c = (tempt - tempc)/10;
  d = tempc%10;
  
  ketqua();
  delay(200);
  
  if(n > 0){
    doc_tung_so(n);
    nghin();
    if( t == 0){
      if(c==0 && d==0){
      }
      else{
      so_0();
      tram();
      if( c==0){
        linh();
      }
     }
   }
  }
  
  if(t > 0){
    doc_tung_so(t);
    tram();
    if( c == 0){
      if(d==0){
           
      }
      else{
      linh();
      }
    }   
 }

 if ( c > 0){
  if( c == 1){
   muoif();
  }
  else{
  doc_tung_so(c); 
  muoi();
  }
 }

 doc_tung_so(d);

 gam();
}

void so_0()
{myDFPlayer.play(2);delay(tg);  }

void so_1()
{myDFPlayer.play(3);delay(tg);  }

void so_2()
{myDFPlayer.play(4);delay(tg);  }

void so_3()
{myDFPlayer.play(5);delay(1000);  }

void so_4()
{myDFPlayer.play(6);delay(tg);  }

void so_5()
{myDFPlayer.play(7);delay(tg);  }

void so_6()
{myDFPlayer.play(8);delay(tg);  }

void so_7()
{myDFPlayer.play(9);delay(tg);  }

void so_8()
{myDFPlayer.play(10);delay(tg);  }

void so_9()
{myDFPlayer.play(11);delay(tg);  }

void muoif()
{myDFPlayer.play(12);delay(tg);  }

void muoi()
{myDFPlayer.play(13);delay(tg);  }

void gam()
{myDFPlayer.play(14);delay(tg);  }

void ketqua()
{myDFPlayer.play(15);delay(tg);  }

void nghin()
{myDFPlayer.play(16);delay(tg);  }

void tram()
{myDFPlayer.play(17);delay(tg);  }

void linh()
{myDFPlayer.play(18); delay(tg);}

void doc_tung_so(int x)
{
  switch(x){
    case 1 : x==1; so_1(); break;
    case 2 : x==2; so_2(); break;
    case 3 : x==3; so_3(); break;
    case 4 : x==4; so_4(); break;
    case 5 : x==5; so_5(); break;
    case 6 : x==6; so_6(); break;
    case 7 : x==7; so_7(); break;
    case 8 : x==8; so_8(); break;
    case 9 : x==9; so_9(); break;
  }
}
 


  
  
