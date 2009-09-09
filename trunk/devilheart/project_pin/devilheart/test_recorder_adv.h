/*******************************************************************

 Title:test_recorder_adv.h
 Function:Define functions to test mem_recorder_adv
 Description:
 Define functions to test mem_recorder_adv
 Version: 1.0
 Date and author: 2009.08.08 hsqfire
*******************************************************************/

#ifndef _TEST_RECORDER_ADV_H
#define _TEST_RECORDER_ADV_H

#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include "mem_recorder_adv.h"

/* test function markTaintedMemory*/
void testMarkTaintedMemoryAdv();

/* test function dismarkTaintedMemory*/
void testDismarkTaintedMemoryAdv();

/* test function isTainted*/
void testIsTaintedAdv();

/* test function dismarkTaintedBlock*/
void testDismarkTaintedBlockAdv();

/* test function markTaintedBlock*/
void testMarkTaintedBlockAdv();

/* init test function*/
void initTestAAdv();

/* close the test*/
void closeTestAdv();

#endif