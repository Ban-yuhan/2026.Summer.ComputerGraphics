#pragma once
#include "DX2DClasses/SceneManager.h"
#include "DX2DClasses/Driect2DFramework.h"

namespace DX2DClasses
{
    class CMemoryLeakTestScene : public ISceneManager
    {
    private:
        CDriect2DFramwork* m_pDX2DFramework = nullptr;
        class CImage* m_pImage = nullptr;
        class CGameObject* m_pGameObject = nullptr;
        class CColorBrushPalettet* m_pColorBrushPalettet = nullptr;

    public:
        CMemoryLeakTestScene();
        ~CMemoryLeakTestScene();

        virtual void Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework) override;
        virtual void Release() override;
        virtual void Update() override;
        virtual void Draw() override;

        // 메모리 누수 테스트를 위한 함수 (의도적으로 해제하지 않음)
        void CreateMemoryLeak();

        // 메모리를 올바르게 해제하는 함수
        void ReleaseMemory();
    };
}