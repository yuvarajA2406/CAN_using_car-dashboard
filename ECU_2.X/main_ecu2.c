/*
 * File:   main_ecu1.c
 * Author: s Yuvaraja
 *
 * Created on 27 November, 2025, 1:53 PM
 */

#include <xc.h>
#include <stdio.h>
#include "adc.h"
#include "digital_keypad.h"
#include "CAN.h"
#include "msg_handler.h"
#include "msg_id.h"

unsigned int speed_val = 0;
unsigned char gear_val = 0;
unsigned int flag=0;

// String buffers
char speed_str[12];

void init_config()
{
    //TRISE = 0x00;
    init_can();
    read_digital_keypad(1);   // initialization only
    init_adc();
}

unsigned int read_speed()
{
    unsigned int adc = read_adc(CHANNEL4);   
    return (adc /10.23);  // scale 0?100
}

void update_gear()
{
    // Expecting mkp to return a key value
    char key = read_digital_keypad(STATE_CHANGE);
    
    
    if(key == SWITCH1)
    {
        if(gear_val < 6)
            gear_val++;
    }
    if(key == SWITCH2)
    {
        if(gear_val > 0)
            gear_val--;
    }
    if(key == SWITCH3)
    {
        gear_val = 7;
        
        if(gear_val == 7)
        {
             if(key == SWITCH2 || key == SWITCH1)
                gear_val = 0;
        }
    }
}

void main(void)
{
    init_config();

    while(1)
    {
        // Read SPEED 
        speed_val = read_speed();
        
        for(int delay = 100; delay--;);
        // Send SPEED over CAN (2 bytes)
        can_transmit(SPEED_MSG_ID, &speed_val, 2);

        

        //Read GEAR
        update_gear();
        
        for(int delay = 100; delay--;);
        // Send GEAR over CAN (1 byte)
        can_transmit(GEAR_MSG_ID, &gear_val, 1);
    }
}

