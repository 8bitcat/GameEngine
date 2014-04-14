#ifndef KERNEL_H_
#define KERNEL_H_

#include <list>
#include "Task.h"

namespace Framework {

	class Kernel
	{

		private:
			typedef std::list<Task*>			TaskList;
			typedef std::list<Task*>::iterator	TaskListIterator;

			TaskList m_tasks;
			TaskList m_pausedTasks;

			void PriorityAdd(Task *pTask);

		public:
			Kernel();
			virtual ~Kernel();

			void 	Execute();
			bool	AddTask(Task *pTask);
			void 	SuspendTask(Task *pTask);
			void 	ResumeTask(Task *pTask);
			void	RemoveTask(Task *pTask);
			void 	KillAllTasks();

			bool 	HasTasks() { return m_tasks.size();	}

	};

} /* namespace Framework */
#endif /* KERNEL_H_ */
