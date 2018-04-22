// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENCV_GLUT_DETAIL_CONFIG_HPP
#define INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENCV_GLUT_DETAIL_CONFIG_HPP

#ifdef __APPLE__
#   include "TargetConditionals.h"
#   ifdef TARGET_OS_MAC
extern "C" {
#       include <GLUT/glut.h>
}
#   endif
#elif defined(_WIN32)
#   define NOMINMAX
#   include <windows.h>
extern "C" {
#   include <GL/gl.h> 
#   include <GL/glut.h>
}
#elif defined(__linux__)
extern "C" {
#   include <GL/glut.h>
}
#endif

#endif
