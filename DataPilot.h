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
#include "GameMain.h"
#include "json11.hpp"
#include "DataSkill.h"
#include "GameUnit.h"
#include "strconv2.h"

enum class GameState : uint64_t;
enum class GameUIState : uint64_t;
class Game_TheReminiscenceOfExellia;

struct DataPilotStats;
class DataSkill;
class DataSkillPilot;
class DataPilot;

class GameSkill;
class GamePilot;
class GameUnit;
class GameUnitTeam;

struct DataPilotStats {
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
};

class DataPilot
{
protected:
	int data_id;
	std::string unlocalized_fullname;
	std::string localized_fullname;
	std::string unlocalized_nickname;
	std::string localized_nickname;
	std::string unlocalized_readname;
	std::string localized_readname;
public:
};

