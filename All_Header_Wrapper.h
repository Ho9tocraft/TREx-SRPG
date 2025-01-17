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

#include "DataPilot.h"
#include "DataHelper.h"
#include "DataUnit.h"
#include "GamePilot.h"
#include "GameUnit.h"
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
class DataPilotSkillDummy;
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
