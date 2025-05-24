#pragma once

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

enum class UnitCondition
{
	/// <summary>
	/// 出撃可能
	/// </summary>
	AVAILABLE_SORTIES,
	/// <summary>
	/// 戦場にいる
	/// </summary>
	IN_THE_BATTLEFIELD,
	/// <summary>
	/// 母艦の中にいる
	/// </summary>
	IN_THE_MOTHERSHIP,
	/// <summary>
	/// 被撃破
	/// </summary>
	BEING_BEATEN_DOWN
};

enum class InGUnitStatCategory
{
	//HP
	HEALTH,
	//EN
	ENERGY,
	//装甲値
	ARMOR,
	//照準値
	SIGHT,
	//運動性
	EVADE
};

struct InGameUnitStatus
{
protected:
	int64_t def_health;      //初期HP
	int64_t def_energy;      //初期EN
	int64_t def_armor_value; //初期装甲値 (TAV)
	int64_t def_sight_value; //初期照準値 (SIG)
	int64_t def_evade_value; //初期運動性 (MOV)
	int64_t max_health;      //最大HP
	int64_t max_energy;      //最大EN
	int64_t current_hp;      //現在HP
	int64_t current_en;      //現在EN
	int64_t armor_value;     //装甲値 (TAV)
	int64_t sight_value;     //照準値 (SIG)
	int64_t evade_value;     //運動性 (MOV)
	int64_t config_hp;       //改造度: HP
	int64_t config_en;       //改造度: EN
	int64_t config_armor;    //改造度: 装甲値
	int64_t config_sight;    //改造度: 照準値
	int64_t config_evade;    //改造度: 運動性
public:
	int64_t getMaxHP() const;
	int64_t getMaxEN() const;
	int64_t getNowHP() const;
	int64_t getNowEN() const;
	int64_t getArmor() const;
	int64_t getSight() const;
	int64_t getEvade() const;
	int64_t getConfHP() const;
	int64_t getConfEN() const;
	int64_t getConfArmor() const;
	int64_t getConfSight() const;
	int64_t getConfEvade() const;
	void setNowHP(int64_t pVal);
	void setNowEN(int64_t pVal);
	void configureStatus(int64_t upwardRank, InGUnitStatCategory configureTarget);
	double calculateConfigureRank() const;
	InGameUnitStatus();
	InGameUnitStatus(DUnitStatus& pStat);
};

class GameUnit
{
protected:
	UnitCondition cond;
	std::shared_ptr<DataUnit> refer_data;
	std::shared_ptr<GamePilot> main_pilot;
	std::vector<std::shared_ptr<GamePilot>> sub_pilots;
	int64_t morale;
public:
	InGameUnitStatus status;
	std::shared_ptr<GamePilot> getMainPilot();
	std::vector<std::shared_ptr<GamePilot>> getSubPilots();
	std::shared_ptr<DataUnit> getRefer();
	UnitCondition getUnitCond() const;
	int64_t getUnitMaxHP() const;
	int64_t getUnitMaxEN() const;
	int64_t getUnitNowHP() const;
	int64_t getUnitNowEN() const;
	int64_t getUnitArmor() const;
	int64_t getUnitSight() const;
	int64_t getUnitEvade() const;
	int64_t getUnitConfHP() const;
	int64_t getUnitConfEN() const;
	int64_t getUnitConfArmor() const;
	int64_t getUnitConfSight() const;
	int64_t getUnitConfEvade() const;
	int64_t getUnitDistTravel() const;
	int64_t getMorale() const;
	double getRankPercent() const;
	void setCond(const UnitCondition pCond);
	void setMorale(const int64_t moraleValue);
	void increaseMorale(const int64_t moraleValue);
	void recoverSP(const int64_t recoverVal);
	void ridePilot(std::shared_ptr<GamePilot> pRef);
	void damageUnit(int64_t pDamage);
	void healUnit(int64_t pHeal);
	GameUnit(std::shared_ptr<DataUnit> pRef, const int64_t confHP, const int64_t confEN,
		const int64_t confArmor, const int64_t confSight, const int64_t confEvade);
	GameUnit(std::shared_ptr<DataUnit> pRef, const int64_t confAll);
};

enum class GameFaction
{
	/// <summary>
	/// 出撃前の未判定
	/// </summary>
	NOT_CREATED,
	/// <summary>
	/// プレイヤー陣営
	/// </summary>
	PLAYER,
	/// <summary>
	/// 敵陣営
	/// </summary>
	ENEMY_1,
	/// <summary>
	/// 中立・第三陣営
	/// </summary>
	ENEMY_2,
	/// <summary>
	/// NPC
	/// </summary>
	ALLY
};

class GameTroop
{
protected:
	int64_t posX;
	int64_t posY;
	bool isMoved;
	int64_t action_count;
	GameFaction faction;
	std::shared_ptr<GameUnit> main_unit;
	std::shared_ptr<GameUnit> sub_unit;
	std::vector<std::vector<int64_t>> movable_area;
	void cal_can_move_range(int64_t pPosY, int64_t pPosX, int64_t pMove);
	void reset_move_range();
public:
	std::string troop_name;
	int64_t getPosX() const;
	int64_t getPosY() const;
	int64_t gsActionCount(int64_t count = -1LL);
	GameFaction getFaction() const;
	int64_t calcTroopDistTravel();
	std::shared_ptr<GameUnit> getUnitMain();
	std::shared_ptr<GameUnit> getUnitSub();
	void swapMain();
	void onDestroy(bool isMain);
	void calcMoveArea();
	void launchUnit(int64_t pPosX, int64_t pPosY, GameFaction pFaction);
	void DrawUnitGraph(int drawX, int drawY);
	GameTroop(std::shared_ptr<GameUnit> pMain, std::shared_ptr<GameUnit> pSub = std::shared_ptr<GameUnit>());
};
