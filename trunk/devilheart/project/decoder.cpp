/*******************************************************************

 Title:decoder.cpp
 Function:To impletment some procedures to decode simple instructions
 Description:
 To impletment some procedures to translate machine code to assemble 
 code
 Version: 1.0
 Date and author: 2009.07.21 hsqfire
*******************************************************************/

#include "decoder.h"


/******************************************************************
 Title:disassemble_code
 Function:Disassembel the instruction and print it to the file
 Input:
 void *drcontext:Private context of single thread
 instr_t *instr:Instruction needed to be disassembled
 file_t *f:Output file
 Output:
******************************************************************/
static void disassemble_code(void *drcontext,instr_t *instr, file_t *f)
{
	opnd_t dstOpnd,srcOpnd;
	int opcode;
	reg_id_t srcA,dstA;
	int immd;
	opcode = instr_get_opcode(instr);
	dstOpnd = instr_get_dst(instr,0);
	srcOpnd = instr_get_src(instr,0);
	dr_mcontext_t mc;
    dr_get_mcontext(drcontext, &mc, NULL);
	dr_fprintf((*f),"Opcode:%d \n",opcode);
	if(instr_reads_memory(instr))
	{
		if(opnd_is_reg(srcOpnd)){
			srcA= srcOpnd.black_box_uint[1];
			dr_fprintf((*f),"Read data from memory at:%d\n",reg_get_value(srcA,(dr_mcontext_t*)&mc));
		}else{
			immd = srcOpnd.black_box_uint[1];
			srcA = srcOpnd.black_box_uint[2];
			dr_fprintf((*f),"Read data from memory at:%d+%d\n",reg_get_value(srcA,(dr_mcontext_t*)&mc),immd);
		}
	}else{
		if(opnd_is_immed(srcOpnd)){
			immd = srcOpnd.black_box_uint[1];
			dr_fprintf((*f),"Reading data from immediate:%d\n",immd);
		}
		else{
			if(opnd_is_near_memory_reference(srcOpnd)){
				srcA = srcOpnd.black_box_uint[2];
				dr_fprintf((*f),"Read address data:%d\n",reg_get_value(srcA,(dr_mcontext_t*)&mc));
			}else if(opnd_is_near_pc(srcOpnd)){
				immd = srcOpnd.black_box_uint[1];
				dr_fprintf((*f),"Read procedure address:%d\n",immd);
			}
			else{
				srcA = srcOpnd.black_box_uint[1];
				dr_fprintf((*f),"Read data from register of:%d\n",srcA);
			}
		}
	}
	if(instr_writes_memory(instr))
	{
		if(opnd_is_reg(dstOpnd)){
			dstA= dstOpnd.black_box_uint[1];
			dr_fprintf((*f),"Write data to memory at:%d\n",reg_get_value(dstA,(dr_mcontext_t*)&mc));
		}else{
			immd = dstOpnd.black_box_uint[1];
			dstA = dstOpnd.black_box_uint[2];
			dr_fprintf((*f),"Write data to memory at:%d+%d\n",reg_get_value(dstA,(dr_mcontext_t*)&mc),immd);
		}
	}else{
		dstA = dstOpnd.black_box_uint[1];
		dr_fprintf((*f),"Write data to register of:%d\n",dstA);
	}
}
