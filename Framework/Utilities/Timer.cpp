/*
 * Timer.cpp
 *
 *  Created on: 23 mar 2014
 *      Author: Drhugo
 */

#include "Timer.h"
#include <time.h>
namespace Framework {

	Timer::Timer(const unsigned int priority)
	: Task(priority)
		, m_timeLastFrame(0)
		, m_frameDt(0.0f)
		, m_simDt(0.0f)
		, m_simMultiplier(1.0f)
	{

	}

	bool Timer::Start()
	{
		m_timeLastFrame = nanoTime();
		return true;
	}

	void Timer::OnResume()
	{
		m_timeLastFrame = nanoTime();
	}

	void Timer::OnSuspend()
	{

	}

	void Timer::Update()
	{
		TimeUnits currentTime = nanoTime();
		const float MULTIPLIER = 0.000000001f;
		m_frameDt = (currentTime - m_timeLastFrame) * MULTIPLIER;
		m_timeLastFrame = currentTime;
		m_simDt = m_frameDt * m_simMultiplier;
	}
	void Timer::Stop()
	{

	}
	Timer::TimeUnits Timer::nanoTime()
	{
		timespec now;
		int err = clock_gettime(CLOCK_MONOTONIC, &now);
		return now.tv_sec*1000000000L + now.tv_nsec;
	}

	Timer::~Timer() {

	}

} /* namespace Framework */
