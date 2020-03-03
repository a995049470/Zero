#include "JsonManager.h"

Document JsonManager::ReadFile(char * _name)
{
	Document d;
	char * json = File::Read(_name);
	d.Parse(json);
	delete[] json;
	return d;
}

float * JsonManager::JsonToFloatArray(Value value, int & len)
{
	assert(value.IsArray());
	len = value.Size();
	float * ptr = new float[len];
	for (int i = 0; i < len; i++)
	{
		ptr[i] = value[i].GetFloat();
	}
	return ptr;
}

int * JsonManager::JsonToIntArray(Value value, int & len)
{
	assert(value.IsArray());
	len = value.Size();
	int * ptr = new int[len];
	for (int i = 0; i < len; i++)
	{
		ptr[i] = value[i].GetInt();
	}
	return ptr;
}


