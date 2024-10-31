#include <windows.h>
#include <iostream>

// Global variable to store the window class name
const char CLASS_NAME[] = "WinAPI Hello World";

// Window Procedure function to process messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static RECT rcBmp{10, 10, 110, 110}; // rectangle that encloses bitmap
    static HBRUSH brush;

    switch (uMsg)
    {
    case WM_CREATE:
        brush = CreateSolidBrush(RGB(50, 151, 151));
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // Here you can add your custom painting code
        FillRect(ps.hdc, &rcBmp, brush);
        EndPaint(hwnd, &ps);
    }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

volatile LONG counter = 0; // Global counter to track timer interrupts
// Timer interrupt handler
VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    // Increment the counter
    InterlockedIncrement(&counter);
    
    // Print the counter value
    std::cout << "Timer Interrupt: " << counter << std::endl;
    std::cout.flush(); // Ensure output is flushed to the console
}

int32_t main()
{
    UINT_PTR timerId = SetTimer(NULL, 0, 1000, TimerProc);
    if (timerId == 0) {
        std::cerr << "Failed to create timer." << std::endl;
        return 1;
    }

    // Register the window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = CLASS_NAME;

    ATOM _atom = RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                                                          // Optional window styles
        MAKEINTATOM(_atom),                                         // Window class
        "Sample WinAPI Window",                                     // Window text
        WS_OVERLAPPEDWINDOW,                                        // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // Size and position
        nullptr,                                                    // Parent window
        nullptr,                                                    // Menu
        GetModuleHandle(nullptr),                                   // Instance handle
        nullptr                                                     // Additional application data
    );

    if (hwnd == nullptr)
    {
        return 0; // Window creation failed
    }

    ShowWindow(hwnd, SW_SHOW); // Show the window

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up the timer
    KillTimer(NULL, timerId);
    std::cout << "Timer stopped." << std::endl;

    return 0;
}
