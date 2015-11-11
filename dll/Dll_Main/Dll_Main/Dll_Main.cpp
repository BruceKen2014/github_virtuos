// Dll_Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>

typedef void(__stdcall *Dll_Printf)(const char*);

typedef struct _stTestBinary
{
	int value1;
	int value2;

	void Serialize()
	{

	}
}TestBinary;
int _tmain(int argc, _TCHAR* argv[])
{
	int i = 0;
	i = 1 << i;
	HINSTANCE dll_instance = LoadLibrary("Dll.dll");
	Dll_Printf prntf = (Dll_Printf)GetProcAddress(dll_instance, "Dll_Printf");
	prntf("this print comes from a dll!");

	FILE* file = NULL;
	fopen_s(&file, "test.bin", "wb");
	int temp_value;
	for (int i = 0; i < 18200/4; ++i)
	{
		int temp_value = 0xffff;
		fwrite(&temp_value, 2, 1, file);
	}
	fwrite(&temp_value,2, 4, file);
	fclose(file);
	return 0;
}
