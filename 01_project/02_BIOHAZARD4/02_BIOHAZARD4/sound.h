//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include <xaudio2.h>

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		//タイトル
		SOUND_LABEL_BGM_TUTORIAL,		//チュートリアル
		SOUND_LABEL_BGM_GAME,			//ゲーム
		SOUND_LABEL_BGM_RESULT,			//リザルト
		SOUND_LABEL_SE_BACK_WALK,		//後ろに歩く
		SOUND_LABEL_SE_DASH,			//ダッシュ
		SOUND_LABEL_SE_DECISION,		//決定
		SOUND_LABEL_SE_DOOR_OPEN,		//門を開く
		SOUND_LABEL_SE_GAME_START,		//ゲームスタート
		SOUND_LABEL_SE_GET,				//アイテム取得
		SOUND_LABEL_SE_KNIFE,			//ナイフ
		SOUND_LABEL_SE_PLAYER_DAMAGE,	//ダメージ(プレイヤー)
		SOUND_LABEL_SE_RELOAD,			//リロード
		SOUND_LABEL_SE_ROTATION,		//ゾンビの回転
		SOUND_LABEL_SE_SHOT,			//射撃
		SOUND_LABEL_SE_TURN,			//後ろを向く
		SOUND_LABEL_SE_WOODEN_BOX,		//木箱を破壊
		SOUND_LABEL_SE_ZOMBIE_DAMAGE,	//ダメージ(ゾンビ)
		SOUND_LABEL_SE_ZOMBIE_DEATH,	//死(ゾンビ)
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								    // XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			    // マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];

};

#endif
