#include <Servo.h>  // Servo kütüphanesini projemize ekledik.
Servo servoM;

int konum = 0;

#define s0 8 //Bağladığımız pinlere göre tanımlamalarımızı yapıyoruz
#define s1 9
#define s2 10
#define s3 11
#define sensorOut 12

#define buzzerpin 2
#define maviled 13
#define kirmiziled 7

int deger = 30;

char renk1;
char renk2;
int durum;

int K, Y, M = 0; //3 ana renk için değişken tanımlıyoruz

int K2, Y2, M2 = 0;

void setup() {

  Serial.println("sistem basladi");

  pinMode(s0, OUTPUT); //S0, S1, S2 ve S3 pinlerini OUTPUT olarak tanımlıyoruz
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorOut, INPUT); //OUT pinini INPUT olarak tanımlıyoruz
  pinMode(buzzerpin, OUTPUT);
  pinMode(maviled, OUTPUT);
  pinMode(kirmiziled, OUTPUT);
  servoM.attach(4);

  digitalWrite(s1, LOW); //Frekans ölçeğimizi %20 olarak tanımlıyoruz
  digitalWrite(s0, HIGH);
  Serial.begin(9600);

  renk_al();

}

void renk_al() {
  digitalWrite(s2, LOW); //Kırmızıyı filtrele
  digitalWrite(s3, LOW);
  K = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  delay(50); //50 milisaniye bekle

  digitalWrite(s2, HIGH); //Yeşili filtrele
  digitalWrite(s3, HIGH);
  Y = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  delay(50);

  digitalWrite(s2, LOW); //Maviyi filtrele
  digitalWrite(s3, HIGH);
  M = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  delay(100); //1000 milisaniye bekle
  //Renk değerlerini 1 saniye boyunca ekranda göreceğiz
  Serial.print("VERİ  --->  ");

  Serial.print("RENK AL ----->    ");
  Serial.print(K);
  Serial.print("------");
  Serial.print(Y);
  Serial.print("------");
  Serial.print(M);
  Serial.println(" ");


}



void loop() {

  digitalWrite(s2, LOW); //Kırmızıyı filtrele
  digitalWrite(s3, LOW);
  K2 = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  delay(50); //50 milisaniye bekle

  digitalWrite(s2, HIGH); //Yeşili filtrele
  digitalWrite(s3, HIGH);
  Y2 = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  delay(50);

  digitalWrite(s2, LOW); //Maviyi filtrele
  digitalWrite(s3, HIGH);
  M2 = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  delay(100); //1000 milisaniye bekle
  //Renk değerlerini 1 saniye boyunca ekranda göreceğiz
  Serial.print("TİTRASYON ----->    ");
  Serial.print(K2);
  Serial.print("------");
  Serial.print(Y2);
  Serial.print("------");
  Serial.print(M2);
  Serial.println(" ");
  //Kalibrasyon bölümünde elde ettiğimiz değerleri bu kısımda kullanacağız
  if ((K - deger) < K2 && K2 < (K + deger) && (M - deger) < M2 && M2  < (M + deger) && (Y - deger) < Y2 && Y2 < (Y + deger)) //Eğer tüm renklerin yoğunluğu yüksekse: Beyaz
  {
    Serial.println(">>>>>>>>>>>>++++++++++++++++<<<<<<<<<<<<<<<<<");
    servoM.write(120);
    digitalWrite(maviled, HIGH);
    digitalWrite(kirmiziled, LOW);
  }

  else {                //Belirlediğimiz kıstaslara uymayan diğer renkler
    Serial.println("!!!!!!!!!!!!!!!!!XXXXXXXXXXXX!!!!!!!!!!!!!!!!");
    servoM.write(60);
    digitalWrite(maviled, LOW);
    digitalWrite(kirmiziled, HIGH);
    digitalWrite(buzzerpin, HIGH);
    delay(50);
    digitalWrite(buzzerpin, LOW);


  }






}
