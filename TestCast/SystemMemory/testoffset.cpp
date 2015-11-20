
#include "stdafx.h"
#include "TestDefine.h"
/*
左移：最高位丢弃，最低位补0
右移：最低位丢弃
	  如果有符号数，最高位补符号位，算术右移
	  如果无符号，最高位补0，逻辑右移
*/
#ifdef _test_offset

int _tmain(int argc, _TCHAR* argv[])
{
	//正数左移
	int i_0 = 0x40000000;
	int i_1 = i_0 << 1; //左移一位后导致最高位为1，变成了32位整形里面最小的负数-2147483648
	int i_2 = i_1 << 1; //再左移一位，最高位1被挤出去了，变成了0
	
	//负数左移
	int i_3 = 0xffffffff;   //-1
	int i_4 = i_3 << 1;		//-2
	int i_5 = i_4 << 1;		//-4

	int i_6 = 0x80000000;
	int i_7 = i_6 >> 1;   //有符号数，右移最高位补符号位
	
	unsigned int i_8 = 0x00000100;
	unsigned int i_9 = i_8 >> 1; //无符号数，最高位补0
	return 0;
}

#endif 
