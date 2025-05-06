#pragma once

/* Includes */
//STL
#include <exception>  //Exception Handling
#include <stdexcept>  //Exception Class
#include <utility>    //Utility Component
#include <ratio>
#include <functional>
#include <memory>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <random>
#include <numeric>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <regex>
//NODEC
#include <nodec/unicode.hpp>
//DXLIB
#include <DxLib.h>
//JSON11
#include "json11.hpp"

/* 前方宣言 */

/// <summary>
/// 地形適応(Key)
/// </summary>
enum class TerrainAdaptType;
/// <summary>
/// 地形適応(Value)
/// </summary>
enum class TerrainAdaptValue;
/// <summary>
/// 性別タイプ
/// </summary>
enum class DPilotGenderType;
/// <summary>
/// 性格タイプ
/// </summary>
enum class DPilotPersonalityType;
/// <summary>
/// パイロット成長タイプ
/// </summary>
enum class DPilotGrowthType;
/// <summary>
/// 気力+用コンディション
/// </summary>
enum class DIncrMoraleCond;
/// <summary>
/// パイロットプロフィール
/// </summary>
struct DPilotProfile;
/// <summary>
/// パイロット設定
/// </summary>
class DataPilot;
/// <summary>
/// パイロットの特殊スキル(抽象クラス)
/// </summary>
class DataPilotSkills;
class DataPSkillDummy;

//Include ho9tocraft
#include "DataPilotSkills.h"

/* 関数プロトタイプ宣言 */
DPilotGenderType ConvertToGenderType(int from);
DPilotGenderType ConvertToGenderType(std::string from);
DPilotPersonalityType ConvertToPersonalityType(int from);
DPilotPersonalityType ConvertToPersonalityType(std::string from);
DPilotGrowthType ConvertToGrowthType(int from);
DPilotGrowthType ConvertToGrowthType(std::string from);

double ConvertTerrainAdaptToAdjustValue(TerrainAdaptValue val);

enum class TerrainAdaptType {
	/// <summary>
	/// 空
	/// </summary>
	AIR,
	/// <summary>
	/// 陸
	/// </summary>
	GROUND,
	/// <summary>
	/// 海
	/// </summary>
	OCEAN,
	/// <summary>
	/// 宇
	/// </summary>
	OUTERLANDS
};

enum class TerrainAdaptValue {
	E,
	D,
	C,
	B,
	A,
	S
};

/* 実体 */
enum class DPilotGenderType {
	/// <summary>
	/// 男
	/// </summary>
	MALE,
	/// <summary>
	/// 女
	/// </summary>
	FEMALE,
	/// <summary>
	/// 無性
	/// </summary>
	NO_MALE,
	/// <summary>
	/// 機械
	/// </summary>
	MACHINE
};
enum class DPilotPersonalityType {
	/// <summary>
	/// 普通
	/// </summary>
	DEFAULT,
	/// <summary>
	/// 強気
	/// </summary>
	BULLISH,
	/// <summary>
	/// 超強気
	/// </summary>
	VERY_BULLISH,
	/// <summary>
	/// 冷静
	/// </summary>
	SERENITY,
	/// <summary>
	/// 慎重
	/// </summary>
	PRUDENT,
	/// <summary>
	/// 楽天家
	/// </summary>
	OPTIMIST,
	/// <summary>
	/// 努力家
	/// </summary>
	HARDWORKER,
	/// <summary>
	/// 短気
	/// </summary>
	IMPATIENT,
	/// <summary>
	/// 大物
	/// </summary>
	SUPERFLUOUS,
	/// <summary>
	/// 超大物
	/// </summary>
	VERY_SUPERFLUOUS,
	/// <summary>
	/// 狡猾
	/// </summary>
	GUILEFUL,
	/// <summary>
	/// 残虐
	/// </summary>
	VIOLENCE,
	/// <summary>
	/// 残影
	/// </summary>
	REMNANT_FIRE,
	/// <summary>
	/// 光輝（リーン専用）
	/// </summary>
	REFLUGENCE
};
enum class DPilotGrowthType {
	/// <summary>
	/// 標準
	/// </summary>
	NORMAL,
	/// <summary>
	/// 格闘・標準
	/// </summary>
	MELEE_NORMAL,
	/// <summary>
	/// 格闘・万能
	/// </summary>
	MELEE_ALMIGHTY,
	/// <summary>
	/// 格闘・射撃重視
	/// </summary>
	MELEE_FOC_RANGED,
	/// <summary>
	/// 格闘・魔力重視
	/// </summary>
	MELEE_FOC_MAGIC,
	/// <summary>
	/// 格闘・防御
	/// </summary>
	MELEE_DEFENSIVE,
	/// <summary>
	/// 格闘・晩成
	/// </summary>
	MELEE_LATE_BLOOM,
	/// <summary>
	/// 射撃・標準
	/// </summary>
	RANGED_NORMAL,
	/// <summary>
	/// 射撃・万能
	/// </summary>
	RANGED_ALMIGHTY,
	/// <summary>
	/// 射撃・格闘重視
	/// </summary>
	RANGED_FOC_MELEE,
	/// <summary>
	/// 射撃・魔力重視
	/// </summary>
	RANGED_FOC_MAGIC,
	/// <summary>
	/// 射撃・防御
	/// </summary>
	RANGED_DEFENSIVE,
	/// <summary>
	/// 射撃・晩成
	/// </summary>
	RANGED_LATE_BLOOM,
	/// <summary>
	/// 魔力・標準
	/// </summary>
	MAGIC_NORMAL,
	/// <summary>
	/// 魔力・万能
	/// </summary>
	MAGIC_ALMIGHTY,
	/// <summary>
	/// 魔力・格闘重視
	/// </summary>
	MAGIC_FOC_MELEE,
	/// <summary>
	/// 魔力・射撃重視
	/// </summary>
	MAGIC_FOC_RANGED,
	/// <summary>
	/// 魔力・防御
	/// </summary>
	MAGIC_DEFENSIVE,
	/// <summary>
	/// 魔力・晩成
	/// </summary>
	MAGIC_LATE_BLOOM,
	/// <summary>
	/// 万能・標準
	/// </summary>
	ALMIGHTY_NORMAL,
	/// <summary>
	/// 万能・晩成
	/// </summary>
	ALMIGHTY_LATE_BLOOM,
	/// <summary>
	/// 精神ポイント(SP)重視
	/// </summary>
	SP_FOCUS,
	/// <summary>
	/// サブパイロット
	/// </summary>
	SUB_PILOTS
};

enum class DIncrMoraleCond {
	/// <summary>
	/// 闘争心
	/// </summary>
	ON_MAP_START = -1,
	/// <summary>
	/// 気力+(回避)
	/// </summary>
	ON_EVADE,
	/// <summary>
	/// 気力+(撃破)
	/// </summary>
	ON_DESTRUCT,
	/// <summary>
	/// 気力+(ダメージ)
	/// </summary>
	ON_DAMAGED,
	/// <summary>
	/// 気力+(命中)
	/// </summary>
	ON_HIT,
	/// <summary>
	/// 戦意高揚
	/// </summary>
	ON_TURN_START
};

struct DPilotProfile {
protected:
	std::string full_name;
	std::string nick_name;
	std::string read_name;
	std::string code_name;
	DPilotGenderType gender_type;
	std::string gender_custom_display;
	DPilotPersonalityType personality_type;
	int drop_experience;
	std::string bgmFile;
	std::string graphFile;
	std::string decideGenderDisplayStr(std::string from_value);
public:
	int BgmHandler;
	int GraphHandler;
	std::string getFullname() const;
	std::string getNickname() const;
	std::string getReadname() const;
	std::string getCodename() const;
	DPilotGenderType getGenderType() const;
	std::string getGenderDisplayStr() const;
	DPilotPersonalityType getPersonality() const;
	int getDropExp() const;
	std::string getBgmFile() const;
	std::string getGraphFile() const;
	/// <summary>
	/// コンストラクタ本体
	/// </summary>
	DPilotProfile(std::string pFullname, std::string pNickname, std::string pReadname, std::string pCodename,
		DPilotGenderType pGenderType, std::string pGenderDispStr, DPilotPersonalityType pPersonalityType, int pDropExp,
		std::string pBgmFile, std::string pGraphPath);
	/// <summary>
	/// string -> enum
	/// </summary>
	DPilotProfile(std::string pFullname, std::string pNickname, std::string pReadname, std::string pCodename, std::string pGenderType,
		std::string pGenderDispStr, std::string pPersonalityType, int pDropExp, std::string pBgmFile, std::string pGraphPath);
	/// <summary>
	/// int -> enum
	/// </summary>
	DPilotProfile(std::string pFullname, std::string pNickname, std::string pReadname, std::string pCodename, int pGenderType,
		std::string pGenderDispStr, int pPersonalityType, int pDropExp, std::string pBgmFile, std::string pGraphPath);
	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	DPilotProfile();
};

class DataPilot {
protected:
	DataPilot(json11::Json raw_data);
public:
	DPilotProfile profile;
	DPilotGrowthType growth_type;
	std::map<TerrainAdaptType, TerrainAdaptValue> terrain_adapt;
	std::vector<DataPilotSkills*> specific_skills;
};
