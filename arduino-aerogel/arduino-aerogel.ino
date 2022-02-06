// Basic example using one-shot measurement.
// The call to readThermocoupleTemperature() is blocking for O(100ms)

#include <Adafruit_MAX31856.h>

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(7, 11, 12, 13);
Adafruit_MAX31856 maxthermo2 = Adafruit_MAX31856(9, 11, 12, 13);
Adafruit_MAX31856 maxthermo3 = Adafruit_MAX31856(8, 11, 12, 13);
Adafruit_MAX31856 maxthermo4 = Adafruit_MAX31856(10, 11, 12, 13);
//Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(47, 32, 46, 32);
//Adafruit_MAX31856 maxthermo4 = Adafruit_MAX31856(38, 36, 34, 32);
//Adafruit_MAX31856 maxthermo3 = Adafruit_MAX31856(30, 28, 26, 24);
//Adafruit_MAX31856 maxthermo4 = Adafruit_MAX31856(38, 36, 34, 32);
// use hardware SPI, just pass in the CS pin
/*Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(10);*/

double temp, temp2, temp3, temp4;
double CJ_temp, CJ_temp2, CJ_temp3, CJ_temp4;

char strBuf[150];

//int led = 43;
int relay1 = 2;
int relay2 = 3;
String sdata="";

int pressure_sensor1=A0;
int pressure_sensor2=A6;
int pressure_sensor3=A2;

int pressure_output1, pressure_output2, pressure_output3;
int actual_pressure1, actual_pressure2, actual_pressure3;

int valve1status, valve2status;

int get_pressure(int pressure_pin) {
  int n_loop = 300;
  int i_loop;
  int analog_pressure_single;
  long analog_pressure_avg = 0;

  for(i_loop=0;i_loop<n_loop;i_loop++) {
    analog_pressure_single = analogRead(pressure_pin);
    analog_pressure_avg += analog_pressure_single;
  }
  analog_pressure_avg /= n_loop;

  return analog_pressure_avg;
  //return map(analog_pressure_avg,0,510,0,810);
  //return map_pressure(analog_pressure_avg);

}

/* 
 *  Pressure | analogRead
 *  500      | 437
 *  600      | 462
 *  700      | 500
 *  800      | 540
 *  900      | 570
 *  1000     | 602
 *  1100     | 643
 *  1200     | 680
 *  1300     | 710
 *  y = y0 + (x - x0)*(y1 - y0)/(x1 - x0)
 */
int map_pressure(int analog_read) {
  float actual_pressure;
  float analog_float = (float) analog_read;
  //For 330 ohms:
  /*if (analog_read<437) {
    //actual_pressure = map(analog_read,0,437,0,500);
    actual_pressure = analog_float*500/437;
  } else if (analog_read<462) {
    //actual_pressure = map(analog_read,437,462,500,600);
    actual_pressure = (analog_float-437)*(600-500)/(462-437) + 500;
  } else if (analog_read<500) {
    //actual_pressure = map(analog_read,462,500,600,700);
    actual_pressure = (analog_float-462)*(700-600)/(500-462) + 600;
  } else if (analog_read<540) {
    //actual_pressure = map(analog_read,500,540,700,800);
    actual_pressure = (analog_float-500)*(800-700)/(540-500) + 700;
  } else if (analog_read<570) {
    //actual_pressure = map(analog_read,540,570,800,900);
    actual_pressure = (analog_float-540)*(900-800)/(570-540) + 800;
  } else if (analog_read<602) {
    //actual_pressure = map(analog_read,570,602,900,1000);
    actual_pressure = (analog_float-570)*(1000-900)/(602-570) + 900;
  } else if (analog_read<643) {
    //actual_pressure = map(analog_read,602,643,1000,1100);
    actual_pressure = (analog_float-602)*(1100-1000)/(643-602) + 1000;
  } else if (analog_read<680) {
    //actual_pressure = map(analog_read,643,680,1100,1200);
    actual_pressure = (analog_float-643)*(1200-1100)/(680-643) + 1100;
  } else if (analog_read<710) {
    //actual_pressure = map(analog_read,680,710,1200,1300);
    actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else {
    actual_pressure = map(analog_read,680,710,1200,1300);
  }*/

  //For 150 ohms:
  if (analog_read<209) {
    actual_pressure = map(analog_read,0,209,0,654);
    //actual_pressure = analog_float*654/209;
  } else if (analog_read<216) {
    actual_pressure = map(analog_read,209,216,654,705);
    //actual_pressure = (analog_float-437)*(600-500)/(462-437) + 500;
  } else if (analog_read<223) {
    actual_pressure = map(analog_read,216,223,705,751);
    //actual_pressure = (analog_float-462)*(700-600)/(500-462) + 600;
  } else if (analog_read<228) {
    actual_pressure = map(analog_read,223,228,751,780);
    //actual_pressure = (analog_float-500)*(800-700)/(540-500) + 700;
  } else if (analog_read<240) {
    actual_pressure = map(analog_read,228,240,780,852);
    //actual_pressure = (analog_float-540)*(900-800)/(570-540) + 800;
  //Values from now on are more reliable:
  } else if (analog_read<247) {
    actual_pressure = map(analog_read,240,247,852,900);
    //actual_pressure = (analog_float-570)*(1000-900)/(602-570) + 900;
  } else if (analog_read<255) {
    actual_pressure = map(analog_read,247,255,900,950);
    //actual_pressure = (analog_float-570)*(1000-900)/(602-570) + 900;
  } else if (analog_read<263) {
    actual_pressure = map(analog_read,255,263,950,1000);
    //actual_pressure = (analog_float-602)*(1100-1000)/(643-602) + 1000;
  } else if (analog_read<270) {
    actual_pressure = map(analog_read,263,270,1000,1050);
    //actual_pressure = (analog_float-643)*(1200-1100)/(680-643) + 1100;
  } else if (analog_read<279) {
    actual_pressure = map(analog_read,270,279,1050,1100);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<287) {
    actual_pressure = map(analog_read,279,287,1100,1150);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<294) {
    actual_pressure = map(analog_read,287,294,1150,1200);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<303) {
    actual_pressure = map(analog_read,294,303,1200,1250);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<310) {
    actual_pressure = map(analog_read,303,310,1250,1300);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<319) {
    actual_pressure = map(analog_read,310,319,1300,1350);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<326) {
    actual_pressure = map(analog_read,319,326,1350,1400);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<333) {
    actual_pressure = map(analog_read,326,333,1400,1450);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<340) {
    actual_pressure = map(analog_read,333,340,1450,1500);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<348) {
    actual_pressure = map(analog_read,340,348,1500,1550);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<357) {
    actual_pressure = map(analog_read,348,357,1550,1600);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<373) {
    actual_pressure = map(analog_read,357,373,1600,1700);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<380) {
    actual_pressure = map(analog_read,373,380,1700,1750);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<389) {
    actual_pressure = map(analog_read,380,389,1750,1800);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<397) {
    actual_pressure = map(analog_read,389,397,1800,1850);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<404) {
    actual_pressure = map(analog_read,397,404,1850,1900);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<412) {
    actual_pressure = map(analog_read,404,412,1900,1950);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<420) {
    actual_pressure = map(analog_read,412,420,1950,2000);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<429) {
    actual_pressure = map(analog_read,420,429,2000,2050);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<435) {
    actual_pressure = map(analog_read,429,435,2050,2100);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<442) {
    actual_pressure = map(analog_read,435,442,2100,2150);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<454) {
    actual_pressure = map(analog_read,442,454,2150,2200);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<467) {
    actual_pressure = map(analog_read,454,467,2200,2250);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<480) {
    actual_pressure = map(analog_read,467,480,2250,2300);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<497) {
    actual_pressure = map(analog_read,480,497,2300,2350);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<513) {
    actual_pressure = map(analog_read,497,513,2350,2400);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<531) {
    actual_pressure = map(analog_read,513,531,2400,2450);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else if (analog_read<546) {
    actual_pressure = map(analog_read,531,546,2450,2500);
    //actual_pressure = (analog_float-680)*(1300-1200)/(710-680) + 1200;
  } else {
    actual_pressure = map(analog_read,531,546,2450,2500);
  }

  return (int) actual_pressure;

}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("MAX31856 thermocouple test");

  maxthermo.begin();
  maxthermo2.begin();
  maxthermo3.begin();
  maxthermo4.begin();

  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);
  maxthermo2.setThermocoupleType(MAX31856_TCTYPE_K);
  maxthermo3.setThermocoupleType(MAX31856_TCTYPE_K);
  maxthermo4.setThermocoupleType(MAX31856_TCTYPE_K);

  Serial.print("Thermocouple 1 type: ");
  switch (maxthermo.getThermocoupleType() ) {
    case MAX31856_TCTYPE_B: Serial.println("B Type"); break;
    case MAX31856_TCTYPE_E: Serial.println("E Type"); break;
    case MAX31856_TCTYPE_J: Serial.println("J Type"); break;
    case MAX31856_TCTYPE_K: Serial.println("K Type"); break;
    case MAX31856_TCTYPE_N: Serial.println("N Type"); break;
    case MAX31856_TCTYPE_R: Serial.println("R Type"); break;
    case MAX31856_TCTYPE_S: Serial.println("S Type"); break;
    case MAX31856_TCTYPE_T: Serial.println("T Type"); break;
    case MAX31856_VMODE_G8: Serial.println("Voltage x8 Gain mode"); break;
    case MAX31856_VMODE_G32: Serial.println("Voltage x8 Gain mode"); break;
    default: Serial.println("Unknown"); break;
  }

  Serial.print("Thermocouple 2 type: ");
  switch (maxthermo2.getThermocoupleType() ) {
    case MAX31856_TCTYPE_B: Serial.println("B Type"); break;
    case MAX31856_TCTYPE_E: Serial.println("E Type"); break;
    case MAX31856_TCTYPE_J: Serial.println("J Type"); break;
    case MAX31856_TCTYPE_K: Serial.println("K Type"); break;
    case MAX31856_TCTYPE_N: Serial.println("N Type"); break;
    case MAX31856_TCTYPE_R: Serial.println("R Type"); break;
    case MAX31856_TCTYPE_S: Serial.println("S Type"); break;
    case MAX31856_TCTYPE_T: Serial.println("T Type"); break;
    case MAX31856_VMODE_G8: Serial.println("Voltage x8 Gain mode"); break;
    case MAX31856_VMODE_G32: Serial.println("Voltage x8 Gain mode"); break;
    default: Serial.println("Unknown"); break;
  }

  Serial.print("Thermocouple 3 type: ");
  switch (maxthermo3.getThermocoupleType() ) {
    case MAX31856_TCTYPE_B: Serial.println("B Type"); break;
    case MAX31856_TCTYPE_E: Serial.println("E Type"); break;
    case MAX31856_TCTYPE_J: Serial.println("J Type"); break;
    case MAX31856_TCTYPE_K: Serial.println("K Type"); break;
    case MAX31856_TCTYPE_N: Serial.println("N Type"); break;
    case MAX31856_TCTYPE_R: Serial.println("R Type"); break;
    case MAX31856_TCTYPE_S: Serial.println("S Type"); break;
    case MAX31856_TCTYPE_T: Serial.println("T Type"); break;
    case MAX31856_VMODE_G8: Serial.println("Voltage x8 Gain mode"); break;
    case MAX31856_VMODE_G32: Serial.println("Voltage x8 Gain mode"); break;
    default: Serial.println("Unknown"); break;
  }

  Serial.print("Thermocouple 4 type: ");
  switch (maxthermo4.getThermocoupleType() ) {
    case MAX31856_TCTYPE_B: Serial.println("B Type"); break;
    case MAX31856_TCTYPE_E: Serial.println("E Type"); break;
    case MAX31856_TCTYPE_J: Serial.println("J Type"); break;
    case MAX31856_TCTYPE_K: Serial.println("K Type"); break;
    case MAX31856_TCTYPE_N: Serial.println("N Type"); break;
    case MAX31856_TCTYPE_R: Serial.println("R Type"); break;
    case MAX31856_TCTYPE_S: Serial.println("S Type"); break;
    case MAX31856_TCTYPE_T: Serial.println("T Type"); break;
    case MAX31856_VMODE_G8: Serial.println("Voltage x8 Gain mode"); break;
    case MAX31856_VMODE_G32: Serial.println("Voltage x8 Gain mode"); break;
    default: Serial.println("Unknown"); break;
  }

  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(pressure_sensor1,INPUT);
  pinMode(pressure_sensor2,INPUT);
  pinMode(pressure_sensor3,INPUT);

// switch relays off
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);

}

void loop() {
  // Check and print any faults
  /*uint8_t fault1 = maxthermo.readFault();
  if (fault1) {
    if (fault1 & MAX31856_FAULT_CJRANGE) Serial.println("Cold Junction Range 1 Fault");
    if (fault1 & MAX31856_FAULT_TCRANGE) Serial.println("Thermocouple Range 1 Fault");
    if (fault1 & MAX31856_FAULT_CJHIGH)  Serial.println("Cold Junction High 1 Fault");
    if (fault1 & MAX31856_FAULT_CJLOW)   Serial.println("Cold Junction Low 1 Fault");
    if (fault1 & MAX31856_FAULT_TCHIGH)  Serial.println("Thermocouple High 1 Fault");
    if (fault1 & MAX31856_FAULT_TCLOW)   Serial.println("Thermocouple Low 1 Fault");
    if (fault1 & MAX31856_FAULT_OVUV)    Serial.println("Over/Under Voltage 1 Fault");
    if (fault1 & MAX31856_FAULT_OPEN)    Serial.println("Thermocouple Open 1 Fault");
  }*/

  //Serial.print("Cold Junction 1 Temp: ");
  //Serial.println(maxthermo.readCJTemperature());
  CJ_temp = maxthermo.readCJTemperature();

  //Serial.print("Thermocouple 1 Temp: ");
  //Serial.println(maxthermo.readThermocoupleTemperature());
  temp = maxthermo.readThermocoupleTemperature();

  //Serial.print("Cold Junction 2 Temp: ");
  //Serial.println(maxthermo2.readCJTemperature());
  CJ_temp2 = maxthermo2.readCJTemperature();

  //Serial.print("Thermocouple 2 Temp: ");
  //Serial.println(maxthermo2.readThermocoupleTemperature());
  temp2 = maxthermo2.readThermocoupleTemperature();

  //Serial.print("Cold Junction 3 Temp: ");
  //Serial.println(maxthermo.readCJTemperature());
  CJ_temp3 = maxthermo3.readCJTemperature();

  //Serial.print("Thermocouple 3 Temp: ");
  //Serial.println(maxthermo.readThermocoupleTemperature());
  temp3 = maxthermo3.readThermocoupleTemperature();

  //Serial.print("Cold Junction 4 Temp: ");
  //Serial.println(maxthermo2.readCJTemperature());
  CJ_temp4 = maxthermo4.readCJTemperature();

  //Serial.print("Thermocouple 4 Temp: ");
  //Serial.println(maxthermo2.readThermocoupleTemperature());
  temp4 = maxthermo4.readThermocoupleTemperature();

//Read pressure
  pressure_output1 = get_pressure(pressure_sensor1);
  pressure_output2 = get_pressure(pressure_sensor2);
  pressure_output3 = get_pressure(pressure_sensor3);
//Map pressure
  actual_pressure1 = map_pressure(pressure_output1);
  actual_pressure2 = map_pressure(pressure_output2);
  actual_pressure3 = map_pressure(pressure_output3);

  Serial.print("Sensor outputs (T1,T2,T3,T4,P1,P2,P3,Y1,Y2): ");
  Serial.print(temp);
  Serial.print(" ");
  Serial.print(temp2);
  Serial.print(" ");
  Serial.print(temp3);
  Serial.print(" ");
  Serial.print(temp4);
  Serial.print(" ");
  //Serial.print(pressure_output1);
  //Serial.print("/");
  Serial.print(actual_pressure1);
  Serial.print(" ");
  //Serial.print(pressure_output2);
  //Serial.print("/");
  Serial.print(actual_pressure2);
  Serial.print(" ");
  //Serial.print(pressure_output3);
  //Serial.print("/");
  Serial.print(actual_pressure3);
  Serial.print(" ");
  Serial.print(valve1status);
  Serial.print(" ");
  Serial.println(valve2status);

  //sprintf(strBuf, "Temperatures: %f %f\n", temp, temp2);
  //Serial.print(strBuf);

  // listen to serial input and act accordingly
  byte ch;
  if (Serial.available()) {
    ch = Serial.read();
    sdata += (char)ch;
    sdata.trim();
    // Process command in sdata.
    switch( sdata.charAt(0) ) {
      case 's':
        valve1status = 1;
        digitalWrite(relay1,HIGH);
        break;
      case 't':
        valve1status = 0;
        digitalWrite(relay1,LOW);
        break;
      case 'w':
        valve2status = 1;
        digitalWrite(relay2,HIGH);
        break;
      case 'k':
        valve2status = 0;
        digitalWrite(relay2,LOW);
        break;
     //default: Serial.println(sdata);
    }
    sdata = ""; // Clear the string ready for the next command.
  }

  delay(100);

}
