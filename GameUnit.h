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
#include "DataPilot.h"
#include "GamePilot.h"
#include "strconv2.h"

enum class DataType : uint64_t;
enum class GameState : uint64_t;
enum class GameUIState : uint64_t;
class ResourceLoader;
class Game_TheReminiscenceOfExellia;

enum class PilotStatsType : uint64_t;
enum class DataTerrainType : uint64_t;
enum class DataTerrainAdapt : uint64_t;
struct DataPilotStats;
enum class DataPilotGender : uint64_t;
enum class DataPilotPersonality : uint64_t;
class DataSkill;
class DataSkillPilot;
class DataSkillDummy;
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

enum class MoraleIncreaseSituation : uint64_t {
	/// <summary>
	/// 敵機被弾
	/// </summary>
	HIT_FROM_OWN,
	/// <summary>
	/// 敵機回避
	/// </summary>
	AVOID_FROM_OWN,
	/// <summary>
	/// 敵機撃墜(メイン)
	/// </summary>
	KILLING_ENEMY_MAIN,
	/// <summary>
	/// 敵機撃墜(サブ)
	/// </summary>
	KILLING_ENEMY_SUB,
	/// <summary>
	/// 自機被弾
	/// </summary>
	HIT_FROM_ENEMY,
	/// <summary>
	/// 自機回避
	/// </summary>
	AVOID_FROM_ENEMY,
	/// <summary>
	/// 味方撃墜
	/// </summary>
	KILLING_ALLY
};

enum class GameUnitFaction : uint64_t {
	PLAYER,
	ENEMY_1,
	ENEMY_2,
	NON_PLAYER
};

class GameUnit
{
protected:
	GamePilot* rided_pilot;
	int64_t Morale;
public:
	int64_t getMorale() const;
	void increaseMoraleEvent(const int64_t valMorale);
	void increaseMoraleCond(const MoraleIncreaseSituation situation);
};

