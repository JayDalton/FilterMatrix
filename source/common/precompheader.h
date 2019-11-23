
#pragma warning(disable : 26812) //Warning C26812 Prefer 'enum class' over 'enum'


#include <variant>
#include <utility>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <optional>
#include <fstream>
#include <string_view>
//#include <experimental/>

#include <string>
#include <string_view>
#include <variant>

#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <numeric>

using namespace std::string_literals;

#include <fstream>

#include <filesystem>

namespace fs = std::filesystem;

// Logging
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include "spdlog/sinks/basic_file_sink.h"
namespace logger = spdlog;

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/reader.h>
#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include <rapidjson/encodings.h>
#include <rapidjson/encodedstream.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
namespace json = rapidjson;


// Codepage: UTF-8 (ÜüÖöÄäẞß)
