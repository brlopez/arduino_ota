#include <Arduino.h>
#include <esp32FOTA.hpp>
#include <credentials.h>

esp32FOTA FOTA;

void setup_wifi()
{
  Serial.print("Connecting to " );
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println(WiFi.localIP());  
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  {
    auto cfg = FOTA.getConfig();
    cfg.name          = "esp32-fota-http";
    cfg.manifest_url  = FOTA_MANIFEST_URL;
    cfg.sem           = SemverClass( 1, 0, 3 ); // major, minor, patch
    cfg.check_sig     = false; // verify signed firmware with rsa public key
    cfg.unsafe        = true; // disable certificate check when using TLS
    //cfg.root_ca       = MyRootCA;
    //cfg.pub_key       = MyRSAKey;
    //cfg.use_device_id = false;
    FOTA.setConfig( cfg );
  }
}

void loop() {
  int t0 = micros();
  FOTA.handle();
  int t1 = micros() - t0;
  Serial.printf("OTA check duration: %u microseconds\n", t1);
  // if (updatedNeeded)
  // {
  //   esp32FOTA.execOTA();
  // }
  delay(2000);
  Serial.println("Version 1.0.3");
}

