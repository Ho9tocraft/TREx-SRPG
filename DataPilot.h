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
#include "all_loaders.h"
#include "main.h"
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

/// <summary>
/// キャラクターの性別
/// </summary>
enum class EnumPilotGender : uint64_t
{
	/// <summary>
	/// 男性
	/// </summary>
	Male,
	/// <summary>
	/// 女性
	/// </summary>
	Female,
	/// <summary>
	/// 無性・中性など
	/// </summary>
	Nomale,
	/// <summary>
	/// 機械
	/// </summary>
	Machine
};

/// <summary>
/// キャラクターの性格
/// </summary>
enum class EnumPilotPersonality : uint64_t
{
	/// <summary>
	/// 弱気
	/// </summary>
	Weak,
	/// <summary>
	/// 普通
	/// </summary>
	Normal,
	/// <summary>
	/// 強気
	/// </summary>
	Strong,
	/// <summary>
	/// 超強気
	/// </summary>
	VeryStrong,
	/// <summary>
	/// 慎重
	/// </summary>
	Careful,
	/// <summary>
	/// 冷静
	/// </summary>
	Selenity,
	/// <summary>
	/// 楽天家
	/// </summary>
	Optimist,
	/// <summary>
	/// 努力家
	/// </summary>
	HardWorker,
	/// <summary>
	/// 短気
	/// </summary>
	QuickTemper,
	/// <summary>
	/// 大物
	/// </summary>
	Bigwig,
	/// <summary>
	/// 超大物
	/// </summary>
	SuperBigwig,
	/// <summary>
	/// 狡猾
	/// </summary>
	Cunning,
	/// <summary>
	/// 残虐
	/// </summary>
	Cruelty,
	/// <summary>
	/// 機械
	/// </summary>
	Machine
};

/// <summary>
/// パイロットのステータスカテゴリ
/// </summary>
enum class EnumPilotStatusCategory : uint64_t
{
	/// <summary>
	/// 格闘値
	/// </summary>
	MEL,
	/// <summary>
	/// 射撃値
	/// </summary>
	RNG,
	/// <summary>
	/// 魔力値
	/// </summary>
	MGC,
	/// <summary>
	/// 技量値
	/// </summary>
	DEX,
	/// <summary>
	/// 防御値
	/// </summary>
	DEF,
	/// <summary>
	/// 命中値
	/// </summary>
	ACU,
	/// <summary>
	/// 回避値
	/// </summary>
	AVD,
	/// <summary>
	/// 抵抗値
	/// </summary>
	RIT,
	/// <summary>
	/// 精神ポイント
	/// </summary>
	SPR
};

enum class EnumTerrainAdaption : uint64_t
{
	/// <summary>
	/// 適正なし、与ダメージ0.1倍
	/// </summary>
	E,
	/// <summary>
	/// Dランク、与ダメージ0.4倍
	/// </summary>
	D,
	/// <summary>
	/// Cランク、与ダメージ0.6倍
	/// </summary>
	C,
	/// <summary>
	/// Bランク、与ダメージ0.8倍
	/// </summary>
	B,
	/// <summary>
	/// Aランク、与ダメージ等倍
	/// </summary>
	A,
	/// <summary>
	/// Sランク、与ダメージ1.2倍
	/// </summary>
	S
};

enum class EnumTerrainType : uint64_t
{
	Air,
	Ground,
	Underwater,
	Outerworld
};

class DataPilot
{
protected:
	string pilotUnlocalizedFullname;
	string pilotUnlocalizedNickname;
	string pilotUnlocalizedReadname;
	string pilotUnlocalizedCodename;
	EnumPilotGender pilotGender;
	EnumPilotPersonality pilotPersonality;
	map<EnumPilotStatusCategory, int64_t> pilotStatus;
	map<EnumTerrainType, EnumTerrainAdaption> pilotTerrainAdaption;
	vector<DataSpecificSkills*> pilotSpecificSkills;
public:
	string getPilotUnlocalizedFullname() const;
	string getPilotUnlocalizedNickname() const;
	string getPilotUnlocalizedReadname() const;
	string getPilotUnlocalizedCodename() const;
	EnumPilotGender getPilotGender() const;
	EnumPilotPersonality getPilotPersonality() const;
	map<EnumPilotStatusCategory, int64_t> getPilotStatus() const;
	map<EnumTerrainType, EnumTerrainAdaption> getPilotTerrainAdaption() const;
	vector<DataSpecificSkills*> getPilotSpecificSkills() const;
};

