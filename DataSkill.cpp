#include "trex_wrapper.h"

void DataSkill::setSkillLocalize(std::map<std::string, json11::Json> jsonFiles)
{
	std::string unlcl_sname_path = this->unlocalized_skill_name_path;
	std::string unlcl_sdesc_path = this->unlocalized_skill_desc_path;
	for (std::pair<std::string, json11::Json> jsonFile : jsonFiles) {
		json11::Json json = jsonFile.second;
		//"contents.specific-skills-data.id-00000000"など
		this->localized_skill_name.insert_or_assign(jsonFile.first, json[unlcl_sname_path]);
		std::vector<std::string> descResult;
		json11::Json::array descJsons = json[unlcl_sdesc_path].array_items();
		for (json11::Json descJson : descJsons) {
			descResult.push_back(descJson.string_value());
		}
		this->localized_skill_desc.insert_or_assign(jsonFile.first, descResult);
	}
}

DataSkill::DataSkill(std::string unlcl_sname_path, std::string unlcl_sdesc_path, std::map<std::string, json11::Json> LangFiles)
{
	this->unlocalized_skill_name_path = unlcl_sname_path;
	this->unlocalized_skill_desc_path = unlcl_sdesc_path;
	this->setSkillLocalize(LangFiles);
}

DataSkill::~DataSkill() {}
