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

void Loader::initializeConfigureData()
{
	std::string path = "./config.json";
	std::ifstream ifs(path);
	if (!ifs) {
		std::map<std::string, int> resolution {{"width", 1600},{"height", 900}};
		json11::Json config = json11::Json::object {
			{ "window", resolution }
		};
		std::ofstream ofs(path);
		ofs << config.dump() << std::endl;
		ofs.close();
	}
}

void Loader::registeringPilot(json11::Json raw_data)
{
	std::shared_ptr<DataPilot> tmpPilot = std::make_shared<DataPilot>(raw_data);
	this->registry_pilots.insert_or_assign(sjis_to_utf8(tmpPilot->profile.getFullname()), std::move(tmpPilot));
}

void Loader::registeringPilot(std::string key, json11::Json raw_data)
{
	this->registry_pilots.insert_or_assign(key, std::make_shared<DataPilot>(raw_data));
}

void Loader::registeringUnit(json11::Json raw_data)
{
	std::shared_ptr<DataUnit> tmpUnit = std::make_shared<DataUnit>(raw_data);
	this->registry_units.insert_or_assign(sjis_to_utf8(tmpUnit->profile.getUFullname()), std::move(tmpUnit));
}

void Loader::registeringUnit(std::string key, json11::Json raw_data)
{
	this->registry_units.insert_or_assign(key, std::make_shared<DataUnit>(raw_data));
}

std::string Loader::loadPath(LoaderHandlerType hType, std::string path)
{
	std::string result = "./Resources/";
	switch (hType)
	{
	case LoaderHandlerType::DATA_PILOT:
		result += "datas/datapacks/pilots.json";
		break;
	case LoaderHandlerType::DATA_UNIT:
		result += "datas/datapacks/units.json";
		break;
	case LoaderHandlerType::DATA_SP:
		result += "datas/datapacks/sp.json";
		break;
	case LoaderHandlerType::DATA_STAGES:
		result += ("datas/datapacks/stages/" + path);
		break;
	case LoaderHandlerType::GRAPH_PILOT:
		result += ("images/pilot/" + path);
		break;
	case LoaderHandlerType::GRAPH_UNIT:
		result += ("images/unit/" + path);
		break;
	case LoaderHandlerType::GRAPH_USER_INTERFACE:
		result += ("images/ui" + path);
		break;
	case LoaderHandlerType::AUDIO:
		result += ("audio/" + path);
		break;
	default:
		break;
	}
	return result;
}

std::shared_ptr<DataPilotSkills> Loader::findSkill(std::string SS_typename)
{
	auto result = this->registry_pskills.find(SS_typename);
	if (result != this->registry_pskills.end()) return result->second;
	return this->registry_pskills.at("ダミー");
}

Loader::Loader()
{
	this->initializeConfigureData();
	this->registry_pskills.insert_or_assign("ダミー", std::make_shared<DPilotSkillDummy>());
	this->unitGraphResolution = 0;
}
