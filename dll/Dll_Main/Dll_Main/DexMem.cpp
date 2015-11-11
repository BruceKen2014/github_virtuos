
#include "stdafx.h"
#include "DexMem.h"
#pragma warning(disable:4996) 
DexMem::DexMem(int memSize)
{
	m_memSize = memSize;
	Reset();

}
DexMem::~DexMem()
{
	free(m_data);
}

void DexMem::Reset()
{
	m_mode = 0;
	m_data = (char*)malloc(sizeof(char)*m_memSize);
	memset(m_data, 0, sizeof(char)*m_memSize);
	m_curr = 0;
	m_length = 0;
}
void DexMem::BeginWrite()
{
	memset(m_data, 0, sizeof(char)*m_memSize);
	m_curr = 0;
}
void DexMem::BeginRead()
{
	m_curr = 0;
}

bool DexMem::End()
{
	return m_curr == m_length;
}
void DexMem::IniFromBuff(char* buff, int length)
{
	BeginWrite();
	memcpy(m_data, buff, length);
}

void DexMem::GetData(int offset, int size, DexMem& _out)
{
	if(offset + size > m_length)
		return;
	char ch[64]; //���ܷ������ �������ʾջ����Ĵ���
	memset(ch, 0, 64);
	while(size > 0)
	{
		if(size > 64)
		{
			memcpy((void*)&ch, &m_data[offset], 64 * sizeof(char));
			_out.AddBuffToEnd(ch, 64);
		}
		else
		{
			memcpy((void*)&ch, &m_data[offset], size * sizeof(char));
			_out.AddBuffToEnd(ch, size);
		}
		memset(ch, 0, 64);
		offset += 64;
		size -= 64;
	}
}
bool DexMem::IniFromFile(const char* filename)
{
	BeginWrite();
	FILE* hFile = NULL;
	hFile = fopen(filename, "rb");
	if(hFile == NULL)
	{
		return false;
	}
	fseek(hFile, 0, SEEK_END);
	m_length = ftell(hFile);
	fseek(hFile, 0, SEEK_SET);
	fread(m_data, m_length, 1, hFile);
	fclose(hFile);
	return true;
}

bool DexMem::IniFromFile(const char* filename, int offset, int size)
{
	BeginWrite();
	FILE* hFile = NULL;
	hFile = fopen(filename, "rb");
	if(hFile == NULL)
	{
		return false;
	}
	m_length = size;
	//��һ�汾���������
	fseek(hFile, offset, SEEK_SET);
	fread(m_data, m_length, 1, hFile);
	fclose(hFile);
	return true;
}

void DexMem::SaveToFile(const char* filename)
{
	BeginRead();
	FILE* hFile = NULL;
	hFile = fopen(filename, "w+");
	if(hFile == NULL)
	{
		return;
	}
	fseek(hFile, 0, SEEK_SET);
	fwrite((const void*)m_data, m_length, 1, hFile);
	fclose(hFile);
}
void DexMem::AddBuffToEnd(char* buff, int length)
{//�����Ѿ�������BeginWrite
	//cout<<"�򻺳���׷��buff��׷�ӳ���"<<length<<endl;
	memcpy(&m_data[m_curr], buff, length);
	m_length += length;
	m_curr += length;
	//cout<<"׷�����!"<<endl;
}
void DexMem::WriteToBuff(char* buff)
{
	BeginRead();
	memcpy(buff, m_data, m_length);
}

void DexMem::WriteString(char* ch)
{
	//cout<<"WriteStringд�룺"<<ch<<endl;

	strcpy(&m_data[m_curr], ch);
	//��������chԴ��С��&m_data[m_curr],���Բ��Ὣ\0����ȥ��
	
	m_curr += strlen(ch);
	m_data[m_curr++] = '\0'; //�����ַ����ָ�������������д���ַ����Ļ����Ὣ�����ִ�����һ��
	
	m_length += strlen(ch) + 1;
	//cout<<"WriteStringд����ϣ�"<<endl;
}

void DexMem::ReadString(char* ch)
{
	//cout<<"ReadString������..."<<endl;

	strcpy(ch, &m_data[m_curr]); //��ʱch�Ĵ�Сһ������m_data[m_curr],�ڿ�����ʱ�����������ֶ�
	//�����\0,��ֹͣ����
	m_curr += strlen(ch) + 1; //Ҫ������һ��\0

	//cout<<"ReadString������ϣ�ֵΪ��"<<ch<<endl;
}
