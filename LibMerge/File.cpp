#include "File.h"


char* File::Read(const char * path)
{
	std::string fileStr;
	std::ifstream file;
	// 保证ifstream对象可以抛出异常：
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// 打开文件
		file.open(path);
		std::stringstream fileStream;
		// 读取文件的缓冲内容到数据流中
		fileStream << file.rdbuf();
		// 关闭文件处理器
		file.close();
		// 转换数据流到string
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
