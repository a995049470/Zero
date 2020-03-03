#include "File.h"


char* File::Read(const char * path)
{
	std::string fileStr;
	std::ifstream file;
	// ��֤ifstream��������׳��쳣��
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// ���ļ�
		file.open(path);
		std::stringstream fileStream;
		// ��ȡ�ļ��Ļ������ݵ���������
		fileStream << file.rdbuf();
		// �ر��ļ�������
		file.close();
		// ת����������string
		fileStr = fileStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ  " << path << std::endl;
	}
	int len = fileStr.length() + 1;
	char* ptr = new char[len];
	//cout << fileStr.length() << endl;
	strcpy_s(ptr, len, fileStr.c_str());
	return ptr;
}
