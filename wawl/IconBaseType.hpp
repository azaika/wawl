#pragma once
#define WAWL_ICON_BASE_TYPE_HPP

#include "BaseType.hpp"

namespace wawl {
	namespace wnd {

		using IconHandle = ::HICON;

		// default window icon
		class OEMIcon {
		public:
			OEMIcon() = delete;
			OEMIcon(const OEMIcon&) = delete;
			OEMIcon& operator = (const OEMIcon&) = delete;

			// default exe icon
			static const OEMIcon App;
			// information mark
			static const OEMIcon Info;
			// question mark
			static const OEMIcon Question;
			// error mark
			static const OEMIcon Error;
			// warning mark
			static const OEMIcon Warning;
			// windows logo
			static const OEMIcon WinLogo;

			Tchar* operator () () const {
				return kind;
			}
			Tchar* unpack() const {
				return kind;
			}

		private:
			explicit constexpr OEMIcon(Tchar* k) : kind(k) {}

			Tchar* kind;

		};

		const OEMIcon OEMIcon::App(IDI_APPLICATION);
		const OEMIcon OEMIcon::Info(IDI_INFORMATION);
		const OEMIcon OEMIcon::Question(IDI_QUESTION);
		const OEMIcon OEMIcon::Error(IDI_ERROR);
		const OEMIcon OEMIcon::Warning(IDI_WARNING);
		const OEMIcon OEMIcon::WinLogo(IDI_WINLOGO);

	} // ::wawl::wnd
} // ::wawl