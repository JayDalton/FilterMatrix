#include "precompheader.h"

#include "Config/Parameter.h"
#include "Config/ValueVisitor.h"

void BaseParameter::Serialize(Writer& writer) const
{
   auto output = overload
   {
      [&writer](bool b) { writer.Bool(b); },
      [&writer](float b) { writer.Double(b); },
      [&writer](double b) { writer.Double(b); },
      [&writer](signed int si) { writer.Int(si); },
      [&writer](unsigned int ui) { writer.Uint(ui); },
      [&writer](const std::string& s) { writer.String(s); },
      [&writer](const fs::path& p) { writer.String(p.string()); },
      //[&writer](const Parameter::ValueList& values) 
      //{ 
      //   writer.StartArray();
      //   writer.EndArray();
      //},
   };
   writer.Key(m_ident.data());
   std::visit(output, m_current);   // recursive call ???
}

void ListParameter::Serialize(Writer& writer) const
{
   writer.StartArray();
   writer.EndArray();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)