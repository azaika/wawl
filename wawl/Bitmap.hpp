#pragma once
#define WAWL_BITMAP_HPP

#include "BaseType.hpp"
#include "BaseUtility.hpp"
#include "BitmapBaseType.hpp"
#include "WindowBaseType.hpp"

namespace wawl {
	namespace wnd {

		class Bitmap {
		public:
			Bitmap() = default;
			Bitmap(Bitmap&&) = default;
			Bitmap& operator = (Bitmap&&) = default;

			// uncopyable
			Bitmap(const Bitmap&) = delete;
			Bitmap& operator = (const Bitmap&) = delete;

			~Bitmap() {
				release();
			}

			Bitmap(
				const Tstring& path,
				const Size& size = {}
			) {
				handle = static_cast<BitmapHandle>(
					::LoadImage(
						0,
						path.c_str(),
						IMAGE_BITMAP,
						size.x, size.y,
						LR_LOADFROMFILE
					));
			}
			Bitmap(
				const Tstring& path,
				Flags<ImageLoadOption> flags,
				const Size& size = {}
			) {
				handle = static_cast<BitmapHandle>(
					::LoadImage(
						0,
						path.c_str(),
						IMAGE_BITMAP,
						size.x, size.y,
						flags.get() | LR_LOADFROMFILE
					));
			}

			bool load(
				const Tstring& path,
				const Size& size = {}
			) {
				handle = static_cast<BitmapHandle>(
					::LoadImage(
						0,
						path.c_str(),
						IMAGE_BITMAP,
						size.x, size.y,
						LR_LOADFROMFILE
					));

				return handle != 0;
			}
			bool load(
				const Tstring& path,
				Flags<ImageLoadOption> flags,
				const Size& size = {}
			) {
				handle = static_cast<BitmapHandle>(
					::LoadImage(
						0,
						path.c_str(),
						IMAGE_BITMAP,
						size.x, size.y,
						flags.get() | LR_LOADFROMFILE
					));

				return handle != 0;
			}

			bool loadFromResource(
				ModuleHandle module,
				const Tstring& instanceName,
				const Size& size = {}
			) {
				handle = static_cast<BitmapHandle>(
					::LoadImage(
						module,
						instanceName.c_str(),
						IMAGE_ICON,
						size.x,
						size.y,
						0
					));

				return handle != 0;
			}
			bool loadFromResource(
				ModuleHandle module,
				const Tstring& instanceName,
				Flags<ImageLoadOption> loadOption,
				const Size& size = {}
			) {
				handle = static_cast<BitmapHandle>(
					::LoadImage(
						module,
						instanceName.c_str(),
						IMAGE_ICON,
						size.x,
						size.y,
						loadOption.get()
					));

				return handle != 0;
			}

			bool release() {
				return ::DeleteObject(handle) != 0;
			}

			Bitmap copy() const {
				return Bitmap(
					static_cast<BitmapHandle>(
						::CopyImage(
							handle,
							IMAGE_BITMAP,
							0, 0,
							LR_COPYRETURNORG
						)));
			}
			Bitmap copy(const Size& size) const {
				return Bitmap(
					static_cast<BitmapHandle>(
						::CopyImage(
							handle,
							IMAGE_BITMAP,
							size.x,
							size.y,
							0
						)));
			}
			Bitmap copy(
				ImageCopyOption options,
				const Size& size = {}
			) {
				return Bitmap(
					static_cast<BitmapHandle>(
						::CopyImage(
							handle,
							IMAGE_BITMAP,
							size.x,
							size.y,
							unpackEnum(options)
						)));
			}

			bool validate() {
				auto h = static_cast<BitmapHandle>(
					::CopyImage(
						handle,
						IMAGE_BITMAP,
						0, 0,
						LR_COPYRETURNORG
					));

				if (h != 0) {
					handle = h;
					return true;
				}
				return false;
			}

			bool isActive() const {
				return handle != 0;
			}
			explicit operator bool() const {
				return isActive();
			}

			BitmapHandle get() const {
				return handle;
			}

		private:
			Bitmap(BitmapHandle h) : handle(h) {}

			BitmapHandle handle = 0;

		};

	} // ::wawl::wnd
} // ::wawl