/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 * Authors: Ben Heberlein and Sanika Dongre
 *
 * ========================================
*/
#include "project.h"
#include "stdlib.h"

#define STEP_DELAY 10
#define NUM_STEPS 15

#define MOTOR_DELAY_F 800000
#define MOTOR_DELAY_R 450000

#define REVERSE 0
#define FORWARD 1

#define ZERO_P 1305//1295
#define ZERO_N 1320//1310

#define POS_30 1200
//#define POS_30 1150

#define NEG_30 1400
//#define NEG_30_N 1680

int16_t acc_value = 0;
uint8_t direction = REVERSE;

uint8_t top_flag = 0;
uint8_t bottom_flag = 0;
uint8_t move_up = 0;
uint8_t move_down = 0;

CY_ISR(ldr_top) {
    top_flag = 1;    
    bottom_flag = 0;
}

CY_ISR(ldr_bottom) {
    bottom_flag = 1;
    top_flag = 0;        
}

CY_ISR(up) {
    slider_off();
    Timer_1_Stop();
    Timer_1_Init();
}

CY_ISR(down) {
    slider_off();
    Timer_2_Stop();
    Timer_2_Init();
}

void meas_acc() {
    acc_value = ADC_SAR_1_GetResult16();
            
    /*LCD_Char_1_Position(0,7);
    LCD_Char_1_PrintString("        ");
    LCD_Char_1_Position(0,7);
    LCD_Char_1_PrintNumber(acc_value); */
}

void zero_accelerometer() {
    
    while (acc_value < ZERO_P || acc_value > ZERO_N) {
        meas_acc();
        /* Go up */
        if (acc_value > ZERO_N) {
            direction = REVERSE;
            reverse(1);
            CyDelay(10);
        /* Go down */
        } else if (acc_value < ZERO_P) {
            direction = FORWARD;
            forward(1);
            CyDelay(10);
        } else {
            break;   
        }
    }
    
    if (direction == FORWARD) {
        forward(5);   
    }
    
    if (direction == REVERSE) {
        reverse(2);   
    }  
}

void pos_accelerometer() {
  
    while (acc_value > POS_30) { //|| acc_value > POS_30_N) {
        meas_acc();
        /* Go up */

        if (acc_value > POS_30) {
            direction = REVERSE;
            reverse(1);
            CyDelay(10);
        /* Go down */
        } //else
        #if 0
        if (acc_value < POS_30) {
            direction = FORWARD;
            forward(1);
            CyDelay(10);
        } else {
            break;   
        } 
        #endif
    }
    
   /* if (direction == FORWARD) {
        forward(3);   
    } */
    
    if (direction == REVERSE) {
        reverse(1);   
    }
    
}

void neg_accelerometer() {
    
    while (acc_value < NEG_30) {// || acc_value > NEG_30_N) {
        meas_acc();
        /* Go up */
        /*if (acc_value > NEG_30) {
            direction = REVERSE;
            reverse(1);
            CyDelay(10); */
        /* Go down */
        //} else 
    
        if (acc_value < NEG_30) {
            direction = FORWARD;
            forward(1);
            CyDelay(10);
        //} else {
        //    break; 
        }
    }
    
    if (direction == FORWARD) {
        forward(3);   
    }
    
    /*if (direction == REVERSE) {
        reverse(1);   
    }*/
    
}

void step1() {
    Pin_3_4_Blue_Write(0);
    Pin_3_3_Orange_Write(1);
    Pin_0_5_Pink_Write(1);
    Pin_0_3_Yellow_Write(0);
    CyDelay(STEP_DELAY);
    meas_acc();
}

void step4() {
    Pin_3_4_Blue_Write(0);
    Pin_3_3_Orange_Write(1);
    Pin_0_5_Pink_Write(0);
    Pin_0_3_Yellow_Write(1);
    CyDelay(STEP_DELAY);    
    meas_acc();
}

void step3() {
    Pin_3_4_Blue_Write(1);
    Pin_3_3_Orange_Write(0);
    Pin_0_5_Pink_Write(0);
    Pin_0_3_Yellow_Write(1);
    CyDelay(STEP_DELAY);
    meas_acc();
}

void step2() {
    Pin_3_4_Blue_Write(1);
    Pin_3_3_Orange_Write(0);
    Pin_0_5_Pink_Write(1);
    Pin_0_3_Yellow_Write(0);
    CyDelay(STEP_DELAY);
    meas_acc();
}

void forward(int n) {
    for (int i = 0; i < n; i++) {
        step1();
        step2();
        step3();
        step4();
    }
}

void reverse(int n) {
    for (int i = 0; i < n; i++) {
        step4();        
        step3();
        step2();        
        step1();
    }
}

void slider_up() {
    Pin_3_1_MotorControlB_Write(0);
    Pin_3_0_MotorControlA_Write(0);
    Pin_3_0_MotorControlA_Write(1);
    Timer_1_WriteCounter(MOTOR_DELAY_F);
    Timer_1_Enable();
    //CyDelay(MOTOR_DELAY_F);
    //Pin_3_1_MotorControlB_Write(0);
    //Pin_3_0_MotorControlA_Write(0);
  
}

void slider_down() {
    Pin_3_0_MotorControlA_Write(0);
    Pin_3_1_MotorControlB_Write(0);
    Pin_3_1_MotorControlB_Write(1);
    Timer_2_WriteCounter(MOTOR_DELAY_R);
    Timer_2_Enable();
    //CyDelay(MOTOR_DELAY_R);
    //Pin_3_1_MotorControlB_Write(0);
    //Pin_3_0_MotorControlA_Write(0);      
}

void slider_off() {
    Pin_3_0_MotorControlA_Write(0);
    Pin_3_1_MotorControlB_Write(0);       
}

void step_forward() {
    step1();
}

void step_back() {
    step2();   
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    LCD_Char_1_Start();
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
    Timer_1_Init();
    Timer_2_Init();
    Timer_1_WritePeriod(MOTOR_DELAY_F);
    Timer_2_WritePeriod(MOTOR_DELAY_R);
    
    isr_top_StartEx(ldr_top);
    isr_bottom_StartEx(ldr_bottom);
    isr_up_StartEx(up);
    isr_down_StartEx(down);
    
    zero_accelerometer();
    LCD_Char_1_Position(1,7);
    LCD_Char_1_PrintString("        ");
    LCD_Char_1_Position(1,7);
    LCD_Char_1_PrintString("LEVEL");
    CyDelay(1500);
    neg_accelerometer();        
    LCD_Char_1_Position(1,7);
    LCD_Char_1_PrintString("        ");
    LCD_Char_1_Position(1,7);
    LCD_Char_1_PrintString("-30 DEG");
    CyDelay(1500);       
    zero_accelerometer();
    LCD_Char_1_Position(1,7);
    LCD_Char_1_PrintString("        ");
    LCD_Char_1_Position(1,7);
    LCD_Char_1_PrintString("LEVEL");
    CyDelay(1500);
    pos_accelerometer();        
    LCD_Char_1_Position(1,7);
    LCD_Char_1_PrintString("        ");
    LCD_Char_1_Position(1,7);
    LCD_Char_1_PrintString("+30 DEG");
    CyDelay(1500);
    zero_accelerometer();
    LCD_Char_1_Position(1,7);
    LCD_Char_1_PrintString("        ");
    LCD_Char_1_Position(1,7);
    LCD_Char_1_PrintString("LEVEL");
    CyDelay(3000);

    //forward(NUM_STEPS/3);
    for (;;) {        
        for (int i = 0; i < NUM_STEPS; i++) {            
            reverse(1);  
            if (top_flag) {
                slider_up();
                LCD_Char_1_Position(1,7);
                LCD_Char_1_PrintString("        ");
                LCD_Char_1_Position(1,7);
                LCD_Char_1_PrintString("TOP");
            }
            if (bottom_flag) {
                slider_down();
                LCD_Char_1_Position(1,7);
                LCD_Char_1_PrintString("        ");
                LCD_Char_1_Position(1,7);
                LCD_Char_1_PrintString("BOTTOM");
            }
            
        }
        
        for (int i = 0; i < NUM_STEPS; i++) {         
            forward(1);
            if (top_flag) {
                slider_up();
                LCD_Char_1_Position(1,7);
                LCD_Char_1_PrintString("        ");
                LCD_Char_1_Position(1,7);
                LCD_Char_1_PrintString("TOP");
            }
            if (bottom_flag) {
                slider_down();
                LCD_Char_1_Position(1,7);
                LCD_Char_1_PrintString("        ");
                LCD_Char_1_Position(1,7);
                LCD_Char_1_PrintString("BOTTOM");
            }
        }
    }
}

/* [] END OF FILE */
