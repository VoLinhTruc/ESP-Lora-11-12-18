#include <ESP8266WiFi.h>

const char ssid[] = "Phong Tro";
const char pwd[] = "phongtro4b";

IPAddress ip(192, 168, 1, 169);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer my_server(502);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  delay(100);
  
  Serial.println();

  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pwd);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.printf("Connected to %s \r\n", ssid);
  Serial.printf("Static IP: %s\r\n", ip.toString().c_str());


  my_server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = my_server.available();
  if(client)
  {
    while(client.connected())
    {
      // Pass TCP to Serial ---------------------
      if(client.available())
      {
        while(client.available())
        {
          uint8_t data = client.read();
          if((data == 10) || (data == 11))
          {
            Serial.write(0);
            Serial.write(10);
            Serial.write(9);
            Serial.write(data - 10);
            
            client.write(data);
          }
          else if((data == 20) || (data == 21))
          {
            Serial.write(0);
            Serial.write(11);
            Serial.write(9);
            Serial.write(data - 20);
            
            client.write(data);
          }
        }
      }
      // Pass TCP to Serial ---------------------
    }
    client.stop();
  }
}
