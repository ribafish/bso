#ifndef __SENSORS_H__
  #include "libsensors.h"
#endif 

float decodeTemperature(int16_t raw){
  
  /**
  * Decode raw temperature to float
  */

  int16_t  tempint;
  uint16_t tempfrac;
  uint16_t absraw;    
  int16_t  sign = 1;
  char     minus = ' ';  
  float temperature;
  
  absraw = raw;
  if (raw < 0) { // Perform 2C's if sensor returned negative data
    absraw = (raw ^ 0xFFFF) + 1;
    sign = -1;
  }
  tempint  = (absraw >> 8) * sign;
  tempfrac = ((absraw>>4) % 16) * 625; // Info in 1/10000 of degree
  minus = ((tempint == 0) & (sign == -1)) ? '-'  : ' ' ;

  temperature = tempint + tempfrac/10000;
  printf ("Temperature = %f\n", temperature);

  return temperature;

}

void printTemperature(float temperature){

  /**
  * Print raw temperature value to string
  */  

  printf ("Temperature = %f\n", temperature);

}