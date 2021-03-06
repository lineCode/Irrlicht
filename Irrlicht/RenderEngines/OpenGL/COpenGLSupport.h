/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2016 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __OPENGLSUPPORT_H__
#define __OPENGLSUPPORT_H__

#ifdef _IRR_COMPILE_WITH_OPENGL_
#include <string>

#define GLEW_STATIC 1

#if defined(_IRR_OPENGL_USE_EXTPOINTER_)
#define GL_GLEXT_LEGACY 1
#else
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/glew.h>

#include "IrrCompileConfig.h"

#ifdef _IRR_WINDOWS_API_
// include windows headers for HWND
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/gl.h>
#ifdef _MSC_VER
#pragma comment(lib, "OpenGL32.lib")
#endif
#elif defined(_IRR_OSX_PLATFORM_)
#include <OpenGL/gl.h>
#elif defined(_IRR_COMPILE_WITH_SDL_DEVICE_)
#define NO_SDL_GLEXT
#include <SDL/SDL_video.h>
#include <SDL/SDL_opengl.h>
#else
#if defined(_IRR_OSX_PLATFORM_)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#endif

#ifdef _WIN32
#include <GL/wglew.h>
#else
#include <GL/glxew.h>
#include <GL/glext.h>
#endif

#ifndef APIENTRY
#define APIENTRY
#endif

#define SAFE_BUFFER_DELETE(x)               \
	if(x)				                    \
		Driver->extGlDeleteBuffers(1, &x); 	\
	x = 0;

#endif
#endif // OGRE_GLSUPPORT_H
