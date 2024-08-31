#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESPAsyncWebServer.h>
#include <DHT22.h>
#include <ArduinoJson.h> 
#include <string>
const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Temperature & Humedity</title>
    <script>
        var gateway = `ws://${window.location.hostname}/ws`;
        var connection = new WebSocket(gateway);
        var tdate1,tdate2,hdate1,hdate2;
        connection.onerror = (e)=>{
            alert(`Websocket error: ${e}`);
        }
        connection.onmessage = (message)=>{
            let jsonData = JSON.parse(message.data);
            try {
                document.getElementById("currentTemperature").innerText = `${jsonData["temperature"][1].toFixed(2)}ºC`;
                document.getElementById("maxtemp").innerText = `${jsonData["temperature"][0].toFixed(2)}ºC`;
                document.getElementById("averagetemp").innerText = `${jsonData["temperature"][3].toFixed(2)}ºC`;
                document.getElementById("mintemp").innerText = `${jsonData["temperature"][2].toFixed(2)}ºC`;
                document.getElementById("maxTtime").innerText = jsonData["temperature"][4];
                document.getElementById("minTtime").innerText =  jsonData["temperature"][5];

                document.getElementById("currentHumedity").innerText =`${jsonData["humidity"][1].toFixed(2)}%`;
                document.getElementById("maxHumidity").innerText = `${jsonData["humidity"][0].toFixed(2)}%`;
                document.getElementById("averageHumidity").innerText = `${jsonData["humidity"][3].toFixed(2)}%`;
                document.getElementById("minHumidity").innerText = `${jsonData["humidity"][2].toFixed(2)}%`;
                document.getElementById("maxHtime").innerText =  jsonData["humidity"][4];
                document.getElementById("minHtime").innerText =  jsonData["humidity"][5];
            }
            catch(error) {
                document.getElementById("minTtime").innerText = "XX:XX";
                document.getElementById("maxHtime").innerText = "XX:XX";
                document.getElementById("minHtime").innerText = "XX:XX";
            }
            console.log(jsonData);
        }
      </script>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&family=Montserrat:ital,wght@0,100..900;1,100..900&family=Oswald:wght@200..700&display=swap');
        * {
            font-family: "Montserrat", sans-serif;
            font-optical-sizing: auto;
            font-style: normal;
            color: white;
            font-size: 30px;
            padding: 0;
            margin: 0;
        }
        html {
            scroll-behavior: smooth;
        }
        header {
            display: flex;
            justify-content: center;
        }
        header nav {
            position: fixed;
            z-index: 100;
            display: flex;
            justify-content: space-between;
            width: 95vw;
        }
        header nav div > a {
            font-weight: 500;
            background-color: #344e41;
            border-radius: 10px;
            font-size: 0.5rem;
            padding: 8px;
            text-decoration: none;
        }
        .container {
            position: relative;
            display: flex;
            flex-direction: column;
            align-items: center;
            align-content: center;
            justify-content: space-evenly;
        }
        .container .temperatureContainer, .container .humidityContainer {
            position: relative;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content:space-evenly;
            background: rgba(251,133,0,1);
            background: linear-gradient(180deg, rgba(251,133,0,1) 55%, rgba(233,135,16,1) 89%, rgba(35,118,247,1) 100%);
            width: 100%;
            height: 100vh;
        }
        .container .humidityContainer {
            background: rgb(35,118,247);
            background: linear-gradient(0deg, rgba(72,80,238,1) 0% ,rgba(35,118,247,1) 100% );
        }
        .container .temperatureContainer > div, .container .humidityContainer > div {
            position: relative;
            display: flex;
            flex-wrap: nowrap;
            flex-direction: row;
            justify-content: space-evenly;
            width: 100%;
        }
        #currentTemperature, #currentHumedity {
            position: relative;
            text-align: center;
            font-size: 2rem;
        }
        #currentTemperature::before, #currentHumedity::before {
            top:50%;
            left: 50%;
            translate: -50%, -50%;
            width: 100%;
            height: 100%;
            content: '';
            background-color: white;
            filter: blur(10px);
            opacity: 0.2;
        }
        .container h2 {
            font-size: 1.2rem;
            text-align: center;
        }
        .container p {
            text-decoration: underline;
            font-size: 0.5rem;
            text-align: left;
        }

    </style>
</head>
<body>
    <header>
        <nav>
            <img src="" alt="">
            <div>
                <a href="#temperature">Temperatura</a>
                <a href="#humidity">Humedad</a>
            </div>
        </nav>
    </header>
    <main class="container">
        <div id="temperature" class="temperatureContainer">
            <div>
              <span>
                <p style="font-size: 0.8rem;">Actual</p>
                <h1 id="currentTemperature"></h1>
              </span>
            </div>
            <div>
                <span>
                 <p>Máxima</p>
                 <h2 id="maxtemp"></h2>
                 <p id="maxTtime"></p>
                </span>
                <span>
                 <p>Promedio</p>
                 <h2 id="averagetemp"></h2>
                </span>
                <span>
                 <p>Mínima</p>
                 <h2 id="mintemp"></h2>
                 <p id="minTtime"></p>
                </span>
             </div>
        </div>
        <div id="humidity" class="humidityContainer">
            <div>
                <span>
                    <p style="font-size: 0.8rem;">Actual</p>
                    <h1 id="currentHumedity"></h1>
                </span>
            </div>
            <div>
                <span>
                 <p>Máxima</p>
                 <h2 id="maxHumidity"></h2>
                 <p id="maxHtime"></p>
                </span>
                <span>
                 <p>Promedio</p>
                 <h2 id="averageHumidity"></h2>
                </span>
                <span>
                 <p>Mínima</p>
                 <h2 id="minHumidity"></h2>
                 <p id="minHtime"></p>
                </span>
             </div>
        </div>
    </main>
</body>
</html>)rawliteral";

#define dht22pin D2

DHT22 dht22(dht22pin);
const char* ssid = "yourroutername";
const char* password = "password";
String JsonData;

float maxH; String t_maxH;
float maxT; String t_maxT;
float minH; String t_minH;
float minT; String t_minT;
float t = dht22.getTemperature();
float h = dht22.getHumidity();

float phamount = 0;
float ptamount = 0;
float ph = 0;
float pt = 0;

WiFiUDP ntpUDP;
NTPClient NTPclient(ntpUDP, "0.es.pool.ntp.org", 7200, 30000);

int amountOfMetrics = 0;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void maxth(float *x, float y, String *t_type) {
  if (y > *x){
    *x = y;
    Serial.print("max: ");
    Serial.println(*x);
    NTPclient.update();
    *t_type = NTPclient.getFormattedTime();
  }
  

}
void minth(float *x, float y, String *t_type) {
  if (y < *x){
    *x = y;
    Serial.print("min: ");
    Serial.println(*x);
    NTPclient.update();
    *t_type = NTPclient.getFormattedTime();
  }
    
}
void average(float *h, float *t, int amount) {
  *h = phamount/amount;
  *t = ptamount/amount;
  /*
  Serial.print("P. Humidity: ");Serial.println(*h);
  Serial.print("P. Temperature: ");Serial.println(*t);
  */
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void setup() {
  minH = dht22.getHumidity();
  minT = dht22.getTemperature();
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ws.onEvent(onEvent);
  server.addHandler(&ws);
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, NULL);
  });
  // Servidor de tiempo
  NTPclient.begin();
  // Start server
  server.begin();
}

void loop() {
  ws.cleanupClients();
  t = dht22.getTemperature();
  h = dht22.getHumidity();

  JsonDocument rawData;
  JsonArray humidity = rawData["humidity"].to<JsonArray>();
  JsonArray temperature = rawData["temperature"].to<JsonArray>();

  maxth(&maxH, h, &t_maxH);
  maxth(&maxT, t, &t_maxT);
  minth(&minH, h, &t_minH);
  minth(&minT, t, &t_minT);
  phamount+=h;
  ptamount+=t;
  amountOfMetrics++;
  average(&ph ,&pt , amountOfMetrics);

  humidity.add(maxH);
  humidity.add(h);
  humidity.add(minH);
  humidity.add(ph);
  humidity.add(t_maxH);
  humidity.add(t_minH);
  temperature.add(maxT);
  temperature.add(t);
  temperature.add(minT);
  temperature.add(pt);
  temperature.add(t_maxT);
  temperature.add(t_minT);
  
  ws.textAll(JsonData);

  serializeJsonPretty(rawData, JsonData);
  if (amountOfMetrics > 10000){
    amountOfMetrics = 0;
    phamount = 0;
    ptamount = 0;
  }
  delay(2000);
}

