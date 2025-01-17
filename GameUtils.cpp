#include "All_Header_Wrapper.h"

DataPilotSkill* GameVariableUtils::ExtractPSkillFromDataMap(std::string const key)
{
	DataPilotSkill* sample = DataMapPilotSkills.contains(key) ? DataMapPilotSkills.at(key).get() :
			DataMapPilotSkills.at("Dummy").get();
//	if (instanceof<DataPilotSKillDummy>(sample)) return new DataPilotSKillDummy();
	return nullptr;
}

GameVariableUtils::GameVariableUtils()
{
	DataMapPilotSkills = {
		{ "Dummy", std::make_unique<DataPilotSkill>(new DataPilotSKillDummy()) }
	};
}
