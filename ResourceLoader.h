﻿#pragma once
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
#include "main.h"
#include "Units.h"
#include "Pilots.h"
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
	namespace Loaders {
		class LanguageHandler;
		class ImageHandler;

		/// <summary>
		/// 言語分類(ローカライズ)の読み込み用クラスです。
		/// </summary>
		class LanguageHandler {
		protected:
		public:
		};

		/* -- End class: LanguageHandler -- */

		/// <summary>
		/// 画像(イメージ)の読み込み用クラスです。
		/// </summary>
		class ImageHandler {
		protected:
		public:
		};
	}
}