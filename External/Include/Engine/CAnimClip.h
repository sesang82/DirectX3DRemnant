#pragma once
#include "CRes.h"

#include "ptr.h"
#include "CMaterial.h"
#include "CMesh.h"
#include "CStructuredBuffer.h"

struct tAnim3DData
{
    int                         AnimClipIdx;        // Ŭ�� �ε��� (���� ���� ���)
    float                       BeginTime;          // Ŭ���� ���۽ð�
    float                       EndTime;            // Ŭ���� ����ð�

    float                       FinishTime;         // �ִϸ��̼� ����ð�

    tAnim3DData() : AnimClipIdx(0), BeginTime(0.f), EndTime(0.f), FinishTime(0.f)
    {}
    ~tAnim3DData() {}
};

class CAnimator3D;
class CStructuredBuffer;
class CAnimClip : public CRes
{
private:
    CAnimator3D*                m_Owner;
    Ptr<CMesh>                  m_originMesh;

    // �ִϸ��̼� ����
    string                      m_AnimName;             // Gui�� ����ϴ� �뵵
    tAnim3DData                 m_AnimData;

    int							m_iFrameCount;          // ���� ������ (30 ����)
    vector<float>				m_AnimUpdateTime;       // �ִϸ��̼� ���� �����ð�

    int							m_CurFrameIdx;          // ���� �������� ������
    int							m_NextFrameIdx;         // ���� ������ �ε���
    float						m_Ratio;                // �� �����Ӱ� ���൵ ����

    // �ִϸ��̼� ���� ����
    bool                        m_Finish;


public:
    int finaltick();

    // �ִϸ����Ϳ��� ����ϴ� �Լ�
public:
    void NewAnimClip(const wstring& _strAnimName, int _clipIdx, float _startTime, float _endTime, Ptr<CMesh> _pMesh);
    void Edit(float _begin, float _end);

public: 
    bool IsFinish() { return m_Finish; }

    // ������ �ִϸ��̼��� �ʱ���·� ��������, �����Ű�� ����
    void Reset() { m_AnimUpdateTime[m_AnimData.AnimClipIdx] = 0.f; m_Finish = false; }
    void TimeClear() { m_AnimUpdateTime[m_AnimData.AnimClipIdx] = 0.f; }

    
    int ConvertTimeToFrame(float _idxTime);
    const int& GetStartFrame();
    const int& GetCurFrame() { return m_CurFrameIdx; }
    const int& GetNextFrame() { return m_NextFrameIdx; }
    const float& GetFrameRatio() { return m_Ratio; }

    // GUI�� �����Ű�� �Լ�
public: 
    // MT ����
    Ptr<CMesh> GetOriginMesh() { return m_originMesh; }
    vector<tMTAnimClip> GetMTAnimClips() { return m_originMesh.Get()->GetMTAnimClips(); }

    // Ŭ�� ����
    void SetAnimName(const string& _name) { m_AnimName = _name; }
    const string& GetAnimName() { return m_AnimName; }
    int GetClipIdx() { return m_AnimData.AnimClipIdx; }
    const float& GetBeginTime() { return m_AnimData.BeginTime; }
    const float& GetEndTime() { return m_AnimData.EndTime; }

    // �ִ� ����
    const float& GetFinishTime() { return m_AnimData.FinishTime; }
    const float& GetCurTime() { return m_AnimUpdateTime[m_AnimData.AnimClipIdx]; }

public:
    int Save(const wstring& _strRelativePath);
    int Load(const wstring& _strFilePath);


    CLONE(CAnimClip);
public:
    CAnimClip(bool _bEngine = false);
    ~CAnimClip();

    friend class CAnimator3D;
};
