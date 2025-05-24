#pragma once

/* Includes */
//STL
#include <exception>  //Exception Handling
#include <stdexcept>  //Exception Class
#include <utility>    //Utility Component
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
/// 読み込みパスの対象
/// </summary>
enum class LoaderHandlerType;
/// <summary>
/// ローダー
/// </summary>
class Loader;

/* 関数プロトタイプ宣言 */
DUnitSize ConvertToUnitSize(int from);
DUnitSize ConvertToUnitSize(std::string from);
DataUWAttributeCondition ConvertToUnitWeaponAttributeCondition(int from);
DataUWAttributeCondition ConvertToUnitWeaponAttributeCondition(std::string from);

enum class DUnitSize {
	/// <summary>
	/// SS (ロボ: 生身 / 生身: 極小サイズ)
	/// </summary>
	SS = -2,
	/// <summary>
	/// S  (ロボ: 小型 / 生身: 小中学生程度)
	/// </summary>
	S,
	/// <summary>
	/// M  (ロボ: MS等 / 生身: 高校生～大人程度)
	/// </summary>
	M,
	/// <summary>
	/// L  (ロボ: 大型 / 生身: 巨漢などなど)
	/// </summary>
	L,
	/// <summary>
	/// LL (ロボ: 超大型 / 生身: 小型ロボ)
	/// </summary>
	LL,
	/// <summary>
	/// 3L (ロボ: 数km単位 / 生身: MS等～数km単位)
	/// </summary>
	XL,
	/// <summary>
	/// 天元突破
	/// </summary>
	IL
};
struct DUnitProfile
{
protected:
	std::string full_name;
	std::string nick_name;
	std::string read_name;
	DUnitSize unit_size;
	int64_t repair_cost;
	int64_t drop_experience;
	std::string graph_path;
public:
	int GraphHandler;
	std::string getUFullname() const;
	std::string getUNickname() const;
	std::string getUReadname() const;
	DUnitSize getUnitSize() const;
	int64_t getRepairCost() const;
	int64_t getUDropExp() const;
	std::string getGraphPath() const;
	DUnitProfile(std::string pFull, std::string pNick, std::string pRead, DUnitSize pSize,
		int64_t pRepCost, int64_t pDrop, std::string pGrPath);
	DUnitProfile(std::string pFull, std::string pNick, std::string pRead, int pSize,
		int64_t pRepCost, int64_t pDrop, std::string pGrPath);
	DUnitProfile(std::string pFull, std::string pNick, std::string pRead, std::string pSize,
		int64_t pRepCost, int64_t pDrop, std::string pGrPath);
	DUnitProfile(DUnitProfile& pRef);
	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	DUnitProfile();
};

struct DUnitStatus
{
protected:
	int64_t max_health;  //HP
	int64_t max_energy;  //EN
	int64_t armor_value; //装甲値 (TAV)
	int64_t sight_value; //照準値 (SIG)
	int64_t evade_value; //運動性 (MOV)
	int64_t distTravel;  //移動距離
public:
	int64_t getMaxHealth() const;
	int64_t getMaxEnergy() const;
	int64_t getArmorVal() const;
	int64_t getSightVal() const;
	int64_t getEvadeVal() const;
	int64_t getDistTravel() const;
	std::map<TerrainAdaptType, TerrainAdaptValue> unitTerrainAdapt;
	DUnitStatus(int64_t pHealth, int64_t pEnergy, int64_t pArmor, int64_t pSight, int64_t pEvade, int64_t pTravel,
		TerrainAdaptValue pAir, TerrainAdaptValue pGround, TerrainAdaptValue pOcean, TerrainAdaptValue pOuter);
	DUnitStatus(int64_t pHealth, int64_t pEnergy, int64_t pArmor, int64_t pSight, int64_t pEvade, int64_t pTravel,
		int pAir, int pGround, int pOcean, int pOuter);
	DUnitStatus(int64_t pHealth, int64_t pEnergy, int64_t pArmor, int64_t pSight, int64_t pEvade, int64_t pTravel,
		std::string pAir, std::string pGround, std::string pOcean, std::string pOuter);
	DUnitStatus(DUnitStatus& pRef);
	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	DUnitStatus();
};

class DataUnit
{
protected:
public:
	DUnitProfile profile;
	std::vector<std::shared_ptr<DataUnitSkills>> specific_passives;
	DUnitStatus status;
	std::vector<std::shared_ptr<DataUnitWeapons>> weapons;
	DataUnit(json11::Json raw_data);
	DataUnit(DataUnit& ref);
};

enum class DataUWAttributeCondition {
	/// <summary>
	/// 格闘
	/// </summary>
	ON_CALC_DAMAGE_MELEE,
	/// <summary>
	/// 射撃
	/// </summary>
	ON_CALC_DAMAGE_RANGE,
	/// <summary>
	/// 魔法
	/// </summary>
	ON_CALC_DAMAGE_MAGIC,
	/// <summary>
	/// 複合
	/// </summary>
	ON_CALC_DAMAGE_MULTI,
	/// <summary>
	/// カテゴリなし(通常武器)
	/// </summary>
	ON_CATEGORY_NONE,
	/// <summary>
	/// MAP兵器
	/// </summary>
	ON_MAP_ATTACK,
	/// <summary>
	/// 合体攻撃(合)
	/// </summary>
	ON_UNISON_WEAPON,
	/// <summary>
	/// 支援武器(F)
	/// </summary>
	ON_MAXIMUM_BREAK_WEAPON,
	/// <summary>
	/// 全体攻撃(ALL)
	/// </summary>
	ON_ALL_ATTACK_FLAG_N,
	/// <summary>
	/// 全体攻撃(ダブルアタック)
	/// </summary>
	ON_ALL_ATTACK_FLAG_W,
	/// <summary>
	/// 特殊効果属性なし
	/// </summary>
	ON_EXTRA_EFFECT_NONE,
	/// <summary>
	/// 移動後使用可能(P)
	/// </summary>
	ON_MOVEMENT_ATTRIBUTE,
	/// <summary>
	/// サイズ差補正無視
	/// </summary>
	ON_CALC_DAMAGE_SIZE_IGNORE,
	/// <summary>
	/// バリア貫通
	/// </summary>
	ON_CALC_DAMAGE_BARRIER_IGNORE,
	/// <summary>
	/// ビーム属性
	/// </summary>
	ON_CALC_DAMAGE_BEAM,
	/// <summary>
	/// その他特殊効果
	/// </summary>
	ON_CALC_EXTRA_EFFECT
};

class DataUWeaponAttributes {
protected:
	DataUWAttributeCondition condition;
public:
	DataUWAttributeCondition getCondition() const;
	bool isTypeAttribute() const;
	bool isCategoryAttribute() const;
	bool isEffectAttribute() const;
	DataUWeaponAttributes(DataUWAttributeCondition cond_type);
	DataUWeaponAttributes(int cond_type);
	DataUWeaponAttributes(std::string cond_type);
};

class DataUnitWeapons {
protected:
	std::string W_name;
	int64_t W_attack;
	int64_t W_min_range;
	int64_t W_max_range;
	std::pair<bool, int64_t> W_cost_en;
	std::pair<bool, int64_t> W_cost_bullet;
	std::pair<bool, int64_t> W_cost_morale;
	int64_t W_adjust_hit;
	int64_t W_adjust_crt;
public:
	std::map<TerrainAdaptType, TerrainAdaptValue> W_terrain_adapt;
	std::vector<std::shared_ptr<DataUWeaponAttributes>> W_att_cond;
	std::string getWName() const;
	int64_t getWATK() const;
	std::string getDispRange();
	int64_t getWMinRange() const;
	int64_t getWMaxRange() const;
	bool requireENFlag() const;
	int64_t requireENCost() const;
	bool requireBulletFlag() const;
	int64_t requireBulletCost() const;
	bool requireMoraleFlag() const;
	int64_t requireMoraleMinimum() const;
	DataUnitWeapons(json11::Json raw_data);
};
