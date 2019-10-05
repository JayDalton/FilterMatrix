
#include "common.h"

// Logging
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include "spdlog/sinks/basic_file_sink.h"

#include "Config/ConfigParameter.h"
#include "Config/Configuration.h"
#include "Config/ValueVisitor.h"

#include "Logger/Logger.h"
#include "Logger/MethodTimer.h"

// Codepage: UTF-8 (ÜüÖöÄäẞß)
