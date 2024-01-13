//==============================================================
//
//残機処理[remain.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _REMAIN_H_		//このマクロ定義がされていなかったら
#define _REMAIN_H_		//2重インクルード防止のマクロを定義する

#include "object2D.h"

//残機クラス
class CRemain : public CObject2D
{
public:
	CRemain();	//コンストラクタ
	~CRemain();	//デストラクタ

	static CRemain *Create(D3DXVECTOR3 pos, int nIdx);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

	void SetMax(int nMaxRemain) { m_nNum = nMaxRemain; }		//残機の最大数
	int GetNum(void) { return m_nNum; }							//残機

private:
	int m_nIdxTexture;		//テクスチャの番号

	static int m_nNum;		//残機の数
	D3DXVECTOR3 m_pos;		//位置
};

#endif