#pragma once

#include <variant>
#include <utility>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <iostream>

template<typename... Base>
struct Visitor : Base...
{
	using Base::operator()...;
};

template<typename ... Base> 
Visitor(Base...) -> Visitor<Base...>;

// YouTube: Jason Turner C++ Weekly - Ep 134 - The Best Possible Way To Create A Visitor?

template<class... Ts> 
struct overload : Ts... 
{ 
   using Ts::operator()...; 
};
template<class... Ts> 
overload(Ts...)->overload<Ts...>;

struct ValueVisitor
{
	void test()
	{
		//constexpr Visitor visitor{
		//	[](double d) -> double { return d + 3.4; },
		//	[](int i) -> int { return i - 2; }
		//};

		//constexpr auto v = std::variant<double, int>{ 9.0 };
		//constexpr auto result = std::visit(visitor, v);
	}
};

// https://www.bfilipek.com/2018/06/variant.html

struct SampleVisitor
{
	void operator()(int i) const {
		std::cout << "int: " << i << "\n";
	}
	void operator()(float f) const {
		std::cout << "float: " << f << "\n";
	}
	void operator()(const std::string& s) const {
		std::cout << "string: " << s << "\n";
	}
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
