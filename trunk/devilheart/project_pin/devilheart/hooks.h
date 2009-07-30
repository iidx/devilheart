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

extern int *regState;

VOID movRMHook(REG dstReg,ADDRINT * addr);

VOID movMRHook(REG srcReg,ADDRINT * addr);

VOID repMovsbHandler(int ecx,ADDRINT *srcAddr,ADDRINT *dstAddr);

#endif