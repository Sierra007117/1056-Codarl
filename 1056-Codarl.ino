#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager
#include <LiquidCrystal_I2C.h> //https://codeload.github.com/johnrickman/LiquidCrystal_I2C/zip/master
#include <TM1637Display.h>
WiFiServer server(80);
String header;

String output1State = "off";
String output2State = "off";
String output3State = "off";
String output4State = "off";

const int output1 = D3;
const int output2 = D8;
const int output3 = D7;
const int output4 = D6;

String newHostname = "1056 Codarl";

#define CLK D0
#define DIO D5
TM1637Display display = TM1637Display(CLK, DIO);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", 28800, 60000);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  display.clear();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("System Armed");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Booting");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Titan           ");
  lcd.setCursor(0, 1);
  lcd.print("Booting>");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Titan Defence   ");
  lcd.setCursor(0, 1);
  lcd.print("Booting>>");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Titan Defence Systems");
  lcd.setCursor(0, 1);
  lcd.print("Booting>>>");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("itan Defence Systems");
  lcd.setCursor(0, 1);
  lcd.print("Booting>>>>");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("tan Defence Systems");
  lcd.setCursor(0, 1);
  lcd.print("Booting>>>>>");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("an Defence Systems");
  lcd.setCursor(0, 1);
  lcd.print("Booting>>>>>>");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("n Defence Systems");
  lcd.setCursor(0, 1);
  lcd.print("Booting>>>>>>>");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print(" Defence Systems");
  lcd.setCursor(0, 1);
  lcd.print("Booting>>>>>>>>");
  delay(500);

  lcd.setCursor(0, 1);
  lcd.print("Booting>>>>>>>>>");
  delay(500);
  lcd.clear();
  Serial.print("Connecting to ");
  Serial.println(WiFi.SSID());
  Serial.printf("Default hostname: %s\n", WiFi.hostname().c_str());
  WiFi.hostname(newHostname.c_str());
  Serial.printf("New hostname: %s\n", WiFi.hostname().c_str());

  pinMode(D4, OUTPUT);

  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);

  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output4, LOW);

  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("Connected.");
  server.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initiating in 10");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Initiating in 09");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Initiating in 08");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Initiating in 07");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Initiating in 06");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Initiating in 05");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Initiating in 04");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Initiating in 03");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Initiating in 02");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Initiating in 01");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Starting Web APP");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Local IP Address");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<01><02><03><04>");
  lcd.setCursor(0, 1);
  lcd.print("^OFF^OFF^OFF^OFF");
}

void loop() {
  digitalWrite(D4, HIGH);
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  Serial.println(WiFi.localIP());
  int A, B;
  display.setBrightness(7); // Set the brightness:
  A = timeClient.getHours() * 100 + timeClient.getMinutes();
  B = timeClient.getSeconds();
  if ((B % 2) == 0)
  {
    display.showNumberDecEx(A, 0b01000000, false, 4, 0);
  }
  else
  {
    display.showNumberDecEx(A, 0b00000000, false, 4, 0);
  }
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {

          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("output1State on");
              lcd.setCursor(0, 0);
              lcd.print(">01<");
              lcd.setCursor(0, 1);
              lcd.print(">ON<");
              output1State = "on";
              digitalWrite(output1, HIGH);
            }
            else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("output1State off");
              lcd.setCursor(0, 0);
              lcd.print("<01>");
              lcd.setCursor(0, 1);
              lcd.print("^OFF");
              output1State = "off";
              digitalWrite(output1, LOW);
            }

            else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("output2State on");
              lcd.setCursor(4, 0);
              lcd.print(">02<");
              lcd.setCursor(4, 1);
              lcd.print(">ON<");
              output2State = "on";
              digitalWrite(output2, HIGH);
            }
            else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("output2State off");
              lcd.setCursor(4, 0);
              lcd.print("<02>");
              lcd.setCursor(4, 1);
              lcd.print("^OFF");
              output2State = "off";
              digitalWrite(output2, LOW);
            }

            else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("output3State on");
              lcd.setCursor(8, 0);
              lcd.print(">03<");
              lcd.setCursor(8, 1);
              lcd.print(">ON<");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("output3State off");
              lcd.setCursor(8, 0);
              lcd.print("<03>");
              lcd.setCursor(8, 1);
              lcd.print("^OFF");
              output3State = "off";
              digitalWrite(output3, LOW);
            }

            else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("output4State on");
              lcd.setCursor(12, 0);
              lcd.print(">04<");
              lcd.setCursor(12, 1);
              lcd.print(">ON<");
              output4State = "on";
              digitalWrite(output4, HIGH);
            }
            else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("output4State off");
              lcd.setCursor(12, 0);
              lcd.print("<04>");
              lcd.setCursor(12, 1);
              lcd.print("^OFF");
              output4State = "off";
              digitalWrite(output4, LOW);
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background: firebrick;}");
            client.println(".button { background-color: green; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: red;}</style></head>");
            client.println("<body><h1>Prototype 420.69</h1>");

            client.println("<p>Relay One | Status : " + output1State + "</p>");
            if (output1State == "off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">Turn OFF</button></a></p>");
            }

            client.println("<p>Relay Two | Status : " + output2State + "</p>");
            if (output2State == "off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">Turn OFF</button></a></p>");
            }

            client.println("<p>Relay Three | Status : " + output3State + "</p>");
            if (output3State == "off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">Turn OFF</button></a></p>");
            }

            client.println("<p>Relay Four | Status : " + output4State + "</p>");
            if (output4State == "off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">Turn OFF</button></a></p>");
            }

            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  digitalWrite(D4, LOW);
}
