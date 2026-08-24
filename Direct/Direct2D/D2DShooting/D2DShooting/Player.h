#pragma once
#include <d2d1.h>
#include <vector>
#include "Bullet.h"

class Player
{
private:
    float m_x, m_y;
    float m_speed;
    ID2D1Bitmap* m_pPlayerBitmap;
    ID2D1Bitmap* m_pBulletBitmap; // 총알 비트맵

    std::vector<Bullet> m_bullets; // 발사된 총알 목록
    bool m_spacePressedLastFrame;  // 연사 방지용 플래그

public:
    Player(float startX, float startY);
    ~Player();

    bool Initialize(ID2D1HwndRenderTarget* pRenderTarget, const wchar_t* playerPath, const wchar_t* bulletPath);
    void Update();
    void Render(ID2D1HwndRenderTarget* pRenderTarget);

private:
    ID2D1Bitmap* LoadBitmapFromFile(ID2D1HwndRenderTarget* pRenderTarget, const wchar_t* filePath);
};