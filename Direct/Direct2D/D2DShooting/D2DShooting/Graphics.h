#pragma once
#include <windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

class Graphics
{
private:
    ID2D1Factory* m_pFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;

public:
    Graphics();
    ~Graphics();

    bool Initialize(HWND hWnd);
    void Release();

    void BeginDraw();
    void EndDraw();

    ID2D1HwndRenderTarget* GetRenderTarget() { return m_pRenderTarget; }
};