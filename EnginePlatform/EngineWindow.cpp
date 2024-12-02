#include "PreCompile.h"
#include "EngineWindow.h"

HINSTANCE UEngineWindow::hInstance;
LPCWSTR UEngineWindow::szTitle = L"Title";
LPCWSTR UEngineWindow::szWindowClass = L"MyWindowClass";

UEngineWindow::UEngineWindow()
{
}

UEngineWindow::~UEngineWindow()
{
}

void UEngineWindow::Init(HINSTANCE _Inst)
{
    MyRegisterClass(_Inst);

    if (!InitInstance(_Inst))
        MsgBoxAssert(L"Windows Initialization Failed");
}

LRESULT UEngineWindow::WndProc(HWND _Hwnd, UINT _Message, WPARAM _WParam, LPARAM _LParam)
{
    switch (_Message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(_Hwnd, &ps);
        EndPaint(_Hwnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(_Hwnd, _Message, _WParam, _LParam);
    }

    return 0;
}

void UEngineWindow::MyRegisterClass(HINSTANCE _Inst)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _Inst;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = nullptr;

    RegisterClassExW(&wcex);
}

bool UEngineWindow::InitInstance(HINSTANCE _Inst)
{
    hInstance = _Inst;
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) 
        return false;

    ShowWindow(hWnd, 1);
    UpdateWindow(hWnd);
    return true;
}

int UEngineWindow::MessageRoop()
{
    MSG msg;

    // 기본 메세지 루프
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}