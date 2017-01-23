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
//                                                                          //
//  WARNING MESSAGE                                                         //
//                                                                          //
//  The User needs to place the rows in KBI pins, columns in GPIO ports.    //
//  After calling "configKeypad" the user shall issue a Enable Interrupts.  //
//  The interruption acknowledge is advised to be issued at the end of the  //
//  interruption.                                                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  USAGE INSTRUCTIONS                                                      //
//                                                                          //
//  In order to use the 4x4 MATRIX KEYPAD the user needs to replace the pin //
//  connections in the define macros with the actual ones (i.e. the physi-  //
//  cal connections on the µCU), the corresponding pin enables for the KBI  //
//  ports and the data direction bits of the physical configuration as      //
//  well. The user shall define the KBI pins used for the rows in the defi- //
//  ne macros as well. The rows numbering goes from top to bottom, the cols //
//  numbering goes from left to right (i.e. ROW1 = 1, 2, 3, A. COL1 = 1, 4, //
//  7, *).                                                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  RETURN INFORMATION WHEN CALLING identifyPushedKPD()                     //
//                                                                          //
//  -----------------      The user's 4x4 matrix keyboard is assumed to be  //
//  | 1 | 2 | 3 | A |      like the one shown in the left part of this sec- //
//  -----------------      tion. The output of identifyPushedKPD() is a     //
//  | 4 | 5 | 6 | B |      single character, type char, it could be either  //
//  -----------------      be 'A', 'B', 'C', 'D', '1', '2', '3', '4', '5',  //
//  | 7 | 8 | 9 | C |      '6', '7', '8', '9', '0', '*' or '#' for each of  //
//  -----------------      the available keys in the keypad; an 'e' will    //
//  | * | 0 | # | D |      be returned if the input was not properly read   //
//  -----------------      ('e' stands for error).                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////



/*
 * matrix4x4Keypad.h
 *
 *  Created on: Jan 20, 2017
 *      Author: toquica
 */

#ifndef MATRIX4X4KEYPAD_H_
#define MATRIX4X4KEYPAD_H_

#define KPAD_ROWD1  PTGD_PTGD1
#define KPAD_ROWD2  PTGD_PTGD2
#define KPAD_ROWD3  PTDD_PTDD2
#define KPAD_ROWD4  PTDD_PTDD3
#define KPAD_COLD1  PTCD_PTCD4
#define KPAD_COLD2  PTFD_PTFD0
#define KPAD_COLD3  PTAD_PTAD0
#define KPAD_COLD4  PTAD_PTAD1
#define KPAD_ROWPE1  PTGPE_PTGPE1
#define KPAD_ROWPE2  PTGPE_PTGPE2
#define KPAD_ROWPE3  PTDPE_PTDPE2
#define KPAD_ROWPE4  PTDPE_PTDPE3
#define KPAD_ROWDD1  PTGDD_PTGDD1
#define KPAD_ROWDD2  PTGDD_PTGDD2
#define KPAD_ROWDD3  PTDDD_PTDDD2
#define KPAD_ROWDD4  PTDDD_PTDDD3
#define KPAD_COLDD1  PTCDD_PTCDD4
#define KPAD_COLDD2  PTFDD_PTFDD0
#define KPAD_COLDD3  PTADD_PTADD0
#define KPAD_COLDD4  PTADD_PTADD1
#define KPAD_ROWKBI1 KBIPE_KBIPE1
#define KPAD_ROWKBI2 KBIPE_KBIPE2
#define KPAD_ROWKBI3 KBIPE_KBIPE5
#define KPAD_ROWKBI4 KBIPE_KBIPE6


void configKPD(void);          // Basic keyboard interrupt configuration.
void rowsAsInterruptKPD(void); // Set row pins as interrupts inputs.
void setColsDDKPD(char data);  // Set the data direction of the columns pins,
                               // Four bits data only.
void setColsDKPD(char data);   // Set the cols data pins. Four bits data only.
void setRowsPEKPD(void);       // Set rows pull up devices.
char identifyPushedKPD(void);  // Identify pushed key on keypad
void rowsAsInputKPD(void);     // Set row pins as general pins input.


void configKPD(void){
	setColsDDKPD(0x0F);
	setColsDKPD(0x00);
	setRowsPEKPD();
	rowsAsInterruptKPD();
	KBI1SC = 0b00000110;        // Busy Flag is set after setting rows as in-
                                // terrupts, it needs to be acknowledge.
}

void rowsAsInterruptKPD(){
	KPAD_ROWKBI1 = 1;
	KPAD_ROWKBI2 = 1;
	KPAD_ROWKBI3 = 1;
	KPAD_ROWKBI4 = 1;
}

void setColsDDKPD(char data){
	KPAD_COLDD1 = (data >> 0) & 0x01;
	KPAD_COLDD2 = (data >> 1) & 0x01;
	KPAD_COLDD3 = (data >> 2) & 0x01;
	KPAD_COLDD4 = (data >> 3) & 0x01;
}

void setColsDKPD(char data){
	KPAD_COLD1 = (data >> 0) & 0x01;
	KPAD_COLD2 = (data >> 1) & 0x01;
	KPAD_COLD3 = (data >> 2) & 0x01;
	KPAD_COLD4 = (data >> 3) & 0x01;
}

void setRowsPEKPD(void){
    KPAD_ROWPE1 = 1;
    KPAD_ROWPE2 = 1;
    KPAD_ROWPE3 = 1;
    KPAD_ROWPE4 = 1;
}

char identifyPushedKPD(){
	char key;
	rowsAsInputKPD();
	setColsDKPD(0x00);
	if(!KPAD_ROWD1){
		setColsDKPD(0x0C);
		if(!KPAD_ROWD1){
			setColsDKPD(0x0E);
			if(!KPAD_ROWD1){
				key = '1';
			}
			else key = '2';
		}
		else{
			setColsDKPD(0x0B);
			if(!KPAD_ROWD1){
				key = '3';
			}
			else key = 'A';
		}
	}
	else if(!KPAD_ROWD2){
		setColsDKPD(0x0C);
		if(!KPAD_ROWD2){
			setColsDKPD(0x0E);
			if(!KPAD_ROWD2){
				key = '4';
			}
			else key = '5';
		}
		else{
			setColsDKPD(0x0B);
			if(!KPAD_ROWD2){
				key = '6';
			}
			else key = 'B';
		}
	}	
	
	else if(!KPAD_ROWD3){
		setColsDKPD(0x0C);
		if(!KPAD_ROWD3){
			setColsDKPD(0x0E);
			if(!KPAD_ROWD3){
				key = '7';
			}
			else key = '8';
		}
		else{
			setColsDKPD(0x0B);
			if(!KPAD_ROWD3){
				key = '9';
			}
			else key = 'C';
		}
	}
	
	else if(!KPAD_ROWD4){
		setColsDKPD(0x0C);
		if(!KPAD_ROWD4){
			setColsDKPD(0x0E);
			if(!KPAD_ROWD4){
				key = '*';
			}
			else key = '0';
		}
		else{
			setColsDKPD(0x0B);
			if(!KPAD_ROWD4){
				key = '#';
			}
			else key = 'D';
		}
	}
	
	else key = 'e';
	setColsDKPD(0x00);
	rowsAsInterruptKPD();
	return key;
}

void rowsAsInputKPD(){
	KPAD_ROWKBI1 = 0;
	KPAD_ROWKBI2 = 0;
	KPAD_ROWKBI3 = 0;
	KPAD_ROWKBI4 = 0;
    KPAD_ROWDD1 = 0;
    KPAD_ROWDD2 = 0;
    KPAD_ROWDD3 = 0;
    KPAD_ROWDD4 = 0;
}

#endif /* MATRIX4X4KEYPAD_H_ */
