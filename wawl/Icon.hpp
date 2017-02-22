#pragma once
#define WAWL_ICON_HPP

#include "IconBaseType.hpp"
#include "WindowBaseType.hpp"
#include "BaseUtility.hpp"

namespace wawl {
	namespace wnd {

		inline IconHandle loadOEMIcon(
			Tchar* type,
			Flags<ImageLoadOption> loadOption,
			Size size = {}
			) {
			return
				static_cast<IconHandle>(
					::LoadImage(
						nullptr,
						type,
						IMAGE_ICON,
						size.x,
						size.y,
						loadOption.get()
						)
					);
		}

		inline IconHandle loadIcon(
			ModuleHandle module,
			const Tstring& fileName,
			Flags<ImageLoadOption> loadOption,
			const Size& size
			) {
			return
				static_cast<IconHandle>(
					::LoadImage(
						module,
						fileName.c_str(),
						IMAGE_ICON,
						size.x,
						size.y,
						loadOption.get() | LR_LOADFROMFILE
						)
					);
		}

		inline IconHandle loadIconFromResource(
			ModuleHandle module,
			const Tstring& instName,
			Flags<ImageLoadOption> loadOption = ImageLoadOption::SystemSize,
			const Size& size = {}
			) {
			return
				static_cast<IconHandle>(
					::LoadImage(
						module,
						instName.c_str(),
						IMAGE_ICON,
						size.x,
						size.y,
						loadOption.get()
						)
					);
		}

		inline IconHandle copyIcon(IconHandle icon) {
			return ::CopyIcon(icon);
		}

		inline bool destroyIcon(IconHandle icon) {
			return ::DestroyIcon(icon) != 0;
		}

	} // ::wawl::wnd
} // ::wawl