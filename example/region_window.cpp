#include "../wawl/Wawl.hpp"

using namespace wawl;

fs::ProcessInfo procInfo = {};

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
		wnd::quitAll(0);
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

	wnd::Property prop(
		propName,
		MsgProc,
		appInst,
		wnd::PropOption::HRedraw | wnd::PropOption::VRedraw,
		wnd::loadIconFromResource(appInst, L"ico"),
		wnd::loadIconFromResource(appInst, L"ico"),
		wnd::loadOEMCursor(
			wnd::OEMCursor::Arrow,
			wnd::ImageLoadOption::DefaultSize
			| wnd::ImageLoadOption::ShareHandle
		),
		wnd::ColorBrush::White
	);
	if (!wnd::registerProperty(prop))
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

	wnd::update(window);
	wnd::setShowMode(window, static_cast<wnd::ShowMode>(cmdShow));

	wnd::Message msg;
	while (wnd::getMessage(msg, window)) {
		wnd::translateMessage(msg);
		wnd::dispatchMessage(msg);
	}

	return static_cast<int>(msg.wParam);
}