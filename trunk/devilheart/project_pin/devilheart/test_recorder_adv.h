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
void testMarkTaintedMemory();

/* test function dismarkTaintedMemory*/
void testDismarkTaintedMemory();

/* test function isTainted*/
void testIsTainted();

/* test function dismarkTaintedBlock*/
void testDismarkTaintedBlock();

/* test function markTaintedBlock*/
void testMarkTaintedBlock();

/* init test function*/
void initTest();

/* close the test*/
void closeTest();

#endif