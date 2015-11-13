// CrtMemoryLeak.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#ifdef _DEBUG
#	define _CRTDBG_MAP_ALLOC //Ϊ���ܹ���׽malloc��й¶������������Ժ�malloc���Ϊ_malloc_dbg
#	define DEBUG_CLIENTBLOCK new(_CLIENT_BLOCK, __FILE__, __LINE__)
#	define new DEBUG_CLIENTBLOCK
#include <crtdbg.h>
#endif
/*
�����#define DEBUG_CLIENTBLOCK new(_CLIENT_BLOCK, __FILE__, __LINE__)����궨��ĺ������������߶�����operate new �������ᵼ�º��滻��ʧ��
STL��xdebug�ļ�������operate new���������������Ӧ�÷���STLͷ�ļ��ĺ���
*/

class CTestClassLeak
{
	int value;
};

class CheckLocalMemLeak
{
	_CrtMemState enterpoint;

public:
	CheckLocalMemLeak()
	{
		_CrtMemCheckpoint(&enterpoint);//��¼����ڴ����
	}
	~CheckLocalMemLeak()
	{
		_CrtMemState exitpoint;
		_CrtMemCheckpoint(&exitpoint);//��¼�˳��ڴ����
		_CrtMemState diff;
		if (_CrtMemDifference(&diff, &enterpoint, &exitpoint))
		{//��������ڴ治һ�������ӡ
			_CrtMemDumpStatistics(&diff);
		}
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);//���ô��������۳�������˳��������ӡ�ڴ�й¶��Ϣ��output����_CrtDumpMemoryLeaks()��ȫ��
	//_CrtSetBreakAlloc(170);//170�����ڴ�й¶����ʱ�ڶ��ٴ������ڴ棬������ڴ˶ϵ�
	{
		CheckLocalMemLeak leakcheck;
		char* testone =(char*) malloc(10);
		free(testone);
	}
	{
		CheckLocalMemLeak leakcheck;
		char* testone = (char*)malloc(10);
	}

	CTestClassLeak* pTestClassNew = new CTestClassLeak();
	char* testMalloc = (char*)malloc(10);
	testMalloc = (char*)malloc(10);
	free(testMalloc);
	int i = 0;
	
	
	//_CrtDumpMemoryLeaks(); //�ֶ���ӡ�ڴ�й¶��Ϣ��output
	return 0;
}

