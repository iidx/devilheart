/*******************************************************************

 Title:ins_handler.h
 Function:Define interfaces and functions to handle instructions
 Description:
 Define interfaces and functions to handle instructions
 Version: 1.1
 Date and author: 2009.07.26 hsqfire
*******************************************************************/

#pragma once
#ifndef _INS_HANDLER_H
#define _INS_HANDLER_H

#include <map>
#include "pin.H"
#include "mem_recorder.h"

#define HANDLERSIZE 100;

/* define handler table*/
typedef map<int,int> HandlerTable;
extern HandlerTable handlerTable;

/* define src and dst operand*/
extern unsigned int srcA,srcB,srcC;
extern unsigned int dstA,dstB,dstC;

/* memory recorder*/
extern MemoryRecorder *memManager;

/* define function to init handler table*/
void initHandlerTable();

/* define function to init ins&handler table*/
void initHandlerFuns();

/* define function to begin handling instruction*/
void begin();

/* define function to end handling instruction*/
void end();

/* define the interface to handle the ins*/
void handlerInsProxy(unsigned int insNum,INS ins);


#endif