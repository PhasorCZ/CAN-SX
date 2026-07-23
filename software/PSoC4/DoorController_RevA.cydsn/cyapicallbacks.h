/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef CYAPICALLBACKS_H
#define CYAPICALLBACKS_H
    

    #define COMPARATOR_REFFERENCE_ENABLE()      EN_1_Write(1)
    #define COMPARATOR_AND_DEBOUNCER_ENABLE()   EN_2_Write(1)
    #define VARIABLE_RESISTOR_VCC_ENABLE()      EN_3_Write(1)
    #define POWER_WINDOW_SWITCH_VCC_ENABLE()    EN_4_Write(1)
    
    #define COMPARATOR_REFFERENCE_DISABLE()     EN_1_Write(0)
    #define COMPARATOR_AND_DEBOUNCER_DISABLE()  EN_2_Write(0)
    #define VARIABLE_RESISTOR_VCC_DISABLE()     EN_3_Write(0)
    #define POWER_WINDOW_SWITCH_VCC_DISABLE()   EN_4_Write(0)
    
    #define POWER_WINDOW_MOTOR_DOWN_ENABLE()    PWM_DOWN_INH_Write(1)
    #define POWER_WINDOW_MOTOR_UP_ENABLE()      PWM_UP_INH_Write(1)
    
    #define POWER_WINDOW_MOTOR_DOWN_DISABLE()   PWM_DOWN_INH_Write(0)
    #define POWER_WINDOW_MOTOR_UP_DISABLE()     PWM_UP_INH_Write(0)
    
#endif /* CYAPICALLBACKS_H */   
/* [] */
