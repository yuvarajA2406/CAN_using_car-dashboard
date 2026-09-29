#include <xc.h>
#include "CAN.h"
#include "msg_handler.h"
#include "msg_id.h"
#include "clcd.h"

/* Simple software delay for LED blinking */
void blink_delay(void)
{
    for (uint32_t i = 0; i < 50000; i++);   // adjust for blink speed
}

/*Handle incoming messages*/
void handle_rpm_data(uint8_t *data, uint8_t len) {
    unsigned char arr[5];
    uint16_t rpm_set = (*data) * 60;

    arr[0] = (rpm_set / 1000) + '0';
    arr[1] = ((rpm_set / 100) % 10) + '0';
    arr[2] = ((rpm_set / 10) % 10) + '0';
    arr[3] = (rpm_set % 10) + '0';
    arr[4] = '\0';
    clcd_print(arr, LINE2(0));
}

void handle_speed_data(uint8_t *data, uint8_t len) {
    unsigned char arr[4];
    uint8_t speed = *data;

    arr[0] = ((speed / 100) % 10) + '0';
    arr[1] = ((speed / 10) % 10) + '0';
    arr[2] = (speed % 10) + '0';
    arr[3] = '\0';
    clcd_print(arr, LINE2(10));
}

void handle_gear_data(uint8_t *data, uint8_t len) {
    uint8_t gear = *data;
    
    if (gear == 0) 
    {
        clcd_putch(' ', LINE2(14));
        clcd_putch('N', LINE2(14));
    } 
    else if (gear == 6) 
    {
        clcd_putch('R', LINE2(14));
    } 
    else if (gear == 7) 
    {
        clcd_putch('C', LINE2(14));
        //gear = 0;
    }
    else 
    {
        clcd_putch(gear + '0', LINE2(14));
    }
}

/*Indicator Handler WITH BLINK*/
void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    uint8_t ind = data[0];

    switch (ind) {
        case 1: // LEFT
//            LATBbits.LATB7 = 0;
//            LATBbits.LATB0 ^= 1;   // blink LEFT LED
            RB7 = 0;
            RB0 ^= 1;
            clcd_print("<--", LINE2(5));
            clcd_print(" ", LINE2(8));
            blink_delay();
            break;

        case 2: // RIGHT
//            LATBbits.LATB0 = 0;
//            LATBbits.LATB7 ^= 1;   // blink RIGHT LED
            RB0 = 0;
            RB7 ^= 1;
            clcd_print("-->", LINE2(5));          
            clcd_print(" ", LINE2(8));
            blink_delay();
            break;

        case 3: // HAZARD
//            LATBbits.LATB0 ^= 1;
//            LATBbits.LATB7 ^= 1;
            RB7 ^= 1;
            RB0 ^= 1;
            clcd_print("<-->", LINE2(5));
            blink_delay();
            break;

        default: // OFF
//            LATBbits.LATB0 = 0;
//            LATBbits.LATB7 = 0;
            RB7 = 0;
            RB0 = 0;
            clcd_print("    ", LINE2(5));
            break;
    }
}

/* Main CAN process function*/
void process_canbus_data()
{
    unsigned int msg_id;
    uint8_t data;
    uint8_t len;

    /* Receive CAN message */
    can_receive(&msg_id, &data, &len);

    //if(len == 0) return;  // no data

    /* Dispatch handlers */
    switch(msg_id)
    {
        case RPM_MSG_ID:
            handle_rpm_data(&data, len);
            break;

        case SPEED_MSG_ID:
            handle_speed_data(&data, len);
            break;

        case GEAR_MSG_ID:
            handle_gear_data(&data, len);
            break;

        case INDICATOR_MSG_ID:
            handle_indicator_data(&data, len);
            break;

        default:
            break;
    }
}

void main(void)
{
    TRISBbits.TRISB0 = 0;  // RIGHT indicator pin
    TRISBbits.TRISB7 = 0;  // LEFT indicator pin
    LATB = 0x00;

    init_can();
    init_clcd();

    while(1)
    {
        clcd_print("RPM  IND  SPD G ", LINE1(0));
        process_canbus_data();
    }
}
