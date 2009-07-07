	.586
	.model flat, stdcall
	option casemap:none
	include c:\masm32\INCLUDE\Windows.inc
	include c:\masm32\INCLUDE\user32.inc
	include c:\masm32\INCLUDE\kernel32.inc
	includelib c:\masm32\lib\user32.lib
	includelib c:\masm32\lib\kernel32.lib
	

	
.data
	szSrc	db	'blabla',0
	szDes	db	MAX_PATH	dup(0)
.data?

	assume	fs:nothing
.code

start:
	lea	esi, offset szSrc
	lea	edi, offset szDes
	mov	ecx,6
	cld
	rep	movsb
	
	invoke	ExitProcess, 0
end start