#include "../wawl/Wawl.hpp"

using namespace wawl;

LongPtr CALLBACK MsgProc(
	wnd::WindowHandle window,
	Uint msg,
	UintPtr wParam,
	LongPtr lParam
) {
	return wnd::defaultProc(window, static_cast<wnd::Msg>(msg), wParam, lParam);
}

int WawlMain(
	AppHandle appInst,
	AppHandle,
	Tchar* cmdLine,
	int cmdShow
) {
	const Tstring propName = L"WndClass";

	// create window property and register it
	if (
		!wnd::registerProperty(
			wnd::Property()
			.name(propName)
			.proc(MsgProc)
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

	auto window =
		wnd::createWindow(
			propName,
			L"wawl test",
			{ wnd::DefaultWindowPos, 640, 480 },
			wnd::Option::Popup
		);
	if (!window)
		return 0;

	// update and show window
	wnd::updateWindow(window);
	wnd::setWindowShowMode(window, static_cast<wnd::ShowMode>(cmdShow));

	// check message queue and process it
	wnd::MsgProcResult msgRes = {};
	while (wnd::getMessage(msgRes, window)) {
		wnd::translateMessage(msgRes);
		wnd::dispatchMessage(msgRes);
	}

	return static_cast<int>(msgRes.wParam);
}