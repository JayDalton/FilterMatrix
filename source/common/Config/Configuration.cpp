#include "precompheader.h"

#include "Configuration.h"

bool Configuration::loadJsonFile(fs::path filePath)
{
   if (!fs::exists(filePath))
   {
      return false;
   }


}

bool Configuration::saveJsonFile(fs::path filePath) const
{
   return false;
}

void Configuration::registerString(const std::string& nameOfParam, const std::string& description, const std::string& defaultValue, std::size_t maximum, std::size_t minimum)
{

}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
