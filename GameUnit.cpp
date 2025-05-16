#include "stdafx.h"
#include "Main.h"
#include "DataPilot.h"
#include "DataPilotSkills.h"
#include "DataUnit.h"
#include "DataUnitSkills.h"
#include "GamePilot.h"
#include "GameUnit.h"

void GameUnit::setMorale(const int64_t moraleValue)
{
	int64_t tempMorale = moraleValue;
	if (tempMorale < 50) {
		//気力下限
		tempMorale = 50;
	}
	else if (tempMorale > 150) {
		//気力上限
		tempMorale = 150;
	}
	this->morale = tempMorale;
}

void GameUnit::increaseMorale(const int64_t moraleValue)
{
	this->setMorale(this->morale + moraleValue);
}

void GameUnit::recoverSP(const int64_t recoverVal)
{
	this->main_pilot->gainSP(recoverVal);
}
