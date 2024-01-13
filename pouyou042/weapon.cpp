//==============================================================
//
//武器の種類表示処理[weapon.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "weapon.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "object.h"
#include "texture.h"
#include "playerModel.h"
#include "game.h"

//マクロ定義
#define WIDTH_WEAPON		(100.0f * 0.5f)		//横幅
#define HEIGHT_WEAPON		(100.0f * 0.5f)		//縦幅

//静的メンバ変数宣言
CObject2D *CWeapon::m_apObject2D[NUM_WEAPON] = {};
LPDIRECT3DTEXTURE9 CWeapon::m_pTexture[NUM_WEAPON] = {};		//テクスチャ

//==============================================================
//コンストラクタ
//==============================================================
CWeapon::CWeapon()
{
	//変数初期化
	//m_pos = D3DXVECTOR3(WIDTH_WEAPON, HEIGHT_WEAPON, 0.0f);		//位置

	for (int nCntBg = 0; nCntBg < NUM_WEAPON; nCntBg++)
	{
		m_nIdxTexture[nCntBg] = -1;		//テクスチャの番号
	}
}

//==============================================================
//デストラクタ
//==============================================================
CWeapon::~CWeapon()
{

}

//==============================================================
//武器の種類表示のテクスチャの読み込み
//==============================================================
//HRESULT CWeapon::Load(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//デバイスの取得
//
//	if (m_pTexture[0] == NULL || m_pTexture[1] == NULL || m_pTexture[2] == NULL)
//	{//テクスチャ設定されてないとき
//
//		//テクスチャの読み込み
//		D3DXCreateTextureFromFile(pDevice,
//			"data\\TEXTURE\\bg100.png",
//			&m_pTexture[0]);
//
//		D3DXCreateTextureFromFile(pDevice,
//			"data\\TEXTURE\\bg101.png",
//			&m_pTexture[1]);
//
//		D3DXCreateTextureFromFile(pDevice,
//			"data\\TEXTURE\\bg102.png",
//			&m_pTexture[2]);
//	}
//
//	return S_OK;
//}

//==============================================================
//武器の種類表示のテクスチャの破棄
//==============================================================
//void CWeapon::Unload(void)
//{
//	//テクスチャの破棄
//	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
//	{
//		if (m_pTexture[nCntBg] != NULL)
//		{
//			m_pTexture[nCntBg]->Release();
//			m_pTexture[nCntBg] = NULL;
//		}
//	}
//}

//==============================================================
//生成処理
//==============================================================
CWeapon *CWeapon::Create(D3DXVECTOR3 pos)
{
	CWeapon *pWeapon = NULL;

	if (pWeapon == NULL)
	{//メモリが使用されてなかったら

		//武器の種類表示の生成
		pWeapon = new CWeapon;

		//初期化処理
		pWeapon->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		//種類設定
		pWeapon->SetType(TYPE_NONE);
	}

	return pWeapon;
}

//==============================================================
//武器の種類表示の初期化処理
//==============================================================
HRESULT CWeapon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	//テクスチャの読み込み
	m_nIdxTexture[0] = pTexture->Regit("data\\TEXTURE\\weapon00.png");
	m_nIdxTexture[1] = pTexture->Regit("data\\TEXTURE\\weapon01.png");
	m_nIdxTexture[2] = pTexture->Regit("data\\TEXTURE\\weapon02.png");

	//初期化処置
	for (int nCntBg = 0; nCntBg < NUM_WEAPON; nCntBg++)
	{
		if (m_apObject2D[nCntBg] == NULL)
		{//使用されてないとき

			//2Dオブジェクト生成
			m_apObject2D[nCntBg] = CObject2D::Create();

			if (m_apObject2D[nCntBg] != NULL)
			{//生成出来たら

				//大きさ設定
				m_apObject2D[nCntBg]->SetSize(WIDTH_WEAPON, HEIGHT_WEAPON);

				//位置設定
				m_apObject2D[nCntBg]->SetPosition(CObject::TYPE_ITEM, pos, WIDTH_WEAPON, HEIGHT_WEAPON);

				if ((pPlayer->GetWeaponType() - 1) != nCntBg)
				{//現在の武器の種類と画像の番号が違う

					//色透明にする
					m_apObject2D[nCntBg]->SetColor(CObject::TYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}

				//テクスチャ割り当て
				m_apObject2D[nCntBg]->BindTexture(m_nIdxTexture[nCntBg]);
			}
		}
	}

	//種類設定
	CObject::SetType(CObject::TYPE_ITEM);

	return S_OK;
}

//==============================================================
//武器の種類表示の終了処理
//==============================================================
void CWeapon::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < NUM_WEAPON; nCntBg++)
	{
		if (m_apObject2D[nCntBg] != NULL)
		{//使用されてるとき

			//終了処理
			m_apObject2D[nCntBg]->Uninit();
			m_apObject2D[nCntBg] = NULL;
		}
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//武器の種類表示の更新処理
//==============================================================
void CWeapon::Update(void)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	for (int nCntBg = 0; nCntBg < NUM_WEAPON; nCntBg++)
	{
		if (m_apObject2D[nCntBg] != NULL)
		{
			if ((pPlayer->GetWeaponType() - 1) != nCntBg)
			{//現在の武器の種類と画像の番号が違う

				//色透明にする
				m_apObject2D[nCntBg]->SetColor(CObject::TYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
			else if((pPlayer->GetWeaponType() - 1) == nCntBg)
			{
				//色半透明にする
				m_apObject2D[nCntBg]->SetColor(CObject::TYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}
}

//==============================================================
//武器の種類表示の描画処理
//==============================================================
void CWeapon::Draw(void)
{
	
}

//==============================================================
//テクスチャ割り当て処理
//==============================================================
void CWeapon::BindTexture(LPDIRECT3DTEXTURE9 pTexture, int nCount)
{
	m_pTexture[nCount] = pTexture;		//テクスチャ割り当て
}