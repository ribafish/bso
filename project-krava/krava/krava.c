/*
*__author: blaz__
*__date: 2016-03-07__
*__assigment1__
*/
#include <stdio.h>
#include <stdlib.h>
#include "contiki.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"
#include "dev/i2cmaster.h"  // Include IC driver
#include "dev/tmp102.h"     // Include sensor driver
#include "../lib/libsensors.h"
#include "../lib/libmessage.h"


/*
* Krava
*/
PROCESS(krava, "krava");
AUTOSTART_PROCESSES(&krava);
PROCESS_THREAD(krava, ev, data)
{	
	//static variables
	static struct etimer et;
	static uint16_t counter = 0;
	static int16_t temperature;
	static float decoded_temperature;
	static int value = 1;
	tmp102_init();

	printf("Test0\n");

	//Our process
	PROCESS_EXITHANDLER(goto exit;)
	PROCESS_BEGIN();
	SENSORS_ACTIVATE(button_sensor);	
	while(1) {

		etimer_set(&et, CLOCK_SECOND*1);
		printf("Test1\n");
		
		if(etimer_expired(&et)){
			printf("Test2\n");
			// temperature = readTemperature();
			decoded_temperature = decodeTemperature(tmp102_read_temp_raw());
			printTemperature(decoded_temperature);
			
		}
		/*
		

		PROCESS_WAIT_EVENT();
		if(((ev==sensors_event) && (data == &button_sensor))){			
			
			//Toggle value we add -1 or +1
			value = -value;
		
		}else if(etimer_expired(&et)){

			leds_off(LEDS_ALL);

			//Add value to counter
			counter+=value;
			printf("%i: ", counter);			

			//Change led colors
			int bit1 = ((counter & ( 1 << 0 )) >> 0);
			int bit2 = ((counter & ( 1 << 1 )) >> 1);
			int bit3 = ((counter & ( 1 << 2 )) >> 2);
						
			printf("%i %i %i\n",bit3,bit2,bit1);			
			
			if(bit3 == 1){
				leds_on(LEDS_RED); //3 bit - 4
			}
			if(bit2 == 1){
				leds_on(LEDS_GREEN); //2 bit - 2
			}
			if(bit1 == 1){
				leds_on(LEDS_BLUE); //1 bit - 1						
			}

			//mod 128
			counter=counter%128;			
			etimer_reset(&et);


		}*/				
	}
	exit:
		leds_off(LEDS_ALL);
		PROCESS_END();
}