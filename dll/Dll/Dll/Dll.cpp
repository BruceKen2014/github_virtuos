// Dll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;
//�ṩ��C++����ʹ��ʱ���ɲ���__stdcall����C++�������Ӹ�����������������ն�ջ
//__stdcall ��ʶ�ĺ�����֧�ֿɱ����
void __stdcall Dll_Printf(const char* content)
{
	cout << content << " tag!"<<endl;
}
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}

