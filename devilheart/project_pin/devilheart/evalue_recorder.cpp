/*******************************************************************

 Title:evalue_recorder.cpp
 Function:Implement functions to evalue mem_recorder
 Description:
 Implement functions to evalue mem_recorder
 Version: 1.0
 Date and author: 2009.07.28 hsqfire, Jiang Bo
*******************************************************************/

#include "evalue_recorder.h"

/* test result output file*/
FILE *traceE;


/******************************************************************
 Title:initTest
 Function:init test function
 Input:
 Output:
******************************************************************/
void initEvalue()
{
	traceE = fopen("evalueResult.out", "w");
}


/******************************************************************
 Title:closeTest
 Function:close the test
 Input:
 Output:
******************************************************************/
void closeEvalue()
{
	fclose(traceE);
}


/******************************************************************
 Title:evalueMarkTaintedMemory
 Function:evalue function markTaintedMemory
 Input:
 Output:
******************************************************************/
void evalueMarkTaintedMemory()
{
	SYSTEMTIME sys;
	int beginTime, endTime;

	unsigned int taintedAddress[1000];
	srand((unsigned)(time(0)));

	MemoryRecorder recorder;
	MemoryRecorderSeq recorderSeq;
	MemoryRecorderAdv recorderAdv;
	for(int i=0;i<1000;i++){
		taintedAddress[i]=0;
		for(int j=0;j<32;j++){
			unsigned int tmp = rand()%16;
			taintedAddress[i] = taintedAddress[i]+(tmp<<j);
		}
	}
	GetLocalTime( &sys );
	beginTime = sys.wHour*3600*1000;
	beginTime += sys.wMinute*60*1000;
	beginTime += sys.wSecond*1000;
	beginTime += sys.wMilliseconds; 
	for(int i=0;i<1000;i++){
		bool result = recorder.markTaintedMemory(taintedAddress[i]);
	}
	GetLocalTime( &sys );
	endTime = sys.wHour*3600*1000;
	endTime += sys.wMinute*60*1000;
	endTime += sys.wSecond*1000;
	endTime += sys.wMilliseconds;
	fprintf(traceE,"testMarkTaintedMemory nedd time:%d milliseconds\n",endTime - beginTime);

	GetLocalTime( &sys );
	beginTime = sys.wHour*3600*1000;
	beginTime += sys.wMinute*60*1000;
	beginTime += sys.wSecond*1000;
	beginTime += sys.wMilliseconds; 
	for(int i=0;i<1000;i++){
		bool result = recorderSeq.markTaintedMemory(taintedAddress[i]);
	}
	GetLocalTime( &sys );
	endTime = sys.wHour*3600*1000;
	endTime += sys.wMinute*60*1000;
	endTime += sys.wSecond*1000;
	endTime += sys.wMilliseconds;
	fprintf(traceE,"testMarkTaintedMemorySeq nedd time:%d milliseconds\n",endTime - beginTime);

	GetLocalTime( &sys );
	beginTime = sys.wHour*3600*1000;
	beginTime += sys.wMinute*60*1000;
	beginTime += sys.wSecond*1000;
	beginTime += sys.wMilliseconds; 
	for(int i=0;i<1000;i++){
		bool result = recorderAdv.markTaintedMemory(taintedAddress[i]);
	}
	GetLocalTime( &sys );
	endTime = sys.wHour*3600*1000;
	endTime += sys.wMinute*60*1000;
	endTime += sys.wSecond*1000;
	endTime += sys.wMilliseconds;
	fprintf(traceE,"testMarkTaintedMemoryAdv nedd time:%d milliseconds\n",endTime - beginTime);
	fprintf(traceE,"*******************************************************************\n");

}


/******************************************************************
 Title:evalueIsTainted
 Function:evalue function isTainted
 Input:
 Output:
******************************************************************/
void evalueIsTainted()
{
	SYSTEMTIME sys;
	int beginTime, endTime;

	unsigned int taintedAddress[1000];

	unsigned int testAddress[1000];

	MemoryRecorder recorder;
	MemoryRecorderSeq recorderSeq;
	MemoryRecorderAdv recorderAdv;
	for(int i=0;i<1000;i++){
		taintedAddress[i]=0;
		for(int j=0;j<32;j++){
			unsigned int tmp = rand()%16;
			taintedAddress[i] = taintedAddress[i]+(tmp<<j);
		}
	}
	for(int i=0;i<1000;i++){
		testAddress[i]=0;
		for(int j=0;j<32;j++){
			unsigned int tmp = rand()%16;
			testAddress[i] = testAddress[i]+(tmp<<j);
		}
	}
	GetLocalTime( &sys );
	beginTime = sys.wHour*3600*1000;
	beginTime += sys.wMinute*60*1000;
	beginTime += sys.wSecond*1000;
	beginTime += sys.wMilliseconds; 
	for(int i=0;i<1000;i++){
		bool result = recorder.markTaintedMemory(testAddress[i]);
	}
	for(int i=0;i<1000;i++){
		int result = recorder.isTainted(testAddress[i]);
	}
	GetLocalTime( &sys );
	endTime = sys.wHour*3600*1000;
	endTime += sys.wMinute*60*1000;
	endTime += sys.wSecond*1000;
	endTime += sys.wMilliseconds;
	fprintf(traceE,"testIsMarkTainted need time:%d milliseconds\n",endTime-beginTime);

	GetLocalTime( &sys );
	beginTime = sys.wHour*3600*1000;
	beginTime += sys.wMinute*60*1000;
	beginTime += sys.wSecond*1000;
	beginTime += sys.wMilliseconds; 
	for(int i=0;i<1000;i++){
		bool result = recorderSeq.markTaintedMemory(testAddress[i]);
	}
	for(int i=0;i<1000;i++){
		int result = recorderSeq.isTainted(testAddress[i]);
	}
	GetLocalTime( &sys );
	endTime = sys.wHour*3600*1000;
	endTime += sys.wMinute*60*1000;
	endTime += sys.wSecond*1000;
	endTime += sys.wMilliseconds;
	fprintf(traceE,"testIsMarkTaintedSeq need time:%d milliseconds\n",endTime-beginTime);

	GetLocalTime( &sys );
	beginTime = sys.wHour*3600*1000;
	beginTime += sys.wMinute*60*1000;
	beginTime += sys.wSecond*1000;
	beginTime += sys.wMilliseconds; 
	for(int i=0;i<1000;i++){
		bool result = recorderAdv.markTaintedMemory(testAddress[i]);
	}
	for(int i=0;i<1000;i++){
		int result = recorderAdv.isTainted(testAddress[i]);
	}
	GetLocalTime( &sys );
	endTime = sys.wHour*3600*1000;
	endTime += sys.wMinute*60*1000;
	endTime += sys.wSecond*1000;
	endTime += sys.wMilliseconds;
	fprintf(traceE,"testIsMarkTaintedAdv need time:%d milliseconds\n",endTime-beginTime);
	fprintf(traceE,"*******************************************************************\n");
}


/******************************************************************
 Title:evalueMarkTaintedBlock
 Function:evalue function markTaintedBlock
 Input:
 Output:
******************************************************************/
void evalueMarkTaintedBlock()
{
	SYSTEMTIME sys;
	int beginTime, endTime;

	int minAddress= 0x0000;
	int length = 0x00100000;

	MemoryRecorder recorder;
	MemoryRecorderSeq recorderSeq;
	MemoryRecorderAdv recorderAdv;
	GetLocalTime( &sys );
	beginTime = sys.wHour*3600*1000;
	beginTime += sys.wMinute*60*1000;
	beginTime += sys.wSecond*1000;
	beginTime += sys.wMilliseconds; 
	recorder.markTaintedBlock(minAddress,length);
	GetLocalTime( &sys );
	endTime = sys.wHour*3600*1000;
	endTime += sys.wMinute*60*1000;
	endTime += sys.wSecond*1000;
	endTime += sys.wMilliseconds;
	fprintf(traceE,"testMarkTaintedBlock need time:%d milliseconds\n",endTime-beginTime);

	GetLocalTime( &sys );
	beginTime = sys.wHour*3600*1000;
	beginTime += sys.wMinute*60*1000;
	beginTime += sys.wSecond*1000;
	beginTime += sys.wMilliseconds; 
	recorderSeq.markTaintedBlock(minAddress,length);
	GetLocalTime( &sys );
	endTime = sys.wHour*3600*1000;
	endTime += sys.wMinute*60*1000;
	endTime += sys.wSecond*1000;
	endTime += sys.wMilliseconds;
	fprintf(traceE,"testMarkTaintedBlockSeq need time:%d milliseconds\n",endTime-beginTime);

	GetLocalTime( &sys );
	beginTime = sys.wHour*3600*1000;
	beginTime += sys.wMinute*60*1000;
	beginTime += sys.wSecond*1000;
	beginTime += sys.wMilliseconds; 
	recorderAdv.markTaintedBlock(minAddress,length);
	GetLocalTime( &sys );
	endTime = sys.wHour*3600*1000;
	endTime += sys.wMinute*60*1000;
	endTime += sys.wSecond*1000;
	endTime += sys.wMilliseconds;
	fprintf(traceE,"testMarkTaintedBlockAdv need time:%d milliseconds\n",endTime-beginTime);
	fprintf(traceE,"*******************************************************************\n");
}