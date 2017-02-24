#pragma once
#define WAWL_CURSOR_BASE_TYPE_HPP

#include "BaseType.hpp"

namespace wawl {
	namespace wnd {

		using CursorHandle = ::HCURSOR;

		using OEMCursorType = Tchar*;
		// default cursor icon
		class OEMCursor {
		public:
			OEMCursor() = delete;
			OEMCursor(const OEMCursor&) = delete;
			OEMCursor& operator = (const OEMCursor&) = delete;

			// default arrow with small hourglass
			static const OEMCursor AppStart;
			// default arrow
			static const OEMCursor Arrow;
			// cross mark
			static const OEMCursor Cross;
			// help mark
			static const OEMCursor Help;
			// Ibeam used in charactor input
			static const OEMCursor IBeam;
			// nix sign
			static const OEMCursor Nix;
			// cross arrow
			static const OEMCursor CrossArrow;
			// arrow for top-right and bottom-left
			static const OEMCursor TrBlArrow;
			// arrow for up and down
			static const OEMCursor UDArrow;
			// arrow for top-left and bottom-right
			static const OEMCursor TlBrArrow;
			// arrow for left and right
			static const OEMCursor LRArrow;
			// up arrow
			static const OEMCursor UpArrow;
			// hourglass mark
			static const OEMCursor HourGlass;

			OEMCursorType unpack() const {
				return type;
			}
			OEMCursorType operator () () const {
				return type;
			}

		private:
			OEMCursor(OEMCursorType t) : type(t) {}
			OEMCursorType type;

		};

		const OEMCursor OEMCursor::AppStart(IDC_APPSTARTING);
	  	const OEMCursor OEMCursor::Arrow(IDC_ARROW);
		const OEMCursor OEMCursor::Cross(IDC_CROSS);
		const OEMCursor OEMCursor::Help(IDC_HELP);
		const OEMCursor OEMCursor::IBeam(IDC_IBEAM);
		const OEMCursor OEMCursor::Nix(IDC_NO);
		const OEMCursor OEMCursor::CrossArrow(IDC_SIZEALL);
		const OEMCursor OEMCursor::TrBlArrow(IDC_SIZENESW);
		const OEMCursor OEMCursor::UDArrow(IDC_SIZENS);
		const OEMCursor OEMCursor::TlBrArrow(IDC_SIZENWSE);
		const OEMCursor OEMCursor::LRArrow(IDC_SIZEWE);
		const OEMCursor OEMCursor::UpArrow(IDC_UPARROW);
		const OEMCursor OEMCursor::HourGlass(IDC_WAIT);

	} // ::wawl::wnd
} // ::wawl