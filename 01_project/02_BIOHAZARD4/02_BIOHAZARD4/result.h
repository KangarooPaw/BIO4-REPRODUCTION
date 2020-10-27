//=============================================================================
//
// リザルト処理 [tutorial.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
//ヘッダファイルのインクルード
//*****************************************************************************
#include "mode.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CResult :public CMode
{
public:
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

#endif