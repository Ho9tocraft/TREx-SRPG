#include "trex_wrapper.h"

DataPilot* GamePilot::getPilotData()
{
	return this->data_pilot;
}

int64_t GamePilot::getMinMorale() const
{
	return this->minMorale;
}

int64_t GamePilot::getMaxMorale() const
{
	return this->maxMorale;
}

int GamePilot::getPilotStatus(const PilotStatsType statKey)
{
	return this->data_pilot->getPilotStats(statKey)
		+ this->pilotStatRevisions.at(StatusUpgradeType::TRAINING).at(statKey)
		+ this->pilotStatRevisions.at(StatusUpgradeType::LEVEL_UP).at(statKey);
}

std::map<PilotStatsType, int> GamePilot::getPilotStatus()
{
	return {
		{ PilotStatsType::MEL, (this->data_pilot->getPilotStats(PilotStatsType::MEL)
			+ this->pilotStatRevisions.at(StatusUpgradeType::TRAINING).at(PilotStatsType::MEL)
			+ this->pilotStatRevisions.at(StatusUpgradeType::LEVEL_UP).at(PilotStatsType::MEL))},
		{ PilotStatsType::RNG, (this->data_pilot->getPilotStats(PilotStatsType::RNG)
			+ this->pilotStatRevisions.at(StatusUpgradeType::TRAINING).at(PilotStatsType::RNG)
			+ this->pilotStatRevisions.at(StatusUpgradeType::LEVEL_UP).at(PilotStatsType::RNG))},
		{ PilotStatsType::MGC, (this->data_pilot->getPilotStats(PilotStatsType::MGC)
			+ this->pilotStatRevisions.at(StatusUpgradeType::TRAINING).at(PilotStatsType::MGC)
			+ this->pilotStatRevisions.at(StatusUpgradeType::LEVEL_UP).at(PilotStatsType::MGC))},
		{ PilotStatsType::DEX, (this->data_pilot->getPilotStats(PilotStatsType::DEX)
			+ this->pilotStatRevisions.at(StatusUpgradeType::TRAINING).at(PilotStatsType::DEX)
			+ this->pilotStatRevisions.at(StatusUpgradeType::LEVEL_UP).at(PilotStatsType::DEX))},
		{ PilotStatsType::DEF, (this->data_pilot->getPilotStats(PilotStatsType::DEF)
			+ this->pilotStatRevisions.at(StatusUpgradeType::TRAINING).at(PilotStatsType::DEF)
			+ this->pilotStatRevisions.at(StatusUpgradeType::LEVEL_UP).at(PilotStatsType::DEF))},
		{ PilotStatsType::ACU, (this->data_pilot->getPilotStats(PilotStatsType::ACU)
			+ this->pilotStatRevisions.at(StatusUpgradeType::TRAINING).at(PilotStatsType::ACU)
			+ this->pilotStatRevisions.at(StatusUpgradeType::LEVEL_UP).at(PilotStatsType::ACU))},
		{ PilotStatsType::AVD, (this->data_pilot->getPilotStats(PilotStatsType::AVD)
			+ this->pilotStatRevisions.at(StatusUpgradeType::TRAINING).at(PilotStatsType::AVD)
			+ this->pilotStatRevisions.at(StatusUpgradeType::LEVEL_UP).at(PilotStatsType::AVD))},
		{ PilotStatsType::RIT, (this->data_pilot->getPilotStats(PilotStatsType::RIT)
			+ this->pilotStatRevisions.at(StatusUpgradeType::TRAINING).at(PilotStatsType::RIT)
			+ this->pilotStatRevisions.at(StatusUpgradeType::LEVEL_UP).at(PilotStatsType::RIT))},
		{ PilotStatsType::SPR, (this->data_pilot->getPilotStats(PilotStatsType::SPR)
			+ this->pilotStatRevisions.at(StatusUpgradeType::TRAINING).at(PilotStatsType::SPR)
			+ this->pilotStatRevisions.at(StatusUpgradeType::LEVEL_UP).at(PilotStatsType::SPR))}
	};
}
