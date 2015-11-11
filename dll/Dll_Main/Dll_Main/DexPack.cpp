
#include "stdafx.h"
#include "DexMem.h"
#include "DexPack.h"


DexPack::DexPack(int size)
{
	m_handler = new DexMem(size);
}

DexPack::~DexPack()
{
	if (m_handler != NULL)
		delete(m_handler);
	m_handler = NULL;
}

void DexPack::Pack(const char* filename, int fileIndex)
{

}