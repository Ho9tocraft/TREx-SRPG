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
#include "GameUnit.h"
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

enum class StatusUpgradeType : uint64_t {
	TRAINING,
	LEVEL_UP
};

class GamePilot
{
protected:
	/// <summary>
	/// レベル(最低1,最大100)
	/// </summary>
	int64_t level;
	/// <summary>
	/// 経験値(最低0,最大499(500到達でレベルアップ))
	/// </summary>
	int64_t experience;
	/// <summary>
	/// 次レベルまでの経験値(最低1,最大500)
	/// </summary>
	int64_t exp_for_levelup;
	/// <summary>
	/// 最大気力
	/// </summary>
	int64_t maxMorale;
	/// <summary>
	/// 最低気力(基本的に気力50)
	/// </summary>
	int64_t minMorale;
	/// <summary>
	/// 元データ
	/// </summary>
	DataPilot* data_pilot;
	std::map<StatusUpgradeType, std::map<PilotStatsType, int>> pilotStatRevisions;
public:
	DataPilot* getPilotData();
	int64_t getMinMorale() const;
	int64_t getMaxMorale() const;
	int getPilotStatus(const PilotStatsType statKey);
	std::map<PilotStatsType, int> getPilotStatus();
};

