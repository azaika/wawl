#pragma once
#define ENABLE_WAWL_BITMAP

#include "BaseType.hpp"
#include "BaseUtility.hpp"
#include "BitmapBaseType.hpp"
#include "WindowBaseType.hpp"

namespace wawl {
	namespace wnd {

		inline BitmapHandle loadBitmap(
			ModuleHandle module,
			const Tstring& fileName,
			UnifyEnum<ImageLoadOption> loadOption,
			const Size& size
			) {
			return
				static_cast<BitmapHandle>(
					::LoadImage(
						module,
						fileName.c_str(),
						IMAGE_BITMAP,
						size.x,
						size.y,
						loadOption.get() | LR_LOADFROMFILE
						)
					);
		}
		inline BitmapHandle loadBitmapFromResource(
			ModuleHandle module,
			const Tstring& instName,
			UnifyEnum<ImageLoadOption> loadOption,
			const Size& size = {}
			) {
			return
				static_cast<BitmapHandle>(
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

		inline BitmapHandle copyBitmap(
			BitmapHandle bitmap
			) {
			return
				static_cast<BitmapHandle>(
					::CopyImage(
						bitmap,
						IMAGE_BITMAP,
						0,
						0,
						LR_COPYRETURNORG
						)
					);
		}
		inline BitmapHandle copyBitmap(
			BitmapHandle bitmap,
			ImageCopyOption options
			) {
			return
				static_cast<BitmapHandle>(
					::CopyImage(
						bitmap,
						IMAGE_BITMAP,
						0,
						0,
						unpackEnum(options)
						)
					);
		}
		inline BitmapHandle copyBitmap(
			BitmapHandle bitmap,
			const Size& size,
			ImageCopyOption options
			) {
			return
				static_cast<BitmapHandle>(
					::CopyImage(
						bitmap,
						IMAGE_BITMAP,
						size.x,
						size.y,
						unpackEnum(options)
						)
					);
		}

		inline bool releaseBitmap(BitmapHandle bitmap) {
			return ::DeleteObject(bitmap) != 0;
		}

	} // ::wawl::wnd
} // ::wawl