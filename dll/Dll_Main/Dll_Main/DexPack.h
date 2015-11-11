

#ifndef _Dex_PACK
#define _Dex_PACK

class DexMem;
class DexPack
{
private:
	DexMem*  m_handler;
public:
	DexPack(int size);
	~DexPack();
public:
	void Pack(const char* filename, int fileIndex);
	void SaveToFile(const char* filename);
};
#endif // !_Dex_PACK
