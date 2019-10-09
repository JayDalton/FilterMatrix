
#include "common.h"

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

#include "Config/Parameter.h"
#include "Config/Configuration.h"
#include "Config/ValueVisitor.h"

#include "Logger/Logger.h"
#include "Logger/MethodTimer.h"

// Codepage: UTF-8 (ÜüÖöÄäẞß)
