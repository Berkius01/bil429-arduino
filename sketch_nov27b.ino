#include <SoftwareSerial.h>    

int rxPin = 10;                                               
int txPin = 11;
SoftwareSerial esp(rxPin, txPin);
  
String agAdi = "test";                    
String agSifresi = "testtest";

String host="192.168.0.10";                                   //Server ip adresi.
String port="11000";                                          //Server port numarası.

void setup() {
  Serial.begin(9600);  //Seri port ile haberleşmemizi başlatıyoruz.
  Serial.println("Started");
  esp.begin(115200);                                          //ESP8266 ile seri haberleşmeyi başlatıyoruz.
  esp.println("AT");                                          //AT komutu ile modül kontrolünü yapıyoruz.
  Serial.println("AT Yollandı");
  while(!esp.find("OK")){                                     //Modül hazır olana kadar bekliyoruz.
    esp.println("AT");
    Serial.println("ESP8266 Bulunamadı.");
  }
  Serial.println("OK Komutu Alındı");
  esp.println("AT+CWMODE=1");                                 //ESP8266 modülünü client olarak ayarlıyoruz.
  while(!esp.find("OK")){                                     //Ayar yapılana kadar bekliyoruz.
    esp.println("AT+CWMODE=1");
    Serial.println("Ayar Yapılıyor....");
  }
  Serial.println("Client olarak ayarlandı");
  Serial.println("Aga Baglaniliyor...");
  esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");    //Ağımıza bağlanıyoruz.
  while(!esp.find("OK"));                                     //Ağa bağlanana kadar bekliyoruz.
  Serial.println("Aga Baglandi.");
  delay(1000);
}


void loop() {
  esp.println("AT+CIPSTART=\"TCP\",\""+host+"\",11000");           //Servera TCP bağlantısı açılıyor.
  if(esp.find("Error")){                                      
    Serial.println("AT+CIPSTART Error");
  }
 String veri;
  veri = String(random(50,100));                                  //Rastgele veri üretiliyor.
  esp.print("AT+CIPSEND=");                                       //Gönderilecek verinin boyutunu ayarlanıyor.       
  esp.println(veri.length()+2);
  if(esp.find(">")){    
    esp.print(veri);                                         
    Serial.println(veri);
    Serial.println("Veri gonderildi.");
    delay(1000);
  }
  Serial.println("Baglantı Kapatildi.");
  esp.println("AT+CIPCLOSE");                                   //Server TCP bağlantısı kapatılıyor.     
  delay(1000);                                               
}
