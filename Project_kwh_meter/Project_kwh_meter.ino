#include "EmonLib.h"
//#include <LiquidCrystal_I2C.h>

EnergyMonitor emon1;
//LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup()
{  
  Serial.begin(9600);
//  lcd.begin();
//  lcd.backlight();
  
  emon1.voltage(1, 234.26, 1.7); //angka 234,.26 dan 1.7 dapat dirubah. namun lebih mudah untuk mengatur variable resistor  
  emon1.current(0, 35);         // nilai 35 bisa diubah sesuai kalibrasi, samakan dengan ampere meter hingga output sama
}

void loop()
{
//semua perhitungan dipanggil disini dengan variable (Irms, supplyVoltage, Daya, Tarif)
  emon1.calcVI(20,2000);         
  double Irms = emon1.calcIrms(1480);       
  double supplyVoltage  = emon1.Vrms;   
  double Daya = Irms*supplyVoltage;
  double kWh = (Daya/1000);         //nilai kWh = W/1000 nilai konsumsi daya dalam 1 jam. jika konsumsi 3 maka tinggal dikalikan 3 saja
  double Tarif = kWh*1444.70;      //nilai 1444.70 adalah nilai tarif perkwh sesuaikan dengan update harga pln (dibulatkan dalam 1 jam)

if (Irms <=0.05){
  Irms = 0.00;
}
else {
  Irms = emon1.calcIrms(1480);
}
  //menampilkan di serial monitor
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print(supplyVoltage,1);
  Serial.println("Tegangan : ");
   Serial.print(supplyVoltage,1);
     Serial.print("V");
//  lcd.print(" V | ");
//  lcd.print(Irms,2);
  Serial.println("Arus : ");
   Serial.print(Irms,2);
    Serial.print("A");
//  lcd.print(" A");
//  lcd.setCursor(0,1);
//  lcd.print(Daya,2);
  Serial.println("Daya : ");
    Serial.print(Daya,2);
      Serial.print("Watt");
//  lcd.print("W | ");
//  lcd.print("Rp.");
  Serial.println("Tarif : Rp.");
    Serial.print(Tarif);
//  lcd.print(Tarif);
  delay(1000);
//  lcd.setCursor(0,0);
//  lcd.print("Pemakaian :");
//  lcd.setCursor(0,1);
//  lcd.print(kWh);
//  delay (1000);
}
