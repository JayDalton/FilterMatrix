#include "precompheader.h"

#include "Configuration.h"

struct ReadHandler 
{
   // Handler API
   bool Null() { logger::info("Null()"); return true; }
   bool Int64(int64_t i) { logger::info("Int64({})", i); return true; }
   bool Uint64(uint64_t u) { logger::info("UInt64({})", u); return true; }
   bool RawNumber(const char* str, json::SizeType length, bool copy) { 
      logger::info("Number({0}, {1}, {2})", str, length, copy); return true;
   }

   bool Bool(bool b) { 

      //auto& param = m_params.back();
      //if (std::holds_alternative<bool>(param))
      //{
      //   return std::get<bool>(param);
      //}


      m_params.back().emplace<BaseParameter>();
      //m_params.back().m_current = b;
      logger::info("Bool({})", b); 
      return true; 
   }
   
   bool Int(signed i) { 
      //m_params.back().m_current = i;
      logger::info("Int({})", i); 
      return true; 
   }
   bool Uint(unsigned u) { 
      //m_params.back().m_current = u;
      logger::info("Uint({})", u); 
      return true; 
   }
   
   bool Double(double d) { 
      //m_params.back().m_current = d;
      logger::info("Double({})", d); 
      return true; 
   }

   bool Key(const char* str, json::SizeType length, bool copy) {
      logger::info("Key({0}, {1}, {2})", str, length, copy); 
      m_params.emplace_back(BaseParameter{ 
         std::string{str, length}, 
         std::string{str, length} 
         });
      return true;
   }

   bool String(const char* str, json::SizeType length, bool copy) { 
      //m_params.back().m_current = std::string{str, length};
      logger::info("String({0}, {1}, {2})", str, length, copy); 
      return true;
   }
   
   bool StartObject() { logger::info("StartObject()"); return true; }
   bool EndObject(json::SizeType count) { 
      logger::info("EndObject({})", count); return true; 
   }
   
   bool StartArray() { logger::info("StartArray()"); return true; }
   bool EndArray(json::SizeType count) { 
      logger::info("EndArray({})", count); 
      return true; 
   }

   const ParameterListing& getParameters() const { return m_params; }

private:
   ParameterListing m_params;
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

   ReadHandler handler;
   json::Reader reader;
   json::IStreamWrapper wrapper(stream);
   if (!reader.Parse(wrapper, handler))
   {
      logger::info("config json file parse error");
      return false;
   }

   const auto& params{ handler.getParameters() };
   //m_params.assign(params.cbegin(), params.cend());
   //for (const auto& param : handler.getParameters())
   //{
   //   param.m_ident;
   //   param.m_label;
   //}

   //json::Document document;
   ////json::IStreamWrapper isw(stream);
   //document.ParseStream(wrapper);
   //if (document.HasParseError())
   //{
   //   logger::info("config json file parse error");
   //   return false;
   //}
   //
   //for (const auto& member : document.GetObject())
   //{
   //   member.name;
   //   member.value;
   //   logger::debug("json member: {0} : {1}", 
   //      member.name.GetString(),
   //      member.value.GetString()
   //   );
   //}
   return false;
}

bool Configuration::saveJsonFile(const fs::path& filePath) const
{
   json::StringBuffer buffer;
   json::PrettyWriter<json::StringBuffer> writer(buffer);

   auto write = [&writer](const auto& value) { value.Serialize(writer); };

   writer.StartObject();
   //writer.Key("Ident");
   //writer.String(m_ident);
   //writer.Key("Label");
   //writer.String(m_label);

   for (const auto& keyValue : m_paramMap)
   {
      std::visit(write, keyValue.second);
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

void Configuration::registerBaseParameter(const BaseParameter& parameter)
{
   m_paramMap.insert_or_assign(parameter.m_ident, parameter);
}

void Configuration::registerListParameter(const ListParameter& parameter)
{
   m_paramMap.insert_or_assign(parameter.m_ident, parameter);
}

const ParameterVariant& Configuration::getParameter(const std::string& ident) const
{
   if (m_paramMap.contains(ident))
   {
      return m_paramMap.at(ident);
   }

   assert(false);
   return m_paramMap.at(0);
}

const BaseParameter& Configuration::getBaseParameter(const std::string& ident) const
{
   const ParameterVariant& param = getParameter(ident);
   if (std::holds_alternative<BaseParameter>(param))
   {
      return std::get<BaseParameter>(param);
   }

   assert(false);
   return std::get<BaseParameter>(param);
}

const ListParameter& Configuration::getListParameter(const std::string& ident) const
{
   const ParameterVariant& param = getParameter(ident);
   if (std::holds_alternative<ListParameter>(param))
   {
      return std::get<ListParameter>(param);
   }

   assert(false);
   return std::get<ListParameter>(param);
}

bool Configuration::setParameter(const std::string& ident, BaseParameter::ValueType value)
{
   //auto found = std::find_if(m_params.begin(), m_params.end(), 
   //   [&ident](const auto& param) { return param.m_ident == ident; }
   //);

   //if (found != m_params.end())
   //{
   //   //found->m_current = value;
   //   return true;
   //}

   //if (m_paramMap.contains(ident))
   //{
   //   m_paramMap.at(ident) /*= value*/;
   //}

   assert(false);
   return false;
}

bool Configuration::setParameter(const std::string& ident, const std::string& value)
{
   //auto found = std::find_if(m_params.begin(), m_params.end(), 
   //   [&ident](const auto& param) { return param.m_ident == ident; }
   //);

   //if (found != m_params.end())
   //{
   //   //found->m_current.emplace<std::string>(value);
   //   return true;
   //}

   assert(false);
   return false;
}

const std::string& Configuration::getStringParameter(const std::string& ident) const
{
   const BaseParameter& param = getBaseParameter(ident);
   if (std::holds_alternative<std::string>(param.m_current))
   {
      return std::get<std::string>(param.m_current);
   }

   assert(false);
   return std::get<std::string>(param.m_current);
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
