#pragma once

//STL
#include <exception>  //Exception Handling
#include <stdexcept>  //Exception Class
#include <utility>    //
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
#include <format>
#include <codecvt>
//NODEC
#include <nodec/unicode.hpp>
//DXLIB
#include <DxLib.h>
//JSON11
#include "json11.hpp"
//STRCONV2
#include "strconv2.h"

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
/// パイロットのステータス項目
/// </summary>
enum class DPilotStatusType;
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
/// <summary>
/// ユニットサイズ
/// </summary>
enum class DUnitSize;
/// <summary>
/// ユニットプロフィール
/// </summary>
struct DUnitProfile;
/// <summary>
/// ユニットステータス
/// </summary>
struct DUnitStatus;
/// <summary>
/// ユニット設定
/// </summary>
class DataUnit;
/// <summary>
/// ユニットの特殊能力
/// </summary>
class DataUnitSkills;
/// <summary>
/// 武装の属性のコンディション
/// </summary>
enum class DataUWAttributeCondition;
/// <summary>
/// 武装の属性
/// </summary>
class DataUWeaponAttributes;
/// <summary>
/// ユニットの武装
/// </summary>
class DataUnitWeapons;
/// <summary>
/// ゲーム上のパイロットデータ
/// </summary>
class GamePilot;
/// <summary>
/// ユニットの状態
/// </summary>
enum class UnitCondition;
/// <summary>
/// ユニットステータスのカテゴリ(改造・参照に使用)
/// </summary>
enum class InGUnitStatCategory;
/// <summary>
/// ゲーム内のユニットステータス
/// </summary>
struct InGameUnitStatus;
/// <summary>
/// ゲーム上のユニットデータ
/// </summary>
class GameUnit;
/// <summary>
/// 陣営
/// </summary>
enum class GameFaction;
/// <summary>
/// ゲーム上のツインユニットデータ
/// </summary>
class GameTroop;
/// <summary>
/// 読み込みパスの対象
/// </summary>
enum class LoaderHandlerType;
/// <summary>
/// ローダー
/// </summary>
class Loader;

enum class LoaderHandlerType {
	/// <summary>
	/// パイロットデータ
	/// </summary>
	DATA_PILOT,
	/// <summary>
	/// ユニットデータ
	/// </summary>
	DATA_UNIT,
	/// <summary>
	/// 精神コマンドデータ
	/// </summary>
	DATA_SP,
	/// <summary>
	/// ステージデータ
	/// </summary>
	DATA_STAGES,
	/// <summary>
	/// 顔グラ
	/// </summary>
	GRAPH_PILOT,
	/// <summary>
	/// ユニットグラ
	/// </summary>
	GRAPH_UNIT,
	/// <summary>
	/// UI
	/// </summary>
	GRAPH_USER_INTERFACE
};

class Loader
{
protected:
public:
	int unitGraphResolution;
	std::map<std::string, std::shared_ptr<DataPilot>, std::less<>> registry_pilots;
	std::map<std::string, std::shared_ptr<DataPilotSkills>, std::less<>> registry_pskills;
	std::map<std::string, std::shared_ptr<DataUnit>, std::less<>> registry_units;
	std::string openTextFile(const std::string& path);
	json11::Json parseResource(const std::string& path);
	void initializeConfigureData();
	void registeringPilot(json11::Json raw_data);
	void registeringPilot(std::string key, json11::Json raw_data);
	void registeringUnit(json11::Json raw_data);
	void registeringUnit(std::string key, json11::Json raw_data);
	std::string loadPath(LoaderHandlerType hType, std::string path = "");
	std::shared_ptr<DataPilotSkills> findSkill(std::string SS_typename);
	Loader();
};

