// TestCast.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
class BaseClass
{
	virtual void func(){}
};
class A :public BaseClass
{

};
class B :public A
{

};
class C
{
	virtual void funcC(){}
};
void g_fun()
{

}
int _tmain(int argc, _TCHAR* argv[])
{
	A* ins_a1 = new A;
	B* ins_b1 = new B;
	C* ins_c1 = new C;

	A* ins_a2 = dynamic_cast<A*> (ins_b1);

	B* ins_b2 = dynamic_cast<B*> (ins_a1);
	B* ins_b3 = dynamic_cast<B*> (ins_c1);
	B* ins_b4 = static_cast<B*> (ins_a1);//
	B* ins_b5 = reinterpret_cast<B*>(g_fun);
	B* ins_b6 = (B*)g_fun;
	B ins_b7 = reinterpret_cast<B&>(*ins_a2);
	float f_1 = 1.65f;
	int	  int_2 = (int)f_1;
	int   int_3 = *(int*)(&f_1);
	int   int_1 = *reinterpret_cast<int*> (&f_1);

	const int int_4 = 6;
	int* int_p1 = const_cast<int*>(&int_4);
	*int_p1 = 1;
	return 0;
}

