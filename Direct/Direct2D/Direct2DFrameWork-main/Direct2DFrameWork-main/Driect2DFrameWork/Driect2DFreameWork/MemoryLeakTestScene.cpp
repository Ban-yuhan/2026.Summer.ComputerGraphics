#include "MemoryLeakTestScene.h"
#include "DX2DClasses/SingletonRenderTarget.h"
#include "DX2DClasses/ColorBrushPalettet.h"
#include "DX2DClasses/Image.h"
#include "DX2DClasses/GameObject.h"
#include "DX2DClasses/DebugHelper.h"

using namespace DX2DClasses;

CMemoryLeakTestScene::CMemoryLeakTestScene()
{
}

CMemoryLeakTestScene::~CMemoryLeakTestScene()
{
    Release();
}

void CMemoryLeakTestScene::Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework)
{
    m_pDX2DFramework = pDX2DFramework;
    ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();

    m_pColorBrushPalettet = new CColorBrushPalettet();
    m_pColorBrushPalettet->Initialize(pRenderTarget);

    m_pImage = new CImage(m_pDX2DFramework->GetD2DRenderTarget(), m_pDX2DFramework->GetImagingFactory(),6);
    m_pImage->ManualLoadImage(hWnd, L"Images\\Player\\player%02d.png"); // 임의의 이미지 경로

    m_pGameObject = new CGameObject();
    m_pGameObject->Initialize(m_pImage, true);

    // 메모리 누수를 발생시키려면 아래 주석을 해제하세요.
    // CreateMemoryLeak();

    // 메모리를 올바르게 해제하려면 아래 함수를 호출하세요. (기본적으로 Release에서 처리)
    // ReleaseMemory();
}

void CMemoryLeakTestScene::Release()
{
    CDebugHelper::LogConsole("MemoryLeakTestScene::Release()\n");
    if (m_pGameObject)
    {
        m_pGameObject->Release();
        delete m_pGameObject;
        m_pGameObject = nullptr;
    }
    if (m_pImage)
    {
        delete m_pImage;
        m_pImage = nullptr;
    }
    if (m_pColorBrushPalettet)
    {
        m_pColorBrushPalettet->Release();
        delete m_pColorBrushPalettet;
        m_pColorBrushPalettet = nullptr;
    }
}

void CMemoryLeakTestScene::Update()
{
    if (m_pGameObject)
        m_pGameObject->Update();
}

void CMemoryLeakTestScene::Draw()
{
    if (m_pGameObject)
    {
        m_pGameObject->Draw();
    }
}

void CMemoryLeakTestScene::CreateMemoryLeak()
{
    CDebugHelper::LogConsole("Intentional Memory Leak 발생!\n");
    // 의도적으로 m_pGameObject, m_pImage, m_pColorBrushPalettet을 해제하지 않음
    // Release() 함수에서 해당 객체들의 delete 코드를 주석 처리하거나,
    // CreateMemoryLeak() 함수를 호출한 후 ReleaseMemory()를 호출하지 않으면 누수가 발생합니다.
}

void CMemoryLeakTestScene::ReleaseMemory()
{
    CDebugHelper::LogConsole("Forcefully releasing memory.\n");
    if (m_pGameObject)
    {
        m_pGameObject->Release();
        delete m_pGameObject;
        m_pGameObject = nullptr;
    }
    if (m_pImage)
    {
        delete m_pImage;
        m_pImage = nullptr;
    }
    if (m_pColorBrushPalettet)
    {
        m_pColorBrushPalettet->Release();
        delete m_pColorBrushPalettet;
        m_pColorBrushPalettet = nullptr;
    }
}