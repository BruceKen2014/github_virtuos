// MultiThread.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <queue>

#include "TestInline.h"
using namespace std;

CRITICAL_SECTION  g_cs;
HANDLE  g_mutex;
void print(int iThreadId)
{
	//WaitForSingleObject(g_mutex, INFINITE);
	//cout << "thread " << iThreadId << " print " << endl;
	//ReleaseMutex(g_mutex);

	EnterCriticalSection(&g_cs);
	cout << "thread " << iThreadId << " print " << endl;
	LeaveCriticalSection(&g_cs);
}
HANDLE event;
HANDLE event2;
DWORD WINAPI ThreadFunction1(LPVOID lpParam)
{
	cout << " create thread1 " << endl;
	while (1)
	{
		WaitForSingleObject(event, INFINITE);
		cout << " accept event1 " << endl;
		SetEvent(event2);
		ResetEvent(event);
	}
	return 0;
}
DWORD WINAPI ThreadFunction2(LPVOID lpParam)
{
	cout << " create thread2 " << endl;
	while (1)
	{
		WaitForSingleObject(event2, INFINITE);
		cout << " accept event2 " << endl;
		ResetEvent(event2);
	}
	return 0;
}
DWORD WINAPI ThreadFunction3(LPVOID lpParam)
{
	cout << " create thread3 " << endl;
	while (1)
	{
		print(3);
	}
	return 0;
}
DWORD WINAPI ThreadFunction4(LPVOID lpParam)
{
	cout << " create thread4 " << endl;
	while (1)
	{
		print(4);
	}
	return 0;
}

template<typename T>
class DexQueue
{
	queue<T> m_que;
	HANDLE mutex;

public:
	DexQueue()
	{
		mutex = CreateMutex(NULL, FALSE, NULL);
	}
	void push(const T& value)
	{
		WaitForSingleObject(mutex, INFINITE);
		queue.push(value);
		ReleaseMutex(mutex);
	}
	T getAndPop()
	{
		WaitForSingleObject(mutex, INFINITE);
		T ret = queue.front();
		queue.pop();
		return ret;
		ReleaseMutex(mutex);
	}
};
#define MACROADD(x)  (x++)
int _tmain(int argc, _TCHAR* argv[])
{
	int testI = 0;
	testI++;
	MACROADD(testI);
	TestInline(testI);  
	TestNotInline(testI);
	classTestInline t;
	t.TestInline(testI);
	t.TestInline2(testI);
	t.TestNotInline(testI);
	event  = CreateEvent(NULL, TRUE, FALSE, "UserEventName1");
	event2 = CreateEvent(NULL, TRUE, FALSE, "UserEventName2");
	InitializeCriticalSection(&g_cs);
	EnterCriticalSection(&g_cs);
	LeaveCriticalSection(&g_cs);
	g_mutex = CreateMutex(NULL, FALSE, NULL);
	HANDLE handleThread1, handleThread2;
	DWORD  dwdHandleId1, dwdHandleId2;
	handleThread1 = CreateThread(NULL, 0, ThreadFunction1, NULL, 0, &dwdHandleId1);
	handleThread2 = CreateThread(NULL, 0, ThreadFunction2, NULL, 0, &dwdHandleId2);
	CloseHandle(handleThread1);
	CloseHandle(handleThread2);
	CreateThread(NULL, 0, ThreadFunction3, NULL, 0, NULL);
	CreateThread(NULL, 0, ThreadFunction4, NULL, 0, NULL);
	while (1)
	{

	}
	return 0;
}

