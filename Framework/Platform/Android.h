/*
 * Android.h
 *
 *  Created on: 21 mar 2014
 *      Author: Drhugo
 */

#ifndef ANDROID_H_
#define ANDROID_H_

#include <android_native_app_glue.h>
#include "../Kernel/Task.h"


namespace Framework {

	class Android
	//Inherits
		: public Task
	{
	private:
			static bool 	m_bClosing;
			static bool 	m_bPaused;
			android_app		*m_pState;

	public:
		 Android(android_app* p_State, const unsigned int priority);
		 virtual ~Android();

		android_app* 	GetAppState() 				{ return m_pState;    }

		virtual bool 	Start();
		virtual void	OnSuspend();
		virtual void	Update();
		virtual void	OnResume();
		virtual void	Stop();

		static void ClearClosing()					{ m_bClosing = false; }
		static void SetPaused(const bool paused) 	{ m_bPaused = paused; }
		static bool IsClosing()						{ return m_bClosing;  }
		static bool IsPaused()						{ return m_bPaused;	  }

	};

} /* namespace Framework */
#endif /* ANDROID_H_ */
