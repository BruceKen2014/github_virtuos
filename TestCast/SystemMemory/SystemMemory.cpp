
#include "stdafx.h"
#include "TestDefine.h"
/*
WIN32：只要包含了windows.h 这个宏就会被定义，同时在project的预编译宏里面，默认创建时也会有WIN32宏
WIN64：目前没有发现任何地方有这个宏定义，只能自己在project的预编译宏里面针对64位进行手动添加
_WIN32：没有显式定义，只要是用visual C++开发的项目，这个宏定义都存在
_WIN64：没有显示定义，在x64配置下才存在

针对以上几点
判断是否是windows平台的代码
#ifdef WIN32
...
#endif
判断Windows下是否是64位程序
#ifdef _WIN64
...
#endif

*/
#ifdef _system_memory
#include <windows.h>
#include <iostream>
using namespace std;

class OSOperator
{

public:
	bool getSystemMemory(int& total, int& avail, int& percent);
};
bool OSOperator::getSystemMemory(int& total, int& avail, int& percent)
{
#ifdef _WIN64
	MEMORYSTATUSEX memoryStatusEx;
	memoryStatusEx.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memoryStatusEx);

	percent = (int)(memoryStatusEx.dwMemoryLoad); //当前已使用的内存百分比
	total = (int)(memoryStatusEx.ullTotalPhys >> 10); //总共内存
	avail = (int)(memoryStatusEx.ullAvailPhys >> 10); //可用内存
#else 
	MEMORYSTATUS memoryStatus;
	memoryStatus.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memoryStatus);

	percent = (int)(memoryStatus.dwMemoryLoad);
	total = (int)(memoryStatus.dwTotalPhys >> 10);
	avail = (int)(memoryStatus.dwAvailPhys >> 10);
#endif


	return true;
}
int _tmain(int argc, _TCHAR* argv[])
{
	OSOperator opertor;
	int total, avail, percent;
	opertor.getSystemMemory(total, avail, percent);
	int total_g = total / (1000*1000);
	int total_m = total /1000 - total_g * 1000;
	int total_k = total - total_g * (1000 * 1000) - total_m * 1000;

	int avail_g = avail / (1000 * 1000);
	int avail_m = avail / 1000 - avail_g * 1000;
	int avail_k = avail - avail_g * (1000 * 1000) - avail_m * 1000;
	cout << "total:" << total_g << "G " << total_m << "M " << total_k <<"K"<<endl;
	cout << "already use percent:" << percent << "%" << endl;
	cout << "avail:" << avail_g << "G " << avail_m << "M " << avail_k << "K" << endl;
	return 0;
}

#endif 
