#include "stdafx.h"
#include "Main.h"
#include "DataPilot.h"
#include "DataPilotSkills.h"
#include "DataUnit.h"
#include "DataUnitSkills.h"
#include "GamePilot.h"
#include "GameUnit.h"

std::map<DPilotGrowthType, std::map<DPilotStatusType, int64_t>> GrowthType = {
    {DPilotGrowthType::NORMAL, {
        {DPilotStatusType::MEL, 0LL},{DPilotStatusType::RNG, 0LL},{DPilotStatusType::MAT, 0LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, 0LL},{DPilotStatusType::MDF, 0LL},{DPilotStatusType::AVD, 0LL},{DPilotStatusType::ACC, 0LL},
        {DPilotStatusType::RST, 0LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::MELEE_NORMAL, {
        {DPilotStatusType::MEL, 4LL},{DPilotStatusType::RNG, -2LL},{DPilotStatusType::MAT, -2LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, 3LL},{DPilotStatusType::MDF, 3LL},{DPilotStatusType::AVD, -3LL},{DPilotStatusType::ACC, 0LL},
        {DPilotStatusType::RST, -3LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::MELEE_ALMIGHTY, {
        {DPilotStatusType::MEL, 6LL},{DPilotStatusType::RNG, -1LL},{DPilotStatusType::MAT, -1LL},{DPilotStatusType::DEX, 1LL},
        {DPilotStatusType::DEF, 4LL},{DPilotStatusType::MDF, 4LL},{DPilotStatusType::AVD, -7LL},{DPilotStatusType::ACC, 1LL},
        {DPilotStatusType::RST, -7LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::MELEE_FOC_RANGED, {
        {DPilotStatusType::MEL, 4LL},{DPilotStatusType::RNG, -1LL},{DPilotStatusType::MAT, -3LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, 3LL},{DPilotStatusType::MDF, 3LL},{DPilotStatusType::AVD, -3LL},{DPilotStatusType::ACC, 0LL},
        {DPilotStatusType::RST, -3LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::MELEE_FOC_MAGIC, {
        {DPilotStatusType::MEL, 4LL},{DPilotStatusType::RNG, -3LL},{DPilotStatusType::MAT, -1LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, 3LL},{DPilotStatusType::MDF, 3LL},{DPilotStatusType::AVD, -3LL},{DPilotStatusType::ACC, 0LL},
        {DPilotStatusType::RST, -3LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::MELEE_DEFENSIVE, {
        {DPilotStatusType::MEL, 3LL},{DPilotStatusType::RNG, -4LL},{DPilotStatusType::MAT, -2LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, 6LL},{DPilotStatusType::MDF, 6LL},{DPilotStatusType::AVD, -5LL},{DPilotStatusType::ACC, 0LL},
        {DPilotStatusType::RST, -4LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::MELEE_LATE_BLOOM, {
        {DPilotStatusType::MEL, 4LL},{DPilotStatusType::RNG, -3LL},{DPilotStatusType::MAT, -3LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, 5LL},{DPilotStatusType::MDF, 5LL},{DPilotStatusType::AVD, -3LL},{DPilotStatusType::ACC, 1LL},
        {DPilotStatusType::RST, -3LL},{DPilotStatusType::SPR, 2LL}
    }},
    {DPilotGrowthType::RANGED_NORMAL, {
        {DPilotStatusType::MEL, -2LL},{DPilotStatusType::RNG, 4LL},{DPilotStatusType::MAT, -2LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, -3LL},{DPilotStatusType::MDF, -3LL},{DPilotStatusType::AVD, 3LL},{DPilotStatusType::ACC, 0LL},
        {DPilotStatusType::RST, 3LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::RANGED_ALMIGHTY, {
        {DPilotStatusType::MEL, -1LL},{DPilotStatusType::RNG, 6LL},{DPilotStatusType::MAT, -1LL},{DPilotStatusType::DEX, 1LL},
        {DPilotStatusType::DEF, -7LL},{DPilotStatusType::MDF, -7LL},{DPilotStatusType::AVD, 4LL},{DPilotStatusType::ACC, 1LL},
        {DPilotStatusType::RST, 4LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::RANGED_FOC_MELEE, {
        {DPilotStatusType::MEL, -1LL},{DPilotStatusType::RNG, 4LL},{DPilotStatusType::MAT, -3LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, -3LL},{DPilotStatusType::MDF, -3LL},{DPilotStatusType::AVD, 3LL},{DPilotStatusType::ACC, 0LL},
        {DPilotStatusType::RST, 3LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::RANGED_FOC_MAGIC, {
        {DPilotStatusType::MEL, -3LL},{DPilotStatusType::RNG, 4LL},{DPilotStatusType::MAT, -1LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, -3LL},{DPilotStatusType::MDF, -3LL},{DPilotStatusType::AVD, 3LL},{DPilotStatusType::ACC, 0LL},
        {DPilotStatusType::RST, 3LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::RANGED_DEFENSIVE, {
        {DPilotStatusType::MEL, -3LL},{DPilotStatusType::RNG, 3LL},{DPilotStatusType::MAT, -3LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, 0LL},{DPilotStatusType::MDF, 1LL},{DPilotStatusType::AVD, 1LL},{DPilotStatusType::ACC, 0LL},
        {DPilotStatusType::RST, 1LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::RANGED_LATE_BLOOM, {
        {DPilotStatusType::MEL, -4LL},{DPilotStatusType::RNG, 4LL},{DPilotStatusType::MAT, -2LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, -3LL},{DPilotStatusType::MDF, -3LL},{DPilotStatusType::AVD, 5LL},{DPilotStatusType::ACC, 1LL},
        {DPilotStatusType::RST, 3LL},{DPilotStatusType::SPR, 2LL}
    }},
    {DPilotGrowthType::MAGIC_NORMAL, {
        {DPilotStatusType::MEL, -3LL},{DPilotStatusType::RNG, -3LL},{DPilotStatusType::MAT, 3LL},{DPilotStatusType::DEX, 3LL},
        {DPilotStatusType::DEF, -6LL},{DPilotStatusType::MDF, 0LL},{DPilotStatusType::AVD, 0LL},{DPilotStatusType::ACC, 3LL},
        {DPilotStatusType::RST, 3LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::MAGIC_ALMIGHTY, {
        {DPilotStatusType::MEL, -2LL},{DPilotStatusType::RNG, -2LL},{DPilotStatusType::MAT, 6LL},{DPilotStatusType::DEX, 4LL},
        {DPilotStatusType::DEF, -5LL},{DPilotStatusType::MDF, -4LL},{DPilotStatusType::AVD, 1LL},{DPilotStatusType::ACC, 1LL},
        {DPilotStatusType::RST, 1LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::MAGIC_FOC_MELEE, {
        {DPilotStatusType::MEL, -1LL},{DPilotStatusType::RNG, -3LL},{DPilotStatusType::MAT, 4LL},{DPilotStatusType::DEX, 3LL},
        {DPilotStatusType::DEF, -6LL},{DPilotStatusType::MDF, -3LL},{DPilotStatusType::AVD, 0LL},{DPilotStatusType::ACC, 3LL},
        {DPilotStatusType::RST, 3LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::MAGIC_FOC_RANGED, {
        {DPilotStatusType::MEL, -3LL},{DPilotStatusType::RNG, -1LL},{DPilotStatusType::MAT, 4LL},{DPilotStatusType::DEX, 3LL},
        {DPilotStatusType::DEF, -6LL},{DPilotStatusType::MDF, -3LL},{DPilotStatusType::AVD, 0LL},{DPilotStatusType::ACC, 3LL},
        {DPilotStatusType::RST, 3LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::MAGIC_DEFENSIVE, {
        {DPilotStatusType::MEL, -5LL},{DPilotStatusType::RNG, -5LL},{DPilotStatusType::MAT, 3LL},{DPilotStatusType::DEX, 0LL},
        {DPilotStatusType::DEF, -1LL},{DPilotStatusType::MDF, 2LL},{DPilotStatusType::AVD, 0LL},{DPilotStatusType::ACC, 3LL},
        {DPilotStatusType::RST, 3LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::MAGIC_LATE_BLOOM, {
        {DPilotStatusType::MEL, -2LL},{DPilotStatusType::RNG, -2LL},{DPilotStatusType::MAT, 5LL},{DPilotStatusType::DEX, 3LL},
        {DPilotStatusType::DEF, -6LL},{DPilotStatusType::MDF, 5LL},{DPilotStatusType::AVD, 0LL},{DPilotStatusType::ACC, 4LL},
        {DPilotStatusType::RST, 3LL},{DPilotStatusType::SPR, 2LL}
    }},
    {DPilotGrowthType::ALMIGHTY_NORMAL, {
        {DPilotStatusType::MEL, 3LL},{DPilotStatusType::RNG, 3LL},{DPilotStatusType::MAT, 3LL},{DPilotStatusType::DEX, 1LL},
        {DPilotStatusType::DEF, -4LL},{DPilotStatusType::MDF, -4LL},{DPilotStatusType::AVD, 2LL},{DPilotStatusType::ACC, 1LL},
        {DPilotStatusType::RST, 0LL},{DPilotStatusType::SPR, 0LL}
    }},
    {DPilotGrowthType::ALMIGHTY_LATE_BLOOM, {
        {DPilotStatusType::MEL, 3LL},{DPilotStatusType::RNG, 3LL},{DPilotStatusType::MAT, 3LL},{DPilotStatusType::DEX, 3LL},
        {DPilotStatusType::DEF, -2LL},{DPilotStatusType::MDF, -2LL},{DPilotStatusType::AVD, 4LL},{DPilotStatusType::ACC, 1LL},
        {DPilotStatusType::RST, 4LL},{DPilotStatusType::SPR, 2LL}
    }},
    {DPilotGrowthType::SP_FOCUS, {
        {DPilotStatusType::MEL, -2LL},{DPilotStatusType::RNG, -2LL},{DPilotStatusType::MAT, -2LL},{DPilotStatusType::DEX, -2LL},
        {DPilotStatusType::DEF, 0LL},{DPilotStatusType::MDF, 0LL},{DPilotStatusType::AVD, 0LL},{DPilotStatusType::ACC, -1LL},
        {DPilotStatusType::RST, 0LL},{DPilotStatusType::SPR, 9LL}
    }},
    {DPilotGrowthType::SUB_PILOTS, {
        {DPilotStatusType::MEL, 0LL},{DPilotStatusType::RNG, 0LL},{DPilotStatusType::MAT, 0LL},{DPilotStatusType::DEX, -2LL},
        {DPilotStatusType::DEF, 0LL},{DPilotStatusType::MDF, 0LL},{DPilotStatusType::AVD, 0LL},{DPilotStatusType::ACC, -1LL},
        {DPilotStatusType::RST, 0LL},{DPilotStatusType::SPR, 9LL}
    }},
};

std::map<DPilotStatusType, int64_t> GrowthBase = {
    {DPilotStatusType::MEL, 4LL},{DPilotStatusType::RNG, 4LL},{DPilotStatusType::MAT, 4LL},{DPilotStatusType::DEX, 4LL},
    {DPilotStatusType::DEF, 8LL},{DPilotStatusType::MDF, 8LL},{DPilotStatusType::AVD, 12LL},{DPilotStatusType::ACC, 12LL},
    {DPilotStatusType::RST, 12LL},{DPilotStatusType::SPR, 8LL}
};

void GamePilot::edit_igStat(DPilotStatusType key, int64_t value)
{
    int64_t minStat = this->refer_data->status[key];
    if (value < minStat) this->inGameStat[key] = minStat;
    else this->inGameStat[key] = value;
}

void GamePilot::levelUp_igStat(int64_t levelup_value)
{
    /*
    * 固定上昇(基準値)
    * 攻撃・防御系+4、命・回・抵+12、防・SP+8
    * 成長率による上昇(補正値)
    */
    //データ元の成長率
    DPilotGrowthType tmpGrowth = this->refer_data->growth_type;
    for (const std::pair<DPilotStatusType, int64_t>& stat : this->inGameStat) {
        DPilotStatusType key = stat.first;
        int64_t statUpPerLevelUp = GrowthBase[key] + GrowthType[tmpGrowth][key];
        int64_t tmpStat = stat.second + levelup_value * statUpPerLevelUp;
        this->edit_igStat(key, tmpStat);
    }
}

int64_t GamePilot::getLevel() const
{
    return this->level;
}

int64_t GamePilot::getExperience() const
{
    return this->experience;
}

int64_t GamePilot::getCurrentSP() const
{
    return this->currentSP;
}

int64_t GamePilot::getCurrentPP() const
{
    return this->currentPP;
}

void GamePilot::edit_level(int64_t value)
{
    int64_t changed_level = this->level + value;
    if (changed_level < 1LL) changed_level = 1LL;
    this->level = changed_level;
}

void GamePilot::gain_experience(int64_t value)
{
    int64_t gain = value;
    if (this->refer_data->isGrowthLate()) {
        //晩成フラグ(Lv40以下の場合は経験値獲得量半減、Lv60以上の場合は獲得量+50)
        if (this->level < 40 && gain > 0) gain /= 2;
        else if (this->level > 60 && gain > 0) gain += 50;
    }
    if (gain <= 0LL) gain = 0LL;
    int64_t pend_result = this->experience + gain;
    if (pend_result >= 500LL) {
        int64_t level_up = pend_result / 500LL;
        this->edit_level(level_up);
        pend_result %= 500LL;
    }
    this->experience = pend_result;
}

void GamePilot::setCurrentSP(int64_t value)
{
    const int64_t max_sp = this->inGameStat[DPilotStatusType::SPR];
    int64_t calc_sp = this->currentSP + value;
    if (calc_sp > max_sp) calc_sp = max_sp;
    else if (calc_sp < 0LL) calc_sp = 0LL;
    this->currentSP = calc_sp;
}

void GamePilot::gainSP(int64_t value)
{
    this->setCurrentSP(this->currentSP + value);
}

void GamePilot::setPP(int64_t value)
{
    if (value <= 0) this->currentPP = 0LL;
    else this->currentPP = value;
}

void GamePilot::gainPP(int64_t value)
{
    this->setPP(this->currentPP + value);
}

std::weak_ptr<DataPilot> GamePilot::getReferData()
{
    return this->refer_data;
}

GamePilot::GamePilot(std::shared_ptr<DataPilot> pRef, int64_t pLevel)
{
    this->refer_data = std::make_shared<DataPilot>(*pRef.get());
    this->level = pLevel;
    this->experience = 0LL;
    this->inGameStat = std::map<DPilotStatusType, int64_t>(this->refer_data->status);
    this->currentSP = this->inGameStat[DPilotStatusType::SPR];
    this->currentPP = 0LL;
}
