
#include "common.h"

// Logging
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include "spdlog/sinks/basic_file_sink.h"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"

namespace json = rapidjson;

#include "Config/ConfigParameter.h"
#include "Config/Configuration.h"
#include "Config/ValueVisitor.h"

#include "Logger/Logger.h"
#include "Logger/MethodTimer.h"

// Codepage: UTF-8 (ÜüÖöÄäẞß)
