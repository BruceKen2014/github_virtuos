

#ifndef TESTINLINE
#define TESTINLINE

inline void TestInline(int& i)
{
	i++;
}
class classTestInline
{
public:
	void TestInline(int& i)
	{
		i++;
	}
	void TestInline2(int& i);
	void TestNotInline(int& i);
};
inline void classTestInline::TestInline2(int& i)
{
	i++;
}
void TestNotInline(int& i);

#endif