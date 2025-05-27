#include "stdafx.h"
#include "Main.h"
#include "Loader.h"
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

void GameUnit::ridePilot(std::shared_ptr<GamePilot> pRef)
{
	if (!this->main_pilot) this->main_pilot = pRef;
	else {
		bool found = false;
		for (std::shared_ptr<GamePilot> tgt : this->sub_pilots) {
			if (pRef->getReferData()->profile.getFullname() == tgt->getReferData()->profile.getFullname()) {
				found = true;
				break;
			}
		}
		if (found) return;
		this->sub_pilots.push_back(pRef);
	}
}

void GameUnit::damageUnit(int64_t pDamage)
{
	this->healUnit(pDamage * -1LL);
}

void GameUnit::healUnit(int64_t pHeal)
{
	this->status.setNowHP(this->getUnitNowHP() + pHeal);
}

void GameUnit::setSavedFaction(GameFaction pSave)
{
	this->savedFaction = pSave;
}

std::shared_ptr<GamePilot> GameUnit::getMainPilot()
{
	return this->main_pilot;
}

std::vector<std::shared_ptr<GamePilot>> GameUnit::getSubPilots()
{
	return this->sub_pilots;
}

std::shared_ptr<DataUnit> GameUnit::getRefer()
{
	return this->refer_data;
}

UnitCondition GameUnit::getUnitCond() const
{
	return this->cond;
}

int64_t GameUnit::getUnitMaxHP() const
{
	return this->status.getMaxHP();
}

int64_t GameUnit::getUnitMaxEN() const
{
	return this->status.getMaxEN();
}

int64_t GameUnit::getUnitNowHP() const
{
	return this->status.getNowHP();
}

int64_t GameUnit::getUnitNowEN() const
{
	return this->status.getNowEN();
}

int64_t GameUnit::getUnitArmor() const
{
	return this->status.getArmor();
}

int64_t GameUnit::getUnitSight() const
{
	return this->status.getSight();
}

int64_t GameUnit::getUnitEvade() const
{
	return this->status.getEvade();
}

int64_t GameUnit::getUnitConfHP() const
{
	return this->status.getConfHP();
}

int64_t GameUnit::getUnitConfEN() const
{
	return this->status.getConfEN();
}

int64_t GameUnit::getUnitConfArmor() const
{
	return this->status.getConfArmor();
}

int64_t GameUnit::getUnitConfSight() const
{
	return this->status.getConfSight();
}

int64_t GameUnit::getUnitConfEvade() const
{
	return this->status.getConfEvade();
}

int64_t GameUnit::getUnitDistTravel() const
{
	return this->refer_data->status.getDistTravel();
}

int64_t GameUnit::getMorale() const
{
	return this->morale;
}

GameFaction GameUnit::getSavedFaction() const
{
	return this->savedFaction;
}

double GameUnit::getRankPercent() const
{
	return this->status.calculateConfigureRank();
}

void GameUnit::setCond(const UnitCondition pCond)
{
	this->cond = pCond;
}

GameUnit::GameUnit(std::shared_ptr<DataUnit> pRef, const int64_t confHP, const int64_t confEN, const int64_t confArmor, const int64_t confSight, const int64_t confEvade)
{
	this->savedFaction = GameFaction::NOT_CREATED;
	this->cond = UnitCondition::AVAILABLE_SORTIES;
	this->refer_data = std::make_shared<DataUnit>(*pRef.get());
	this->refer_data->profile.GraphHandler = LoadGraph(
		sjis_to_utf8("./Resources/images/unit/" + this->refer_data->profile.getGraphPath()).c_str());
	this->status = InGameUnitStatus(this->refer_data->status);
	this->morale = 100;
	this->status.configureStatus(confHP, InGUnitStatCategory::HEALTH);
	this->status.configureStatus(confEN, InGUnitStatCategory::ENERGY);
	this->status.configureStatus(confArmor, InGUnitStatCategory::ARMOR);
	this->status.configureStatus(confSight, InGUnitStatCategory::SIGHT);
	this->status.configureStatus(confEvade, InGUnitStatCategory::EVADE);
}

GameUnit::GameUnit(std::shared_ptr<DataUnit> pRef, const int64_t confAll) : GameUnit(pRef, confAll, confAll, confAll, confAll, confAll)
{
}

int64_t InGameUnitStatus::getMaxHP() const
{
	return this->max_health;
}

int64_t InGameUnitStatus::getMaxEN() const
{
	return this->max_energy;
}

int64_t InGameUnitStatus::getNowHP() const
{
	return this->current_hp;
}

int64_t InGameUnitStatus::getNowEN() const
{
	return this->current_en;
}

int64_t InGameUnitStatus::getArmor() const
{
	return this->armor_value;
}

int64_t InGameUnitStatus::getSight() const
{
	return this->sight_value;
}

int64_t InGameUnitStatus::getEvade() const
{
	return this->evade_value;
}

int64_t InGameUnitStatus::getConfHP() const
{
	return this->config_hp;
}

int64_t InGameUnitStatus::getConfEN() const
{
	return this->config_en;
}

int64_t InGameUnitStatus::getConfArmor() const
{
	return this->config_armor;
}

int64_t InGameUnitStatus::getConfSight() const
{
	return this->config_sight;
}

int64_t InGameUnitStatus::getConfEvade() const
{
	return this->config_evade;
}

void InGameUnitStatus::setNowHP(int64_t pVal)
{
	if (pVal < 0LL) pVal = 0LL;
	else if (pVal > this->max_health) pVal = this->max_health;
	this->current_hp = pVal;
}

void InGameUnitStatus::setNowEN(int64_t pVal)
{
	if (pVal < 0LL) pVal = 0LL;
	else if (pVal > this->max_energy) pVal = this->max_energy;
	this->current_en = pVal;
}

void InGameUnitStatus::configureStatus(int64_t upwardRank, InGUnitStatCategory configureTarget)
{
	/*
	* HP:   200/Rank
	* EN:    20/Rank
	* 装甲: 100/Rank
	* 照準:  10/Rank
	* 運動:   5/Rank
	*/
	switch (configureTarget)
	{
	case InGUnitStatCategory::HEALTH:
		this->config_hp += upwardRank;
		if (this->config_hp < 0) this->config_hp = 0;
		this->max_health = this->config_hp == 0 ? this->def_health : this->max_health + 200 * this->config_hp;
		break;
	case InGUnitStatCategory::ENERGY:
		this->config_en += upwardRank;
		if (this->config_en < 0) this->config_hp = 0;
		this->max_energy = this->config_en == 0 ? this->def_energy : this->max_energy + 20 * this->config_en;
		break;
	case InGUnitStatCategory::ARMOR:
		this->config_armor += upwardRank;
		if (this->config_armor < 0) this->config_armor = 0;
		this->armor_value = this->config_armor == 0 ? this->def_armor_value : this->armor_value + 100 * this->config_armor;
		break;
	case InGUnitStatCategory::SIGHT:
		this->config_sight += upwardRank;
		if (config_sight < 0) this->config_sight = 0;
		this->sight_value = this->config_sight == 0 ? this->def_sight_value : this->sight_value + 10 * this->config_sight;
		break;
	case InGUnitStatCategory::EVADE:
		this->config_evade += upwardRank;
		if (config_evade < 0) this->config_evade = 0;
		this->evade_value = this->config_evade == 0 ? this->def_evade_value : this->evade_value + 5 * this->config_evade;
		break;
	default:
		break;
	}
}

double InGameUnitStatus::calculateConfigureRank() const
{
	return std::round(
		static_cast<double>(this->config_hp + this->config_en + this->config_armor + this->config_sight + this->config_evade) / 5.0);
}

InGameUnitStatus::InGameUnitStatus()
{
	this->def_health = 1000LL;
	this->def_energy = 100LL;
	this->def_armor_value = 1000LL;
	this->def_sight_value = 150LL;
	this->def_evade_value = 100LL;
	this->max_health = this->def_health;
	this->max_energy = this->def_energy;
	this->armor_value = this->def_armor_value;
	this->sight_value = this->def_sight_value;
	this->evade_value = this->def_evade_value;
	this->current_hp = this->max_health;
	this->current_en = this->max_energy;
	this->config_hp = 0LL;
	this->config_en = 0LL;
	this->config_armor = 0LL;
	this->config_sight = 0LL;
	this->config_evade = 0LL;
}

InGameUnitStatus::InGameUnitStatus(DUnitStatus& pStat)
{
	this->def_health = pStat.getMaxHealth();
	this->def_energy = pStat.getMaxEnergy();
	this->def_armor_value = pStat.getArmorVal();
	this->def_sight_value = pStat.getSightVal();
	this->def_evade_value = pStat.getEvadeVal();
	this->max_health = this->def_health;
	this->max_energy = this->def_energy;
	this->armor_value = this->def_armor_value;
	this->sight_value = this->def_sight_value;
	this->evade_value = this->def_evade_value;
	this->current_hp = this->max_health;
	this->current_en = this->max_energy;
	this->config_hp = 0LL;
	this->config_en = 0LL;
	this->config_armor = 0LL;
	this->config_sight = 0LL;
	this->config_evade = 0LL;
}

void GameTroop::cal_can_move_range(int64_t pPosY, int64_t pPosX, int64_t pMove)
{
	this->movable_area[pPosY][pPosX] = pMove;
	if (this->movable_area[pPosY - 1][pPosX] < pMove) this->cal_can_move_range(pPosY - 1, pPosX, pMove - 1LL);
	if (this->movable_area[pPosY][pPosX + 1] < pMove) this->cal_can_move_range(pPosY, pPosX + 1, pMove - 1LL);
	if (this->movable_area[pPosY][pPosX - 1] < pMove) this->cal_can_move_range(pPosY, pPosX - 1, pMove - 1LL);
	if (this->movable_area[pPosY + 1][pPosX] < pMove) this->cal_can_move_range(pPosY + 1, pPosX, pMove - 1LL);
}

void GameTroop::reset_move_range()
{
	this->movable_area = std::vector<std::vector<int64_t>>(-1);
}

int64_t GameTroop::getPosX() const
{
	return this->posX;
}

int64_t GameTroop::getPosY() const
{
	return this->posY;
}

int64_t GameTroop::gsActionCount(int64_t count)
{
	if (count > -1LL) this->action_count = count;
	return this->action_count;
}

GameFaction GameTroop::getFaction() const
{
	return this->faction;
}

int64_t GameTroop::calcTroopDistTravel()
{
	if (this->main_unit) {
		if (this->sub_unit) return (this->main_unit->getUnitDistTravel() + this->sub_unit->getUnitDistTravel()) / 2LL;
		else return this->main_unit->getUnitDistTravel();
	}
	return 0;
}

std::shared_ptr<GameUnit> GameTroop::getUnitMain()
{
	return this->main_unit;
}

std::shared_ptr<GameUnit> GameTroop::getUnitSub()
{
	return this->sub_unit;
}

void GameTroop::swapMain()
{
	if (!this->sub_unit) return;
	this->main_unit.swap(sub_unit);
}

void GameTroop::onDestroy(bool isMain)
{
	if (isMain) {
		if (this->sub_unit && this->sub_unit->getUnitCond() != UnitCondition::BEING_BEATEN_DOWN) {
			this->swapMain();
			this->sub_unit->setCond(UnitCondition::BEING_BEATEN_DOWN);
		}
		else this->main_unit->setCond(UnitCondition::BEING_BEATEN_DOWN);
	}
	else this->sub_unit->setCond(UnitCondition::BEING_BEATEN_DOWN);
}

void GameTroop::calcMoveArea()
{
}

void GameTroop::launchUnit(int64_t pPosX, int64_t pPosY, GameFaction pFaction)
{
	this->posX = pPosX;
	this->posY = pPosY;
	this->faction = pFaction;
}

void GameTroop::DrawUnitGraph(int drawX, int drawY)
{
	const int& uGraphRes = game_loader->unitGraphResolution;
	DrawExtendGraph(drawX, drawY, drawX + uGraphRes, drawY + uGraphRes, 
		this->main_unit->getRefer()->profile.GraphHandler, TRUE);
}

GameTroop::GameTroop(std::shared_ptr<GameUnit> pMain, std::shared_ptr<GameUnit> pSub)
{
	this->isMoved = false;
	this->action_count = 1LL;
	this->faction = GameFaction::NOT_CREATED;
	this->main_unit = pMain;
	this->sub_unit = pSub;
	this->posX = LLONG_MIN;
	this->posY = LLONG_MIN;
}
