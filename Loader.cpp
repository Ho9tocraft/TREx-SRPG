#include "stdafx.h"
#include "Main.h"
#include "Loader.h"
#include "DataPilot.h"
#include "DataPilotSkills.h"
#include "DataUnit.h"
#include "DataUnitSkills.h"
#include "GamePilot.h"
#include "GameUnit.h"

std::string Loader::openTextFile(const std::string& path)
{
	using namespace std;
	ifstream ifs(path, ios::binary);
	stringstream buffer;
	buffer << ifs.rdbuf();
	string str = buffer.str();
	if (str[0] == -17 && str[1] == -69 && str[2] == -65) str = str.substr(3);
	return str;
}

json11::Json Loader::parseResource(const std::string& path)
{
	std::string raw_string = utf8_to_sjis(this->openTextFile(path));
	std::string err;
	json11::Json parsed = json11::Json::parse(raw_string, err, json11::COMMENTS);
	if (!err.empty()) {
		std::string error_message = "json parser error: " + err;
		throw std::exception(error_message.c_str());
	}
	return parsed;
}

void Loader::registeringPilot(std::string key, json11::Json raw_data)
{
	this->register_pilots.insert_or_assign(key, std::make_shared<DataPilot>(raw_data));
}

void Loader::registeringUnit(std::string key, json11::Json raw_data)
{
	this->register_units.insert_or_assign(key, std::make_shared<DataUnit>(raw_data));
}
