#pragma once
#define ENABLE_WAWL_ALL

#include "WawlBase.hpp"
#include "Input.hpp"
#include "FileSystem.hpp"
#include "Window.hpp"
#include "Region.hpp"
#include "MessageBox.hpp"
#include "System.hpp"

#ifdef _USRDLL
#define WawlMain DllMain
#else // _USRDLL
#define WawlMain _tWinMain
#endif // _USRDLL