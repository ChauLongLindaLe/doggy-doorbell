#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include "twilio.hpp"
#include <BLEScan.h>
#include <WiFi.h>
//Where credentials are stored
#include "secret.h"

static const char *message = "Woof Woof, Peasant. I need a pee";

Twilio *twilio;

boolean found;
int scan_time = 3;
int doggy_threshold = -60;
int cooldown_time = 5000;

//Change ID to match your LBE tag
char doggyId[] = "0783b03e-XXXX-XXXX-XXXX-XXXXXXXXXXXX";
boolean messageSuccess;

void setup() {
  BLEDevice::init("");
  Serial.begin(115200);
  //  wifi
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  
  // twilio instance
  
  twilio = new Twilio(account_sid, auth_token);
}

void loop() {
  found = false;
  messageSuccess = false;
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  BLEScanResults results = scan->start(scan_time);
  
  for (int i = 0; i < results.getCount(); i++) {
    BLEAdvertisedDevice device = results.getDevice(i);
    if (not device.haveServiceUUID()){continue;}
    if (device.getServiceUUID().toString() == doggyId ) {
      found = true;
      Serial.println("Device found");
      int rssi = device.getRSSI();
      Serial.print("RSSI: ");
      Serial.println(rssi);
      if (rssi > doggy_threshold){
        Serial.println("Gonna send a message");
        send_sms();
        if(messageSuccess){
          Serial.println("Cool down initiated");
          delay(cooldown_time);
        }
      }
    }
  }
  
  if (!found) {Serial.println("Not found this loop");}
  
  delay(1);
}


void send_sms() {
  String response;
  bool success = twilio->send_message(to_number, from_number, message, response);
  if (success) {
    Serial.println("Sent message successfully!");
    messageSuccess = true;
  } else {
    Serial.println(response);
  }
}
