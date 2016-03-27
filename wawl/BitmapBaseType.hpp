#pragma once
#define ENABLE_WAWL_BITMAPBASETYPE

#include "BaseType.hpp"

namespace wawl {
	namespace wnd {

		using BitmapHandle = ::HBITMAP;

		// options of image copy
		enum class ImageCopyOption : Uint {
			Move = LR_COPYDELETEORG,
			ReadFromResources = LR_COPYFROMRESOURCE,
			CheckError = LR_COPYRETURNORG,
			UseDIB = LR_CREATEDIBSECTION
		};

	} // ::wawl::wnd
} // ::wawl