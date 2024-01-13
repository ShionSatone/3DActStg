//==============================================================
//
//数字処理[number.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _NUMBER_H_		//このマクロ定義がされていなかったら
#define _NUMBER_H_		//2重インクルード防止のマクロを定義する

#include "object.h"

//数字クラス
class CNumber : public CObject
{
public:
	CNumber();	//コンストラクタ
	//CNumber(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//コンストラクタ（オーバーロード）
	~CNumber();	//デストラクタ

	static CNumber *Create(void);		//生成処理

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	virtual void Uninit(void);		//終了処理
	virtual void Update(void);		//更新処理
	virtual void Draw(void);		//描画処理

	void BindTexture(int nIdxTexture);		//外部からテクスチャ指定
	void SetSize(float fWidth, float fHeight) { m_fHeight = fHeight; m_fWidth = fWidth; }	//オブジェクトのサイズ設定

	void SetTex(TYPE type, int nPatternAnim, float nDigitX);		//アニメーション
	void SetType(float fTexU, float fTexV);			//多重背景

	void SetPosition(TYPE type, D3DXVECTOR3 pos, float fWidth, float fHeight);	//位置設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//位置取得
	void SetColor(TYPE type, D3DXCOLOR col);		//色設定
	D3DXCOLOR GetColor(void) { return m_col; }		//色取得

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ

	int m_nIdxTexture;		//テクスチャの番号

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//向き
	D3DXCOLOR m_col;		//色
	float m_fHeight;		//縦幅
	float m_fWidth;			//横幅
	TYPE m_type;			//種類
};

#endif
