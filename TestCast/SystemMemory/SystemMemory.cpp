
#include "stdafx.h"
#include "TestDefine.h"
/*
WIN32��ֻҪ������windows.h �����ͻᱻ���壬ͬʱ��project��Ԥ��������棬Ĭ�ϴ���ʱҲ����WIN32��
WIN64��Ŀǰû�з����κεط�������궨�壬ֻ���Լ���project��Ԥ������������64λ�����ֶ����
_WIN32��û����ʽ���壬ֻҪ����visual C++��������Ŀ������궨�嶼����
_WIN64��û����ʾ���壬��x64�����²Ŵ���

������ϼ���
�ж��Ƿ���windowsƽ̨�Ĵ���
#ifdef WIN32
...
#endif
�ж�Windows���Ƿ���64λ����
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

	percent = (int)(memoryStatusEx.dwMemoryLoad); //��ǰ��ʹ�õ��ڴ�ٷֱ�
	total = (int)(memoryStatusEx.ullTotalPhys >> 10); //�ܹ��ڴ�
	avail = (int)(memoryStatusEx.ullAvailPhys >> 10); //�����ڴ�
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
