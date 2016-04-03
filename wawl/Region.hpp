#pragma once
#define ENABLE_WAWL_BITMAP

#include"BaseType.hpp"
#include"BaseUtility.hpp"
#include"RegionBaseType.hpp"

namespace wawl {
	namespace wnd {

		inline const bool& cmpRegion(const RegionData& rgn1, const RegionData& rgn2) {
			return
				static_cast<bool>(
					::EqualRgn(
						static_cast<HRGN>(rgn1),
						static_cast<HRGN>(rgn2)
						)
					);
		}

		inline RegionData combine(const RegionData& rgn1, const RegionData& rgn2, CombineMode mode) {
			RegionData ret;
			::CombineRgn(static_cast<HRGN>(ret), static_cast<HRGN>(rgn1), static_cast<HRGN>(rgn2), static_cast<int>(mode));

			return ret;
		}

		inline RegionData createRegion(const wawl::Rectangle& rect, const double& rx, const double& ry) {

			return
				static_cast<RegionData>(
					::CreateRoundRectRgn(
						rect.x,
						rect.y,
						rect.x + rect.w,
						rect.y + rect.h,
						rx,
						ry
						)
					);
		}

		inline RegionData createRegion(const wawl::Rectangle& rect) {
			return
				static_cast<RegionData>(
					wawl::wnd::createRegion(
						rect
						)
					);
		}

		inline RegionData createRegion(const std::vector<wawl::Position>& points, FillMode mode) {
			std::vector<POINT> points_;

			for (auto point : points) {
				::POINT p;
				p.x = point.x;
				p.y = point.y;
				points_.push_back(p);
			}

			return static_cast<RegionData>(
				::CreatePolygonRgn(
					points_.data(),
					points_.size(),
					static_cast<int>(mode)
					)
				);
		}

		inline RegionData createRegion(const wawl::Position& pos, const double& rx, const double& ry) {

			return
				static_cast<RegionData>(
					::CreateEllipticRgn(
						pos.x - rx,
						pos.y - ry,
						pos.x + rx,
						pos.y + ry
						)
					);
		}

		inline RegionData createRegion(const wawl::Position& pos, const double& radius) {
			
			return wawl::wnd::createRegion(pos, radius, radius);
		}

		inline void setRegionWindow(WindowHandle window, const RegionData& region) {
			::SetWindowRgn(window, region, true);
		}

	}
}