#pragma once

/* Includes */
//STL
#include <exception>  //Exception Handling
#include <stdexcept>  //Exception Class
#include <utility>    //
#include <ratio>
#include <functional>
#include <memory>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <random>
#include <numeric>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <format>
//NODEC
#include <nodec/unicode.hpp>
//DXLIB
#include <DxLib.h>
//JSON11
#include "json11.hpp"
//STRCONV2
#include "strconv2.h"

/* 前方宣言 */
/// <summary>
/// 地形適応(Key)
/// </summary>
enum class TerrainAdaptType;
/// <summary>
/// 地形適応(Value)
/// </summary>
enum class TerrainAdaptValue;
/// <summary>
/// 性別タイプ
/// </summary>
enum class DPilotGenderType;
/// <summary>
/// 性格タイプ
/// </summary>
enum class DPilotPersonalityType;
/// <summary>
/// パイロット成長タイプ
/// </summary>
enum class DPilotGrowthType;
/// <summary>
/// パイロットのステータス項目
/// </summary>
enum class DPilotStatusType;
/// <summary>
/// 気力+用コンディション
/// </summary>
enum class DIncrMoraleCond;
/// <summary>
/// パイロットプロフィール
/// </summary>
struct DPilotProfile;
/// <summary>
/// パイロット設定
/// </summary>
class DataPilot;
/// <summary>
/// パイロットの特殊スキル(抽象クラス)
/// </summary>
class DataPilotSkills;
class DataPSkillDummy;
/// <summary>
/// ユニットサイズ
/// </summary>
enum class DUnitSize;
/// <summary>
/// ユニットプロフィール
/// </summary>
struct DUnitProfile;
/// <summary>
/// ユニットステータス
/// </summary>
struct DUnitStatus;
/// <summary>
/// ユニット設定
/// </summary>
class DataUnit;
/// <summary>
/// ユニットの特殊能力
/// </summary>
class DataUnitSkills;
/// <summary>
/// 武装の属性のコンディション
/// </summary>
enum class DataUWAttributeCondition;
/// <summary>
/// 武装の属性
/// </summary>
class DataUWeaponAttributes;
/// <summary>
/// ユニットの武装
/// </summary>
class DataUnitWeapons;
/// <summary>
/// ゲーム上のパイロットデータ
/// </summary>
class GamePilot;
/// <summary>
/// ユニットの状態
/// </summary>
enum class UnitCondition;
/// <summary>
/// ユニットステータスのカテゴリ(改造・参照に使用)
/// </summary>
enum class InGUnitStatCategory;
/// <summary>
/// ゲーム内のユニットステータス
/// </summary>
struct InGameUnitStatus;
/// <summary>
/// ゲーム上のユニットデータ
/// </summary>
class GameUnit;
/// <summary>
/// 陣営
/// </summary>
enum class GameFaction;
/// <summary>
/// ゲーム上のツインユニットデータ
/// </summary>
class GameTroop;
/// <summary>
/// 読み込みパスの対象
/// </summary>
enum class LoaderHandlerType;
/// <summary>
/// ローダー
/// </summary>
class Loader;

extern std::map<DPilotGrowthType, std::map<DPilotStatusType, int64_t>> GrowthType;
extern std::map<DPilotStatusType, int64_t> GrowthBase;

class GamePilot
{
protected:
	int64_t level;
	int64_t experience;
	int64_t currentPP;
	int64_t currentSP;
	std::shared_ptr<DataPilot> refer_data;
	void edit_igStat(DPilotStatusType key, int64_t value);
	void levelUp_igStat(int64_t levelup_value);
public:
	std::map<DPilotStatusType, int64_t> inGameStat;
	int64_t getLevel() const;
	int64_t getExperience() const;
	int64_t getCurrentSP() const;
	int64_t getCurrentPP() const;
	void edit_level(int64_t value);
	void gain_experience(int64_t value);
	void setCurrentSP(int64_t value);
	void gainSP(int64_t value);
	void setPP(int64_t value);
	void gainPP(int64_t value);
	std::shared_ptr<DataPilot> getReferData();
	GamePilot(std::shared_ptr<DataPilot> pRef, int64_t pLevel);
};

