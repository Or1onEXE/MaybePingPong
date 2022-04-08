#include <Windows.h>

bool running = true;

struct RenderState {
	int height, width;
	void* memory;

	BITMAPINFO bitmapInfo;
};

RenderState renderState;

#include "renderer.cpp"

LRESULT CALLBACK windowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	switch (uMsg) {
		case WM_CLOSE: 
		case WM_DESTROY: {
			running = false;
		} break;

		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			renderState.width = rect.right - rect.left;
			renderState.height = rect.bottom - rect.top;

			int size = renderState.width * renderState.height * sizeof(unsigned int);

			if (renderState.memory) VirtualFree(renderState.memory, 0, MEM_RELEASE);
			renderState.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			renderState.bitmapInfo.bmiHeader.biSize = sizeof(renderState.bitmapInfo.bmiHeader);
			renderState.bitmapInfo.bmiHeader.biWidth = renderState.width;
			renderState.bitmapInfo.bmiHeader.biHeight = renderState.height;
			renderState.bitmapInfo.bmiHeader.biPlanes = 1;
			renderState.bitmapInfo.bmiHeader.biBitCount = 32;
			renderState.bitmapInfo.bmiHeader.biCompression = BI_RGB;

		} break;

		default:
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return result;
}


int WinMain(HINSTANCE hIstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	// Create window class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = windowCallback;

	// Regsiter class
	RegisterClass(&window_class);

	// Create window
	HWND window = CreateWindow(window_class.lpszClassName, L"My First Game!", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hIstance, 0);
	HDC hdc = GetDC(window);

	while (running) {
		// Input 
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		// Simulte 
		clearScreen();
		drawRect(50, 50, 200, 500, 0x000000);

		// Render
		StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.memory, &renderState.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}
}