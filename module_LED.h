// ********* Settings LED *************
#define pin_LED D5
int limit_light_off = 300; // limt to switch off
int limit_light_on = 200; // limti to switch on

void setup_function_LED() {
  pinMode(pin_LED, OUTPUT);
}

void loop_function_LED() {
  int lv = (int)root["Light"];
  
  if (lv < limit_light_on) {
    digitalWrite(pin_LED, HIGH);
  }
  else if (lv > limit_light_off) {
    digitalWrite(pin_LED, LOW);
  }

}

