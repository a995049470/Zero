#pragma once
#include "File.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <assert.h>

using namespace rapidjson;

class JsonManager
{
public:
	static Document ReadFile(char * _name);
	static float * JsonToFloatArray(Value value, int& len);
	static int * JsonToIntArray(Value value, int& len);
};

