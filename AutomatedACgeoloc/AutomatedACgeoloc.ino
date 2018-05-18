
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "haha";
const char* password = "8906751991";
const char* mqtt_server = "iot.iandwe.in";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
float dist;
String msg2;
void setup() {
  pinMode(D4, OUTPUT);    
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); 
}
void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msg[i]=(char)payload[i];
  }
  Serial.println();
  if ((String)topic=="Anything/SIT")
  {
    String msg1=(String)msg;
    dist= msg1.toFloat();
    Serial.println(msg1);
  
   if (dist <0.70 && msg2=="onn" ) 
   {
     digitalWrite(D4, HIGH);   
   } 
   else if (dist>0.70)
     {
      digitalWrite(D4, LOW); 
     }
     memset(msg, 0, sizeof(msg));
  }
  if((String)topic=="AConOFF")
  {
    msg2=(String)msg;
    if (msg2=="onn")
    {
      digitalWrite(D4, HIGH); 
      memset(msg, 0, sizeof(msg));
    }
    else if(msg2=="off")
    {
      digitalWrite(D4, LOW);
      memset(msg, 0, sizeof(msg));
    }
  }
  
  }


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");  
     client.subscribe("Anything/SIT");
     client.subscribe("AConOFF");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();
  /*if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world %ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Anything/SIT", msg);*/
}
