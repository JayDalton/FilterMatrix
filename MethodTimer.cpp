#include "pch.h"

#include <iostream>

#include "MethodTimer.h"

MethodTimer::MethodTimer(const char* label)
	: m_time(std::chrono::steady_clock::now())
	, m_label(label)
{
}

MethodTimer::~MethodTimer()
{
	const auto duration = std::chrono::steady_clock::now() - m_time;
	const auto millisecs = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	if (m_label.empty())
	{
		std::cout << "Method";
	}
	else
	{
		std::cout << m_label;
	}
	std::cout << " took " << millisecs.count() << " ms" << std::endl;
}

