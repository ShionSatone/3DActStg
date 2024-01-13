//==============================================================
//
//プレイヤー処理[playerModel.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "playerModel.h"
#include "manager.h"
#include "renderer.h"
#include "objectX.h"
#include "modelHierarchy.h"
#include "input.h"
#include "bullet.h"
#include "motion.h"
#include "camera.h"
#include "debugproc.h"
#include "particle.h"
#include "bulletRemain.h"
#include "game.h"
#include "sound.h"
#include "life.h"
#include "enemyModel.h"
#include "tutorial.h"
#include "fade.h"
#include "score.h"

//マクロ定義
#define POS					(10.0f)		//pos初期値
#define CURVE_RL			(0.5f)		//左右の角度
#define CURVE_UP			(0.0f)		//上の角度
#define CURVE_DOWN			(1.0f)		//下の角度
#define MOVE_Y				(1.0f)		//移動量Y
#define JUMP_HEIGHT			(15.0f)		//ジャンプの高さ
#define MAX_STR				(128)		//文字の最大数
#define HUMAN_MOVE			(0.5f)		//人間の移動量
#define FISH_MOVE			(0.1f)		//金魚の移動量
#define STOP_MOVE			(0.8f)		//止まる移動量
#define FILE_HUMAN			"data\\TEXT\\motion_weapon.txt"		//プレイヤーモデルのテキスト
#define LIFE_ICE			(35)				//氷の寿命
#define LIFE_VAPOR			(50)				//蒸気の寿命
#define MOVE_WATER			(10.0f)		//水の移動量
#define MOVE_ICE			(3.0f)		//氷の移動量
#define MOVE_VAPOR			(2.0f)		//蒸気の移動量
#define MAX_BULLET			(400)		//弾数
#define MAX_LIFE			(400)		//最大体力
#define HIT_CNT				(60 * 2)	//攻撃当たるまでのカウント数
#define DAMAGE_CNT			(9)			//ダメージカウント数
#define APP_CNT				(100)	//点滅時間
#define STEP_CNT			(25)	//歩く音のカウンター

//静的メンバ変数宣言
char *CPlayerModel::m_apFileName[PARTS_MAX] =
{
	"data\\MODEL\\player\\00_body.x",
	"data\\MODEL\\player\\01_head.x",
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
	"data\\MODEL\\player\\17_fish.x",
};

//==============================================================
//コンストラクタ
//==============================================================
CPlayerModel::CPlayerModel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
	m_posSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//復活用の位置
	m_posKeepHuman = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//人間の位置保存用
	m_posKeepFish = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//金魚の位置保存用
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//モデルの最大値
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//モデルの最小値
	m_fMoveBulet = 5.0f;		//弾の移動量

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//プレイヤー(パーツ)へのポインタ
	}

	m_nNumModel = 0;		//プレイヤー(パーツ)の総数
	m_bJump = false;		//ジャンプしたか
	m_pMotion = NULL;
	m_bMove = false;		//歩いてるか
	m_bLand = true;			//着地した
	m_bAction = false;		//攻撃してるかの判定
	m_fRotDest = 0.0f;	//目標
	m_fRotDiff = 0.0f;	//差分
	m_Type = PLAYERTYPE_HUMAN;		//人間の状態にする
	m_particleType = PARTICLETYPE_WATER;	//パーティクルの種類
	m_nType = 1;		//何番目のパーティクルか
	m_nParticleLife = 50;			//パーティクルの寿命
	m_state = STATE_NONE;		//状態
	m_nCntDamage = 0;			//ダメージカウンター
	m_nCntHit = HIT_CNT;			//攻撃あたるまでのカウンター
	m_bPad = false;			//パッドのスティックを倒してるか
	m_nCntSand = STEP_CNT;			//砂のパーティクルカウンター

}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CPlayerModel::CPlayerModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
	m_posSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//復活用の位置
	m_posKeepHuman = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//人間の位置保存用
	m_posKeepFish = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//金魚の位置保存用
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//モデルの最大値
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//モデルの最小値
	m_rot = rot;		//向き
	m_fMoveBulet = 5.0f;		//弾の移動量

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//プレイヤー(パーツ)へのポインタ
	}

	m_nNumModel = 0;		//プレイヤー(パーツ)の総数
	m_bJump = false;		//ジャンプしたか
	m_pMotion = NULL;
	m_bMove = false;		//歩いてるか
	m_bLand = true;			//着地した
	m_bAction = false;		//攻撃してるかの判定
	m_fRotDest = 0.0f;	//目標
	m_fRotDiff = 0.0f;	//差分

	m_Type = PLAYERTYPE_HUMAN;		//人間の状態にする
	m_particleType = PARTICLETYPE_WATER;	//パーティクルの種類
	m_nType = 1;		//何番目のパーティクルか
	m_nParticleLife = 50;			//パーティクルの寿命
	m_state = STATE_NONE;		//状態
	m_nCntDamage = 0;			//ダメージカウンター
	m_nCntHit = HIT_CNT;			//攻撃あたるまでのカウンター
	m_nCntMove = STEP_CNT;				//足音のカウンター
	m_bPad = false;			//パッドのスティックを倒してるか
	m_nCntSand = STEP_CNT;			//砂のパーティクルカウンター
}

//==============================================================
//デストラクタ
//==============================================================
CPlayerModel::~CPlayerModel()
{

}

//==============================================================
//プレイヤーの生成処理
//==============================================================
CPlayerModel *CPlayerModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayerModel *pPlayerModel = NULL;

	if (pPlayerModel == NULL)
	{//メモリが使用されてなかったら

		//プレイヤーの生成
		pPlayerModel = new CPlayerModel(pos, rot);
	}

	//初期化処理
	pPlayerModel->Init(pos, rot);

	//種類の設定
	//pPlayerModel->SetType(CObject::TYPE_PLAYER);

	return pPlayerModel;
}

//==============================================================
//プレイヤーの初期化処理
//==============================================================
HRESULT CPlayerModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CLife *pLife = CGame::GetLife();

	//位置の設定
	m_pos = pos;

	//向きの設定
	m_rot = rot;
	m_fRotDest = rot.y;

	m_posKeepFish = D3DXVECTOR3(0.0f, -5000.0f, 0.0f);		//金魚の初期位置設定

	//プレイヤーの生成（全パーツ分）
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//モーションの初期化・生成
	m_pMotion = m_pMotion->Create(m_pMotion->MOTIONTEXT_PLAYER);
	m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	m_pMotion->Init();

	//モデルのファイル読み込み
	CPlayerModel::LoadFile();

	//最大値・最小値代入
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//最大値Y
		if ((nCntPlayer <= PARTS_BODY && nCntPlayer <= PARTS_HEAD) ||
			(nCntPlayer <= PARTS_LEG_R && nCntPlayer <= PARTS_FOOT_R))
		{
			m_max.y += m_apModel[nCntPlayer]->GetSizeMax().y;		//最大値加算
		}

		//最大値入れ替え
		if (m_max.x < m_apModel[nCntPlayer]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntPlayer]->GetSizeMax().x;		//最小値X
		}
		if (m_max.z < m_apModel[nCntPlayer]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntPlayer]->GetSizeMax().z;		//最小値Z

		}

		//最小値入れ替え
		if (m_min.x > m_apModel[nCntPlayer]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntPlayer]->GetSizeMin().x;		//最小値X
		}
		if (m_min.y > m_apModel[nCntPlayer]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntPlayer]->GetSizeMin().y;		//最小値Y
		}
		if (m_min.z > m_apModel[nCntPlayer]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntPlayer]->GetSizeMin().z;		//最小値Z

		}
	}

	m_max.y += 10.0f;

	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//寿命設定
		pLife->SetMax(MAX_LIFE);
	}

	CObject::SetType(CObject::TYPE_PLAYER);

	return S_OK;
}

//==============================================================
//プレイヤーの終了処理
//==============================================================
void CPlayerModel::Uninit(void)
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		if (m_apModel[nCntPlayer] != NULL)
		{//使用されてるとき

			//終了処理
			m_apModel[nCntPlayer]->Uninit();
			m_apModel[nCntPlayer] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//使用されてるとき

		//モーションの破棄
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//プレイヤーの更新処理
//==============================================================
void CPlayerModel::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得
	CCamera *pCamera = CManager::GetCamera();		//カメラの情報取得
	CGame *pGame = CScene::GetGame();

#if _DEBUG

	if (pInputKeyboard->GetTrigger(DIK_F4) == true)
	{//F4が押されたとき

		//プレイヤーの種類入れ替え
		m_Type = m_Type ? PLAYERTYPE_HUMAN : PLAYERTYPE_GOLDFISH;

		//待機モーションに設定
		m_pMotion->Set(m_pMotion->MOTIONTYPE_NEUTRAL);

		if (m_Type == PLAYERTYPE_HUMAN)
		{//人間になったら

			m_posKeepFish = m_pos;		//金魚の位置保存しておく
			m_pos = m_posKeepHuman;		//地上の位置に戻る
			m_rot = D3DXVECTOR3(0.0f, 0.5f * -D3DX_PI, 0.0f);
			m_fRotDest = 0.5f * -D3DX_PI;
			pCamera->SetPositionVY(m_pos.y + 189.0f + sinf(m_rot.x) * -300.0f);		//カメラの位置設定
			pCamera->SetPositionRY(m_pos.y + 168.0f + sinf(m_rot.x) * -10.0f);		//カメラの位置設定
			pCamera->SetMode(true);		//平行投影
			pCamera->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			pGame->SetGameMode(pGame->GAMEMODE_GROUND);		//地上モードに設定
		}
		else if(m_Type == PLAYERTYPE_GOLDFISH)
		{//金魚になったら

			m_posKeepHuman = m_pos;		//人間の位置保存しておく
			m_pos = m_posKeepFish;		//水中の位置に戻る
			m_rot = D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f);
			m_fRotDest = 1.0f * D3DX_PI;
			pCamera->SetPositionVY(m_pos.y + 50.0f + sinf(m_rot.x) * 300.0f);		//カメラの位置設定
			pCamera->SetPositionRY(m_pos.y + 50.0f + sinf(m_rot.x) * 300.0f);		//カメラの位置設定

			pGame->SetGameMode(pGame->GAMEMODE_UNDER);		//水中モードに設定
		}
	}

#endif

	//前回の位置更新
	m_posOld = m_pos;

	switch (m_Type)
	{
	case PLAYERTYPE_HUMAN:		//人間

		//人間の更新処理
		CPlayerModel::UpdateHuman();

		pDebugProc->Print("\n-----[人間の姿]-----\n");
		pDebugProc->Print("\n～～[地上エリア]～～\n");

		break;

	case PLAYERTYPE_GOLDFISH:	//金魚

		//金魚の更新処理
		CPlayerModel::UpdataFish();

		pDebugProc->Print("\n-----[金魚の姿]-----\n");
		pDebugProc->Print("\n～～[水中エリア]～～\n");

		break;
	}

	//モーションの更新処理
	m_pMotion->Update();

	//デバッグ表示
	pDebugProc->Print("\nプレイヤーの位置 (%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);
	pDebugProc->Print("プレイヤーの移動量 (%f, %f, %f)\n", m_move.x, m_move.y, m_move.z);
	pDebugProc->Print("プレイヤーの向き   (%f, %f, %f)\n", m_rot.x, m_rot.y, m_rot.z);
}

//==============================================================
//人間の更新処理
//==============================================================
void CPlayerModel::UpdateHuman(void)
{
	CLife *pLife = CGame::GetLife();
	CSound *pSound = CManager::GetSound();

	if (m_pos.x >= 10240.0f && m_pos.y >= -4300.0f)
	{
		
	}
	else
	{
		//プレイヤーの操作
		CPlayerModel::ControlHumanKeyboard();
		CPlayerModel::ControlHumanPad();
	}

	if (m_bMove == true && m_bJump == false)
	{//歩いてるとき && ジャンプしてない

		if ((m_nCntMove % STEP_CNT) == 0)
		{//一定時間たったら

			//BGM再生
			pSound->Play(pSound->SOUND_LABEL_SE_STEP);
		}
	}
	else
	{
		m_nCntMove = STEP_CNT;
	}

	m_nCntMove++;

	//移動量加算
	m_move.y -= MOVE_Y;

	//位置更新
	m_pos += m_move;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.1f;
	//m_move.z += (0.0f - m_move.z) * 0.1f;

	switch (m_state)
	{
	case STATE_NONE:		//通常状態

		break;

	case STATE_ATTACK:		//攻撃状態

		break;

	case STATE_DAMAGE:		//ダメージ状態

		m_nCntDamage--;		//ダメージ時間減算
		m_nCntHit--;		//攻撃あたるまでのカウンター減算

		if (m_nCntDamage <= 0)
		{//ダメージ時間が終わったら

			m_state = CObject::STATE_NONE;

			//状態設定
			for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
			{
				m_apModel[nCntPlayer]->SetState(m_state);		//通常状態にする

			}
		}

		break;

	case STATE_APPEAR:		//点滅状態

		m_nCntDamage--;		//ダメージ時間減算

		if ((m_nCntDamage % 3) == 0)
		{//一定時間経ったら

			//表示切替
			for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
			{
				m_apModel[nCntPlayer]->SetDisp();

			}
		}

		if (m_nCntDamage <= 0)
		{//ダメージ時間が終わったら

			m_state = CObject::STATE_NONE;		//通常状態にする

			//状態設定
			for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
			{
				m_apModel[nCntPlayer]->SetState(m_state);		//状態設定

			}
		}

		break;

	case STATE_DEATH:		//死亡状態

		pLife->SetMax(MAX_LIFE);
		pLife->SetNumCon(0);
		m_nCntDamage = APP_CNT;

		CScore *pScore = CGame::GetScore();		//スコアの情報
		CFade *pFade = CManager::GetFade();		//フェードの情報取得

		//スコア設定
		CManager::SetNumScore(pScore->Get());

		//リザルトの判定
		CManager::SetResult(false);

		//リザルト
		pFade->SetFade(CScene::MODE_RESULT);

		break;
	}

	//当たり判定
	if (CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max) == true)
	{//着地したら

		//最後に着地した位置
		if (m_pos.x >= 7715.0f && m_pos.x <= 8460.0f)
		{
			m_posSave = D3DXVECTOR3(7715.0f, 130.0f, m_pos.z);
		}
		else
		{
			m_posSave = m_pos;
		}

		if (m_bLand == false)
		{
			//パーティクルの生成
			CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXCOLOR(0.8f, 0.7f, 0.6f, 0.8f), PARTICLETYPE_MOVE, 20, 10.0f);
		}

		m_bJump = false;	//ジャンプしてない状態にする
		m_bLand = true;		//着地した状態にする

		if ((m_pMotion->GetType() != m_pMotion->MOTIONTYPE_MOVE && m_bMove == true && m_bJump == false && m_bLand == true && m_bAction == false))
		{//地面についたら(そのあと移動)

			//移動状態にする
			m_pMotion->Set(m_pMotion->MOTIONTYPE_MOVE);


		}
		else if ((m_pMotion->GetType() == m_pMotion->MOTIONTYPE_JUMP && m_bMove == false && m_bJump == false && m_bLand == true && m_bAction == false))
		{//地面についたら(完全に止まる)

			//着地状態にする
			m_pMotion->Set(m_pMotion->MOTIONTYPE_LAND);
		}

		//パーティクル生成
		//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);
	}
	else if (CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max) == false)
	{
		m_bJump = true;		//ジャンプしてる状態にする
		m_bLand = false;	//着地してない状態にする
	}

	//向きの補正
	CPlayerModel::RotCorrection();

	//画面外処理
	CPlayerModel::Screen();

	if (m_bMove == true && m_pMotion->GetType() == m_pMotion->MOTIONTYPE_NEUTRAL)
	{//歩いてる && 待機状態

		//歩かせる
		m_pMotion->Set(m_pMotion->MOTIONTYPE_MOVE);
	}
	else if (m_pMotion->IsFinish() == true && m_bAction == true)
	{//攻撃が終わったら

		m_bAction = false;		//攻撃してない状態にする
	}
	else if ((m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_pMotion->IsFinish() == true) ||
		(m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_bMove == false && m_bJump == false && m_bLand == true && m_bAction == false))
	{//モーションが終了したら

		//待機状態に戻す
		m_pMotion->Set(m_pMotion->MOTIONTYPE_NEUTRAL);
	}
}

//==============================================================
//金魚の更新処理
//==============================================================
void CPlayerModel::UpdataFish(void)
{
	//プレイヤーの操作
	CPlayerModel::ControlGoldFish();

	//位置更新
	m_pos += m_move;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//当たり判定
	/*for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_apModel[nCntPlayer]->GetSizeMin(), m_apModel[nCntPlayer]->GetSizeMax());
	}*/

	//向きの補正
	CPlayerModel::RotCorrection();

	//画面外処理
	CPlayerModel::Screen();
}

//==============================================================
//向きの補正処理
//==============================================================
void CPlayerModel::RotCorrection(void)
{
	//向きの差分を求める
	m_fRotDiff = m_fRotDest - m_rot.y;

	//目標の方向までの差分を修正
	if (m_fRotDiff < -D3DX_PI)
	{
		m_fRotDiff += D3DX_PI * 2;
	}
	else if (m_fRotDiff > D3DX_PI)
	{
		m_fRotDiff -= D3DX_PI * 2;
	}

	//差分足す
	m_rot.y += m_fRotDiff * 0.1f;

	//現在の方向修正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//==============================================================
//プレイヤーのキーボード操作処理(人間)
//==============================================================
void CPlayerModel::ControlHumanKeyboard(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得
	CCamera *pCamera = CManager::GetCamera();		//カメラの情報取得
	CBulletRemain *pBulletRemainGame = CGame::GetBulletRemain();
	CLife *pLife = CGame::GetLife();
	CSound *pSound = CManager::GetSound();

	//移動
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{//右

#if 0

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//奥
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * HUMAN_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * HUMAN_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -0.75f;

		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//手前
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * HUMAN_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * HUMAN_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -0.25f;

		}
		else
#endif
		{
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * HUMAN_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * HUMAN_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;
		}

		m_bMove = true;		//歩かせる
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{//左

#if 0

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//奥
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * HUMAN_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * HUMAN_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.75f;

		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//手前
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * HUMAN_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * HUMAN_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.25f;

		}
		else
#endif
		{
			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * HUMAN_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * HUMAN_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;
		}

		m_bMove = true;		//歩かせる
	}

#if 0
	else if (pInputKeyboard->GetPress(DIK_W) == true)
	{//奥
		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_UP) * HUMAN_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_UP) * HUMAN_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 1.0f;

		m_bMove = true;		//歩かせる

	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{//手前
		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_DOWN) * HUMAN_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_DOWN) * HUMAN_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.0f;

		m_bMove = true;		//歩かせる

	}
#endif

	if ((m_move.x <= STOP_MOVE && m_move.x >= -STOP_MOVE) && (m_move.z <= STOP_MOVE && m_move.z >= -STOP_MOVE))
	{//歩いてないとき

		m_bMove = false;		//歩いてない状態にする
	}

	if ((CManager::GetMode() == CScene::MODE_TUTORIAL && CTutorial::GetStep() >= CTutorial::STEP_JUMP) || CManager::GetMode() == CScene::MODE_GAME)
	{
		//ジャンプ
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bJump == false)
		{//SPACEキーを押してたら && ジャンプしてなかったら

			//ジャンプする
			m_move.y = JUMP_HEIGHT;

			//ジャンプした状態にする
			m_bJump = true;
			m_bLand = false;

			//BGM再生
			pSound->Play(pSound->SOUND_LABEL_SE_JUMP);

			//モーションの設定
			m_pMotion->Set(m_pMotion->MOTIONTYPE_JUMP);
		}
	}

	//弾発射
	if ((CManager::GetMode() == CScene::MODE_TUTORIAL && CTutorial::GetStep() >= CTutorial::STEP_BULLET) || 
		(CManager::GetMode() == CScene::MODE_GAME) && pBulletRemainGame->GetNumBullet() < MAX_BULLET)
	{
		if (pInputKeyboard->GetTrigger(DIK_I) == true)
		{//↑キーを押したら

			//弾の生成
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(0.0f, m_fMoveBulet, 0.0f), CObject::TYPE_PLAYER, m_particleType);

			//パーティクル生成
			//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

			//SE再生
			CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

			if (m_bAction == false)
			{
				//モーションの設定
				m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
			}

			m_bAction = true;		//攻撃してる状態にする
		}
		else if (pInputKeyboard->GetTrigger(DIK_K) == true)
		{//↓キーを押したら

			//SE再生
			CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

			//弾の生成
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(0.0f, -m_fMoveBulet, 0.0f), CObject::TYPE_PLAYER, m_particleType);

			//パーティクル生成
			//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

			if (m_bAction == false)
			{
				//モーションの設定
				m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
			}

			m_bAction = true;
		}
		else if (pInputKeyboard->GetTrigger(DIK_J) == true)
		{//←キーを押したら

			//SE再生
			CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

			//向き変更
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;

			//弾の生成
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(-m_fMoveBulet, 0.0f, 0.0f), CObject::TYPE_PLAYER, m_particleType);

			//パーティクル生成
			//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

			if (m_bAction == false)
			{
				//モーションの設定
				m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
			}

			m_bAction = true;

		}
		else if (pInputKeyboard->GetTrigger(DIK_L) == true)
		{//→キーを押したら

			//SE再生
			CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

			//向き変更
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;

			//弾の生成
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(m_fMoveBulet, 0.0f, 0.0f), CObject::TYPE_PLAYER, m_particleType);

			//パーティクル生成
			//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

			if (m_bAction == false)
			{
				//モーションの設定
				m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
			}

			m_bAction = true;
		}
		else if (pInputKeyboard->GetTrigger(DIK_U) == true)
		{//RSHIFTキーを押したら

			//SE再生
			CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

			//向き変更
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;

			//弾の生成
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), 
				D3DXVECTOR3(sinf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * m_fMoveBulet, 
					cosf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * m_fMoveBulet, 
					0.0f), CObject::TYPE_PLAYER, m_particleType);

			//パーティクル生成
			//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

			if (m_bAction == false)
			{
				//モーションの設定
				m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
			}

			m_bAction = true;

		}
		else if (pInputKeyboard->GetTrigger(DIK_M) == true)
		{//Mキーを押したら(左下)

			//SE再生
			CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

			//向き変更
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;

			//弾の生成
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
				D3DXVECTOR3(sinf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * m_fMoveBulet,
					cosf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * m_fMoveBulet,
					0.0f), CObject::TYPE_PLAYER, m_particleType);

			//パーティクル生成
			//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

			if (m_bAction == false)
			{
				//モーションの設定
				m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
			}

			m_bAction = true;

		}
		else if (pInputKeyboard->GetTrigger(DIK_O) == true)
		{//ENDキーを押したら

			//SE再生
			CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

			//向き変更
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;

			//弾の生成
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
				D3DXVECTOR3(sinf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * m_fMoveBulet,
					cosf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * m_fMoveBulet,
					0.0f), CObject::TYPE_PLAYER, m_particleType);

			//パーティクル生成
			//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

			if (m_bAction == false)
			{
				//モーションの設定
				m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
			}

			m_bAction = true;

		}
		else if (pInputKeyboard->GetTrigger(DIK_PERIOD) == true)
		{//.キーを押したら

			//SE再生
			CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

			//向き変更
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;

			//弾の生成
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
				D3DXVECTOR3(sinf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * m_fMoveBulet,
					cosf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * m_fMoveBulet,
					0.0f), CObject::TYPE_PLAYER, m_particleType);

			//パーティクル生成
			//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

			if (m_bAction == false)
			{
				//モーションの設定
				m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
			}

			m_bAction = true;

		}

	}

	

#if 0
	//弾の種類
	if (pInputKeyboard->GetTrigger(DIK_7) == true)
	{//7キーを押したら

		if (m_nType > PARTICLETYPE_WATER)
		{//1番目より上だったら

			m_nType -= 1;
		}
		else if (m_nType <= PARTICLETYPE_WATER)
		{//1番目以下だったら

			m_nType = PARTICLETYPE_VAPOR;		//3番目にする
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_8) == true)
	{//8キーを押したら

		if (m_nType < PARTICLETYPE_VAPOR)
		{//3番目より下だったら

			m_nType += 1;
		}
		else if (m_nType >= PARTICLETYPE_VAPOR)
		{//3番目以上だったら

			m_nType = PARTICLETYPE_WATER;
		}
	}

	//弾の種類切り替え
	switch (m_nType)
	{
	case PARTICLETYPE_WATER:	//水

		m_particleType = PARTICLETYPE_WATER;
		m_fMoveBulet = MOVE_WATER;

		break;

	case PARTICLETYPE_ICE:		//氷

		m_particleType = PARTICLETYPE_ICE;
		m_fMoveBulet = MOVE_ICE;

		break;

	case PARTICLETYPE_VAPOR:	//蒸気

		m_particleType = PARTICLETYPE_VAPOR;
		m_fMoveBulet = MOVE_VAPOR;

		break;
	}
#endif
}

//==============================================================
//プレイヤーのパッド操作処理(人間)
//==============================================================
void CPlayerModel::ControlHumanPad(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();			//パッドの情報
	CCamera *pCamera = CManager::GetCamera();		//カメラの情報取得
	CBulletRemain *pBulletRemainGame = CGame::GetBulletRemain();
	CLife *pLife = CGame::GetLife();
	CSound *pSound = CManager::GetSound();

	//移動
	if (pInputJoyPad->GetPressLX(0).x > 0.0f)
	{//右
		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * HUMAN_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * HUMAN_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;

		m_bMove = true;		//歩かせる
	}
	else if (pInputJoyPad->GetPressLX(0).x < 0.0f)
	{//左

		m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * HUMAN_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * HUMAN_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;

		m_bMove = true;		//歩かせる
	}

	if ((m_move.x <= STOP_MOVE && m_move.x >= -STOP_MOVE) && (m_move.z <= STOP_MOVE && m_move.z >= -STOP_MOVE))
	{//歩いてないとき

		m_bMove = false;		//歩いてない状態にする
	}

	if ((CManager::GetMode() == CScene::MODE_TUTORIAL && CTutorial::GetStep() >= CTutorial::STEP_JUMP) || CManager::GetMode() == CScene::MODE_GAME)
	{
		//ジャンプ
		if (pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_B, 0) == true && m_bJump == false)
		{//Bボタンを押してたら && ジャンプしてなかったら

			//ジャンプする
			m_move.y = JUMP_HEIGHT;

			//ジャンプした状態にする
			m_bJump = true;
			m_bLand = false;

			//BGM再生
			pSound->Play(pSound->SOUND_LABEL_SE_JUMP);

			//モーションの設定
			m_pMotion->Set(m_pMotion->MOTIONTYPE_JUMP);
		}
	}

	if (pInputJoyPad->GetPressRX(0).y == 0.0f && pInputJoyPad->GetPressRX(0).x == 0.0f)
	{
		m_bPad = false;		//スティックを倒してない状態にする
	}

	//弾発射
	if ((CManager::GetMode() == CScene::MODE_TUTORIAL && CTutorial::GetStep() >= CTutorial::STEP_BULLET) ||
		(CManager::GetMode() == CScene::MODE_GAME) && pBulletRemainGame->GetNumBullet() < MAX_BULLET)
	{
		if (m_bPad == false)
		{//スティックを倒してなかったら

			if (pInputJoyPad->GetPressRX(0).x < 0.0f)
			{//←キーを押したら

				if (pInputJoyPad->GetPressRX(0).y > 0.0f)
				{//↑キーを押したら

					//弾の生成
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
						D3DXVECTOR3(sinf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * m_fMoveBulet,
							cosf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * m_fMoveBulet,
							0.0f), CObject::TYPE_PLAYER, m_particleType);
				}
				else if (pInputJoyPad->GetPressRX(0).y < 0.0f)
				{//↓キーを押したら

					//弾の生成
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
						D3DXVECTOR3(sinf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * m_fMoveBulet,
							cosf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * m_fMoveBulet,
							0.0f), CObject::TYPE_PLAYER, m_particleType);
				}
				else
				{
					//弾の生成
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(-m_fMoveBulet, 0.0f, 0.0f), CObject::TYPE_PLAYER, m_particleType);
				}

				m_bPad = true;

				//SE再生
				CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

				//向き変更
				m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;

				//パーティクル生成
				//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

				if (m_bAction == false)
				{
					//モーションの設定
					m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
				}

				m_bAction = true;

			}
			else if (pInputJoyPad->GetPressRX(0).x > 0.0f)
			{//→キーを押したら

				if (pInputJoyPad->GetPressRX(0).y > 0.0f)
				{//↑キーを押したら

					//弾の生成
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
						D3DXVECTOR3(sinf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * m_fMoveBulet,
							cosf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * m_fMoveBulet,
							0.0f), CObject::TYPE_PLAYER, m_particleType);
				}
				else if (pInputJoyPad->GetPressRX(0).y < 0.0f)
				{//↓キーを押したら

					//弾の生成
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
						D3DXVECTOR3(sinf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * m_fMoveBulet,
							cosf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * m_fMoveBulet,
							0.0f), CObject::TYPE_PLAYER, m_particleType);
				}
				else
				{
					//弾の生成
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(m_fMoveBulet, 0.0f, 0.0f), CObject::TYPE_PLAYER, m_particleType);
				}

				m_bPad = true;

				//SE再生
				CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

				//向き変更
				m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;

				//パーティクル生成
				//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

				if (m_bAction == false)
				{
					//モーションの設定
					m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
				}

				m_bAction = true;
			}
			else if (pInputJoyPad->GetPressRX(0).y > 0.0f)
			{//↑キーを押したら

				m_bPad = true;

				//弾の生成
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(0.0f, m_fMoveBulet, 0.0f), CObject::TYPE_PLAYER, m_particleType);

				//パーティクル生成
				//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

				//SE再生
				CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

				if (m_bAction == false)
				{
					//モーションの設定
					m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
				}

				m_bAction = true;		//攻撃してる状態にする
			}
			else if (pInputJoyPad->GetPressRX(0).y < 0.0f)
			{//↓キーを押したら

				m_bPad = true;

				//SE再生
				CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

				//弾の生成
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(0.0f, -m_fMoveBulet, 0.0f), CObject::TYPE_PLAYER, m_particleType);

				//パーティクル生成
				//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);

				if (m_bAction == false)
				{
					//モーションの設定
					m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
				}

				m_bAction = true;
			}
		}

	}
}

//==============================================================
//プレイヤーの操作処理(金魚)
//==============================================================
void CPlayerModel::ControlGoldFish(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得
	CCamera *pCamera = CManager::GetCamera();		//カメラの情報取得

	//移動
#if 0		
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{//右

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//奥
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * FISH_MOVE;
			m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * FISH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -0.75f;

		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//手前
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * FISH_MOVE;
			m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * FISH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -0.25f;

		}
		else
		{
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FISH_MOVE;
			m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FISH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{//左

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//奥
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * FISH_MOVE;
			m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * FISH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.75f;

		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//手前
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * FISH_MOVE;
			m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * FISH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.25f;

		}
		else
		{
			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FISH_MOVE;
			m_move.y += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FISH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;
		}
	}

	else if (pInputKeyboard->GetPress(DIK_W) == true)
	{//上
		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_UP) * FISH_MOVE;
		m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_UP) * FISH_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 1.0f;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{//下
		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_DOWN) * FISH_MOVE;
		m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_DOWN) * FISH_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.0f;
	}
#endif

	//奥に進む
	m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_UP) * FISH_MOVE;
	m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_UP) * FISH_MOVE;
	m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 1.0f;

	m_bMove = true;		//泳がせる
}

//==============================================================
//画面外判定処理
//==============================================================
void CPlayerModel::Screen(void)
{
	CGame *pGame = CScene::GetGame();

	if (CManager::GetMode() == CScene::MODE_TUTORIAL && m_pos.x > 300.0f)
	{//チュートリアルのとき

		m_pos.x = 300.0f;
		m_move.x = 0.0f;
	}
	else if (pGame->GetGameMode() == pGame->GAMEMODE_BOSS && m_pos.x < 9700.0f)
	{
		//ゲームモード変更
		pGame->SetGameMode(pGame->GAMEMODE_GROUND);
	}
	else if (m_Type == PLAYERTYPE_HUMAN && pGame->GetGameMode() != pGame->GAMEMODE_BOSS &&
		m_pos.y < -200.0f && 
		m_pos.x > -1000.0f && m_pos.x < 9700.0f)
	{//画面下に出たら

		if (m_rot.y < 0)
		{
			m_pos = D3DXVECTOR3(m_posSave.x - 100.0f, m_posSave.y, m_posSave.z);
		}
		else if (m_rot.y > 0)
		{
			m_pos = D3DXVECTOR3(m_posSave.x + 100.0f, m_posSave.y, m_posSave.z);
		}

		m_bLand = true;		//着地した
		m_bJump = false;	//ジャンプしてない

		m_state = STATE_NONE;		//通常状態にする

		m_nCntDamage = 0;

		CPlayerModel::Hit();
	}
	else if (m_Type == PLAYERTYPE_HUMAN && m_pos.x >= 9700.0f && m_pos.y <= 0.0f &&
		pGame->GetGameMode() != pGame->GAMEMODE_BOSS)
	{//ステージの端に来たら

		//ゲームモード変更
		pGame->SetGameMode(pGame->GAMEMODE_BOSS);
	}
}

//==============================================================
//プレイヤーの描画処理
//==============================================================
void CPlayerModel::Draw(void)
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

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//プレイヤーの描画
		m_apModel[nCntPlayer]->Draw();
	}
}

//==============================================================
//プレイヤーのヒット処理
//==============================================================
void CPlayerModel::Hit(void)
{
	CLife *pLife = CGame::GetLife();
	CSound *pSound = CManager::GetSound();
	int nLife = 0;

	if (m_state != CObject::STATE_DAMAGE && m_state != CObject::STATE_APPEAR && m_nCntDamage <= 0)
	{
		//BGM再生
		pSound->Play(pSound->SOUND_LABEL_SE_DAMAGE001);

		//体力減らす
		pLife->SetNum(-40);

		//寿命取得
		nLife = pLife->GetMax();

		if (nLife > 0)
		{//まだ寿命が残ってたら

			m_state = CObject::STATE_APPEAR;

			m_nCntDamage = HIT_CNT;			//ダメージ状態を保つ時間設定
			m_nCntHit = HIT_CNT;				//攻撃あたるまでのカウンター

			for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
			{
				//プレイヤーの色設定
				m_apModel[nCntPlayer]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			}
		}
		else if (nLife <= 0)
		{//寿命がなかったら

			m_state = CObject::STATE_DEATH;

			//パーティクル生成
			CParticle::Create(m_pos, D3DXCOLOR(0.1f, 0.4f, 0.5f, 1.0f), PARTICLETYPE_ENEMY, 30, 40);
		}

		//状態設定
		for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
		{
			m_apModel[nCntPlayer]->SetState(m_state);		//ダメージ状態にする
		}
	}
}

//==============================================================
//モデルファイル読み込み処理
//==============================================================
void CPlayerModel::LoadFile(void)
{
	FILE *pFile;				//ファイルポインタ
	char aString[MAX_STR];		//文字読み込み
	int nIndex = 0, nParent = 0;	//パーツNo.,親番号
	D3DXVECTOR3 pos, rot;

	//ファイル開く
	pFile = fopen(FILE_HUMAN, "r");

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