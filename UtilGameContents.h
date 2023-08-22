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
#include "strconv2.h"
#include "ResourceLoader.h"
#include "main.h"
#include "Pilots.h"
#include "Parser.h"
#include "Units.h"
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
	namespace Utils {
		enum class EnumMagicalElement : uint64_t;
		class JSONParser;

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
	}
}
