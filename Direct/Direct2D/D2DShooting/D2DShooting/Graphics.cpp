#include "Graphics.h"

Graphics::Graphics()
    : m_pFactory(nullptr), m_pRenderTarget(nullptr)
{
}

Graphics::~Graphics()
{
    Release();
}

bool Graphics::Initialize(HWND hWnd)
{
    // 1. Direct2D 팩토리 생성
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
    if (FAILED(hr)) return false;

    // 2. 윈도우 클라이언트 영역 크기 구하기
    RECT rc;
    GetClientRect(hWnd, &rc);

    // 3. 렌더 타겟(도화지) 생성
    hr = m_pFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
        &m_pRenderTarget
    );

    if (FAILED(hr)) return false;

    return true;
}

void Graphics::Release()
{
    if (m_pRenderTarget) { m_pRenderTarget->Release(); m_pRenderTarget = nullptr; }
    if (m_pFactory) { m_pFactory->Release(); m_pFactory = nullptr; }
}

void Graphics::BeginDraw()
{
    if (m_pRenderTarget)
    {
        m_pRenderTarget->BeginDraw();

        // 1. 현재 윈도우 창의 클라이언트 영역(실제 그려지는 해상도) 크기 구하기
        D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();

        // 2. 가상 기준 해상도(1920x1080) 대비 현재 창 크기 비율 계산
        float scaleX = renderTargetSize.width / 1920.0f;
        float scaleY = renderTargetSize.height / 1080.0f;

        // 3. Direct2D 변환 행렬 적용 (이후에 그려지는 모든 객체에 일괄 적용됨)
        m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(scaleX, scaleY));

        // 4. 배경색 클리어 (파란색 예시)
        m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CornflowerBlue));
    }
}

void Graphics::EndDraw()
{
    if (m_pRenderTarget)
    {
        m_pRenderTarget->EndDraw();
    }
}