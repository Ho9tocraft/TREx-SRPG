#pragma once
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

#include <openssl/aes.h>

#pragma warning(push)
#pragma warning(disable: 4251)
#pragma warning(disable: 4275)
#pragma warning(disable: 4996)
#include <yaml-cpp/yaml.h>
#pragma warning(pop)

#include <DxLib.h>

#include "all_loaders.h"
#include "strconv2.h"
#include "ResourceLoader.h"
#include "main.h"
#include "Pilots.h"
#include "Parser.h"
#include "Units.h"
#include "json11.hpp"

using namespace std;
/* DROPBOX/JSON11 LIBRARIES */
using namespace json11;

namespace TREx {
	struct DictDataEnviroment;
	/// <summary>
	/// 武器に付与される元素的属性。
	/// </summary>
	enum class EnumMagicalElement : uint64_t;
	/// <summary>
	/// 地形適応のヘッダとなる種類。
	/// </summary>
	enum class EnumTerrainAdaptionType : uint64_t;
	/// <summary>
	/// 地形適応の中身。
	/// </summary>
	enum class EnumTerrainAdaptionRank : uint64_t;
	class JSONParser;

	enum class EnumGender : uint64_t;
	enum class EnumPilotPersonality : uint64_t;
	enum class EnumSpecies : uint64_t;
	enum class EnumPilotStatusInitials : uint64_t;
	enum class EnumSpecificSkills : int64_t;

	class DataSpecies;
	class SpecificSkill;
	class SpiritualPower;
	class SpiritualPowerEffect;
	class ActiveConditionSS;
	class DataSpiritualEffect;
	class DataPilot;
	class GamePilot;

	class DataUnit;
	class GameUnit;



	enum class EnumMagicalElement : uint64_t {
		/// <summary>
		/// 霊極性:光属性
		/// </summary>
		UmbralLight,
		/// <summary>
		/// 霊極性:水属性
		/// </summary>
		UmbralWater,
		/// <summary>
		/// 霊極性:氷属性
		/// </summary>
		UmbralIce,
		/// <summary>
		/// 霊極性:土属性
		/// </summary>
		UmbralEarth,
		/// <summary>
		/// 星極性:闇
		/// </summary>
		AstralDark,
		/// <summary>
		/// 星極性:風
		/// </summary>
		AstralWind,
		/// <summary>
		/// 星極性:雷
		/// </summary>
		AstralLightning,
		/// <summary>
		/// 星極性:炎
		/// </summary>
		AstralFire,
		/// <summary>
		/// 剣極性:毒
		/// </summary>
		GenSwordToxic,
		/// <summary>
		/// 剣極性:病気
		/// </summary>
		GenSwordPlague,
		/// <summary>
		/// 剣極性:精神効果
		/// </summary>
		GenSwordMindConfuse,
		/// <summary>
		/// 剣極性:呪い
		/// </summary>
		GenSwordAccursed,
		/// <summary>
		/// 剣極性:黒炎
		/// </summary>
		GenSwordBlackflame
	};

	enum class EnumTerrainAdaptionType : uint64_t {
		/// <summary>
		/// 空
		/// </summary>
		Air,
		/// <summary>
		/// 陸
		/// </summary>
		Ground,
		/// <summary>
		/// 海
		/// </summary>
		Underwater,
		/// <summary>
		/// 宇
		/// </summary>
		Outerworld
	};

	enum class EnumTerrainAdaptionRank : uint64_t {
		/// <summary>
		/// -（行動・攻撃不能）
		/// </summary>
		E,
		/// <summary>
		/// D（40％）
		/// </summary>
		D,
		/// <summary>
		/// C（80％）
		/// </summary>
		C,
		/// <summary>
		/// B（90％）
		/// </summary>
		B,
		/// <summary>
		/// A（等倍）
		/// </summary>
		A,
		/// <summary>
		/// S（110％）
		/// </summary>
		S
	};
}
