#pragma once
#define ENABLE_WAWL_REGION

#include <array>
#include <vector>

#include "WawlBase.hpp"
#include "WindowBaseType.hpp"
#include "RegionBaseType.hpp"

namespace wawl {
	namespace wnd {

		// equivalence comparison of region
		inline bool equalsRegion(RegionHandle lhv, RegionHandle rhv) {
			return ::EqualRgn(lhv, rhv) != 0;
		}

		inline CombineResult combineRegion(RegionHandle target, RegionHandle rgn1, RegionHandle rgn2, CombineMode mode) {
			::CombineRgn(target, rgn1, rgn2, unpackEnum(mode));
		}

		inline RegionHandle createRegion(const Rectangle& rect, const Size& roundSize) {
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

		inline RegionHandle createRectRegion(const Rectangle& rect) {
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

		inline RegionHandle createEllipticRegion(const Rectangle& circumscribeRect) {
			return
				::CreateEllipticRgn(
					circumscribeRect.x,
					circumscribeRect.y,
					circumscribeRect.x + circumscribeRect.w,
					circumscribeRect.y + circumscribeRect.h
				);
		}

		inline bool setWindowRegion(WindowHandle window, RegionHandle region, bool doRedraw = true) {
			return ::SetWindowRgn(window, region, doRedraw) != 0;
		}
		inline bool resetWindowRegion(WindowHandle window, bool doRedraw = true) {
			return ::SetWindowRgn(window, nullptr, doRedraw) != 0;
		}

	}
}