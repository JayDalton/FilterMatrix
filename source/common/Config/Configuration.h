#pragma once

//struct Parameter;
struct Parameter
{
   using ValueList = std::vector<Parameter>;
   using ValueType = std::variant
      <bool, signed, unsigned, float, double
      , std::string, fs::path, ValueList
      >
   ;

   std::string m_ident;
   std::string m_label;
   ValueType m_current;
   ValueType m_maximum;
   ValueType m_minimum;
};

/////////////////////////////////////////////////////////////////////////////

struct Configuration
{
   std::string m_ident;
   std::string m_label;

   bool loadJsonFile(const fs::path& filePath);
   bool saveJsonFile(const fs::path& filePath) const;

protected:
   void registerParameter(const Parameter& parameter);

   const Parameter& getParameter(const std::string& ident) const;

   bool setParameter(const std::string& ident, Parameter::ValueType value);
   bool setParameter(const std::string& ident, const std::string& value);

   const std::string& getStringParameter(const std::string& ident) const;
   const fs::path& getPathParameter(const std::string& ident) const;

   std::vector<Parameter> m_params;
};

///////////////////////////////////////////////////////////////////////////

// Codepage: UTF-8 (ÜüÖöÄäẞß)
