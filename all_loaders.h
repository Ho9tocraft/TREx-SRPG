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

#include <openssl/evp.h>
#include <openssl/aes.h>

#pragma warning(push)
#pragma warning(disable: 4251)
#pragma warning(disable: 4275)
#pragma warning(disable: 4996)
#include <yaml-cpp/yaml.h>
#pragma warning(pop)

#include <DxLib.h>

#include "strconv2.h"
#include "json11.hpp"
/* 独自ライブラリ */
#include "main.h"
#include "DataPilot.h"
#include "DataSpecificSkills.h"
#include "GamePilot.h"

using namespace std;
/* DROPBOX/JSON11 LIBRARIES */
using namespace json11;

enum class EnumPilotGender : uint64_t;
enum class EnumPilotPersonality : uint64_t;
enum class EnumPilotStatusCategory : uint64_t;
enum class EnumTerrainAdaption : uint64_t;
enum class EnumTerrainType : uint64_t;

class DataSpecificSkills;
class DataPilot;

class GamePilot;
