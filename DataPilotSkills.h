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
#include "DataPilot.h"

class DataPilotSkills
{
protected:
	std::string SS_registryName;
	std::string SS_displayName;
	std::vector<std::string> SS_description;
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
	DataPilotSkills(std::string pRegName, std::string pDispName, std::vector<std::string> pDesc,
		bool pUnique, double pAtkBuffPct, double pLuckPct, double pComHitPct, double pComEvdPct,
		double pOwnHitPct, double pOwnEvdPct, double pOwnCrtPct, int64_t pSPRegenVal, double pConsumeSPDecr);
public:
	std::string getRegName() const;
	std::string getDispName() const;
	std::vector<std::string> getDescription() const;
	bool getIsUnique() const;
	virtual double  calcAttackBuffPercent();   //アタッカー、援護攻撃(デバフ)
	virtual int64_t calcAttackBuffConstant();  //インファイト、ガンファイト、メイジファイト
	virtual double  calcArmorBuffPercent();    //底力など
	virtual double  calcDamageDecrPercent();   //ガードなど
	virtual int64_t calcMoveRangeIncrease();   //インファイト
	virtual int64_t calcWeaponRangeIncrease(); //ガンファイト、メイジファイト
	virtual double  calcHitCommanding();       //指揮官(命中)
	virtual double  calcEvadeCommanding();     //指揮官(回避)
	virtual double  calcHitOwner();            //天才、念動力など(命中)
	virtual double  calcEvadeOwner();          //天才、念動力など(回避)
	virtual double  calcCriticalOwner();       //天才、念動力など(CRT)
	virtual int64_t calcSPRegenerate();        //SP回復
	virtual bool    canBeSupport();            //援護攻撃、援護防御、MB発動(隣接確認)
	virtual bool    canBeSAttack();            //援護攻撃、MB発動
	virtual bool    canBeSDefence();           //援護防御
	virtual bool    canBeCounter();            //カウンター
	virtual bool    isActiveReverseStrength(); //底力(条件)
	virtual int64_t calcSPUp();                //SPアップ
	virtual int64_t calcHitStat();             //見切り(命中)
	virtual int64_t calcEvadeStat();           //見切り(回避)
	virtual int64_t calcMoraleOverdrive();     //気力限界突破
	virtual bool    canREAttack();         //再攻撃
	virtual bool    isFocusAttackAvailable();  //集束攻撃
	virtual bool    isHitAndAway();            //ヒットアンドアウェイ
	virtual int64_t calcIncrMoraleCond(DIncrMoraleCond pCond); //気力+、戦意高揚、闘争心
	virtual double  calcConsumeSPDecr();       //集中力
	virtual bool    canRepSupExtraAction();    //修理技能(HP回復量+20％)、補給技能(移動後使用可能)
	virtual bool    isLearning();              //ラーニング
	virtual bool    isBulletSave();            //Bセーブ
	virtual bool    isEnergySave();            //Eセーブ
};

class DPilotSkillDummy : DataPilotSkills {
protected:
	DPilotSkillDummy();
public:
	static DataPilotSkills* generateSkills();
};

