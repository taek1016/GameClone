#include "stdafx.h"
#include "AnimationNode.h"
#include "GameObject.h"

USING(Engine)

CAnimationNode::CAnimationNode(CGameObject* obj)
{
	m_pTransform = obj->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
}

CAnimationNode::CAnimationNode()
{
	m_pTransform = nullptr;
}

CAnimationNode::~CAnimationNode()
{
	
}

CAnimationNode::CAnimationNode(const CAnimationNode & rhs)
	: CBase(rhs),
	m_StartInfo(rhs.m_StartInfo),
	m_EndInfo(rhs.m_EndInfo),
	m_fTime(rhs.m_fTime),
	m_vecAnimTransformInfo(rhs.m_vecAnimTransformInfo)
{

}

void CAnimationNode::SetAnimTransform(ANIMTRANSFORM animTrans)
{
	m_bTransform[animTrans] = true;
}

void CAnimationNode::SetAnimInfo(ANIM_TRANSFORM_INFO start, ANIM_TRANSFORM_INFO end, float fTime, int interval)
{
	m_vecAnimTransformInfo.clear();

	m_StartInfo = start;
	m_EndInfo = end;
	m_fTime = fTime;
	m_fCurTime = 0.f;
	m_iAnimInterval = interval;
	m_bEnd = false;

	_vec3 lengthPos = m_EndInfo.vPosition - m_StartInfo.vPosition;
	_vec3 lengthRot = m_EndInfo.vRotation - m_StartInfo.vRotation;
	_vec3 lengthScale = m_EndInfo.vScale - m_StartInfo.vScale;

	_vec3 pos = m_StartInfo.vPosition;
	_vec3 rot = m_StartInfo.vRotation;
	_vec3 scale = m_StartInfo.vScale;

	float offset = 1.f / m_iAnimInterval;
	for (int i = 0; i < m_iAnimInterval; i++)
	{
		ANIM_TRANSFORM_INFO info;

		pos += lengthPos * offset;
		rot += lengthRot * offset;
		scale += lengthScale * offset;

		info.vPosition = pos;
		info.vRotation = rot;
		info.vScale = scale;

		m_vecAnimTransformInfo.push_back(info);
	}
}

void CAnimationNode::Play()
{
	if (m_pTransform == nullptr)
		return;
	m_bEnd = false;
	if(m_bTransform[TRANS_POS])
		m_pTransform->Set_Pos(&m_StartInfo.vPosition);

	if (m_bTransform[TRANS_ROT])
	{
		m_pTransform->Set_Angle(ROTATION::ROT_X, D3DXToRadian(m_StartInfo.vRotation.x));
		m_pTransform->Set_Angle(ROTATION::ROT_Y, D3DXToRadian(m_StartInfo.vRotation.y));
		m_pTransform->Set_Angle(ROTATION::ROT_Z, D3DXToRadian(m_StartInfo.vRotation.z));
	}

	if (m_bTransform[TRANS_SCALE])
		m_pTransform->Set_Scale(m_StartInfo.vScale.x, m_StartInfo.vScale.y, m_StartInfo.vScale.z);

	
}

void CAnimationNode::Stop()
{
	m_iCurIndex = 0;
}

void CAnimationNode::Action(const float& fDeltaTime)
{
	if (m_pTransform == nullptr)
	{
		return;
	}
	m_fCurTime += fDeltaTime;
	//if (m_fCurTime >= m_fTime && !m_bEnd)
	{
		if (m_bTransform[TRANS_POS])
			m_pTransform->Set_Pos(&m_vecAnimTransformInfo[m_iCurIndex].vPosition);

		if (m_bTransform[TRANS_ROT])
		{
			m_pTransform->Set_Angle(ROTATION::ROT_X, D3DXToRadian(m_vecAnimTransformInfo[m_iCurIndex].vRotation.x));
			m_pTransform->Set_Angle(ROTATION::ROT_Y, D3DXToRadian(m_vecAnimTransformInfo[m_iCurIndex].vRotation.y));
			m_pTransform->Set_Angle(ROTATION::ROT_Z, D3DXToRadian(m_vecAnimTransformInfo[m_iCurIndex].vRotation.z));
		}

		if (m_bTransform[TRANS_SCALE])
			m_pTransform->Set_Scale(&m_vecAnimTransformInfo[m_iCurIndex].vScale);
		m_iCurIndex++;
		m_fCurTime = 0;
		if (static_cast<size_t>(m_iCurIndex) >= m_vecAnimTransformInfo.size())
		{
			m_iCurIndex = 0;
			m_bEnd = true;
		}
	}
}

void CAnimationNode::Initialize()
{
	ZeroMemory(&m_StartInfo, sizeof(ANIM_TRANSFORM_INFO));
	ZeroMemory(&m_EndInfo, sizeof(ANIM_TRANSFORM_INFO));
	m_fTime = 0.f;
	m_iAnimInterval = 0;
}

void CAnimationNode::SaveData(HANDLE hFile)
{
	DWORD dwBytes = 0;

	WriteFile(hFile, &m_fTime, sizeof(m_fTime), &dwBytes, nullptr);

	WriteFile(hFile, &m_iAnimInterval, sizeof(m_iAnimInterval), &dwBytes, nullptr);

	WriteFile(hFile, &m_StartInfo, sizeof(ANIM_TRANSFORM_INFO), &dwBytes, nullptr);

	WriteFile(hFile, &m_EndInfo, sizeof(ANIM_TRANSFORM_INFO), &dwBytes, nullptr);

	WriteFile(hFile, m_bTransform, sizeof(bool) * 3, &dwBytes, nullptr);

	int size = m_vecAnimTransformInfo.size();
	WriteFile(hFile, &size, sizeof(int), &dwBytes, nullptr);

	int index = 0;
	auto iter = m_vecAnimTransformInfo.begin();
	while (iter != m_vecAnimTransformInfo.end())
	{
		WriteFile(hFile, &m_vecAnimTransformInfo[index++], sizeof(ANIM_TRANSFORM_INFO), &dwBytes, nullptr);
		iter++;
	}
}

void CAnimationNode::LoadData(HANDLE hFile)
{
	DWORD dwBytes = 0;
	m_fTime = 0;
	ReadFile(hFile, &m_fTime, sizeof(m_fTime), &dwBytes, nullptr);

	ReadFile(hFile, &m_iAnimInterval, sizeof(m_iAnimInterval), &dwBytes, nullptr);

	ReadFile(hFile, &m_StartInfo, sizeof(ANIM_TRANSFORM_INFO), &dwBytes, nullptr);

	ReadFile(hFile, &m_EndInfo, sizeof(ANIM_TRANSFORM_INFO), &dwBytes, nullptr);

	ReadFile(hFile, m_bTransform, sizeof(bool) * 3, &dwBytes, nullptr);

	int size = 0;
	ReadFile(hFile, &size, sizeof(int), &dwBytes, nullptr);

	int index = 0;
	for(int i=0;i<size;i++)
	{
		ANIM_TRANSFORM_INFO info;
		ReadFile(hFile, &info, sizeof(ANIM_TRANSFORM_INFO), &dwBytes, nullptr);
		m_vecAnimTransformInfo.push_back(info);
	}
}

void CAnimationNode::freeMem(void)
{
	m_pTransform = nullptr;
}
