#pragma once

#include <variant>

template<typename ... Base>
struct Visitor : Base ...
{
	using Base::operator()...;
};

template<typename ... T> Visitor(T...)->Visitor<T...>;

struct ValueVisitor
{
	void test()
	{
		constexpr Visitor visitor{
			[](double d) -> double { return d + 3.4; },
			[](int i) -> int { return i - 2; }
		};

		constexpr auto v = std::variant<double, int>{ 9.0 };
		//constexpr auto result = std::visit(visitor, v);
	}
};

