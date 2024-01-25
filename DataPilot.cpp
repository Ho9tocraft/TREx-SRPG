#include "all_loaders.h"

string DataPilot::getPilotUnlocalizedFullname() const
{
	return this->pilotUnlocalizedFullname;
}

string DataPilot::getPilotUnlocalizedNickname() const
{
	return this->pilotUnlocalizedNickname;
}

string DataPilot::getPilotUnlocalizedReadname() const
{
	return this->pilotUnlocalizedReadname;
}

string DataPilot::getPilotUnlocalizedCodename() const
{
	return this->pilotUnlocalizedCodename;
}

EnumPilotGender DataPilot::getPilotGender() const
{
	return this->pilotGender;
}

EnumPilotPersonality DataPilot::getPilotPersonality() const
{
	return this->pilotPersonality;
}

map<EnumPilotStatusCategory, int64_t> DataPilot::getPilotStatus() const
{
	return this->pilotStatus;
}

map<EnumTerrainType, EnumTerrainAdaption> DataPilot::getPilotTerrainAdaption() const
{
	return this->pilotTerrainAdaption;
}

vector<DataSpecificSkills*> DataPilot::getPilotSpecificSkills() const
{
	return this->pilotSpecificSkills;
}
