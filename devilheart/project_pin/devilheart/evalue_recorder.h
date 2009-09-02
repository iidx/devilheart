/*******************************************************************

 Title:evalue_recorder.h
 Function:Define functions to evalue mem_recorder
 Description:
 Define functions to evalue mem_recorder
 Version: 1.0
 Date and author: 2009.07.28 hsqfire
*******************************************************************/

#ifndef _EVALUE_RECORDER_H
#define _EVALUE_RECORDER_H

#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <math.h>
#include <afx.h>
#include <windows.h>
#include <ctime>
#include "mem_recorder.h"
#include "mem_recorder_seq.h"
#include "mem_recorder_adv.h"

/* evalue function markTaintedMemory*/
void evalueMarkTaintedMemory();

/* evalue function isTainted*/
void evalueIsTainted();

/* evalue function markTaintedBlock*/
void evalueMarkTaintedBlock();

/* init test function*/
void initTest();

/* close the test*/
void closeTest();

#endif