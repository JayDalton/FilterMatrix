#pragma once

#include <string>
#include <string_view>
#include <variant>

#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <numeric>

using namespace std::string_literals;

struct Parameter
{
	std::string m_ident;
	std::string m_label;
};

struct Unsigned : public Parameter
{
	using Type = std::uint32_t;
	static constexpr const char* m_label{ "unsigned" };

	Unsigned(std::string_view ident, std::string_view label,
		Type min = 0, Type max = 100, Type standard = 0)
		: Parameter{ ident.data(), label.data() }, m_minimum(min), m_maximum(max)
		, m_default(standard), m_current(standard)
	{
	}

	Type m_minimum{ std::numeric_limits<Type>::min() };
	Type m_maximum{ std::numeric_limits<Type>::max() };
	Type m_default{};
	Type m_current{};
};

struct Integer : public Parameter
{
	using Type = std::int32_t;
	static constexpr const char* m_label{ "integer" };

	Integer(std::string_view ident, std::string_view label, 
		Type min = 0, Type max = 100, Type standard = 0)
		: Parameter{ ident.data(), label.data() }, m_minimum(min), m_maximum(max)
		, m_default(standard), m_current(standard)
	{
	}

	Type m_minimum{ std::numeric_limits<Type>::min() };
	Type m_maximum{ std::numeric_limits<Type>::max() };
	Type m_default{};
	Type m_current{};
};

struct Single : public Parameter
{
	using Type = float;
	static constexpr const char* m_label{ "single" };

	Single(std::string_view ident, std::string_view label,
		Type min = 0, Type max = 100, Type standard = 0)
		: Parameter{ ident.data(), label.data() }
		, m_minimum(min), m_maximum(max)
		, m_default(standard), m_current(standard)
	{
	}

	Type m_minimum{ std::numeric_limits<Type>::min() };
	Type m_maximum{ std::numeric_limits<Type>::max() };
	Type m_default{};
	Type m_current{};
};

struct Double : public Parameter
{
	using Type = double;
	static constexpr const char* m_label{ "integer" };

	Double(std::string_view ident, std::string_view label,
		Type min = 0, Type max = 100, Type standard = 0)
		: Parameter{ ident.data(), label.data() }
		, m_minimum(min), m_maximum(max)
		, m_default(standard), m_current(standard)
	{
	}

	Type m_minimum{ std::numeric_limits<Type>::min() };
	Type m_maximum{ std::numeric_limits<Type>::max() };
	Type m_default{};
	Type m_current{};
};

struct String : public Parameter
{
	using Type = std::string;
	using Size = std::uint32_t;
	static constexpr const char* m_label{ "string" };

	String(std::string_view ident, std::string_view label,
		Type standard, Size min = 0, Size max = 1000)
		: Parameter{ ident.data(), label.data() }, m_minimum(min), m_maximum(max)
		, m_default(standard), m_current(standard)
	{
	}

	const Size m_minimum{};
	const Size m_maximum{};
	const Type m_default{};
	Type m_current{};
};

struct Boolean : public Parameter
{
	static constexpr const char* m_type{ "boolean" };

	Boolean(std::string_view ident, std::string_view label, bool standard)
		: Parameter{ ident.data(), label.data() }
		, m_default(standard), m_current(standard)
	{
	}

	bool m_default{};
	bool m_current{};
};

struct Configuration
{
	using ConfigValue = std::variant<std::monostate, bool, int, double, std::string>;
	std::string m_name;
	ConfigValue m_value;

	void registerString(
		std::string_view nameOfParam,
		std::string_view description,
		std::uint32_t maxLength
	);

	void registerDouble(
		std::string_view nameOfParam,
		std::string_view description,
		double min, double max,
		double defaultValue
	);

	void registerInteger(
		std::string_view nameOfParam,
		std::string_view description,
		std::int32_t min, std::int32_t max,
		std::int32_t defaultValue
	);

	void registerBoolean(
		std::string_view nameOfParam,
		std::string_view description
	);

	std::map<std::string, ConfigValue> m;
};

struct FilterConfig : public Configuration
{
	double getValue1() const;

	unsigned getValue2() const;

	std::string getValue3() const;


};

