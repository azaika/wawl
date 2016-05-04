#pragma once
#define ENABLE_WAWL_ALL

#include "WawlBase.hpp"
#include "Input.hpp"
#include "FileSystem.hpp"
#include "Window.hpp"
#include "Region.hpp"
#include "MessageBox.hpp"
#include "System.hpp"
#include "Debug.hpp"

#ifdef _USRDLL
#define WawlMain DllMain
#else // _USRDLL
#define WawlMain WINAPI _tWinMain
#endif // _USRDLL