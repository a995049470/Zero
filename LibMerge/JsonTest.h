#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "File.h"

using namespace rapidjson;

void jt()
{
	auto json = File::Read("j1.json");
	Document d;
	d.Parse(json);
	string name = d["name"].GetString();
	int age = d["age"].GetInt();
	cout << age << endl;
	
	while (true)
	{

	}
}