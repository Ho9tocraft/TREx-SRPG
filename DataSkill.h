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
#include "DataPilot.h"
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

class DataSkill {
protected:
	std::string unlocalized_skill_name_path;
	std::string unlocalized_skill_desc_path;
	std::map<std::string, std::vector<std::string>> localized_skill_name;
	std::map<std::string, std::vector<std::string>> localized_skill_desc;
public:
	void setSkillLocalize(std::map<std::string, json11::Json> jsonFiles);
	DataSkill(std::string unlcl_sname_path, std::string unlcl_sdesc_path, std::map<std::string, json11::Json> LangFiles);
	virtual ~DataSkill();
};

class DataSkillPilot : DataSkill {
protected:
public:
};

