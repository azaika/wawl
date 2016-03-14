#pragma once
#define ENABLER_WAWL_FILESYSTEM

#include "File.hpp"
#include "Console.hpp"
#include "Process.hpp"

namespace wawl {
	namespace fs {

		// ToDo: move to other file
		inline FileHandle openNamedPipe(
			const Tstring& pipeName,
			SimpleAccessDesc accessMode
			) {
			return ::CreateFile(
				pipeName.c_str(),
				unpackEnum(accessMode),
				0,
				nullptr,
				OPEN_EXISTING,
				0,
				0
				);
		}

	} // ::wawl::fs
} // ::wawl