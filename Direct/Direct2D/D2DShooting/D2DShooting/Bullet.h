#pragma once
#include <d2d1.h>

class Bullet
{
private:
    float m_x, m_y;
    float m_speed;
    bool m_active;

public:
    Bullet(float x, float y);

    void Update();
    void Render(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Bitmap* pBitmap);

    bool IsActive() const { return m_active; }
};