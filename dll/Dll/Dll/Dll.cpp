// Dll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;
//提供给C++程序使用时，可不加__stdcall，非C++程序必须加该声明，用以自身清空堆栈
//__stdcall 标识的函数不支持可变参数
void __stdcall Dll_Printf(const char* content)
{
	cout << content << " tag!"<<endl;
}
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}

