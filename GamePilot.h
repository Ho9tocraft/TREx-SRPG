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

class GamePilot
{
protected:
public:
};

