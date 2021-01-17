#include <stdio.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#define goJsonSize 200
#define HTTP_PORT 80
#define WIFI_RETRY_DELAY 60
#define MAX_WIFI_INIT_RETRY 5


ESP8266WebServer http_rest_server(HTTP_PORT);

const char *wifi_ssid = "WIFI";
const char *wifi_passwd = "123456789";

// Written for ArduinoJson v6 Only


// IPAddress static_ip(10, 170, 241, 100);
// IPAddress subnet(255, 255, 255, 0);
// IPAddress gateway(10, 170, 241, 1);

struct Io
{
    byte id;
    byte gpio;
    byte status;
} gpio_resource;

void init_gpio_resource()
{
    gpio_resource.id = 0;
    gpio_resource.gpio = 0;
    gpio_resource.status = LOW;
}
// Initialize Wifi and Connect
int init_wifi()
{
    int retries = 0;

    Serial.println("Connecting to WiFi AP..........");

    WiFi.mode(WIFI_STA);
    // WiFi.config(static_ip, subnet, gateway);
    WiFi.begin(wifi_ssid, wifi_passwd);
    // check the status of WiFi connection to be WL_CONNECTED
    while ((WiFi.status() != WL_CONNECTED) && (retries < MAX_WIFI_INIT_RETRY))
    {
        retries++;
        delay(WIFI_RETRY_DELAY);
        Serial.print("#");
    }
    return WiFi.status(); // return the WiFi connection status
}

void config_rest_server_routing() {
    http_rest_server.on("/", HTTP_GET, []() {
        http_rest_server.send(200, "text/html",
            "Welcome to the ESP8266 REST Web Server");
    });
    http_rest_server.on("/io", HTTP_GET, get_io);
    http_rest_server.on("/io", HTTP_POST, post_put_io);
    http_rest_server.on("/io", HTTP_PUT, post_put_io);
}

// HTTP GET JSON
void get_io() {
    StaticJsonDocument<200> goJson;

    goJson["id"] = gpio_resource.id;
    goJson["gpio"] = gpio_resource.gpio;
    goJson["status"] = gpio_resource.status;

    char buffer[goJsonSize]; 
    serializeJson(goJson, buffer);
    http_rest_server.send(200, "application/json", buffer);
}

// HTTP POST/PUT
void post_put_io() {
    StaticJsonDocument<500> goJson;
    String post_body = http_rest_server.arg("plain");
    Serial.println(post_body);

    deserializeJson(goJson, post_body);
    Serial.print("HTTP Method: ");
    Serial.println(http_rest_server.method());
    
    auto error = deserializeJson(goJson, post_body);
    if (error) {
        Serial.print("Deserialzed Failed: ");
        Serial.println(error.c_str());
        return;
    } else {
        if (http_rest_server.method() == HTTP_POST) {
            if ((goJson["id"] != 0) && (goJson["id"] != gpio_resource.id)) {
                Serial.println("POST SHOULD WORK");
                json_to_resource(goJson);
                http_rest_server.sendHeader("Location", "/io/" + String(gpio_resource.id));
                http_rest_server.send(201);
                pinMode(gpio_resource.gpio, OUTPUT);
            } else if (goJson["id"] == 0) {
                http_rest_server.send(404);
            } else if (goJson["id"] == gpio_resource.id) {
                http_rest_server.send(409);
            }
        } else if (http_rest_server.method() == HTTP_PUT) {
            if (goJson["id"] == gpio_resource.id) {
                json_to_resource(goJson);
                http_rest_server.sendHeader("Location", "/io/" + String(gpio_resource.id));
                http_rest_server.send(200);
                digitalWrite(gpio_resource.gpio, gpio_resource.status);
            } else {
                http_rest_server.send(404);
            }
        }
    }

}

void json_to_resource(JsonDocument& jsonBuffer) {
    int id, gpio, status;
    // JsonObject jsonBuffer = jsonobj.as<JsonObject>();
    id = jsonBuffer["id"];
    gpio = jsonBuffer["gpio"];
    status = jsonBuffer["status"];

    Serial.println(id);
    Serial.println(gpio);
    Serial.println(status);

    gpio_resource.id = id;
    gpio_resource.gpio = gpio;
    gpio_resource.status = status;
}

// Initialize Io struct, wifi, serial, http server
void setup(void) {
    Serial.begin(115200);

    init_gpio_resource();
    if (init_wifi() == WL_CONNECTED)
    {
        Serial.print("Connetted to ");
        Serial.print(wifi_ssid);
        Serial.print("--- IP: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.print("Error connecting to: ");
        Serial.println(wifi_ssid);
    }

    config_rest_server_routing();

    http_rest_server.begin();
    Serial.println("HTTP REST Server Started");
}

void loop(void) {
    http_rest_server.handleClient();
}
