#pragma once
#include "CRenderComponent.h"

#include "ptr.h"
#include "CParticleUpdateShader.h"

class CStructuredBuffer;
class CParticleUpdateShader;
class CTexture;

class CParticleSystem :
    public CRenderComponent
{
private:
    CStructuredBuffer*          m_ParticleBuffer;
    CStructuredBuffer*          m_RWBuffer;
    CStructuredBuffer*          m_ModuleDataBuffer;
    
    tParticleModule             m_ModuleData;
    tRWParticleBuffer		    m_RWPrticleBuffer;
    Ptr<CParticleUpdateShader>  m_UpdateCS; // 파티클 업데이트 셰이더
   
    float                       m_AccTime;
    float                       m_SpawnTime;

    Ptr<CTexture>               m_ParticleTex;
    Ptr<CTexture>               m_NoiseTex;

    bool                        m_bOnceExcute;
    bool                        m_bBursts;
    bool                        m_bLoop;
    bool                        m_bUseSpark; // 스파크처럼 튀는거 만들때는 이 옵션을 킬 것

    



public:
    virtual void finaltick() override;
    virtual void render() override;
    virtual void render(UINT _iSubset) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CParticleSystem);


public:
    float RandomFloat(float min, float max);

    void SetParticleTex(Ptr<CTexture> _Tex)
    {
        m_ParticleTex = _Tex;
    }

    void SetNoiseTex(Ptr<CTexture> _Tex)
    {
        m_NoiseTex = _Tex;
    }

    void SetModuleData(tParticleModule _ModuleData)
    {
        m_ModuleData = _ModuleData;
    }


    Ptr<CTexture> GetParticleTex() const
    {
        return m_ParticleTex;
    }

    tParticleModule GetModuleData() const
    {
        return m_ModuleData;
    }

    Ptr<CParticleUpdateShader> GetUpdateCS() const
    {
		return m_UpdateCS;
	}

    CStructuredBuffer* GetParticleBuffer() const
    {
        		return m_ParticleBuffer;
    }

    void SetOnceExcute(bool _bOnceExcute) { m_bOnceExcute = _bOnceExcute; }
    bool GetOnceExcute() const { return m_bOnceExcute; }

    void SetBursts(bool _bBursts) { m_bBursts = _bBursts; }
    bool GetBursts() const { return m_bBursts; }

    void SetSpawnTime(float _fSpawnTime) { m_SpawnTime = _fSpawnTime; }
    float GetSpawnTime() const { return m_SpawnTime; }

    void SetLoop(bool _bLoop) { m_bLoop = _bLoop; }
    bool GetLoop() const { return m_bLoop; }

    Vec3 CreateRandomDirection(const Vector3& normal, float openAngle);

    void SetUseSpark(bool _bUseSpark) { m_bUseSpark = _bUseSpark; }
    bool GetUseSpark() const { return m_bUseSpark; }




public:
    CParticleSystem();
    CParticleSystem(const CParticleSystem& _other);
    virtual ~CParticleSystem();
};

