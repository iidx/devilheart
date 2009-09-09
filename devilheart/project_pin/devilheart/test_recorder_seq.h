/*******************************************************************

 Title:test_recorder_seq.h
 Function:Define functions to test mem_recorder_seq
 Description:
 Define functions to test mem_recorder_adv
 Version: 1.0
 Date and author: 2009.08.08 hsqfire
*******************************************************************/

#ifndef _TEST_RECORDER_SEQ_H
#define _TEST_RECORDER_SEQ_H

#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include "mem_recorder_seq.h"

/* test function markTaintedMemory*/
void testMarkTaintedMemorySeq();

/* test function dismarkTaintedMemory*/
void testDismarkTaintedMemorySeq();

/* test function isTainted*/
void testIsTaintedSeq();

/* test function dismarkTaintedBlock*/
void testDismarkTaintedBlockSeq();

/* test function markTaintedBlock*/
void testMarkTaintedBlockSeq();

/* init test function*/
void initTestSeq();

/* close the test*/
void closeTestSeq();

#endif