﻿#pragma once
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

class ResourceLoader {
protected:
	std::map<std::string, std::string> pilotSkillKeybind;
	std::map<std::string, json11::Json> langFiles;
	std::map<std::string, DataSkillPilot*> pilotSkillDatabase;
public:
	json11::Json getLangFile(std::string langKey);
	DataSkillPilot* getPilotSkill(std::string skillKey);
	ResourceLoader();
};
