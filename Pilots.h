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

#include "all_loaders.h"
#include "ResourceLoader.h"
#include "strconv2.h"
#include "main.h"
#include "Parser.h"
#include "Units.h"
#include "UtilGameContents.h"
#include "json11.hpp"

using namespace std;
/* DROPBOX/JSON11 LIBRARIES */
using namespace json11;

namespace TREx {
	enum class EnumMagicalElement : uint64_t;
	enum class EnumTerrainAdaptionType : uint64_t;
	enum class EnumTerrainAdaptionRank : uint64_t;
	class JSONParser;

	enum class EnumGender : uint64_t;
	enum class EnumPilotPersonality : uint64_t;
	enum class EnumSpecies : uint64_t;
	enum class EnumPilotStatusInitials : uint64_t;
	enum class EnumSpecificSkills : int64_t;

	class DataSpecies;
	class SpecificSkill;
	class ActiveConditionSS;
	class DataSpiritualEffect;
	class DataPilot;
	class GamePilot;

	enum class EnumGender : uint64_t {
		/// <summary>
		/// 男性
		/// </summary>
		Male,
		/// <summary>
		/// 女性
		/// </summary>
		Female,
		/// <summary>
		/// 中性
		/// </summary>
		Neutral,
		/// <summary>
		/// 無性
		/// </summary>
		Asexual,
		/// <summary>
		/// 機械
		/// </summary>
		Machine
	};

	enum class EnumPilotPersonality : uint64_t {
		/// <summary>
		/// 性格：普通
		/// </summary>
		ordinary,
		/// <summary>
		/// 性格：強気
		/// </summary>
		strong,
		/// <summary>
		/// 性格：超強気
		/// </summary>
		very_strong,
		/// <summary>
		/// 性格：冷静
		/// </summary>
		calm,
		/// <summary>
		/// 性格：慎重
		/// </summary>
		cautious,
		/// <summary>
		/// 性格：楽天家
		/// </summary>
		optimist,
		/// <summary>
		/// 性格：努力家
		/// </summary>
		hardworking,
		/// <summary>
		/// 性格：短気
		/// </summary>
		quicktemper,
		/// <summary>
		/// 性格：大物
		/// </summary>
		bigwig,
		/// <summary>
		/// 性格：超大物
		/// </summary>
		very_bigwig,
		/// <summary>
		/// 性格：狡猾
		/// </summary>
		sly,
		/// <summary>
		/// 性格：残虐
		/// </summary>
		cruelty,
		/// <summary>
		/// 性格：機械
		/// </summary>
		machine
	};

	enum class EnumSpecies : uint64_t {
		/* -- SW2.5-FF14互換(ほかSW2.5ベース種族): PC種族 -- */
		/// <summary>
		/// 人間(ヒューラン:ミッドランダー相当)
		/// </summary>
		HumanMidlander,
		/// <summary>
		/// 人間(ヒューラン:ハイランダー相当)
		/// </summary>
		HumanHighlander,
		/// <summary>
		/// ヴァルキリー(ミッドランダー相当)
		/// </summary>
		HumanValkyrieNormalMidlander,
		/// <summary>
		/// ヴァルキリー(ハイランダー相当)
		/// </summary>
		HumanValkyrieNormalHighlander,
		/// <summary>
		/// ヴァルキリー(ノーブル現代種)
		/// </summary>
		HumanValkyrieNobleModern,
		/// <summary>
		/// ヴァルキリー(ノーブル古代種)
		/// </summary>
		HumanValkyrieNobleAncient,
		/// <summary>
		/// エルフ(エレゼン:フォレスター相当)
		/// </summary>
		ElvesForester,
		/// <summary>
		/// エルフ(エレゼン:シェーダー相当)
		/// </summary>
		ElvesShader,
		/// <summary>
		/// スノウエルフ(エレゼン:シェーダー相当)
		/// </summary>
		ElvesSnowed,
		/// <summary>
		/// ミストエルフ(エレゼン:フォレスター相当)
		/// </summary>
		ElvesMist,
		/// <summary>
		/// ノーブルエルフ(エレゼン:フォレスター相当)
		/// </summary>
		ElvesNobleForester,
		/// <summary>
		/// ノーブルエルフ(エレゼン:シェーダー相当)
		/// </summary>
		ElvesNobleShader,
		/// <summary>
		/// ドワーフ(通常)
		/// </summary>
		DwarfFire,
		/// <summary>
		/// ドワーフ(ダークドワーフ)
		/// </summary>
		DwarfDark,
		/// <summary>
		/// タビット(通常種)
		/// </summary>
		TabbitNormal,
		/// <summary>
		/// タビット(パイカ種)
		/// </summary>
		TabbitPica,
		/// <summary>
		/// タビット(リバス種)
		/// </summary>
		TabbitRivash,
		/// <summary>
		/// ルーンフォーク(通常種)
		/// </summary>
		RunefolkCommon,
		/// <summary>
		/// 魔動天使(※注:似たようなもんだからね)
		/// </summary>
		RunefolkMagitechAngel,
		/// <summary>
		/// 護衛型ルーンフォーク
		/// </summary>
		RunefolkDefender,
		/// <summary>
		/// 戦闘型ルーンフォーク
		/// </summary>
		RunefolkAttacker,
		/// <summary>
		/// ナイトメア(人間)
		/// </summary>
		NightmareHuman,
		/// <summary>
		/// ナイトメア(エルフ)
		/// </summary>
		NightmareElves,
		/// <summary>
		/// ナイトメア(ドワーフ)
		/// </summary>
		NightmareDwarf,
		/// <summary>
		/// ナイトメア(リルドラケン)
		/// </summary>
		NightmareLilidracken,
		/// <summary>
		/// ナイトメア(ソレイユ)
		/// </summary>
		NightmareSunbreaker,
		/// <summary>
		/// ナイトメア(シャドウ)
		/// </summary>
		NightmareShadow,
		/// <summary>
		/// リカント(通常種)
		/// </summary>
		LycanNormal,
		/// <summary>
		/// リカント(大型草食種)
		/// </summary>
		LycanLargerHerbivore,
		/// <summary>
		/// リカント(小型草食種)
		/// </summary>
		LycanSmallerHerbivore,
		/// <summary>
		/// リルドラケン(通常種)
		/// </summary>
		LilidrackenNormal,
		/// <summary>
		/// 小翼種リルドラケン
		/// </summary>
		LilidrackenSmallwing,
		/// <summary>
		/// 有毛種リルドラケン
		/// </summary>
		LilidrackenHairy,
		/// <summary>
		/// グラスランナー(通常種)
		/// </summary>
		GrassrunnerNormal,
		/// <summary>
		/// アリーシャグラスランナー
		/// </summary>
		GrassrunnerAlisha,
		/// <summary>
		/// クリメノスグラスランナー
		/// </summary>
		GrassrunnerClimenos,
		/// <summary>
		/// メリア(通常種)
		/// </summary>
		MeriaNormal,
		/// <summary>
		/// カーニバラスメリア
		/// </summary>
		MeriaCannibalistic,
		/// <summary>
		/// ファンギーメリア
		/// </summary>
		MeriaFungy,
		/// <summary>
		/// ティエンス(通常種)
		/// </summary>
		TienceNormal,
		/// <summary>
		/// ティエンス機解種
		/// </summary>
		TienceTechEasy,
		/// <summary>
		/// ティエンス魔解種
		/// </summary>
		TienceDemonEasy,
		/// <summary>
		/// レプラカーン(通常種)
		/// </summary>
		LeprechaunNormal,
		/// <summary>
		/// 放浪種レプラカーン
		/// </summary>
		LeprechaunVagrant,
		/// <summary>
		/// 探索種レプラカーン
		/// </summary>
		LeprechaunSearch,
		/// <summary>
		/// アルヴ
		/// </summary>
		Arve,
		/// <summary>
		/// シャドウ
		/// </summary>
		Shadow,
		/// <summary>
		/// ソレイユ
		/// </summary>
		Sunbreaker,
		/// <summary>
		/// スプリガン
		/// </summary>
		Spriggan,
		/// <summary>
		/// アビスボーン
		/// </summary>
		Abyssborne,
		/// <summary>
		/// ハイマン(ヒューラン:ミッドランダー相当)
		/// </summary>
		LittleHighHumanMidlander,
		/// <summary>
		/// ハイマン(ヒューラン:ハイランダー相当)
		/// </summary>
		LittleHighHumanHighlander,
		/// <summary>
		/// フロウライト
		/// </summary>
		Fluorite,
		/* -- FF14: PC種族 -- */
		/// <summary>
		/// ララフェル・プレーンフォーク
		/// </summary>
		LalafellPlainsfolk,
		/// <summary>
		/// ララフェル・デューンフォーク
		/// </summary>
		LalafellDunesfolk,
		/// <summary>
		/// ミコッテ・サンシーカー
		/// </summary>
		MiqoteSunseeker,
		/// <summary>
		/// ミコッテ・ムーンキーパー
		/// </summary>
		MiqoteMoonkeeper,
		/// <summary>
		/// ルガディン・ローエンガルデ
		/// </summary>
		RoegadynLohengarde,
		/// <summary>
		/// ルガディン・ゼーヴォルフ
		/// </summary>
		RoegadynSeewolf,
		/// <summary>
		/// アウラ・レン
		/// </summary>
		AuRaRaen,
		/// <summary>
		/// アウラ・ゼラ
		/// </summary>
		AuRaXaela,
		/// <summary>
		/// ラヴァ・ヴィエラ
		/// </summary>
		RavaViera,
		/// <summary>
		/// ヴィナ・ヴィエラ
		/// </summary>
		VeenaViera,
		/// <summary>
		/// ロスガル・へリオン
		/// </summary>
		HrothgarHelions,
		/// <summary>
		/// ロスガル・ロスト
		/// </summary>
		HrothgarTheLost,
		/* -- TREx独自: PC種族 -- */
		/// <summary>
		/// ミディール・ドラゴノイド
		/// </summary>
		DragonoidMidir,
		/// <summary>
		/// ミドガルズオルム・ドラゴノイド
		/// </summary>
		DragonoidMidgardsormr,
		/// <summary>
		/// [NPC専用]星の記録者
		/// </summary>
		Starlogger,
		/* -- SW2.5: 敵データ -- */
		/// <summary>
		/// [敵専用]蛮族
		/// </summary>
		Barbaroses,
		/// <summary>
		/// [敵専用]動物
		/// </summary>
		NatureBeasts,
		/// <summary>
		/// [敵専用]植物
		/// </summary>
		SoulAlignedPlants,
		/// <summary>
		/// [敵専用]アンデッド
		/// </summary>
		Undeads,
		/// <summary>
		/// [敵専用]魔法生物
		/// </summary>
		MagicalEntities,
		/// <summary>
		/// [敵専用]魔動機
		/// </summary>
		MagitechMachines,
		/// <summary>
		/// [敵専用]幻獣
		/// </summary>
		MysticBeasts,
		/// <summary>
		/// [敵専用]妖精
		/// </summary>
		Fae,
		/// <summary>
		/// [敵専用]魔神
		/// </summary>
		BorneFromTheAbyssos,
		/// <summary>
		/// [敵専用]人族
		/// </summary>
		MereMortal,
		/// <summary>
		/// [敵専用]神族
		/// </summary>
		MereDemigod,
		/* -- FF14: 敵データ -- */
		/// <summary>
		/// [敵専用]蛮神(疑似氷神除く)
		/// </summary>
		Primals,
		/* -- TREx独自: 敵データ -- */
		/// <summary>
		/// [疑似氷神も該当,敵専用]真実に近付いた者
		/// </summary>
		NearestTruth,
		/// <summary>
		/// [敵専用]その他
		/// </summary>
		Other = 0xffffffffffffffffui64
	};

	enum class EnumPilotStatusInitials : uint64_t {
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
		/// SP初期値ボーナス
		/// </summary>
		SPB
	};

	/// <summary>
	/// 特殊技能の一覧です。
	/// </summary>
	enum class EnumSpecificSkills : int64_t {
		/// <summary>
		/// 特殊技能:アタッカー
		/// </summary>
		Attacker,
		/// <summary>
		/// 特殊技能:インファイト
		/// </summary>
		InFight,
		/// <summary>
		/// 特殊技能:ガンファイト
		/// </summary>
		GunFight,
		/// <summary>
		/// 特殊技能:メイジファイト
		/// </summary>
		MageFight,
		/// <summary>
		/// 特殊技能:強運
		/// </summary>
		HigherResult,
		/// <summary>
		/// 特殊技能:指揮官
		/// </summary>
		Commander,
		/// <summary>
		/// 特殊技能:天才
		/// </summary>
		Genius,
		/// <summary>
		/// 特殊技能:念動力
		/// </summary>
		Psychokinesis,
		/// <summary>
		/// 特殊技能:予知
		/// </summary>
		Prediction,
		/// <summary>
		/// 特殊技能:ラッキー
		/// </summary>
		Lucky,
		/// <summary>
		/// 特殊技能:SP回復
		/// </summary>
		SPRegeneration,
		/// <summary>
		/// 特殊技能:援護攻撃
		/// </summary>
		SupportAttack,
		/// <summary>
		/// 特殊技能:援護防御
		/// </summary>
		CoveringGuard,
		/// <summary>
		/// 特殊技能:カウンター
		/// </summary>
		Counterattack,
		/// <summary>
		/// 特殊技能:連続攻撃
		/// </summary>
		AttackInSuccession,
		/// <summary>
		/// 特殊技能:底力
		/// </summary>
		Potentiality,
		/// <summary>
		/// 特殊技能:SPアップ
		/// </summary>
		SPCapacityUp,
		/// <summary>
		/// 特殊技能:ガード
		/// </summary>
		Guard,
		/// <summary>
		/// 特殊技能:見切り
		/// </summary>
		Forsaken,
		/// <summary>
		/// 特殊技能:気力限界突破
		/// </summary>
		SpiritualLimitBreakthrough,
		/// <summary>
		/// 特殊技能:再攻撃
		/// </summary>
		ReAttack,
		/// <summary>
		/// 特殊技能:集束攻撃
		/// </summary>
		FocusedAttack,
		/// <summary>
		/// 特殊技能:ヒット＆アウェイ
		/// </summary>
		HitAndAway,
		/// <summary>
		/// 特殊技能:リベンジ
		/// </summary>
		Revenge,
		/// <summary>
		/// 特殊技能:連携攻撃
		/// </summary>
		CoordinatedAttack,
		/// <summary>
		/// 特殊技能:連続行動
		/// </summary>
		ActionInSuccession,
		/// <summary>
		/// 特殊技能:MB発動
		/// </summary>
		ActivatableMaximumBreak,
		/// <summary>
		/// 特殊技能:気力+(回避)
		/// </summary>
		IncreaseSpiritWhenEvasion,
		/// <summary>
		/// 特殊技能:気力+(撃破)
		/// </summary>
		IncreaseSpiritWhenDestruction,
		/// <summary>
		/// 特殊技能:気力+(ダメージ)
		/// </summary>
		IncreaseSpiritWhenInjured,
		/// <summary>
		/// 特殊技能:気力+(命中)
		/// </summary>
		IncreaseSpiritWhenSuccessAttack,
		/// <summary>
		/// 特殊技能:気力+(ALL)
		/// </summary>
		IncreaseSpiritWhenAllConditions,
		/// <summary>
		/// 特殊技能:戦意高揚
		/// </summary>
		IncreaseWill,
		/// <summary>
		/// 特殊技能:闘争心
		/// </summary>
		Belligerence,
		/// <summary>
		/// 特殊技能:集中力
		/// </summary>
		KeepConcentration,
		/// <summary>
		/// 特殊技能:治癒技能(SRWにおける「修理技能」に相当)
		/// </summary>
		Healing,
		/// <summary>
		/// 特殊技能:補給技能
		/// </summary>
		Supplying,
		/// <summary>
		/// 特殊技能:ラーニング
		/// </summary>
		Learning,
		/// <summary>
		/// 特殊技能:Bセーブ
		/// </summary>
		BulletSave,
		/// <summary>
		/// 特殊技能:Eセーブ
		/// </summary>
		EnergySave,
		/// <summary>
		/// 特殊技能:EXPアップ
		/// </summary>
		AdvancedExperience,
		/// <summary>
		/// 特殊技能:デュナミスの高揚(特殊技能)
		/// </summary>
		QuickeningDynamis,
		/// <summary>
		/// 特殊技能:タンクマスタリー
		/// </summary>
		TankMastery,
		/// <summary>
		/// 特殊技能:ヒーラーマスタリー
		/// </summary>
		HealerMastery,
		/// <summary>
		/// 種族特徴:運命変転[人間]
		/// </summary>
		SpeciesTwistOfFate,
		/// <summary>
		/// 種族特徴:暗視[汎用]
		/// </summary>
		SpeciesNightVision,
		/// <summary>
		/// 種族特徴:優しき水[汎エルフ]
		/// </summary>
		SpeciesGentleWater,
		/// <summary>
		/// 種族特徴:厳つき氷[雪エルフ]
		/// </summary>
		SpeciesSeverityIce,
		/// <summary>
		/// 種族特徴:惑いの霧[霧エルフ]
		/// </summary>
		SpeciesMistOfConfusion,
		/// <summary>
		/// 種族特徴:炎身[ドワーフ]
		/// </summary>
		SpeciesBlazingBody,
		/// <summary>
		/// 種族特徴:第六感[タビット]
		/// </summary>
		SpeciesSixthSence,
		/// <summary>
		/// 種族特徴:ホイッスル[パイカタビット]
		/// </summary>
		SpeciesWhistle,
		/// <summary>
		/// 種族特徴:HP変換[ルンフォ]
		/// </summary>
		SpeciesHPConvert,
		/// <summary>
		/// 種族特徴:仲間との絆[護衛ルンフォ]
		/// </summary>
		SpeciesPowerOfFerrows,
		/// <summary>
		/// 種族特徴:任務遂行の意志[戦闘ルンフォ]
		/// </summary>
		SpeciesWillToDuty,
		/// <summary>
		/// 種族特徴:異貌[ナイトメア]
		/// </summary>
		SpeciesAnotherForm,
		/// <summary>
		/// 種族特徴:弱点[ナイトメア]
		/// </summary>
		SpeciesWeakPoint,
		/// <summary>
		/// 種族特徴:獣変貌[リカント]
		/// </summary>
		SpeciesBeastForm,
		/// <summary>
		/// 種族特徴:獣変貌（大型草食獣）[大型草食種リカント]
		/// </summary>
		SpeciesLargerHerbivoreBeastForm,
		/// <summary>
		/// 種族特徴:獣変貌（小型草食獣）[小型草食種リカント]
		/// </summary>
		SpeciesSmallerHerbivoreBeastForm,
		/// <summary>
		/// 種族特徴:鱗の皮膚[リルドラケン]
		/// </summary>
		SpeciesScaleSkin,
		/// <summary>
		/// 種族特徴:風の翼[リルドラケン]
		/// </summary>
		SpeciesWindWings,
		/// <summary>
		/// 種族特徴:竜の咆哮[小翼種リルドラケン]
		/// </summary>
		SpeciesWyrmRoar,
		/// <summary>
		/// 種族特徴:暖かき風[有毛種リルドラケン]
		/// </summary>
		SpeciesFriendlyWind,
		/// <summary>
		/// 種族特徴:マナ不干渉[グラスランナー]
		/// </summary>
		SpeciesNoninterfaceAether,
		/// <summary>
		/// 種族特徴:虫や植物との意思疎通[グラスランナー]
		/// </summary>
		SpeciesForeboding,
		/// <summary>
		/// 種族特徴:繁茂する生命[メリア]
		/// </summary>
		SpeciesLifeThriving,
		/// <summary>
		/// 種族特徴:捕食する生命[カーニバラスメリア]
		/// </summary>
		SpeciesPredatoryLife,
		/// <summary>
		/// 種族特徴:胞子散布[ファンギーメリア]
		/// </summary>
		SpeciesSporulation,
		/// <summary>
		/// 種族特徴:通じ合う意識[ティエンス]
		/// </summary>
		SpeciesCommunicationSense,
		/// <summary>
		/// 種族特徴:無生物と通じ合う意識[ティエンス機解種]
		/// </summary>
		SpeciesCommunicationSenseInanimationMatter,
		/// <summary>
		/// 種族特徴:魔神と通じ合う意識[ティエンス魔解種]
		/// </summary>
		SpeciesCommunicationSenseBorneFromTheAbyssos,
		/// <summary>
		/// 種族特徴:姿なき職人[レプラカーン]
		/// </summary>
		SpeciesInvisibleArtisan,
		/// <summary>
		/// 種族特徴:姿消す職人[放浪種レプラカーン]
		/// </summary>
		SpeciesDisappearingArtisan,
		/// <summary>
		/// 種族特徴:群れなす職人[探索種レプラカーン]
		/// </summary>
		SpeciesSwarmingArtisan,
		/// <summary>
		/// 種族特徴:吸精[アルヴ]
		/// </summary>
		SpeciesAbsorption,
		/// <summary>
		/// 種族特徴:月光の守り[シャドウ]
		/// </summary>
		SpeciesDedicatedToMoonlight, //意味は「月満ちる夜 ～喜びの神域 エウプロシュネ～」
		/// <summary>
		/// 種族特徴:輝く肉体[ソレイユ]
		/// </summary>
		SpeciesRadiantBody,
		/// <summary>
		/// 種族特徴:太陽の再生[ソレイユ]
		/// </summary>
		SpeciesSunRegeneration,
		/// <summary>
		/// 種族特徴:太陽の子[ソレイユ]
		/// </summary>
		SpeciesInTheBalance, //意味は「命の天秤 ～輝ける神域 アグライア～」
		/// <summary>
		/// 種族特徴:巨人化[スプリガン]
		/// </summary>
		SpeciesMegalomania,
		/// <summary>
		/// 種族特徴:奈落の落とし子／アビストランク[アビスボーン]
		/// </summary>
		SpeciesAbyssalBastardAbyssTrunk,
		/// <summary>
		/// 種族特徴:奈落の落とし子／アビスアーム[アビスボーン]
		/// </summary>
		SpeciesAbyssalBastardAbyssArm,
		/// <summary>
		/// 種族特徴:奈落の落とし子／アビスアイ[アビスボーン]
		/// </summary>
		SpeciesAbyssalBastardAbyssEye,
		/// <summary>
		/// 種族特徴:魔法の申し子[ハイマン]
		/// </summary>
		SpeciesMagicChildren,
		/// <summary>
		/// 種族特徴:デジャヴ[ハイマン]
		/// </summary>
		SpeciesPseudoEcho, //「超える力もどき」の意
		/// <summary>
		/// 種族特徴:魂の輝き[フロウライト]
		/// </summary>
		SpeciesSoulLight,
		/// <summary>
		/// 種族特徴:鉱石の生命[フロウライト]
		/// </summary>
		SpeciesOreLife,
		/// <summary>
		/// 種族特徴:黒炎の遣い手[ダークドワーフ]
		/// </summary>
		SpeciesBlackflameMastery,
		/// <summary>
		/// 種族特徴:戦乙女の光羽[汎ヴァルキリー／貴ヴァルキリー共通]
		/// </summary>
		SpeciesValkyrieLightWings,
		/// <summary>
		/// 種族特徴:戦乙女の祝福[汎ヴァルキリー／貴ヴァルキリー共通]
		/// </summary>
		SpeciesValkyrieBlessing,
		/// <summary>
		/// 種族特徴:重力の祝福[貴ヴァルキリー]
		/// </summary>
		SpeciesGravitationalBlessing,
		/// <summary>
		/// 種族特徴:血の刃[貴ヴァルキリー]
		/// </summary>
		SpeciesBladeOfBlood,
		/// <summary>
		/// 種族特徴:水の申し子[貴エルフ]
		/// </summary>
		SpeciesWaterDependents,
		/// <summary>
		/// 種族特徴:カリスマ[貴エルフ]
		/// </summary>
		SpeciesCharism,
		/// <summary>
		/// 種族特徴:皮膚装甲[オプション]
		/// </summary>
		SpeciesArmorySkin,
		/// <summary>
		/// 種族特徴:濃いエーテル[オプション]
		/// </summary>
		DenseAether,
	};
	/// <summary>
	/// 種族データの定義です。
	/// </summary>
	class DataSpecies {
	protected:
		/* -- 変数系 -- */
		/// <summary>
		/// 種族に関わる大まかな分類です。
		/// </summary>
		EnumSpecies speciesAbout;
		/// <summary>
		/// 種族別の基礎ステータスになります。
		/// </summary>
		map<EnumPilotStatusInitials, int64_t> speciesBaselineStatus;
		/// <summary>
		/// <para>穢れの値です。大まかな目安は以下の通りです。</para>
		/// <para>人族: 0～1</para>
		/// <para>FF14種族: 1～2</para>
		/// <para>蛮族: 1以上5未満</para>
		/// <para>アンデッド: 5</para>
		/// <para>星の記録者: -1</para>
		/// <para>その他: 基本0</para>
		/// </summary>
		int64_t speciesDisgrace;
		/// <summary>
		/// 種族特徴です。特殊技能としてカウントされます。
		/// </summary>
		vector<SpecificSkill*> speciesSpecificSkills;
		/* -- 関数系 -- */
		/// <summary>
		/// 基礎ステータスを定義します。
		/// </summary>
		void setBaselineStatus();
		/// <summary>
		/// 種族特徴を定義します。
		/// </summary>
		void setSpecificSkills();
	public:
		/// <summary>
		/// 種族の概要を上位クラスへ返却する関数です。
		/// </summary>
		/// <returns>種族概要(列挙型)</returns>
		EnumSpecies getSpeciesAbout() const {
			return this->speciesAbout;
		}
		/// <summary>
		/// 種族別の基礎ステータスを上位クラスへ返却する関数です。
		/// </summary>
		/// <returns>種族別の基礎ステータス</returns>
		map<EnumPilotStatusInitials, int64_t> getSpeciesBaselineStatus() const {
			return this->speciesBaselineStatus;
		}
		/// <summary>
		/// 種族別の基礎『穢れ』値を上位クラスへ返却する関数です。
		/// </summary>
		/// <returns>基礎『穢れ』値</returns>
		int64_t getSpeciesDisgrace() const {
			return this->speciesDisgrace;
		}
		/// <summary>
		/// 種族別の種族特徴（特殊技能）を上位クラスへ返却する関数です。
		/// </summary>
		/// <returns></returns>
		vector<SpecificSkill*> getSpeciesSpecificSkills() const {
			return this->speciesSpecificSkills;
		}
		/// <summary>
		/// 種族クラスのコンストラクタ
		/// </summary>
		/// <param name="specJson">JSON形式の種族データ</param>
		DataSpecies(Json specJson);
		/// <summary>
		/// 種族クラスのコピーコンストラクタ
		/// </summary>
		/// <param name="from">コピー元</param>
		DataSpecies(const DataSpecies* from);
	};

	inline void DataSpecies::setBaselineStatus() {
		/*
		* ステータスの割り振りについて
		* 穢れ0の場合に、合計値が1320になるように割り振る。
		* 穢れ持ちは基本合計値に+（穢れ×90、各ステ+穢れx10）。
		* 戦闘用ルーンフォークは穢れ+2相当、アルヴは穢れ-2相当。
		* FF14種族はハイデリンキックのせいで穢れ+1、特にアウラは+2として勘定。
		* 星の記録者は穢れが-1になる。
		*/
		//基本的なステータスの値はこの通りになる。
		this->speciesDisgrace = 0LL;
		this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
			{ EnumPilotStatusInitials::MEL, 140LL },
			{ EnumPilotStatusInitials::RNG, 140LL },
			{ EnumPilotStatusInitials::MGC, 140LL },
			{ EnumPilotStatusInitials::DEX, 170LL },
			{ EnumPilotStatusInitials::DEF, 130LL },
			{ EnumPilotStatusInitials::ACU, 180LL },
			{ EnumPilotStatusInitials::AVD, 180LL },
			{ EnumPilotStatusInitials::RIT, 180LL },
			{ EnumPilotStatusInitials::SPB, 60LL }
		};

		switch (this->speciesAbout) {
			/*
			* 人間ミドラン: ベース値。つまり「ニューター」。
			*/
		case EnumSpecies::HumanMidlander:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 0LL;
		}
		break;
		/*
		* 人間ハイラン: MEL+10, RNG-20, MGC-20, DEX=DEF, DEF+20, ACU+10, AVD-10, RIT+5, SPB+5
		*/
		case EnumSpecies::HumanHighlander:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 5LL;
		}
		break;
		/*
		* 汎ヴァルミドラン: MEL+5, RNG-10, MGC+10, DEX+5, DEF-10, ACU+5, AVD+5, RIT-20, SPB+10
		*/
		case EnumSpecies::HumanValkyrieNormalMidlander:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 10LL;
		}
		break;
		/*
		* 汎ヴァルハイラン: MEL+15, RNG-30, MGC-10, DEX+5, DEF+10, ACU+15, AVD-5, RIT-15, SPB+15
		*/
		case EnumSpecies::HumanValkyrieNormalHighlander:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 15LL;
		}
		break;
		/*
		* 貴ヴァルモダンブランチ: MEL+5, RNG-20, MGC+10, DEX+5, DEF+10, ACU+5, AVD-15, RIT-15, SPB+15
		*/
		case EnumSpecies::HumanValkyrieNobleModern:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 15LL;
		}
		break;
		/*
		* 貴ヴァルオールドブランチ: MEL-25, RNG+25, MGC+5, DEX-5, DEF-10, ACU+25, AVD-15, RIT-15, SPB+15
		*/
		case EnumSpecies::HumanValkyrieNobleAncient:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 15LL;
		}
		break;
		/*
		* 汎エルフフォレスター: MEL-10, RNG+10, MGC+10, DEX+5, DEF-5, ACU=DEF, AVD-5, RIT-5, SPB=DEF
		*/
		case EnumSpecies::ElvesForester:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 0LL;
		}
		break;
		/*
		* 汎エルフシェーダー: MEL-10, RNG=DEF, MGC+20, DEX+10, DEF-5, ACU=DEF, AVD-5, RIT-10, SPB=DEF
		*/
		case EnumSpecies::ElvesShader:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 0LL;
		}
		break;
		/*
		* 貴エルフフォレスター: MEL-30, RNG-10, MGC+60, DEX+15, DEF-30, ACU=DEF, AVD-5, RIT+5, SPB-5
		*/
		case EnumSpecies::ElvesNobleForester:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 60LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 5LL;
		}
		break;
		/*
		* 貴エルフフォレスター: MEL-30, RNG-20, MGC+75, DEX+30, DEF-50, ACU=DEF, AVD-5, RIT+10, SPB-10
		*/
		case EnumSpecies::ElvesNobleShader:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 75LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 50LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 10LL;
		}
		break;
		/*
		* 霧エルフ: MEL-20, RNG+10, MGC+10, DEX+5, DEF=DEF, ACU-5, AVD-5, RIT-5, SPB+10
		*/
		case EnumSpecies::ElvesMist:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 10LL;
		}
		break;
		/*
		* 雪エルフ: MEL-20, RNG=DEF, MGC+20, DEX+10, DEF=DEF, ACU-5, AVD-5, RIT-10, SPB+15
		*/
		case EnumSpecies::ElvesSnowed:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 15LL;
		}
		break;
		/*
		* ドワーフ: MEL+10, RNG-10, MGC-10, DEX-5, DEF+25, ACU-5, AVD-5, RIT+10, SPB-5
		*/
		case EnumSpecies::DwarfFire:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 5LL;
		}
		break;
		/*
		* ダークドワーフ: MEL+15, RNG-10, MGC-15, DEX-5, DEF+25, ACU-5, AVD-5, RIT+5, SPB=DEF
		*/
		case EnumSpecies::DwarfDark:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 0LL;
		}
		break;
		/*
		* タビット通常種: MEL-40, RNG-40, MGC+60, DEX-10, DEF-5, ACU-5, AVD+10, RIT+15, SPB+15
		*/
		case EnumSpecies::TabbitNormal:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 60LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 15LL;
		}
		break;
		/*
		* タビットパイカ種: MEL-40, RNG-40, MGC+50, DEX+10, DEF-5, ACU-10, AVD+10, RIT+10, SPB+15
		*/
		case EnumSpecies::TabbitPica:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 50LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 15LL;
		}
		break;
		/*
		* タビットリバス種: MEL-40, RNG-40, MGC+40, DEX-20, DEF-5, ACU+20, AVD+20, RIT+10, SPB+15
		*/
		case EnumSpecies::TabbitRivash:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 15LL;
		}
		break;
		/*
		* ルーンフォーク通常ロット: MEL-5, RNG-5, MGC+5, DEX+5, DEF+10, ACU-10, AVD-10, RIT+5, SPB+5
		*/
		case EnumSpecies::RunefolkCommon:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 5LL;
		}
		break;
		/*
		* 魔動天使: MEL+30, RNG+30, MGC-15, DEX+15, DEF-25, ACU+20, AVD-35, RIT+5, SPB-25
		*/
		case EnumSpecies::RunefolkMagitechAngel:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 25LL;
		}
		break;
		/*
		* 護衛型ルーンフォーク: MEL-25, RNG-25, MGC-25, DEX+25, DEF+50, ACU-15, AVD-15, RIT+20, SPB+10
		*/
		case EnumSpecies::RunefolkDefender:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 50LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 10LL;
		}
		break;
		/*
		* 戦闘型ルーンフォーク: MEL+40, RNG+40, MGC+30, DEX-30, DEF-50, ACU+30, AVD-20, RIT-20, SPB-20
		*/
		case EnumSpecies::RunefolkAttacker:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 50LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 20LL;
		}
		break;
		/*
		* ナイトメア: 全小分類共通で「MEL+10, RNG+10, MGC+10, DEX-15, DEF-20, ACU+5, AVD-20, RIT-10, SPB+30」
		*/
		case EnumSpecies::NightmareHuman:
		case EnumSpecies::NightmareElves:
		case EnumSpecies::NightmareDwarf:
		case EnumSpecies::NightmareLilidracken:
		case EnumSpecies::NightmareSunbreaker:
		case EnumSpecies::NightmareShadow:
		{
			this->speciesDisgrace = 1LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 30LL;
		}
		break;
		/*
		* リカント通常種: MEL+5, RNG+5, MGC-10, DEX+10, DEF+10, ACU+5, AVD-5, RIT-10, SPB-10
		*/
		case EnumSpecies::LycanNormal:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 10LL;
		}
		break;
		/*
		* リカント大型草食種: MEL+15, RNG+15, MGC-30, DEX+30, DEF+30, ACU+15, AVD-45, RIT-15, SPB-15
		*/
		case EnumSpecies::LycanLargerHerbivore:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 45LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 15LL;
		}
		break;
		/*
		* リカント小型草食種: MEL-5, RNG-5, MGC+10, DEX-10, DEF-10, ACU+5, AVD+10, RIT-15, SPB+20
		*/
		case EnumSpecies::LycanSmallerHerbivore:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 20LL;
		}
		break;
		/*
		* リルドラケン通常種: MEL+35, RNG+10, MGC-25, DEX-10, DEF+30, ACU-20, AVD-25, RIT-15, SPB+20
		*/
		case EnumSpecies::LilidrackenNormal:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 20LL;
		}
		break;
		/*
		* リルドラケン小翼種: MEL+45, RNG+10, MGC-35, DEX-10, DEF+30, ACU-20, AVD-30, RIT-10, SPB+20
		*/
		case EnumSpecies::LilidrackenSmallwing:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 45LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 20LL;
		}
		break;
		/*
		* リルドラケン有翼種: MEL+20, RNG+15, MGC-5, DEX+10, DEF+50, ACU+10, AVD-75, RIT+5, SPB-30
		*/
		case EnumSpecies::LilidrackenHairy:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 50LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 75LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 30LL;
		}
		break;
		/*
		* グラスランナー通常種: MEL-20, RNG-20, MGC-40, DEX+30, DEF-40, ACU+30, AVD+30, RIT+15, SPB+15
		*/
		case EnumSpecies::GrassrunnerNormal:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 15LL;
		}
		break;
		/*
		* アリーシャグラスランナー: MEL-25, RNG-25, MGC-40, DEX+30, DEF-40, ACU+35, AVD+35, RIT+15, SPB+15
		*/
		case EnumSpecies::GrassrunnerAlisha:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 15LL;
		}
		break;
		/*
		* クリメノスグラスランナー: MEL-25, RNG-25, MGC-50, DEX+40, DEF-40, ACU+35, AVD+35, RIT+10, SPB+20
		*/
		case EnumSpecies::GrassrunnerClimenos:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 50LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 20LL;
		}
		break;
		/*
		* メリア通常種: MEL-20, RNG-10, MGC+45, DEX+15, DEF-10, ACU+20, AVD+10, RIT-25, SPB-25
		*/
		case EnumSpecies::MeriaNormal:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 45LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 25LL;
		}
		break;
		/*
		* カーニバラスメリア: MEL-15, RNG-15, MGC+40, DEX+20, DEF-20, ACU+15, AVD+15, RIT-25, SPB-15
		*/
		case EnumSpecies::MeriaCannibalistic:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 15LL;
		}
		break;
		/*
		* ファンギーメリア: MEL-25, RNG-5, MGC+35, DEX+25, DEF-30, ACU+10, AVD+30, RIT-35, SPB-5
		*/
		case EnumSpecies::MeriaFungy:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 5LL;
		}
		break;
		/*
		* ティエンス通常種: MEL+10, RNG+10, MGC-10, DEX+5, DEF+5, ACU+5, AVD+5, RIT-10, SPB-20
		*/
		case EnumSpecies::TienceNormal:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 20LL;
		}
		break;
		/*
		* ティエンス機解種: MEL-10, RNG+20, MGC-10, DEX+5, DEF+5, ACU+10, AVD-10, RIT-15, SPB+5
		*/
		case EnumSpecies::TienceTechEasy:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 5LL;
		}
		break;
		/*
		* ティエンス魔解種: MEL-10, RNG-10, MGC+30, DEX-20, DEF-10, ACU+15, AVD+15, RIT-30, SPB+20
		*/
		case EnumSpecies::TienceDemonEasy:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 20LL;
		}
		break;
		/*
		* レプラカーン通常種: MEL-40, RNG+20, MGC+20, DEX+10, DEF-10, ACU+10, AVD+10, RIT+10, SPB-30
		*/
		case EnumSpecies::LeprechaunNormal:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 30LL;
		}
		break;
		/*
		* レプラカーン放浪種: MEL-40, RNG+20, MGC+20, DEX+10, DEF-10, ACU+5, AVD+15, RIT+10, SPB-30
		*/
		case EnumSpecies::LeprechaunVagrant:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 30LL;
		}
		break;
		/*
		* レプラカーン探索種: MEL-20, RNG+20, RNG+20, DEX-10, DEF-10, ACU+10, AVD+10, RIT-30, SPB+10
		*/
		case EnumSpecies::LeprechaunSearch:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 10LL;
		}
		break;
		/*
		* アルヴ: MEL-10, RNG-10, MGC+30, DEX-10, DEF-10, ACU-40, AVD-40, RIT+45, SPB+45
		*/
		case EnumSpecies::Arve:
		{
			this->speciesDisgrace = 1LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 45LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 45LL;
		}
		break;
		/*
		* シャドウ: MEL+5, RNG+5, MGC+5, DEX-30, DEF+5, ACU-30, AVD+10, RIT+10, SPB+20
		*/
		case EnumSpecies::Shadow:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 20LL;
		}
		break;
		/*
		* ソレイユ: MEL+20, RNG+20, MGC-40, DEX+10, DEF-10, ACU+20, AVD-20, RIT-20, SPB+20
		*/
		case EnumSpecies::Sunbreaker:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 20LL;
		}
		break;
		/*
		* スプリガン: MEL+10, RNG+10, MGC+10, DEX-30, DEF+30, ACU+10, AVD-25, RIT+10, SPB-25
		*/
		case EnumSpecies::Spriggan:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 25LL;
		}
		break;
		/*
		* アビスボーン: MEL+20, RNG+20, MGC+40, DEX-20, DEF+10, ACU-30, AVD-30, RIT-30, SPB+20
		*/
		case EnumSpecies::Abyssborne:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 20LL;
		}
		break;
		/*
		* ハイマンミドラン: MEL-40, RNG-40, MGC+40, DEX-30, DEF-30, ACU+30, AVD+30, RIT=DEF, SPB+40
		*/
		case EnumSpecies::LittleHighHumanMidlander:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 40LL;
		}
		break;
		/*
		* ハイマンハイラン: MEL-30, RNG-60, MGC+20, DEX-30, DEF-10, ACU+40, AVD+20, RIT+5, SPB+45
		*/
		case EnumSpecies::LittleHighHumanHighlander:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 60LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 45LL;
		}
		break;
		/*
		* フロウライト: MEL+20, RNG+20, MGC+20, DEX-10, DEF+50, ACU-25, AVD-25, RIT-30, SPB-20
		*/
		case EnumSpecies::Fluorite:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 50LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 20LL;
		}
		break;
		/*
		* ララフェルプレーンフォーク: MEL-40, RNG+30, MGC+20, DEX+20, DEF-20, ACU=DEF, AVD+10, RIT-20, SPB=DEF
		*/
		case EnumSpecies::LalafellPlainsfolk:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 0LL;
		}
		break;
		/*
		* ララフェルデューンフォーク: MEL-40, RNG+10, MGC+20, DEX=DEF, DEF-20, ACU+20, AVD+10, RIT-20, SPB+20
		*/
		case EnumSpecies::LalafellDunesfolk:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 20LL;
		}
		break;
		/*
		* ミコッテサンシーカー: MEL+40, RNG-20, MGC-15, DEX+40, DEF-10, ACU-15, AVD-30, RIT-10, SPB+20
		*/
		case EnumSpecies::MiqoteSunseeker:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 20LL;
		}
		break;
		/*
		* ミコッテムーンキーパー: MEL-15, RNG-20, MGC+40, DEX+40, DEF-10, ACU-30, AVD-15, RIT-10, SPB+20
		*/
		case EnumSpecies::MiqoteMoonkeeper:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 20LL;
		}
		break;
		/*
		* ルガディンローエンガルデ: MEL+15, RNG-10, MGC-10, DEX+15, DEF+25, ACU-15, AVD-15, RIT+25, SPB-30
		*/
		case EnumSpecies::RoegadynLohengarde:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 30LL;
		}
		break;
		/*
		* ルガディンゼーヴォルフ: MEL+25, RNG-10, MGC-10, DEX-5, DEF+25, ACU-5, AVD-15, RIT+25, SPB-30
		*/
		case EnumSpecies::RoegadynSeewolf:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 30LL;
		}
		break;
		/*
		* アウラ・レン: MEL+5, RNG+5, MGC+5, DEX+5, DEF-15, ACU+10, AVD+10, RIT-35, SPB+10
		*/
		case EnumSpecies::AuRaRaen:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 10LL;
		}
		break;
		/*
		* アウラ・ゼラ: MEL+20, RNG+5, MGC+5, DEX-25, DEF-15, ACU+10, AVD+10, RIT-20, SPB+10
		*/
		case EnumSpecies::AuRaXaela:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 10LL;
		}
		break;
		/*
		* ラヴァ・ヴィエラ: MEL-15, RNG+30, MGC+15, DEX+30, DEF-30, ACU+15, AVD-15, RIT-20, SPB-10
		*/
		case EnumSpecies::RavaViera:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 10LL;
		}
		break;
		/*
		* ヴィナ・ヴィエラ: MEL-15, RNG+20, MGC+40, DEX+15, DEF-20, ACU-5, AVD-15, RIT-10, SPB-20
		*/
		case EnumSpecies::VeenaViera:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 20LL;
		}
		break;
		/*
		* ロスガル（ヘリオン／ロスト）: MEL+60, RNG+30, MGC-45, DEX-60, DEF+60, ACU-30, AVD-15, RIT+10, SPB-10
		*/
		case EnumSpecies::HrothgarHelions:
		case EnumSpecies::HrothgarTheLost:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 0LL;
		}
		break;
		/*
		* ミディール・ドラゴノイド: MEL+30, RNG+30, MGC+15, DEX-30, DEF-15, ACU-15, AVD-10, RIT-35, SPB+30
		*/
		case EnumSpecies::DragonoidMidir:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 0LL;
		}
		break;
		/*
		* ミドガルズオルム・ドラゴノイド: MEL+30, RNG+15, MGC+30, DEX+15, DEF-60, ACU-15, AVD-10, RIT-35, SPB+30
		*/
		case EnumSpecies::DragonoidMidgardsormr:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 60LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 35LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 30LL;
		}
		break;
		/*
		* 星の記録者: MEL-25, RNG-25, MGC-10, DEX+50, DEF+30, ACU-20, AVD-20, RIT-20, SPB+40
		*/
		case EnumSpecies::Starlogger:
		{
			this->speciesDisgrace = -1LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 25LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 50LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 40LL;
		}
		break;
		/*
		* 蛮族（敵）
		*/
		case EnumSpecies::Barbaroses:
		{
			this->speciesDisgrace = 2LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 10LL;
		}
		break;
		/*
		* 動物（敵）
		*/
		case EnumSpecies::NatureBeasts:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 90LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 30LL;
		}
		break;
		/*
		* 植物（敵）
		*/
		case EnumSpecies::SoulAlignedPlants:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 20LL;
		}
		break;
		/*
		* アンデッド（敵）: 基本的なステータスは人間ミッドランダーと相違ない
		*/
		case EnumSpecies::Undeads:
		{
			this->speciesDisgrace = 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 0LL;
		}
		break;
		/*
		* 魔法生物（敵）
		*/
		case EnumSpecies::MagicalEntities:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 60LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 45LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 45LL;
		}
		break;
		/*
		* 魔動機（敵）
		*/
		case EnumSpecies::MagitechMachines:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 10LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 5LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 5LL;
		}
		break;
		/*
		* 幻獣（敵）
		*/
		case EnumSpecies::MysticBeasts:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] -= 15LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] -= 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 5LL;
		}
		break;
		/*
		* 妖精（敵）: 変化なし
		*/
		case EnumSpecies::Fae:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 0LL;
		}
		break;
		/*
		* 魔神（敵）: 全面的プラス補正
		*/
		case EnumSpecies::BorneFromTheAbyssos:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 60LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 60LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 30LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 60LL;
		}
		break;
		/*
		* 人族（敵）: 基本的にはPCの「人間ミッドランダー」と同じ
		*/
		case EnumSpecies::MereMortal:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] += 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 0LL;
		}
		break;
		/*
		* 神族（敵）
		*/
		case EnumSpecies::MereDemigod:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 40LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 80LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] += 0LL;
		}
		break;
		/*
		* 蛮神（敵）
		*/
		case EnumSpecies::Primals:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 45LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 45LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 45LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 45LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 45LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 45LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 40LL;
		}
		break;
		/*
		* 真実に近付いた者（敵）
		*/
		case EnumSpecies::NearestTruth:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] += 90LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] += 90LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] += 90LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] -= 90LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] -= 90LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] += 20LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] -= 90LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] -= 40LL;
		}
		break;
		/*
		* その他（敵）: ゼロ初期化
		*/
		case EnumSpecies::Other:
		{
			this->speciesBaselineStatus[EnumPilotStatusInitials::MEL] = 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RNG] = 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::MGC] = 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEX] = 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::DEF] = 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::ACU] = 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::AVD] = 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::RIT] = 0LL;
			this->speciesBaselineStatus[EnumPilotStatusInitials::SPB] = 0LL;
		}
		break;
		}

		for (auto iter = begin(this->speciesBaselineStatus); iter != end(this->speciesBaselineStatus); iter++) {
			const auto& target = *iter;
			//アルヴは実数値+1に対して穢れ-2相当とする
			if (this->speciesAbout == EnumSpecies::Arve) {
				this->speciesBaselineStatus[target.first] -= 20LL;
				continue;
			}
			this->speciesBaselineStatus[target.first] += this->speciesDisgrace * 10LL;
			//戦闘型ルンフォは穢れ+2相当とする
			if (this->speciesAbout == EnumSpecies::RunefolkAttacker) this->speciesBaselineStatus[target.first] += 20LL;
			//FF14種族は穢れ+1～2（アウラ）相当とする
			if (this->speciesAbout == EnumSpecies::LalafellPlainsfolk || this->speciesAbout == EnumSpecies::LalafellDunesfolk ||
					this->speciesAbout == EnumSpecies::MiqoteSunseeker || this->speciesAbout == EnumSpecies::MiqoteMoonkeeper ||
					this->speciesAbout == EnumSpecies::RoegadynLohengarde || this->speciesAbout == EnumSpecies::RoegadynSeewolf ||
					this->speciesAbout == EnumSpecies::AuRaRaen || this->speciesAbout == EnumSpecies::AuRaXaela ||
					this->speciesAbout == EnumSpecies::HrothgarHelions || this->speciesAbout == EnumSpecies::HrothgarTheLost ||
					this->speciesAbout == EnumSpecies::RavaViera || this->speciesAbout == EnumSpecies::VeenaViera) {
				this->speciesBaselineStatus[target.first] += 10LL;
				if (this->speciesAbout == EnumSpecies::AuRaRaen || this->speciesAbout == EnumSpecies::AuRaXaela) {
					this->speciesBaselineStatus[target.first] += 10LL;
				}
			}
			//ドラゴノイドは穢れ+3相当とする。
			if (this->speciesAbout == EnumSpecies::DragonoidMidir || this->speciesAbout == EnumSpecies::DragonoidMidgardsormr) {
				this->speciesBaselineStatus[target.first] += 30LL;
			}
		}
	}

	inline void DataSpecies::setSpecificSkills() {
		this->speciesSpecificSkills = vector<SpecificSkill*>();
	}

	inline DataSpecies::DataSpecies(Json specJson) {
		string broad = specJson["broad"].is_string() ? specJson["broad"].string_value() : "";
		string middle = specJson["middle"].is_string() ? specJson["middle"].string_value() : "";
		string tribe = specJson["tribe"].is_string() ? specJson["tribe"].string_value() : "";

		/* -- 種族の大まかな分類の実行 -- */
		{
			/* -- SW2.x種族(一部追加あり) -- */
			//人間／ヴァルキリー／ノーブルヴァルキリー
			if (compareLineString(broad, "Human")) {
				//人間
				if (compareLineString(middle, "Normal") || middle.empty()) {
					if (compareLineString(tribe, "Midlander")) this->speciesAbout = EnumSpecies::HumanMidlander;
					else if (compareLineString(tribe, "Highlander")) this->speciesAbout = EnumSpecies::HumanHighlander;
					else throw runtime_error("Tribes Selection Error");
				}
				//ヴァルキリー
				else if (compareLineString(middle, "ValkyrieNormal")) {
					if (compareLineString(tribe, "Midlander")) this->speciesAbout = EnumSpecies::HumanValkyrieNormalMidlander;
					else if (compareLineString(tribe, "Highlander")) this->speciesAbout = EnumSpecies::HumanValkyrieNormalHighlander;
					else throw runtime_error("Tribes Selection Error");
				}
				//ノーブルヴァルキリー
				else if (compareLineString(middle, "ValkyrieNoble")) {
					if (compareLineString(tribe, "Ancient")) this->speciesAbout = EnumSpecies::HumanValkyrieNobleAncient;
					else if (compareLineString(tribe, "Modern") || compareLineString(tribe, "Current")) this->speciesAbout = EnumSpecies::HumanValkyrieNobleModern;
					else throw runtime_error("Tribes Selection Error");
				}
			}
			//エルフ／ノーブルエルフ
			else if (compareLineString(broad, "Elves")) {
				//エルフ
				if (compareLineString(middle, "Normal") || middle.empty()) {
					if (compareLineString(tribe, "Forester")) this->speciesAbout = EnumSpecies::ElvesForester;
					else if (compareLineString(tribe, "Shader")) this->speciesAbout = EnumSpecies::ElvesShader;
					else throw runtime_error("Tribes Selection Error");
				}
				//スノウエルフ
				else if (compareLineString(middle, "Snowed")) this->speciesAbout = EnumSpecies::ElvesSnowed;
				//ミストエルフ
				else if (compareLineString(middle, "Mist")) this->speciesAbout = EnumSpecies::ElvesMist;
				//ノーブルエルフ
				else if (compareLineString(middle, "Noble")) {
					if (compareLineString(tribe, "Forester")) this->speciesAbout = EnumSpecies::ElvesNobleForester;
					else if (compareLineString(tribe, "Shader")) this->speciesAbout = EnumSpecies::ElvesNobleShader;
					else throw runtime_error("Tribes Selection Error");
				}
			}
			//ドワーフ／ダークドワーフ
			else if (compareLineString(broad, "Dwarf")) {
				if (compareLineString(middle, "Fire") || middle.empty()) this->speciesAbout = EnumSpecies::DwarfFire;
				else if (compareLineString(middle, "Dark")) this->speciesAbout = EnumSpecies::DwarfDark;
			}
			//タビット
			else if (compareLineString(broad, "Tabbit")) {
				if (compareLineString(middle, "Normal") || middle.empty()) this->speciesAbout = EnumSpecies::TabbitNormal;
				else if (compareLineString(middle, "Pica")) this->speciesAbout = EnumSpecies::TabbitPica;
				else if (compareLineString(middle, "Rivash")) this->speciesAbout = EnumSpecies::TabbitRivash;
			}
			//ルーンフォーク／魔動天使
			else if (compareLineString(broad, "Runefolk")) {
				if (compareLineString(middle, "Normal") ||
						compareLineString(middle, "Common") ||
						middle.empty()) this->speciesAbout = EnumSpecies::RunefolkCommon;
				else if (compareLineString(middle, "MagitechAngel")) this->speciesAbout = EnumSpecies::RunefolkMagitechAngel;
				else if (compareLineString(middle, "Defender")) this->speciesAbout = EnumSpecies::RunefolkDefender;
				else if (compareLineString(middle, "Attacker")) this->speciesAbout = EnumSpecies::RunefolkAttacker;
			}
			//ナイトメア
			else if (compareLineString(broad, "Nightmare")) {
				if (compareLineString(middle, "Human")) this->speciesAbout = EnumSpecies::NightmareHuman;
				else if (compareLineString(middle, "Elves")) this->speciesAbout = EnumSpecies::NightmareElves;
				else if (compareLineString(middle, "Dwarf")) this->speciesAbout = EnumSpecies::NightmareDwarf;
				else if (compareLineString(middle, "Lilidracken")) this->speciesAbout = EnumSpecies::NightmareLilidracken;
				else if (compareLineString(middle, "Sunbreaker")) this->speciesAbout = EnumSpecies::NightmareSunbreaker;
				else if (compareLineString(middle, "Shadow")) this->speciesAbout = EnumSpecies::NightmareShadow;
				else throw runtime_error("Sub-Category Selection Error");
			}
			//リカント
			else if (compareLineString(broad, "Lycan")) {
				if (compareLineString(middle, "Normal") || middle.empty()) this->speciesAbout = EnumSpecies::LycanNormal;
				else if (compareLineString(middle, "LargerHerbivore")) this->speciesAbout = EnumSpecies::LycanLargerHerbivore;
				else if (compareLineString(middle, "SmallerHerbivore")) this->speciesAbout = EnumSpecies::LycanSmallerHerbivore;
			}
			//リルドラケン
			else if (compareLineString(broad, "Lilidracken")) {
				if (compareLineString(middle, "Normal") || middle.empty()) this->speciesAbout = EnumSpecies::LilidrackenNormal;
				else if (compareLineString(middle, "Smallwing")) this->speciesAbout = EnumSpecies::LilidrackenSmallwing;
				else if (compareLineString(middle, "Hairy")) this->speciesAbout = EnumSpecies::LilidrackenHairy;
			}
			//グラスランナー
			else if (compareLineString(broad, "Grassrunner")) {
				if (compareLineString(middle, "Normal") || middle.empty()) this->speciesAbout = EnumSpecies::GrassrunnerNormal;
				else if (compareLineString(middle, "Alisha")) this->speciesAbout = EnumSpecies::GrassrunnerAlisha;
				else if (compareLineString(middle, "Climenos")) this->speciesAbout = EnumSpecies::GrassrunnerClimenos;
			}
			//メリア
			else if (compareLineString(broad, "Meria")) {
				if (compareLineString(middle, "Normal") || middle.empty()) this->speciesAbout = EnumSpecies::MeriaNormal;
				else if (compareLineString(middle, "Cannibalistic")) this->speciesAbout = EnumSpecies::MeriaCannibalistic;
				else if (compareLineString(middle, "Fungy")) this->speciesAbout = EnumSpecies::MeriaFungy;
			}
			//ティエンス
			else if (compareLineString(broad, "Tience")) {
				if (compareLineString(middle, "Normal") || middle.empty()) this->speciesAbout = EnumSpecies::TienceNormal;
				else if (compareLineString(middle, "TechEasy")) this->speciesAbout = EnumSpecies::TienceTechEasy;
				else if (compareLineString(middle, "DemonEasy")) this->speciesAbout = EnumSpecies::TienceDemonEasy;
			}
			//レプラカーン
			else if (compareLineString(broad, "Leprechaun")) {
				if (compareLineString(middle, "Normal") || middle.empty()) this->speciesAbout = EnumSpecies::LeprechaunNormal;
				else if (compareLineString(middle, "Vagrant")) this->speciesAbout = EnumSpecies::LeprechaunVagrant;
				else if (compareLineString(middle, "Search")) this->speciesAbout = EnumSpecies::LeprechaunSearch;
			}
			//アルヴ
			else if (compareLineString(broad, "Arve")) this->speciesAbout = EnumSpecies::Arve;
			//シャドウ
			else if (compareLineString(broad, "Shadow")) this->speciesAbout = EnumSpecies::Shadow;
			//ソレイユ
			else if (compareLineString(broad, "Sunbreaker")) this->speciesAbout = EnumSpecies::Sunbreaker;
			//スプリガン
			else if (compareLineString(broad, "Spriggan")) this->speciesAbout = EnumSpecies::Spriggan;
			//アビスボーン
			else if (compareLineString(broad, "Abyssborne")) this->speciesAbout = EnumSpecies::Abyssborne;
			//ハイマン
			else if (compareLineString(broad, "LittleHighHuman")) {
				if (compareLineString(tribe, "Midlander")) this->speciesAbout = EnumSpecies::LittleHighHumanMidlander;
				else if (compareLineString(tribe, "Highlander")) this->speciesAbout = EnumSpecies::LittleHighHumanHighlander;
			}
			//フロウライト
			else if (compareLineString(broad, "Fluorite")) this->speciesAbout = EnumSpecies::Fluorite;
			/* -- FF14種族(一部のみ) -- */
			//ララフェル
			else if (compareLineString(broad, "Lalafell")) {
				if (compareLineString(tribe, "Plainsfolk")) this->speciesAbout = EnumSpecies::LalafellPlainsfolk;
				else if (compareLineString(tribe, "Dunefolk")) this->speciesAbout = EnumSpecies::LalafellDunesfolk;
				else throw runtime_error("Tribes Selection Error");
			}
			//ミコッテ
			else if (compareLineString(broad, "Miqote")) {
				if (compareLineString(tribe, "Sunseeker")) this->speciesAbout = EnumSpecies::MiqoteSunseeker;
				else if (compareLineString(tribe, "Moonkeeper")) this->speciesAbout = EnumSpecies::MiqoteMoonkeeper;
				else throw runtime_error("Tribes Selection Error");
			}
			//ルガディン
			else if (compareLineString(broad, "Roegadyn")) {
				if (compareLineString(tribe, "Lohengarde")) this->speciesAbout = EnumSpecies::RoegadynLohengarde;
				else if (compareLineString(tribe, "Seewolf")) this->speciesAbout = EnumSpecies::RoegadynSeewolf;
				else throw runtime_error("Tribes Selection Error");
			}
			//アウラ
			else if (compareLineString(broad, "AuRa")) {
				if (compareLineString(tribe, "Raen")) this->speciesAbout = EnumSpecies::AuRaRaen;
				else if (compareLineString(tribe, "Xaela")) this->speciesAbout = EnumSpecies::AuRaXaela;
				else throw runtime_error("Tribes Selection Error");
			}
			//ヴィエラ
			else if (compareLineString(broad, "Viera")) {
				if (compareLineString(tribe, "Rava")) this->speciesAbout = EnumSpecies::RavaViera;
				else if (compareLineString(tribe, "Veena")) this->speciesAbout = EnumSpecies::VeenaViera;
				else throw runtime_error("Tribes Selection Error");
			}
			//ロスガル
			else if (compareLineString(broad, "Hrothgar")) {
				if (compareLineString(tribe, "Helions")) this->speciesAbout = EnumSpecies::HrothgarHelions;
				else if (compareLineString(tribe, "TheLost")) this->speciesAbout = EnumSpecies::HrothgarTheLost;
				else throw runtime_error("Tribes Selection Error");
			}
			/* -- 新造 -- */
			//ドラゴノイド
			else if (compareLineString(broad, "Dragonoid")) {
				if (compareLineString(middle, "Midir")) this->speciesAbout = EnumSpecies::DragonoidMidir;
				else if (compareLineString(middle, "Midgardsormr")) this->speciesAbout = EnumSpecies::DragonoidMidgardsormr;
			}
			//星の記録者ほか、小分類ができない種族たち
			else if (compareLineString(broad, "Starlogger")) this->speciesAbout = EnumSpecies::Starlogger;
			else if (compareLineString(broad, "Barbaroses")) this->speciesAbout = EnumSpecies::Barbaroses;
			else if (compareLineString(broad, "NatureBeasts")) this->speciesAbout = EnumSpecies::NatureBeasts;
			else if (compareLineString(broad, "SoulAlignedPlants")) this->speciesAbout = EnumSpecies::SoulAlignedPlants;
			else if (compareLineString(broad, "Undeads")) this->speciesAbout = EnumSpecies::Undeads;
			else if (compareLineString(broad, "MagicalEntities")) this->speciesAbout = EnumSpecies::MagicalEntities;
			else if (compareLineString(broad, "MagitechMachines")) this->speciesAbout = EnumSpecies::MagitechMachines;
			else if (compareLineString(broad, "MysticBeasts")) this->speciesAbout = EnumSpecies::MysticBeasts;
			else if (compareLineString(broad, "Fae")) this->speciesAbout = EnumSpecies::Fae;
			else if (compareLineString(broad, "BorneFromTheAbyssos")) this->speciesAbout = EnumSpecies::BorneFromTheAbyssos;
			else if (compareLineString(broad, "MereMortal")) this->speciesAbout = EnumSpecies::MereMortal;
			else if (compareLineString(broad, "MereDemigod")) this->speciesAbout = EnumSpecies::MereDemigod;
			else if (compareLineString(broad, "Primals")) this->speciesAbout = EnumSpecies::Primals;
			else if (compareLineString(broad, "NearestTruth")) this->speciesAbout = EnumSpecies::NearestTruth;
			else if (broad.empty()) throw runtime_error("Species is Need Select");
			else this->speciesAbout = EnumSpecies::Other;
		}

		/* ステータスの決定 */
		this->setBaselineStatus();
	}

	inline DataSpecies::DataSpecies(const DataSpecies* from) {
		this->speciesAbout = from->speciesAbout;
		this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>(from->speciesBaselineStatus);
		this->speciesDisgrace = from->speciesDisgrace;
	}
	/* -- End class: DataSpecies -- */

	/// <summary>
	/// パイロットの特殊技能に関わるデータクラスです。
	/// </summary>
	class SpecificSkill {
	protected:
		/// <summary>
		/// 特殊技能の種類
		/// </summary>
		EnumSpecificSkills skillType;
		/// <summary>
		/// 効果発揮条件
		/// </summary>
		ActiveConditionSS* skillActiveCondition;
	public:
		/// <summary>
		/// 特殊技能の種類を返却します。
		/// </summary>
		/// <returns>特殊技能の種類</returns>
		EnumSpecificSkills getSkillType() const {
			return this->skillType;
		}
		/// <summary>
		/// 効果発揮条件を返却します。
		/// </summary>
		/// <returns>効果発揮条件</returns>
		ActiveConditionSS* getSkillActiveCondition() const {
			return this->skillActiveCondition;
		}
	};
	/* -- End class: SpecificSkill -- */

	/// <summary>
	/// ベースとなる設定
	/// </summary>
	class ActiveConditionSS {
	protected:
		int32_t acMorale;
		int64_t acLLevel;
	public:
		/// <summary>
		/// 条件の評価を行います。
		/// </summary>
		/// <param name="pilot">ゲーム上での処理対象</param>
		/// <returns>評価に基づく成否</returns>
		bool AvailableConditions(GamePilot* pilot);
		bool LearnConditions(GamePilot* pilot);
	};

	inline bool ActiveConditionSS::AvailableConditions(GamePilot* pilot) {
		//
	}

	inline bool ActiveConditionSS::LearnConditions(GamePilot* pilot) {
		//
	}
	/* -- End class: ActiveConditionSS -- */

	/// <summary>
	/// パイロットのデータを格納するクラスです。
	/// </summary>
	class DataPilot {
	protected:
		/// <summary>
		/// 識別用のデータIDです。
		/// </summary>
		uint32_t pilotDataId;
		/// <summary>
		/// [Unlocalized] 本名
		/// </summary>
		string pilotFullname;
		/// <summary>
		/// [Unlocalized] 愛称
		/// </summary>
		string pilotNickname;
		/// <summary>
		/// [Unlocalized] 読み仮名
		/// </summary>
		string pilotReadname;
		/// <summary>
		/// [Unlocalized] 通り名
		/// </summary>
		string pilotCodename;
		/// <summary>
		/// パイロットの種族
		/// </summary>
		DataSpecies* pilotSpecies;
		/// <summary>
		/// パイロットの性別
		/// </summary>
		EnumGender pilotGender;
		/// <summary>
		/// パイロットの性格
		/// </summary>
		EnumPilotPersonality pilotPersonality;
		/// <summary>
		/// 種族的に与えられた穢れの値
		/// </summary>
		int64_t pilotAdditionalDisgrace;
		/// <summary>
		/// パイロットの初期ステータス
		/// </summary>
		map<EnumPilotStatusInitials, int64_t> pilotDataStatus;
		/// <summary>
		/// パイロットの初期精神ポイント
		/// </summary>
		int64_t pilotSpiritualPoint;
		/* -- 関数 -- */

		/// <summary>
	/// パイロットの性別データを列挙型に変換します。
	/// </summary>
	/// <param name="rawGender">性別データの生データ(string型)</param>
		void setPilotGender(string rawGender);
		/// <summary>
		/// パイロットの性別データを列挙型に変換します。
		/// </summary>
		/// <param name="rawGender">性別データの生データ(json型)</param>
		void setPilotGender(Json rawGender);
		/// <summary>
		/// パイロットの性格データを列挙型に変換します。
		/// </summary>
		/// <param name="rawPersonality">性格データの生データ(string型)</param>
		void setPilotPersonality(string rawPersonality);
		/// <summary>
		/// パイロットの性格データを列挙型に変換します。
		/// </summary>
		/// <param name="rawPersonality">性格データの生データ(json型)</param>
		void setPilotPersonality(Json rawPersonality);
		/// <summary>
		/// パイロットの初期ステータスを定義します。
		/// </summary>
		/// <param name="addtional_status"></param>
		void setPilotDataStatus(Json addtional_status);
	public:
		/// <summary>
		/// 識別用のデータIDを返却する関数です。
		/// </summary>
		/// <returns>識別用のデータID</returns>
		uint32_t getPilotDataId() const {
			return this->pilotDataId;
		}
		/// <summary>
		/// パイロットの本名に関わる翻訳前文字列を返却する関数です。
		/// </summary>
		/// <returns>[Unlocalized] 本名</returns>
		string getPilotFullname() const {
			return this->pilotFullname;
		}
		/// <summary>
		/// パイロットの愛称に関わる翻訳前文字列を返却する関数です。
		/// </summary>
		/// <returns>[Unlocalized] 愛称</returns>
		string getPilotNickname() const {
			return this->pilotNickname;
		}
		/// <summary>
		/// パイロットの読みに関わる翻訳前文字列を返却する関数です。
		/// </summary>
		/// <returns>[Unlocalized] 読み仮名</returns>
		string getPilotReadname() const {
			return this->pilotReadname;
		}
		/// <summary>
		/// パイロットの通称に関わる翻訳前文字列を返却する関数です。
		/// </summary>
		/// <returns>[Unlocalized] 通称</returns>
		string getPilotCodename() const {
			return this->pilotCodename;
		}
		/// <summary>
		/// パイロットの種族インスタンス・ポインタを返却する関数です。
		/// </summary>
		/// <returns>種族データ</returns>
		DataSpecies* getPilotSpecies() const {
			return this->pilotSpecies;
		}
		/// <summary>
		/// パイロットの性別データを返却する関数です。
		/// </summary>
		/// <returns>性別。必ずしも設定した通りに返却されるわけではなく、ヴァルキリー系とロスガルのみ特殊処理が走っている。</returns>
		EnumGender getPilotGender() const {
			return this->pilotGender;
		}
		/// <summary>
		/// パイロットの性格データを返却する関数です。
		/// </summary>
		/// <returns>性格。必ずしも設定した通りに返却されるわけではなく、ミスがあると「普通」が返却される。</returns>
		EnumPilotPersonality getPilotPersonality() const {
			return this->pilotPersonality;
		}
		/// <summary>
		/// パイロットの合計穢れ値を返却する関数です。
		/// </summary>
		/// <returns>穢れ値の合計</returns>
		int64_t getPilotAdditionalDisgrace() const {
			return this->pilotAdditionalDisgrace;
		}
		/// <summary>
		/// パイロットの初期ステータスを返却する関数です。
		/// </summary>
		/// <returns>パイロットの初期ステータス(MAP型)</returns>
		map<EnumPilotStatusInitials, int64_t> getPilotDataStatus() const {
			return this->pilotDataStatus;
		}
		/// <summary>
		/// パイロットの初期ステータスを各項目ごとに返却する関数です。
		/// </summary>
		/// <param name="index">項目の列挙型</param>
		/// <returns>パイロットの初期ステータス(int64_t型)</returns>
		int64_t getPilotDataStatus(EnumPilotStatusInitials index) const {
			return this->pilotDataStatus.at(index);
		}
		/// <summary>
		/// パイロットの初期精神ポイントを返却する関数です。
		/// </summary>
		/// <returns>パイロットの初期精神ポイント</returns>
		int64_t getPilotSpiritualPoint() const {
			return this->pilotSpiritualPoint;
		}
		/// <summary>
		/// DataPilotクラスのコンストラクタ
		/// </summary>
		/// <param name="jsonDat">JSONデータ。配列データではないので注意</param>
		DataPilot(Json jsonDat);
	};

	inline void DataPilot::setPilotGender(string rawGender) {
		if (compareLineString(rawGender, "Male")) this->pilotGender = EnumGender::Male;
		else if (compareLineString(rawGender, "Female")) this->pilotGender = EnumGender::Female;
		else if (compareLineString(rawGender, "Neutral")) this->pilotGender = EnumGender::Neutral;
		else if (compareLineString(rawGender, "Asexual")) this->pilotGender = EnumGender::Asexual;
		else if (compareLineString(rawGender, "Machine")) this->pilotGender = EnumGender::Machine;
		else {
			if (this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HumanValkyrieNormalMidlander ||
					this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HumanValkyrieNormalHighlander ||
					this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HumanValkyrieNobleModern ||
					this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HumanValkyrieNobleAncient) this->pilotGender = EnumGender::Female;
			else if (this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HrothgarHelions ||
					this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HrothgarTheLost) this->pilotGender = EnumGender::Male;
			else throw runtime_error("Gender Settings Error");
		}
		if (this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HumanValkyrieNormalMidlander ||
				this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HumanValkyrieNormalHighlander ||
				this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HumanValkyrieNobleModern ||
				this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HumanValkyrieNobleAncient) this->pilotGender = EnumGender::Female;
		else if (this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HrothgarHelions ||
				this->pilotSpecies->getSpeciesAbout() == EnumSpecies::HrothgarTheLost) this->pilotGender = EnumGender::Male;
	}

	inline void DataPilot::setPilotGender(Json rawGender) {
		this->setPilotGender(rawGender.is_string() ? rawGender.string_value() : rawGender["gender"].string_value());
	}

	inline void DataPilot::setPilotPersonality(string rawPersonality) {
		if (compareLineString(rawPersonality, "Bigwig") ||
			compareLineString(rawPersonality, "大物")) this->pilotPersonality = EnumPilotPersonality::bigwig;
		else if (compareLineString(rawPersonality, "Calm") ||
			compareLineString(rawPersonality, "冷静")) this->pilotPersonality = EnumPilotPersonality::calm;
		else if (compareLineString(rawPersonality, "Cautious") ||
			compareLineString(rawPersonality, "慎重")) this->pilotPersonality = EnumPilotPersonality::cautious;
		else if (compareLineString(rawPersonality, "Cruelty") ||
			compareLineString(rawPersonality, "残虐")) this->pilotPersonality = EnumPilotPersonality::cruelty;
		else if (compareLineString(rawPersonality, "hardworking") ||
			compareLineString(rawPersonality, "努力家")) this->pilotPersonality = EnumPilotPersonality::hardworking;
		else if (compareLineString(rawPersonality, "machine") ||
			compareLineString(rawPersonality, "機械")) this->pilotPersonality = EnumPilotPersonality::machine;
		else if (compareLineString(rawPersonality, "optimist") ||
			compareLineString(rawPersonality, "楽天家")) this->pilotPersonality = EnumPilotPersonality::optimist;
		else if (compareLineString(rawPersonality, "ordinary") ||
			compareLineString(rawPersonality, "普通")) this->pilotPersonality = EnumPilotPersonality::ordinary;
		else if (compareLineString(rawPersonality, "quicktemper") ||
			compareLineString(rawPersonality, "短気")) this->pilotPersonality = EnumPilotPersonality::quicktemper;
		else if (compareLineString(rawPersonality, "sly") ||
			compareLineString(rawPersonality, "狡猾")) this->pilotPersonality = EnumPilotPersonality::sly;
		else if (compareLineString(rawPersonality, "strong") ||
			compareLineString(rawPersonality, "強気")) this->pilotPersonality = EnumPilotPersonality::strong;
		else if (compareLineString(rawPersonality, "very_bigwig") ||
			compareLineString(rawPersonality, "VeryBigwig") ||
			compareLineString(rawPersonality, "超大物")) this->pilotPersonality = EnumPilotPersonality::very_bigwig;
		else if (compareLineString(rawPersonality, "very_strong") ||
			compareLineString(rawPersonality, "VeryStrong") ||
			compareLineString(rawPersonality, "超強気")) this->pilotPersonality = EnumPilotPersonality::very_strong;
		else this->pilotPersonality = EnumPilotPersonality::ordinary;
	}

	inline void DataPilot::setPilotPersonality(Json rawPersonality) {
		this->setPilotPersonality(rawPersonality.is_string() ? rawPersonality.string_value() : rawPersonality["personality"].string_value());
	}

	inline void DataPilot::setPilotDataStatus(Json additional_status) {
		this->pilotDataStatus = map<EnumPilotStatusInitials, int64_t>(this->pilotSpecies->getSpeciesBaselineStatus());
		this->pilotDataStatus[EnumPilotStatusInitials::MEL] += static_cast<int64_t>(additional_status["MEL"].int_value());
		this->pilotDataStatus[EnumPilotStatusInitials::RNG] += static_cast<int64_t>(additional_status["RNG"].int_value());
		this->pilotDataStatus[EnumPilotStatusInitials::MGC] += static_cast<int64_t>(additional_status["MGC"].int_value());
		this->pilotDataStatus[EnumPilotStatusInitials::DEX] += static_cast<int64_t>(additional_status["DEX"].int_value());
		this->pilotDataStatus[EnumPilotStatusInitials::DEF] += static_cast<int64_t>(additional_status["DEF"].int_value());
		this->pilotDataStatus[EnumPilotStatusInitials::ACU] += static_cast<int64_t>(additional_status["ACU"].int_value());
		this->pilotDataStatus[EnumPilotStatusInitials::AVD] += static_cast<int64_t>(additional_status["AVD"].int_value());
		this->pilotDataStatus[EnumPilotStatusInitials::RIT] += static_cast<int64_t>(additional_status["RIT"].int_value());
		this->pilotDataStatus[EnumPilotStatusInitials::SPB] += static_cast<int64_t>(additional_status["SPB"].int_value());
	}

	inline DataPilot::DataPilot(Json jsonDat) {
		this->pilotDataId = static_cast<uint32_t>(jsonDat["data_id"].number_value());
		this->pilotFullname = jsonDat["fullname"].string_value();
		this->pilotNickname = jsonDat["nickname"].string_value();
		this->pilotReadname = jsonDat["readname"].string_value();
		this->pilotCodename = jsonDat["codename"].string_value();
		this->pilotSpecies = new DataSpecies(jsonDat["species"]);
		this->setPilotGender(jsonDat["gender"].string_value());
		this->setPilotPersonality(jsonDat["personality"].string_value());
		this->setPilotDataStatus(jsonDat["additional_status"]);
		this->pilotAdditionalDisgrace = this->pilotSpecies->getSpeciesDisgrace() + static_cast<int64_t>(jsonDat["additional_disgrace"].int_value());
		this->pilotSpiritualPoint = this->pilotDataStatus[EnumPilotStatusInitials::SPB] + 20;
	}
	/* -- End class: DataPilot -- */

	/// <summary>
	/// ゲーム上での処理を走らせるためのパイロットクラスです。
	/// </summary>
	class GamePilot {
	protected:
		/// <summary>
		/// データ元のパイロットデータ。
		/// </summary>
		DataPilot* basedPilot;
		/// <summary>
		/// ローカライザーによって翻訳されたパイロットのフルネーム
		/// </summary>
		string localizedPilotFullname;
		/// <summary>
		/// ローカライザーによって翻訳されたパイロットの愛称
		/// </summary>
		string localizedPilotNickname;
		/// <summary>
		/// ローカライザーによって翻訳されたパイロットの読み仮名
		/// </summary>
		string localizedPilotReadname;
		/// <summary>
		/// ローカライザーによって翻訳されたパイロットのコードネーム
		/// </summary>
		string localizedPilotCodename;
		/// <summary>
		/// パイロットのレベル
		/// </summary>
		int64_t pilotLevel;
	public:
		/// <summary>
		/// データ元のパイロットデータを返却します。
		/// </summary>
		/// <returns>データ元のパイロットデータ</returns>
		DataPilot* getBasedPilot() const {
			return this->basedPilot;
		}
		/// <summary>
		/// ローカライザーによって翻訳されたパイロットのフルネームを返却します。
		/// </summary>
		/// <returns>ローカライザーによって翻訳されたパイロットのフルネーム</returns>
		string getLocalizedPilotFullname() const {
			return this->localizedPilotFullname;
		}
		/// <summary>
		/// ローカライザーによって翻訳されたパイロットの愛称を返却します。
		/// </summary>
		/// <returns>ローカライザーによって翻訳されたパイロットの愛称</returns>
		string getLocalizedPilotNickname() const {
			return this->localizedPilotNickname;
		}
		/// <summary>
		/// ローカライザーによって翻訳されたパイロットの読み仮名を返却します。
		/// </summary>
		/// <returns>ローカライザーによって翻訳されたパイロットの読み仮名</returns>
		string getLocalizedPilotReadname() const {
			return this->localizedPilotReadname;
		}
		/// <summary>
		/// ローカライザーによって翻訳されたパイロットのコードネームを返却します。
		/// </summary>
		/// <returns>ローカライザーによって翻訳されたパイロットのコードネーム</returns>
		string getLocalizedPilotCodename() const {
			return this->localizedPilotCodename;
		}
		/// <summary>
		/// パイロットの現在レベルを返却します。パイロットの最大レベルは100です。
		/// </summary>
		/// <returns>パイロットの現在レベル</returns>
		int64_t getPilotLevel() const {
			return this->pilotLevel;
		}
		GamePilot(DataPilot* pilotDat);
		GamePilot(DataPilot* pilotDat, int64_t pLevel);
	};

	GamePilot::GamePilot(DataPilot* pilotDat) {
		this->basedPilot = pilotDat;
		this->pilotLevel = 1LL;
	}
	GamePilot::GamePilot(DataPilot* pilotDat, int64_t pLevel) : GamePilot(pilotDat) {
		this->pilotLevel = pLevel;
	}
	/* -- End class: GamePilot -- */
}

using namespace TREx;

