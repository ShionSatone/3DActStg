//==============================================================
//
//プレイヤー処理[player.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _PLAYER_H_		//このマクロ定義がされていなかったら
#define _PLAYER_H_		//2重インクルード防止のマクロを定義する

#include "object2D.h"

//マクロ定義
#define WIDTH_PLAYER	(100.0f * 0.5f)		//プレイヤーの横幅
#define HEIGHT_PLAYER	(150.0f)			//プレイヤーの縦幅

//プレイヤークラス
class CPlayer : public CObject2D
{
public:
	CPlayer();	//コンストラクタ
	CPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//コンストラクタ（オーバーロード）
	~CPlayer();	//デストラクタ

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void Control(void);		//入力処理
	void Screen(void);		//画面外判定

	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//位置の取得

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//テクスチャの番号

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_posOld;	//位置（前回）
	D3DXVECTOR3 m_rot;		//向き
	D3DXVECTOR3 m_move;		//移動量

	int m_nCounterAnim;		//アニメーションカウンター
	int m_nPatternAnim;		//パターンNo.カウンター
	int m_nRandSpeed;		//位置のランダムな速さ	
	float m_fRandCol;		//ランダムな色
	float m_fRandRot;		//ランダムな向き
	bool m_bJump;			//ジャンプしたかの判定
};

#endif