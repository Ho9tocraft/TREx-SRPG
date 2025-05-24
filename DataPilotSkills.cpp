#include "stdafx.h"
#include "Main.h"
#include "Loader.h"
#include "DataPilot.h"
#include "DataPilotSkills.h"
#include "DataUnit.h"
#include "DataUnitSkills.h"
#include "GamePilot.h"
#include "GameUnit.h"

DataPilotSkills::DataPilotSkills(std::string pRegName, std::string pDispName, std::vector<std::string> pDesc, std::vector<int64_t> pLvDef,
		std::vector<int64_t> pLvLrn, bool pUnique, double pAtkBuffPct, double pLuckPct, double pComHitPct, double pComEvdPct,
		double pOwnHitPct, double pOwnEvdPct, double pOwnCrtPct, int64_t pSPRegenVal, double pConsumeSPDecr)
{
	this->SS_registryName = pRegName;
	this->SS_displayName = pDispName;
	this->SS_description = std::vector<std::string>(pDesc);
	this->SS_levelDefine = std::vector<int64_t>(pLvDef);
	this->SS_levelLearn = std::vector<int64_t>(pLvLrn);
	this->SS_uniqueSkill = pUnique;
	this->SS_atkBuffPercent = pAtkBuffPct;
	this->SS_luckPercent = pLuckPct;
	this->SS_incrHitPercentCommanding = pComHitPct;
	this->SS_incrEvadePercentCommanding = pComEvdPct;
	this->SS_incrHitPercentOwner = pOwnHitPct;
	this->SS_incrEvadePercentOwner = pOwnEvdPct;
	this->SS_incrCriticalPercentOwner = pOwnCrtPct;
	this->SS_SPRegenerateValue = pSPRegenVal;
	this->SS_ConsumeSPDecreasePercent = pConsumeSPDecr;
}

std::string DataPilotSkills::getRegName() const
{
	return this->SS_registryName;
}

std::string DataPilotSkills::getDispName() const
{
	return this->SS_displayName;
}

std::vector<std::string> DataPilotSkills::getDescription() const
{
	return this->SS_description;
}

bool DataPilotSkills::getIsUnique() const
{
	return this->SS_uniqueSkill;
}

bool DataPilotSkills::calcSkillLearned(std::shared_ptr<GamePilot> owner)
{
	int64_t tempLv = owner->getLevel();
	if (tempLv >= this->SS_levelLearn[0]) return true;
	return false;
}

int64_t DataPilotSkills::calcSkillLevel(std::shared_ptr<GamePilot> owner)
{
	int64_t index = 0LL;
	for (uint64_t i = 0; i < this->SS_levelLearn.size(); i++) {
		if (owner->getLevel() >= this->SS_levelLearn.at(i)) {
			index = i;
		} else break;
	}
	return this->SS_levelDefine.at(index);
}

double DataPilotSkills::calcAttackBuffPercent(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0.0;
}

int64_t DataPilotSkills::calcAttackBuffConstant(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0;
}

double DataPilotSkills::calcArmorBuffPercent(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0.0;
}

double DataPilotSkills::calcDamageDecrPercent(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0.0;
}

int64_t DataPilotSkills::calcMoveRangeIncrease(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0;
}

int64_t DataPilotSkills::calcWeaponRangeIncrease(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0;
}

double DataPilotSkills::calcHitCommanding(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0.0;
}

double DataPilotSkills::calcEvadeCommanding(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0.0;
}

double DataPilotSkills::calcHitOwner(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0.0;
}

double DataPilotSkills::calcEvadeOwner(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0.0;
}

double DataPilotSkills::calcCriticalOwner(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0.0;
}

int64_t DataPilotSkills::calcSPRegenerate(std::shared_ptr<GamePilot> owner)
{
	return 0;
}

bool DataPilotSkills::canBeSupport(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return false;
}

bool DataPilotSkills::canBeSAttack(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return false;
}

bool DataPilotSkills::canBeSDefence(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return false;
}

bool DataPilotSkills::canBeCounter(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return false;
}

bool DataPilotSkills::isActiveReverseStrength(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return false;
}

int64_t DataPilotSkills::calcSPUp(std::shared_ptr<GamePilot> owner)
{
	return 0;
}

int64_t DataPilotSkills::calcHitStat(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0;
}

int64_t DataPilotSkills::calcEvadeStat(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0;
}

int64_t DataPilotSkills::calcMoraleOverdrive(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return 0;
}

bool DataPilotSkills::canREAttack(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return false;
}

bool DataPilotSkills::isFocusAttackAvailable(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return false;
}

bool DataPilotSkills::isHitAndAway(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return false;
}

int64_t DataPilotSkills::calcIncrMoraleCond(std::shared_ptr<GamePilot> owner, DIncrMoraleCond pCond, bool isMain)
{
	return 0;
}

double DataPilotSkills::calcConsumeSPDecr(std::shared_ptr<GamePilot> owner)
{
	return 0.0;
}

bool DataPilotSkills::canRepSupExtraAction(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return false;
}

bool DataPilotSkills::isLearning(std::shared_ptr<GamePilot> owner)
{
	return false;
}

bool DataPilotSkills::isBulletSave(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return false;
}

bool DataPilotSkills::isEnergySave(std::shared_ptr<GamePilot> owner, bool isMain)
{
	return false;
}

DPilotSkillDummy::DPilotSkillDummy() : DataPilotSkills("Dummy", "ダミーの特殊スキル", std::vector<std::string>{"これはダミーです"},
		std::vector<int64_t>{1}, std::vector<int64_t>{1}, false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0.0)
{
}
