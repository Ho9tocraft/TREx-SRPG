#pragma once
#include <string>
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
#include <iomanip>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>

#include "all_loaders.h"
#include "main.h"
#include "JSONParser.h"

using namespace std;
/* BOOST C++ LIBRARIES */
using namespace boost;
using namespace property_tree;
using namespace json_parser;
using namespace foreach;
using namespace optional_config;
using namespace optional_detail;
using namespace optional_ns;

namespace TREx {
	namespace Units {
		class DataUnit;
		class GameUnit;

		/// <summary>
		/// Unitのデータクラスになります。
		/// </summary>
		class DataUnit {
		protected:
		public:
		};

		class GameUnit {
		protected:
		public:
		};
	}
}

using namespace TREx;

