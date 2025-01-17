#include "All_Header_Wrapper.h"

float TerrainAdaptCompare::CalculateTerrainAdaptUnitAndPilot(TerrainAdaptValue adaptUnit, TerrainAdaptValue adaptPilot)
{
	/*
		E = 0 / D = 1 / C = 2 / B = 3 / A = 4 / S = 5
		計算式: (地形適応ランク指数)×0.25+追加補正
		Sのみ、追加補正あり(-0.05)
		よって、計算上の補正値は以下の通り
		E = 0.00 / D = 0.25 / C = 0.50 / B = 0.75 / A = 1.00 / S = 1.20
	*/
	float adaptValUnit = static_cast<float>(static_cast<int>(adaptUnit)) * 0.25f + (adaptUnit == TerrainAdaptValue::S ? -0.05f : 0);
	float adaptValPilot = static_cast<float>(static_cast<int>(adaptPilot)) * 0.25f + (adaptPilot == TerrainAdaptValue::S ? -0.05f : 0);
	/*
		それぞれの平均値を取る。
	*/
	return std::round((adaptValUnit + adaptValPilot) * 100.0f / 2.0f) / 100.0f;
}

TerrainAdaptValue TerrainAdaptCompare::GetTerrainAdaptAverage(TerrainAdaptValue adaptUnit, TerrainAdaptValue adaptPilot)
{
	float adaptValAverageFloat = TerrainAdaptCompare::CalculateTerrainAdaptUnitAndPilot(adaptUnit, adaptPilot);
	TerrainAdaptValue adaptValAverageResult = TerrainAdaptValue::E;
	if (adaptValAverageFloat > 0.125f) adaptValAverageResult = TerrainAdaptValue::D;
	if (adaptValAverageFloat > 0.375f) adaptValAverageResult = TerrainAdaptValue::C;
	if (adaptValAverageFloat > 0.625f) adaptValAverageResult = TerrainAdaptValue::B;
	if (adaptValAverageFloat > 0.875f) adaptValAverageResult = TerrainAdaptValue::A;
	if (adaptValAverageFloat > 1.0f) adaptValAverageResult = TerrainAdaptValue::S;
	return adaptValAverageResult;
}

void DataPilot::SetDataPilot(Json dataOrigin)
{
}

std::string DataPilot::GetPilotName(EntityNameStrCategory target) const
{
	return target == EntityNameStrCategory::FULL_NAME ? this->pilotFullname :
			target == EntityNameStrCategory::NICK_NAME ? this->pilotNickname :
			target == EntityNameStrCategory::READ_NAME ? this->pilotReadname :
			target == EntityNameStrCategory::CODE_NAME ? this->pilotCodename : "";
}

EnumPilotGender DataPilot::GetPilotGender() const
{
	return this->pilotGender;
}

std::string DataPilot::GetPilotGenderStr() const
{
	switch (this->pilotGender)
	{
	case EnumPilotGender::Undefined:
		return this->pilotGenderCustomDisplay.empty() ? "不明" : this->pilotGenderCustomDisplay;
	case EnumPilotGender::Male:
		return "男";
	case EnumPilotGender::Female:
		return "女";
	case EnumPilotGender::Machine:
		return "機械";
	default:
		return "不明";
	}
}

EnumPilotPersonality DataPilot::GetPilotPersonality() const
{
	return this->pilotPersonality;
}

std::string DataPilot::GetPilotPersonalityStr() const
{
	switch (this->pilotPersonality)
	{
	case EnumPilotPersonality::GENERALLY:
		return "普通";
	case EnumPilotPersonality::STUBBORN:
		return "強気";
	case EnumPilotPersonality::HIGH_STUBBORN:
		return "超強気";
	case EnumPilotPersonality::SERENITY:
		return "冷静";
	case EnumPilotPersonality::CAREFUL:
		return "慎重";
	case EnumPilotPersonality::EASY_GOING:
		return "楽天家";
	case EnumPilotPersonality::HARDWORKING:
		return "努力家";
	case EnumPilotPersonality::IMPATIENT:
		return "短気";
	case EnumPilotPersonality::BIGWIG:
		return "大物";
	case EnumPilotPersonality::VERY_BIGWIG:
		return "超大物";
	case EnumPilotPersonality::DEVIOUS:
		return "狡猾";
	case EnumPilotPersonality::BRUTALITY:
		return "残虐";
	case EnumPilotPersonality::REMNANT_SHADOW:
		return "残影";
	case EnumPilotPersonality::SACRED_FIRE:
		return "浄火";
	default:
		return "？？？";
	}
}

EnumPilotGrowthType DataPilot::GetPilotGrowthType() const
{
	return this->pilotGrowthType;
}

std::map<TerrainAdaptType, TerrainAdaptValue>& DataPilot::GetPilotTerrainAdapt()
{
	return this->pilotTerrainAdapt;
}

std::map<EnumPilotStatCategory, int64_t> ExpandEnumPilotGrowthType::GetPilotGrowthType(EnumPilotGrowthType pGrowthType) const
{
	return this->tablePilotGrowthCalc.at(pGrowthType);
}

void DataPilotSkill::setDefDisplayData(std::string pDefName, std::vector<std::string> pDefDesc)
{
	if (pDefName.empty() || pDefDesc.empty()) throw "Invalid Arg: DefName or DefDesc param value is blank or invalid";
	this->skillDefaultName = pDefName;
	this->skillDefaultDesc = std::vector<std::string>(pDefDesc);
}

void DataPilotSkill::setCusDisplayData(std::string pCusName, std::vector<std::string> pCusDesc)
{
	this->skillCustomName = pCusName;
	this->skillCustomDesc = std::vector<std::string>(pCusDesc);
}

std::string DataPilotSkill::GetSkillDefaultName() const
{
	return this->skillDefaultName;
}

std::string DataPilotSkill::GetSkillCustomName() const
{
	return this->skillCustomName;
}

std::vector<std::string> DataPilotSkill::GetSkillDefaultDesc() const
{
	return this->skillDefaultDesc;
}

std::vector<std::string> DataPilotSkill::GetSkillCustomDesc() const
{
	return this->skillCustomDesc;
}

DataPilotSkill::DataPilotSkill(std::string pDefName, std::vector<std::string> pDefDesc, std::string pCusName, std::vector<std::string> pCusDesc)
{
	this->setDefDisplayData(pDefName, pDefDesc);
	this->setCusDisplayData(pCusName, pCusDesc);
}

DataPilotSkill::DataPilotSkill(DataPilotSkill const& iRhs) : DataPilotSkill(iRhs.skillDefaultName, iRhs.skillDefaultDesc,
	iRhs.skillCustomName, iRhs.skillCustomDesc)
{
}

DataPilotSkill::DataPilotSkill(DataPilotSkill* iRhs) : DataPilotSkill(iRhs->skillDefaultName, iRhs->skillDefaultDesc,
	iRhs->skillCustomName, iRhs->skillCustomDesc)
{
}

DataPilotSKillDummy::DataPilotSKillDummy() : DataPilotSkill("ダミーの特殊スキル", { "ダミーの特殊スキル。", "効果はない。"}, "", {})
{
}

DataPilotSKillDummy::DataPilotSKillDummy(DataPilotSKillDummy const& iRhs) : DataPilotSkill(iRhs)
{
}

DataPilotSKillDummy::DataPilotSKillDummy(DataPilotSKillDummy* iRhs) : DataPilotSkill(iRhs)
{
}
