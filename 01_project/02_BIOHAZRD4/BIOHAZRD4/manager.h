#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//前方宣言
class CRenderer;
class CPlayer;
class CInputKeyboard;
class CCamera;
class CLight;
class CDebugProc;

//マネージャークラス
class CManager
{
public:
	CManager();//インクリメント
	~CManager();//デクリメント
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindouw);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理

	CPlayer *GetPlayer(void);				//プレイヤー
	static CInputKeyboard *GetInput(void);	//レンダラー
	static CRenderer *GetRenderer(void);	//キーボード
	static CCamera *GetCamera(void);		//カメラ
	static CLight *GetLight(void);			//ライト
	static CDebugProc*GetDebug(void);		//デバッグ
private:								  
	static CPlayer *m_pPlayer;				//プレイヤー
	static CRenderer *m_pRenderer;			//レンダラー
	static CInputKeyboard *m_pInputKeyboard;//キーボード
	static CCamera *m_pCamera;				//カメラ
	static CLight *m_pLight;				//ライト
	static CDebugProc*m_pDebugProc;			//デバッグ
};	

#endif // !_MANAGER_H_
