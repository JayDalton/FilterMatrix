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
   json::StringBuffer buffer;
   json::PrettyWriter<json::StringBuffer> writer(buffer);

   auto output = overload
   {
      [&writer](bool b) { writer.Bool(b); },
      [&writer](float b) { writer.Double(b); },
      [&writer](double b) { writer.Double(b); },
      [&writer](signed int si) { writer.Int(si); },
      [&writer](unsigned int ui) { writer.Uint(ui); },
      [&writer](const std::string& s) { writer.String(s.data()); },
      [&writer](const fs::path& p) { writer.String(p.string().data()); },
   };

   writer.StartObject();
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

   //// Prepare reader and input stream.
   //Reader reader;
   //char readBuffer[65536];
   //FileReadStream is(stdin, readBuffer, sizeof(readBuffer));

   //// Prepare writer and output stream.
   //char writeBuffer[65536];
   //json::FileWriteStream os(stdout, writeBuffer, sizeof(writeBuffer));
   //json::PrettyWriter<json::FileWriteStream> writer(os);


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

   //m_map.emplace(std::make_pair("", parameter));
}

const Parameter& Configuration::getParameter(const std::string& paramName) const
{
   // TODO: insert return statement here
   auto found = std::find_if(m_params.begin(), m_params.end(), 
      [&paramName](const Parameter& param) {
         return param.m_ident == paramName;
      }
   );

   if (found != m_params.end())
   {
      return *found;
   }

   return {};
}

ParameterOpt Configuration::getParameterOpt(const std::string& paramName) const
{
   auto found = std::find_if(m_params.begin(), m_params.end(), 
      [&paramName](const Parameter& param) {
         return param.m_ident == paramName;
      }
   );

   if (found != m_params.end())
   {
      return *found;
   }

   return {};
}

//void Configuration::registerString(const std::string& nameOfParam, const std::string& description, const std::string& defaultValue, std::size_t maximum, std::size_t minimum)
//{
//
//}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
