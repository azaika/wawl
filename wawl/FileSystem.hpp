#pragma once
#define ENABLER_WAWL_FILESYSTEM

#include "File.hpp"
#include "Pipe.hpp"
#include "Console.hpp"
#include "Process.hpp"

namespace wawl {
	namespace fs {
        
        // result of findFile which contains file data
		using FileInfo = WIN32_FIND_DATA;
        
        // file search handle
		using SearchHandle = Handle;

		inline SearchHandle findFile(const Tstring& fileName, FileInfo& info) {
			return ::FindFirstFile(fileName.c_str(), &info);
		}
		inline bool findNextFile(Handle searchHandle, FileInfo& info) {
			return ::FindNextFile(searchHandle, &info) != 0;
		}

		inline bool closeSearchHandle(SearchHandle handle) {
			return ::FindClose(handle) != 0;
		}
        
        // get system temporary directory path
		inline bool getTempDirPath(Tstring& buf) {
			buf.resize(MAX_PATH);
			buf.resize(::GetTempPath(static_cast<Uint32>(buf.size()), &buf[0]));
			return buf.size() != 0;
		}
        
        // get current directory path of this process
		inline bool getCurrentDirPath(Tstring& buf) {
			buf.resize(MAX_PATH);
			buf.resize(::GetCurrentDirectory(static_cast<Uint32>(buf.size()), &buf[0]));
			return buf.size() != 0;
		}
        
        // get system32 directory path
		inline bool getSystemDirPath(Tstring& buf) {
			buf.resize(MAX_PATH);
			buf.resize(::GetSystemDirectory(&buf[0], static_cast<Uint>(buf.size())));
			return buf.size() != 0;
		}
        
        // get Windows directory path of local user
		inline bool getWindowsDirPath(Tstring& buf) {
			buf.resize(MAX_PATH);
			buf.resize(::GetWindowsDirectory(&buf[0], static_cast<Uint>(buf.size())));
			return buf.size() != 0;
		}
        
        // get common Windows directory path of all user
		inline bool getSystemWindowsDirPath(Tstring& buf) {
			buf.resize(MAX_PATH);
			buf.resize(::GetSystemWindowsDirectory(&buf[0], static_cast<Uint>(buf.size())));
			return buf.size() != 0;
		}

		inline bool createDir(const Tstring& path) {
			return ::CreateDirectory(path.c_str(), nullptr) != 0;
		}
		inline bool createDir(const Tstring& path, const SecurityAttr& secAttr) {
			return ::CreateDirectory(path.c_str(), const_cast<SecurityAttr*>(&secAttr)) != 0;
		}

		inline bool removeDir(const Tstring& path) {
			return ::RemoveDirectory(path.c_str()) != 0;
		}

	} // ::wawl::fs
} // ::wawl