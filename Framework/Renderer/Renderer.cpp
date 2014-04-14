/*
 * Renderer.cpp
 *
 *  Created on: 25 mar 2014
 *      Author: Drhugo
 */

#include "Renderer.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <cassert>
#include "Renderable.h"
#include "Geometry/Geometry.h"
//#include "Textures/Texture.h"
#include "Shader/Shader.h"
namespace Framework {

	Renderer::Renderer(android_app *pState, const unsigned int priority) {
	// TODO Auto-generated constructor stub

	}

	Renderer::~Renderer() {
		// TODO Auto-generated destructor stub
	}

	void Renderer::Init()
	{
		//This method is used to initialize OpenGL ES and EGL

		//**** SPECIFY ATTRIBUTES AND CONFIGURATION
		//COLORS ARE SET TO MINUMUM EIGHT BITS PER COLOR COMPONENT

		const EGLint attributes[] =
		{
				EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
				EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
				EGL_BLUE_SIZE, 8,
				EGL_GREEN_SIZE, 8,
				EGL_RED_SIZE, 8,
				EGL_NONE
		};

		EGLint 		format;
		EGLint 		numConfigs;
		EGLConfig  	config;
		//Get the display
		m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		//Initialize display
		eglInitialize(m_display, NULL, NULL);

		//Choose EGL config pick first config that matches pur criterias!
		eglChooseConfig(m_display,attributes,&config,1,&numConfigs);
		/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is guaranteed to be accepted by
		ANativeWindow_setBuffersGeometry(). As soon as we pick a EGLConfig, we can safely reconfigure the
		ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */

		eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);
		ANativeWindow_setBuffersGeometry(m_pState->window,0,0,format);
		m_surface = eglCreateWindowSurface(m_display,config,m_pState->window, NULL);

		EGLint contextAttributes[] =
		{
				EGL_CONTEXT_CLIENT_VERSION, 2,
				EGL_NONE
		};

		m_context = eglCreateContext(m_display,config,NULL,contextAttributes);
		eglMakeCurrent(m_display,m_surface,m_surface,m_context)

		eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_width);
		eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_width);

		m_initialized = true;
	}

	void Renderer::Draw(Renderable *pRenderable)
	{
		assert(pRenderable);
		if(pRenderable)
		{

			Geometry *pGeometry	= pRenderable->GetGeometry();
			Shader   *pShader = pRenderable->GetShader();

			assert(pShader && pGeometry);

			pShader->Setup(*pRenderable);

			glDrawElements(GL_TRIANGLES,
						   pGeometry->GetNumIndices(),
						   GL_UNSIGNED_SHORT,
						   pGeometry->GetIndexBuffer());



		}


	}
	void Renderer::AddRenderable(Renderable *pRenderable)
	{
		m_renderables.push_back(pRenderable);

	}

	void Renderer::RemoveRenderable(Renderable * pRenderable)
	{
		for(RenderableVectorIterator iter = m_renderables.begin();
			iter != m_renderables.end(); ++iter)
		{
			Renderable *pCurrent = *iter;
			if(pCurrent == pRenderable)
			{
				m_renderables.erase(iter);
				break;
			}
		}
	}

	void Renderer::Destroy()
	{
		m_initialized = false;

		if(m_display != EGL_NO_DISPLAY)
		{
			eglMakeCurrent(m_display, EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);

			if(m_context != EGL_NO_CONTEXT)
			{
				eglDestroyContext(m_display,m_context);
			}
			if(m_surface != EGL_NO_SURFACE)
			{
				eglDestroySurface(m_display,m_surface);
			}
			eglTerminate(m_display);

			m_context = EGL_NO_CONTEXT;
			m_display = EGL_NO_DISPLAY;
			m_surface = EGL_NO_SURFACE;
		}
	}

	bool Renderer::Start()
	{
		return true;
	}

	void Renderer::OnSuspend()
	{

	}

	void Renderer::Update()
	{
		if(m_initialized)
		{
			glClearColor(0.95f, 0.95f, 0.95f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for(RenderableVectorIterator iter = m_renderables.begin();
					iter != m_renderables.end(); ++iter)
			{
				Renderable *pRenderable = *iter;
				if(pRenderable)
				{
					Draw(pRenderable);
				}
			}
			eglSwapBuffers(m_display,m_surface);
		}
	}
	v

	void Renderer::OnResume()
	{

	}
	void Renderer::Stop()
	{

	}

} /* namespace Framework */
