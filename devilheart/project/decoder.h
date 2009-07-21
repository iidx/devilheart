/*******************************************************************

 Title:decoder.h
 Function:Define some procedures to decode simple instructions
 Description:
 Define some procedures to translate machine code to assemble code
 Version: 1.0
 Date and author: 2009.07.21 hsqfire
*******************************************************************/

#ifndef _DECODER_H
#define _DECODER_H

#include <stddef.h> /* for offsetof */
#include "dr_api.h"

/* Disassemble the instruction and print it to the file           */
static void disassemble_code(void *drcontext,instr_t *instr,file_t *f);

#endif