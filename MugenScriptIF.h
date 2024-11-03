#pragma once
#include "DxLibDebugSlave.h"
#ifdef _DEBUG
#define  MUGEN_SCRIPT_DEBUG
#endif

#define MUGEN_SCRIPT_DEBUG

namespace MugenScriptDxLib
{
	class MugenScriptDxLibDebugger
	{
	public:

		int StartDebugging();
		void UpdateDebugger();
		bool IsRequestLoadScript();
		Mugenshuen::string_t GetLoadScriptPath();
		void SetDebugValue(Mugenshuen::string_t key, MugenScript::MugenScriptDatabaseValue value);
	private:
		Mugenshuen::queue_t<Mugenshuen::string_t> loadScriptPathQueue;
		MugenScriptDebug::MugenScriptDxLibDebuggerSlave debuggerSlave;
	}static debugger;
}