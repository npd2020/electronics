#include <ESP8266WiFi.h> //бібліотека для роботи з мікроконтролером є стандартною бібліотекою мікроконтролера
#include <PubSubClient.h> //бібліотека для роботи з MQTT її треба завантажити окремо (див у папці library)

#define LED1 2 // порти виходу керування
#define LED2 0


const char *ssid =  "Xiaomi_6D2F";  // Імя вайфай точки доступу
const char *pass =  "*********"; // Пароль точки вайфай доступу

const char *mqtt_server = "test.mosquitto.org"; // Імя сервера MQTT
const int mqtt_port = 1883; // Порт для підключення до сервера MQTT
const char *mqtt_user = ""; // Логін від сервера
const char *mqtt_pass = ""; // Пароль від сервера
const char *topicled1 = "test1"; // топіки з якими ми працюємо
const char *topicled2 = "test2";

#define BUFFER_SIZE 100

WiFiClient wclient;      
PubSubClient client(wclient, mqtt_server, mqtt_port);

void callback(const MQTT::Publish& pub)     // функція отримання даних від сервера
{
    String payload = pub.payload_string();
    
    if(String(pub.topic()) == topicled2)    //  перевіряємо чи з правильного топіка прийшли дані 
    {
        int stledG = payload.toInt();        //  перетворюємо дані в тип int (вони приходять в типі char*)
        digitalWrite(LED2, stledG);       //  вмикаємо, чи вимикаємо реле залежно від отриманих даних
    }
    
    if(String(pub.topic()) == topicled1)    //  перевіряємо чи з правильного топіка прийшли дані
    {
        int stledG = payload.toInt();        //  перетворюємо дані в тип int (вони приходять в типі char*)
        digitalWrite(LED1, stledG);       //  вмикаємо, чи вимикаємо реле залежно від отриманих даних
    }
}

void setup() {

    pinMode(LED1, OUTPUT);//налаштовуємо порти на вихід даних 
    pinMode(LED2, OUTPUT);
    digitalWrite(LED1,HIGH);//вмикаємо світло при запуску мікроконтролера
    digitalWrite(LED2,HIGH);

    while(true){//намагаємся анулювати попередні налаштування доки не вийде
      if (WiFi.status() != WL_CONNECTED) {//якщо ми не підключені до марежі - підключаємось
          WiFi.begin(ssid, pass);
          
          if (WiFi.waitForConnectResult() != WL_CONNECTED)
              return;
      }

      delay (1000);// затримка для стабільності
      
      // піддключаємося до MQTT сервера
      if (WiFi.status() == WL_CONNECTED) {
          if (!client.connected()) {
              if (client.connect(MQTT::Connect("START").set_auth(mqtt_user, mqtt_pass))) {
              } else {  
              }
          }
          
          if (client.connected()){
            client.loop();
            client.publish(MQTT::Publish(topicled1, "1").set_retain());//анульовуємо попередні налаштування
            client.publish(MQTT::Publish(topicled2, "1").set_retain());          
            client.disconnect();//видключаємося від сервера
            delay(1000);//затримка для стабільносиі
            break;//ми анулювали налаштування, виходима із циклу
          }
      }
    }
    
}

unsigned long last_time=0;
#define timecrack 2000

void loop() {
    // підключаємось до wi-fi
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, pass);
        
        if (WiFi.waitForConnectResult() != WL_CONNECTED)
            return;
    }
    
    // підключаємося до MQTT сервера
    if (WiFi.status() == WL_CONNECTED) {
        if (!client.connected()) {
            if (client.connect(MQTT::Connect("arduinoClient2").set_auth(mqtt_user, mqtt_pass))) {
                client.set_callback(callback);
                client.subscribe(topicled1);                  // підписуємось на топік з даними для першого реле
                client.subscribe(topicled2);                  // підписуємось на топік з даними для другого реле
            } else {
            }
        }
        if (client.connected()){
           client.loop();// зміюємо налаштування в залежності від отриманих даних з сервера
        }
    }

    if(millis()-last_time<timecrack){//кожні дві секунди (timecrack) перезавантажуємо сервер, (на випадок завісання це рятує)
    
      client.disconnect();
      last_time = millis();
        
    }
}
