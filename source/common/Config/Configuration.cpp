#include "precompheader.h"

#include "Configuration.h"

struct MyHandler {
   bool Null() { logger::info("Null()"); return true; }
   bool Bool(bool b) { logger::info("Bool({})", b); return true; }
   bool Int(signed i) { logger::info("Int({})", i); return true; }
   bool Uint(unsigned u) { logger::info("Uint({})", u); return true; }
   bool Int64(int64_t i) { logger::info("Int64({})", i); return true; }
   bool Uint64(uint64_t u) { logger::info("UInt64({})", u); return true; }
   bool Double(double d) { logger::info("Double({})", d); return true; }

   bool RawNumber(const char* str, json::SizeType length, bool copy) { 
      logger::info("Number({0}, {1}, {2})", str, length, copy); return true;
   }
   bool String(const char* str, json::SizeType length, bool copy) { 
      logger::info("String({0}, {1}, {2})", str, length, copy); return true;
   }
   bool StartObject() { logger::info("StartObject()"); return true; }
   bool Key(const char* str, json::SizeType length, bool copy) {
      logger::info("Key({0}, {1}, {2})", str, length, copy); return true;
   }
   bool EndObject(json::SizeType memberCount) { 
      logger::info("EndObject({})", memberCount); return true; 
   }
   bool StartArray() { logger::info("StartArray()"); return true; }
   bool EndArray(json::SizeType elementCount) { 
      logger::info("EndArray({})", elementCount); return true; 
   }
};

bool Configuration::loadJsonFile(const fs::path& filePath)
{
   if (!fs::exists(filePath))
   {
      logger::info("config json file not existing");
      return false;
   }

   std::ifstream stream(filePath, std::ios::binary);
   if (!stream)
   {
      logger::info("config json file can not read");
      return false;
   }

   //MyHandler handler;
   //json::Reader reader;
   //json::IStreamWrapper isw(stream);
   //if (!reader.Parse(isw, handler))
   //{
   //   return false;
   //}

   json::Document document;
   json::IStreamWrapper isw(stream);
   document.ParseStream(isw);
   if (document.HasParseError())
   {
      logger::info("config json file parse error");
      return false;
   }
   
   for (const auto& member : document.GetObject())
   {
      member.name;
      member.value;
      logger::debug("json member: {0} : {1}", 
         member.name.GetString(),
         member.value.GetString()
      );
   }
}

bool Configuration::saveJsonFile(const fs::path& filePath) const
{
   json::StringBuffer buffer;
   json::PrettyWriter<json::StringBuffer> writer(buffer);

   auto output = overload
   {
      [&writer](bool b) { writer.Bool(b); },
      [&writer](float b) { writer.Double(b); },
      [&writer](double b) { writer.Double(b); },
      [&writer](signed int si) { writer.Int(si); },
      [&writer](unsigned int ui) { writer.Uint(ui); },
      [&writer](const std::string& s) { writer.String(s); },
      [&writer](const fs::path& p) { writer.String(p.string()); },
      [&writer](const Parameter::ValueList& p) 
      { 
         writer.StartArray();
         for (const auto& value : p)
         {
            writer.Key(value.m_ident.data());
            //std::visit(output, value.m_current); // recursive call
            writer.String(value.m_label.data());
         }
         writer.EndArray();
      },
   };

   writer.StartObject();
   //writer.Key("Ident");
   //writer.String(m_ident);
   //writer.Key("Label");
   //writer.String(m_label);

   for (const Parameter& param : m_params)
   {
      writer.Key(param.m_ident.data());
      std::visit(output, param.m_current);
   }
   writer.EndObject();

   if (!fs::exists(filePath))
   {
      fs::create_directories(filePath.parent_path());
   }

   if (auto stream = std::ofstream(filePath, std::ios::binary))
   {
      stream << buffer.GetString() << std::endl;
      return true;
   }

   return false;
}

void Configuration::registerParameter(const Parameter& parameter)
{
   m_params.emplace_back(parameter);
}

const Parameter& Configuration::getParameter(const std::string& ident) const
{
   auto found = std::find_if(m_params.begin(), m_params.end(), 
      [&ident](const Parameter& param) { return param.m_ident == ident; }
   );

   if (found != m_params.end())
   {
      return *found;
   }

   assert(false);
   return {};
}

bool Configuration::setParameter(const std::string& ident, Parameter::ValueType value)
{
   auto found = std::find_if(m_params.begin(), m_params.end(), 
      [&ident](const Parameter& param) { return param.m_ident == ident; }
   );

   if (found != m_params.end())
   {
      found->m_current = value;
      return true;
   }

   assert(false);
   return false;
}

bool Configuration::setParameter(const std::string& ident, const std::string& value)
{
   auto found = std::find_if(m_params.begin(), m_params.end(), 
      [&ident](const Parameter& param) { return param.m_ident == ident; }
   );

   if (found != m_params.end())
   {
      found->m_current.emplace<std::string>(value);
      return true;
   }

   assert(false);
   return false;
}

const std::string& Configuration::getStringParameter(const std::string& ident) const
{
   const auto& param = getParameter(ident);
   if (std::holds_alternative<std::string>(param.m_current))
   {
      return std::get<std::string>(param.m_current);
   }

   assert(false);
   return {};
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
