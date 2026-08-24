#include "Player.h"
#include <windows.h>
#include <wincodec.h>

#pragma comment(lib, "windowscodecs.lib")

Player::Player(float startX, float startY)
    : m_x(startX), m_y(startY), m_speed(3.0f),
    m_pPlayerBitmap(nullptr), m_pBulletBitmap(nullptr), m_spacePressedLastFrame(false)
{
}

Player::~Player()
{
    if (m_pPlayerBitmap) m_pPlayerBitmap->Release();
    if (m_pBulletBitmap) m_pBulletBitmap->Release();
}

ID2D1Bitmap* Player::LoadBitmapFromFile(ID2D1HwndRenderTarget* pRenderTarget, const wchar_t* filePath)
{
    IWICImagingFactory* pWICFactory = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (void**)&pWICFactory);
    if (FAILED(hr)) return nullptr;

    IWICBitmapDecoder* pDecoder = nullptr;
    hr = pWICFactory->CreateDecoderFromFilename(filePath, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
    if (FAILED(hr)) { pWICFactory->Release(); return nullptr; }

    IWICBitmapFrameDecode* pFrame = nullptr;
    hr = pDecoder->GetFrame(0, &pFrame);
    if (FAILED(hr)) { pDecoder->Release(); pWICFactory->Release(); return nullptr; }

    IWICFormatConverter* pConverter = nullptr;
    ID2D1Bitmap* pBitmap = nullptr;
    hr = pWICFactory->CreateFormatConverter(&pConverter);
    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeMedianCut);
        if (SUCCEEDED(hr))
        {
            pRenderTarget->CreateBitmapFromWicBitmap(pConverter, nullptr, &pBitmap);
        }
        pConverter->Release();
    }

    pFrame->Release();
    pDecoder->Release();
    pWICFactory->Release();

    return pBitmap;
}

bool Player::Initialize(ID2D1HwndRenderTarget* pRenderTarget, const wchar_t* playerPath, const wchar_t* bulletPath)
{
    m_pPlayerBitmap = LoadBitmapFromFile(pRenderTarget, playerPath);
    m_pBulletBitmap = LoadBitmapFromFile(pRenderTarget, bulletPath);

    return (m_pPlayerBitmap != nullptr);
}

void Player::Update()
{
    // 이동
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)  m_x -= m_speed;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) m_x += m_speed;
    if (GetAsyncKeyState(VK_UP) & 0x8000)    m_y -= m_speed;
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)  m_y += m_speed;

    // 스페이스바 입력 처리
    bool isSpaceDown = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;

    if (isSpaceDown && !m_spacePressedLastFrame)
    {
        // 플레이어 64x64 기준 중앙 상단 (32px 위치)에서 총알(32px) 생성
        float bulletX = m_x;// + 16.0f; // (64 - 32) / 2 = 16
        float bulletY = m_y - 20.0f; // 비행기 바로 위
        m_bullets.push_back(Bullet(bulletX, bulletY));
    }

    m_spacePressedLastFrame = isSpaceDown;

    // 총알 위치 업데이트
    for (auto it = m_bullets.begin(); it != m_bullets.end(); )
    {
        it->Update();
        if (!it->IsActive())
        {
            it = m_bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Player::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
    // 1. 총알 그리기
    for (auto& bullet : m_bullets)
    {
        bullet.Render(pRenderTarget, m_pBulletBitmap);
    }

    // 2. 플레이어 그리기
    if (m_pPlayerBitmap)
    {
        D2D1_RECT_F destRect = D2D1::RectF(m_x, m_y, m_x + 64.0f, m_y + 64.0f);
        pRenderTarget->DrawBitmap(m_pPlayerBitmap, destRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
    }
}