#pragma once

#include <string>

using Writer = json::PrettyWriter<json::StringBuffer>;

//struct ParameterBase
//{
//   //std::string m_ident;
//   //std::string m_label;
//   //using ValueType = std::variant<
//   //   bool, signed, unsigned, double, 
//   //   std::string, fs::path>;
//   //using ValueList = std::vector<ValueType>;
//};

//class Writer;

struct BaseParameter /*: public ParameterBase*/
{
   using ValueType = std::variant<
      bool, signed, unsigned, double, 
      std::string, fs::path>;

   std::string m_ident;
   std::string m_label;
   ValueType m_current;
   ValueType m_maximum;
   ValueType m_minimum;

   void Serialize(Writer& writer) const;
};

struct ListParameter /*: public ParameterBase*/
{
   using ValueType = std::variant<
      bool, signed, unsigned, double, 
      std::string, fs::path>;

   using ValueList = std::vector<ValueType>;

   std::string m_ident;
   std::string m_label;
   ValueList m_current;

   void Serialize(Writer& writer) const;
};

struct ConfigParameter
{
   std::string m_ident;
   std::string m_label;

   void Serialize(Writer& writer) const;
};

using ParameterVariant = std::variant<BaseParameter, ListParameter>;
using ParameterListing = std::vector<ParameterVariant>;
using ParameterMapping = std::unordered_map<std::string, ParameterVariant>;


// Codepage: UTF-8 (ÜüÖöÄäẞß)

