#include "Bullet.h"

Bullet::Bullet(float x, float y)
    : m_x(x), m_y(y), m_speed(10.0f), m_active(true)
{
}

void Bullet::Update()
{
    m_y -= m_speed; // 위로 이동 (- 방향이어야 함)

    if (m_y < -50.0f) // 화면 위쪽 밖으로 완전히 나가면 삭제
    {
        m_active = false;
    }
}

void Bullet::Render(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Bitmap* pBitmap)
{
    if (pBitmap && m_active)
    {
        // 총알 출력 크기 (32x32로 살짝 키우고 보정)
        D2D1_RECT_F destRect = D2D1::RectF(m_x, m_y, m_x + 64.0f, m_y + 64.0f);

        pRenderTarget->DrawBitmap(
            pBitmap,
            destRect,
            1.0f,
            D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
        );
    }
}