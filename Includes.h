#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#pragma once

#pragma warning(disable : 26812)
#pragma warning(disable : 4091 ) // 'typedef ': ignored on left of 'sizebuf_s' when no variable is declared

#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <deque>
#include <TlHelp32.h>
#include <algorithm>
#include <corecrt_io.h> // _access
#include <filesystem> // std::filesystem
#include <mutex> // std::mutex
#include <functional> // std::function
#include <chrono> // std::chrono
#include <array>
#include <fstream>
#include <string>
#include <sstream>

// @todo: Maybe do something with preprocessor to not include this all time?
#include <conio.h>

/// 3rdParty ///
// OpenGL
#include <GL/glew.h>
// Detours
#include <detours/detours.h>
// ImGUI
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/impl/imgui_impl_opengl2.h>
#include <imgui/impl/imgui_impl_win32.h>
// Soil
#include <soil/SOIL2.h>

#undef VOID
using VOID = void;

// Our files
#include "Defines.h"
#include "CCodeMeasurement.h"
#include "main.h"
#include "CKeyboardEvent.h"
#include "CImGUI.h"

#endif
