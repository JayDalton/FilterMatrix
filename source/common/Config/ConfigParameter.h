#pragma once

#include <string>

/*

<Config>
  <Parameter type="integer" name="">...</Parameter>

</Config>

*/


//struct ConfigParameter
//{
//	const enum class Type
//	{
//		String,
//		Double,
//		Integer,
//		Boolean,
//		Listing,
//		Signed,
//		Unsinged,
//		Enumeration,
//		Configuration,
//	};
//
//	Type getType() const;
//	const std::string& getName() const;
//	std::string getDescription() const;
//
//	virtual void reset() = 0;
//
//	virtual Parameter* createCopy() const = 0;
//
//	bool fromXml(const QDomNodeList& nodeList);
//	virtual void fromXml(const QDomNodeList& nodeList, int index) = 0;
//	virtual void toXml(QDomElement& parentNode) const = 0;
//
//	virtual QString getValueAsString() const = 0;
//	virtual bool isValid() const;
//
//	QString getTypeAsSting() const;
//	virtual bool hasType(const QString& typeString) const;
//
//	void setSupportedSuffixSet(const QSet<QString>& supportedSuffixSet);
//	bool isSuffixSupported(const QString& suffix) const;
//	virtual bool setActiveValueSuffix(const QString& suffix);
//	QString getActiveValueSuffix() const;
//
//	bool operator==(const ConfigParameter& other) const;
//	bool operator!=(const ConfigParameter& other) const;
//
//	virtual ~ConfigParameter();
//
//protected:
//	Parameter(const Type type,
//		const QString& typeString,
//		const QString& name,
//		const QString& description,
//		bool hide = false);
//	Parameter(const Parameter& other);
//
//	const Type m_type;
//	const std::string m_name;
//	const QString m_typeString;
//	const std::string m_description;
//};
//
////////////////////////////////////////////////////////////////////////////
//
//class ParameterConfig : public Config
//{
//public:
//	ParameterConfig(Parameter::Type type);
//
//	QString getName() const;
//	QString getDescription() const;
//	Parameter::Type getType() const;
//	bool isHidden() const;
//	QString getSuffix() const;
//
//	ParameterConfig* getParameterConfigFromType(Parameter::Type type) const;
//	ParameterConfig* getParameterConfigFromParameter(const Parameter& parameter) const;
//
//	virtual void setParameterData(const Parameter& parameter);
//	virtual Parameter* createParameter() const = 0;
//
//protected:
//	void updateParameterSuffix(Parameter& parameter) const;
//
//private:
//	static const QString PARAMETER_NAME;
//	static const QString PARAMETER_DESCRIPTION;
//	static const QString PARAMETER_TYPE;
//	static const QString PARAMETER_HIDE;
//	static const QString PARAMETER_SUFFIX;
//
//	std::string m_;
//};

