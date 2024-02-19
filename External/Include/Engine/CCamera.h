#pragma once
#include "CComponent.h"
#include "CFrustum.h"

class CCamera : public CComponent
{
private:
    CFrustum                m_Frustum;
    tRay                    m_ray;      // 마우스 방향을 향하는 직선

    int                     m_iCamIdx;          // 카메라 우선순위
    PROJ_TYPE               m_ProjType;
    UINT                    m_iLayerMask;
    float                   m_fAspectRatio;
    float                   m_fScale;           // Orthograpic 에서 사용하는 카메라 배율
    float                   m_Far;
    float                   m_Fov;
    float                   m_OrthoWidth;
    float                   m_OrthoHeight;

    Matrix                  m_matView;
    Matrix                  m_matViewInv;
    Matrix                  m_matProj;
    Matrix                  m_matProjInv;

    //vector<CGameObject*>              m_vecDeferred;
    //vector<CGameObject*>              m_vecDeferredDecal;
    map<ULONG64, vector<tInstObj>>		m_mapInstGroup_D;	    // Deferred
    map<ULONG64, vector<tInstObj>>		m_mapInstGroup_F;	    // Foward ( Opaque, Mask )	
    map<INT_PTR, vector<tInstObj>>		m_mapSingleObj;		    // Single Object

    vector<CGameObject*>                m_vecOpaque;
    vector<CGameObject*>                m_vecMask;
    vector<CGameObject*>                m_vecDecal;
    vector<CGameObject*>                m_vecTransparent;    
    vector<CGameObject*>                m_vecUI;
    vector<CGameObject*>                m_vecPost;

    vector<CGameObject*>                m_vecShadow;            // 이건 안쓸듯
    map<ULONG64, vector<tInstObj>>		m_mapInstGroup_S;	    // Deferred
    map<INT_PTR, vector<tInstObj>>		m_mapSingleObj_S;		// Single Object

public:
    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }
    PROJ_TYPE GetProjType() { return m_ProjType; }

    void SetScale(float _fScale) { m_fScale = _fScale; }
    float GetScale() { return m_fScale; }

    void SetFar(float _Far) { m_Far = _Far; }
    float GetFar() { return m_Far; }

    void SetLayerMask(int _iLayer, bool _Visible);
    void SetLayerMaskAll(bool _Visible);

    void SetCameraIndex(int _idx);

    const tRay& GetRay() { return m_ray; }
    // 추후에 degree 변환 기능 추가하기
    void SetFov(float _Radian) { m_Fov = _Radian; }
    float GetFov() { return m_Fov; }

    void SetOrthoWidth(float _width) { m_OrthoWidth = _width; }
    void SetOrthoHeight(float _height) { m_OrthoHeight = _height; }

    float GetorthoWidth() { return m_OrthoWidth; }
    float GetOrthoHeight() { return m_OrthoHeight; }


    const Matrix& GetViewMat() { return m_matView; }
    const Matrix& GetProjMat() { return m_matProj; }

    const Matrix& GetViewInvMat() { return m_matViewInv; }
    const Matrix& GetProjInvMat() { return m_matProjInv; }

public:
    void SortObject();
    void SortObject_Shadow();
    void render();
    void render_shadowmap();


public:
    virtual void begin() override;
    virtual void finaltick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

protected:
    void CalRay();  // 마우스 방향으로 광선 연산

private:
    void clear();
    void clear_shadow();

    void render_deferred();
    void render_forward();

    void geometryRender();  // 함수 크기 줄이려고 만든것
    void lightRender();     // 
    void mergeRender();     // 

    //void render_opaque();
    //void render_mask();
    void render_decal();
    void render_transparent();
    void render_postprocess();
    void render_ui();


    void CalcViewMat();
    void CalcProjMat();
    void updateMatrix();

    

    CLONE(CCamera);
public:    
    CCamera();
    CCamera(const CCamera& _Other);
    ~CCamera();
};

