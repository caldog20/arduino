#include <ESP8266WiFi.h> 

#define ssid "WIFI" // Replace with your network name
#define password "123456789" // Replace with your network password
#define hostname "esp-gpio-control";
#define HTTP_PORT 80

// Uncomment '#define STATICIP' define below and change the IPAddress static_ip, subnet, gateway and dns if you wish to use a static IP
// Otherwise it will use DHCP

#define STATICIP


#ifdef STATICIP
IPAddress static_ip(10, 170, 241, 100);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(10, 170, 241, 1);
IPAddress dns(10, 170, 241, 1);
#endif

WiFiServer server(HTTP_PORT);

String header;
String State[9] = {"Off", "Off", "Off", "Off", "Off", "Off", "Off", "Off", "Off"};
const int GPIO[] = {16, 5, 4, 0, 2, 14, 12, 13, 15};


void init_wifi() {
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    #ifdef STATICIP
    WiFi.config(static_ip, subnet, gateway);
    #endif
    #ifndef STATICIP
    WiFi.hostname(hostname);
    #endif
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.print(" Wifi connected. IP Address: ");
    Serial.print(WiFi.localIP());
    Serial.println("");
    Serial.print(" Wifi will listen on port ");
    Serial.print(HTTP_PORT);
    Serial.println("");

    delay(2000);
}

void init_gpio() {
    for (int i = 0; i < 9; i++) {
        pinMode(GPIO[i], OUTPUT);
        digitalWrite(GPIO[i], LOW);
    }
    Serial.println("");
    Serial.println("GPIO pins are now initialized...");
    Serial.println("");
}

void setup() { 
    
    Serial.begin(115200);
    
    delay(2000);
    
    init_gpio();
    init_wifi();
    server.begin(); // Starting the web server
    Serial.println("Webserver Ready");

    
}

void loop() {
    // Searching for new clients
    WiFiClient client = server.available();

    if (client) {
        // Serial.println("New client");
        boolean blank_line = true; // boolean to locate when the http request ends
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                header += c;

                if (c == '\n' && blank_line) {
                    // Serial.print(header);

                    // Finding the right credential string
                    // if (header.indexOf("VXNlcjoxMjM0") >= 0) { // 
                        //successful login
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    // turns the GPIO on and off
                if (header.indexOf("GET / HTTP/1.1") >= 0) {
                    Serial.println("Main Web Page");
                }
                else if (header.indexOf("GET /GPIO16on HTTP/1.1") >= 0) {
                    Serial.println("GPIO 16 On");
                    State[0] = "On";
                    digitalWrite(GPIO[0], HIGH);
                }
                else if (header.indexOf("GET /GPIO16off HTTP/1.1") >= 0) {
                    Serial.println("GPIO 16 Off");
                    State[0] = "Off";
                    digitalWrite(GPIO[0], LOW);
                }
                else if (header.indexOf("GET /GPIO5on HTTP/1.1") >= 0) {
                    Serial.println("GPIO 5 On");
                    State[1] = "On";
                    digitalWrite(GPIO[1], HIGH);
                }
                else if (header.indexOf("GET /GPIO5off HTTP/1.1") >= 0) {
                    Serial.println("GPIO 5 Off");
                    State[1] = "Off";
                    digitalWrite(GPIO[1], LOW);
                }
                else if (header.indexOf("GET /GPIO4on HTTP/1.1") >= 0) {
                    Serial.println("GPIO 4 On");
                    State[2] = "On";
                    digitalWrite(GPIO[2], HIGH);
                }
                else if (header.indexOf("GET /GPIO4off HTTP/1.1") >= 0) {
                    Serial.println("GPIO 4 Off");
                    State[2] = "Off";
                    digitalWrite(GPIO[2], LOW);
                }
                else if (header.indexOf("GET /GPIO0on HTTP/1.1") >= 0) {
                    Serial.println("GPIO 0 On");
                    State[3] = "On";
                    digitalWrite(GPIO[3], HIGH);
                }
                else if (header.indexOf("GET /GPIO0off HTTP/1.1") >= 0) {
                    Serial.println("GPIO 0 Off");
                    State[3] = "Off";
                    digitalWrite(GPIO[3], LOW);
                }
                else if (header.indexOf("GET /GPIO2on HTTP/1.1") >= 0) {
                    Serial.println("GPIO 2 On");
                    State[4] = "On";
                    digitalWrite(GPIO[4], HIGH);
                }
                else if (header.indexOf("GET /GPIO2off HTTP/1.1") >= 0) {
                    Serial.println("GPIO 2 Off");
                    State[4] = "Off";
                    digitalWrite(GPIO[4], LOW);
                }
                else if (header.indexOf("GET /GPIO14on HTTP/1.1") >= 0) {
                    Serial.println("GPIO 14 On");
                    State[5] = "On";
                    digitalWrite(GPIO[5], HIGH);
                }
                else if (header.indexOf("GET /GPIO14off HTTP/1.1") >= 0) {
                    Serial.println("GPIO 14 Off");
                    State[5] = "Off";
                    digitalWrite(GPIO[5], LOW);
                }
                else if (header.indexOf("GET /GPIO12on HTTP/1.1") >= 0) {
                    Serial.println("GPIO 12 On");
                    State[6] = "On";
                    digitalWrite(GPIO[6], HIGH);
                }
                else if (header.indexOf("GET /GPIO12off HTTP/1.1") >= 0) {
                    Serial.println("GPIO 12 Off");
                    State[6] = "Off";
                    digitalWrite(GPIO[6], LOW);
                }
                else if (header.indexOf("GET /GPIO13on HTTP/1.1") >= 0) {
                    Serial.println("GPIO 13 On");
                    State[7] = "On";
                    digitalWrite(GPIO[7], HIGH);
                }
                else if (header.indexOf("GET /GPIO13off HTTP/1.1") >= 0) {
                    Serial.println("GPIO 13 Off");
                    State[7] = "Off";
                    digitalWrite(GPIO[7], LOW);
                }
                else if (header.indexOf("GET /GPIO15on HTTP/1.1") >= 0) {
                    Serial.println("GPIO 15 On");
                    State[8] = "On";
                    digitalWrite(GPIO[8], HIGH);
                }
                else if (header.indexOf("GET /GPIO15off HTTP/1.1") >= 0) {
                    Serial.println("GPIO 15 Off");
                    State[8] = "Off";
                    digitalWrite(GPIO[8], LOW);
                }
                // Web page
                client.println("<!DOCTYPE HTML>");
                client.println("<html>");
                client.println("<head>");
                client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                client.println("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">");
                client.println("</head><div class=\"container\">");
                client.println("<h1>ESP8266 GPIO Web Interface</h1>");
                client.println("<h2>GPIO Control</h2>");
                client.println("<h3>GPIO 16: State: " + State[0]);
                client.println("<div class=\"row\">");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO16on\" class=\"btn btn-block btn-lg btn-primary\" role=\"button\">ON</a></div>");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO16off\" class=\"btn btn-block btn-lg btn-info\" role=\"button\">OFF</a></div>");
                client.println("</div>");
                client.println("<h3>GPIO 5: State: " + State[1]);
                client.println("<div class=\"row\">");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO5on\" class=\"btn btn-block btn-lg btn-primary\" role=\"button\">ON</a></div>");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO5off\" class=\"btn btn-block btn-lg btn-info\" role=\"button\">OFF</a></div>");
                client.println("</div>");
                client.println("<h3>GPIO 4: State: " + State[2]);
                client.println("<div class=\"row\">");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO4on\" class=\"btn btn-block btn-lg btn-primary\" role=\"button\">ON</a></div>");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO4off\" class=\"btn btn-block btn-lg btn-info\" role=\"button\">OFF</a></div>");
                client.println("</div>");
                client.println("<h3>GPIO 0: State: " + State[3]);
                client.println("<div class=\"row\">");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO0on\" class=\"btn btn-block btn-lg btn-primary\" role=\"button\">ON</a></div>");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO0off\" class=\"btn btn-block btn-lg btn-info\" role=\"button\">OFF</a></div>");
                client.println("</div>");
                client.println("<h3>GPIO 2: State: " + State[4]);
                client.println("<div class=\"row\">");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO2on\" class=\"btn btn-block btn-lg btn-primary\" role=\"button\">ON</a></div>");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO2off\" class=\"btn btn-block btn-lg btn-info\" role=\"button\">OFF</a></div>");
                client.println("</div>");
                client.println("<h3>GPIO 14: State: " + State[5]);
                client.println("<div class=\"row\">");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO14on\" class=\"btn btn-block btn-lg btn-primary\" role=\"button\">ON</a></div>");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO14off\" class=\"btn btn-block btn-lg btn-info\" role=\"button\">OFF</a></div>");
                client.println("</div>");
                client.println("<h3>GPIO 12: State: " + State[6]);
                client.println("<div class=\"row\">");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO12on\" class=\"btn btn-block btn-lg btn-primary\" role=\"button\">ON</a></div>");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO12off\" class=\"btn btn-block btn-lg btn-info\" role=\"button\">OFF</a></div>");
                client.println("</div>");
                client.println("<h3>GPIO 13: State: " + State[7]);
                client.println("<div class=\"row\">");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO13on\" class=\"btn btn-block btn-lg btn-primary\" role=\"button\">ON</a></div>");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO13off\" class=\"btn btn-block btn-lg btn-info\" role=\"button\">OFF</a></div>");
                client.println("</div>");
                client.println("<h3>GPIO 15: State: " + State[8]);
                client.println("<div class=\"row\">");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO15on\" class=\"btn btn-block btn-lg btn-primary\" role=\"button\">ON</a></div>");
                client.println("<div class=\"col-md-2\"><a href=\"/GPIO15off\" class=\"btn btn-block btn-lg btn-info\" role=\"button\">OFF</a></div>");
                client.println("</div></div></html>");
                // }
                // else { // Http request fails for unauthorized users
                //     client.println("HTTP/1.1 401 Unauthorized");
                //     client.println("WWW-Authenticate: Basic realm=\"Secure\"");
                //     client.println("Content-Type: text/html");
                //     client.println();
                //     client.println("<html>Authentication failed</html>");
                // }
                header = "";
                break;
                }
                if (c == '\n') { // starts reading a new line
                blank_line = true;
                }
                else if (c != '\r') { // finds a character on the current line
                blank_line = false;
                }
            }
        }
        delay(1);
        client.stop(); // ending the client connection
        // Serial.println("Client disconnected.");
    }
}