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
/// <summary>
/// 地形情報
/// </summary>
struct GameMapPath;
/// <summary>
/// ゲーム実行クラス
/// </summary>
class GameMain;

struct GameMapPath
{
protected:
	std::string path_name;
	int64_t move_cost;
	TerrainAdaptType terrain_adapt;
public:
	std::string getPathName() const;
	int64_t getMoveCost() const;
	TerrainAdaptType getTerrain() const;
	GameMapPath();
	GameMapPath(json11::Json raw_data);
};

class GameMain {
protected:
	std::shared_ptr<GamePilot> definationPilot(std::shared_ptr<GamePilot> unit);
public:
	bool stage_loaded;
	int map_soundhandler;
	uint64_t map_round;
	int64_t map_width;
	int64_t map_height;
	GameFaction map_phase;
	json11::Json operation_condition;
	std::map<uint64_t, json11::Json> eventTurns;
	std::map<uint64_t, std::map<GameFaction, bool>> isInitialized;
	std::map<std::string, bool, std::less<>> generatedPilot;
	std::map<std::string, std::shared_ptr<GameUnit>, std::less<>> savedUnit;
	std::vector<std::shared_ptr<GameTroop>> troopList;
	std::vector<std::vector<std::pair<bool, GameMapPath>>> stageMap;
	void DrawStageGraph(int windowWidth, int windowHeight);
	void setStageMap(json11::Json raw_data);
	void eventOnDestroy();
	void eventOnTurn();
	void LaunchUnitFromSaveData(std::string pKeyPilotMain, int64_t pPosX, int64_t pPosY,
		std::string pKeyPilotSub = "", GameFaction pFaction = static_cast<GameFaction>(1));
	void CreateUnitByFaction(std::string pKeyUnitMain, int64_t pUnitMainRankHP, int64_t pUnitMainRankEN, int64_t pUnitMainRankArmor,
		int64_t pUnitMainRankSight, int64_t pUnitMainRankEvade, std::string pKeyPilotMain, int64_t pPilotMainLevel, std::string pFaction,
		int64_t pPosX, int64_t pPosY, std::string pKeyUnitSub = "", int64_t pUnitSubRankHP = 0LL, int64_t pUnitSubRankEN = 0LL,
		int64_t pUnitSubRankArmor = 0LL, int64_t pUnitSubRankSight = 0LL, int64_t pUnitSubRankEvade = 0LL, std::string pKeyPilotSub = "",
		int64_t pPilotSubLevel = 0LL);
	void CreateUnitByFaction(std::string pKeyUnitMain, int64_t pUnitMainRank, std::string pKeyPilotMain, int64_t pPilotMainLevel, int64_t pPosX,
		int64_t pPosY, std::string pFaction, std::string pKeyUnitSub = "", int64_t pUnitRankSub = 0LL, std::string pKeyPilotSub = "",
		int64_t pPilotSubLevel = 0LL);
	void SequenceIncreaseTurn();
	bool foundFaction(GameFaction faction);
	GameMain();
};

extern std::shared_ptr<Loader> game_loader;
extern std::shared_ptr<GameMain> game_main;
