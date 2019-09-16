#pragma once

#include <chrono>

class MethodTimer
{
public:
	explicit MethodTimer(const char* label = nullptr);
	~MethodTimer();

private:
	std::chrono::time_point<std::chrono::steady_clock> m_time;
	std::string m_label;
};

