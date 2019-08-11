#pragma once


class MethodTimer
{
public:
	explicit MethodTimer();
	explicit MethodTimer(std::string label);
	~MethodTimer();

private:
	std::chrono::time_point<std::chrono::steady_clock> m_time;
	std::string m_label;
};

