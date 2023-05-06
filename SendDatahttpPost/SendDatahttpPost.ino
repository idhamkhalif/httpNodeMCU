#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Galaxy M33";
const char* password = "123456789";
float temperature;
float humidity;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  delay(1000);
}

void loop() {
  temperature = random(20, 50);
  humidity = random(80, 90);

  if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    String address;
    address = "http://monitoringapp0901.000webhostapp.com/monitoring/insert.php?temperature=";
    address += String(temperature);
    address += "&humidity=";
    address += String(humidity);


    http.begin(client, address); //Specify request destination
    int httpCode = http.GET();//Send the request
    String payload;
    if (httpCode > 0) { //Check the returning code
      payload = http.getString();   //Get the request response payload
      payload.trim();
      if ( payload.length() > 0 ) {
        Serial.println(payload + "\n");
      }
    }

    http.end();   //Close connection
  } else {
    Serial.print("Not connected to wifi "); Serial.println(ssid);
  }
  delay(60000); //interval 60s
}
