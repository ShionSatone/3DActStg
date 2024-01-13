//==============================================================
//
//弾の処理[bullet.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "enemyModel.h"
#include "effect.h"
#include "particle.h"
#include "sound.h"
#include "score.h"
#include "texture.h"
#include "objectX.h"
#include "debugproc.h"
#include "bulletRemain.h"
#include "game.h"
#include "camera.h"

//マクロ定義
#define WIDTH_BULLET	(50.0f * 0.5f)		//弾の横幅
#define HEIGHT_BULLET	(50.0f * 0.5f)		//弾の縦幅
#define NUM_PATTERN		(10)				//パターン数
#define MOVE_SPEED		(3.0f)				//弾の移動速度
#define ANGLE_UP		(0.75f)				//上の角度
#define ANGLE_DOWN		(0.25f)				//下の角度
#define ANGLE_WIDTH		(0.5f)				//横の角度
#define DEST_WATER		(50)				//水が消滅するまでの時間
#define DEST_ICE		(40)				//氷が消滅するまでの時間
#define DEST_VAPOR		(40)				//蒸気が消滅するまでの時間
#define DEST_ENEMY		(70)				//敵の弾が消滅するまでの時間
#define RADIUS_WATER	(25.0f)				//水の半径
#define RADIUS_ICE		(10.0f)				//氷の半径
#define RADIUS_VAPOR	(30.0f)				//蒸気の半径
#define RADIUS_ENEMY	(25.0f)				//敵の弾の半径

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;		//テクスチャ

//==============================================================
//コンストラクタ
//==============================================================
CBullet::CBullet()
{
	m_nIdxTexture = -1;		//テクスチャの番号
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置(前回)
	m_move = D3DXVECTOR3(5.0f, 0.0f, 0.0f);	//移動量
	m_nLife = DEST_WATER;		//弾消滅の時間
	m_particleType = PARTICLETYPE_NONE;		//パーティクルの種類
	m_fRadius = WIDTH_BULLET;		//弾の半径
	m_nParticleLife = 8;		//パーティクルの寿命
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CBullet::CBullet(int particleType)
{
	m_nIdxTexture = -1;		//テクスチャの番号
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置(前回)
	m_particleType = particleType;		//パーティクルの種類

	//弾消滅の時間
	switch (m_particleType)
	{
	case PARTICLETYPE_NONE:		//何もなし

		break;

	case PARTICLETYPE_WATER:		//水

		m_nLife = DEST_WATER;
		m_fRadius = RADIUS_WATER;
		m_nParticleLife = 8;

		break;

	case PARTICLETYPE_ICE:			//氷

		m_nLife = DEST_ICE;
		m_fRadius = RADIUS_ICE;
		m_nParticleLife = 14;

		break;

	case PARTICLETYPE_VAPOR:		//蒸気

		m_nLife = DEST_VAPOR;
		m_fRadius = RADIUS_VAPOR;
		m_nParticleLife = 8;

		break;

	case PARTICLETYPE_ENEMY:		//敵の弾

		m_nLife = DEST_ENEMY;
		m_fRadius = RADIUS_ENEMY;
		m_nParticleLife = 8;

		break;

	case PARTICLETYPE_WITCH:		//魔女の弾

		m_nLife = DEST_ENEMY;
		m_fRadius = RADIUS_ENEMY;
		m_nParticleLife = 10;

		break;
	}
}

//==============================================================
//デストラクタ
//==============================================================
CBullet::~CBullet()
{

}

//==============================================================
//弾の生成処理
//==============================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, int particleType)
{
	CBullet *pBullet = NULL;

	if (pBullet == NULL)
	{//メモリが使用されてなかったら

		//弾の生成
		pBullet = new CBullet(particleType);
	}

	//初期化処理
	pBullet->Init(pos, move, type);

	return pBullet;
}

//==============================================================
//弾の初期化処理
//==============================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type)
{
	CTexture *pTexture = CManager::GetTexture();
	CBulletRemain *pBulletRemain = CGame::GetBulletRemain();

	m_type = type;		//種類

	//テクスチャの読み込み
	switch (m_particleType)
	{
	case PARTICLETYPE_NONE:			//何もなし

		m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\bullet000.png");

		break;

	case PARTICLETYPE_WATER:		//水

		m_nIdxTexture = pTexture->TEX_WATER;

		break;

	case PARTICLETYPE_ICE:			//氷

		m_nIdxTexture = pTexture->TEX_ICE;

		break;

	case PARTICLETYPE_VAPOR:		//蒸気

		m_nIdxTexture = pTexture->TEX_VAPOR;

		break;

	case PARTICLETYPE_ENEMY:		//敵の弾

		m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\bullet002.png");

		break;

	case PARTICLETYPE_WITCH:		//魔女の弾

		m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\bullet003.png");

		break;
	}

	//テクスチャの割り当て
	CBillboard::BindTexture(m_nIdxTexture);

	//ビルボードの初期化処理
	CBillboard::Init(pos, move);

	//種類の設定
	CObject::SetType(CObject::TYPE_BULLET);

	//弾の大きさ設定
	CBillboard::SetSize(WIDTH_BULLET, HEIGHT_BULLET);

	//弾の移動量代入
	CBillboard::SetMove(move);

	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (m_particleType != PARTICLETYPE_ENEMY && m_particleType != PARTICLETYPE_NONE && m_particleType != PARTICLETYPE_WITCH)
		{
			//弾の消費数加算
			pBulletRemain->SetNumBullet(10);
		}
	}

	return S_OK;
}

//==============================================================
//弾の終了処理
//==============================================================
void CBullet::Uninit(void)
{
	//ビルボードの終了処理
	CBillboard::Uninit();
}

//==============================================================
//弾の更新処理
//==============================================================
void CBullet::Update(void)
{
	//消滅までの時間減算
	m_nLife--;

	//位置取得
	m_pos = CBillboard::GetPosition();
	m_move = CBillboard::GetMove();

	m_posOld = m_pos;		//現在の位置		

	//位置更新
	m_pos += m_move;

	//位置設定
	CBillboard::SetPosition(CObject::TYPE_BULLET, m_pos);

	//ビルボードの更新処理
	CBillboard::Update();

	//弾削除
	if (m_nLife <= 0)
	{//画面外に出たら || 弾が消滅する時間になったら

		if (m_nLife <= 0 && m_type != TYPE_ENEMY)
		{
			//爆発の生成
			CParticle::Create(m_pos, D3DXCOLOR(0.0f, 0.7f, 0.5f, 1.0f), PARTICLETYPE_EXPLOSION, 0, 13);
		}

		//弾の終了処理
		CBullet::Uninit();
	}
	else
	{//まだ弾が消滅してなかったら

		//敵との当たり判定
		if (CBullet::CollisionModel(&m_pos, &m_posOld) == true)
		{//敵と当たったら

			//弾の終了処理
			CBullet::Uninit();
		}
	}

	//エフェクトの生成
	CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fRadius, m_nParticleLife, m_particleType);
}

//==============================================================
//弾の描画処理
//==============================================================
void CBullet::Draw(void)
{
	//ビルボードの描画処理
	CBillboard::Draw();
}

//==============================================================
//当たり判定
//==============================================================
bool CBullet::Colision(D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		CObject *pObj;

		//オブジェクトを取得
		pObj = GetObject(nCntObj);

		if (pObj != NULL)
		{//メモリが使用されているとき

			CObject::TYPE type;

			//種類を取得
			type = pObj->GetType();

			if (type == pObj->TYPE_ENEMY)
			{//種類が敵の場合

				//敵の位置取得
				D3DXVECTOR3 posEnemy = pObj->GetPosition();

				if (pos.x >= posEnemy.x - WIDTH_ENEMY && pos.x <= posEnemy.x + WIDTH_ENEMY &&
					pos.y >= posEnemy.y - HEIGHT_ENEMY && pos.y <= posEnemy.y + HEIGHT_ENEMY)
				{//敵と弾が当たった

					//SE再生
					CSound::Play(CSound::SOUND_LABEL_SE_DAMAGE000);

					//爆発の生成
					CExplosion::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//パーティクルの生成
					CParticle::Create(pos, D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f), m_particleType, 100, 20.0f);

					//スコア加算
					CScore::Add(50000);

					//敵の終了処理
					pObj->Uninit();

					//弾の終了処理
					CBillboard::Uninit();

					return true;
				}
			}
			else if (type == pObj->TYPE_BLOCK)
			{//種類がブロックのとき

				//敵の位置取得
				D3DXVECTOR3 posBlock = pObj->GetPosition();

				//ブロックの当たり判定(左上)
				if (CBullet::ColisionBlockLeft(pos, posBlock) == true)
				{//当たってたら

					//SE再生
					CSound::Play(CSound::SOUND_LABEL_SE_DAMAGE000);

					//爆発の生成
					CExplosion::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//弾の終了処理
					CBillboard::Uninit();

					return true;
				}
			}

		}
	}

	return false;
}

//==============================================================
//ブロックの当たり判定(中心：[左上])
//==============================================================
bool CBullet::ColisionBlockLeft(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock)
{
	if (pos.x + WIDTH_BULLET >= posBlock.x && pos.x - WIDTH_BULLET <= posBlock.x + 100.0f &&
		pos.y >= posBlock.y && pos.y - HEIGHT_BULLET <= posBlock.y + 100.0f)
	{//当たったら

		return true;
	}

	return false;
}

//==============================================================
//ブロックの当たり判定(中心：[中央])
//==============================================================
bool CBullet::ColisionBlockCenter(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock)
{
	if (pos.x >= posBlock.x - 100.0f && pos.x <= posBlock.x + 100.0f &&
		pos.y >= posBlock.y - 100.0f && pos.y <= posBlock.y + 100.0f)
	{//当たったら

		return true;
	}

	return false;
}

//==============================================================
//モデルの当たり判定
//==============================================================
bool CBullet::CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();
	CCamera *pCamera = CManager::GetCamera();
	CSound *pSound = CManager::GetSound();

	for (int nCntModel = 0; nCntModel < MAX_OBJECT; nCntModel++)
	{
		//オブジェクトを取得
		CObject *pObj = GetObject(nCntModel);

		if (pObj != NULL)
		{//メモリが使用されているとき

			//種類を取得
			CObject::TYPE type = pObj->GetType();

			//プレイヤーの弾
			if (m_type == TYPE_PLAYER)
			{
				if (type == pObj->TYPE_MODEL || type == TYPE_ENEMY || type == TYPE_SWITCH)
				{//種類がモデルの場合

					//モデルの位置取得
					D3DXVECTOR3 posModel = pObj->GetPosition();
					D3DXVECTOR3 rotModel = pObj->GetRotation();
					D3DXVECTOR3 minModel = pObj->GetSizeMin();
					D3DXVECTOR3 maxModel = pObj->GetSizeMax();

					if (pPos->x + WIDTH_BULLET >= posModel.x + minModel.x &&
						pPos->x - WIDTH_BULLET <= posModel.x + maxModel.x &&
						pPos->y + HEIGHT_BULLET >= posModel.y + minModel.y &&
						pPos->y - HEIGHT_BULLET <= posModel.y + maxModel.y &&
						pPos->z > posModel.z + minModel.z &&
						pPos->z < posModel.z + maxModel.z)
					{
						if (type == TYPE_ENEMY)
						{//敵の場合

							//敵のヒット処理
							pObj->Hit();
						}
						else if (type == TYPE_SWITCH)
						{//スイッチの場合

							pCamera->SetMode();

							//BGM再生
							pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);
						}

						//爆発の生成
						CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

						return true;
					}
				}
			}
			else if (m_type == TYPE_ENEMY)
			{
				if (type == pObj->TYPE_MODEL || type == pObj->TYPE_PLAYER || type == pObj->TYPE_SWITCH)
				{//種類がモデルの場合

					//モデルの位置取得
					D3DXVECTOR3 posModel = pObj->GetPosition();
					D3DXVECTOR3 rotModel = pObj->GetRotation();
					D3DXVECTOR3 minModel = pObj->GetSizeMin();
					D3DXVECTOR3 maxModel = pObj->GetSizeMax();

					if (pPos->x + WIDTH_BULLET >= posModel.x + minModel.x &&
						pPos->x - WIDTH_BULLET <= posModel.x + maxModel.x &&
						pPos->y + HEIGHT_BULLET >= posModel.y + minModel.y &&
						pPos->y - HEIGHT_BULLET <= posModel.y + maxModel.y &&
						pPos->z > posModel.z + minModel.z &&
						pPos->z < posModel.z + maxModel.z)
					{
						if (type == TYPE_PLAYER)
						{//敵の場合

							//敵のヒット処理
							pObj->Hit();
						}
						else if (type == TYPE_SWITCH)
						{//スイッチの場合

							//BGM再生
							pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

							pCamera->SetMode();
						}

						//爆発の生成
						CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

						return true;
					}

					//if (pPos->y + HEIGHT_BULLET > posModel.y + minModel.y
					//	&& pPos->y - HEIGHT_BULLET < posModel.y + maxModel.y)
					//{
					//	if (pPosOld->x <= posModel.x + minModel.x
					//		&& pPos->x > posModel.x + minModel.x
					//		&& pPos->z > posModel.z + minModel.z
					//		&& pPos->z < posModel.z + maxModel.z)
					//	{//左にめり込んだ場合

					//		if (type == TYPE_PLAYER)
					//		{//敵の場合

					//			//敵のヒット処理
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//スイッチの場合

					//			//BGM再生
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

					//			pCamera->SetMode();
					//		}

					//		//爆発の生成
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		return true;

					//	}

					//	if (pPosOld->x >= posModel.x + maxModel.x
					//		&& pPos->x < posModel.x + maxModel.x
					//		&& pPos->z > posModel.z + minModel.z
					//		&& pPos->z < posModel.z + maxModel.z)
					//	{//右にめり込んだ場合

					//		//爆発の生成
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		if (type == TYPE_PLAYER)
					//		{//プレイヤーの場合

					//			//プレイヤーのヒット処理
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//スイッチの場合

					//			//BGM再生
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

					//			pCamera->SetMode();
					//		}

					//		return true;
					//	}

					//	if (pPosOld->z <= posModel.z + minModel.z
					//		&& pPos->z > posModel.z + minModel.z
					//		&& pPos->x > posModel.x + minModel.x
					//		&& pPos->x < posModel.x + maxModel.x)
					//	{//手前にめり込んだ場合

					//		//爆発の生成
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		if (type == TYPE_PLAYER)
					//		{//プレイヤーの場合

					//			//プレイヤーのヒット処理
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//スイッチの場合

					//			//BGM再生
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

					//			pCamera->SetMode();
					//		}

					//		return true;
					//	}

					//	if (pPosOld->z >= posModel.z + maxModel.z
					//		&& pPos->z < posModel.z + maxModel.z
					//		&& pPos->x > posModel.x + minModel.x
					//		&& pPos->x < posModel.x + maxModel.x)
					//	{//奥にめり込んだ場合

					//		//爆発の生成
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		if (type == TYPE_PLAYER)
					//		{//プレイヤーの場合

					//			//プレイヤーのヒット処理
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//スイッチの場合

					//			//BGM再生
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

					//			pCamera->SetMode();
					//		}

					//		return true;
					//	}

					//	if (pPosOld->y <= posModel.y + minModel.y
					//		&& pPos->y > posModel.y + minModel.y
					//		&& pPos->x > posModel.x + minModel.x
					//		&& pPos->x < posModel.x + maxModel.x
					//		&& pPos->z > posModel.z + minModel.z
					//		&& pPos->z < posModel.z + maxModel.z)
					//	{//底にめり込んだ場合

					//		//爆発の生成
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		if (type == TYPE_PLAYER)
					//		{//プレイヤーの場合

					//			//プレイヤーのヒット処理
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//スイッチの場合

					//			//BGM再生
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);
					//			pCamera->SetMode();
					//		}

					//		return true;
					//	}

					//	if (pPosOld->y >= posModel.y + maxModel.y
					//		&& pPos->y < posModel.y + maxModel.y
					//		&& pPos->x > posModel.x + minModel.x
					//		&& pPos->x < posModel.x + maxModel.x
					//		&& pPos->z > posModel.z + minModel.z
					//		&& pPos->z < posModel.z + maxModel.z)
					//	{//上にめり込んだ場合

					//		//爆発の生成
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		if (type == TYPE_PLAYER)
					//		{//プレイヤーの場合

					//			//プレイヤーのヒット処理
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//スイッチの場合

					//			//BGM再生
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

					//			pCamera->SetMode();
					//		}

					//		return true;
					//	}
					//}
				}
			}
		}
	}

	return false;
}