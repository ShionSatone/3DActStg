//==============================================================
//
//アイテム処理[itemModel.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "itemModel.h"
#include "game.h"
#include "model.h"
#include "playerModel.h"
#include "material.h"
#include "life.h"
#include "bulletRemain.h"
#include "sound.h"
#include "score.h"

//静的メンバ変数宣言
LPD3DXMESH CItemModel::m_pMesh = NULL;						//メッシュ（頂点情報）へのポインタ
LPD3DXBUFFER CItemModel::m_pBuffMat = NULL;					//マテリアルへのポインタ
DWORD CItemModel::m_dwNumMat = NULL;
const char *CItemModel::m_pFilename[TYPE_MAX] = 			//ファイルの名前
{
	NULL,
	"data\\MODEL\\item_water.x",		//水
	"data\\MODEL\\item_ice.x",			//氷
	"data\\MODEL\\item_vepor.x",		//蒸気
	"data\\MODEL\\recovery.x",			//回復
	//NULL
};

//==============================================================
//コンストラクタ
//==============================================================
CItemModel::CItemModel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_type = TYPEITEM_NONE;	//種類
	m_nIdx = -1;				//モデルの番号
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CItemModel::CItemModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type)
{
	m_pos = pos;		//位置
	m_rot = rot;		//向き
	m_type = type;		//種類
	m_nIdx = -1;		//モデルの番号
}

//==============================================================
//デストラクタ
//==============================================================
CItemModel::~CItemModel()
{

}

//==============================================================
//アイテムの生成処理
//==============================================================
CItemModel *CItemModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type)
{
	CItemModel *pItemModel = NULL;

	if (pItemModel == NULL)
	{//メモリが使用されてなかったら

		//アイテムの生成
		pItemModel = new CItemModel(pos, rot, type);
	}

	//初期化処理
	pItemModel->Init(pos, rot);

	return pItemModel;
}

//==============================================================
//アイテムの初期化処理
//==============================================================
HRESULT CItemModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CMaterial *pMaterial = CManager::GetMaterial();

	//モデルの読み込み
	m_nIdx = pMaterial->Regit(m_pFilename[m_type]);

	//マテリアルの割り当て
	CObjectX::BindMaterial(m_nIdx);

	//オブジェクトXの初期化処理
	CObjectX::Init(pos, rot);

	//種類の設定
	CObject::SetType(CObject::TYPE_ITEM);

	return S_OK;
}

//==============================================================
//アイテムの終了処理
//==============================================================
void CItemModel::Uninit(void)
{
	//オブジェクトXの終了処理
	CObjectX::Uninit();
}

//==============================================================
//アイテムの更新処理
//==============================================================
void CItemModel::Update(void)
{
	//オブジェクトXの更新処理
	CObjectX::Update();
}

//==============================================================
//アイテムの描画処理
//==============================================================
void CItemModel::Draw(void)
{
	//オブジェクトXの描画処理
	CObjectX::Draw();
}

//==============================================================
//アイテムのヒット処理
//==============================================================
void CItemModel::Hit(void)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();
	CLife *pLife = CGame::GetLife();
	CBulletRemain *pBR = CGame::GetBulletRemain();
	CSound *pSound = CManager::GetSound();
	CScore *pScore = CGame::GetScore();

	if (m_type != TYPEITEM_LIFE/* && m_type != TYPEITEM_KEY*/)
	{//武器の種類のアイテムの時

		//SE再生
		pSound->Play(pSound->SOUND_LABEL_SE_ITEM000);

		//武器の種類変更する
		pPlayer->SetWeaponType(m_type);

		//弾回復
		pBR->SetNumBullet(-100);

		//スコア加算
		pScore->Add(1050);
	}
	else if (m_type == TYPEITEM_LIFE)
	{//回復アイテムの時

		//SE再生
		pSound->Play(pSound->SOUND_LABEL_SE_ITEM100);

		//体力増やす
		pLife->SetNum(60);

		//スコア加算
		pScore->Add(700);
	}

	//終了処理
	CItemModel::Uninit();
}