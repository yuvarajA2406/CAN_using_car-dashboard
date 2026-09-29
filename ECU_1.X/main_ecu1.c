/*
 * File:   main_ecu1.c
 * Author: s Yuvaraja
 *
 * Created on 27 November, 2025, 1:53 PM
 */

#include <xc.h>
#include "adc.h"
#include "clcd.h"
#include "digital_keypad.h"
#include "CAN.h"
#include "msg_handler.h"
#include "msg_id.h"

unsigned int rpm_val = 0;
unsigned char indicator_val = 0;

// String buffers
char rpm_str[6];

void init_config()
{
    TRISB = 0x00;
    PORTB = 0x00;

    init_can();
    read_digital_keypad(1);   // initialization only
    init_adc();
}

unsigned int read_rpm()
{
    unsigned int adc_value = read_adc(CHANNEL4)/10.23;
    return adc_value ;
}

void update_indicators()
{
    // Expecting mkp to return a key value
    char key = read_digital_keypad(STATE_CHANGE);

    if(key == SWITCH1)
        indicator_val = 1;
    else if(key == SWITCH2)
        indicator_val = 2;
    else if(key == SWITCH3)
        indicator_val = 3;
    else if(key == SWITCH4)
        indicator_val = 0;
}

void main(void)
{
    init_config();

    while(1)
    {
        //Read RPM 
        rpm_val = read_rpm();

        // Send RPM over CAN (2 bytes)
        can_transmit(RPM_MSG_ID, &rpm_val, 1);

        for(int delay = 100; delay--;);

        // Read Indicators
        update_indicators();

        // Send indicators over CAN (1 byte)
        can_transmit(INDICATOR_MSG_ID, &indicator_val, 1);

        for(int delay = 200; delay--;);
    }
}

