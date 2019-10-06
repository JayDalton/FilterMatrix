#pragma once

struct Parameter;
using ParameterOpt = std::optional<Parameter>;

struct Configuration
{
   std::string m_ident;
   std::string m_label;

   bool loadJsonFile(fs::path filePath);

   bool saveJsonFile(fs::path filePath) const;

protected:

   void registerParameter(const Parameter& parameter);

   const Parameter& getParameter(const std::string& paramName) const;

   ParameterOpt getParameterOpt(const std::string& paramName) const;

   std::optional<std::string> getStringParameter(const std::string& ident) const;


   std::vector<Parameter> m_params;
	std::map<std::string, Parameter> m_map;
   //std::array<Parameter> m_array;
};

///////////////////////////////////////////////////////////////////////////

struct Parameter
{
   using ValueType = std::variant
      <bool, signed, unsigned, float, double
      , std::string, fs::path/*, Configuration*/
      >
   ;

   std::string m_ident;
   std::string m_label;
   ValueType m_current;
   ValueType m_maximum;
   ValueType m_minimum;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
