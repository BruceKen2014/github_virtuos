
#include "TestInline.h"
void TestNotInline(int& i)
{
	i++;
}

void classTestInline::TestNotInline(int& i)
{
	i++;
}


