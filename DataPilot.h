#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <compare>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <random>
#include <locale>
#include <sstream>
#include <string>
#include <exception>
#include <DxLib.h>
#include "json11.hpp"

#include "All_Header_Wrapper.h"
#include "DataHelper.h"
#include "DataUnit.h"
#include "GamePilot.h"
#include "GameUtils.h"
#include "Main.h"

/* -- 前方宣言 -- */

/// <summary>
/// ゲームで用いる変数の類を保存する構造体
/// </summary>
struct GameVariableUtils;
/// <summary>
/// エンティティ名取得時に用いるマクロ
/// </summary>
enum class EntityNameStrCategory : int64_t;
/// <summary>
/// 地形適応の項目
/// </summary>
enum class TerrainAdaptType;
/// <summary>
/// 地形適応の値
/// </summary>
enum class TerrainAdaptValue;
/// <summary>
/// パイロット性別
/// </summary>
enum class EnumPilotGender : int64_t;
/// <summary>
/// イベント中の気力変動効果の発動トリガー
/// </summary>
enum class EnumGameplayMoraleEffectEvent : int64_t;
/// <summary>
/// パイロット性格
/// </summary>
enum class EnumPilotPersonality : int64_t;
/// <summary>
/// パイロットの能力値の成長タイプ
/// </summary>
enum class EnumPilotGrowthType : int64_t;
/// <summary>
/// パイロットの能力値のカテゴリ
/// </summary>
enum class EnumPilotStatCategory : int64_t;
/// <summary>
/// 地形適応同士の比較
/// </summary>
class TerrainAdaptCompare;
/// <summary>
/// ※要static参照 パイロット性格の拡張クラス
/// </summary>
class ExpandEnumPilotPersonality;
/// <summary>
/// パイロットの能力値の成長タイプに関わる拡張クラス
/// </summary>
class ExpandEnumPilotGrowthType;
/// <summary>
/// ライブラリに登録するためのスキルデータ（の、抽象クラス）
/// </summary>
class DataPilotSkill;
/// <summary>
/// 存在しないスキルを指定したときのダミー用スキル
/// </summary>
class DataPilotSKillDummy;
/// <summary>
/// 底力スキル
/// </summary>
class DataPilotSkillPotentiality;
/// <summary>
/// ライブラリに登録するためのパイロットデータ
/// </summary>
class DataPilot;
/// <summary>
/// ライブラリに登録するためのユニットデータ
/// </summary>
class DataUnit;
/// <summary>
/// ゲーム上で運用するパイロットデータ
/// </summary>
class GamePilot;
/// <summary>
/// ゲーム上で運用するユニットデータ
/// </summary>
class GameUnit;

using namespace json11;

/* --クラス等宣言-- */
enum class TerrainAdaptType {
	/// <summary>
	/// 空中
	/// </summary>
	AIR,
	/// <summary>
	/// 陸上
	/// </summary>
	GROUND,
	/// <summary>
	/// 海上／水中
	/// </summary>
	OCEAN,
	/// <summary>
	/// 宇宙／異界
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

enum class EnumPilotGender : int64_t {
	/// <summary>
	/// 不定・無性別など
	/// </summary>
	Undefined = -1LL,
	/// <summary>
	/// 男
	/// </summary>
	Male,
	/// <summary>
	/// 女
	/// </summary>
	Female,
	/// <summary>
	/// 機械（AIの類）
	/// </summary>
	Machine
};

enum class EnumGameplayMoraleEffectEvent : int64_t {
	/// <summary>
	/// 自分->敵：被弾
	/// </summary>
	HIT_OWN_ATTACK,
	/// <summary>
	/// 自分->敵：回避
	/// </summary>
	AVO_OWN_ATTACK,
	/// <summary>
	/// 自分->敵：撃破
	/// </summary>
	DFT_OWN_ATTACK,
	/// <summary>
	/// サブ->敵：撃破
	/// </summary>
	DFT_SUB_ATTACK,
	/// <summary>
	/// 敵->自分：被弾
	/// </summary>
	HIT_OPP_ATTACK,
	/// <summary>
	/// 敵->自分：回避
	/// </summary>
	AVO_OPP_ATTACK,
	/// <summary>
	/// 敵->味方：撃破
	/// </summary>
	DFT_OPP_ATTACK
};

enum class EnumPilotPersonality : int64_t {
	/// <summary>
	/// 普通
	/// </summary>
	GENERALLY,
	/// <summary>
	/// 強気
	/// </summary>
	STUBBORN,
	/// <summary>
	/// 超強気
	/// </summary>
	HIGH_STUBBORN,
	/// <summary>
	/// 冷静
	/// </summary>
	SERENITY,
	/// <summary>
	/// 慎重
	/// </summary>
	CAREFUL,
	/// <summary>
	/// 楽天家
	/// </summary>
	EASY_GOING,
	/// <summary>
	/// 努力家
	/// </summary>
	HARDWORKING,
	/// <summary>
	/// 短気
	/// </summary>
	IMPATIENT,
	/// <summary>
	/// 大物
	/// </summary>
	BIGWIG,
	/// <summary>
	/// 超大物
	/// </summary>
	VERY_BIGWIG,
	/// <summary>
	/// 狡猾
	/// </summary>
	DEVIOUS,
	/// <summary>
	/// 残虐
	/// </summary>
	BRUTALITY,
	/// <summary>
	/// 残影
	/// </summary>
	REMNANT_SHADOW,
	/// <summary>
	/// 浄火
	/// </summary>
	SACRED_FIRE
};

enum class EnumPilotGrowthType : int64_t {
	/// <summary>
	/// 標準
	/// </summary>
	NORMS,
	/// <summary>
	/// 格闘・標準
	/// </summary>
	MELEE_STANDARD,
	/// <summary>
	/// 格闘・万能
	/// </summary>
	MELEE_ALLROUND,
	/// <summary>
	/// 格闘・射撃重視
	/// </summary>
	MELEE_FOCUS_RANGED,
	/// <summary>
	/// 格闘・魔装重視
	/// </summary>
	MELEE_FOCUS_MAGIC,
	/// <summary>
	/// 格闘・防御
	/// </summary>
	MELEE_DEFENCE,
	/// <summary>
	/// 格闘・晩成
	/// </summary>
	MELEE_LATECOMERS,
	/// <summary>
	/// 射撃・標準
	/// </summary>
	RANGED_STANDARD,
	/// <summary>
	/// 射撃・万能
	/// </summary>
	RANGED_ALLROUND,
	/// <summary>
	/// 射撃・格闘重視
	/// </summary>
	RANGED_FOCUS_MELEE,
	/// <summary>
	/// 射撃・魔装重視
	/// </summary>
	RANGED_FOCUS_MAGIC,
	/// <summary>
	/// 射撃・防御
	/// </summary>
	RANGED_DEFENCE,
	/// <summary>
	/// 射撃・晩成
	/// </summary>
	RANGED_LATECOMERS,
	/// <summary>
	/// 魔装・標準
	/// </summary>
	MAGIC_STANDARD,
	/// <summary>
	/// 魔装・万能
	/// </summary>
	MAGIC_ALLROUND,
	/// <summary>
	/// 魔装・格闘重視
	/// </summary>
	MAGIC_FOCUS_MELEE,
	/// <summary>
	/// 魔装・射撃重視
	/// </summary>
	MAGIC_FOCUS_RANGED,
	/// <summary>
	/// 魔装・防御
	/// </summary>
	MAGIC_DEFENCE,
	/// <summary>
	/// 魔装・晩成
	/// </summary>
	MAGIC_LATECOMERS,
	/// <summary>
	/// 万能・標準
	/// </summary>
	ALLROUNDER_STANDARD,
	/// <summary>
	/// 万能・晩成
	/// </summary>
	ALLROUNDER_LATECOMERS,
	/// <summary>
	/// SP重視
	/// </summary>
	SP_EXTREME,
	/// <summary>
	/// サブパイロット
	/// </summary>
	SUB_PILOT
};

enum class EnumPilotStatCategory : int64_t {
	/// <summary>
	/// 格闘
	/// </summary>
	MEL,
	/// <summary>
	/// 射撃
	/// </summary>
	RNG,
	/// <summary>
	/// 魔装
	/// </summary>
	MAT,
	/// <summary>
	/// 技量
	/// </summary>
	DEX,
	/// <summary>
	/// 物理防御
	/// </summary>
	DEF,
	/// <summary>
	/// 魔法防御
	/// </summary>
	MDF,
	/// <summary>
	/// 回避
	/// </summary>
	AVD,
	/// <summary>
	/// 命中
	/// </summary>
	ACC,
	/// <summary>
	/// 魔法抵抗
	/// </summary>
	RST,
	/// <summary>
	/// 精神ポイント(SP)
	/// </summary>
	SPR
};

class TerrainAdaptCompare {
private:
	TerrainAdaptCompare();
public:
	static float CalculateTerrainAdaptUnitAndPilot(TerrainAdaptValue adaptUnit, TerrainAdaptValue adaptPilot);
	static TerrainAdaptValue GetTerrainAdaptAverage(TerrainAdaptValue adaptUnit, TerrainAdaptValue adaptPilot);
};

class ExpandEnumPilotPersonality {
private:
	ExpandEnumPilotPersonality();
protected:
public:
	static int64_t ApplyMoraleByPersonality(EnumGameplayMoraleEffectEvent ev, EnumPilotPersonality ps);
};

class ExpandEnumPilotGrowthType {
private:
	ExpandEnumPilotGrowthType();
protected:
	std::map<EnumPilotGrowthType, std::map<EnumPilotStatCategory, int64_t>> tablePilotGrowthCalc = {
		{ EnumPilotGrowthType::NORMS, {
			{ EnumPilotStatCategory::MEL,   0LL }, { EnumPilotStatCategory::RNG,   0LL }, { EnumPilotStatCategory::MAT,   0LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF,   0LL }, { EnumPilotStatCategory::MDF,   0LL },
			{ EnumPilotStatCategory::AVD,   0LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST,   0LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::MELEE_STANDARD, {
			{ EnumPilotStatCategory::MEL,  20LL }, { EnumPilotStatCategory::RNG, -15LL }, { EnumPilotStatCategory::MAT, -15LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF,  15LL }, { EnumPilotStatCategory::MDF,  15LL },
			{ EnumPilotStatCategory::AVD, -10LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST, -10LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::MELEE_ALLROUND, {
			{ EnumPilotStatCategory::MEL,  30LL }, { EnumPilotStatCategory::RNG, -10LL }, { EnumPilotStatCategory::MAT, -10LL },
			{ EnumPilotStatCategory::DEX,   5LL }, { EnumPilotStatCategory::DEF,  20LL }, { EnumPilotStatCategory::MDF,  20LL },
			{ EnumPilotStatCategory::AVD, -30LL }, { EnumPilotStatCategory::ACC,   5LL }, { EnumPilotStatCategory::RST, -30LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::MELEE_FOCUS_RANGED, {
			{ EnumPilotStatCategory::MEL,  20LL }, { EnumPilotStatCategory::RNG,  -5LL }, { EnumPilotStatCategory::MAT, -15LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF,  10LL }, { EnumPilotStatCategory::MDF,  10LL },
			{ EnumPilotStatCategory::AVD, -10LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST, -10LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::MELEE_FOCUS_MAGIC, {
			{ EnumPilotStatCategory::MEL,  20LL }, { EnumPilotStatCategory::RNG, -15LL }, { EnumPilotStatCategory::MAT,  -5LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF,  10LL }, { EnumPilotStatCategory::MDF,  10LL },
			{ EnumPilotStatCategory::AVD, -10LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST, -10LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::MELEE_DEFENCE, {
			{ EnumPilotStatCategory::MEL,  15LL }, { EnumPilotStatCategory::RNG, -20LL }, { EnumPilotStatCategory::MAT, -20LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF,  30LL }, { EnumPilotStatCategory::MDF,  30LL },
			{ EnumPilotStatCategory::AVD, -25LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST, -10LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::MELEE_LATECOMERS, {
			{ EnumPilotStatCategory::MEL,  20LL }, { EnumPilotStatCategory::RNG, -20LL }, { EnumPilotStatCategory::MAT, -20LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF,  25LL }, { EnumPilotStatCategory::MDF,  25LL },
			{ EnumPilotStatCategory::AVD, -25LL }, { EnumPilotStatCategory::ACC,  10LL }, { EnumPilotStatCategory::RST, -25LL },
			{ EnumPilotStatCategory::SPR,  10LL }
		}},
		{ EnumPilotGrowthType::RANGED_STANDARD, {
			{ EnumPilotStatCategory::MEL, -15LL }, { EnumPilotStatCategory::RNG,  20LL }, { EnumPilotStatCategory::MAT, -15LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF, -15LL }, { EnumPilotStatCategory::MDF, -15LL },
			{ EnumPilotStatCategory::AVD,  20LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST,  20LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::RANGED_ALLROUND, {
			{ EnumPilotStatCategory::MEL,  -5LL }, { EnumPilotStatCategory::RNG,  30LL }, { EnumPilotStatCategory::MAT,  -5LL },
			{ EnumPilotStatCategory::DEX,   5LL }, { EnumPilotStatCategory::DEF, -15LL }, { EnumPilotStatCategory::MDF, -15LL },
			{ EnumPilotStatCategory::AVD,  20LL }, { EnumPilotStatCategory::ACC,   5LL }, { EnumPilotStatCategory::RST,  20LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::RANGED_FOCUS_MELEE, {
			{ EnumPilotStatCategory::MEL,   0LL }, { EnumPilotStatCategory::RNG,  15LL }, { EnumPilotStatCategory::MAT, -15LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF, -15LL }, { EnumPilotStatCategory::MDF, -15LL },
			{ EnumPilotStatCategory::AVD,  15LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST,  15LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::RANGED_FOCUS_MAGIC, {
			{ EnumPilotStatCategory::MEL, -15LL }, { EnumPilotStatCategory::RNG,  15LL }, { EnumPilotStatCategory::MAT,   0LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF, -15LL }, { EnumPilotStatCategory::MDF, -15LL },
			{ EnumPilotStatCategory::AVD,  15LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST,  15LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::RANGED_DEFENCE, {
			{ EnumPilotStatCategory::MEL, -20LL }, { EnumPilotStatCategory::RNG,   0LL }, { EnumPilotStatCategory::MAT,  10LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF,   0LL }, { EnumPilotStatCategory::MDF,   0LL },
			{ EnumPilotStatCategory::AVD,   5LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST,   5LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::RANGED_LATECOMERS, {
			{ EnumPilotStatCategory::MEL, -20LL }, { EnumPilotStatCategory::RNG,   0LL }, { EnumPilotStatCategory::MAT,  20LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF, -15LL }, { EnumPilotStatCategory::MDF, -15LL },
			{ EnumPilotStatCategory::AVD,  20LL }, { EnumPilotStatCategory::ACC,  10LL }, { EnumPilotStatCategory::RST,  25LL },
			{ EnumPilotStatCategory::SPR,  10LL }
		}},
		{ EnumPilotGrowthType::MAGIC_STANDARD, {
			{ EnumPilotStatCategory::MEL, -15LL }, { EnumPilotStatCategory::RNG, -15LL }, { EnumPilotStatCategory::MAT,  20LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF, -20LL }, { EnumPilotStatCategory::MDF,  15LL },
			{ EnumPilotStatCategory::AVD,   0LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST,  15LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::MAGIC_ALLROUND, {
			{ EnumPilotStatCategory::MEL, -10LL }, { EnumPilotStatCategory::RNG, -10LL }, { EnumPilotStatCategory::MAT,  10LL },
			{ EnumPilotStatCategory::DEX,  10LL }, { EnumPilotStatCategory::DEF, -10LL }, { EnumPilotStatCategory::MDF,   5LL },
			{ EnumPilotStatCategory::AVD,   0LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST,   5LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::MAGIC_FOCUS_MELEE, {
			{ EnumPilotStatCategory::MEL, -15LL }, { EnumPilotStatCategory::RNG, -10LL }, { EnumPilotStatCategory::MAT,  15LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF,   0LL }, { EnumPilotStatCategory::MDF,  -5LL },
			{ EnumPilotStatCategory::AVD,   0LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST,  15LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::MAGIC_FOCUS_RANGED, {
			{ EnumPilotStatCategory::MEL, -20LL }, { EnumPilotStatCategory::RNG,  -5LL }, { EnumPilotStatCategory::MAT,  15LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF,   0LL }, { EnumPilotStatCategory::MDF,  -5LL },
			{ EnumPilotStatCategory::AVD,   5LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST,  10LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::MAGIC_DEFENCE, {
			{ EnumPilotStatCategory::MEL, -20LL }, { EnumPilotStatCategory::RNG, -20LL }, { EnumPilotStatCategory::MAT,  15LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF,   5LL }, { EnumPilotStatCategory::MDF,  10LL },
			{ EnumPilotStatCategory::AVD,   0LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST,  15LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::MAGIC_LATECOMERS, {
			{ EnumPilotStatCategory::MEL, -25LL }, { EnumPilotStatCategory::RNG, -25LL }, { EnumPilotStatCategory::MAT,  20LL },
			{ EnumPilotStatCategory::DEX,  10LL }, { EnumPilotStatCategory::DEF, -10LL }, { EnumPilotStatCategory::MDF,  15LL },
			{ EnumPilotStatCategory::AVD,  10LL }, { EnumPilotStatCategory::ACC,   5LL }, { EnumPilotStatCategory::RST,  25LL },
			{ EnumPilotStatCategory::SPR,  10LL }
		}},
		{ EnumPilotGrowthType::ALLROUNDER_STANDARD, {
			{ EnumPilotStatCategory::MEL,  15LL }, { EnumPilotStatCategory::RNG,  15LL }, { EnumPilotStatCategory::MAT,  15LL },
			{ EnumPilotStatCategory::DEX,   5LL }, { EnumPilotStatCategory::DEF, -10LL }, { EnumPilotStatCategory::MDF, -10LL },
			{ EnumPilotStatCategory::AVD,  15LL }, { EnumPilotStatCategory::ACC,   5LL }, { EnumPilotStatCategory::RST,   5LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}},
		{ EnumPilotGrowthType::ALLROUNDER_LATECOMERS, {
			{ EnumPilotStatCategory::MEL,  15LL }, { EnumPilotStatCategory::RNG,  15LL }, { EnumPilotStatCategory::MAT,  15LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF, -10LL }, { EnumPilotStatCategory::MDF, -10LL },
			{ EnumPilotStatCategory::AVD,  20LL }, { EnumPilotStatCategory::ACC,   5LL }, { EnumPilotStatCategory::RST,   5LL },
			{ EnumPilotStatCategory::SPR,  10LL }
		}},
		{ EnumPilotGrowthType::SP_EXTREME, {
			{ EnumPilotStatCategory::MEL, -10LL }, { EnumPilotStatCategory::RNG, -10LL }, { EnumPilotStatCategory::MAT, -10LL },
			{ EnumPilotStatCategory::DEX, -10LL }, { EnumPilotStatCategory::DEF,   0LL }, { EnumPilotStatCategory::MDF,   0LL },
			{ EnumPilotStatCategory::AVD,   0LL }, { EnumPilotStatCategory::ACC,  -5LL }, { EnumPilotStatCategory::RST,   0LL },
			{ EnumPilotStatCategory::SPR,  35LL }
		}},
		{ EnumPilotGrowthType::SUB_PILOT, {
			{ EnumPilotStatCategory::MEL,   0LL }, { EnumPilotStatCategory::RNG,   0LL }, { EnumPilotStatCategory::MAT,   0LL },
			{ EnumPilotStatCategory::DEX,   0LL }, { EnumPilotStatCategory::DEF,   0LL }, { EnumPilotStatCategory::MDF,   0LL },
			{ EnumPilotStatCategory::AVD,   0LL }, { EnumPilotStatCategory::ACC,   0LL }, { EnumPilotStatCategory::RST,   0LL },
			{ EnumPilotStatCategory::SPR,   0LL }
		}}
	};
public:
	std::map<EnumPilotStatCategory, int64_t> GetPilotGrowthType(EnumPilotGrowthType pGrowthType) const;
};

class DataPilotSkill {
protected:
	std::string skillDefaultName;
	std::string skillCustomName;
	std::vector<std::string> skillDefaultDesc;
	std::vector<std::string> skillCustomDesc;
	void setDefDisplayData(std::string pDefName, std::vector<std::string> pDefDesc);
	void setCusDisplayData(std::string pCusName, std::vector<std::string> pCusDesc);
public:
	std::string GetSkillDefaultName() const;
	std::string GetSkillCustomName() const;
	std::vector<std::string> GetSkillDefaultDesc() const;
	std::vector<std::string> GetSkillCustomDesc() const;
	/*
	* TODO:
	* - 特殊スキルの発動条件(引数: GameUnit)
	* - 発動時の特殊効果
	*/
	DataPilotSkill(std::string pDefName, std::vector<std::string> pDefDesc, std::string pCusName, std::vector<std::string> pCusDesc);
	DataPilotSkill(DataPilotSkill const& iRhs);
	DataPilotSkill(DataPilotSkill* iRhs);
};

class DataPilotSKillDummy : public DataPilotSkill {
protected:
public:
	DataPilotSKillDummy();
	DataPilotSKillDummy(DataPilotSKillDummy const& iRhs);
	DataPilotSKillDummy(DataPilotSKillDummy* iRhs);
};

class DataPilot {
protected:
	std::string pilotFullname;
	std::string pilotNickname;
	std::string pilotReadname;
	std::string pilotCodename;
	std::string pilotGenderCustomDisplay;
	std::string pilotBgmPath;
	std::string pilotGraphPath;
	EnumPilotGender pilotGender;
	EnumPilotPersonality pilotPersonality;
	EnumPilotGrowthType pilotGrowthType;
	std::map<TerrainAdaptType, TerrainAdaptValue> pilotTerrainAdapt;
	std::vector<std::unique_ptr<DataPilotSkill>> pilotSkills;
	void SetDataPilot(Json dataOrigin);
public:
	std::string GetPilotName(EntityNameStrCategory target) const;
	EnumPilotGender GetPilotGender() const;
	std::string GetPilotGenderStr() const;
	EnumPilotPersonality GetPilotPersonality() const;
	std::string GetPilotPersonalityStr() const;
	EnumPilotGrowthType GetPilotGrowthType() const;
	std::map<TerrainAdaptType, TerrainAdaptValue>& GetPilotTerrainAdapt();
};
