//#include <xc.h>
//#include "adc.h"
//#include "clcd.h"
//
//void init_matrix_keypad(void)
//{
//    TRISB = 0x1F; //(TRISB & 0x01) | 0x1E;
//    RBPU = 0;       //portb pull up enable
//}
//unsigned char scan_key(void)
//{
//    //reading SW1, SW4, SW7, SW10
//    R0 = 0; R1 = 1; R2 = 1;
//    if(C0 == 0)     return 1;
//    if(C1 == 0)     return 4;
//    if(C2 == 0)     return 7;
//    if(C3 == 0)     return 10;
//
//    //reading SW2, SW5, SW8, SW11
//    R0 = 1; R1 = 0; R2 = 1;
//    if(C0 == 0)     return 2;
//    if(C1 == 0)     return 5;
//    if(C2 == 0)     return 8;
//    if(C3 == 0)     return 11;
//
//    //reading SW3, SW6, SW9, SW12
//    R2 = 0; R1 = 1; R0 = 1;
//    if(C0 == 0)     return 3;
//    if(C1 == 0)     return 6;
//    if(C2 == 0)     return 9;
//    if(C3 == 0)     return 12;
//
//    return 0;
//}
//unsigned char read_matrix_keypad(unsigned char detection_type)
//{
//    static unsigned char once = 1;
//    if(detection_type == LEVEL)
//    {
//        return scan_key();
//    }
//    else if(detection_type == STATE_CHANGE)
//    {
//        unsigned char key = scan_key();
//        if((key != ALL_RELEASED) && once)
//        {
//           once = 0;
//           return key;
//        }
//        else if (key == ALL_RELEASED)
//        {
//            once = 1;
//        }
//        return ALL_RELEASED;
//    }
//}
