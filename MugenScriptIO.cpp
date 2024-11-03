#include "MugenScriptIO.h"
#include "MugenScriptIF.h"
#include <fstream>
void MugenScript::MugenScriptSelector::Init(size_type numRow, size_type numColumn)
{
	assert(numRow);
	assert(numColumn);
	selector.resize(numColumn);
	value.resize(numColumn);
	for (size_type i = 0; i < numColumn; ++i)
	{
		selector[i].resize(numRow);
		value[i].resize(numRow);
	}
}

void MugenScript::MugenScriptSelector::SetSelect(size_type row, size_type column, MugenScriptContainer::string_t name, int returnValue)
{
	assert(column < selector.size());
	assert(row < selector[column].size());

	selector[column][row] = name;
	value[column][row] = returnValue;
}

MugenScriptContainer::string_t MugenScript::MugenScriptSelector::GetSelectName(size_type row, size_type column)
{
	assert(column < selector.size());
	assert(row < selector[column].size());
	return selector[column][row];
}

int MugenScript::MugenScriptSelector::GetSelectValue(size_type row, size_type column)
{
	assert(column < selector.size());
	assert(row < selector[column].size());
	return value[column][row];
}

void MugenScript::MugenScriptSelectorBox::SetSelectorPos(size_type numRow, size_type numColumn, size_type sizeRow, size_type sizeColumn)
{
	this->numRow = numRow;
	this->numColumn = numColumn;
	this->sizeRow = sizeRow;
	this->sizeColumn = sizeColumn;
}

void MugenScript::MugenScriptSelectorBox::GetSelectorPosSizeDivNum(size_type row, size_type column, const position_t base, position_t& pos)
{
	pos.y = base.y + sizeRow * row / numRow;
	pos.x = base.x + sizeColumn * column / sizeColumn;
}

void MugenScript::MugenScriptSelectorBox::GetSelectorPosSizeMulNum(size_type row, size_type column, const position_t base, position_t& pos)
{
	assert(row < numRow);
	assert(column < numColumn);
	pos.y = base.y + sizeRow * row;
	pos.x = base.x + sizeColumn * column;
}


void MugenScript::MugenScriptSelectorIndex::Init(size_type numRow, size_type numColumn)
{
	this->numRow = numRow;
	this->numColumn = numColumn;
	indexRow = 0;
	indexColumn = 0;
}

void MugenScript::MugenScriptSelectorIndex::IncrementRow()
{
	indexRow = abs(++indexRow) % numRow;
}

void MugenScript::MugenScriptSelectorIndex::DecrementRow()
{
	if (!indexRow)
		indexRow = numRow;
	indexRow = abs(--indexRow) % numRow;
}

void MugenScript::MugenScriptSelectorIndex::IncrementColumn()
{
	indexColumn = abs(++indexColumn) % numColumn;
}

void MugenScript::MugenScriptSelectorIndex::DecrementColumn()
{
	if (!indexColumn)
		indexColumn = numColumn;
	indexColumn = abs(--indexColumn) % numColumn;
}

int MugenScript::MugenScriptSelectorIndex::GetIndexRow()
{
	return indexRow;
}

int MugenScript::MugenScriptSelectorIndex::GetIndexColumn()
{
	return indexColumn;
}

void MugenScript::MugenScriptSelectorIndex::SetIndex(int value)
{
	indexRow = value;
	indexColumn = value;
}

void MugenScript::MugenScriptDxLibKeyInput::Key_Update() 
{
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			mKey[i]++;
		}
		else {
			mKey[i] = 0;
		}
	}
}

int MugenScript::MugenScriptDxLibKeyInput::Key_Get(int KeyCode) 
{
	return mKey[KeyCode];
}
int MugenScript::MugenScriptDxLibKeyInput::InputKeyDecide()
{
	return Key_Get(KEY_INPUT_Z) + Key_Get(KEY_INPUT_RETURN) + Key_Get(KEY_INPUT_SPACE);
}
int MugenScript::MugenScriptDxLibKeyInput::InputKeyCancel()
{
	return Key_Get(KEY_INPUT_X) + Key_Get(KEY_INPUT_BACK) + Key_Get(KEY_INPUT_ESCAPE);
}
int MugenScript::MugenScriptDxLibKeyInput::InputKeyMenu()
{
	return Key_Get(KEY_INPUT_TAB) + Key_Get(KEY_INPUT_C);
}
int MugenScript::MugenScriptDxLibKeyInput::InputKeyRight()
{
	return Key_Get(KEY_INPUT_RIGHT);
}
int MugenScript::MugenScriptDxLibKeyInput::InputKeyLeft()
{
	return Key_Get(KEY_INPUT_LEFT);
}
int MugenScript::MugenScriptDxLibKeyInput::InputKeyUp()
{
	return Key_Get(KEY_INPUT_UP);
}
int MugenScript::MugenScriptDxLibKeyInput::InputKeyDown()
{
	return Key_Get(KEY_INPUT_DOWN);
}
int MugenScript::MugenScriptDxLibKeyInput::InputKeyEnter()
{
	return Key_Get(KEY_INPUT_RETURN);
}
MugenScript::MugenScriptDxLibKeyInput& MugenScript::MugenScriptDxLibKeyInput::instance()
{
	static MugenScriptDxLibKeyInput input;
	return input;
}

void MugenScript::MugenScriptCommandInputText::Init()
{
	ZeroMemory(buffer, sizeof(buffer));
	if (inputKeyHandle)
		DeleteKeyInput(inputKeyHandle);
	inputKeyHandle = MakeKeyInput(16, FALSE, FALSE, FALSE);
	SetActiveKeyInput(inputKeyHandle);
}

void MugenScript::MugenScriptCommandInputText::Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)
{
	if (opecode != MSM_REQUEST_INPUT_TEXT)
		return;

	auto& key = MugenScript::MugenScriptDxLibKeyInput::instance();
	if (key.InputKeyEnter() == 1 && CheckKeyInput(inputKeyHandle))
	{
		if (strcmp(buffer,"")==0)
		{
			DeleteKeyInput(inputKeyHandle);
			inputKeyHandle = 0;
		}
	}
	if (inputKeyHandle)
	{
		SetActiveKeyInput(inputKeyHandle);
		GetKeyInputString(buffer, inputKeyHandle);
	}
	registerName = PopStack().value.str;
}

bool MugenScript::MugenScriptCommandInputText::IsActive() const
{
	return inputKeyHandle;
}

bool MugenScript::MugenScriptCommandInputText::EmptyInputString() const
{
	return registerName == "";
}

MugenScriptContainer::string_t MugenScript::MugenScriptCommandInputText::PopInputRegisterName()
{
	MugenScriptContainer::string_t ret = registerName;
	registerName = "";
	return ret;
}

void MugenScript::MugenScriptCommandChoise::Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)
{
	switch (opecode)
	{
	case MugenScript::MSM_REQUEST_INPUT_CHOISE_KEY:
	{
		auto jumpLavel = PopStack();
		cancel.jumpLabel = jumpLavel;
		break;
	}
	case MugenScript::MSM_REQUEST_OUTPUT_CHOISE:
	{
		auto choiseName = PopStack();
		if (!choiseQueue.empty())
			choiseQueue.pop();
		cancel.jumpLabel = "";
		count = 0;
		break;
	}
	case MugenScript::MSM_REQUEST_OUTPUT_CHOISE_DEFINE:
	{
		auto defName = PopStack();
		auto jumpLavel = PopStack();
		ChoiseData data;
		data.choiseName = defName;
		data.jumpLabel = jumpLavel;
		choiseQueue.push(data);
		count++;
		break;
	}
	default:
		break;
	}
}

MugenScript::MugenScriptCommandChoise::ChoiseData MugenScript::MugenScriptCommandChoise::PopChoiseData()
{
	if (choiseQueue.empty())
		return ChoiseData();
	ChoiseData data = choiseQueue.front();
	choiseQueue.pop();
	return data;
}

MugenScript::MugenScriptCommandChoise::ChoiseData MugenScript::MugenScriptCommandChoise::GetCanelData()
{
	return cancel;
}

bool MugenScript::MugenScriptCommandChoise::Empty()
{
	return choiseQueue.empty();
}

int MugenScript::MugenScriptCommandChoise::GetNumChoise()
{
	return count;
}

void MugenScript::MugenScriptTextBox::Update(int speed)
{
	for (int i = 0; i < speed; ++i)
		if (textOutputIndex < text.length())
			textOutputIndex++;
		else
			textOutputIndex = text.length();
}

void MugenScript::MugenScriptTextBox::SetText(MugenScriptContainer::string_t str)
{
	text = str;
}

void MugenScript::MugenScriptTextBox::SetIndexZero()
{
	textOutputIndex = 0;
}

void MugenScript::MugenScriptTextBox::SetIndexMax()
{
	textOutputIndex = text.length();
}

MugenScriptContainer::string_t MugenScript::MugenScriptTextBox::GetText()
{
	MugenScriptContainer::string_t rText = text;
	int strLengh = 0;
	auto charLengh = 0;
	for (int i = 0; i < textOutputIndex && i < text.length(); i += charLengh)
	{
		auto pText=&text.c_str()[i];
		charLengh = MugenScript::GetCharactorLen(pText);
		strLengh += charLengh;
	}
	if (strLengh < text.length())
	{
		rText.resize(strLengh);
		rText += "\0";
	}
	return rText;
}

int MugenScript::MugenScriptTextBox::GetIndex()
{
	return textOutputIndex;
}

int MugenScript::MugenScriptTextBox::GetTextLen()
{
	return text.length();
}

void MugenScript::MugenScriptTextDrawer::Draw(MugenScriptContainer::string_t str)
{
	DrawFormatString(MUGEN_SCRIPT_TEXT_X, MUGEN_SCRIPT_TEXT_Y, GetColor(0, 0, 0), str.c_str());
}

void MugenScript::MugenScriptCommandManager::Update()
{
	SetState();
	switch (state)
	{
	case MugenScript::MugenScriptControlState_Init:
		if (!inputLoadQueue.empty())
		{
			MugenScriptContainer::vector_t<MugenScriptMachineBehavior> behaviors;
			MugenScriptContainer::vector_t<MugenScriptMachineCommandIO*> commands;
			behaviors.push_back(MSM_REQUEST_OUTPUT_CHOISE);
			behaviors.push_back(MSM_REQUEST_OUTPUT_CHOISE_DEFINE);
			behaviors.push_back(MSM_REQUEST_INPUT_CHOISE_KEY);
			behaviors.push_back(MSM_REQUEST_INPUT_TEXT);
			behaviors.push_back(MSM_REQUEST_OUTPUT_PICTURE);
			behaviors.push_back(MSM_REQUEST_OUTPUT_PICTURE_FACIAL);
			behaviors.push_back(MSM_REQUEST_OUTPUT_PICTURE_POS);
			behaviors.push_back(MSM_REQUEST_OUTPUT_PICTURE_VALISH);
			behaviors.push_back(MSM_REQUEST_OUTPUT_SET_BGM);
			behaviors.push_back(MSM_REQUEST_OUTPUT_PLAY_BGM);
			behaviors.push_back(MSM_REQUEST_OUTPUT_PAUSE_BGM);
			behaviors.push_back(MSM_REQUEST_OUTPUT_STOP_BGM);
			behaviors.push_back(MSM_REQUEST_OUTPUT_PLAY_SE);
			behaviors.push_back(MSM_READ);
			behaviors.push_back(MSM_STORE);
			behaviors.push_back(MSM_REQUEST_LOAD_DATABASE);
			behaviors.push_back(MSM_REQUEST_LOAD_TABLE);
			behaviors.push_back(MSM_REQUEST_UNLOAD_DATABASE);
			behaviors.push_back(MSM_REQUEST_ACCESS_TABLE);
			behaviors.push_back(MSM_REQUEST_ACCESS_RELATION);
			behaviors.push_back(MSM_REQUEST_ACCESS_COLUMN);

			commands.push_back(&choiseCommand);
			commands.push_back(&choiseCommand);
			commands.push_back(&choiseCommand);
			commands.push_back(&inputTextCommand);
			commands.push_back(&pictureCommand);
			commands.push_back(&pictureCommand);
			commands.push_back(&pictureCommand);
			commands.push_back(&pictureCommand);
			commands.push_back(&soundCommand);
			commands.push_back(&soundCommand);
			commands.push_back(&soundCommand);
			commands.push_back(&soundCommand);
			commands.push_back(&soundCommand);
			commands.push_back(&databaseCommand);
			commands.push_back(&databaseCommand);
			commands.push_back(&databaseCommand);
			commands.push_back(&databaseCommand);
			commands.push_back(&databaseCommand);
			commands.push_back(&databaseCommand);
			commands.push_back(&databaseCommand);
			commands.push_back(&databaseCommand);

			loader.LoadScript(inputLoadQueue.front(), buffer);
			inputLoadQueue.pop();
			textbox.SetText("");
			textbox.SetIndexZero();

			progSize = loader.GetSizeProg();
			numPage = loader.GetNumPage();
			writer = machine.GetWriter();
			registerIO = machine.GetRegisterIO();
			machine.EndScript();
			machine.Init(behaviors,commands);
			machine.SetPage(0, progSize, buffer.code());
		}
		break;
	case MugenScript::MugenScriptControlState_Update:
	{
		input.Input();
		UpdateMachine();
		InputTextBox();
		UpdateTextBox();
		break;
	}
	case MugenScript::MugenScriptControlState_Choise:
	{
		input.Input();
		UpdateMachine();
		UpdateTextBox(); 
		UpdateChoise();
		break;
	}

	case MugenScript::MugenScriptControlState_Input:
	{
		input.Input();
		UpdateMachine();
		UpdateTextBox();
		UpdateInputText();
		break;
	}
	default:
		break;
	}
	UpdatePicture();
	UpdateSound();
	DrawTextBox();
	if (state == MugenScriptControlState_Choise)
		DrawChoise();
	if (state == MugenScriptControlState_Input)
		DrawInputText();
}

void MugenScript::MugenScriptCommandManager::SetState()
{
	switch (state)
	{
	case MugenScript::MugenScriptControlState_Awake:
		if (!inputLoadQueue.empty())
			state = MugenScriptControlState_Init;
		break;

	case MugenScript::MugenScriptControlState_Init:
		if (inputLoadQueue.empty() && progSize)
			state = MugenScriptControlState_Update;
		break;

	case MugenScript::MugenScriptControlState_Update:
		if (!inputLoadQueue.empty())
			state = MugenScriptControlState_Init;
		if (!choiseList.empty())
			state = MugenScriptControlState_Choise;
		if (!inputTextRegister.empty())
			state = MugenScriptControlState_Input;
		break;

	case MugenScript::MugenScriptControlState_Choise:
		if (choiseList.empty())
			state = MugenScriptControlState_Update;
		break;

	case MugenScriptControlState_Input:
		if (inputTextRegister.empty())
			state = MugenScriptControlState_Update;
		break;

	default:
		break;
	}
}

void MugenScript::MugenScriptCommandManager::PushLoadQueue(MugenScriptContainer::string_t path)
{
	inputLoadQueue.push(path);
}

void MugenScript::MugenScriptCommandManager::StartDebugging()
{
#ifdef MUGEN_SCRIPT_DEBUG

	MugenScriptDxLib::debugger.StartDebugging();

#endif
}

void MugenScript::MugenScriptCommandManager::UpdateDebugging()
{
#ifdef MUGEN_SCRIPT_DEBUG
	MugenScriptDxLib::debugger.UpdateDebugger();
	if (MugenScriptDxLib::debugger.IsRequestLoadScript())
	{
		auto path = MugenScriptDxLib::debugger.GetLoadScriptPath();
		PushLoadQueue(path.C_Str());
	}
	MugenScriptDxLib::debugger.SetDebugValue("machine_pc", machine.GetCurrentPC());
	MugenScriptDxLib::debugger.SetDebugValue("machine_prog_size", progSize);
#endif
}

MugenScript::MugenScriptCommandManager::MugenScriptCommandManager():
	machine(),
	input(),
	textbox(),
	textDrawer(),
	loader(),
	buffer(),
	writer(machine.GetWriter()),
	registerIO(machine.GetRegisterIO()),
	inputTextCommand(machine.GetStack()),
	choiseCommand(machine.GetStack()),
	pictureCommand(machine.GetStack()),
	soundCommand(machine.GetStack()),
	databaseCommand(machine.GetStack(),machine.GetRegisterIO()),
	state(),
	outputText(),
	inputLoadQueue(),
	inputPageRequest(),
	progSize(),
	numPage()
{
	handleUICursor = LoadGraph("image/UI/cursor.png");
	handleUIMessageBox = LoadGraph("image/UI/messageBox.png");
	handleUIselectWindow = LoadGraph("image/UI/selectWindow.png");
}

MugenScript::MugenScriptTextBoxState MugenScript::MugenScriptCommandManager::GetState()
{
	MugenScriptTextBoxState textState;

	int index = textbox.GetIndex();
	int length = textbox.GetTextLen();
	if (index < length)
		textState = MugenScriptTextBoxState_Update;
	else if (!outputText.empty())
		textState = MugenScriptTextBoxState_Next;
	else if (index >= length)
		textState = MugenScriptTextBoxState_Last;
	return textState; 
}

void MugenScript::MugenScriptCommandManager::InputTextBox()
{
	bool nextText = false;
	if (input.CheckDownDecide() || input.CheckDownChancel())
		nextText = true;
	switch (GetState())
	{
	case MugenScript::MugenScriptTextBoxState_Update:
		if (nextText)
			textbox.SetIndexMax();
		break;
	case MugenScript::MugenScriptTextBoxState_Last:
		if (nextText)
		{
			inputPageRequest.push(machine.GetCurrentPage() + 1);
		}
		break;
	default:
		break;
	}
}

void MugenScript::MugenScriptCommandManager::UpdateTextBox()
{

	switch (GetState())
	{
	case MugenScript::MugenScriptTextBoxState_Update:
		textbox.Update(1);

		break;
	case MugenScript::MugenScriptTextBoxState_Last:
		break;

	case MugenScript::MugenScriptTextBoxState_Next:
		if (!outputText.empty())
		{
			textbox.SetText(outputText.front());
			textbox.SetIndexZero();
			outputText.pop();
		}
		break;

	default:
		break;
	}
}

void MugenScript::MugenScriptCommandManager::DrawTextBox()
{
	DrawGraph(0, 0, handleUIMessageBox, TRUE);
	textDrawer.Draw(textbox.GetText());
}

void MugenScript::MugenScriptCommandManager::DrawChoise()
{
	DrawGraph(0, 0, handleUIselectWindow, TRUE);
	for (int i = 0; i < choiseList.size(); ++i)
	{
		MugenScriptSelectorBox::position_t pos = {};
		selectorBox.GetSelectorPosSizeMulNum(i, 0, { MUGEN_SCRIPT_CHOISE_BOX_LEFT,MUGEN_SCRIPT_CHOISE_BOX_TOP }, pos);
		if(i==selectorIndex.GetIndexRow())
			DrawGraph(0, i*MUGEN_SCRIPT_CHOISE_BOX_HEIGHT, handleUICursor, TRUE);
		DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), selector.GetSelectName(i, 0).c_str());
	}
}

void MugenScript::MugenScriptCommandManager::DrawInputText()
{
	inputText.Draw();
}

void MugenScript::MugenScriptCommandManager::UpdateInputText()
{
	if (inputText.IsActive())
	{
		inputText.Update();
	}
	else
	{
		registerIO->SetRegister(inputTextRegister.front(), inputText.GetStr());
		inputTextRegister.pop();
		inputPageRequest.push(machine.GetCurrentPage() + 1);
	}
}

void MugenScript::MugenScriptCommandManager::UpdateChoise()
{
	if (input.CheckDownUpKey())
		selectorIndex.DecrementRow();
	else if (input.CheckDownDownKey())
		selectorIndex.IncrementRow();
	else if (input.CheckDownDecide())
	{
		auto idx = selector.GetSelectValue(selectorIndex.GetIndexRow(), selectorIndex.GetIndexColumn());
		inputJumpLabelRequest.push(choiseList[idx].jumpLabel.value.str);
		choiseList.clear();
	}
	else if (input.CheckDownChancel())
	{
		inputJumpLabelRequest.push(choiseCommand.GetCanelData().jumpLabel.value.str);
		choiseList.clear();
	}

}

void MugenScript::MugenScriptCommandManager::UpdatePicture()
{
	while (!pictureCommand.Empty())
	{
		auto data = pictureCommand.PopPictureData();
		switch (data.pos)
		{
		case MugenScriptPicturePos_None:
			pictureList.erase(data.handle);
			break;

		case MugenScriptPicturePos_Left:

			pictureList[data.pos] = data.handle;
			break;

		case MugenScriptPicturePos_Right:
			pictureList[data.pos] = data.handle;
			break;

		case MugenScriptPicturePos_Center:
			pictureList[data.pos] = data.handle;
			break;

		case MugenScriptPicturePos_Back:
			pictureList[data.pos] = data.handle;
			break;

		default:
			break;
		}
	}

	for (int i = 0;i < MugenScriptPicturePos_NumPos; ++i)
	{

		auto handle = pictureList[i];
		switch (i)
		{
		case MugenScriptPicturePos_None:
			break;

		case MugenScriptPicturePos_Left:
			DrawGraph(MUGEN_SCRIPT_PICTURE_POS_LEFT, MUGEN_SCRIPT_PICTURE_POS_Y, handle,TRUE);
			break;

		case MugenScriptPicturePos_Right:
			DrawGraph(MUGEN_SCRIPT_PICTURE_POS_RIGHT, MUGEN_SCRIPT_PICTURE_POS_Y, handle, TRUE);
			break;

		case MugenScriptPicturePos_Center:
			DrawGraph(MUGEN_SCRIPT_PICTURE_POS_CENTER, MUGEN_SCRIPT_PICTURE_POS_Y, handle, TRUE);
			break;

		case MugenScriptPicturePos_Back:
			DrawGraph(MUGEN_SCRIPT_BACKGROUND_X, MUGEN_SCRIPT_BACKGROUND_Y, handle, TRUE);
			break;

		default:
			break;
		}
	}
}

void MugenScript::MugenScriptCommandManager::UpdateSound()
{
	if (!soundCommand.Empty())
	{
		auto request = soundCommand.PopRequest();
		switch (request)
		{
		case MugenScript::MugenScriptSoundRequest_Play:
			PlaySoundMem(soundCommand.GetHandle(), DX_PLAYTYPE_BACK);
			break;
		case MugenScript::MugenScriptSoundRequest_PlayLoop:
			PlaySoundMem(soundCommand.GetHandle(), DX_PLAYTYPE_LOOP);
			break;
		case MugenScript::MugenScriptSoundRequest_Pause:
			StopSoundMem(soundCommand.GetHandle());
			break;
		case MugenScript::MugenScriptSoundRequest_Stop:
			StopSoundMem(soundCommand.GetHandle());
			SetSoundCurrentTime(0, soundCommand.GetHandle());
			break;
		default:
			break;
		}
	}
}

void MugenScript::MugenScriptCommandManager::UpdateMachine()
{
	if (!inputPageRequest.empty())
	{
		machine.SetPage(inputPageRequest.front(), progSize, buffer.code());
		inputPageRequest.pop();
	}

	if (!inputJumpLabelRequest.empty())
	{
		machine.SetLavel(inputJumpLabelRequest.front(), progSize, buffer.code());
		inputJumpLabelRequest.pop();
	}

	machine.Read(buffer.code(), progSize);
	MugenScriptContainer::string_t outStr;
	if (!writer->Empty())
	{
		while (!writer->Empty())
		{
			outStr += writer->PopString();
		}
		outputText.push(outStr);
	}

	if (!choiseCommand.Empty())
	{
		while (!choiseCommand.Empty())
		{
			choiseList.push_back(choiseCommand.PopChoiseData());
		}
		selector.Init(choiseList.size(), 1);
		selectorIndex.Init(choiseList.size(), 1);
		selectorBox.SetSelectorPos(choiseList.size(), 1, MUGEN_SCRIPT_CHOISE_BOX_HEIGHT, MUGEN_SCRIPT_CHOISE_BOX_WIDTH);
		for (int i = 0; i < choiseList.size(); ++i)
			selector.SetSelect(i, 0, choiseList[i].choiseName.value.str, i);
	}

	if (!inputTextCommand.EmptyInputString())
	{
		inputTextRegister.push(inputTextCommand.PopInputRegisterName());
		inputText.Active();
	}

	if (machine.GetCurrentPage() == numPage)
		machine.EndScript();
}

void MugenScript::MugenScriptMachineInput::Input()
{
	auto& key = MugenScriptDxLibKeyInput::instance();
	key.Key_Update();
}

bool MugenScript::MugenScriptMachineInput::CheckDownDecide() const
{
	auto& key = MugenScriptDxLibKeyInput::instance();
	return key.InputKeyDecide() == 1;
}

bool MugenScript::MugenScriptMachineInput::CheckDownChancel() const
{
	auto& key = MugenScriptDxLibKeyInput::instance();
	return key.InputKeyCancel() == 1;
}

bool MugenScript::MugenScriptMachineInput::CheckDownEnter() const
{
	auto& key = MugenScriptDxLibKeyInput::instance();
	return key.InputKeyEnter() == 1;
}

bool MugenScript::MugenScriptMachineInput::CheckDownUpKey() const
{
	auto& key = MugenScriptDxLibKeyInput::instance();
	return key.InputKeyUp() == 1;
}

bool MugenScript::MugenScriptMachineInput::CheckDownDownKey() const
{
	auto& key = MugenScriptDxLibKeyInput::instance();
	return key.InputKeyDown() == 1;
}

MugenScript::MugenScriptCode* MugenScript::MugenScriptCodeBuffer::code() const
{
	return codePtr;
}

int MugenScript::MugenScriptCodeBuffer::size() const
{
	return capacity;
}

void MugenScript::MugenScriptCodeBuffer::clear()
{
	for (int i = 0; i < capacity; ++i)
		codePtr[i] = { MSM_NONE,0 };
}

void MugenScript::MugenScriptCodeBuffer::set(int capacity, MugenScriptCode* code)
{
	this->capacity = capacity;
	this->codePtr = code;
}

void MugenScript::MugenScriptMachineLoader::LoadScript(MugenScriptContainer::string_t path, MugenScriptCodeBuffer& buffer)
{
	MugenScript::MugenScriptConfigration& config = MugenScriptConfigration::instance();
	MugenScript::MugenScriptTokenizer tokenizer;
	MugenScript::MugenScriptParser parser;
	MugenScript::MugenScriptGeneratorEx generator;
	std::ifstream file(path);
	MugenScriptContainer::string_t codeStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	if (file)
	{
		auto& configData = config.GetKeywordData();
		auto token = tokenizer.Tokenize(configData.size(), configData.data(), codeStr.length(), codeStr.c_str());
		auto tree = parser.Parse(configData.size(), configData.data(), token);
		generator.Genrate(configData.size(), configData.data(), buffer.code(), tree);
		numPage = generator.GetNumPage();
		sizeProg= generator.GetProgSize();
	}
}

int MugenScript::MugenScriptMachineLoader::GetNumPage() const
{
	return numPage;
}

int MugenScript::MugenScriptMachineLoader::GetSizeProg() const
{
	return sizeProg;
}

void MugenScript::MugenScriptInputText::Update()
{
	auto& key = MugenScript::MugenScriptDxLibKeyInput::instance();
	if (key.InputKeyEnter() == 1 && CheckKeyInput(inputKeyHandle))
	{
		if (strcmp(buffer, "") != 0)
		{
			DeleteKeyInput(inputKeyHandle);
			inputKeyHandle = 0;
		}
	}
	if (inputKeyHandle)
	{
		SetActiveKeyInput(inputKeyHandle);
		GetKeyInputString(buffer, inputKeyHandle);
	}

}

void MugenScript::MugenScriptInputText::Draw()const
{
	DrawKeyInputString(MUGEN_SCRIPT_KEYINPUT_LEFT, MUGEN_SCRIPT_KEYINPUT_TOP, inputKeyHandle);
}

void MugenScript::MugenScriptInputText::Active()
{
	ZeroMemory(buffer, sizeof(buffer));
	if (inputKeyHandle)
		DeleteKeyInput(inputKeyHandle);
	inputKeyHandle = MakeKeyInput(16, FALSE, FALSE, FALSE);
	SetActiveKeyInput(inputKeyHandle);
}

bool MugenScript::MugenScriptInputText::IsActive()
{
	return inputKeyHandle;
}

char* MugenScript::MugenScriptInputText::GetStr()
{
	return buffer;
}

void MugenScript::MugenScriptCommandPicture::Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)
{
	switch (opecode)
	{
	case MugenScript::MSM_REQUEST_OUTPUT_PICTURE:
	{
		auto picture = MugenScriptPictureLoader::instance();
		PictureData data;
		data.handle = picture.GetPicture(PopStack().value.str, facial);
		data.pos = pos;
		pos = MugenScriptPicturePos_None;
		facial = MugenScriptPictureFacial_None;
		pictureQueue.push(data);
		break;
	}
	case MugenScript::MSM_REQUEST_OUTPUT_PICTURE_FACIAL:
		facial = GetFacial(PopStack().value.str);
		break;
	case MugenScript::MSM_REQUEST_OUTPUT_PICTURE_VALISH:
		pos = MugenScriptPicturePos_None;
		break;
	case MugenScript::MSM_REQUEST_OUTPUT_PICTURE_POS:
		pos = GetPos(PopStack().value.str);
		break;
	default:
		break;
	}
}

bool MugenScript::MugenScriptCommandPicture::Empty()
{
	return pictureQueue.empty();
}

MugenScript::MugenScriptCommandPicture::PictureData MugenScript::MugenScriptCommandPicture::PopPictureData()
{
	PictureData data=pictureQueue.front();
	pictureQueue.pop();
	return data;
}

MugenScript::MugenScriptPictureFacial MugenScript::MugenScriptCommandPicture::GetFacial(const char* str)
{
	MugenScriptContainer::string_t cmpStr = str;
	if (cmpStr == "fun")
		return MugenScriptPictureFacial_Fun;
	else if (cmpStr == "angry")
		return MugenScriptPictureFacial_Angry;
	else if (cmpStr == "sad")
		return MugenScriptPictureFacial_Sad;
	else if (cmpStr == "happy")
		return MugenScriptPictureFacial_Happy;
	else if (cmpStr == "shock")
		return MugenScriptPictureFacial_Shock;
	else
		return MugenScriptPictureFacial_None;
}

MugenScript::MugenScriptPicturePos MugenScript::MugenScriptCommandPicture::GetPos(const char* str)
{
	MugenScriptContainer::string_t cmpStr = str;
	if (cmpStr == "L")
		return MugenScriptPicturePos_Left;
	else if (cmpStr == "R")
		return MugenScriptPicturePos_Right;
	else if (cmpStr == "C")
		return MugenScriptPicturePos_Center;
	else if (cmpStr == "back")
		return MugenScriptPicturePos_Back;
	else
		return MugenScriptPicturePos_None;

}

MugenScript::MugenScriptPictureLoader& MugenScript::MugenScriptPictureLoader::instance()
{
	static MugenScriptPictureLoader loader;
	return loader;
}

int MugenScript::MugenScriptPictureLoader::GetPicture(MugenScriptContainer::string_t name, MugenScriptPictureFacial facial)
{
	return pictureMap[name][facial];
}

MugenScript::MugenScriptPictureLoader::MugenScriptPictureLoader()
{

	int handleBack = LoadGraph("image/back/TERA.png");
	int handleBack2 = LoadGraph("image/back/SAKE.png");
	pictureMap["TERA"][0] = handleBack;
	pictureMap["SAKE"][0] = handleBack2;
}

void MugenScript::MugenScriptSoundLoader::GetSoundData(MugenScriptContainer::string_t fileName, int& handle, int& loopSample)
{
	auto sound = soundMap[fileName];
	handle = sound.handle;
	loopSample = sound.loopSample;
}

MugenScript::MugenScriptSoundLoader& MugenScript::MugenScriptSoundLoader::instance()
{
	static MugenScriptSoundLoader loader;
	return loader;
}

MugenScript::MugenScriptSoundLoader::MugenScriptSoundLoader()
{
	MugenScriptContainer::string_t dir = "BGM/";
	MugenScriptContainer::string_t file = "‚ ‚Ì‘‚Í¡‚à’¾‚ñ‚Å‚¢‚é‚©.ogg";
	MugenScriptContainer::string_t path = dir + file;

	auto handle = LoadSoundMem(path.c_str());
	ChangeVolumeSoundMem(100, handle); 
	soundMap[file] = { handle,0 };
}

void MugenScript::MugenScriptCommandSound::Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)
{
	auto& loader = MugenScriptSoundLoader::instance();
	switch (opecode)
	{
	case MugenScript::MSM_REQUEST_OUTPUT_SOUND:
		break;
	case MugenScript::MSM_REQUEST_OUTPUT_SET_BGM:
		loader.GetSoundData(PopStack().value.str, handle, loopSample);
		break;
	case MugenScript::MSM_REQUEST_OUTPUT_PLAY_BGM:
		requestQueue.push(MugenScriptSoundRequest_PlayLoop);
		break;
	case MugenScript::MSM_REQUEST_OUTPUT_PAUSE_BGM:
		requestQueue.push(MugenScriptSoundRequest_Pause);
		break;
	case MugenScript::MSM_REQUEST_OUTPUT_STOP_BGM:
		requestQueue.push(MugenScriptSoundRequest_Stop);
		break;
	case MugenScript::MSM_REQUEST_OUTPUT_PLAY_SE:
		requestQueue.push(MugenScriptSoundRequest_Play);
		break;
	default:
		break;
	}
}

bool MugenScript::MugenScriptCommandSound::Empty()
{
	return requestQueue.empty();
}

MugenScript::MugenScriptSoundRequest MugenScript::MugenScriptCommandSound::PopRequest()
{
	auto ret = requestQueue.front();
	requestQueue.pop();
	return ret;
}

int MugenScript::MugenScriptCommandSound::GetHandle() const
{
	return handle;
}

int MugenScript::MugenScriptCommandSound::GetLoopSample() const
{
	return loopSample;
}

void MugenScript::MugenScriptCommandDatabase::Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)
{
	switch (opecode)
	{
	case MugenScript::MSM_READ:
	{

		if (!accessDB)
		{
			registerIO->Execute(opecode, operand);
			return;
		}
		MugenScriptDatabaseValue value;
		value = db.GetValue();
		MugenScriptOperand p;
		switch (value.type)
		{
		case DATABASE_VALUE_TYPE_INT:
			p = value.value.ivalue;
			break;

		case DATABASE_VALUE_TYPE_DBL:
			p = value.value.dvalue;
			break;

		case DATABASE_VALUE_TYPE_STR:
			p = value.value.string;
			break;

		default:
			break;
		}
		PushStack(p);
		accessDB = false;
		break;
	}
	case MugenScript::MSM_STORE:
	{
		if (!accessDB)
		{
			registerIO->Execute(opecode, operand);
			return;
		}
		auto p = PopStack();
		MugenScriptDatabaseValue v;
		switch (p.tag)
		{

		case MSM_TAG_INT:
			v = p.value.ivalue;
			break;
		case MSM_TAG_DBL:
			v = p.value.dvalue;
			break;
		case MSM_TAG_STRING:
			v = p.value.str;
			assert(false);
			break;
		default:
			break;
		}
		db.SetValue(v);
		db.WriteRecord();
		accessDB = false;
		break;
	}
	case MugenScript::MSM_REQUEST_LOAD_DATABASE:
	{
		Mugenshuen::string_t dbName = PopStack().value.str;
		db.SetDatabase(dbName);
		break;
	}
	case MugenScript::MSM_REQUEST_LOAD_TABLE:
	{
		Mugenshuen::string_t tblName = PopStack().value.str;
		db.SetTable(tblName);
		break;
	}

	case MugenScript::MSM_REQUEST_UNLOAD_DATABASE:
	{
		db.Clear();
		break;
	}

	case MugenScript::MSM_REQUEST_ACCESS_TABLE:
	{
		Mugenshuen::string_t column = PopStack().value.str;
		Mugenshuen::string_t record = PopStack().value.str;
		db.SeekRecord(column, record.C_Str());
		accessDB = true;
		break;
	}
	case MugenScript::MSM_REQUEST_ACCESS_RELATION:
	{
		Mugenshuen::string_t relation = PopStack().value.str;
		db.SeekRelation(relation, db.GetValue());
		break;
	}
	case MugenScript::MSM_REQUEST_ACCESS_COLUMN:
		db.SetColumn(PopStack().value.str);
		break;
	default:
		break;
	}
}

void MugenScript::MugenScriptCommandDatabase::EndScript()
{
	db.Clear();
}

MugenScript::MugenScriptCommandDatabase::MugenScriptCommandDatabase(MugenScriptContainer::stack_t<MugenScript::MugenScriptMachineEx::StackType>*stack, MugenScriptCommandRegisterIO* io):
	MugenScriptMachineCommandIO(stack),
	registerIO(io)
{
}

void MugenScript::MugenScriptCommandToDatabaseIO::Open(const Mugenshuen::string_t database)
{
	auto path = database + ".mdb";
	file.open(path);
}

void MugenScript::MugenScriptCommandToDatabaseIO::Close(const Mugenshuen::string_t database)
{
	file.close();
}

void MugenScript::MugenScriptCommandToDatabaseIO::SetDatabase(const Mugenshuen::string_t database)
{
	auto path = database + ".mdb";
	MugenScriptDatabaseReader reader;
	if (file.is_loaded())
		file.close();
	file.open(path);
	file.begin();
	reader.ReadDatabaseMap(map, file);
	//editor.LoadDatabase(database);
}

void MugenScript::MugenScriptCommandToDatabaseIO::SetTable(const Mugenshuen::string_t table)
{
	int keyIndex = 0;
	MugenScriptDatabaseTableMapData data;
	MugenScriptDatabaseReader reader;
	MugenScriptDatabaseTableProp prop;
	data.name = table;
	auto n = map.find(keyIndex, data);
	if (!n)
		return;
	reader.SeekTableStart(n->keys[keyIndex].pos,file);
	if (this->table)
		delete this->table;
	this->table = new MugenScriptDatabaseTableEx;
	this->table->Load(file);
	this->table->CopyColumn(column);
	this->table->CopyIndex(index);
	tableName = table;
	tablePos = n->keys[keyIndex].pos;
	writeRecord.UpdateColumnData();
	//this->table = editor.LoadTable(table);
}

void MugenScript::MugenScriptCommandToDatabaseIO::Clear()
{
	//editor.CloseDatabsae(true);
	if (table)
		delete table;
	table = nullptr;
	tableName = "";
	recordID = -1;
	columnID = -1;
	relationColumnID = -1;
	relationRecordID = -1;
	relationRecordIDValue = -1;
	relation = nullptr;
	column.Clear();
	index.Clear();
	file.close();
}

void MugenScript::MugenScriptCommandToDatabaseIO::SetColumn(const Mugenshuen::string_t column)
{
	if (!table)
		return;
	columnID = table->FindColumn(column);
	if (columnID == -1)
	{
		Mugenshuen::string_t message = "no column exist : ";
		MessageDatabaseIO(message + column + " ,table : " + table->Name());
	}

	auto type = table->TypesColumn()[columnID];
	if (type == DATABASE_VALUE_TYPE_EX_REL)
		relation = table->GetRelation(columnID);
	else
		relation = nullptr;

}

void MugenScript::MugenScriptCommandToDatabaseIO::SeekRecord(const Mugenshuen::string_t column, const MugenScriptDatabaseValue id)
{
	if (!table)
	{
		MessageDatabaseIO("table is not loaded");
		recordID = -1;
		return;
	}
	MugenScriptDatabaseReader reader;
	record.resize(this->table->NumColumn());
	table->CreateIndex(column);
	table->ReadIndex(column, id, 1, &recordID);
	reader.ReadTableRecord(tablePos, recordID, index, this->column, record.data(), file);
}

void MugenScript::MugenScriptCommandToDatabaseIO::SeekRelation(const Mugenshuen::string_t column, const MugenScriptDatabaseValue id)
{
	if (!relation)
	{
		MessageDatabaseIO("relation no exist");
		return;
	}

	relationColumnID = relation->relationTableColumn.Find(column);
	relationRecordIDValue = id;
	if (recordID!=-1&&relationColumnID != -1 && relation)
	{
		table->Read(recordID, record.data());
		auto relationRecord = relation->GetRelation(relationRecordID,record[columnID]);
		record.resize(relation->relationTableColumn.GetNumColumn());
		for (int i = 0; i < record.size(); ++i)
			record[i] = relationRecord[i];
		columnID = relationColumnID;
	}
	else
	{
		if (relationColumnID == -1)
		{
			Mugenshuen::string_t message = "relation column no exist : ";
			MessageDatabaseIO(message + column);
		}

		recordID = -1;
		relationRecordID = -1;
	}
} 

const MugenScript::MugenScriptDatabaseValue MugenScript::MugenScriptCommandToDatabaseIO::GetValue() const
{
	if (columnID != -1 && recordID != -1)
		return record.data()[columnID];
	return MugenScriptDatabaseValue(DATABASE_VALUE_TYPE_INVALID);
}

void MugenScript::MugenScriptCommandToDatabaseIO::SetValue(const MugenScriptDatabaseValue value)
{
	if(columnID!=-1)
		record.data()[columnID] = value;
}

void MugenScript::MugenScriptCommandToDatabaseIO::WriteRecord()
{
	if (!relation)
	{
		int keyIndex = 0;
		MugenScriptDatabaseTableMapData mapData;
		MugenScriptDatabaseWriter writer;
		mapData.name = tableName;
		auto n = map.find(keyIndex,mapData);
		if (!n && (columnID != -1 || recordID != -1))
			return;
		table->MugenScriptDatabaseTable::Read(recordID,writeRecord.Get());
		writeRecord.Get()[columnID] = record[columnID];
		table->MugenScriptDatabaseTable::Replace(recordID, writeRecord.Get());
		writer.WriteRecord(n->keys[keyIndex].pos, recordID, index, writeRecord, file);
	}
	else
		relation->SetRelation(relationRecordID, record.data());
}

MugenScript::MugenScriptCommandToDatabaseIO::MugenScriptCommandToDatabaseIO() :
	tableName(),
	recordID(),
	columnID(),
	relationColumnID(),
	relationRecordID(),
	relationRecordIDValue(),
	file(),
	map(),
	table(),
	relation(),
	record(),
	column(0, 0, 0, 0),
	index(),
	writeRecord(&column)
{
}

void MugenScript::MugenScriptCommandToDatabaseIO::MessageDatabaseIO(Mugenshuen::string_t message)
{
	MessageBox(nullptr, message.C_Str(), "database io message", MB_OK);
}
