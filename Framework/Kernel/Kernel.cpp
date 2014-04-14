/*
 * Kernel.cpp
 *
 *  Created on: 20 mar 2014
 *      Author: Drhugo
 */

#include "Kernel.h"
#include "../Platform/Android.h"

namespace Framework {

	Kernel::Kernel() {
		// TODO Auto-generated constructor stub

	}

	Kernel::~Kernel() {
		// TODO Auto-generated destructor stub
	}

	void Kernel::PriorityAdd(Task *pTask)
	{
		TaskListIterator tIter;

		for (tIter = m_tasks.begin(); tIter != m_tasks.end(); ++tIter)
		{
			Task *pCurrentTask = (*tIter);

			if(pCurrentTask->Priority() > pTask->Priority())
			{
				break;
			}

			m_tasks.insert(tIter,pTask);

		}
	}

	bool Kernel::AddTask(Task * pTask)
	{
		bool started = pTask->Start();

		if(started)
		{
			PriorityAdd(pTask);
		}

		return started;
	}

	void Kernel::RemoveTask(Task *pTask)
	{
		if(std::find(m_tasks.begin(),m_tasks.end(), pTask) != m_tasks.end())
		{
				pTask->SetCanKill(true);
		}
	}

	void Kernel::SuspendTask(Task *pTask)
	{
		if(std::find(m_tasks.begin(),m_tasks.end(),pTask) != m_tasks.end())
		{
			pTask->OnSuspend();
			m_tasks.remove(pTask);
			m_pausedTasks.push_front(pTask);
		}
	}

	void Kernel::ResumeTask(Task *pTask)
	{
		if(std::find(m_pausedTasks.begin(),m_pausedTasks.end(), pTask) != m_pausedTasks.end())
		{
			pTask->OnResume();
			m_pausedTasks.remove(pTask);
			PriorityAdd(pTask);

		}
	}

	void Kernel::KillAllTasks()
	{
		for(TaskListIterator iter = m_tasks.begin(); iter != m_tasks.end(); ++iter)
		{
				(*iter)->SetCanKill(true);
		}
	}

	void Kernel::Execute()
	{
		while(m_tasks.size())
		{
			if(Android::IsClosing())
			{
				KillAllTasks();
			}

			TaskListIterator tIter;

			for(tIter = m_tasks.begin(); tIter != m_tasks.end(); ++tIter)
			{
				Task *pTask = (*tIter);
				++tIter;
				if(!pTask->CanKill())
				{
					pTask->Update();
				}
			}

			for(tIter = m_tasks.begin(); tIter != m_tasks.end();)
			{
				Task *pTask = (*tIter);
				++tIter;
				if(pTask->CanKill())
				{
					pTask->Stop();
					m_tasks.remove(pTask);
					pTask = 0;
				}
			}
		}

		Android::ClearClosing();
	}

} /* namespace Framework */
