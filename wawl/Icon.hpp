#pragma once
#define WAWL_ICON_HPP

#include "IconBaseType.hpp"
#include "WindowBaseType.hpp"
#include "BaseUtility.hpp"

namespace wawl {
	namespace wnd {

		class Icon {
		public:
			constexpr Icon() = default;
			constexpr Icon(Icon&&) = default;
			constexpr Icon& operator = (Icon&&) = default;

			// uncopyable
			Icon(const Icon&) = delete;
			Icon& operator = (const Icon&) = delete;

			// load OEM icon with system metrix
			Icon(const OEMIcon& oem, Flags<ImageLoadOption> loadOption = {}) {
				handle = static_cast<IconHandle>(
					::LoadImage(
						nullptr,
						oem.unpack(),
						IMAGE_ICON,
						0, 0,
						loadOption.get() | LR_DEFAULTSIZE
					));
			}
			// load OEM icon with specified size
			Icon(
				const OEMIcon& oem,
				const Size& size,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<IconHandle>(
					::LoadImage(
						nullptr,
						oem.unpack(),
						IMAGE_ICON,
						size.x, size.y,
						loadOption.get()
					));
			}

			// load from file with system metrix
			Icon(const Tstring& path, Flags<ImageLoadOption> loadOption = {}) {
				handle = static_cast<IconHandle>(
					::LoadImage(
						nullptr,
						path.c_str(),
						IMAGE_ICON,
						0, 0,
						loadOption.get() | LR_LOADFROMFILE | LR_DEFAULTSIZE
					));
			}
			// load from fiel with specified size
			Icon(
				const Tstring& path,
				const Size& size,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<IconHandle>(
					::LoadImage(
						nullptr,
						path.c_str(),
						IMAGE_ICON,
						size.x, size.y,
						loadOption.get() | LR_LOADFROMFILE
					));
			}

			// load from resource with system metrix
			Icon(
				ModuleHandle module,
				const Tstring& instanceName,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<IconHandle>(
					::LoadImage(
						module,
						instanceName.c_str(),
						IMAGE_ICON,
						0, 0,
						loadOption.get() | LR_DEFAULTSIZE
					));
			}
			// load from resource with specified size
			Icon(
				ModuleHandle module,
				const Tstring& instanceName,
				const Size& size,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<IconHandle>(
					::LoadImage(
						module,
						instanceName.c_str(),
						IMAGE_ICON,
						size.x, size.y,
						loadOption.get()
					));
			}

			// load OEM icon with system metrix
			bool load(const OEMIcon& oem, Flags<ImageLoadOption> loadOption = {}) {
				handle = static_cast<IconHandle>(
					::LoadImage(
						nullptr,
						oem.unpack(),
						IMAGE_ICON,
						0, 0,
						loadOption.get() | LR_DEFAULTSIZE
					));

				return isActive();
			}
			// load OEM icon with specified size
			bool load(
				const OEMIcon& oem,
				const Size& size,
				Flags<ImageLoadOption> loadOption = {}
			) {
				handle = static_cast<IconHandle>(
					::LoadImage(
						nullptr,
						oem.unpack(),
						IMAGE_ICON,
						size.x, size.y,
						loadOption.get()
					));

				return isActive();
			}

			// load from file
			bool load(const Tstring& path, Flags<ImageLoadOption> loadOption = {}) {
				handle = static_cast<IconHandle>(
					::LoadImage(
						nullptr,
						path.c_str(),
						IMAGE_ICON,
						0, 0,
						loadOption.get() | LR_LOADFROMFILE | LR_DEFAULTSIZE
					));

				return isActive();
			}
			bool load(const Tstring& path, const Size& size) {
				handle = static_cast<IconHandle>(
					::LoadImage(
						nullptr,
						path.c_str(),
						IMAGE_ICON,
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
				handle = static_cast<IconHandle>(
					::LoadImage(
						nullptr,
						path.c_str(),
						IMAGE_ICON,
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
				handle = static_cast<IconHandle>(
					::LoadImage(
						module,
						instanceName.c_str(),
						IMAGE_ICON,
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
				handle = static_cast<IconHandle>(
					::LoadImage(
						module,
						instanceName.c_str(),
						IMAGE_ICON,
						size.x, size.y,
						loadOption.get()
					));

				return isActive();
			}

			// release icon resource
			// don't call this function if the icon is shared resource
			bool destroy() {
				return ::DestroyIcon(handle) != 0;
			}
			
			// copy icon
			// pay attention that the icon become a shared resource after call this
			Icon copy() {
				return Icon(::CopyIcon(handle));
			}

			bool validate() {
				auto h = static_cast<IconHandle>(
					::CopyImage(
						handle,
						IMAGE_ICON,
						0, 0,
						LR_COPYRETURNORG
					));

				if (h != 0) {
					handle = h;
					return true;
				}
				return false;
			}

			constexpr bool isActive() const {
				return handle != 0;
			}
			constexpr explicit operator bool() const {
				return isActive();
			}

			constexpr IconHandle getHandle() const {
				return handle;
			}

		private:
			constexpr explicit Icon(IconHandle h) : handle(h) {}

			IconHandle handle = 0;

		};

	} // ::wawl::wnd
} // ::wawl