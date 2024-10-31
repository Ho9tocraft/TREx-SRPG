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
#include "json11.hpp"
#include "DataSkill.h"
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
class DataSkillDummy;
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

enum class DataType : uint64_t {
	PILOTS,
	UNITS,
	SPECIFIC_SKILLS,
	SPECIFIC_ABILITIES,
	SPIRITUALS
};

enum class GameState : uint64_t {
	/// <summary>
	/// タイトル画面
	/// </summary>
	GAME_TITLE = 0LL,
	/// <summary>
	/// シナリオ(ステージ前)
	/// </summary>
	GAME_SCENARIO_PUSH,
	/// <summary>
	/// シナリオ(マップ内)
	/// </summary>
	GAME_SCENARIO_INMAP,
	/// <summary>
	/// 戦闘(ゲームメイン1)
	/// </summary>
	GAME_SCENARIO_BATTLE,
	/// <summary>
	/// シナリオ(ステージ後)
	/// </summary>
	GAME_SCENARIO_POP,
	/// <summary>
	/// インターミッション
	/// </summary>
	GAME_INTERMISSION,
	/// <summary>
	/// ゲームクリア
	/// </summary>
	GAME_CLEAR,
	/// <summary>
	/// ミッション失敗など
	/// </summary>
	GAME_OVER
};

enum class GameUIState : uint64_t {
	/* タイトル画面 */
	/// <summary>
	/// (0)タイトル画面のメニュー
	/// <para>1.はじめから開始(Start)</para>
	/// <para>2.データをロードして開始(Load)</para>
	/// <para>3.途中セーブしたデータから開始(Continue)</para>
	/// <para>4.図鑑(Library)</para>
	/// <para>5.システム(Settings)</para>
	/// <para>6.ゲーム終了(Quit Game)</para>
	/// </summary>
	TITLE_MENU = 0LL,
	/* -- 部隊共通 -- */
	/// <summary>
	/// (A)出撃時のコマンド(出撃準備コマンド)
	/// <para>1.出撃選択へ</para>
	/// <para>2.準備メニュー</para>
	/// <para>3.作戦目的</para>
	/// <para>4.マップ配置へ</para>
	/// <para>5.途中セーブ</para>
	/// </summary>
	BATTLE_PRE_LAUNCH,
	/// <summary>
	/// (B)マップコマンド(元のスパロボと異なり、部隊表はふたつ選択肢として表示される)
	/// <para>1.フェイズ終了</para>
	/// <para>2.検索</para>
	/// <para>3.味方部隊表</para>
	/// <para>4.敵部隊表</para>
	/// <para>5.作戦目的</para>
	/// <para>6.戦況報告</para>
	/// <para>7.システム</para>
	/// <para>8.途中セーブ</para>
	/// </summary>
	BATTLE_MAP_COMMAND,
	/// <summary>
	/// (B-1)フェイズ終了コマンド
	/// </summary>
	BATTLE_PHASE_TRANSITION,
	/// <summary>
	/// (B-2)検索
	/// </summary>
	BATTLE_SEARCH,
	/// <summary>
	/// (B-3)味方部隊表
	/// </summary>
	BATTLE_ALLY_TEAM_LIST,
	/// <summary>
	/// (B-4)敵部隊表
	/// </summary>
	BATTLE_ENEMY_TEAM_LIST,
	/// <summary>
	/// (A-3)(B-5)作戦目的画面
	/// </summary>
	BATTLE_OPERATION_END,
	/// <summary>
	/// (B-6)戦況報告
	/// </summary>
	BATTLE_COMBAT_REPORT,
	/// <summary>
	/// (0-5)(B-7)システム設定
	/// </summary>
	BATTLE_SYSTEM_CONFIG,
	/// <summary>
	/// (A-5)(B-8)途中セーブ
	/// </summary>
	BATTLE_INTERMEDIATE_SAVE,
	/* -- ユニット関連 -- */
	/// <summary>
	/// (C)このターンに移動しておらず、移動可能な場合のユニットコマンド
	/// <para> 1.移動</para>
	/// <para> 2.攻撃(射程が届くなら)</para>
	/// <para> 3.地上／空中切り替え(ステージが地上なら)</para>
	/// <para> 4.メイン変更(ツインユニット時)[注1]</para>
	/// <para> 5.解散(ツインユニット時)／合流(シングルユニット時かつ母艦ではない)</para>
	/// <para> 6.変形系個別コマンド(可能なら)[注2]</para>
	/// <para> 7.補助系個別コマンド(可能なら)[注3]</para>
	/// <para> 8.修理(修理装置を持っているなら)</para>
	/// <para> 9.補給(補給装置を持っているなら)</para>
	/// <para>10.精神</para>
	/// <para>11.能力</para>
	/// <para>[注1]固有のUIなし</para>
	/// <para>[注2]ジェニオンの「GAIモード」などもここ</para>
	/// <para>[注3]ソーラリアンの事象制御やゼルガードのドグマなどもここ</para>
	/// </summary>
	BATTLE_PLAYER_INDIVIDUAL_COMMAND1,
	/// <summary>
	/// (D)移動後のユニットコマンド
	/// <para>1.攻撃(射程が届く+移動後使用可能なら)</para>
	/// <para>2.修理(修理装置を持っているなら)</para>
	/// <para>3.補給(補給装置を持っている+メインユニットのメインパイロットが「補給技能」を習得しているなら)</para>
	/// <para>4.待機</para>
	/// </summary>
	BATTLE_PLAYER_INDIVIDUAL_COMMAND2,
	/// <summary>
	/// (E)攻撃後のユニットコマンド(※メインユニットのメインパイロットが「ヒット＆アウェイ」を習得しているなら)
	/// <para>1.移動</para>
	/// <para>2.待機</para>
	/// </summary>
	BATTLE_PLAYER_INDIVIDUAL_COMMAND3,
	/// <summary>
	/// (F)攻撃後かつ移動後のユニットコマンド(※メインユニットのメインパイロットが「ヒット＆アウェイ」を習得しているなら)
	/// <para>1.待機</para>
	/// <para>(非表示選択肢).考え直す(移動をキャンセルする)</para>
	/// </summary>
	BATTLE_PLAYER_INDIVIDUAL_COMMAND4,
	/// <summary>
	/// (G)行動後のユニットコマンド
	/// <para>1.メイン変更(ツインユニット時)</para>
	/// <para>2.精神</para>
	/// <para>3.能力</para>
	/// </summary>
	BATTLE_PLAYER_INDIVIDUAL_COMMAND5,
	/// <summary>
	/// (H)敵ユニットの移動範囲表示(そのまま○ボタンを押すと敵ユニットの能力表示)
	/// </summary>
	BATTLE_ENEMY_MOVE_RANGE,
	/// <summary>
	/// (C-1)(E-1)移動範囲の表示と移動地点の決定
	/// </summary>
	BATTLE_PLAYER_UNIT_MOVE,
	/// <summary>
	/// (C-2)(D-1)攻撃時の武装を選択する画面
	/// </summary>
	BATTLE_PLAYER_UNIT_WEAPON_SELECT,
	/// <summary>
	/// (C-2-SL)(D-1-SL)武装の射程表示
	/// </summary>
	BATTLE_PLAYER_UNIT_WEAPON_RANGE,
	/// <summary>
	/// (C-2-CF)(D-1-CF)戦闘の予測を表示する画面
	/// </summary>
	BATTLE_UNIT_COMBAT_CONFIRM,
	/// <summary>
	/// (C-5)ツインユニットの合流／解散を決定する画面
	/// </summary>
	BATTLE_PLAYER_UNIT_TEAM_CONFIRM,
	/// <summary>
	/// (C-6)ユニットの変形／合体を決定する画面
	/// </summary>
	BATTLE_PLAYER_UNIT_VR_SELECT,
	/// <summary>
	/// (C-6-EX)ユニットの変形／合体の確認画面
	/// <para>合体の場合: グレンラガン+超銀河ダイグレン→超銀河グレンラガンなど</para>
	/// <para>変形の場合: ジェニオン→ジェニオン・ガイ→ジェミニオン・レイ、超銀河グレンラガン→天元突破グレンラガンなど</para>
	/// </summary>
	BATTLE_PLAYER_UNIT_VR_CONFIRM,
	/// <summary>
	/// (C-7)ユニットの補助系個別コマンド
	/// <para>ルルーシュ搭乗機の「戦術指揮」や、ゼルガードの「ドグマ」なんかがここに該当</para>
	/// </summary>
	BATTLE_PLAYER_UNIT_EXTRA_FEATURES,
	/// <summary>
	/// (C-7-SL)(C-8)(C-9)ユニットの補助系個別コマンドや、「修理」「補給」使用時の射程表示
	/// <para>「修理」は射程0～2(射程0はメインユニット除く)</para>
	/// <para>「補給」は射程0～1(射程0はメインユニット除く)</para>
	/// <para>「戦術指揮」は射程1～5かつ起点指定(起点内に指揮者が含まれるチームがいても対象外)</para>
	/// </summary>
	BATTLE_PLAYER_UNIT_FEATURES_RANGE,
	/// <summary>
	/// (C-7-CF)(C-8-CF)(C-9-CF)ユニットの補助系個別コマンドや、「修理」「補給」使用時の確認表示
	/// </summary>
	BATTLE_PLAYER_UNIT_FEATURES_CONFIRM,
	/// <summary>
	/// (C-10)(G-2)精神コマンド(選択画面)
	/// </summary>
	BATTLE_PLAYER_UNIT_SPIRITUAL_POWERS_SELECT,
	/// <summary>
	/// (C-10-TG)(G-2-TG)精神コマンド(対象選択)
	/// </summary>
	BATTLE_PLAYER_UNIT_SPIRITUAL_POWERS_TARGET,
	/// <summary>
	/// ユニットステータス画面
	/// </summary>
	BATTLE_UNIT_STATUS
};

class Game_TheReminiscenceOfExellia {
protected:
	GameState currentState;
public:
	GameState getCurrentState() const;
	void DrawGameTitle();
	void DrawGameIntermission();
	void DrawGameMap();
	void DrawGameEventInMap();
	void GameMain();
};

class Game_UI {
protected:
public:
};
