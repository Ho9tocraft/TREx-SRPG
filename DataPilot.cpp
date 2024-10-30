#include "trex_wrapper.h"

int DataPilotStats::getPilotStats(PilotStatsType statKey) const
{
	int result = 0;
	switch (statKey)
	{
	case PilotStatsType::MEL:
		result = MELEE;
		break;
	case PilotStatsType::RNG:
		result = RANGED;
		break;
	case PilotStatsType::MGC:
		result = MAGIC;
		break;
	case PilotStatsType::DEX:
		result = DEXTERITY;
		break;
	case PilotStatsType::DEF:
		result = DEFENCE;
		break;
	case PilotStatsType::ACU:
		result = ACCURACY;
		break;
	case PilotStatsType::AVD:
		result = AVOIDANCE;
		break;
	case PilotStatsType::RIT:
		result = RESISTANCE;
		break;
	case PilotStatsType::SPR:
		result = SPIRITUALS;
		break;
	default:
		break;
	}
	return result;
}

DataPilotStats::DataPilotStats(int defined_melee, int defined_ranged, int defined_magic, int defined_dexterity, int defined_defence,
		int defined_accuracy, int defined_avoidance, int defined_resistance, int defined_spirituals)
{
	MELEE = defined_melee >= 0 ? defined_melee : 0;
	RANGED = defined_ranged >= 0 ? defined_ranged : 0;
	MAGIC = defined_magic >= 0 ? defined_magic : 0;
	DEXTERITY = defined_dexterity >= 0 ? defined_dexterity : 0;
	DEFENCE = defined_defence >= 0 ? defined_defence : 0;
	ACCURACY = defined_accuracy >= 0 ? defined_accuracy : 0;
	AVOIDANCE = defined_avoidance >= 0 ? defined_avoidance : 0;
	RESISTANCE = defined_resistance >= 0 ? defined_resistance : defined_avoidance >= 0 ? defined_avoidance : 0;
	SPIRITUALS = defined_spirituals >= 0 ? defined_spirituals : 0;
}

DataPilotStats::DataPilotStats() : DataPilotStats(0, 0, 0, 0, 0, 0, 0, 0, 0) {}

DataPilotStats::DataPilotStats(const DataPilotStats& rhs) : DataPilotStats(
			rhs.MELEE, rhs.RANGED, rhs.MAGIC, rhs.DEXTERITY, rhs.DEFENCE,
			rhs.ACCURACY, rhs.AVOIDANCE, rhs.RESISTANCE, rhs.SPIRITUALS) {}

DataPilotStats& DataPilotStats::operator=(const DataPilotStats& rhs)
{
	MELEE = rhs.MELEE;
	RANGED = rhs.RANGED;
	MAGIC = rhs.MAGIC;
	DEXTERITY = rhs.DEXTERITY;
	DEFENCE = rhs.DEFENCE;
	ACCURACY = rhs.ACCURACY;
	AVOIDANCE = rhs.AVOIDANCE;
	RESISTANCE = rhs.RESISTANCE;
	SPIRITUALS = rhs.SPIRITUALS;
	return *this;
}

int DataPilot::getPilotStats(PilotStatsType statKey)
{
	return this->pilotDefaultStats.getPilotStats(statKey);
}

DataPilotGender DataPilot::getPilotGender() const
{
	return this->pilotGender;
}

DataPilotPersonality DataPilot::getPilotPersonality() const
{
	return this->pilotPersonality;
}

DataPilot::DataPilot(json11::Json pilotData)
{
	this->data_id = pilotData["data_id"].int_value();
	this->unlocal_fullname_path = pilotData["fullname"].string_value();
	this->unlocal_nickname_path = pilotData["nickname"].string_value();
	this->unlocal_readname_path = pilotData["readname"].string_value();
	this->unlocal_codename_path = pilotData["codename"].string_value();
	this->pilotGender = static_cast<DataPilotGender>(pilotData["gender"].int_value());
	this->pilotPersonality = static_cast<DataPilotPersonality>(pilotData["personality"].int_value());
	this->pilotDefaultStats = DataPilotStats(
		pilotData["pilot_status"]["MEL"].int_value(), pilotData["pilot_status"]["RNG"].int_value(),
		pilotData["pilot_status"]["MGC"].int_value(), pilotData["pilot_status"]["DEX"].int_value(),
		pilotData["pilot_status"]["DEF"].int_value(), pilotData["pilot_status"]["ACU"].int_value(),
		pilotData["pilot_status"]["AVD"].int_value(), pilotData["pilot_status"]["RIT"].int_value(),
		pilotData["pilot_status"]["SPR"].int_value());
	this->pilotTerrainAdapts = {
		{ DataTerrainType::AIR, static_cast<DataTerrainAdapt>(pilotData["terrain_adaption"]["air"].int_value()) },
		{ DataTerrainType::GROUND, static_cast<DataTerrainAdapt>(pilotData["terrain_adaption"]["ground"].int_value()) },
		{ DataTerrainType::UNDERWATER, static_cast<DataTerrainAdapt>(pilotData["terrain_adaption"]["underwater"].int_value()) },
		{ DataTerrainType::SEA_OF_THE_STARS, static_cast<DataTerrainAdapt>(pilotData["terrain_adaption"]["outerworld"].int_value()) }
	};
}
