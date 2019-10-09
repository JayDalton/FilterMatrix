#pragma once

#include "Config/Parameter.h"

/////////////////////////////////////////////////////////////////////////////

struct Configuration
{
   std::string m_ident;
   std::string m_label;

   bool loadJsonFile(const fs::path& filePath);
   bool saveJsonFile(const fs::path& filePath) const;

protected:
   void registerBaseParameter(const BaseParameter& parameter);
   void registerListParameter(const ListParameter& parameter);

   const ParameterVariant& getParameter(const std::string& ident) const;
   const BaseParameter& getBaseParameter(const std::string& ident) const;
   const ListParameter& getListParameter(const std::string& ident) const;

   bool setParameter(const std::string& ident, BaseParameter::ValueType value);
   bool setParameter(const std::string& ident, const std::string& value);

   const std::string& getStringParameter(const std::string& ident) const;
   const fs::path& getPathParameter(const std::string& ident) const;

private:
   ParameterMapping m_paramMap;
};

///////////////////////////////////////////////////////////////////////////

// Codepage: UTF-8 (ÜüÖöÄäẞß)
