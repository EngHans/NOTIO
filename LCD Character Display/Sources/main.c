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
//  Program:    LCD Character Display                                       //
//  Goal:       Test 16x1 LCD character display LMM83T064D3                 //
//  Manager:    Toquica Cáceres, Hans Milos                                 //
//  Charge:     Mechatronics Student                                        //
//  Programmers                                                             //
//  List:       Toquica Cáceres Hans Milos, Manager                         //
//  Revision                                                                //
//  List:       Mon 12-26-16 11:28: (Version 0.0) Project was created       //
//              Thu 01-19-17 22:19: (Version 1.0) Header was completed, no  //
//                  actual library created, only header file                //
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


void main(void) {
	startMicro();
    EnableInterrupts;


	startLCD();
	
	printStringLCD("Jonathan Murc");
	
	customCharacterLCD(0x00, 0x07, 0x00, 0x0C, 0x04, 0x04, 0x04, 0x0E, 0x00);
	printLCD(0);
	printLCD('a');
	delay(255,255);
		
    for(;;) {
        	
    } /* loop forever */
}
