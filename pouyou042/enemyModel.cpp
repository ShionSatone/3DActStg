//==============================================================
//
//モデル処理[model.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "enemymodel.h"
#include "manager.h"
#include "renderer.h"
#include "score.h"
#include "object.h"
#include "particle.h"
#include "modelHierarchy.h"
#include "motion.h"
#include "debugproc.h"
#include "bullet.h"
#include "playerModel.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "camera.h"
#include "itemModel.h"
#include "switch.h"

//マクロ定義
#define NUM_MODEL			(2)			//敵の種類
#define POS					(10.0f)		//pos初期値
#define MODEL_LEN			(3.0f)		//距離
#define CURVE_RL			(0.5f)		//左右の角度
#define CURVE_UP			(0.0f)		//上の角度
#define CURVE_DOWN			(1.0f)		//下の角度
#define MAX_STR				(128)		//文字の最大数
#define FILE_FROG			"data\\TEXT\\motion_frog.txt"		//カエルのテキスト
#define FILE_AQUATICA		"data\\TEXT\\motion_weapon.txt"		//アクアティカのテキスト
#define FILE_WITCH			"data\\TEXT\\motion_witch.txt"		//魔女のテキスト
#define NUM_LEAF			(5)			//葉をまとめて何枚飛ばすか
#define CURVE_LEAF			(D3DX_PI * 2 * 0.2f)		//葉を打つ角度の分割
#define JUMP_HEIGHT			(20.0f)		//ジャンプの高さ
#define FROG_MOVE_Y			(1.0f)		//移動量Y
#define LIFE_WITCH			(15)		//魔女の寿命
#define SWITCH_WITCH		(60 * 5)	//魔女の攻撃切り替え時間
#define SWITCH_3D			(60 * 13)	//立体切り替え時間
#define SWITCH_END			(60 * 8)	//3D終了時間

//静的メンバ変数宣言
LPD3DXMESH CEnemyModel::m_pMesh = NULL;						//メッシュ（頂点情報）へのポインタ
LPD3DXBUFFER CEnemyModel::m_pBuffMat = NULL;				//マテリアルへのポインタ
DWORD CEnemyModel::m_dwNumMat = NULL;
CEnemyModel *CEnemyModel::m_apEnemyModel[MAX_ENEMY_MODEL] = {};		//敵の情報
int CEnemyModel::m_nNumAll = 0;			//敵の総数
CEnemWitch::ATTACK CEnemWitch::m_attack = ATTACK_GROUND;	//攻撃の種類

//カエルのパーツ
char *CEnemyFrog::m_apFileName[PARTS_MAX] =
{
	"data\\MODEL\\frog\\00_body.x",
	"data\\MODEL\\frog\\01_arm_LU.x",
	"data\\MODEL\\frog\\02_arm_LD.x",
	"data\\MODEL\\frog\\03_hand_L.x",
	"data\\MODEL\\frog\\04_arm_RU.x",
	"data\\MODEL\\frog\\05_arm_RD.x",
	"data\\MODEL\\frog\\06_hand_R.x",
	"data\\MODEL\\frog\\07_leg_LU.x",
	"data\\MODEL\\frog\\08_leg_LD.x",
	"data\\MODEL\\frog\\09_ankle_L.x",
	"data\\MODEL\\frog\\10_shoe_L.x",
	"data\\MODEL\\frog\\11_leg_RU.x",
	"data\\MODEL\\frog\\12_leg_RD.x",
	"data\\MODEL\\frog\\13_ankle_R.x",
	"data\\MODEL\\frog\\14_shoe_R.x",
};

//ロリッパアクアティカのパーツ
char *CEnemyAquatica::m_apFileName[PARTS_MAX] =
{
	"data\\MODEL\\aqua.x",
	/*"data\\MODEL\\player\\01_head.x",
	"data\\MODEL\\player\\02_hair.x",
	"data\\MODEL\\player\\03_LU_arm.x",
	"data\\MODEL\\player\\04_LD_arm.x",
	"data\\MODEL\\player\\05_L_hand.x",
	"data\\MODEL\\player\\06_RU_arm.x",
	"data\\MODEL\\player\\07_RD_arm.x",
	"data\\MODEL\\player\\08_R_hand.x",
	"data\\MODEL\\player\\09_waist.x",
	"data\\MODEL\\player\\10_skirt.x",
	"data\\MODEL\\player\\11_LU_leg.x",
	"data\\MODEL\\player\\12_LD_leg.x",
	"data\\MODEL\\player\\13_L_shoe.x",
	"data\\MODEL\\player\\14_RU_leg.x",
	"data\\MODEL\\player\\15_RD_leg.x",
	"data\\MODEL\\player\\16_R_shoe.x",
	"data\\MODEL\\player\\17_fish.x",*/
};

//魔女のパーツ
char *CEnemWitch::m_apFileName[PARTS_MAX] =
{
	"data\\MODEL\\witch\\00_body.x",
	"data\\MODEL\\witch\\01_head.x",
	"data\\MODEL\\witch\\02_LU_arm.x",
	"data\\MODEL\\witch\\03_LD_arm.x",
	"data\\MODEL\\witch\\04_L_hand.x",
	"data\\MODEL\\witch\\05_RU_arm.x",
	"data\\MODEL\\witch\\06_RD_arm.x",
	"data\\MODEL\\witch\\07_R_hand.x",
	"data\\MODEL\\witch\\08_waist.x",
	"data\\MODEL\\witch\\09_skirt.x",
	"data\\MODEL\\witch\\10_LU_leg.x",
	"data\\MODEL\\witch\\11_LD_leg.x",
	"data\\MODEL\\witch\\12_L_shoe.x",
	"data\\MODEL\\witch\\13_RU_leg.x",
	"data\\MODEL\\witch\\14_RD_leg.x",
	"data\\MODEL\\witch\\15_R_shoe.x",
};

//==============================================================
//コンストラクタ
//==============================================================
CEnemyModel::CEnemyModel()
{
	m_pMotion = NULL;		//モーションの情報

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置(前回)
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//敵の最大値
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//敵の最小値
	m_nLife = 3;			//寿命
	m_nCntDamage = 0;		//ダメージカウンター
	m_nCntAttack = 0;		//攻撃カウンター
	m_state = CObject::STATE_NONE;		//通常状態

	m_nID = m_nNumAll;			//敵の番号更新
	m_nNumAll++;		//総数加算

	m_bAction = false;			//攻撃したか
	m_bJump = false;			//ジャンプしたか
	m_bLand = true;			//着地したか
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CEnemyModel::CEnemyModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	m_pMotion = NULL;		//モーションの情報

	m_pos = pos;		//位置
	m_rot = rot;		//向き
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//敵の最大値
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//敵の最小値
	m_nLife = nLife;			//寿命
	m_nCntDamage = 0;		//ダメージカウンター
	m_nCntAttack = 0;		//攻撃カウンター
	m_state = CObject::STATE_NONE;		//通常状態

	m_nID = m_nNumAll;			//敵の番号更新
	m_nNumAll++;		//総数加算

	m_bAction = false;			//攻撃したか
	m_bJump = false;			//ジャンプしたか
	m_bLand = true;			//着地したか
}

//==============================================================
//デストラクタ
//==============================================================
CEnemyModel::~CEnemyModel()
{
	m_nNumAll--;		//総数減算
}

//==============================================================
//敵の生成処理
//==============================================================
CEnemyModel *CEnemyModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE type, int nLife)
{
	if (m_nNumAll < MAX_ENEMY_MODEL)
	{//モデルの数が最大未満だったら

		int nIdx = m_nNumAll;		//総数代入

		if (m_apEnemyModel[nIdx] == NULL)
		{//メモリが使用されてなかったら

			//敵の生成
			switch (type)
			{
			case ENEMYTYPE_FROG:		//カエル

				m_apEnemyModel[nIdx] = new CEnemyFrog(pos, rot, nLife);

				break;

			case ENEMYTYPE_AQUATICA:	//ロリッパアクアティカ

				m_apEnemyModel[nIdx] = new CEnemyAquatica(pos, rot, nLife);

				break;

			case ENEMYTYPE_WITCH:		//魔女

				m_apEnemyModel[nIdx] = new CEnemWitch(pos, rot, nLife);

				break;
			}
		}

		//初期化処理
		m_apEnemyModel[nIdx]->Init(pos, rot);

		//種類の設定
		m_apEnemyModel[nIdx]->SetType(CObject::TYPE_ENEMY);

		return m_apEnemyModel[nIdx];
	}

	return NULL;
}
#if 0

//==============================================================
//敵の初期化処理
//==============================================================
HRESULT CEnemyModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	

	return S_OK;
}

#endif

//==============================================================
//敵の終了処理
//==============================================================
void CEnemyModel::Uninit(void)
{
	int nID = m_nID;		//番号代入

	if (m_apEnemyModel[nID] != NULL)
	{//メモリが使用されていたら

		m_apEnemyModel[nID] = NULL;
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//敵の更新処理
//==============================================================
void CEnemyModel::Update(void)
{
	/*CDebugProc *pDebugProc = CManager::GetDebugProc();

	pDebugProc->Print("\n敵の数：%d\n", m_nNumAll);*/

	
}

//==============================================================
//敵の描画処理
//==============================================================
void CEnemyModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//****************************************************************************************
//カエル
//
//==============================================================
//コンストラクタ[カエル]
//==============================================================
CEnemyFrog::CEnemyFrog()
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//敵(パーツ)へのポインタ
	}
}

//==============================================================
//コンストラクタ[カエル](オーバーロード)
//==============================================================
CEnemyFrog::CEnemyFrog(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//敵(パーツ)へのポインタ
	}

	m_nLife = nLife;		//寿命代入
}

//==============================================================
//デストラクタ[カエル]
//==============================================================
CEnemyFrog::~CEnemyFrog()
{

}

//==============================================================
//カエルの初期化処理
//==============================================================
HRESULT CEnemyFrog::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//位置
	m_rot = rot;		//向き

	//敵の生成（全パーツ分）
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//モーションの初期化・生成
	m_pMotion = m_pMotion->Create(m_pMotion->MOTIONTEXT_FROG);
	m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	m_pMotion->Init();

	//敵のファイル読み込み
	CEnemyFrog::LoadFile();

	//最大値・最小値代入
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		//最大値Y
		if ((nCntEnemy <= PARTS_BODY/* && nCntEnemy <= PARTS_HEAD) ||
			(nCntEnemy <= PARTS_LEG_R && nCntEnemy <= PARTS_FOOT_R*/))
		{
			m_max.y += m_apModel[nCntEnemy]->GetSizeMax().y;		//最大値加算
		}

		//最大値入れ替え
		if (m_max.x < m_apModel[nCntEnemy]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntEnemy]->GetSizeMax().x;		//最小値X
		}
		if (m_max.z < m_apModel[nCntEnemy]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntEnemy]->GetSizeMax().z;		//最小値Z

		}

		//最小値入れ替え
		if (m_min.x > m_apModel[nCntEnemy]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntEnemy]->GetSizeMin().x;		//最小値X
		}
		if (m_min.y > m_apModel[nCntEnemy]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntEnemy]->GetSizeMin().y;		//最小値Y
		}
		if (m_min.z > m_apModel[nCntEnemy]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntEnemy]->GetSizeMin().z;		//最小値Z
		}
	}

	m_max.y += 25.0f;

	return S_OK;
}

//==============================================================
//カエルの終了処理
//==============================================================
void CEnemyFrog::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		if (m_apModel[nCntEnemy] != NULL)
		{//使用されてるとき

			//終了処理
			m_apModel[nCntEnemy]->Uninit();
			m_apModel[nCntEnemy] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//使用されてるとき

		//モーションの破棄
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//敵の終了処理
	CEnemyModel::Uninit();
}

//==============================================================
//カエルの更新処理
//==============================================================
void CEnemyFrog::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	m_posOld = m_pos;		//現在の位置

	//プレイヤーの向き取得
	//m_rot.x = -pPlayerModel->GetRotation().x;

	//移動量加算
	m_move.y -= FROG_MOVE_Y;

	//位置更新
	m_pos += m_move;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//当たり判定
	if (CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max) == true)
	{//着地したら

		//m_bJump = false;		//ジャンプしてない状態にする
	}

	switch (m_state)
	{
	case STATE_NONE:		//通常状態

		m_bJump = false;

		if (pPlayer->GetPosition().x > m_pos.x - (SCREEN_WIDTH * 0.5f) &&
			pPlayer->GetPosition().x < m_pos.x + (SCREEN_WIDTH * 0.5f))
		{//プレイヤーが敵の近くに来たら

			if (m_nCntAttack >= 60 * 3)
			{//一定時間経ったら

				m_state = STATE_ATTACK;		//攻撃状態にする
				m_nCntAttack = 0;			//攻撃カウンター初期化
			}
			else
			{//時間が経ってなかったら

				m_nCntAttack++;		//攻撃カウンター加算
			}
		}
		break;

	case STATE_ATTACK:		//攻撃状態

		//ジャンプする
		m_move.x = -10.0f;
		m_move.y = JUMP_HEIGHT;

		if (m_bJump == false)
		{//ジャンプしてなかったら

			m_bJump = true;		//ジャンプ状態にする

			//ジャンプモーション
			m_pMotion->Set(m_pMotion->MOTIONTYPE_JUMP);

			//パーティクル生成
			CParticle::Create(m_pos, D3DXCOLOR(0.7f, 0.5f, 0.4f, 1.0f), PARTICLETYPE_JUMP, 30, 20);
		}

		//攻撃する(舌で攻撃)
		//弾の生成(仮)
		//CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_ENEMY);

		m_state = STATE_NONE;		//通常状態にする

		break;

	case STATE_DAMAGE:		//ダメージ状態

		m_nCntDamage--;		//ダメージ時間減算

		if (m_nCntDamage <= 0)
		{//ダメージ時間が終わったら

			m_state = CObject::STATE_NONE;

			//状態設定
			for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
			{
				m_apModel[nCntEnemy]->SetState(m_state);		//通常状態にする

			}
		}

		break;
	}

	if ((m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_pMotion->IsFinish() == true) && m_bJump == false)
	{//モーションが終了したら

		//待機状態に戻す
		m_pMotion->Set(m_pMotion->MOTIONTYPE_NEUTRAL);
	}

	//モーションの更新処理
	m_pMotion->Update();

	//敵の更新処理
	CEnemyModel::Update();
}

//==============================================================
//カエルの描画処理
//==============================================================
void CEnemyFrog::Draw(void)
{
	//敵の描画処理
	CEnemyModel::Draw();

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//敵の描画
		m_apModel[nCntPlayer]->Draw();
	}
}

//==============================================================
//カエルのヒット処理
//==============================================================
void CEnemyFrog::Hit(void)
{
	CSound *pSound = CManager::GetSound();

	//BGM再生
	pSound->Play(pSound->SOUND_LABEL_SE_DAMAGE000);

	m_nLife--;

	if (m_nLife > 0)
	{//まだ寿命が残ってたら

		m_state = CObject::STATE_DAMAGE;

		for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
		{
			m_apModel[nCntEnemy]->SetState(m_state);		//ダメージ状態にする
		}

		m_nCntDamage = 5;					//ダメージ状態を保つ時間設定
	}
	else if (m_nLife <= 0)
	{//寿命がなかったら

		//スコア加算
		CScore::Add(10520);

		//爆発の生成
		CParticle::Create(m_pos, D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f), PARTICLETYPE_EXPLOSION, 0, 13);

		//終了処理
		CEnemyModel::Uninit();
	}
}

//==============================================================
//カエルのモデルファイル読み込み処理
//==============================================================
void CEnemyFrog::LoadFile(void)
{
	FILE *pFile;				//ファイルポインタ
	char aString[MAX_STR];		//文字読み込み
	int nIndex = 0, nParent = 0;	//パーツNo.,親番号
	D3DXVECTOR3 pos, rot;

	//ファイル開く
	pFile = fopen(FILE_FROG, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		while (strcmp(&aString[0], "CHARACTERSET") != 0)
		{//[CHARACTERSET]するまでの間

			fscanf(pFile, "%s", &aString[0]);		//文字読み込み
		}

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{//[CHARACTERSET]が来たら

			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{//[END_CHARACTERSET]がくるまでの間

				fscanf(pFile, "%s", &aString[0]);		//文字読み込み

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{//[PARTSSET]が来たら

					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{//[END_PARTSSET]がくるまでの間

						fscanf(pFile, "%s", &aString[0]);		//文字読み込み

						if (strcmp(&aString[0], "INDEX") == 0)
						{//パーツNo.

							fscanf(pFile, "%s", &aString[0]);		//文字読み込み
							fscanf(pFile, "%d", &nIndex);			//パーツNo.読み込み

						}
						else if (strcmp(&aString[0], "PARENT") == 0)
						{//親情報

							fscanf(pFile, "%s", &aString[0]);		//文字読み込み
							fscanf(pFile, "%d", &nParent);			//親番号読み込み

							if (nParent == -1)
							{//親がいなかったら

								m_apModel[nIndex]->SetParent(NULL);		//NULLを入れる
							}
							else
							{//親がいたら

								m_apModel[nIndex]->SetParent(m_apModel[nParent]);		//親番号入れる
							}
						}
						else if (strcmp(&aString[0], "POS") == 0)
						{//位置情報

							fscanf(pFile, "%s", &aString[0]);	//文字読み込み

							fscanf(pFile, "%f", &pos.x);		//位置読み込み
							fscanf(pFile, "%f", &pos.y);		//位置読み込み
							fscanf(pFile, "%f", &pos.z);		//位置読み込み

							m_apModel[nIndex]->SetPosition(pos);		//位置設定
							m_apModel[nIndex]->SetDefaultPosition(pos);	//初期位置設定

						}
						else if (strcmp(&aString[0], "ROT") == 0)
						{//向き情報

							fscanf(pFile, "%s", &aString[0]);	//文字読み込み

							fscanf(pFile, "%f", &rot.x);		//向き読み込み
							fscanf(pFile, "%f", &rot.y);		//向き読み込み
							fscanf(pFile, "%f", &rot.z);		//向き読み込み

							m_apModel[nIndex]->SetRotation(rot);		//向き設定
							m_apModel[nIndex]->SetDefaultRotation(rot);	//初期向き設定
						}
					}
				}
			}
		}

		//ファイル閉じる
		fclose(pFile);
	}
}

//****************************************************************************************
//ロリッパアクアティカ
//
//==============================================================
//コンストラクタ[ロリッパアクアティカ]
//==============================================================
CEnemyAquatica::CEnemyAquatica()
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//敵(パーツ)へのポインタ
	}
}

//==============================================================
//コンストラクタ[ロリッパアクアティカ](オーバーロード)
//==============================================================
CEnemyAquatica::CEnemyAquatica(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//敵(パーツ)へのポインタ
	}

	m_nLife = nLife;		//寿命代入
}

//==============================================================
//デストラクタ[ロリッパアクアティカ]
//==============================================================
CEnemyAquatica::~CEnemyAquatica()
{

}

//==============================================================
//ロリッパアクアティカの初期化処理
//==============================================================
HRESULT CEnemyAquatica::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//位置
	m_rot = rot;		//向き

	//敵の生成（全パーツ分）
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	////モーションの初期化・生成
	//m_pMotion = m_pMotion->Create(m_pMotion->MOTIONTEXT_PLAYER);
	//m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	//m_pMotion->Init();

	////敵のファイル読み込み
	//CEnemyAquatica::LoadFile();

	//最大値・最小値代入
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		//最大値Y
		if ((nCntEnemy <= PARTS_BODY/* && nCntEnemy <= PARTS_HEAD) ||
			(nCntEnemy <= PARTS_LEG_R && nCntEnemy <= PARTS_FOOT_R*/))
		{
			m_max.y += m_apModel[nCntEnemy]->GetSizeMax().y;		//最大値加算
		}

		//最大値入れ替え
		if (m_max.x < m_apModel[nCntEnemy]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntEnemy]->GetSizeMax().x;		//最小値X
		}
		if (m_max.z < m_apModel[nCntEnemy]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntEnemy]->GetSizeMax().z;		//最小値Z

		}

		//最小値入れ替え
		if (m_min.x > m_apModel[nCntEnemy]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntEnemy]->GetSizeMin().x;		//最小値X
		}
		if (m_min.y > m_apModel[nCntEnemy]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntEnemy]->GetSizeMin().y;		//最小値Y
		}
		if (m_min.z > m_apModel[nCntEnemy]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntEnemy]->GetSizeMin().z;		//最小値Z
		}
	}

	m_max.y += 25.0f;

	return S_OK;
}

//==============================================================
//ロリッパアクアティカの終了処理
//==============================================================
void CEnemyAquatica::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		if (m_apModel[nCntEnemy] != NULL)
		{//使用されてるとき

		 //終了処理
			m_apModel[nCntEnemy]->Uninit();
			m_apModel[nCntEnemy] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//使用されてるとき

		//モーションの破棄
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//敵の終了処理
	CEnemyModel::Uninit();
}

//==============================================================
//ロリッパアクアティカの更新処理
//==============================================================
void CEnemyAquatica::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	m_posOld = m_pos;		//現在の位置

	//当たり判定
	CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max);

	switch (m_state)
	{
	case STATE_NONE:		//通常状態

		if (pPlayer->GetPosition().x >= m_pos.x - (SCREEN_WIDTH * 0.5f) &&
			pPlayer->GetPosition().x <= m_pos.x + (SCREEN_WIDTH * 0.5f))
		{//プレイヤーが敵の近くに来たら

			if (m_nCntAttack >= 60 * 1)
			{//一定時間経ったら

				m_state = STATE_ATTACK;		//攻撃状態にする
				m_nCntAttack = 0;			//攻撃カウンター初期化
			}
			else
			{//時間が経ってなかったら

				m_nCntAttack++;		//攻撃カウンター加算
			}
		}

		break;

	case STATE_ATTACK:		//攻撃状態

		//攻撃する(葉を飛ばす)
		for (int nCntBullet = 0; nCntBullet < NUM_LEAF; nCntBullet++)
		{
			CBullet::Create(D3DXVECTOR3(m_pos.x, (m_pos.y + m_max.y) * 0.5f, m_pos.z - 10.0f),
				D3DXVECTOR3(sinf((float)(nCntBullet * CURVE_LEAF) + CURVE_LEAF) * 1.0f,
					cosf((float)(nCntBullet * CURVE_LEAF) + CURVE_LEAF) * 1.0f,
					0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_ENEMY);

		}

		m_state = STATE_NONE;		//通常状態にする

		break;

	case STATE_DAMAGE:		//ダメージ状態

		m_nCntDamage--;		//ダメージ時間減算

		if (m_nCntDamage <= 0)
		{//ダメージ時間が終わったら

			m_state = CObject::STATE_NONE;

			//状態設定
			for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
			{
				m_apModel[nCntEnemy]->SetState(m_state);		//通常状態にする

			}
		}

		break;
	}

	pDebugProc->Print("敵の位置(%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);

	//敵の更新処理
	CEnemyModel::Update();
}

//==============================================================
//ロリッパアクアティカの描画処理
//==============================================================
void CEnemyAquatica::Draw(void)
{
	//敵の描画処理
	CEnemyModel::Draw();

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//敵の描画
		m_apModel[nCntPlayer]->Draw();
	}
}

//==============================================================
//ロリッパアクアティカのヒット処理
//==============================================================
void CEnemyAquatica::Hit(void)
{
	CSound *pSound = CManager::GetSound();

	//BGM再生
	pSound->Play(pSound->SOUND_LABEL_SE_DAMAGE000);
	
	m_nLife--;

	if (m_nLife > 0)
	{//まだ寿命が残ってたら

		m_state = CObject::STATE_DAMAGE;

		for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
		{
			m_apModel[nCntEnemy]->SetState(m_state);		//ダメージ状態にする
		}

		m_nCntDamage = 5;					//ダメージ状態を保つ時間設定
	}
	else if (m_nLife <= 0)
	{//寿命がなかったら

		//スコア加算
		CScore::Add(15000);

		//爆発の生成
		CParticle::Create(m_pos, D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f), PARTICLETYPE_EXPLOSION, 0, 13);

		//終了処理
		CEnemyModel::Uninit();
	}
}

//==============================================================
//ロリッパアクアティカのモデルファイル読み込み処理
//==============================================================
void CEnemyAquatica::LoadFile(void)
{
	FILE *pFile;				//ファイルポインタ
	char aString[MAX_STR];		//文字読み込み
	int nIndex = 0, nParent = 0;	//パーツNo.,親番号
	D3DXVECTOR3 pos, rot;

	//ファイル開く
	pFile = fopen(FILE_AQUATICA, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		while (strcmp(&aString[0], "CHARACTERSET") != 0)
		{//[CHARACTERSET]するまでの間

			fscanf(pFile, "%s", &aString[0]);		//文字読み込み
		}

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{//[CHARACTERSET]が来たら

			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{//[END_CHARACTERSET]がくるまでの間

				fscanf(pFile, "%s", &aString[0]);		//文字読み込み

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{//[PARTSSET]が来たら

					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{//[END_PARTSSET]がくるまでの間

						fscanf(pFile, "%s", &aString[0]);		//文字読み込み

						if (strcmp(&aString[0], "INDEX") == 0)
						{//パーツNo.

							fscanf(pFile, "%s", &aString[0]);		//文字読み込み
							fscanf(pFile, "%d", &nIndex);			//パーツNo.読み込み

						}
						else if (strcmp(&aString[0], "PARENT") == 0)
						{//親情報

							fscanf(pFile, "%s", &aString[0]);		//文字読み込み
							fscanf(pFile, "%d", &nParent);			//親番号読み込み

							if (nParent == -1)
							{//親がいなかったら

								m_apModel[nIndex]->SetParent(NULL);		//NULLを入れる
							}
							else
							{//親がいたら

								m_apModel[nIndex]->SetParent(m_apModel[nParent]);		//親番号入れる
							}
						}
						else if (strcmp(&aString[0], "POS") == 0)
						{//位置情報

							fscanf(pFile, "%s", &aString[0]);	//文字読み込み

							fscanf(pFile, "%f", &pos.x);		//位置読み込み
							fscanf(pFile, "%f", &pos.y);		//位置読み込み
							fscanf(pFile, "%f", &pos.z);		//位置読み込み

							m_apModel[nIndex]->SetPosition(pos);		//位置設定
							m_apModel[nIndex]->SetDefaultPosition(pos);	//初期位置設定

						}
						else if (strcmp(&aString[0], "ROT") == 0)
						{//向き情報

							fscanf(pFile, "%s", &aString[0]);	//文字読み込み

							fscanf(pFile, "%f", &rot.x);		//向き読み込み
							fscanf(pFile, "%f", &rot.y);		//向き読み込み
							fscanf(pFile, "%f", &rot.z);		//向き読み込み

							m_apModel[nIndex]->SetRotation(rot);		//向き設定
							m_apModel[nIndex]->SetDefaultRotation(rot);	//初期向き設定
						}
					}
				}
			}
		}

		//ファイル閉じる
		fclose(pFile);
	}
}

//****************************************************************************************
//魔女
//
//==============================================================
//コンストラクタ[魔女]
//==============================================================
CEnemWitch::CEnemWitch()
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//敵(パーツ)へのポインタ
	}

	m_nCntEnemy = 0;	//敵出現までのカウント
	m_fAngle = 0.0f;		//角度
	m_bItem = false;		//アイテム出現していいのか
}

//==============================================================
//コンストラクタ[魔女](オーバーロード)
//==============================================================
CEnemWitch::CEnemWitch(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//敵(パーツ)へのポインタ
	}

	m_nLife = nLife;		//寿命代入
	m_form = FORM_FIRST;	//第１形態
	m_attack = ATTACK_GROUND;		//攻撃の種類
	m_nCntSwitch = 0;	//切り替えカウント
	m_bBgm = false;		//BGMが鳴ったか
	m_rot = rot;	//向き
	m_nCntEnemy = 0;	//敵出現までのカウント
	m_fAngle = 0.0f;		//角度
	m_nCntItem = 0;		//アイテム出現カウント
	m_bItem = false;		//アイテム出現していいのか
}

//==============================================================
//デストラクタ[魔女]
//==============================================================
CEnemWitch::~CEnemWitch()
{

}

//==============================================================
//魔女の初期化処理
//==============================================================
HRESULT CEnemWitch::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//位置
	m_rot = rot;		//向き

	//敵の生成（全パーツ分）
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//モーションの初期化・生成
	m_pMotion = m_pMotion->Create(CMotion::MOTIONTEXT_WITCH);
	m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	m_pMotion->Init();

	//敵のファイル読み込み
	CEnemWitch::LoadFile();

	//最大値・最小値代入
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		//最大値Y
		if ((nCntEnemy <= PARTS_BODY && nCntEnemy <= PARTS_HEAD) ||
			(nCntEnemy <= PARTS_LEG_R && nCntEnemy <= PARTS_FOOT_R))
		{
			m_max.y += m_apModel[nCntEnemy]->GetSizeMax().y;		//最大値加算
		}

		//最大値入れ替え
		if (m_max.x < m_apModel[nCntEnemy]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntEnemy]->GetSizeMax().x;		//最小値X
		}
		if (m_max.z < m_apModel[nCntEnemy]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntEnemy]->GetSizeMax().z;		//最小値Z

		}

		//最小値入れ替え
		if (m_min.x > m_apModel[nCntEnemy]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntEnemy]->GetSizeMin().x;		//最小値X
		}
		if (m_min.y > m_apModel[nCntEnemy]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntEnemy]->GetSizeMin().y;		//最小値Y
		}
		if (m_min.z > m_apModel[nCntEnemy]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntEnemy]->GetSizeMin().z;		//最小値Z
		}
	}

	m_max.y += 10.0f;
	m_min.y = 0.0f;

	return S_OK;
}

//==============================================================
//魔女の終了処理
//==============================================================
void CEnemWitch::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		if (m_apModel[nCntEnemy] != NULL)
		{//使用されてるとき

		 //終了処理
			m_apModel[nCntEnemy]->Uninit();
			m_apModel[nCntEnemy] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//使用されてるとき

		//モーションの破棄
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//敵の終了処理
	CEnemyModel::Uninit();
}

//==============================================================
//魔女の更新処理
//==============================================================
void CEnemWitch::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();
	CPlayerModel *pPlayer = CGame::GetPlayerModel();
	CCamera *pCamera = CManager::GetCamera();
	CGame *pGame = CScene::GetGame();

	m_posOld = m_pos;		//現在の位置

	m_nCntSwitch++;
	m_nCntEnemy++;

	//当たり判定
	CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max);

	if ((pGame->GetGameMode() == pGame->GAMEMODE_BOSS && pPlayer->GetPosition().x >= 10452.0f) || m_bBgm == true)
	{//ボス戦の時

		if (m_bBgm == false)
		{//BGMがなったとき

			CSound *pSound = CManager::GetSound();

			//BGMの停止
			pSound->Stop(pSound->SOUND_LABEL_BGM002);

			//BGM再生
			pSound->Play(pSound->SOUND_LABEL_BGMBOSS);

			m_bBgm = true;
		}

		switch (m_state)
		{
		case STATE_NONE:		//通常状態

			if (pCamera->GetMode() == false)
			{
				m_attack = ATTACK_3D;
			}

			if (m_bAction == true && m_pMotion->IsFinish() == true)
			{//攻撃し終わったら

				//待機状態に戻す
				m_pMotion->Set(m_pMotion->MOTIONTYPE_NEUTRAL);

				m_bAction = false;		//攻撃してない状態にする
			}

			if (m_nCntAttack >= 60 * 2)
			{//一定時間経ったら

				m_state = STATE_ATTACK;		//攻撃状態にする
				m_nCntAttack = 0;			//攻撃カウンター初期化
			}
			else
			{//時間が経ってなかったら

				m_nCntAttack++;		//攻撃カウンター加算
			}

			break;

		case STATE_ATTACK:		//攻撃状態

			m_state = STATE_NONE;		//通常状態にする

			if (m_form == FORM_FIRST)
			{//第１形態のとき

				if (m_attack == ATTACK_GROUND)
				{
					//弾の生成
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(sinf(m_rot.y) * -2.0f, 0.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
				}
				else if (m_attack == ATTACK_FLY)
				{
					//弾の生成
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(sinf(m_rot.y) * -2.0f, -2.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
				}
				else if (m_attack == ATTACK_3D)
				{
					int nBulletRand = rand() % 4;

					switch (nBulletRand)
					{
					case 0:

						for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
						{
							//弾の生成
							CBullet::Create(D3DXVECTOR3(10200.0f + (nCntBullet * 100.0f), -4800.0f, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
						}

						break;

					case 1:

						for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
						{
							//弾の生成
							CBullet::Create(D3DXVECTOR3(10400.0f + (nCntBullet * 100.0f), -4800.0f, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
						}

						break;

					case 2:

						for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
						{
							//弾の生成
							CBullet::Create(D3DXVECTOR3(10200.0f, -4900.0f + (nCntBullet * 100.0f), 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
						}

						break;

					case 3:

						for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
						{
							//弾の生成
							CBullet::Create(D3DXVECTOR3(10650.0f, -4900.0f + (nCntBullet * 100.0f), 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
						}

						break;
					}

					
				}

				if (m_bAction == false)
				{//攻撃してないとき

					//攻撃する
					m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
					m_bAction = true;
				}
			}
			else
			{
				//弾の生成
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, -10.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
			}

			break;

		case STATE_DAMAGE:		//ダメージ状態

			m_nCntDamage--;		//ダメージ時間減算

			if (m_nCntDamage <= 0)
			{//ダメージ時間が終わったら

				m_state = CObject::STATE_NONE;

				//状態設定
				for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
				{
					m_apModel[nCntEnemy]->SetState(m_state);		//通常状態にする

				}
			}

			break;

		case STATE_DEATH:		//死亡状態

			if (m_form == FORM_FIRST)
			{//第１形態のとき

				m_pos = D3DXVECTOR3(0.0f, -4990.0f, 1000.0f);
				m_nLife = LIFE_WITCH;
				m_form = FORM_SECOND;		//第２形態
				pPlayer->SetPosition(D3DXVECTOR3(0.0f, -5000.0f, 0.0f));
				m_state = STATE_NONE;
			}

			break;
		}

		switch (m_attack)
		{
		case ATTACK_GROUND:		//地面

			if ((m_nCntSwitch % SWITCH_WITCH) == 0)
			{
				m_attack = ATTACK_FLY;		//空中攻撃
				m_pos.y = -4800.0f;
				m_fAngle = 0.0f;
			}

			if (m_pos.x > pPlayer->GetPosition().x)
			{
				m_rot.y = 0.5f * D3DX_PI;		//左向かせる
			}
			else if (m_pos.x < pPlayer->GetPosition().x)
			{
				m_rot.y = 0.5f * -D3DX_PI;		//右向かせる
			}

			if ((m_nCntSwitch % SWITCH_3D) == 0)
			{//3D切り替え処理

				pCamera->SetMode(true);
				m_pos = D3DXVECTOR3(10500.0f, -4800.0f, 80.0f);
				m_rot.y = 0.0f;
				m_attack = ATTACK_3D;
			}


			break;

		case ATTACK_FLY:		//空中

			m_fAngle += 0.05f;
			m_pos.y = m_pos.y + sinf(m_fAngle) * 0.5f;

			if ((m_nCntSwitch % SWITCH_WITCH) == 0)
			{
				m_attack = ATTACK_GROUND;	//地面攻撃
				m_pos.y = -4990.0f;

			}

			if (m_pos.x > pPlayer->GetPosition().x)
			{
				m_rot.y = 0.5f * D3DX_PI;		//左向かせる
			}
			else if (m_pos.x < pPlayer->GetPosition().x)
			{
				m_rot.y = 0.5f * -D3DX_PI;		//右向かせる
			}

			if ((m_nCntSwitch % SWITCH_3D) == 0)
			{//3D切り替え処理

				pCamera->SetMode(false);
				m_pos = D3DXVECTOR3(10500.0f, -4800.0f, 80.0f);
				m_rot.y = 0.0f;
				m_attack = ATTACK_3D;
			}

			break;
			
		case ATTACK_3D:			//3D

			if (pCamera->GetMode() == true)
			{
				m_nCntItem = 0;
				m_pos.y = -4990.0f;
				m_pos.z = 0.0f;
				m_attack = ATTACK_GROUND;
			}

			if ((m_nCntItem == 60 * 9) && m_bItem == false)
			{
				CSwitch::Create(D3DXVECTOR3(10600.0f, -4800.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				CItemModel::Create(D3DXVECTOR3(10300.0f, -4900.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_WATER);

				m_bItem = true;
			}

			m_nCntItem++;

			break;
		}

		//位置変更処理
		if ((m_nCntEnemy % 480) == 0)
		{
			float randPos = float(rand() % 200);

			if (m_pos.x > 10500.0f)
			{
				m_pos.x -= randPos;
			}
			else if (m_pos.x <= 10500.0f)
			{
				m_pos.x += randPos;
			}
		}

		/*if (m_bItem == true)
		{
			if (m_nCntItem >= 60 * 20)
			{
				CItemModel::Create(D3DXVECTOR3(10300.0f, -4900.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_WATER);

				m_nCntItem = 0;
			}

			m_nCntItem++;
		}*/

		m_pos += m_move;

		pDebugProc->Print("敵の位置(%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);
		pDebugProc->Print("敵の向き( %f )\n", m_rot.y);

	}

	//モーションの更新処理
	m_pMotion->Update();

	//敵の更新処理
	CEnemyModel::Update();
}

//==============================================================
//魔女の描画処理
//==============================================================
void CEnemWitch::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//デバイスの取得

	//敵の描画処理
	CEnemyModel::Draw();

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//敵の描画
		m_apModel[nCntPlayer]->Draw();
	}

	//通常
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//==============================================================
//魔女のヒット処理
//==============================================================
void CEnemWitch::Hit(void)
{
	CSound *pSound = CManager::GetSound();

	m_nLife--;

	//BGM再生
	pSound->Play(pSound->SOUND_LABEL_SE_DAMAGE000);

	if (m_nLife > 0)
	{//まだ寿命が残ってたら

		m_state = CObject::STATE_DAMAGE;

		for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
		{
			m_apModel[nCntEnemy]->SetState(m_state);		//ダメージ状態にする
		}

		m_nCntDamage = 5;					//ダメージ状態を保つ時間設定
	}
	else if (m_nLife <= 0)
	{//寿命がなかったら

		CScore *pScore = CGame::GetScore();		//スコアの情報

		//スコア加算
		CScore::Add(1055000);

		//爆発の生成
		CParticle::Create(m_pos, D3DXCOLOR(0.7f, 0.0f, 0.7f, 1.0f), PARTICLETYPE_EXPLOSION, 0, 13);

		//スコア設定
		CManager::SetNumScore(pScore->Get());

		//if (m_form == FORM_SECOND)
		{//第2形態のとき

			CFade *pFade = CManager::GetFade();		//フェードの情報取得

			//リザルトの判定
			CManager::SetResult(true);

			//終了処理
			CEnemyModel::Uninit();

			//リザルト画面
			pFade->SetFade(CScene::MODE_RESULT);
		}
	}
}

//==============================================================
//魔女のモデルファイル読み込み処理
//==============================================================
void CEnemWitch::LoadFile(void)
{
	FILE *pFile;				//ファイルポインタ
	char aString[MAX_STR];		//文字読み込み
	int nIndex = 0, nParent = 0;	//パーツNo.,親番号
	D3DXVECTOR3 pos, rot;

	//ファイル開く
	pFile = fopen(FILE_WITCH, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		while (strcmp(&aString[0], "CHARACTERSET") != 0)
		{//[CHARACTERSET]するまでの間

			fscanf(pFile, "%s", &aString[0]);		//文字読み込み
		}

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{//[CHARACTERSET]が来たら

			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{//[END_CHARACTERSET]がくるまでの間

				fscanf(pFile, "%s", &aString[0]);		//文字読み込み

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{//[PARTSSET]が来たら

					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{//[END_PARTSSET]がくるまでの間

						fscanf(pFile, "%s", &aString[0]);		//文字読み込み

						if (strcmp(&aString[0], "INDEX") == 0)
						{//パーツNo.

							fscanf(pFile, "%s", &aString[0]);		//文字読み込み
							fscanf(pFile, "%d", &nIndex);			//パーツNo.読み込み

						}
						else if (strcmp(&aString[0], "PARENT") == 0)
						{//親情報

							fscanf(pFile, "%s", &aString[0]);		//文字読み込み
							fscanf(pFile, "%d", &nParent);			//親番号読み込み

							if (nParent == -1)
							{//親がいなかったら

								m_apModel[nIndex]->SetParent(NULL);		//NULLを入れる
							}
							else
							{//親がいたら

								m_apModel[nIndex]->SetParent(m_apModel[nParent]);		//親番号入れる
							}
						}
						else if (strcmp(&aString[0], "POS") == 0)
						{//位置情報

							fscanf(pFile, "%s", &aString[0]);	//文字読み込み

							fscanf(pFile, "%f", &pos.x);		//位置読み込み
							fscanf(pFile, "%f", &pos.y);		//位置読み込み
							fscanf(pFile, "%f", &pos.z);		//位置読み込み

							m_apModel[nIndex]->SetPosition(pos);		//位置設定
							m_apModel[nIndex]->SetDefaultPosition(pos);	//初期位置設定

						}
						else if (strcmp(&aString[0], "ROT") == 0)
						{//向き情報

							fscanf(pFile, "%s", &aString[0]);	//文字読み込み

							fscanf(pFile, "%f", &rot.x);		//向き読み込み
							fscanf(pFile, "%f", &rot.y);		//向き読み込み
							fscanf(pFile, "%f", &rot.z);		//向き読み込み

							m_apModel[nIndex]->SetRotation(rot);		//向き設定
							m_apModel[nIndex]->SetDefaultRotation(rot);	//初期向き設定
						}
					}
				}
			}
		}

		//ファイル閉じる
		fclose(pFile);
	}
}