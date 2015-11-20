

#ifndef _TEST_DEFINE_H
#define _TEST_DEFINE_H

#include <iostream>
using namespace std;
/*
要添加新的测试文件，先添加一个标志改文件的宏，然后新建cpp文件，将testfiletemplate.cpp里面的文件内容覆盖
新的文件，并替换_new_test_name为对应的宏即可
*/
//以下测试宏只能同时定义一个

//#define _system_memory   //获取系统内存例子
#define _test_offset	 //测试左移右移操作符
#endif