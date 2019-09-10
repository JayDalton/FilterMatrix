#pragma once

#include <variant>
#include <utility>
#include <typeinfo>
#include <type_traits>

template<typename ... Base>
struct Visitor : Base ...
{
	using Base::operator()...;
};

template<typename ... T> Visitor(T...)->Visitor<T...>;

// YouTube: Jason Turner C++ Weekly - Ep 134 - The Best Possible Way To Create A Visitor?

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

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...)->overload<Ts...>;

