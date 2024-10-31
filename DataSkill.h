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
#include "DataPilot.h"
#include "GamePilot.h"
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

class DataSkill {
protected:
	std::string unlocalized_skill_name_path;
	std::string unlocalized_skill_desc_path;
	std::map<std::string, std::string> localized_skill_name;
	std::map<std::string, std::vector<std::string>> localized_skill_desc;
public:
	void setSkillLocalize(std::map<std::string, json11::Json> jsonFiles);
	std::string getSkillName(std::string lang);
	std::vector<std::string> getSkillDesc(std::string lang);
	virtual bool skillCondition(GameUnit* unit) = 0;
	virtual void skillEffect(GameUnit*& unit) = 0;
	DataSkill(std::string unlcl_sname_path, std::string unlcl_sdesc_path, std::map<std::string, json11::Json> LangFiles);
	virtual ~DataSkill();
};

class DataSkillPilot : DataSkill {
protected:
public:
};

class DataSkillAttacker : DataSkillPilot {
protected:
public:
	bool skillCondition(GameUnit* unit) override;
	void skillEffect(GameUnit*& unit) override;
};
