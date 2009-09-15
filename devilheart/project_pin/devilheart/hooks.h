/*******************************************************************

 Title:hooks.h
 Function:Define some hook function to handle some instructions
 Description:
 Define some hook function to handle some instructions
 Version: 1.0
 Date and author: 2009.07.30 hsqfire
*******************************************************************/


#ifndef _HOOKS_H
#define _HOOKS_H

#include "pin.H"
#include "mem_recorder.h"

/* memory recorder*/
extern MemoryRecorder *memManager;

/* handle result output file*/
extern FILE *output;

/* handle log file*/
extern FILE *log;

/* register state*/
extern int *regState;

/* hook function to handle mov R,M instruction*/
VOID movRMHook(REG dstReg,ADDRINT * addr);

/* hook function to handle mov M,R instruction*/
VOID movMRHook(REG srcReg,ADDRINT * addr);

/* hook function to handle rep movsb*/
VOID repMovsbHook(int ecx,ADDRINT *srcAddr,ADDRINT *dstAddr);

/* hook function to handle movzx R,M*/
VOID movzxRMHook(REG dstReg,ADDRINT * addr);

/* hook function to handle movzx R,R*/
VOID movzxRRHook(REG dstReg,REG srcReg);

/* hook function to handle movsd*/
VOID movsdHook(ADDRINT *srcAddr,ADDRINT *dstAddr);

#endif