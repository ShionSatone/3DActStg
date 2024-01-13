//==============================================================
//
//リザルト処理[result.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _RESULT_H_		//このマクロ定義がされていなかったら
#define _RESULT_H_		//2重インクルード防止のマクロを定義する

#include "manager.h"

//前方宣言
class CScore;			//スコアの情報

//リザルト画面クラスの定義
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CScore *m_pScore;		//スコアの情報

	static bool bReset;				//リセットしたか
};

#endif

