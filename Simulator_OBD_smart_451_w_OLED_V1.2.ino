
// https://github.com/ThingPulse/esp8266-oled-ssd1306


#include <CAN.h>
#include <Wire.h>
#include "SSD1306.h"

SSD1306  display(0x3c, SDA, SCL);

//#####################
//DISPLAY

char data1[100];
char data2[100];
char data3[100];
char data4[100];
char data5[100];
char data6[100];
char data7[100];
char data8[100];


int rpm_display  ;
char gear_display ;
int speed_display ;
int water_display ;
float turbo_display ;
char* tempomat_display = " " ;
char* paddle_display  = " " ;
int time_h_display;
int time_m_display;
int tempomat_speed_display = 0;


//####################

int kmh ;
int id1;
int id2;


int rpm;
uint8_t id_rpm1;
uint8_t id_rpm2;

uint8_t id11 ;
uint8_t id22 ;


int gear;
uint8_t gear_id;


int stund;
int minu;
int seku;

uint8_t stund_id;
uint8_t minu_id;
uint8_t seku_id;


int temp ;
uint8_t temp_id;



int tempomat_mode ;
int tempomat_speed ;

uint8_t  tempomat_mode_id;
uint8_t  tempomat_speed_id;



int boost ;
uint8_t boost_id;







void setup()
{
      Serial.begin(115200);
      while (!Serial);
      pinMode(33, INPUT);
      pinMode(26, INPUT);
      pinMode(25, INPUT);

      Serial.println("CAN Sender");

      // start the CAN bus at 500 kbps
      if (!CAN.begin(500E3))
      {
            Serial.println("Starting CAN failed!");
            while (1);
      }



      display.init();
      display.flipScreenVertically();

      //init Screen
      display.setFont(ArialMT_Plain_16);
      display.setTextAlignment(TEXT_ALIGN_CENTER);
      display.drawString(64, 10, "CAN Simulator");
      display.setFont(ArialMT_Plain_10);
      display.drawString(64, 30, "by Petros T.");


      display.display();
      delay(3000);
      display.clear();




}

void loop()
{




      rpm = map(analogRead(34), 4095, 0, 0, 7000);
      kmh = map(analogRead(34), 4095, 0, 0, 200);
      gear = map(analogRead(34), 4095, 0, 1, 8);

      stund = map(analogRead(34), 4095, 0, 0, 24);
      minu = map(analogRead(34), 4095, 0, 0, 59);
      seku = map(analogRead(34), 4095, 0, 0, 59);

      temp = map(analogRead(34), 4095, 0, 0, 250);

      tempomat_mode = map(analogRead(34), 4095, 0, 0, 4);
      tempomat_speed = map(analogRead(34), 4095, 0, 0, 200);

      boost = map(analogRead(34), 4095, 0, 0, 255);









      //MAP DISPLAY





      rpm_display  = map(analogRead(34), 4095, 0, 0, 7000);
      //gear_display = 'N' ;
      speed_display  = map(analogRead(34), 4095, 0, 0, 200);
      water_display = map(analogRead(34), 4095, 0, -40, 210);
      turbo_display  = map(analogRead(34), 4095, 0, -100, 155);
      //tempomat_display = "SET" ;
      //paddle_display = "+ & -" ;
      time_h_display = map(analogRead(34), 4095, 0, 0, 24);
      time_m_display = map(analogRead(34), 4095, 0, 0, 59);
      tempomat_speed_display  = map(analogRead(34), 4095, 0, 0, 200);
















      //RPM ###########################


      id_rpm1 = rpm >> 8; // bit 2
      id_rpm2 = rpm % 256 ; // bit 3



      Serial.print("Rpm: ");
      Serial.print(rpm);
      Serial.print(" | ");

      CAN.beginPacket(0x212, 8);
      CAN.write(0x00); //0
      CAN.write(0x00); //1
      CAN.write(id_rpm1); //2 bit 1
      CAN.write(id_rpm2); //3 bit 2
      CAN.write(0x00); //4
      CAN.write(0x00); //5
      CAN.write(0x00); //6
      CAN.write(0x00); //7
      CAN.endPacket();

      //#############################




      //KMH #######################




      id1 = (kmh * 18) / 256;
      id2 = (kmh * 18) % 256;

      id11 = id1;
      id22 = id2;


      Serial.print("kmh: ");
      Serial.print(kmh);
      Serial.print(" | ");

      CAN.beginPacket(0x200, 8);
      CAN.write(0x00); //0
      CAN.write(0x00); //1
      CAN.write(id11); //2
      CAN.write(id22); //3
      CAN.write(0x00); //4
      CAN.write(0x00); //5
      CAN.write(0x00); //6
      CAN.write(0x00); //7
      CAN.endPacket();

      //#############################



      // GEAR ########################

      switch (gear)
      {
            case 1: gear_id = 0x4E;
                  Serial.print("Gang N");
                  gear_display = 'N' ;
                  // statements
                  break;
            case 2: gear_id = 0x31;
                  Serial.print("Gang 1");
                  gear_display = '1' ;
                  // statements
                  break;
            case 3: gear_id = 0x32;
                  Serial.print("Gang 2");
                  gear_display = '2' ;
                  // statements
                  break;
            case 4: gear_id = 0x33;
                  Serial.print("Gang 3");
                  gear_display = '3' ;
                  // statements
                  break;
            case 5: gear_id = 0x34;
                  Serial.print("Gang 4");
                  gear_display = '4' ;
                  // statements
                  break;
            case 6: gear_id = 0x35;
                  Serial.print("Gang 5");
                  gear_display = '5' ;
                  // statements
                  break;
            case 7: gear_id = 0x52;
                  Serial.print("Gang R");
                  gear_display = 'R' ;
                  // statements
                  break;
            case 8: gear_id = 0x01;
                  Serial.print("Gang A");
                  gear_display = 'A' ;
                  // statements
                  break;

            default:
                  // statements
                  break;
      }


      CAN.beginPacket(0x418, 8);
      CAN.write(gear_id); //0
      CAN.write(0x00); //1
      CAN.write(0x00); //2
      CAN.write(0x00); //3
      CAN.write(0x00); //4
      CAN.write(0x00); //5
      CAN.write(0x00); //6
      CAN.write(0x00); //7
      CAN.endPacket();
      Serial.print(" | ");



      //#############################




      // Uhrzeit #######################

      stund_id = stund;
      minu_id = minu;
      seku_id = seku;


      Serial.print("Uhrzeit: ");
      Serial.print(stund);
      Serial.print(":");
      Serial.print(minu);
      Serial.print(":");
      Serial.print(seku);
      Serial.print(" | ");



      CAN.beginPacket(0x783, 8);
      CAN.write(0x00); //0
      CAN.write(0x00); //1
      CAN.write(0x29); //2
      CAN.write(stund_id); //3
      CAN.write(minu_id); //4
      CAN.write(seku_id); //5
      CAN.write(0x00); //6
      CAN.write(0x00); //7
      CAN.endPacket();


      //########################






      //Collant Temp ##############

      temp_id = temp;

      Serial.print("Coolant Temp: ");
      Serial.print(temp);
      Serial.print(" | ");


      CAN.beginPacket(0x7e8, 8);
      CAN.write(0x03); //0
      CAN.write(0x41); //1
      CAN.write(0x05); //2
      CAN.write(temp_id); //3
      CAN.write(0x00); //4
      CAN.write(0x00); //5
      CAN.write(0x00); //6
      CAN.write(0x00); //7
      CAN.endPacket();






      //############################





      //Boost ############## not working atm

      boost_id = boost;

      Serial.print("Boost: ");
      Serial.print(boost);
      Serial.print(" | ");


      CAN.beginPacket(0x7e8, 8);
      CAN.write(0x03); //0
      CAN.write(0x41); //1
      CAN.write(0x0B); //2
      CAN.write(boost_id); //3
      CAN.write(0x00); //4
      CAN.write(0x00); //5
      CAN.write(0x00); //6
      CAN.write(0x00); //7
      CAN.endPacket();






      //############################


      //Paddles #############################


      if (digitalRead(25) == HIGH)

      {
            paddle_display = "+ & -" ;
            Serial.print("Paddle Booth | ");
            CAN.beginPacket(0x236, 8);
            CAN.write(0x06); //6
            CAN.endPacket();
      }


      if (digitalRead(26) == HIGH)

      {
            paddle_display = "+" ;
            Serial.print("Paddle + | ");
            CAN.beginPacket(0x236, 8);
            CAN.write(0x02); //4
            CAN.endPacket();
      }



      if (digitalRead(33) == HIGH)

      {
            paddle_display = "-" ;
            Serial.print("Paddle - | ");
            CAN.beginPacket(0x236, 8);
            CAN.write(0x04); //2
            CAN.endPacket();
      }




      else if ( digitalRead(25) == LOW && digitalRead(33) == LOW && digitalRead(26) == LOW)

      {
            paddle_display = " " ;
            Serial.print("Paddle unpressed | ");
            CAN.beginPacket(0x236, 8);
            CAN.write(0x00); //0
            CAN.endPacket();
      }










      //Tempomat #############################

      if (tempomat_mode == 0)
      {
            tempomat_display = "OFF" ;
            tempomat_mode_id = 0x00; //aus
      }

      if (tempomat_mode == 1)
      {
            tempomat_display = "ON" ;
            tempomat_mode_id = 0x20; //an
      }


      if (tempomat_mode == 2)
      {
            tempomat_display = "SET" ;
            tempomat_mode_id = 0x30; // Set
      }




      tempomat_speed_id = tempomat_speed;


      Serial.print("Tempomat Mode: ");
      Serial.print(tempomat_mode);
      Serial.print(" | ");


      Serial.print("Tempomat Mode: ");
      Serial.print(tempomat_speed);
      Serial.print(" | ");



      CAN.beginPacket(0x210, 8);
      CAN.write(0x00); //0
      CAN.write(0x00); //1
      CAN.write(0x00); //2
      CAN.write(0x00); //3
      CAN.write(tempomat_mode_id); //4
      CAN.write(0x00); //5
      CAN.write(0x00); //6
      CAN.write(tempomat_speed_id); //7
      CAN.endPacket();



      // #############################





      Serial.println(" ");



      //PRINT DISPLAY
      //##################################









      //CONSOLE OUTPUT
      sprintf(data1, "Rpm: %d", rpm_display);
      sprintf(data2, "Gear: %c", gear_display);
      sprintf(data3, "Km/h: %d", speed_display);
      sprintf(data4, "Water: %d C°", water_display);
      sprintf(data5, "Turbo: %.2f Bar", (turbo_display / 100));
      sprintf(data6, "Tempomat: %s Kmh: %d", tempomat_display, tempomat_speed_display);
      sprintf(data7, "Paddle: %s", paddle_display);
      sprintf(data8, "Time: %d:%d", time_h_display, time_m_display );





      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.setFont(ArialMT_Plain_10);

      //PRINT TO OLED
      display.clear();

      display.drawString(0, 0, data1 ); //RPM
      display.drawString(0, 10, data2); //gear
      display.drawString(0, 20, data3); //speed
      display.drawString(0, 30, data4); //water
      display.drawString(0, 40, data5); //turbo
      display.drawString(0, 50, data6); //tempomat
      display.drawString(64, 0, data7); // paddle
      display.drawString(64, 10, data8); // Time





      display.display();





























}
