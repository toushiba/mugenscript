#include "MugenScriptIF.h"
#include <Windows.h>

int MugenScriptDxLib::MugenScriptDxLibDebugger::StartDebugging()
{
	return debuggerSlave.StartDebugging("MugenScriptDebug");
}

void MugenScriptDxLib::MugenScriptDxLibDebugger::UpdateDebugger()
{
	if (!debuggerSlave.IsEmptyMessage())
	{
		auto message = debuggerSlave.PopMessage();
		bool set = MugenScriptDebug::MugenScriptDxLibDebuggerSlave::MugenScriptDebugProcessMessage_SetValue & message.message;
		if (set)
		{
			loadScriptPathQueue.push(debuggerSlave.GetDebugValue(message.name).value.string);
		}
	}
	debuggerSlave.UpdateDebuggerProcess();
}

bool MugenScriptDxLib::MugenScriptDxLibDebugger::IsRequestLoadScript()
{
	return !loadScriptPathQueue.empty();
}

Mugenshuen::string_t MugenScriptDxLib::MugenScriptDxLibDebugger::GetLoadScriptPath()
{
	if (IsRequestLoadScript())
	{
		auto ret= loadScriptPathQueue.front();
		loadScriptPathQueue.pop();
		return ret;
	}
	return "";
}

void MugenScriptDxLib::MugenScriptDxLibDebugger::SetDebugValue(Mugenshuen::string_t key,MugenScript::MugenScriptDatabaseValue value)
{
	debuggerSlave.SetDebugValue(key, value);
}
