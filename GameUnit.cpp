#include "trex_wrapper.h"

int64_t GameUnit::getMorale() const
{
	return this->Morale;
}

void GameUnit::increaseMoraleEvent(const int64_t valMorale)
{
	if      ((Morale + valMorale) > rided_pilot->getMaxMorale()) Morale = rided_pilot->getMaxMorale();
	else if ((Morale + valMorale) < rided_pilot->getMinMorale()) Morale = rided_pilot->getMinMorale();
	else Morale += valMorale;
}

void GameUnit::increaseMoraleCond(const MoraleIncreaseSituation situation)
{
	int64_t fluctuation = 0LL;
	switch (situation)
	{
	case MoraleIncreaseSituation::HIT_FROM_OWN:
		switch (this->rided_pilot->getPilotData()->getPilotPersonality())
		{
		case DataPilotPersonality::STRONG_MIND:
		case DataPilotPersonality::HARDWORKING:
		case DataPilotPersonality::SLY_CUNNING:
		case DataPilotPersonality::BRUTALITY:
			fluctuation = 1LL;
			break;
		case DataPilotPersonality::VERY_STRONG_MIND:
		case DataPilotPersonality::SERENITY:
		case DataPilotPersonality::BIGWIG:
			fluctuation = 2LL;
			break;
		case DataPilotPersonality::VERY_BIGWIG:
		case DataPilotPersonality::REMNANTS:
			fluctuation = 3LL;
			break;
		default:
			break;
		}
		break;
	case MoraleIncreaseSituation::AVOID_FROM_OWN:
		switch (this->rided_pilot->getPilotData()->getPilotPersonality())
		{
		case DataPilotPersonality::HARDWORKING:
			fluctuation = -2LL;
			break;
		case DataPilotPersonality::VERY_STRONG_MIND:
			fluctuation = -1LL;
			break;
		case DataPilotPersonality::STRONG_MIND:
		case DataPilotPersonality::SLY_CUNNING:
			fluctuation = 1LL;
			break;
		case DataPilotPersonality::QUICK_TEMPER:
		case DataPilotPersonality::BRUTALITY:
			fluctuation = 2LL;
			break;
		case DataPilotPersonality::OPTIMIST:
		case DataPilotPersonality::BIGWIG:
			fluctuation = 3LL;
			break;
		case DataPilotPersonality::VERY_BIGWIG:
			fluctuation = 4LL;
			break;
		case DataPilotPersonality::REMNANTS:
			fluctuation = 5LL;
			break;
		default:
			break;
		}
		break;
	case MoraleIncreaseSituation::KILLING_ENEMY_MAIN:
		fluctuation = 3LL;
		switch (this->rided_pilot->getPilotData()->getPilotPersonality())
		{
		case DataPilotPersonality::SERENITY:
			fluctuation -= 2LL;
			break;
		case DataPilotPersonality::QUICK_TEMPER:
		case DataPilotPersonality::BIGWIG:
		case DataPilotPersonality::VERY_BIGWIG:
			fluctuation += 1LL;
			break;
		case DataPilotPersonality::REMNANTS:
			fluctuation += 2LL;
			break;
		default:
			break;
		}
		break;
	case MoraleIncreaseSituation::KILLING_ENEMY_SUB:
		fluctuation = 2LL;
		switch (this->rided_pilot->getPilotData()->getPilotPersonality())
		{
		case DataPilotPersonality::SERENITY:
			fluctuation = 0LL;
			break;
		case DataPilotPersonality::NORMAL:
			fluctuation -= 1LL;
			break;
		case DataPilotPersonality::QUICK_TEMPER:
		case DataPilotPersonality::BIGWIG:
		case DataPilotPersonality::VERY_BIGWIG:
			fluctuation += 1LL;
			break;
		case DataPilotPersonality::REMNANTS:
			fluctuation += 3LL;
			break;
		default:
			break;
		}
		break;
	case MoraleIncreaseSituation::HIT_FROM_ENEMY:
		fluctuation = 1LL;
		switch (this->rided_pilot->getPilotData()->getPilotPersonality())
		{
		case DataPilotPersonality::REMNANTS:
			fluctuation = 0LL;
			break;
		case DataPilotPersonality::VERY_STRONG_MIND:
		case DataPilotPersonality::OPTIMIST:
		case DataPilotPersonality::QUICK_TEMPER:
		case DataPilotPersonality::SLY_CUNNING:
			fluctuation += 1LL;
			break;
		case DataPilotPersonality::BIGWIG:
		case DataPilotPersonality::BRUTALITY:
			fluctuation += 2LL;
			break;
		case DataPilotPersonality::VERY_BIGWIG:
			fluctuation += 3LL;
			break;
		default:
			break;
		}
		break;
	case MoraleIncreaseSituation::AVOID_FROM_ENEMY:
		switch (this->rided_pilot->getPilotData()->getPilotPersonality())
		{
		case DataPilotPersonality::STRONG_MIND:
		case DataPilotPersonality::CAREFUL:
		case DataPilotPersonality::HARDWORKING:
		case DataPilotPersonality::BRUTALITY:
			fluctuation = 1LL;
			break;
		case DataPilotPersonality::SERENITY:
		case DataPilotPersonality::BIGWIG:
			fluctuation = 2LL;
			break;
		case DataPilotPersonality::VERY_BIGWIG:
		case DataPilotPersonality::SLY_CUNNING:
			fluctuation = 3LL;
			break;
		default:
			break;
		}
		break;
	case MoraleIncreaseSituation::KILLING_ALLY:
		switch (this->rided_pilot->getPilotData()->getPilotPersonality())
		{
		case DataPilotPersonality::HARDWORKING:
			fluctuation = -1LL;
			break;
		case DataPilotPersonality::STRONG_MIND:
		case DataPilotPersonality::CAREFUL:
			fluctuation = 1LL;
			break;
		case DataPilotPersonality::VERY_STRONG_MIND:
		case DataPilotPersonality::QUICK_TEMPER:
		case DataPilotPersonality::SLY_CUNNING:
		case DataPilotPersonality::BRUTALITY:
			fluctuation = 2LL;
			break;
		case DataPilotPersonality::BIGWIG:
		case DataPilotPersonality::VERY_BIGWIG:
			fluctuation = 3LL;
			break;
		case DataPilotPersonality::REMNANTS:
			fluctuation = 15LL;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	this->increaseMoraleEvent(fluctuation);
}
