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
#include "Pilots.h"
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
		class JSONParser;

		/* -- begin class: JSONParser -- */

		/// <summary>
		/// JSONをパーシングするためのクラスです。
		/// </summary>
		class JSONParser {
		protected:
		public:
		};

		/* -- end class: JSONParser -- */
	}
}

using namespace TREx;
