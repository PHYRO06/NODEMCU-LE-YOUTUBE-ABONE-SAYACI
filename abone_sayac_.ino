#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif

#include <WiFiClientSecure.h>


#include <YoutubeApi.h>



#include <ArduinoJson.h>


#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Wire.h>


const char ssid[] = "XXXX";       // internet adınız
const char password[] = "YYYY";  // internet şifresi
#define API_KEY "ZZZZ"       // Google API key
#define CHANNEL_ID "UCFlDPkGt1yds_QMbbxANElg" 


WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

unsigned long timeBetweenRequests = 60 * 1000;  

void setup() {
 Wire.begin(D2, D1);
 lcd.begin();

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  
  Serial.print("\nWiFi baglaniyor: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi baglandı!");
  Serial.print("IP adresin: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  #ifdef ESP8266
  client.setInsecure();
  #endif

}

void loop() {
    
  if(api.getChannelStatistics(CHANNEL_ID)) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ABONE SAYISI");
    lcd.setCursor(0, 1);
    lcd.print(api.channelStats.subscriberCount);
    delay(2000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("IZLENME SAYISI");
    lcd.setCursor(0, 1);
    lcd.print(api.channelStats.viewCount);
    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VIDEO SAYISI");
    lcd.setCursor(0, 1);
    lcd.print(api.channelStats.videoCount);
    delay(2000);

  }
  //delay(timeBetweenRequests);
}
