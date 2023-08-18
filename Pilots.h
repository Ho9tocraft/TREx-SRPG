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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>

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
#include "Units.h"
#include "Parser.h"
#include "json11.hpp"

using namespace std;
/* BOOST C++ LIBRARIES */
using namespace boost::property_tree;
using namespace boost::property_tree::json_parser;
using namespace boost::foreach;
using namespace boost::optional_config;
using namespace boost::optional_detail;
using namespace boost::optional_ns;
/* DROPBOX/JSON11 LIBRARIES */
using namespace json11;

namespace TREx {
	namespace Pilots {
		enum class EnumGender : uint64_t;
		enum class EnumSpecies : uint64_t;
		enum class EnumPilotStatusInitials : uint64_t;
		enum class EnumSpecificSkills : int64_t;

		class DataSpecies;
		class SpecificSkill;
		class ActiveConditionSS;
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
			/// 特殊技能:治癒(SRWにおける「修理技能」に相当)
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
		};

		/// <summary>
		/// 種族データの定義です。
		/// </summary>
		class DataSpecies {
		protected:
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
			/// <para>蛮族: 1以上5未満</para>
			/// <para>アンデッド: 5</para>
			/// <para>星の記録者: -1</para>
			/// <para>その他: 基本0</para>
			/// </summary>
			int64_t speciesDisgrace;
			/// <summary>
			/// 基礎ステータスを定義します。
			/// </summary>
			void setBaselineStatus();
		public:
			DataSpecies(Json specJson);
		};

		inline void DataSpecies::setBaselineStatus() {
			/*
			* ステータスの割り振りについて
			* 合計値が1320になるように割り振る（「星の記録者」まで）。
			* 穢れ持ちは基本合計値に+（穢れ×90）。
			*/
			switch (this->speciesAbout) {
			/*
			* 人間ミドラン: ベース値。つまり「ニューター」。
			*/
			case EnumSpecies::HumanMidlander:
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
				break;
			/*
			* 人間ハイラン: MEL+10, RNG-20, MGC-20, DEX=DEF, DEF+20, ACU+10, AVD-10, RIT+5, SPB+5
			*/
			case EnumSpecies::HumanHighlander:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 150LL },
					{ EnumPilotStatusInitials::RNG, 120LL },
					{ EnumPilotStatusInitials::MGC, 120LL },
					{ EnumPilotStatusInitials::DEX, 170LL },
					{ EnumPilotStatusInitials::DEF, 150LL },
					{ EnumPilotStatusInitials::ACU, 190LL },
					{ EnumPilotStatusInitials::AVD, 170LL },
					{ EnumPilotStatusInitials::RIT, 185LL },
					{ EnumPilotStatusInitials::SPB, 65LL }
				};
				break;
			/*
			* 汎ヴァルミドラン: MEL+5, RNG-10, MGC+10, DEX+5, DEF-10, ACU+5, AVD+5, RIT-20, SPB+10
			*/
			case EnumSpecies::HumanValkyrieNormalMidlander:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 145LL },
					{ EnumPilotStatusInitials::RNG, 130LL },
					{ EnumPilotStatusInitials::MGC, 150LL },
					{ EnumPilotStatusInitials::DEX, 175LL },
					{ EnumPilotStatusInitials::DEF, 120LL },
					{ EnumPilotStatusInitials::ACU, 185LL },
					{ EnumPilotStatusInitials::AVD, 185LL },
					{ EnumPilotStatusInitials::RIT, 160LL },
					{ EnumPilotStatusInitials::SPB, 70LL }
				};
				break;
			/*
			* 汎ヴァルハイラン: MEL+15, RNG-30, MGC-10, DEX+5, DEF+10, ACU+15, AVD-5, RIT-15, SPB+15
			*/
			case EnumSpecies::HumanValkyrieNormalHighlander:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 155LL },
					{ EnumPilotStatusInitials::RNG, 110LL },
					{ EnumPilotStatusInitials::MGC, 130LL },
					{ EnumPilotStatusInitials::DEX, 175LL },
					{ EnumPilotStatusInitials::DEF, 140LL },
					{ EnumPilotStatusInitials::ACU, 195LL },
					{ EnumPilotStatusInitials::AVD, 175LL },
					{ EnumPilotStatusInitials::RIT, 165LL },
					{ EnumPilotStatusInitials::SPB, 75LL }
				};
				break;
			/*
			* 貴ヴァルモダンブランチ: MEL+5, RNG-20, MGC+10, DEX+5, DEF+10, ACU+5, AVD-15, RIT-15, SPB+15
			*/
			case EnumSpecies::HumanValkyrieNobleModern:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 145LL },
					{ EnumPilotStatusInitials::RNG, 120LL },
					{ EnumPilotStatusInitials::MGC, 150LL },
					{ EnumPilotStatusInitials::DEX, 175LL },
					{ EnumPilotStatusInitials::DEF, 140LL },
					{ EnumPilotStatusInitials::ACU, 195LL },
					{ EnumPilotStatusInitials::AVD, 165LL },
					{ EnumPilotStatusInitials::RIT, 165LL },
					{ EnumPilotStatusInitials::SPB, 75LL }
				};
				break;
			/*
			* 貴ヴァルオールドブランチ: MEL-25, RNG+25, MGC+5, DEX-5, DEF-10, ACU+25, AVD-15, RIT-15, SPB+15
			*/
			case EnumSpecies::HumanValkyrieNobleAncient:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 115LL },
					{ EnumPilotStatusInitials::RNG, 165LL },
					{ EnumPilotStatusInitials::MGC, 145LL },
					{ EnumPilotStatusInitials::DEX, 165LL },
					{ EnumPilotStatusInitials::DEF, 120LL },
					{ EnumPilotStatusInitials::ACU, 205LL },
					{ EnumPilotStatusInitials::AVD, 165LL },
					{ EnumPilotStatusInitials::RIT, 165LL },
					{ EnumPilotStatusInitials::SPB, 75LL }
				};
				break;
			/*
			* 汎エルフフォレスター: MEL-10, RNG+10, MGC+10, DEX+5, DEF-5, ACU=DEF, AVD-5, RIT-5, SPB=DEF
			*/
			case EnumSpecies::ElvesForester:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 130LL },
					{ EnumPilotStatusInitials::RNG, 150LL },
					{ EnumPilotStatusInitials::MGC, 150LL },
					{ EnumPilotStatusInitials::DEX, 175LL },
					{ EnumPilotStatusInitials::DEF, 125LL },
					{ EnumPilotStatusInitials::ACU, 180LL },
					{ EnumPilotStatusInitials::AVD, 175LL },
					{ EnumPilotStatusInitials::RIT, 175LL },
					{ EnumPilotStatusInitials::SPB, 60LL }
				};
				break;
			/*
			* 汎エルフシェーダー: MEL-10, RNG=DEF, MGC+20, DEX+10, DEF-5, ACU=DEF, AVD-5, RIT-10, SPB=DEF
			*/
			case EnumSpecies::ElvesShader:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 130LL },
					{ EnumPilotStatusInitials::RNG, 140LL },
					{ EnumPilotStatusInitials::MGC, 160LL },
					{ EnumPilotStatusInitials::DEX, 180LL },
					{ EnumPilotStatusInitials::DEF, 125LL },
					{ EnumPilotStatusInitials::ACU, 180LL },
					{ EnumPilotStatusInitials::AVD, 175LL },
					{ EnumPilotStatusInitials::RIT, 170LL },
					{ EnumPilotStatusInitials::SPB, 60LL }
				};
				break;
			/*
			* 貴エルフフォレスター: MEL-30, RNG-10, MGC+60, DEX+15, DEF-30, ACU=DEF, AVD-5, RIT+5, SPB-5
			*/
			case EnumSpecies::ElvesNobleForester:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 110LL },
					{ EnumPilotStatusInitials::RNG, 130LL },
					{ EnumPilotStatusInitials::MGC, 200LL },
					{ EnumPilotStatusInitials::DEX, 185LL },
					{ EnumPilotStatusInitials::DEF, 100LL },
					{ EnumPilotStatusInitials::ACU, 180LL },
					{ EnumPilotStatusInitials::AVD, 175LL },
					{ EnumPilotStatusInitials::RIT, 185LL },
					{ EnumPilotStatusInitials::SPB, 55LL }
				};
				break;
			/*
			* 貴エルフフォレスター: MEL-30, RNG-20, MGC+75, DEX+30, DEF-50, ACU=DEF, AVD-5, RIT+10, SPB-10
			*/
			case EnumSpecies::ElvesNobleShader:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 110LL },
					{ EnumPilotStatusInitials::RNG, 120LL },
					{ EnumPilotStatusInitials::MGC, 215LL },
					{ EnumPilotStatusInitials::DEX, 200LL },
					{ EnumPilotStatusInitials::DEF, 80LL },
					{ EnumPilotStatusInitials::ACU, 180LL },
					{ EnumPilotStatusInitials::AVD, 175LL },
					{ EnumPilotStatusInitials::RIT, 190LL },
					{ EnumPilotStatusInitials::SPB, 50LL }
				};
				break;
			/*
			* 霧エルフ: MEL-20, RNG+10, MGC+10, DEX+5, DEF=DEF, ACU-5, AVD-5, RIT-5, SPB+10
			*/
			case EnumSpecies::ElvesMist:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 120LL },
					{ EnumPilotStatusInitials::RNG, 150LL },
					{ EnumPilotStatusInitials::MGC, 150LL },
					{ EnumPilotStatusInitials::DEX, 175LL },
					{ EnumPilotStatusInitials::DEF, 130LL },
					{ EnumPilotStatusInitials::ACU, 175LL },
					{ EnumPilotStatusInitials::AVD, 175LL },
					{ EnumPilotStatusInitials::RIT, 175LL },
					{ EnumPilotStatusInitials::SPB, 70LL }
				};
				break;
			/*
			* 雪エルフ: MEL-20, RNG=DEF, MGC+20, DEX+10, DEF=DEF, ACU-5, AVD-5, RIT-10, SPB+15
			*/
			case EnumSpecies::ElvesSnowed:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 120LL },
					{ EnumPilotStatusInitials::RNG, 140LL },
					{ EnumPilotStatusInitials::MGC, 160LL },
					{ EnumPilotStatusInitials::DEX, 180LL },
					{ EnumPilotStatusInitials::DEF, 125LL },
					{ EnumPilotStatusInitials::ACU, 175LL },
					{ EnumPilotStatusInitials::AVD, 175LL },
					{ EnumPilotStatusInitials::RIT, 170LL },
					{ EnumPilotStatusInitials::SPB, 75LL }
				};
				break;
			/*
			* ドワーフ: MEL+10, RNG-10, MGC-10, DEX-5, DEF+25, ACU-5, AVD-5, RIT+10, SPB-5
			*/
			case EnumSpecies::DwarfFire:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 150LL },
					{ EnumPilotStatusInitials::RNG, 130LL },
					{ EnumPilotStatusInitials::MGC, 130LL },
					{ EnumPilotStatusInitials::DEX, 165LL },
					{ EnumPilotStatusInitials::DEF, 155LL },
					{ EnumPilotStatusInitials::ACU, 175LL },
					{ EnumPilotStatusInitials::AVD, 170LL },
					{ EnumPilotStatusInitials::RIT, 190LL },
					{ EnumPilotStatusInitials::SPB, 55LL }
				};
				break;
			/*
			* ダークドワーフ: MEL+15, RNG-10, MGC-15, DEX-5, DEF+25, ACU-5, AVD-5, RIT+5, SPB=DEF
			*/
			case EnumSpecies::DwarfDark:
				this->speciesBaselineStatus = map<EnumPilotStatusInitials, int64_t>{
					{ EnumPilotStatusInitials::MEL, 155LL },
					{ EnumPilotStatusInitials::RNG, 130LL },
					{ EnumPilotStatusInitials::MGC, 125LL },
					{ EnumPilotStatusInitials::DEX, 165LL },
					{ EnumPilotStatusInitials::DEF, 155LL },
					{ EnumPilotStatusInitials::ACU, 175LL },
					{ EnumPilotStatusInitials::AVD, 170LL },
					{ EnumPilotStatusInitials::RIT, 185LL },
					{ EnumPilotStatusInitials::SPB, 60LL }
				};
				break;
			//TODO: タビット～ルンフォ
			/*
			* タビット通常種: MEL-40, RNG-40, MGC+60, DEX-5, DEF+25, ACU-5, AVD-5, RIT+5, SPB=DEF
			*/
			/*
			* タビットパイカ種: MEL-40, RNG-40, MGC+50, DEX-5, DEF+25, ACU-5, AVD-5, RIT+5, SPB=DEF
			*/
			/*
			* タビットリバス種: MEL-40, RNG-40, MGC+40, DEX-5, DEF+25, ACU-5, AVD-5, RIT+5, SPB=DEF
			*/
			}
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
		/* -- End class: DataSpecies -- */

		/// <summary>
		/// パイロットの特殊技能に関わるデータクラスです。
		/// </summary>
		class SpecificSkill {
		protected:
			EnumSpecificSkills skillType;
		public:
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
			string pilotFullname;
			string pilotNickname;
			string pilotReadname;
			string pilotCodename;
			DataSpecies* pilotSpecies;
			EnumGender pilotGender;
			map<EnumPilotStatusInitials, int64_t> pilotDataStatus;
		public:
			DataPilot(Json jsonDat);
		};

		inline DataPilot::DataPilot(Json jsonDat) {
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
			DataPilot basedPilot;
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
		};
		/* -- End class: GamePilot -- */
	}
}

using namespace TREx;

