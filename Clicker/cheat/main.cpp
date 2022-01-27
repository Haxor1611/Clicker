#include "gui.h"

#include <thread>
#include <Windows.h>
#include "Globals.h"
void Destroy();
void minimize(HWND, bool);
void doClicks();
void doJitter();
//void humanise();
//void doJitter();
DWORD getRandomY();
DWORD getRandomX();
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
	std::thread{ doJitter }.detach();

	while (gui::exit)
	{
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		if (GetAsyncKeyState(VK_INSERT) & 1) {
			show = !show;
			minimize(gui::window, show);
		}
		if (GetAsyncKeyState(VK_RBUTTON) & 1) {
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
		
			if ( Globals::enabled) {
				POINT currentMousePos;
				GetCursorPos(&currentMousePos);
				mouse_event(MOUSEEVENTF_LEFTDOWN, currentMousePos.x, currentMousePos.y, 0, 0);
				Sleep(1);
				mouse_event(MOUSEEVENTF_LEFTUP, currentMousePos.x, currentMousePos.y, 0, 0);
				Sleep(Globals::interval);
			}
		
	}
}/*
void doJitter() {
	while (true) {
		if (Globals::jitterEnabled) {
			mouse_event(MOUSEEVENTF_MOVE, getRandomX(), getRandomY(), 0, 0);
			Sleep((rand() % Globals::jitter) * rand() % 750);
		}
	}
}
DWORD getRandomX() {
	DWORD x;
	int minPlu = rand() % 3;
	if (minPlu == 1) {
		x = (rand() % Globals::jitter) * 2 - (rand() % 2) * 5;

	}
	else {
		x = (rand() % Globals::jitter) * 2 + (rand() % 2) * 5;
	}
	return x;
}
DWORD getRandomY() {
	DWORD y;
	int minPlu = rand() % 3;
	if (minPlu == 1) {
		y = (rand() % Globals::jitter) * 2 - (rand() % 2) * 5;

	}
	else {
		y = (rand() % Globals::jitter) * 2 + (rand() % 2) * 5;
	}
	return y;
}
*/
