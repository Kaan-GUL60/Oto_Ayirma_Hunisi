//75.101.132.229



#define s0 8 //Bağladığımız pinlere göre tanımlamalarımızı yapıyoruz
#define s1 9
#define s2 10
#define s3 11
#define sensorOut 12


int K, Y, M = 0; //3 ana renk için değişken tanımlıyoruz

void setup() {

  pinMode(s0, OUTPUT); //S0, S1, S2 ve S3 pinlerini OUTPUT olarak tanımlıyoruz
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorOut, INPUT); //OUT pinini INPUT olarak tanımlıyoruz

  digitalWrite(s1, LOW); //Frekans ölçeğimizi %20 olarak tanımlıyoruz
  digitalWrite(s0, HIGH);
  Serial.begin(9600);

}

void loop() {

  
  digitalWrite(s2, LOW); //Kırmızıyı filtrele
  digitalWrite(s3, LOW);
  K = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Kırmızı= ");
  Serial.print(K); //Kırmızı için aldığımız değeri serial monitöre yazdır
  Serial.print("  ");
  delay(50); //50 milisaniye bekle


  digitalWrite(s2, HIGH); //Yeşili filtrele
  digitalWrite(s3, HIGH);
  Y = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Yeşil= ");
  Serial.print(Y); //Yeşil için aldığımız değeri serial monitöre yazdır
  Serial.print("   ");
  delay(50);


  digitalWrite(s2, LOW); //Maviyi filtrele
  digitalWrite(s3, HIGH);
  M = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Mavi= ");
  Serial.print(M); //Mavi için aldığımız değeri serial monitöre yazdır
  Serial.println();
  delay(1000); //1000 milisaniye bekle
  //Renk değerlerini 1 saniye boyunca ekranda göreceğiz


  //Kalibrasyon bölümünde elde ettiğimiz değerleri bu kısımda kullanacağız
  if (K < 45 && M < 45 && Y < 45) //Eğer tüm renklerin yoğunluğu yüksekse: Beyaz
  {
    Serial.print("Renk = Beyaz   ");
  } else if (K < 100 && Y < M && abs(K - Y) < 20)
  //Kırmızı yoğunluğu yüksek ve yeşille arasındaki değer 20'den azsa: Sarı
  {
    Serial.print("Renk = Sarı   ");
  }/* else if (K < 100 && M < Y && abs(M - K) < 20)
  //Kırmızı yoğunluğu yüksek ve mavi ile arasındaki değer 20'den azsa: Magenta
  {
    Serial.print("Renk = Magenta   ");
  }*/ else if (Y < 130 && Y < M && Y < K)
  //Yeşil yoğunluğu belli bir seviyenin üstünde ve kırmızı-maviden daha yoğunsa: Yeşil
  {
    Serial.print("Renk = Yeşil   ");
  } else if (M < 100 && M < Y && M < K)
  //Mavi yoğunluğu belli bir seviyenin üstünde ve yeşil-kırmızıdan daha yoğunsa: Mavi
  {
    Serial.print("Renk = Mavi   ");
  } else if (K < 100 && K < Y && K < M)
  //Kırmızı yoğunluğu belli bir seviyenin üstünde ve yeşil-maviden daha yoğunsa: Kırmızı
  {
    Serial.print("Renk = Kırmızı   ");
  } else {
    Serial.print("Renk algılanamadı   "); //Belirlediğimiz kıstaslara uymayan diğer renkler
  }

  Serial.println(); //Serial monitörde bir satır aşağı geç
  delay(1000); //1000 milisaniye bekle
  delay(150);

}
