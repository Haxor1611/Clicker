#include "gui.h"

#include <thread>
#include <Windows.h>
#include "Globals.h"
void Destroy();
void minimize(HWND, bool);
void doClicks();
//void humanise();
//void doJitter();

bool show;



int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	// create gui
	gui::CreateHWindow("Cheat Menu");
	gui::CreateDevice();
	gui::CreateImGui();
	SetWindowPos(gui::window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);

	std::thread{ doClicks }.detach();

	while (gui::exit)
	{
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		if (GetAsyncKeyState(VK_INSERT) & 1) {
			show = !show;
			minimize(gui::window, show);
		}
		if (GetAsyncKeyState(VK_F1) & 1) {
			Globals::enabled = !Globals::enabled;
		}
		if (GetAsyncKeyState(VK_END) & 1) {
			Destroy();
		}
		
		Globals::interval = ((int)lround(1000 / Globals::cps)) + (1 + (rand() % Globals::humanisation));

		
		
	}

	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}

void Destroy() {
	gui::EndRender();
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

}
void minimize(HWND window, bool isShown) {
	if (!isShown)
	{
		ShowWindow(window, SW_HIDE);
	}
	else
	{
		ShowWindow(window, SW_NORMAL);
	}
}


void doClicks()
{
	
	while (true) {
		if (Globals::enabled) {
			if (GetAsyncKeyState(VK_LBUTTON)) {
				POINT currentMousePos;
				GetCursorPos(&currentMousePos);
				mouse_event(MOUSEEVENTF_LEFTDOWN, currentMousePos.x, currentMousePos.y, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, currentMousePos.x, currentMousePos.y, 0, 0);
				Sleep(Globals::interval);
			}

		}
			
		
		
	}
}
