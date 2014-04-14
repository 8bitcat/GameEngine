/*
 * Renderer.h
 *
 *  Created on: 25 mar 2014
 *      Author: Drhugo
 */
#ifndef RENDERER_H_
#define RENDERER_H_

#include  "../Kernel/Task.h"
#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <Renderable.h>
#include <stl/_vector.h>

namespace Framework {

	class Renderer : Task
	{

		private:
		typedef std::vector<Renderable*>		RenderableVector;
		typedef RenderableVector::iterator	RenderableVectorIterator;
		RenderableVector	m_renderables;
		android_app* 		m_pState;
		EGLDisplay			m_display;
		EGLContext			m_context;
		EGLSurface			m_surface;
		int 				m_height;
		int 				m_width;
		bool				m_initialized;



		public:
		void AddRenderable(Renderable * pRenderable);
		void RemoveRenderable(Renderable * pRenderable);
		void Draw(Renderable * pRenderable);
		explicit Renderer(android_app *pState, const unsigned int priority);
		virtual ~Renderer();
		void Init();
		void Destroy();

		//Inherited from Task
		virtual bool 		Start();
		virtual void 		OnSuspend();
		virtual void 		Update();
		virtual void 		OnResume();
		virtual void 		Stop();

		bool IsInitialized() { return m_initialized; }

	};

} /* namespace Framework */
#endif /* RENDERER_H_ */
