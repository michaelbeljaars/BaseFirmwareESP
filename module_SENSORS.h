// ********* Settings Level sensor *************
#define pin_level A0
float value_level = 0;
float limit_level_min = 20.0;
float limit_level_max = 250.0;
int avg = 100;

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void measure_level() {
  value_level = 0;

  for (int i = 0; i < avg; i++) {
    value_level += analogRead(pin_level);
  }
  value_level = value_level / avg;

  if (true) {
    if (value_level < limit_level_min) {
      value_level = limit_level_min;
    }

    if (value_level > limit_level_max) {
      value_level = limit_level_max;
    }

    value_level = 1.0 / value_level;
    value_level = round(mapfloat(value_level, (1.0 / limit_level_max), (1.0 / limit_level_min), 100.0, 0.0));
  }

  root["level"] = value_level;
}


void setup_function_SENSORS() {

}

void loop_function_SENSORS() {
  measure_level();
}

