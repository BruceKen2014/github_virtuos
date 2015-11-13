// CrtMemoryLeak.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#ifdef _DEBUG
#	define _CRTDBG_MAP_ALLOC //为了能够捕捉malloc的泄露，定义这个宏以后malloc会成为_malloc_dbg
#	define DEBUG_CLIENTBLOCK new(_CLIENT_BLOCK, __FILE__, __LINE__)
#	define new DEBUG_CLIENTBLOCK
#include <crtdbg.h>
#endif
/*
如果在#define DEBUG_CLIENTBLOCK new(_CLIENT_BLOCK, __FILE__, __LINE__)这个宏定义的后面又声明或者定义了operate new 函数，会导致宏替换而失败
STL的xdebug文件声明了operate new函数，所以这个宏应该放在STL头文件的后面
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
		_CrtMemCheckpoint(&enterpoint);//记录入口内存情况
	}
	~CheckLocalMemLeak()
	{
		_CrtMemState exitpoint;
		_CrtMemCheckpoint(&exitpoint);//记录退出内存情况
		_CrtMemState diff;
		if (_CrtMemDifference(&diff, &enterpoint, &exitpoint))
		{//如果两块内存不一样，则打印
			_CrtMemDumpStatistics(&diff);
		}
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);//调用此语句后，无论程序如何退出，均会打印内存泄露信息到output，比_CrtDumpMemoryLeaks()更全面
	//_CrtSetBreakAlloc(170);//170是在内存泄露发生时第多少次申请内存，程序会在此断点
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
	
	
	//_CrtDumpMemoryLeaks(); //手动打印内存泄露信息到output
	return 0;
}

