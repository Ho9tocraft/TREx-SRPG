#pragma once
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
		public:
		};
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
			DataSpecies pilotSpecies;
			map<EnumPilotStatusInitials, int64_t> pilotDataStatus;
		public:
			DataPilot(Json jsonDat);
		};

		DataPilot::DataPilot(Json jsonDat) {
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
			/// パイロットのレベル
			/// </summary>
			int64_t pilotLevel;
		public:
		};
		/* -- End class: GamePilot -- */
	}
}

using namespace TREx;

