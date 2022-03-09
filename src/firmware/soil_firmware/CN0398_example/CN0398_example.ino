#include <SPI.h>
#include "CN0398.h"
#include "Communication.h"

bool ask_user_prompts = true;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  SPI.setDataMode(SPI_MODE3); //CPHA = CPOL = 1    MODE = 3

  pinMode(CS_PIN, OUTPUT);

  CN0398_setup();
  CN0398_init();
  delay(500);
  Serial.println(F("Initialization complete!\n"));

  Serial.println(F("Do you want to perform pH calibration [y/N]?"));

  
}



void loop() {
  
  if(ask_user_prompts) {
    ask_user_prompts = false;
    while (Serial.available() == 0){
      
    }
    
    char response = Serial.read();
    Serial.println(response);
          
          if (response == 'y' || response == 'Y') {
              Serial.println(F("Do you want to calibrate offset voltage [y/N]?"));
    
              while (Serial.available() == 0) {
                Serial.println("hello");
              }
              response = Serial.read();
              Serial.println(response);
              CN0398_calibrate_ph(response);
        } else {
            CN0398_set_use_nernst(true);
            Serial.println("Do you want to load default calibration?[y/N]. If not[N], the Nernst equation will be used.");
            response = Serial.read();
            if (response == 'y' || response == 'Y') {
              CN0398_set_use_nernst(false);
            }
            Serial.println();
        }
  }
  /*
  delay(DISPLAY_REFRESH);
  CN0398_set_data();
  CN0398_display_data();
  */
}
  
