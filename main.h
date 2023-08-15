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

#include <DxLib.h>

#include "all_loaders.h"
#include "Units.h"
#include "Parser.h"

template <typename Of, typename What>
inline bool instanceof(const What w) { return dynamic_cast<const Of*>(w) != 0; }
