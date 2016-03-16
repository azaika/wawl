#pragma once
#define ENABLE_WAWL_PIPE

#include "WawlBase.hpp"
#include "FileBaseType.hpp"

namespace wawl {
	namespace fs {
		namespace pipe {

			// open named pipe
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

		} //::wawl::fs::pipe
	} // wawl::fs
} // ::wawl