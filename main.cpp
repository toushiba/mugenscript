#include "DxLib.h"
#include "MugenScript.h"
#include "MugenScriptIO.h"
#include "MugenScriptIF.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8); 
	SetAlwaysRunFlag(TRUE);
	ChangeWindowMode(TRUE),
		SetGraphMode(1280, 960, 32);
	SetWindowSize(1000, 750);
	DxLib_Init(),
		SetDrawScreen(DX_SCREEN_BACK);//ウィンドウモード変更と裏画面設定
	SetWindowIconID(333);
	SetFontSize(24);

	MugenScript::MugenScriptCommandManager manager;
	MugenScript::MugenScriptPictureLoader::instance();
	MugenScript::MugenScriptSoundLoader::instance();
	//manager.PushLoadQueue("text/NewGame_utf8.txt");
	//manager.PushLoadQueue("../MugenScript/DxLib/debug_script.txt");
	manager.StartDebugging();
	int count = 0;

#ifdef MUGEN_SCRIPT_DEBUG


 	while (1) {
		if (GetWindowActiveFlag() == TRUE)
		{
			if (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
				manager.Update();
			else
				break;

			if (CheckHitKey(KEY_INPUT_ESCAPE))
				break;
		}
		else
		{
			if (ProcessMessage() != 0)
				break;
		}
		manager.UpdateDebugging();
	}
#else
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) 
	{
		manager.Update();

		if (CheckHitKey(KEY_INPUT_ESCAPE))
			break;
	}
#endif

	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}