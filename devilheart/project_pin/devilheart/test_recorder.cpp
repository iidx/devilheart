/*******************************************************************

 Title:test_recorder.cpp
 Function:Implement functions to test mem_recorder
 Description:
 Implement functions to test mem_recorder
 Version: 1.0
 Date and author: 2009.07.28 hsqfire, Jiang Bo
*******************************************************************/

#include "test_recorder.h"

/* test result output file*/
FILE *trace;


/******************************************************************
 Title:initTest
 Function:init test function
 Input:
 Output:
******************************************************************/
void initTest()
{
	trace = fopen("testResult.out", "w");
}


/******************************************************************
 Title:closeTest
 Function:close the test
 Input:
 Output:
******************************************************************/
void closeTest()
{
	fclose(trace);
}


/******************************************************************
 Title:testMarkTaintedMemory
 Function:test function markTaintedMemory
 Input:
 Output:
******************************************************************/
void testMarkTaintedMemory()
{
	int dataNum = 0;
	int failNum = 0;

	unsigned int taintedAddress[]={
		0x0000
	};
	
	bool testResult[]={
		true
	};

	MemoryRecorder recorder;
	for(int i=0;i<dataNum;i++){
		bool result = recorder.markTaintedMemory(taintedAddress[i]);
		if(result!=testResult[i]){
			failNum ++;
			fprintf(trace,"mark address:0x%x  result:fail\n",taintedAddress[i]);
		}else{
			fprintf(trace,"mark address:0x%x  result:success\n",taintedAddress[i]);
		}
	}
	fprintf(trace,"testMarkTaintedMemory test all:%d fail:%d\n",dataNum,failNum);
	fprintf(trace,"*******************************************************************");
}


/******************************************************************
 Title:testDismarkTaintedMemory
 Function:test function dismarkTaintedMemory
 Input:
 Output:
******************************************************************/
void testDismarkTaintedMemory()
{
	int preDataNum = 0;
	int dataNum = 0;
	int failNum = 0;

	unsigned int taintedAddress[]={
		0x0000
	};
	
	unsigned int untaintedAddress[]={
		0x0000
	};

	bool testResult[]={
		true
	};

	MemoryRecorder recorder;
	for(int i=0;i<preDataNum;i++){
		recorder.markTaintedMemory(taintedAddress[i]);
	}
	for(int i=0;i<dataNum;i++){
		bool result = recorder.dismarkTaintedMemory(untaintedAddress[i]);
		if(result!=testResult[i]){
			failNum ++;
			fprintf(trace,"dismark address:0x%x  result:fail\n",untaintedAddress[i]);
		}else{
			fprintf(trace,"dismark address:0x%x  result:success\n",untaintedAddress[i]);
		}
	}
	fprintf(trace,"testDisMarkTaintedMemory test all:%d fail:%d\n",dataNum,failNum);
	fprintf(trace,"*******************************************************************");
}


/******************************************************************
 Title:testIsTainted
 Function:test function isTainted
 Input:
 Output:
******************************************************************/
void testIsTainted()
{
	int preDataNum1 = 0;
	int preDataNum2 = 0;
	int dataNum = 0;
	int failNum = 0;

	unsigned int taintedAddress[]={
		0x0000
	};
	
	unsigned int untaintedAddress[]={
		0x0000
	};

	unsigned int testAddress[]={
		0x0000
	};

	int testResult[]={
		1
	};

	MemoryRecorder recorder;
	for(int i=0;i<preDataNum1;i++){
		recorder.markTaintedMemory(taintedAddress[i]);
	}
	for(int i=0;i<preDataNum2;i++){
		recorder.markTaintedMemory(untaintedAddress[i]);
	}
	for(int i=0;i<dataNum;i++){
		int result = recorder.isTainted(testAddress[i]);
		if(result!=testResult[i]){
			failNum ++;
			fprintf(trace,"test state of address:0x%x  result:fail\n",testAddress[i]);
		}else{
			fprintf(trace,"test state of address:0x%x  result:success\n",testAddress[i]);
		}
	}
	fprintf(trace,"testIsMarkTainted test all:%d fail:%d\n",dataNum,failNum);
	fprintf(trace,"*******************************************************************");
}


/******************************************************************
 Title:testDismarkTaintedBlock
 Function:test function dismarkTaintedBlock
 Input:
 Output:
******************************************************************/
void testDismarkTaintedBlock()
{
	int dataNum = 0;
	int failNum = 0;
	int preDataNum = 0;

	int minAddress= 0x0000;
	int length = 0;
	unsigned int taintedAddress[]={
		0x0000
	};
	unsigned int testAddress[]={
		0x0000
	};

	int testResult[]={
		1
	};

	MemoryRecorder recorder;
	for(int i=0;i<preDataNum;i++){
		recorder.markTaintedMemory(taintedAddress[i]);
	}
	recorder.dismarkTaintedBlock(minAddress,length);
	for(int i=0;i<dataNum;i++){
		int result = recorder.isTainted(testAddress[i]);
		if(result!=testResult[i]){
			failNum ++;
			fprintf(trace,"test state of address:0x%x  result:fail\n",testAddress[i]);
		}else{
			fprintf(trace,"test state of address:0x%x  result:success\n",testAddress[i]);
		}
	}
	fprintf(trace,"testDismarkTaintedBlock test all:%d fail:%d\n",dataNum,failNum);
	fprintf(trace,"*******************************************************************");
}


/******************************************************************
 Title:testMarkTaintedBlock
 Function:test function markTaintedBlock
 Input:
 Output:
******************************************************************/
void testMarkTaintedBlock()
{
	int dataNum = 0;
	int failNum = 0;
	int preDataNum = 0;

	int minAddress= 0x0000;
	int length = 0;
	unsigned int taintedAddress[]={
		0x0000
	};
	unsigned int testAddress[]={
		0x0000
	};

	int testResult[]={
		1
	};

	MemoryRecorder recorder;
	for(int i=0;i<preDataNum;i++){
		recorder.markTaintedMemory(taintedAddress[i]);
	}
	recorder.markTaintedBlock(minAddress,length);
	for(int i=0;i<dataNum;i++){
		int result = recorder.isTainted(testAddress[i]);
		if(result!=testResult[i]){
			failNum ++;
			fprintf(trace,"test state of address:0x%x  result:fail\n",testAddress[i]);
		}else{
			fprintf(trace,"test state of address:0x%x  result:success\n",testAddress[i]);
		}
	}
	fprintf(trace,"testMarkTaintedBlock test all:%d fail:%d\n",dataNum,failNum);
	fprintf(trace,"*******************************************************************");
}