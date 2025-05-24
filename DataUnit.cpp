#include "stdafx.h"
#include "Main.h"
#include "DataPilot.h"
#include "DataPilotSkills.h"
#include "DataUnit.h"
#include "DataUnitSkills.h"
#include "GamePilot.h"
#include "GameUnit.h"

DUnitSize ConvertToUnitSize(int from)
{
	return static_cast<DUnitSize>(from);
}

DUnitSize ConvertToUnitSize(std::string from)
{
	using std::regex;
	using std::regex_match;
	using namespace std::regex_constants;
	regex SizeS(R"(^S(サイズ)?|小型)", ECMAScript, icase);
	regex SizeM(R"(^M(サイズ)?|中型)", ECMAScript, icase);
	regex SizeL(R"(^L(サイズ)?|大型)", ECMAScript, icase);
	regex Size2L(R"(^[2L]L(サイズ)?|大型)", ECMAScript, icase);
	regex Size3L(R"(^[3X]L(サイズ)?|超大型)", ECMAScript, icase);
	regex SizeInf(R"(^無限|∞)", ECMAScript, icase);
	int convert_index = regex_match(from, SizeS) ? -1 : regex_match(from, SizeM) ? 0 :
		regex_match(from, SizeL) ? 1 : regex_match(from, Size2L) ? 2 :
		regex_match(from, Size3L) ? 3 : regex_match(from, SizeInf) ? 4 : -2;
	return ConvertToUnitSize(convert_index);
}

DataUWAttributeCondition ConvertToUnitWeaponAttributeCondition(int from)
{
	return static_cast<DataUWAttributeCondition>(from);
}

DataUWAttributeCondition ConvertToUnitWeaponAttributeCondition(std::string from)
{
	using std::regex;
	using std::regex_match;
	using namespace std::regex_constants;
	regex rgxCalcMelee(R"(^Mele?|格闘?)", ECMAScript, icase);
	regex rgxCalcRange(R"(^Ra?nge?|射撃?)", ECMAScript, icase);
	regex rgxCalcMagic(R"(^Mag(ic|e)|魔法?)", ECMAScript, icase);
	regex rgxCalcMulti(R"(^Mu?lti?|複合?)", ECMAScript, icase);
	regex rgxCategNone(R"(^N(on)?Cat(egory)?|(特性|カテ(ゴリ)?)なし)", ECMAScript, icase);
	regex rgxCategMAPW(R"(^MAP(-W(eapon)?|兵器)?)", ECMAScript, icase);
	regex rgxCategUnis(R"(^Uni(son|te)?|合体(攻撃)?)", ECMAScript, icase);
	regex rgxCategSupW(R"(^Sup(port)?|支援武器|F)", ECMAScript, icase);
	regex rgxCategALLN(R"(^ALL|全体攻撃)", ECMAScript, icase);
	regex rgxCategALLW(R"(^ALL/?W)", ECMAScript, icase);
	regex rgxAttrPlace(R"(^P(武器)?|移動後(使用)?(可能)?)", ECMAScript, icase);
	regex rgxAttrIgSiz(R"(^Size|サイズ差(補正)?(無視)?)", ECMAScript, icase);
	regex rgxAttrIgBar(R"(^Barrier|バリア(貫通)?)", ECMAScript, icase);
	regex rgxAttrBeamW(R"(^BeamW(eapon)?|ビーム(兵器|武器)?|B)", ECMAScript, icase);
	regex rgxAttrEffec(R"(^Effect|特殊(効果)?|S(武器)?)", ECMAScript, icase);
	int convert_index = regex_match(from, rgxCalcMelee) ? 0 : regex_match(from, rgxCalcRange) ? 1 :
		regex_match(from, rgxCalcMagic) ?  2 : regex_match(from, rgxCalcMulti) ?  3 :
		regex_match(from, rgxCategNone) ?  4 : regex_match(from, rgxCategMAPW) ?  5 :
		regex_match(from, rgxCategUnis) ?  6 : regex_match(from, rgxCategSupW) ?  7 :
		regex_match(from, rgxCategALLN) ?  8 : regex_match(from, rgxCategALLW) ?  9 :
		regex_match(from, rgxAttrPlace) ? 11 : regex_match(from, rgxAttrIgSiz) ? 12 :
		regex_match(from, rgxAttrIgBar) ? 13 : regex_match(from, rgxAttrBeamW) ? 14 :
		regex_match(from, rgxAttrEffec) ? 15 : 10;
	return ConvertToUnitWeaponAttributeCondition(convert_index);
}

std::string DUnitProfile::getUFullname() const
{
	return this->full_name;
}

std::string DUnitProfile::getUNickname() const
{
	return this->nick_name;
}

std::string DUnitProfile::getUReadname() const
{
	return this->read_name;
}

DUnitSize DUnitProfile::getUnitSize() const
{
	return this->unit_size;
}

int64_t DUnitProfile::getRepairCost() const
{
	return this->repair_cost;
}

int64_t DUnitProfile::getUDropExp() const
{
	return this->drop_experience;
}

std::string DUnitProfile::getGraphPath() const
{
	return this->graph_path;
}

int64_t DUnitStatus::getMaxHealth() const
{
	return max_health;
}

int64_t DUnitStatus::getMaxEnergy() const
{
	return max_energy;
}

int64_t DUnitStatus::getArmorVal() const
{
	return armor_value;
}

int64_t DUnitStatus::getSightVal() const
{
	return sight_value;
}

int64_t DUnitStatus::getEvadeVal() const
{
	return evade_value;
}

int64_t DUnitStatus::getDistTravel() const
{
	return distTravel;
}

DUnitStatus::DUnitStatus(int64_t pHealth, int64_t pEnergy, int64_t pArmor, int64_t pSight, int64_t pEvade, int64_t pTravel,
	TerrainAdaptValue pAir, TerrainAdaptValue pGround, TerrainAdaptValue pOcean, TerrainAdaptValue pOuter)
{
	max_health = pHealth;
	max_energy = pEnergy;
	armor_value = pArmor;
	sight_value = pSight;
	evade_value = pEvade;
	distTravel = pTravel;
	unitTerrainAdapt.insert_or_assign(TerrainAdaptType::AIR, pAir);
	unitTerrainAdapt.insert_or_assign(TerrainAdaptType::GROUND, pGround);
	unitTerrainAdapt.insert_or_assign(TerrainAdaptType::OCEAN, pOcean);
	unitTerrainAdapt.insert_or_assign(TerrainAdaptType::OUTERLANDS, pOuter);
}

DUnitStatus::DUnitStatus(int64_t pHealth, int64_t pEnergy, int64_t pArmor, int64_t pSight, int64_t pEvade, int64_t pTravel,
	int pAir, int pGround, int pOcean, int pOuter) : DUnitStatus(pHealth, pEnergy, pArmor, pSight, pEvade, pTravel,
	ConvertToTAdaptValue(pAir), ConvertToTAdaptValue(pGround), ConvertToTAdaptValue(pOcean),
	ConvertToTAdaptValue(pOuter))
{
}

DUnitStatus::DUnitStatus(int64_t pHealth, int64_t pEnergy, int64_t pArmor, int64_t pSight, int64_t pEvade, int64_t pTravel,
	std::string pAir, std::string pGround, std::string pOcean, std::string pOuter) : DUnitStatus(pHealth, pEnergy, pArmor, pSight,
	pEvade, pTravel, ConvertToTAdaptValue(pAir), ConvertToTAdaptValue(pGround), ConvertToTAdaptValue(pOcean),
	ConvertToTAdaptValue(pOuter))
{
}

DUnitStatus::DUnitStatus(DUnitStatus& pRef) : DUnitStatus(pRef.max_health, pRef.max_energy, pRef.armor_value, pRef.sight_value, pRef.evade_value,
	pRef.distTravel, pRef.unitTerrainAdapt[TerrainAdaptType::AIR], pRef.unitTerrainAdapt[TerrainAdaptType::GROUND],
	pRef.unitTerrainAdapt[TerrainAdaptType::OCEAN], pRef.unitTerrainAdapt[TerrainAdaptType::OUTERLANDS])
{
}

DUnitStatus::DUnitStatus() : DUnitStatus(1000LL, 100LL, 1000LL, 100LL, 100LL, 6, 4, 4, 3, 4)
{
}

DUnitProfile::DUnitProfile(std::string pFull, std::string pNick, std::string pRead, DUnitSize pSize, int64_t pRepCost, int64_t pDrop, std::string pGrPath)
{
	full_name = pFull;
	nick_name = pNick;
	read_name = pRead;
	unit_size = pSize;
	repair_cost = pRepCost;
	drop_experience = pDrop;
	graph_path = pGrPath;
	GraphHandler = -1;
}

DUnitProfile::DUnitProfile(std::string pFull, std::string pNick, std::string pRead, int pSize, int64_t pRepCost, int64_t pDrop,
		std::string pGrPath) : DUnitProfile(pFull, pNick, pRead, ConvertToUnitSize(pSize), pRepCost, pDrop, pGrPath)
{
}

DUnitProfile::DUnitProfile(std::string pFull, std::string pNick, std::string pRead, std::string pSize, int64_t pRepCost, int64_t pDrop,
		std::string pGrPath) : DUnitProfile(pFull, pNick, pRead, ConvertToUnitSize(pSize), pRepCost, pDrop, pGrPath)
{
}

DUnitProfile::DUnitProfile(DUnitProfile& pRef) : DUnitProfile(pRef.full_name, pRef.nick_name, pRef.read_name, pRef.unit_size,
		pRef.repair_cost, pRef.drop_experience, pRef.graph_path)
{
	this->GraphHandler = pRef.GraphHandler;
}

DUnitProfile::DUnitProfile() : DUnitProfile("", "", "", DUnitSize::M, 0, 0, "")
{
}

DataUWAttributeCondition DataUWeaponAttributes::getCondition() const
{
	return this->condition;
}

bool DataUWeaponAttributes::isTypeAttribute() const
{
	return (this->condition == DataUWAttributeCondition::ON_CALC_DAMAGE_MELEE ||
		this->condition == DataUWAttributeCondition::ON_CALC_DAMAGE_RANGE ||
		this->condition == DataUWAttributeCondition::ON_CALC_DAMAGE_MAGIC ||
		this->condition == DataUWAttributeCondition::ON_CALC_DAMAGE_MULTI);
}

bool DataUWeaponAttributes::isCategoryAttribute() const
{
	return (this->condition == DataUWAttributeCondition::ON_ALL_ATTACK_FLAG_N ||
		this->condition == DataUWAttributeCondition::ON_ALL_ATTACK_FLAG_W ||
		this->condition == DataUWAttributeCondition::ON_MAP_ATTACK ||
		this->condition == DataUWAttributeCondition::ON_MAXIMUM_BREAK_WEAPON||
		this->condition == DataUWAttributeCondition::ON_UNISON_WEAPON);
}

bool DataUWeaponAttributes::isEffectAttribute() const
{
	return (this->condition == DataUWAttributeCondition::ON_MOVEMENT_ATTRIBUTE ||
		this->condition == DataUWAttributeCondition::ON_CALC_DAMAGE_SIZE_IGNORE ||
		this->condition == DataUWAttributeCondition::ON_CALC_DAMAGE_BARRIER_IGNORE ||
		this->condition == DataUWAttributeCondition::ON_CALC_EXTRA_EFFECT);
}

DataUWeaponAttributes::DataUWeaponAttributes(DataUWAttributeCondition cond_type)
{
	this->condition = cond_type;
}

DataUWeaponAttributes::DataUWeaponAttributes(int cond_type) :
	DataUWeaponAttributes(ConvertToUnitWeaponAttributeCondition(cond_type))
{
}

DataUWeaponAttributes::DataUWeaponAttributes(std::string cond_type) :
	DataUWeaponAttributes(ConvertToUnitWeaponAttributeCondition(cond_type))
{
}

DataUnitWeapons::DataUnitWeapons(json11::Json raw_data)
{
	this->W_name = raw_data["w_name"].string_value();
	this->W_attack = raw_data["w_atk"].int_value();
	this->W_min_range = raw_data["w_range"]["min"].int_value();
	this->W_max_range = raw_data["w_range"]["max"].int_value();
	{
		std::string keyReq = "require", keyCost = "cost";
		json11::Json consume_en = raw_data["w_cost"]["consume_en"];
		json11::Json consume_blt = raw_data["w_cost"]["consume_blt"];
		json11::Json require_morale = raw_data["w_cost"]["require_morale"];
		this->W_cost_en = std::pair<bool, int64_t>(consume_en[keyReq].bool_value(), consume_en[keyCost].int_value());
		this->W_cost_bullet = std::pair<bool, int64_t>(consume_blt[keyReq].bool_value(), consume_blt[keyCost].int_value());
		this->W_cost_morale = std::pair<bool, int64_t>(require_morale[keyReq].bool_value(), consume_blt[keyCost].int_value());
	}
	{
		json11::Json tempTerrain = raw_data["w_terrain"];
		TerrainAdaptValue tempAir = ConvertToTAdaptValue(tempTerrain["air"].int_value());
		TerrainAdaptValue tempGround = ConvertToTAdaptValue(tempTerrain["ground"].int_value());
		TerrainAdaptValue tempOcean = ConvertToTAdaptValue(tempTerrain["ocean"].int_value());
		TerrainAdaptValue tempOuter = ConvertToTAdaptValue(tempTerrain["outerlands"].int_value());
		this->W_terrain_adapt.insert_or_assign(TerrainAdaptType::AIR, tempAir);
		this->W_terrain_adapt.insert_or_assign(TerrainAdaptType::GROUND, tempGround);
		this->W_terrain_adapt.insert_or_assign(TerrainAdaptType::OCEAN, tempOcean);
		this->W_terrain_adapt.insert_or_assign(TerrainAdaptType::OUTERLANDS, tempOuter);
	}
	this->W_adjust_hit = raw_data["w_adjust"]["ACC"].int_value();
	this->W_adjust_crt = raw_data["w_adjust"]["CRT"].int_value();

	// 0～3: WType / 4～9: WCategory / 10～15: WAttribute
	this->W_att_cond.push_back(
		std::make_shared<DataUWeaponAttributes>(raw_data["w_type"].int_value()));         //0～3
	this->W_att_cond.push_back(
		std::make_shared<DataUWeaponAttributes>(raw_data["w_category"].int_value() + 4)); //4～9
	json11::Json::array arrAttribute = raw_data["w_attribute"].array_items();
	for (json11::Json tempAttribute : arrAttribute) {
		int tempAttributeType = tempAttribute.int_value() + 10;                        //10～15
		this->W_att_cond.push_back(std::make_shared<DataUWeaponAttributes>(tempAttributeType));
	}
	json11::Json::array arrEffects = raw_data["w_effects"].array_items();
}

std::string DataUnitWeapons::getWName() const
{
	return this->W_name;
}

int64_t DataUnitWeapons::getWATK() const
{
	return this->W_attack;
}

std::string DataUnitWeapons::getDispRange()
{
	return std::format("{0}～{1}", this->W_min_range, this->W_max_range);
}

int64_t DataUnitWeapons::getWMinRange() const
{
	return this->W_min_range;
}

int64_t DataUnitWeapons::getWMaxRange() const
{
	return this->W_max_range;
}

bool DataUnitWeapons::requireENFlag() const
{
	return this->W_cost_en.first;
}

int64_t DataUnitWeapons::requireENCost() const
{
	return this->W_cost_en.second;
}

bool DataUnitWeapons::requireBulletFlag() const
{
	return this->W_cost_bullet.first;
}

int64_t DataUnitWeapons::requireBulletCost() const
{
	return this->W_cost_bullet.second;
}

bool DataUnitWeapons::requireMoraleFlag() const
{
	return this->W_cost_morale.first;
}

int64_t DataUnitWeapons::requireMoraleMinimum() const
{
	return this->W_cost_morale.second;
}

DataUnit::DataUnit(json11::Json raw_data)
{
	json11::Json tProfile = raw_data["profile"];
	{
		std::string tFName = tProfile["full_name"].string_value();
		std::string tNName = tProfile["nick_name"].string_value();
		std::string tRName = tProfile["read_name"].string_value();
		int tRawSize = tProfile["unit_size"].int_value();
		int tRepairCost = tProfile["repair_cost"].int_value();
		int tDropExp = tProfile["drop_experience"].int_value();
		std::string tIcoGraphPath = tProfile["icon_graph"].string_value();
		this->profile = DUnitProfile(tFName, tNName, tRName, tRawSize, tRepairCost, tDropExp, tIcoGraphPath);
	}
	json11::Json::array tPassiveSkill = raw_data["specific_passive_abilities"].array_items();
	json11::Json tStatus = raw_data["status"];
	{
		int64_t tHP  = tStatus["HP"].int_value();
		int64_t tEN  = tStatus["EN"].int_value();
		int64_t tTAV = tStatus["TAV"].int_value();
		int64_t tSIG = tStatus["SIG"].int_value();
		int64_t tMOB = tStatus["MOB"].int_value();
		int64_t tTRV = tStatus["TRV"].int_value();
		int tTAdAir = tStatus["TAdapt"]["air"].int_value();
		int tTAdGro = tStatus["TAdapt"]["ground"].int_value();
		int tTAdOce = tStatus["TAdapt"]["ocean"].int_value();
		int tTAdOut = tStatus["TAdapt"]["outerlands"].int_value();
		this->status = DUnitStatus(tHP, tEN, tTAV, tSIG, tMOB, tTRV, tTAdAir, tTAdGro, tTAdOce, tTAdOut);
	}
	json11::Json::array tWeapons = raw_data["weapons"].array_items();
	for (json11::Json tWeapon : tWeapons) {
		this->weapons.push_back(std::make_shared<DataUnitWeapons>(tWeapon));
	}
}

DataUnit::DataUnit(DataUnit& pRef)
{
	this->profile = DUnitProfile(pRef.profile);
	this->specific_passives = std::vector<std::shared_ptr<DataUnitSkills>>(pRef.specific_passives);
	this->status = DUnitStatus(pRef.status);
	this->weapons = std::vector<std::shared_ptr<DataUnitWeapons>>(pRef.weapons);
}
