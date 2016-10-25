#pragma once
#define WAWL_REGION_HPP

#include <array>
#include <vector>

#include "WawlBase.hpp"
#include "WindowBaseType.hpp"
#include "RegionBaseType.hpp"

namespace wawl {
	namespace wnd {

		// equivalence comparison of initializedRegion
		inline bool equalsRegion(RegionHandle lhv, RegionHandle rhv) {
			return ::EqualRgn(lhv, rhv) != 0;
		}

		// combine region and region
		// 'target' and 'rgn1' or 'rgn2' can be same handle
		inline CombineResult combineRegion(RegionHandle target, RegionHandle rgn1, RegionHandle rgn2, CombineMode mode) {
			return static_cast<CombineResult>(::CombineRgn(target, rgn1, rgn2, unpackEnum(mode)));
		}
        inline CombineResult mergeRegion(RegionHandle to, RegionHandle from, CombineMode mode) {
            return static_cast<CombineResult>(::CombineRgn(to, to, from, unpackEnum(mode)));
        }

		inline RegionHandle createRoundRectRegion(const Rect& rect, const Size& roundSize) {
			return
				::CreateRoundRectRgn(
					rect.x,
					rect.y,
					rect.x + rect.w,
					rect.y + rect.h,
					roundSize.x,
					roundSize.y
				);
		}

		inline RegionHandle createRectRegion(const Rect& rect) {
			return
				::CreateRectRgn(
					rect.x,
					rect.y,
					rect.x + rect.w,
					rect.y + rect.h
				);
		}

		inline RegionHandle createPolygonRegion(const Position* points, int n, FillMode fillMode) {
			return
				::CreatePolygonRgn(
					reinterpret_cast<const ::POINT*>(points),
					n,
					unpackEnum(fillMode)
				);
		}
		inline RegionHandle createPolygonRegion(const std::vector<Position>& points, FillMode fillMode) {
			return
				createPolygonRegion(
					points.data(),
					static_cast<int>(points.size()),
					fillMode
				);
		}
		template <size_t N>
		inline RegionHandle createPolygonRegion(const std::array<Position, N>& points, FillMode fillMode) {
			return
				ceatePolygonRegion(
					points.data(),
					static_cast<int>(N),
					fillMode
				);
		}

		inline RegionHandle createEllipticRegion(const Rect& circumscribeRect) {
			return
				::CreateEllipticRgn(
					circumscribeRect.x,
					circumscribeRect.y,
					circumscribeRect.x + circumscribeRect.w,
					circumscribeRect.y + circumscribeRect.h
				);
		}

		// set region to window
		inline bool setRegion(WindowHandle window, RegionHandle region, bool doRedraw = true) {
			return ::SetWindowRgn(window, region, doRedraw) != 0;
		}
		// reset window region
		inline bool resetRegion(WindowHandle window, bool doRedraw = true) {
			return ::SetWindowRgn(window, nullptr, doRedraw) != 0;
		}

		inline CombineResult copyRegion(WindowHandle window, RegionHandle initializedRegion) {
			return static_cast<CombineResult>(::GetWindowRgn(window, initializedRegion));
		}

	} // ::wawl::wnd
} // ::wawl