//==============================================================
//
//プレイヤー処理[player.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "effect.h"
#include "sound.h"
#include "block.h"
#include "debugproc.h"
#include "texture.h"

//マクロ定義
#define NUM_PATTERN		(10)				//パターン数
#define MOVE_SPEED		(1.0f)				//プレイヤーの移動速度
#define ANGLE_UP		(0.75f)				//上の角度
#define ANGLE_DOWN		(0.25f)				//下の角度
#define ANGLE_WIDTH		(0.5f)				//横の角度
#define MOVE_Y			(0.5f)				//移動量Y
#define JUMP_HEIGHT		(-14.0f)			//ジャンプの高さ

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//==============================================================
//コンストラクタ
//==============================================================
CPlayer::CPlayer()
{
	m_nIdxTexture = -1;		//テクスチャの番号
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_nCounterAnim = 0;		//アニメーションカウンター
	m_nPatternAnim = 0;		//パターンNo.カウンター
	m_nRandSpeed = rand() % 4 + 1;
	m_fRandCol = (float)(rand() % 10) * 0.1f;
	m_fRandRot = (float)(rand() % 10) * 0.01f;
	m_bJump = false;		//ジャンプしたか
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CPlayer::CPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_nIdxTexture = -1;		//テクスチャの番号
	m_pos = pos;			//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = rot;			//向き
	m_nCounterAnim = 0;		//アニメーションカウンター
	m_nPatternAnim = 0;		//パターンNo.カウンター
	m_nRandSpeed = rand() % 4 + 1;		//位置を動かす速さ
	m_fRandCol = (float)(rand() % 10) * 0.1f;	//色
	m_fRandRot = (float)(rand() % 10) * 0.01f;	//向き
	m_bJump = false;		//ジャンプしたか
}

//==============================================================
//デストラクタ
//==============================================================
CPlayer::~CPlayer()
{

}

//==============================================================
//プレイヤーの生成処理
//==============================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{//メモリが使用されてなかったら

		//プレイヤーの生成
		pPlayer = new CPlayer(pos, rot);
	}

	//初期化処理
	pPlayer->Init(pos, rot);

	return pPlayer;
}

//==============================================================
//プレイヤーの初期化処理
//==============================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();

	//テクスチャの読み込み
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\player000.png");

	//テクスチャの割り当て
	CObject2D::BindTexture(m_nIdxTexture);

	//オブジェクト2Dの初期化処理
	CObject2D::Init(pos, rot);

	//種類の設定
	CObject::SetType(CObject::TYPE_PLAYER);

	//プレイヤーの大きさ設定
	CObject2D::SetSize(WIDTH_PLAYER, HEIGHT_PLAYER);

	return S_OK;
}

//==============================================================
//プレイヤーの終了処理
//==============================================================
void CPlayer::Uninit(void)
{
	//サウンド停止
	CSound::Stop();

	//2Dオブジェクトの終了処理
	CObject2D::Uninit();
}

//==============================================================
//プレイヤーの更新処理
//==============================================================
void CPlayer::Update(void)
{
	m_nCounterAnim++;

	//位置取得
	m_pos = CObject2D::GetPosition();

	//前回の位置代入
	m_posOld = m_pos;

	//移動処理
	CPlayer::Control();

	//移動量加算
	m_move.y += MOVE_Y;

	//位置更新
	m_pos += m_move;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.1f;

	//ブロックとの当たり判定処理
	if (CBlock::Collision(&m_pos, &m_posOld, &m_move, WIDTH_PLAYER, HEIGHT_PLAYER) == true)
	{//着地したら

		m_bJump = false;	//着地状態にする
	}
	else
	{
		m_bJump = true;		//ジャンプ状態にする
	}

	//画面外処理
	CPlayer::Screen();

	//位置設定
	CObject2D::SetPosition(CObject::TYPE_PLAYER, m_pos, WIDTH_PLAYER, HEIGHT_PLAYER);

	////エフェクトの生成
	//CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y - HEIGHT_PLAYER * 0.5f, m_pos.z), 
	//	D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 40.0f * 0.5f, 8, CObject::TYPE_PLAYER);
}

//==============================================================
//プレイヤーの入力処理
//==============================================================
void CPlayer::Control(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();			//ゲームパッドの情報取得

	//移動
	if (pInputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetPress(pInputJoyPad->BUTTON_X, 0) || pInputJoyPad->GetPressRX(0).x < -0.0f)
	{//Aキーが押された時

		m_move.x += sinf(-D3DX_PI * ANGLE_WIDTH) * MOVE_SPEED;
		m_move.y += cosf(-D3DX_PI * ANGLE_WIDTH) * MOVE_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetPress(pInputJoyPad->BUTTON_B, 0) || pInputJoyPad->GetPressRX(0).x > 0.0f)
	{//Dキーが押された時

		m_move.x += sinf(D3DX_PI * ANGLE_WIDTH) * MOVE_SPEED;
		m_move.y += cosf(D3DX_PI * ANGLE_WIDTH) * MOVE_SPEED;
	}

	//ジャンプ
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bJump == false)
	{//SPACEキーを押してたら && ジャンプしてなかったら

		//ジャンプする
		m_move.y = JUMP_HEIGHT;

		//ジャンプした状態にする
		m_bJump = true;
	}

	//弾発射
	if (pInputKeyboard->GetTrigger(DIK_UP) == true)
	{//↑キーを押したら

		//SE再生
		CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

		//弾の生成
		//CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - HEIGHT_PLAYER * 0.5f, m_pos.z), D3DXVECTOR3(0.0f, 10.0f, 0.0f), CObject::TYPE_PLAYER, CBullet::BULLETTYPE_WATER);
	}
	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true)
	{//↓キーを押したら

		//SE再生
		CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

		//弾の生成
		//CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - HEIGHT_PLAYER * 0.5f, m_pos.z), D3DXVECTOR3(0.0f, -10.0f, 0.0f), CObject::TYPE_PLAYER, CBullet::BULLETTYPE_WATER);
	}
	if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{//←キーを押したら

		//SE再生
		CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

		//弾の生成
		//CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - HEIGHT_PLAYER * 0.5f, m_pos.z), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), CObject::TYPE_PLAYER, CBullet::BULLETTYPE_WATER);
	}
	if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{//→キーを押したら

		//SE再生
		CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

		//弾の生成
		//CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - HEIGHT_PLAYER * 0.5f, m_pos.z), D3DXVECTOR3(10.0f, 0.0f, 0.0f), CObject::TYPE_PLAYER, CBullet::BULLETTYPE_WATER);
	}

}

//==============================================================
//画面外判定処理
//==============================================================
void CPlayer::Screen(void)
{
	//画面外判定(横)
	if (m_pos.x < WIDTH_PLAYER)
	{//画面左に出たら

		m_pos.x = WIDTH_PLAYER;

	}
	else if (m_pos.x > SCREEN_WIDTH - WIDTH_PLAYER)
	{//画面右に出たら

		m_pos.x = SCREEN_WIDTH - WIDTH_PLAYER;

	}

	//画面外判定(縦)
	if (m_pos.y < HEIGHT_PLAYER)
	{//画面上に出たら

		m_pos.y = HEIGHT_PLAYER;
	}
	else if (m_pos.y > SCREEN_HEIGHT)
	{//画面下に出たら

		m_pos.y = SCREEN_HEIGHT;
		m_move.y = 0.0f;

		m_bJump = false;
	}
}

//==============================================================
//プレイヤーの描画処理
//==============================================================
void CPlayer::Draw(void)
{
	//2Dオブジェクトの描画処理
	CObject2D::Draw();
}