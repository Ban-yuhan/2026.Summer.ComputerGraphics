#include <windows.h>
#include "Graphics.h" // 우리가 만든 그래픽스 헤더 추가!
#include "Player.h"

Graphics g_Graphics; // 그래픽스 객체 전역 선언
Player g_Player(928.0f, 900.0f);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        // 1. 창 크기 조절 시 16:9 비율 강제 고정
    case WM_SIZING:
    {
        RECT* pRect = (RECT*)lParam;

        // 윈도우의 가로/세로 길이 계산
        int width = pRect->right - pRect->left;
        int height = pRect->bottom - pRect->top;

        // 기준 비율 (16:9 = 1.7777...)
        const float targetAspect = 16.0f / 9.0f;

        // 사용자가 드래그하는 방향에 따라 비율 맞춰 조정
        if (wParam == WMSZ_LEFT || wParam == WMSZ_RIGHT ||
            wParam == WMSZ_BOTTOMLEFT || wParam == WMSZ_BOTTOMRIGHT)
        {
            // 가로 폭에 맞춰 세로 높이 재계산
            int newHeight = (int)(width / targetAspect);
            pRect->bottom = pRect->top + newHeight;
        }
        else
        {
            // 세로 높이에 맞춰 가로 폭 재계산
            int newWidth = (int)(height * targetAspect);
            pRect->right = pRect->left + newWidth;
        }
        return TRUE;
    }

    // 2. 최소/최대 창 크기 제한 (선택 사항)
    case WM_GETMINMAXINFO:
    {
        LPMINMAXINFO pMMI = (LPMINMAXINFO)lParam;

        // 최소 크기 제한 (800 x 450)
        pMMI->ptMinTrackSize.x = 800;
        pMMI->ptMinTrackSize.y = 450;

        // 최대 크기 제한 (1920 x 1080)
        pMMI->ptMaxTrackSize.x = 1920;
        pMMI->ptMaxTrackSize.y = 1080;
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    CoInitialize(nullptr);

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"MyGameWindowClass";
    wcex.hIconSm = nullptr;

    RegisterClassEx(&wcex);

    RECT wr = { 0, 0, 1920, 1080 };

    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hWnd = CreateWindowW(
        L"MyGameWindowClass",
        L"My First Game Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        wr.right - wr.left,   // 보정된 전체 가로 크기
        wr.bottom - wr.top, // 보정된 전체 세로 크기
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hWnd) return FALSE;

    // 윈도우 창을 띄운 직후 Direct2D 초기화 연동!
    if (!g_Graphics.Initialize(hWnd))
    {
        return FALSE;
    }
    
    if (!g_Player.Initialize(g_Graphics.GetRenderTarget(), L"Resources/Player.png", L"Resources/Bullet.png"))
    {
        MessageBox(hWnd, L"이미지를 로드하는 데 실패했습니다! (Player.png 또는 Bullet.png 확인)", L"에러", MB_OK);
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // 1. 키보드 입력 처리 및 위치 계산
            g_Player.Update();

            // 2. 화면 그리기
            g_Graphics.BeginDraw();

            // ★ 플레이어를 화면에 그리는 함수 호출!
            g_Player.Render(g_Graphics.GetRenderTarget());

            g_Graphics.EndDraw();
        }
    }

    // 프로그램 종료 시 그래픽스 리소스 해제
    g_Graphics.Release();

    CoUninitialize();

    return (int)msg.wParam;
}