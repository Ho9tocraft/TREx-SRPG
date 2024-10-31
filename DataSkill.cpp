#include "trex_wrapper.h"

void DataSkill::setSkillLocalize(std::map<std::string, json11::Json> jsonFiles)
{
	for (std::pair<std::string, json11::Json> jsonFile : jsonFiles) {
		json11::Json json = jsonFile.second;
		//"contents.specific-skills-data.id-00000000"など
		localized_skill_name.insert_or_assign(jsonFile.first, json[this->unlocalized_skill_name_path].string_value());
		std::vector<std::string> descResult;
		json11::Json::array descJsons = json[this->unlocalized_skill_desc_path].array_items();
		for (json11::Json descJson : descJsons) {
			descResult.push_back(descJson.string_value());
		}
		localized_skill_desc.insert_or_assign(jsonFile.first, descResult);
	}
}

std::string DataSkill::getSkillName(std::string lang)
{
	return localized_skill_name.at(lang);
}

std::vector<std::string> DataSkill::getSkillDesc(std::string lang)
{
	return localized_skill_desc.at(lang);
}

DataSkill::DataSkill(std::string unlcl_sname_path, std::string unlcl_sdesc_path, std::map<std::string, json11::Json> LangFiles)
{
	this->unlocalized_skill_name_path = unlcl_sname_path;
	this->unlocalized_skill_desc_path = unlcl_sdesc_path;
	this->setSkillLocalize(LangFiles);
}

DataSkill::~DataSkill() {}

DataSkillPilot::DataSkillPilot(std::string unlcl_sname_path, std::string unlcl_sdesc_path,
	std::map<std::string, json11::Json> LangFiles) : DataSkill(unlcl_sname_path, unlcl_sdesc_path, LangFiles)
{}

bool DataSkillAttacker::skillCondition(GameUnit* unit)
{
	return unit->getMorale() >= 130LL;
}

void DataSkillAttacker::skillEffect(GameUnit*& unit)
{}

DataSkillAttacker::DataSkillAttacker(std::string unlcl_sname_path, std::string unlcl_sdesc_path,
		std::map<std::string, json11::Json> LangFiles) : DataSkillPilot(unlcl_sname_path, unlcl_sdesc_path, LangFiles)
{}

bool DataSkillDummy::skillCondition(GameUnit* unit)
{
	return false;
}

void DataSkillDummy::skillEffect(GameUnit*& unit)
{}

DataSkillDummy::DataSkillDummy(std::string unlcl_sname_path, std::string unlcl_sdesc_path,
		std::map<std::string, json11::Json> LangFiles) : DataSkillPilot(unlcl_sname_path, unlcl_sdesc_path, LangFiles)
{}
