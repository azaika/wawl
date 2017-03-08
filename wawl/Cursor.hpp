#pragma once
#define WAWL_CURSOR_HPP

#include "CursorBaseType.hpp"
#include "WindowBaseType.hpp"
#include "BaseUtility.hpp"

namespace wawl {
	namespace wnd {

		class Cursor {
		public:
			constexpr Cursor() = default;
			constexpr Cursor(Cursor&&) = default;
			constexpr Cursor& operator = (Cursor&&) = default;

			// uncopyable
			Cursor(const Cursor&) = delete;
			Cursor& operator = (const Cursor&) = delete;

			// load OEM cursor with system metrix
			Cursor(const OEMCursor& oem, Flags<ImageLoadOption> loadOption = {}) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						nullptr,
						oem.unpack(),
						IMAGE_CURSOR,
						0, 0,
						loadOption.get() | LR_DEFAULTSIZE
					));
			}
			// load OEM cursor with specified size
			Cursor(
				const OEMCursor& oem,
				const Size& size,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						nullptr,
						oem.unpack(),
						IMAGE_CURSOR,
						size.x, size.y,
						loadOption.get()
					));
			}

			// load from file with system metrix
			Cursor(const Tstring& path, Flags<ImageLoadOption> loadOption = {}) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						nullptr,
						path.c_str(),
						IMAGE_CURSOR,
						0, 0,
						loadOption.get() | LR_LOADFROMFILE | LR_DEFAULTSIZE
					));
			}
			// load from fiel with specified size
			Cursor(
				const Tstring& path,
				const Size& size,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						nullptr,
						path.c_str(),
						IMAGE_CURSOR,
						size.x, size.y,
						loadOption.get() | LR_LOADFROMFILE
					));
			}

			// load from resource with system metrix
			Cursor(
				ModuleHandle module,
				const Tstring& instanceName,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						module,
						instanceName.c_str(),
						IMAGE_CURSOR,
						0, 0,
						loadOption.get() | LR_DEFAULTSIZE
					));
			}
			// load from resource with specified size
			Cursor(
				ModuleHandle module,
				const Tstring& instanceName,
				const Size& size,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						module,
						instanceName.c_str(),
						IMAGE_CURSOR,
						size.x, size.y,
						loadOption.get()
					));
			}

			// load OEM cursor with system metrix
			bool load(const OEMCursor& oem, Flags<ImageLoadOption> loadOption = {}) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						nullptr,
						oem.unpack(),
						IMAGE_CURSOR,
						0, 0,
						loadOption.get() | LR_DEFAULTSIZE
					));

				return isActive();
			}
			// load OEM cursor with specified size
			bool load(
				const OEMCursor& oem,
				const Size& size,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						nullptr,
						oem.unpack(),
						IMAGE_CURSOR,
						size.x, size.y,
						loadOption.get()
					));

				return isActive();
			}

			// load from file
			bool load(const Tstring& path, Flags<ImageLoadOption> loadOption = {}) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						nullptr,
						path.c_str(),
						IMAGE_CURSOR,
						0, 0,
						loadOption.get() | LR_LOADFROMFILE | LR_DEFAULTSIZE
					));

				return isActive();
			}
			bool load(const Tstring& path, const Size& size) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						nullptr,
						path.c_str(),
						IMAGE_CURSOR,
						size.x, size.y,
						LR_LOADFROMFILE
					));

				return isActive();
			}
			bool load(
				const Tstring& path,
				const Size& size,
				Flags<ImageLoadOption> loadOption
			) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						nullptr,
						path.c_str(),
						IMAGE_CURSOR,
						size.x, size.y,
						loadOption.get() | LR_LOADFROMFILE
					));

				return isActive();
			}

			// load from resource
			bool loadFromResource(
				ModuleHandle module,
				const Tstring& instanceName,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						module,
						instanceName.c_str(),
						IMAGE_CURSOR,
						0, 0,
						loadOption.get() | LR_DEFAULTSIZE
					));

				return isActive();
			}
			bool loadFromResource(
				ModuleHandle module,
				const Tstring& instanceName,
				const Size& size,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<CursorHandle>(
					::LoadImage(
						module,
						instanceName.c_str(),
						IMAGE_CURSOR,
						size.x, size.y,
						loadOption.get()
					));

				return isActive();
			}

			// release cursor resource
			// don't call this function if the cursor is shared resource
			bool destroy() {
				return ::DestroyCursor(handle) != 0;
			}

			CursorHandle copy() {
				return CopyCursor(handle);
			}

			constexpr bool isActive() const {
				return handle != 0;
			}
			constexpr explicit operator bool() const {
				return isActive();
			}

			constexpr CursorHandle getHandle() const {
				return handle;
			}

		private:
			constexpr explicit Cursor(CursorHandle h) : handle(h) {}

			CursorHandle handle = 0;

		};

	} // ::wawl::wnd
} // ::wawl