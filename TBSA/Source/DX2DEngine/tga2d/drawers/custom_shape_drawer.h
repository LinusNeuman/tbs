#pragma once
#include "render/render_common.h"
#include "shaders/Shader.h"

namespace DX2D
{
    struct ObjectBufferTypeCustomShape
    {
        Vector4f myRotationAndSize;
        Vector2f myPosition;
        Vector2f myDummy;
    };

    class CDirectEngine;
    class CCustomShape;
    class CRenderObjectCustom;
    class CCustomShapeDrawer : public CShader
    {
    public:
        CCustomShapeDrawer(CEngine* anEngine);
        ~CCustomShapeDrawer();
        bool Init();
        void Draw(CRenderObjectCustom* aObject);
    private:
        CCustomShapeDrawer &operator =( const CCustomShapeDrawer &anOther ) = delete;

        bool CreateInputLayout(ID3D10Blob* aVS) override;
        bool InitShaders();
        void CreateBuffer();

        int SetShaderParameters(CRenderObjectCustom* aObject);
        int UpdateVertexes(CRenderObjectCustom* aObject);
        ID3D11Buffer *myVertexBuffer;    // global
        CDirectEngine& myEngine;
        ID3D11Buffer* myObjectBuffer;
        int myMaxPoints;
    };
}