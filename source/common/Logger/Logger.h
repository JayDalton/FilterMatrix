#pragma once

#include <iostream>
#include <string_view>
//#include <experimental/>


using cstr = const char * const;

static constexpr cstr past_last_slash(cstr str, cstr last_slash)
{
   return
      *str == '\0' ? last_slash :
      *str == '/' ? past_last_slash(str + 1, str + 1) :
      past_last_slash(str + 1, last_slash);
}

static constexpr cstr past_last_slash(cstr str) 
{ 
   return past_last_slash(str, str);
}

#define __SHORT_FILE__ ({constexpr cstr sf__ {past_last_slash(__FILE__)}; sf__;})

struct Logger
{
   explicit Logger();
   ~Logger();
   // const char* functionName, const char* fileName, int lineNo, int maxDurationMSecs = 0
   //explicit Logger(const std::string_view& message, const std::string_view& file, const std::string_view& line);
   //~Logger();

   static void debug(std::string_view message);

private:
   struct Impl;
   static std::unique_ptr<Impl> m;
};

struct CallLogger
{
   CallLogger(std::string_view message, std::string_view file = __FILE__);
};

constexpr auto Square = [] (int n) { return n*n; }; // implicitly constexpr
//constexpr auto LOGGER_CALL() { return Logger(__FUNCTION__, __FILE__, __LINE__); }

