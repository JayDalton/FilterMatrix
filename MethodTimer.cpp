#include "pch.h"

#include <iostream>

#include "MethodTimer.h"

MethodTimer::MethodTimer()
	: m_time(std::chrono::steady_clock::now())
{

}

MethodTimer::MethodTimer(std::string label)
	: m_time(std::chrono::steady_clock::now())
	, m_label(label)
{
}

MethodTimer::~MethodTimer()
{
	const auto duration = std::chrono::steady_clock::now() - m_time;
	const auto millisecs = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	std::cout << m_label.empty() ? "Method" : m_label;
	std::cout << " took " << millisecs.count() << " ms" << std::endl;
}

