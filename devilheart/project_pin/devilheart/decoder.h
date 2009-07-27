/*******************************************************************

 Title:decode.h
 Function:Define interfaces to decode instructions
 Description:
 Define interfaces to decode instructions
 Version: 1.1
 Date and author: 2009.07.26 hsqfire
*******************************************************************/

#ifndef _DECODER_H
#define _DECODER_H

#include "pin.H"
#include "ins_handler.h"


/* Define operand kind to locate the handler function
 * Here only first 2 operand is necessary
 * R:register
 * M:memrory
 * I:immediate
 * ONLY:only one operand
 * NONE:none operand
 */
enum OperandKind{
	NONE = 0x0, 
	RONLY = 0x2,
	MONLY = 0x3,
	IONLY = 0x1,
	R_R = 0x22,
	R_I = 0x21,
	I_R = 0x12,
	R_M = 0x23,
	M_R = 0x32,
	I_M = 0x13,
	M_I = 0x31,
	M_M = 0x33
};

/* define how to calculate the index of the ins*/
#define INSNUM(x,y) (unsigned int)((x<<8)| y)

/* define the interface to handle the ins*/
void handleIns(unsigned int insNum,INS ins);

/* define the interface to get the displacement*/
OperandKind getOperandKind(INS ins);

#endif