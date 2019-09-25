#pragma once

#include <string>

/*

<Config>
  <Parameter type="integer" name="">...</Parameter>

</Config>

*/


struct ConfigParameter
{
   enum class Type
   {
      None
   };

   ConfigParameter();
};

//////////////////////////////////////////////////////////////////////////

struct ParameterConfig : public ConfigParameter
{
	ParameterConfig(ConfigParameter::Type type);

	std::string m_;
};

