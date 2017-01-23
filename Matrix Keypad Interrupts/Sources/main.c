//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
////     //////    //              //                //    //              ///
////      /////    //    //////    //                //    //    //////    ///
////        ///    //    //////    ////////    ////////    //    //////    ///
////    /    //    //    //////    ////////    ////////    //    //////    ///
////    //    /    //    //////    ////////    ////////    //    //////    ///
////    ///        //    //////    ////////    ////////    //    //////    ///
////    ////       //    //////    ////////    ////////    //    //////    ///
////    /////      //    //////    ////////    ////////    //    //////    ///
////    //////     //              ////////    ////////    //              ///
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  NOTIO INGENIERÍA S.A.S                                                  //
//  AUTOMATION DEPARTMENT                                                   //
//                                                                          //
//  Program:    Matrix Keypad Interrupt                                     //
//  Goal:       Test 4x1 matrix keypad with KBI interrupts                  //
//  Manager:    Toquica Cáceres, Hans Milos                                 //
//  Charge:     Mechatronics Student                                        //
//  Programmers                                                             //
//  List:       Toquica Cáceres Hans Milos, Manager                         //
//  Revision                                                                //
//  List:       Thu 01-19-17 23:02: (Version 0.0) Project was created       //
//              Sun 01-22-17 22:19: (Version 1.0) The matrix keypad library //
//                  was completed successfully, a test is made with the LCD //
//                  screen, a fake cellphone interface was created, errors  //
//                  were minimized and the program is working accordingly.  //
//  Current                                                                 //
//  Version:    V1.0                                                        //
//                                                                          // 
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Variables list:                                                         //
//  ''''''''' '''''                                                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  LET THE PROGRAMMING BEGIN                                               //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "main_asm.h" /* interface to the assembly module */
#include "functions.h"
#include "aw60config.h"
#include "lmm83t064d3.h"
#include "matrix4x4Keypad.h"

int i = 0;

interrupt VectorNumber_Vkeyboard1 void kbiinterriptforme(void){
	char userInput;
	if(i == 0){
		clearDisplayLCD();
	}
	userInput = identifyPushedKPD();
	if(userInput != 'A' && userInput != 'B' && userInput != 'C' && userInput != 'D' && userInput != 'e'){
		printLCD(userInput);
		delay(255,255);
		if((i + 1) % 8 == 0){
			if((i + 1) % 16 == 0){
				goToFirstRowLCD();
			}
			else goToSecondRowLCD();
		}
		i++;
	}
	else if (userInput == 'A'){
		clearDisplayLCD();
		i = 0;
		printStringLCD("Llamando");
		delay(255,255);
		delay(255,255);
		delay(255,255);
		delay(255,255);
		delay(255,255);
		delay(255,255);
		delay(255,255);
		delay(255,255);
		clearDisplayLCD();
		printStringLCD("Ocupado");
		delay(255,255);
		delay(255,255);
		delay(255,255);
		delay(255,255);
		delay(255,255);
		delay(255,255);
		delay(255,255);
		delay(255,255);
	}
	else if(userInput != 'e'){
		clearDisplayLCD();
		i = 0;
		printStringLCD("Disponible");
		delay(255,255);
	}
	else {
		clearDisplayLCD();
		i = 0;
		printStringLCD("Error");
	}
	KBI1SC_KBACK = 1;
}

void main(void) {
	startMicro();
	configKPD();
	startLCD();
	printStringLCD("CLARO");
	delay(255,255);
	delay(255,255);
	delay(255,255);
	delay(255,255);
	delay(255,255);
	delay(255,255);
	delay(255,255);
	delay(255,255);
	clearDisplayLCD();
	printStringLCD("Disponible");
    EnableInterrupts;
		
    for(;;) {
        	
    } /* loop forever */
}


