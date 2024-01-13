//==============================================================
//
//弾の処理[bullet.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _BULLET_H_		//このマクロ定義がされていなかったら
#define _BULLET_H_		//2重インクルード防止のマクロを定義する

#include "billboard.h"

//弾クラスの定義
class CBullet : public CBillboard
{
public:

	CBullet();	//コンストラクタ
	CBullet(int particleType);	//コンストラクタ(オーバーロード)
	~CBullet();	//デストラクタ

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type, int particleType);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	bool Colision(D3DXVECTOR3 pos);		//当たり判定
	bool ColisionBlockLeft(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock);		//ブロックの当たり判定(中心：[左上])
	bool ColisionBlockCenter(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock);	//ブロックの当たり判定(中心：[中央])
	bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld);		//モデルの当たり判定

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//テクスチャの番号

	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_posOld;	//位置(前回)
	int m_nLife;			//弾が消えるまでの時間
	int m_nParticleLife;	//パーティクルの寿命
	float m_fRadius;		//弾の半径
	TYPE m_type;			//誰の弾か
	int m_particleType;	//パーティクルの種類
};

#endif