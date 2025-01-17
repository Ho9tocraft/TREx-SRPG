#include "All_Header_Wrapper.h"

DataPilotSkill* GameVariableUtils::ExtractPSkillFromDataMap(std::string const key)
{
	DataPilotSkill* sample = DataMapPilotSkills.contains(key) ? DataMapPilotSkills.at(key).get() :
			DataMapPilotSkills.at("Dummy").get();
	if (instanceof<DataPilotSkillDummy>(sample)) return new DataPilotSkillDummy(dynamic_cast<DataPilotSkillDummy*>(sample));
	else return nullptr;
}

GameVariableUtils::GameVariableUtils()
{
	DataMapPilotSkills = {
		{ "Dummy", std::make_unique<DataPilotSkill>(new DataPilotSkillDummy()) }
	};
}
