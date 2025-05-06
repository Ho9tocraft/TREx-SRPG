#include "stdafx.h"
#include "DataPilotSkills.h"

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

DataPilotSkills* DPilotSkillDummy::generateSkills()
{
	return new DPilotSkillDummy();
}
