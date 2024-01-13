//==============================================================
//
//投影スイッチ処理[switch.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _SWITCH_H_		//このマクロ定義がされていなかったら
#define _SWITCH_H_		//2重インクルード防止のマクロを定義する

#include"objectX.h"

//投影スイッチクラスの定義
class CSwitch : CObjectX
{
public:

	CSwitch();		//コンストラクタ
	CSwitch(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//コンストラクタ(オーバーロード)
	~CSwitch();		//デストラクタ

	static CSwitch *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);

private:

	static int m_nNumAll;			//モデルの種類

	static LPD3DXMESH m_pMesh;			//メッシュ（頂点情報）へのポインタ
	static LPD3DXBUFFER m_pBuffMat;		//マテリアルへのポインタ
	static DWORD m_dwNumMat;			//マテリアルの数
	static const char *m_pFilename;		//ファイル名

	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_rot;			//向き
	int m_nMaxModel;			//モデルの設置数
	int m_nIdx;					//モデルの番号

	int m_type;			//アイテムの種類
};

#endif