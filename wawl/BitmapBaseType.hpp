#pragma once
#define WAWL_BITMAP_BASE_TYPE_HPP

#include "BaseType.hpp"
#include "Detail.hpp"

namespace wawl {
	namespace wnd {

		using BitmapHandle = ::HBITMAP;

		using BitmapHeader = ::BITMAP;

		// options of image copy
		enum class ImageCopyOption : Uint {
			Move = LR_COPYDELETEORG,
			ReadFromResources = LR_COPYFROMRESOURCE,
			CheckError = LR_COPYRETURNORG,
			UseDIB = LR_CREATEDIBSECTION
		};

	} // ::wawl::wnd

	WAWL_DETAIL_ENABLE_FLAG(wnd::ImageCopyOption)

} // ::wawl