/*
 * lmm83t064d3.h
 *
 *  Created on: Jan 10, 2017
 *      Author: toquica
 */

#ifndef LMM83T064D3_H_
#define LMM83T064D3_H_
#ifndef byte
    typedef unsigned char byte;
#endif

#include "functions.h"

#define LCD_DB0     PTGD_PTGD6    // LCD Data Bit 0 in PORT G pin 6
#define LCD_DB1     PTGD_PTGD5    // LCD Data Bit 1 in PORT G pin 5
#define LCD_DB2     PTGD_PTGD3    // LCD Data Bit 2 in PORT G pin 4
#define LCD_DB3     PTDD_PTDD1    // LCD Data Bit 3 in PORT D pin 1
#define LCD_DB4     PTDD_PTDD0    // LCD Data Bit 4 in PORT D pin 0
#define LCD_DB5     PTBD_PTBD3    // LCD Data Bit 5 in PORT B pin 3
#define LCD_DB6     PTBD_PTBD2    // LCD Data Bit 6 in PORT B pin 2
#define LCD_DB7     PTBD_PTBD1    // LCD Data Bit 7 in PORT B pin 1
#define LCD_A       PTBD_PTBD0    // LCD Backlight LCD anode in PORT B pin 0
#define LCD_E       PTCD_PTCD2    // LCD Enable in PORT C pin 2
#define LCD_RW      PTCD_PTCD3    // LCD Read/Write in PORT D pin 3
#define LCD_RS      PTCD_PTCD5    // LCD Register Select in PORT C pin 5
#define LCD_DDB0    PTGDD_PTGDD6  // LCD Data Direction Bit 0 in PORT G pin 6
#define LCD_DDB1    PTGDD_PTGDD5  // LCD Data Direction Bit 1 in PORT G pin 5
#define LCD_DDB2    PTGDD_PTGDD3  // LCD Data Direction Bit 2 in PORT G pin 4
#define LCD_DDB3    PTDDD_PTDDD1  // LCD Data Direction Bit 3 in PORT D pin 1
#define LCD_DDB4    PTDDD_PTDDD0  // LCD Data Direction Bit 4 in PORT D pin 0
#define LCD_DDB5    PTBDD_PTBDD3  // LCD Data Direction Bit 5 in PORT B pin 3
#define LCD_DDB6    PTBDD_PTBDD2  // LCD Data Direction Bit 6 in PORT B pin 2
#define LCD_DDB7    PTBDD_PTBDD1  // LCD Data Direction Bit 7 in PORT B pin 1


// Set LCD DB byte to data value
#define LCD_DB(data) \
    LCD_DB0 = (data >> 0) & 0x01; \
    LCD_DB1 = (data >> 1) & 0x01; \
    LCD_DB2 = (data >> 2) & 0x01; \
    LCD_DB3 = (data >> 3) & 0x01; \
    LCD_DB4 = (data >> 4) & 0x01; \
    LCD_DB5 = (data >> 5) & 0x01; \
    LCD_DB6 = (data >> 6) & 0x01; \
    LCD_DB7 = (data >> 7) & 0x01;

// Set LCD DDB byte to data value
#define LCD_DDB(data) \
    LCD_DDB0 = (data >> 0) & 0x01; \
    LCD_DDB1 = (data >> 1) & 0x01; \
    LCD_DDB2 = (data >> 2) & 0x01; \
    LCD_DDB3 = (data >> 3) & 0x01; \
    LCD_DDB4 = (data >> 4) & 0x01; \
    LCD_DDB5 = (data >> 5) & 0x01; \
    LCD_DDB6 = (data >> 6) & 0x01; \
    LCD_DDB7 = (data >> 7) & 0x01;

void enableLCD();               // Send enable signal for printing, includes
                                // check of busy flag
void startLCD(void);
void sendLCD(char data);        // Send data to LCD
void configLCD(char data);      // LCD configuration
void printLCD(char data);       // Print a character to current LCD address
int  checkBusyFlagLCD(void);    // Return BusyFlag
void setInputLCD(void);         // Set LCD DB0 to DB7 pins as inputs
void setOutputLCD(void);        // Set LCD DB0 to DB7 pins as outputs
char getAddressLCD(void);       // Get current DDRAM address
void setAddressLCD(char address); // Set DDRAM address
void setCurrentAddressLCD(void); // Set Current DDRAM address (not valid if
                                // the address counter changes)
void customCharacterLCD(char address, char rowOne, char rowTwo, char rowThree, char rowFour, char rowFive, char rowSix, char rowSeven, char rowEight);
                                // Create character row by row in desired
                                // address
void printStringLCD(char str[]); // Print a string to current LCD address
void goToFirstRowLCD(void);     // Go to first LCD screen row
void goToSecondRowLCD(void);    // Go to second LCD screen row



void enableLCD(){
    LCD_E = 1;
    LCD_E = 0;
    while(checkBusyFlagLCD());
}

void startLCD(){
    LCD_A = 1;
    LCD_E = 0;
    LCD_RW = 0;
    
    configLCD(0b00000001);        // Clear display and sets DDRAM address to 0                                    
    configLCD(0b00000011);        // Return display from being shifted
    configLCD(0b00000110);        // 
            //          >----------- Set cursor incrementing address 
    configLCD(0b00001111);        // 
            //       ||>---------- Blink ON
            //       |>----------- Cursor ON
            //       >------------ Display ON
    configLCD(0b00111000);        // 
            //     ||>------------ 5x8 dots characters
            //     |>------------- 2 lines display
            //     >-------------- 8 bits interface data length
}

void configLCD(char data){
    LCD_RS = 0;
    sendLCD(data);
}

void printLCD(char data){
    LCD_RS = 1;
    sendLCD(data);
}

void sendLCD(char data){
    LCD_DB(data);
    enableLCD();
}

int  checkBusyFlagLCD(){
    int BF=0;
    LCD_RS = 0;
    setInputLCD();
    LCD_RW = 1;
    LCD_E = 1;
    BF = LCD_DB7;
    LCD_E = 0;
    LCD_RW = 0;
    setOutputLCD();
    return BF;
}


void setInputLCD(void){
    LCD_DDB(0x00);
}

void setOutputLCD(void){
    LCD_DDB(0xFF);
}


char getAddressLCD(void){
    typedef union {
      char Byte;
      struct {
        byte AD0      :1;         // LCD Address Bit 0
        byte AD1      :1;         // LCD Address Bit 1
        byte AD2      :1;         // LCD Address Bit 2
        byte AD3      :1;         // LCD Address Bit 3
        byte AD4      :1;         // LCD Address Bit 4
        byte AD5      :1;         // LCD Address Bit 5
        byte AD6      :1;         // LCD Address Bit 6
        byte AD7      :1;         // LCD Address Bit 7
      } Bits;
    } currentLCDAddress;
    currentLCDAddress currentAddress = {0};    
    LCD_RS = 0;
    setInputLCD();
    LCD_RW = 1;
    LCD_E = 1;
    currentAddress.Bits.AD0 = LCD_DB0;
    currentAddress.Bits.AD1 = LCD_DB1;
    currentAddress.Bits.AD2 = LCD_DB2;
    currentAddress.Bits.AD3 = LCD_DB3;
    currentAddress.Bits.AD4 = LCD_DB4;
    currentAddress.Bits.AD5 = LCD_DB5;
    currentAddress.Bits.AD6 = LCD_DB6;
    LCD_E = 0;
    LCD_RW = 0;
    setOutputLCD();
    return currentAddress.Byte;
}


void setAddressLCD(char addressDesired){
    addressDesired = addressDesired + 128;
    configLCD(addressDesired);
}

void setCurrentAddressLCD(void){
    configLCD(getAddressLCD() + 128);
}

void customCharacterLCD(char address, char rowOne, char rowTwo, char rowThree, char rowFour, char rowFive, char rowSix, char rowSeven, char rowEight){
    char displayAddress = getAddressLCD();
    address = address + 64;
    configLCD(address);
    printLCD(rowOne);
    printLCD(rowTwo);
    printLCD(rowThree);
    printLCD(rowFour);
    printLCD(rowFive);
    printLCD(rowSix);
    printLCD(rowSeven);
    printLCD(rowEight);
    setAddressLCD(displayAddress);    
}

void printStringLCD(char str[]){
    int i = 0;
    while (str[i] != '\0'){
        printLCD(str[i]);
        if((i + 1) % 8 == 0){
            if((i + 1) % 16 == 0){
                goToFirstRowLCD();
            }
            else goToSecondRowLCD();
        }
        i = i + 1;
    }
}

void goToFirstRowLCD(void){
    configLCD(0b10000000);
}

void goToSecondRowLCD(void){
    configLCD(0b11000000);
}

#endif /* LMM83T064D3_H_ */
