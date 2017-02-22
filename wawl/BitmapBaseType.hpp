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
			// delete original image after copy
			Move = LR_COPYDELETEORG,
			// load image by resource file only if the original image has loaded by resource file
			ReadFromResources = LR_COPYFROMRESOURCE,
			// copy as DIB data 
			AsDIB = LR_CREATEDIBSECTION,
			// use system metrix if the specified size is Zero
			UseSystemSize = LR_DEFAULTSIZE,
			// copy as monochromatize image
			Monochromatize = LR_MONOCHROME
		};

	} // ::wawl::wnd

	WAWL_DETAIL_ENABLE_FLAG(wnd::ImageCopyOption)

} // ::wawl