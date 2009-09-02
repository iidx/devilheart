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
FILE *traceT;


/******************************************************************
 Title:initTest
 Function:init test function
 Input:
 Output:
******************************************************************/
void initTest()
{
	traceT = fopen("testResult.out", "w");
}


/******************************************************************
 Title:closeTest
 Function:close the test
 Input:
 Output:
******************************************************************/
void closeTest()
{
	fclose(traceT);
}


/******************************************************************
 Title:testMarkTaintedMemory
 Function:test function markTaintedMemory
 Input:
 Output:
******************************************************************/
void testMarkTaintedMemory()
{
	int dataNum = 3;
	int failNum = 0;

	unsigned int taintedAddress[]={
		0x0000000A,0x000B0000,0xC0000000
	};
	
	bool testResult[]={
		true,true,true
	};

	MemoryRecorder recorder;
	for(int i=0;i<dataNum;i++){
		bool result = recorder.markTaintedMemory(taintedAddress[i]);
		if(result!=testResult[i]){
			failNum ++;
			fprintf(traceT,"mark address:0x%x  result:fail\n",taintedAddress[i]);
		}else{
			//fprintf(traceT,"mark address:0x%x  result:success\n",taintedAddress[i]);
		}
	}
	fprintf(traceT,"testMarkTaintedMemory test all:%d fail:%d\n",dataNum,failNum);
	fprintf(traceT,"*******************************************************************\n");
}


/******************************************************************
 Title:testDismarkTaintedMemory
 Function:test function dismarkTaintedMemory
 Input:
 Output:
******************************************************************/
void testDismarkTaintedMemory()
{
	int preDataNum = 3;
	int dataNum = 3;
	int failNum = 0;

	unsigned int taintedAddress[]={
		0xA00000,0x0000B000,0x0000000C
	};
	
	unsigned int untaintedAddress[]={
		0x0000000D,0x000E000,0xF0000000
	};

	bool testResult[]={
		true,true,true
	};

	MemoryRecorder recorder;
	for(int i=0;i<preDataNum;i++){
		recorder.markTaintedMemory(taintedAddress[i]);
	}
	for(int i=0;i<dataNum;i++){
		bool result = recorder.dismarkTaintedMemory(untaintedAddress[i]);
		if(result!=testResult[i]){
			failNum ++;
			fprintf(traceT,"dismark address:0x%x  result:fail\n",untaintedAddress[i]);
		}else{
			//fprintf(traceT,"dismark address:0x%x  result:success\n",untaintedAddress[i]);
		}
	}
	fprintf(traceT,"testDisMarkTaintedMemory test all:%d fail:%d\n",dataNum,failNum);
	fprintf(traceT,"*******************************************************************\n");
}


/******************************************************************
 Title:testIsTainted
 Function:test function isTainted
 Input:
 Output:
******************************************************************/
void testIsTainted()
{
	int preDataNum1 = 3;
	int preDataNum2 = 3;
	int dataNum = 3;
	int failNum = 0;

	unsigned int taintedAddress[]={
		0x0000ABCD,0xABCD0000,0xDCBA0000
	};
	
	unsigned int untaintedAddress[]={
		0xA0B0C0D0,0x0B0A0C0D,0xD0C0B0A0
	};

	unsigned int testAddress[]={
		0x0000ABCD,0x0B0A0C0D,0xD0C0B0A0
	};

	int testResult[]={
		1,0,0
	};

	MemoryRecorder recorder;
	for(int i=0;i<preDataNum1;i++){
		recorder.markTaintedMemory(taintedAddress[i]);
	}
	for(int i=0;i<preDataNum2;i++){
		recorder.dismarkTaintedMemory(untaintedAddress[i]);
	}
	for(int i=0;i<dataNum;i++){
		int result = recorder.isTainted(testAddress[i]);
		if(result!=testResult[i]){
			failNum ++;
			fprintf(traceT,"test state of address:0x%x  result:fail\n",testAddress[i]);
		}else{
			//fprintf(trace,"test state of address:0x%x  result:success\n",testAddress[i]);
		}
	}
	fprintf(traceT,"testIsMarkTainted test all:%d fail:%d\n",dataNum,failNum);
	fprintf(traceT,"*******************************************************************\n");
}


/******************************************************************
 Title:testDismarkTaintedBlock
 Function:test function dismarkTaintedBlock
 Input:
 Output:
******************************************************************/
void testDismarkTaintedBlock()
{
	int dataNum = 3;
	int failNum = 0;
	int preDataNum = 3;

	int minAddress= 0x00000000;
	int length = 0x00001234;
	unsigned int taintedAddress[]={
		0x00000001,0x00001222,0x00001235
	};
	unsigned int testAddress[]={
		0x00000001,0x00001222,0x00001235
	};

	int testResult[]={
		0,0,1
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
			fprintf(traceT,"test state of address:0x%x  result:fail\n",testAddress[i]);
		}else{
			//fprintf(traceT,"test state of address:0x%x  result:success\n",testAddress[i]);
		}
	}
	fprintf(traceT,"testDismarkTaintedBlock test all:%d fail:%d\n",dataNum,failNum);
	fprintf(traceT,"*******************************************************************\n");
}


/******************************************************************
 Title:testMarkTaintedBlock
 Function:test function markTaintedBlock
 Input:
 Output:
******************************************************************/
void testMarkTaintedBlock()
{
	int dataNum = 3;
	int failNum = 0;
	int preDataNum = 3;

	int minAddress= 0x0000;
	int length = 0x00001234;
	unsigned int taintedAddress[]={
		0x00000001,0x00001222,0x00001235
	};
	unsigned int testAddress[]={
		0x00000001,0x00001222,0x00001235
	};

	int testResult[]={
		1,1,1
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
			fprintf(traceT,"test state of address:0x%x  result:fail\n",testAddress[i]);
		}else{
			//fprintf(traceT,"test state of address:0x%x  result:success\n",testAddress[i]);
		}
	}
	fprintf(traceT,"testMarkTaintedBlock test all:%d fail:%d\n",dataNum,failNum);
	fprintf(traceT,"*******************************************************************\n");
}