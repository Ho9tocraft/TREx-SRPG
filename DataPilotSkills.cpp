#include "stdafx.h"
#include "Main.h"
#include "DataPilot.h"
#include "DataPilotSkills.h"
#include "DataUnit.h"
#include "DataUnitSkills.h"
#include "GamePilot.h"
#include "GameUnit.h"

DataPilotSkills::DataPilotSkills(std::string pRegName, std::string pDispName, std::vector<std::string> pDesc, bool pUnique, double pAtkBuffPct, double pLuckPct, double pComHitPct, double pComEvdPct, double pOwnHitPct, double pOwnEvdPct, double pOwnCrtPct, int64_t pSPRegenVal, double pConsumeSPDecr)
{
	this->SS_registryName = pRegName;
	this->SS_displayName = pDispName;
	std::copy(pDesc.begin(), pDesc.end(), this->SS_description.begin());
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

double DataPilotSkills::calcAttackBuffPercent(std::weak_ptr<GameUnit> owner)
{
	return 0.0;
}

int64_t DataPilotSkills::calcAttackBuffConstant(std::weak_ptr<GameUnit> owner)
{
	return 0;
}

double DataPilotSkills::calcArmorBuffPercent(std::weak_ptr<GameUnit> owner)
{
	return 0.0;
}

double DataPilotSkills::calcDamageDecrPercent(std::weak_ptr<GameUnit> owner)
{
	return 0.0;
}

int64_t DataPilotSkills::calcMoveRangeIncrease(std::weak_ptr<GameUnit> owner)
{
	return 0;
}

int64_t DataPilotSkills::calcWeaponRangeIncrease(std::weak_ptr<GameUnit> owner)
{
	return 0;
}

double DataPilotSkills::calcHitCommanding(std::weak_ptr<GameUnit> owner)
{
	return 0.0;
}

double DataPilotSkills::calcEvadeCommanding(std::weak_ptr<GameUnit> owner)
{
	return 0.0;
}

double DataPilotSkills::calcHitOwner(std::weak_ptr<GameUnit> owner)
{
	return 0.0;
}

double DataPilotSkills::calcEvadeOwner(std::weak_ptr<GameUnit> owner)
{
	return 0.0;
}

double DataPilotSkills::calcCriticalOwner(std::weak_ptr<GameUnit> owner)
{
	return 0.0;
}

int64_t DataPilotSkills::calcSPRegenerate(std::weak_ptr<GameUnit> owner)
{
	return 0;
}

bool DataPilotSkills::canBeSupport(std::weak_ptr<GameUnit> owner)
{
	return false;
}

bool DataPilotSkills::canBeSAttack(std::weak_ptr<GameUnit> owner)
{
	return false;
}

bool DataPilotSkills::canBeSDefence(std::weak_ptr<GameUnit> owner)
{
	return false;
}

bool DataPilotSkills::canBeCounter(std::weak_ptr<GameUnit> owner)
{
	return false;
}

bool DataPilotSkills::isActiveReverseStrength(std::weak_ptr<GameUnit> owner)
{
	return false;
}

int64_t DataPilotSkills::calcSPUp(std::weak_ptr<GameUnit> owner)
{
	return 0;
}

int64_t DataPilotSkills::calcHitStat(std::weak_ptr<GameUnit> owner)
{
	return 0;
}

int64_t DataPilotSkills::calcEvadeStat(std::weak_ptr<GameUnit> owner)
{
	return 0;
}

int64_t DataPilotSkills::calcMoraleOverdrive(std::weak_ptr<GameUnit> owner)
{
	return 0;
}

bool DataPilotSkills::canREAttack(std::weak_ptr<GameUnit> owner)
{
	return false;
}

bool DataPilotSkills::isFocusAttackAvailable(std::weak_ptr<GameUnit> owner)
{
	return false;
}

bool DataPilotSkills::isHitAndAway(std::weak_ptr<GameUnit> owner)
{
	return false;
}

int64_t DataPilotSkills::calcIncrMoraleCond(std::weak_ptr<GameUnit> owner, DIncrMoraleCond pCond)
{
	return 0;
}

double DataPilotSkills::calcConsumeSPDecr(std::weak_ptr<GameUnit> owner)
{
	return 0.0;
}

bool DataPilotSkills::canRepSupExtraAction(std::weak_ptr<GameUnit> owner)
{
	return false;
}

bool DataPilotSkills::isLearning(std::weak_ptr<GameUnit> owner)
{
	return false;
}

bool DataPilotSkills::isBulletSave(std::weak_ptr<GameUnit> owner)
{
	return false;
}

bool DataPilotSkills::isEnergySave(std::weak_ptr<GameUnit> owner)
{
	return false;
}

DPilotSkillDummy::DPilotSkillDummy() : DataPilotSkills("Dummy", "ダミーの特殊スキル", std::vector<std::string>{"これはダミーです"},
		false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0.0)
{
}

std::shared_ptr<DataPilotSkills> DPilotSkillDummy::createInstance()
{
	return std::make_shared<DataPilotSkills>(DPilotSkillDummy());
}
