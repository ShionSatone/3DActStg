//==============================================================
//
//敵の処理[enemy.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _ENEMY_H_		//このマクロ定義がされていなかったら
#define _ENEMY_H_		//2重インクルード防止のマクロを定義する

#include "object2D.h"

//マクロ定義
#define WIDTH_ENEMY		(100.0f * 0.5f)		//敵の横幅
#define HEIGHT_ENEMY	(100.0f * 0.5f)		//敵の縦幅

//敵クラス
class CEnemy : public CObject2D
{
public:
	CEnemy();	//コンストラクタ
	~CEnemy();	//デストラクタ

	static HRESULT Load(void);		//テクスチャの読み込み
	static void Unload(void);		//テクスチャの破棄
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//テクスチャの番号

	//D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_pos;		//位置
};

#endif