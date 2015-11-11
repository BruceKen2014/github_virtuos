

/*
Dex������Զ���ṹ�������л�
*/
#ifndef _DEX_MEM_H
#define _DEX_MEM_H
#include <string>


//Ĭ���ṩ���ڴ��СΪ10M
#define  MEM_DEFAULT_BUFF (10 * 1024*1024)
class DexMem
{
public:
	enum
	{
		MEM_READ = 0,
		MEM_WRITE = 1
	};
protected:
	bool    m_mode; //0:�������� 1���������
	char*   m_data;
	size_t     m_length;
	size_t     m_curr;
	int     m_memSize; //�����Բ��ݵ��ڴ��С

public:
	DexMem(int memSize = MEM_DEFAULT_BUFF);
	~DexMem();
	void Reset();
public:
	
	//friend DexMem& operator << (bool args);
	//friend DexMem& operator << (int args);
	//friend DexMem& operator << (short args);
	//friend DexMem& operator << (char args);
	//friend DexMem& operator << (string args);
	//friend DexMem& operator >> (bool args);
	//friend DexMem& operator >> (int args);
	//friend DexMem& operator >> (short args);
	//friend DexMem& operator >> (char args);
	//friend DexMem& operator >> (string args);
	char* GetData()		{return m_data;}
	void  GetData(int offset, int size, DexMem& _out); //��ָ��ƫ�ƴ�ȡ��ָ�����ȵ����ݵ�_out��
	int   GetLength()	{return (int)m_length;}
	void BeginWrite();
	void BeginRead();
	bool End();
	void IniFromBuff(char* buff, int length);
	bool IniFromFile(const char* filename); //���������ļ�
	bool IniFromFile(const char* filename, int offset, int size); //����һ���ļ��еĲ�������
	void SaveToFile(const char* filename);
	void AddBuffToEnd(char* buff, int length); //׷��buff����
	void WriteToBuff(char* buff);	
	void WriteString(char* ch);
	void ReadString(char* ch);

	//����ģ�庯����ʵ�ֲ��ܷ���cpp�ļ��У���˱㲻��������ϸ��
	//�������ģ��Ļ�������Ҫ���ض��Write����
	//����պ�Ҫ����������ʹ�ã��ɿ������صķ���
	//TODO:�������������ʱ����һЩ���⴦���Ѵﵽ���ܵ�Ŀ��
	template<typename T>
	void Write(const T& _In)
	{
		memcpy(&m_data[m_curr], &_In, sizeof(T));
		m_length += sizeof(T);
		m_curr += sizeof(T);
	}
	template<typename T>
	void Read(T& _Out)
	{
		memcpy((void*)&_Out, &m_data[m_curr], sizeof(T));
		m_curr += sizeof(T);
	}
	template<typename T>
	friend DexMem& operator << (DexMem& mem, const T& _In)
	{
		mem.Write(_In);
		return mem;
	}
	template<typename T>
	friend DexMem& operator >> (DexMem& mem, T& _Out)
	{
		mem.Read(_Out);
		return mem;
	}

};
/*
ע�⣺
1�����ڴ����struct ���ṹ�����������ݶ���Ҫarchive��struct,�����������<< >>
   ֱ�ӵ���mem<<param �� mem<<param ���ɣ���Ϊ<< >>��ֱ�Ӷ��ڴ���в���
2�����ܶ�char*���ͽ���<< >> ���� ��Ϊsizeofȥ�ĽṹΪ4 ��һ��ָ��Ĵ�С���Ӷ��ַ�������
   ��ʧ�ܣ�������ReadString WriteString
3�����ܶ�string����<< >> Ҳ������ReadString WriteString����Ϊstring��sizeof������string
   ��ǰ���ֽ������ı�
*/

#endif