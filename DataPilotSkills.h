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

class DataPilotSkills
{
protected:
	std::string SS_registryName;
	std::string SS_displayName;
	std::vector<std::string> SS_description;
	std::vector<int64_t> SS_levelDefine;
	std::vector<int64_t> SS_levelLearn;
	bool    SS_uniqueSkill;
	double  SS_atkBuffPercent;
	double  SS_luckPercent;
	double  SS_incrHitPercentCommanding;
	double  SS_incrEvadePercentCommanding;
	double  SS_incrHitPercentOwner;
	double  SS_incrEvadePercentOwner;
	double  SS_incrCriticalPercentOwner;
	int64_t SS_SPRegenerateValue;
	double  SS_ConsumeSPDecreasePercent;
public:
	std::string getRegName() const;
	std::string getDispName() const;
	std::vector<std::string> getDescription() const;
	bool getIsUnique() const;
	bool calcSkillLearned(std::shared_ptr<GamePilot> owner);
	int64_t calcSkillLevel(std::shared_ptr<GamePilot> owner);
	virtual double  calcAttackBuffPercent(std::shared_ptr<GamePilot> owner, bool isMain);   //アタッカー、援護攻撃(デバフ)
	virtual int64_t calcAttackBuffConstant(std::shared_ptr<GamePilot> owner, bool isMain);  //インファイト、ガンファイト、メイジファイト
	virtual double  calcArmorBuffPercent(std::shared_ptr<GamePilot> owner, bool isMain);    //底力など
	virtual double  calcDamageDecrPercent(std::shared_ptr<GamePilot> owner, bool isMain);   //ガードなど
	virtual int64_t calcMoveRangeIncrease(std::shared_ptr<GamePilot> owner, bool isMain);   //インファイト
	virtual int64_t calcWeaponRangeIncrease(std::shared_ptr<GamePilot> owner, bool isMain); //ガンファイト、メイジファイト
	virtual double  calcHitCommanding(std::shared_ptr<GamePilot> owner, bool isMain);       //指揮官(命中)
	virtual double  calcEvadeCommanding(std::shared_ptr<GamePilot> owner, bool isMain);     //指揮官(回避)
	virtual double  calcHitOwner(std::shared_ptr<GamePilot> owner, bool isMain);            //天才、念動力など(命中)
	virtual double  calcEvadeOwner(std::shared_ptr<GamePilot> owner, bool isMain);          //天才、念動力など(回避)
	virtual double  calcCriticalOwner(std::shared_ptr<GamePilot> owner, bool isMain);       //天才、念動力など(CRT)
	virtual int64_t calcSPRegenerate(std::shared_ptr<GamePilot> owner);		                //SP回復
	virtual bool    canBeSupport(std::shared_ptr<GamePilot> owner, bool isMain);            //援護攻撃、援護防御、MB発動(隣接確認)
	virtual bool    canBeSAttack(std::shared_ptr<GamePilot> owner, bool isMain);            //援護攻撃、MB発動
	virtual bool    canBeSDefence(std::shared_ptr<GamePilot> owner, bool isMain);           //援護防御
	virtual bool    canBeCounter(std::shared_ptr<GamePilot> owner, bool isMain);            //カウンター
	virtual bool    isActiveReverseStrength(std::shared_ptr<GamePilot> owner, bool isMain); //底力(条件)
	virtual int64_t calcSPUp(std::shared_ptr<GamePilot> owner);                             //SPアップ
	virtual int64_t calcHitStat(std::shared_ptr<GamePilot> owner, bool isMain);             //見切り(命中)
	virtual int64_t calcEvadeStat(std::shared_ptr<GamePilot> owner, bool isMain);           //見切り(回避)
	virtual int64_t calcMoraleOverdrive(std::shared_ptr<GamePilot> owner, bool isMain);     //気力限界突破
	virtual bool    canREAttack(std::shared_ptr<GamePilot> owner, bool isMain);			    //再攻撃
	virtual bool    isFocusAttackAvailable(std::shared_ptr<GamePilot> owner, bool isMain);  //集束攻撃
	virtual bool    isHitAndAway(std::shared_ptr<GamePilot> owner, bool isMain);            //ヒットアンドアウェイ
	virtual int64_t calcIncrMoraleCond(std::shared_ptr<GamePilot> owner, DIncrMoraleCond pCond, bool isMain); //気力+、戦意高揚、闘争心
	virtual double  calcConsumeSPDecr(std::shared_ptr<GamePilot> owner);                    //集中力
	virtual bool    canRepSupExtraAction(std::shared_ptr<GamePilot> owner, bool isMain);    //修理技能(HP回復量+20％)、補給技能(移動後使用可能)
	virtual bool    isLearning(std::shared_ptr<GamePilot> owner);                           //ラーニング
	virtual bool    isBulletSave(std::shared_ptr<GamePilot> owner, bool isMain);            //Bセーブ
	virtual bool    isEnergySave(std::shared_ptr<GamePilot> owner, bool isMain);            //Eセーブ
	DataPilotSkills(std::string pRegName, std::string pDispName, std::vector<std::string> pDesc, std::vector<int64_t> pLvDef,
		std::vector<int64_t> pLvLrn, bool pUnique, double pAtkBuffPct, double pLuckPct, double pComHitPct, double pComEvdPct,
		double pOwnHitPct, double pOwnEvdPct, double pOwnCrtPct, int64_t pSPRegenVal, double pConsumeSPDecr);
};

class DPilotSkillDummy : public DataPilotSkills {
protected:
public:
	DPilotSkillDummy();
};

