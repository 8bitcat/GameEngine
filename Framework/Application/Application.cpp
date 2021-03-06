#include "Application.h"

namespace Framework
{
	Application::Application(android_app* state)
	:	m_androidTask(state, Task::PLATFORM_PRIORITY)
		,	m_timerTask(Task::TIMER_PRIORITY)
	{
	}

	Application::~Application()
	{

	}

	bool Application::Initialize()
	{
		bool ret = true;
		//ADD ANDROID TASK TO KERNEL LIST
		m_kernel.AddTask(&m_androidTask);
		//ADD TIMER   TASK TO KERNEL LIST
	    m_kernel.AddTask(&m_timerTask);

		return ret;
	}

	void Application::Run()
	{
		m_kernel.Execute();
	}
}
