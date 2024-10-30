#pragma once
#include <exception>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <numeric>
#include <unordered_set>
#include <algorithm>
#include <tuple>
#include <ios>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <DxLib.h>

#include "trex_wrapper.h"
#include "Main.h"
#include "ResourceLoader.h"
#include "GameMain.h"
#include "json11.hpp"
#include "DataSkill.h"
#include "GamePilot.h"
#include "GameUnit.h"
#include "strconv2.h"

enum class DataType : uint64_t;
enum class GameState : uint64_t;
enum class GameUIState : uint64_t;
class Game_TheReminiscenceOfExellia;

enum class PilotStatsType : uint64_t;
enum class DataTerrainType : uint64_t;
enum class DataTerrainAdapt : uint64_t;
struct DataPilotStats;
enum class DataPilotGender : uint64_t;
enum class DataPilotPersonality : uint64_t;
class DataSkill;
class DataSkillPilot;
class DataSkillAttacker;

class DataPilot;

class GameSkill;
class GameSkillPilot;
enum class StatusUpgradeType : uint64_t;
class GamePilot;
enum class MoraleIncreaseSituation : uint64_t;
enum class GameUnitFaction : uint64_t;
class GameUnit;
class GameUnitTeam;

enum class PilotStatsType : uint64_t {
	/// <summary>
	/// 格闘
	/// </summary>
	MEL,
	/// <summary>
	/// 射撃
	/// </summary>
	RNG,
	/// <summary>
	/// 魔法
	/// </summary>
	MGC,
	/// <summary>
	/// 技量
	/// </summary>
	DEX,
	/// <summary>
	/// 防御
	/// </summary>
	DEF,
	/// <summary>
	/// 命中
	/// </summary>
	ACU,
	/// <summary>
	/// 回避(物理回避)
	/// </summary>
	AVD,
	/// <summary>
	/// 抵抗(魔法回避)
	/// </summary>
	RIT,
	/// <summary>
	/// 精神ポイント
	/// </summary>
	SPR
};

enum class DataTerrainType : uint64_t {
	/// <summary>
	/// 空中
	/// </summary>
	AIR,
	/// <summary>
	/// 地上
	/// </summary>
	GROUND,
	/// <summary>
	/// 水中
	/// </summary>
	UNDERWATER,
	/// <summary>
	/// 宇宙
	/// </summary>
	SEA_OF_THE_STARS
};

enum class DataTerrainAdapt : uint64_t {
	/// <summary>
	/// 補正値0.1倍
	/// </summary>
	E,
	/// <summary>
	/// 補正値0.25倍
	/// </summary>
	D,
	/// <summary>
	/// 補正値0.5倍
	/// </summary>
	C,
	/// <summary>
	/// 補正値0.75倍
	/// </summary>
	B,
	/// <summary>
	/// 補正値等倍
	/// </summary>
	A,
	/// <summary>
	/// 補正値1.2倍
	/// </summary>
	S
};

struct DataPilotStats {
protected:
	/// <summary>
	/// 格闘(近接火力)
	/// </summary>
	int MELEE;
	/// <summary>
	/// 射撃(遠隔物理火力)
	/// </summary>
	int RANGED;
	/// <summary>
	/// 魔力(遠隔魔法火力)
	/// </summary>
	int MAGIC;
	/// <summary>
	/// 技量
	/// </summary>
	int DEXTERITY;
	/// <summary>
	/// 防御
	/// </summary>
	int DEFENCE;
	/// <summary>
	/// 命中
	/// </summary>
	int ACCURACY;
	/// <summary>
	/// 回避(物理回避)
	/// </summary>
	int AVOIDANCE;
	/// <summary>
	/// 抵抗(魔法回避)
	/// </summary>
	int RESISTANCE;
	/// <summary>
	/// 精神ポイント
	/// </summary>
	int SPIRITUALS;
public:
	int getPilotStats(PilotStatsType statKey) const;
	DataPilotStats(int defined_melee, int defined_ranged, int defined_magic, int defined_dexterity, int defined_defence,
			int defined_accuracy, int defined_avoidance, int defined_resistance, int defined_spirituals);
	DataPilotStats();
	DataPilotStats(const DataPilotStats& rhs);
	DataPilotStats& operator=(const DataPilotStats& rhs);
};

enum class DataPilotGender : uint64_t {
	/// <summary>
	/// 男性
	/// </summary>
	MALE,
	/// <summary>
	/// 女性
	/// </summary>
	FEMALE,
	/// <summary>
	/// 無性または性別不詳
	/// </summary>
	NOMALE,
	/// <summary>
	/// 機械
	/// </summary>
	MACHINE
};

enum class DataPilotPersonality : uint64_t {
	/// <summary>
	/// 普通
	/// </summary>
	NORMAL,
	/// <summary>
	/// 強気
	/// </summary>
	STRONG_MIND,
	/// <summary>
	/// 超強気
	/// </summary>
	VERY_STRONG_MIND,
	/// <summary>
	/// 冷静
	/// </summary>
	SERENITY,
	/// <summary>
	/// 慎重
	/// </summary>
	CAREFUL,
	/// <summary>
	/// 楽天家
	/// </summary>
	OPTIMIST,
	/// <summary>
	/// 努力家
	/// </summary>
	HARDWORKING,
	/// <summary>
	/// 短気
	/// </summary>
	QUICK_TEMPER,
	/// <summary>
	/// 大物
	/// </summary>
	BIGWIG,
	/// <summary>
	/// 超大物
	/// </summary>
	VERY_BIGWIG,
	/// <summary>
	/// 狡猾
	/// </summary>
	SLY_CUNNING,
	/// <summary>
	/// 残虐
	/// </summary>
	BRUTALITY,
	/// <summary>
	/// 残影
	/// </summary>
	REMNANTS
};

class DataPilot
{
protected:
	int data_id;
	std::string unlocal_fullname_path;
	std::string unlocal_nickname_path;
	std::string unlocal_readname_path;
	std::string unlocal_codename_path;
	std::map<std::string, std::string> localized_fullname;
	std::map<std::string, std::string> localized_nickname;
	std::map<std::string, std::string> localized_readname;
	std::map<std::string, std::string> localized_codename;
	DataPilotGender pilotGender;
	DataPilotPersonality pilotPersonality;
	DataPilotStats pilotDefaultStats;
	std::map<DataTerrainType, DataTerrainAdapt> pilotTerrainAdapts;
	std::vector<DataSkillPilot*> pilotSkills;
public:
	int getPilotStats(PilotStatsType statKey);
	DataPilotGender getPilotGender() const;
	DataPilotPersonality getPilotPersonality() const;
	DataPilot(json11::Json pilotData);
};

