#include "../wawl/Wawl.hpp"

using namespace wawl;

LongPtr CALLBACK MsgProc(
	wnd::WindowHandle window,
	Uint msg,
	UintPtr wParam,
	LongPtr lParam
) {
	using wnd::Msg;
	static auto region = wnd::createRoundRectRegion({ 0, 0, 640, 480 }, { 200, 200 });

	switch (static_cast<Msg>(msg)) {
		case Msg::Create:
			wnd::setRegion(window, region);
			break;
		case Msg::MouseLClick:
			wnd::postQuitMsg(0);
			break;
		default:
			return wnd::defaultProc(window, static_cast<wnd::Msg>(msg), wParam, lParam);
	}

	return 0;
}

int WawlMain(
	AppHandle appInst,
	AppHandle,
	Tchar* cmdLine,
	int cmdShow
) {
	const Tstring propName = L"WndClass";
	
	if (
		!wnd::registerProperty(
			wnd::Property()
			.name(propName)
			.proc(MsgProc)
			.appHandle(appInst)
			.option(wnd::PropOption::HRedraw | wnd::PropOption::VRedraw)
			.cursor(
				wnd::loadOEMCursor(
					wnd::OEMCursor::Arrow,
					wnd::ImageLoadOption::DefaultSize
					| wnd::ImageLoadOption::ShareHandle
				)
			)
			.background(wnd::ColorBrush::White)
		))
		return 0;

	wnd::WindowHandle window =
		wnd::createWindow(
			propName,
			L"wawl test",
			{ 300, 150, 640, 480 },
			wnd::Option::Popup
		);
	if (!window)
		return 0;

	wnd::updateWindow(window);
	wnd::setWindowShowMode(window, static_cast<wnd::ShowMode>(cmdShow));

	wnd::MsgProcResult msg;
	while (wnd::getMessage(msg, window)) {
		wnd::translateMessage(msg);
		wnd::dispatchMessage(msg);
	}

	return static_cast<int>(msg.wParam);
}