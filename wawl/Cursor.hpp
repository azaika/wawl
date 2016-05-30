#pragma once
#define ENABLE_WAWL_CURSOR

#include "CursorBaseType.hpp"
#include "WindowBaseType.hpp"
#include "BaseUtility.hpp"

namespace wawl {
	namespace wnd {

		inline CursorHandle loadOEMCursor(
			Tchar* type,
			UnifyEnum<ImageLoadOption> loadOption,
			Size size = {}
			) {
			return
				static_cast<CursorHandle>(
					::LoadImage(
						nullptr,
						type,
						IMAGE_CURSOR,
						size.x,
						size.y,
						loadOption.get()
						)
					);
		}

		inline CursorHandle loadCursor(
			ModuleHandle module,
			const Tstring& fileName,
			UnifyEnum<ImageLoadOption> loadOption,
			const Size& size
			) {
			return
				static_cast<CursorHandle>(
					::LoadImage(
						module,
						fileName.c_str(),
						IMAGE_CURSOR,
						size.x,
						size.y,
						loadOption.get() | LR_LOADFROMFILE
						)
					);
		}

		inline CursorHandle loadCursorFromResource(
			ModuleHandle module,
			const Tstring& instName,
			UnifyEnum<ImageLoadOption> loadOption,
			const Size& size = {}
			) {
			return
				static_cast<CursorHandle>(
					::LoadImage(
						module,
						instName.c_str(),
						IMAGE_CURSOR,
						size.x,
						size.y,
						loadOption.get()
						)
					);
		}

		inline CursorHandle copyCursor(CursorHandle cursor) {
			return CopyCursor(cursor);
		}

		inline bool destroyCursor(CursorHandle cursor) {
			return ::DestroyCursor(cursor) != 0;
		}

	} // ::wawl::wnd
} // ::wawl