#pragma once

// std
#include <chrono>
#include <future>
#include <vector>
#include <variant>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <string_view>

// boost

#include <experimental/coroutine>
using std::experimental::coroutine_handle;

// openCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>


// own
#include "MethodTimer.h"
#include "MatrixFilter.h"
#include "MatrixViewer.h"
#include "ValueVisitor.h"


#include "Configuration.h"