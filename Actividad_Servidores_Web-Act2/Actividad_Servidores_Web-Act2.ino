#include <WiFi.h>

/*------------------Servidor Web en puerto 80---------------------*/

#define PORT 80
WiFiServer server(PORT);

/*---------------------Credenciales de WiFi-----------------------*/

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

/*---------------------VARIABLES GLOBALES-------------------------*/
int contconexion = 0;
int i, disp2 = 22, disp1 = 23, t = 750;
String header;  // Variable para guardar el HTTP request

String display1 = "off";
String display2 = "off";
// A   B   C  D   E   F   G
const uint8_t seg[7] = { 4, 16, 17, 5, 18, 19, 21 };
const bool dig[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },  //0
  { 0, 1, 1, 0, 0, 0, 0 },  //1
  { 1, 1, 0, 1, 1, 0, 1 },  //2
  { 1, 1, 1, 1, 0, 0, 1 },  //3
  { 0, 1, 1, 0, 0, 1, 1 },  //4
  { 1, 0, 1, 1, 0, 1, 1 },  //5
  { 1, 0, 1, 1, 1, 1, 1 },  //6
  { 1, 1, 1, 0, 0, 0, 0 },  //7
  { 1, 1, 1, 1, 1, 1, 1 },  //8
  { 1, 1, 1, 1, 0, 1, 1 },  //9
};
/*------------------------CODIGO HTML------------------------------*/
/* - ATENCION -
  se tiene que poner cada linea entre comillas y reemplazar las comillas dentro por
  comillas simples */

String pagina = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<meta charset='utf-8' />"
                "<title>Servidor Web ESP32</title>"
                "</head>"
                "<body>"
                "<center>"
                "<h1>Servidor Web ESP32</h1>"
                "<p><a href='/display1'><button style='height:50px;width:100px'>display1</button></a></p>"
                "<p><a href='/display2'><button style='height:50px;width:100px'>display2</button></a></p>"

                "</center>"
                "</body>"
                "</html>";


/*---------------------------SETUP--------------------------------*/
void setup() {
  Serial.begin(115200);
  Serial.println("");
  for (i = 0; i < 7; i++) {
    pinMode(seg[i], OUTPUT);
    digitalWrite(seg[i], LOW);
  }
  pinMode(disp2, OUTPUT);
  digitalWrite(disp2, HIGH);
  pinMode(disp1, OUTPUT);
  digitalWrite(disp1, HIGH);

  // Conexión WIFI
  WiFi.begin(ssid, password);
  //Cuenta hasta 50 si no se puede conectar lo cancela
  while (WiFi.status() != WL_CONNECTED and contconexion < 50) {
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion < 50) {
    //para usar con ip fija
    //IPAddress ip(192,168,1,180);
    //IPAddress gateway(192,168,1,1);
    //IPAddress subnet(255,255,255,0);
    //WiFi.config(ip, gateway, subnet);

    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println(WiFi.localIP());
    server.begin();  // iniciamos el servidor
  } else {
    Serial.println("");
    Serial.println("Error de conexion");
  }
}

/*----------------------------LOOP----------------------------------*/

void loop() {
  WiFiClient client = server.available();  // Escucha a los clientes entrantes

  if (client) {                     // Si se conecta un nuevo cliente
    Serial.println("New Client.");  //
    String currentLine = "";        //
    while (client.connected()) {    // loop mientras el cliente está conectado
      if (client.available()) {     // si hay bytes para leer desde el cliente
        char c = client.read();     // lee un byte
        Serial.write(c);            // imprime ese byte en el monitor serial
        header += c;
        if (c == '\n') {  // si el byte es un caracter de salto de linea
          // si la nueva linea está en blanco significa que es el fin del
          // HTTP request del cliente, entonces respondemos:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // enciende y apaga el GPIO
            if (header.indexOf("GET /display1") >= 0) {
              Serial.println("GPIO display1");
              display1 = "on";
              display2 = "off";
              digitalWrite(disp2, HIGH);
              digitalWrite(disp1, LOW);

              if (header.indexOf("GET /display1/dis1=0") >= 0) {
                Serial.println("GPIO Num0");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[0][i]);
                }
              } else if (header.indexOf("GET /display1/dis1=1") >= 0) {
                Serial.println("GPIO Num1");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[1][i]);
                }
              } else if (header.indexOf("GET /display1/dis1=2") >= 0) {
                Serial.println("GPIO Num2");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[2][i]);
                }
              } else if (header.indexOf("GET /display1/dis1=3") >= 0) {
                Serial.println("GPIO Num3");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[3][i]);
                }
              } else if (header.indexOf("GET /display1/dis1=4") >= 0) {
                Serial.println("GPIO Num4");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[4][i]);
                }
              } else if (header.indexOf("GET /display1/dis1=5") >= 0) {
                Serial.println("GPIO Num5");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[5][i]);
                }
              } else if (header.indexOf("GET /display1/dis1=6") >= 0) {
                Serial.println("GPIO Num6");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[6][i]);
                }
              } else if (header.indexOf("GET /display1/dis1=7") >= 0) {
                Serial.println("GPIO Num7");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[7][i]);
                }
              } else if (header.indexOf("GET /display1/dis1=8") >= 0) {
                Serial.println("GPIO Num8");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[8][i]);
                }
              } else if (header.indexOf("GET /display1/dis1=9") >= 0) {
                Serial.println("GPIO Num9");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[9][i]);
                }
              } else {
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], LOW);
                }
              }
            } else if (header.indexOf("GET /display2") >= 0) {
              Serial.println("GPIO display2");
              display1 = "off";
              display2 = "on";
              digitalWrite(disp2, LOW);
              digitalWrite(disp1, HIGH);


              if (header.indexOf("GET /display2/dis2=0") >= 0) {
                Serial.println("GPIO Num0");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[0][i]);
                }
              } else if (header.indexOf("GET /display2/dis2=1") >= 0) {
                Serial.println("GPIO Num1");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[1][i]);
                }
              } else if (header.indexOf("GET /display2/dis2=2") >= 0) {
                Serial.println("GPIO Num2");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[2][i]);
                }
              } else if (header.indexOf("GET /display2/dis2=3") >= 0) {
                Serial.println("GPIO Num3");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[3][i]);
                }
              } else if (header.indexOf("GET /display2/dis2=4") >= 0) {
                Serial.println("GPIO Num4");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[4][i]);
                }
              } else if (header.indexOf("GET /display2/dis2=5") >= 0) {
                Serial.println("GPIO Num5");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[5][i]);
                }
              } else if (header.indexOf("GET /display2/dis2=6") >= 0) {
                Serial.println("GPIO Num6");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[6][i]);
                }
              } else if (header.indexOf("GET /display2/dis2=7") >= 0) {
                Serial.println("GPIO Num7");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[7][i]);
                }
              } else if (header.indexOf("GET /display2/dis2=8") >= 0) {
                Serial.println("GPIO Num8");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[8][i]);
                }
              } else if (header.indexOf("GET /display2/dis2=9") >= 0) {
                Serial.println("GPIO Num9");
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], dig[9][i]);
                }
              } else {
                for (i = 0; i < 7; i++) {
                  digitalWrite(seg[i], LOW);
                }
              }
            }
            // Muestra la página web
            client.println(pagina);
            if (display1 == "on") {
              client.println("<p><a href='/display1/dis1=0'><button style='height:50px;width:100px'>0</button></a></p><p><a href='/display1/dis1=1'><button style='height:50px;width:100px'>1</button></a></p>");
              client.println("<p><a href='/display1/dis1=2'><button style='height:50px;width:100px'>2</button></a></p>");
              client.println("<p><a href='/display1/dis1=3'><button style='height:50px;width:100px'>3</button></a></p>");
              client.println("<p><a href='/display1/dis1=4'><button style='height:50px;width:100px'>4</button></a></p>");
              client.println("<p><a href='/display1/dis1=5'><button style='height:50px;width:100px'>5</button></a></p>");
              client.println("<p><a href='/display1/dis1=6'><button style='height:50px;width:100px'>6</button></a></p>");
              client.println("<p><a href='/display1/dis1=7'><button style='height:50px;width:100px'>7</button></a></p>");
              client.println("<p><a href='/display1/dis1=8'><button style='height:50px;width:100px'>8</button></a></p>");
              client.println("<p><a href='/display1/dis1=9'><button style='height:50px;width:100px'>9</button></a></p>");
            }
            if (display2 == "on") {
              client.println("<p><a href='/display2/dis2=0'><button style='height:50px;width:100px'>0</button></a></p><p><a href='/display2/dis2=1'><button style='height:50px;width:100px'>1</button></a></p>");
              client.println("<p><a href='/display2/dis2=2'><button style='height:50px;width:100px'>2</button></a></p>");
              client.println("<p><a href='/display2/dis2=3'><button style='height:50px;width:100px'>3</button></a></p>");
              client.println("<p><a href='/display2/dis2=4'><button style='height:50px;width:100px'>4</button></a></p>");
              client.println("<p><a href='/display2/dis2=5'><button style='height:50px;width:100px'>5</button></a></p>");
              client.println("<p><a href='/display2/dis2=6'><button style='height:50px;width:100px'>6</button></a></p>");
              client.println("<p><a href='/display2/dis2=7'><button style='height:50px;width:100px'>7</button></a></p>");
              client.println("<p><a href='/display2/dis2=8'><button style='height:50px;width:100px'>8</button></a></p>");
              client.println("<p><a href='/display2/dis2=9'><button style='height:50px;width:100px'>9</button></a></p>");
            }
            // la respuesta HTTP temina con una linea en blanco
            client.println();
            break;
          } else {  // si tenemos una nueva linea limpiamos currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // si C es distinto al caracter de retorno de carro
          currentLine += c;      // lo agrega al final de currentLine
        }
      }
    }
    // Limpiamos la variable header
    header = "";
    // Cerramos la conexión
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
