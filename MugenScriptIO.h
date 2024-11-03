#pragma once
#include "MugenScript.h"
#include "MugenScriptDatabase.h"
#include <DxLib.h>

#define MUGEN_SCRIPT_TEXT_X 30
#define MUGEN_SCRIPT_TEXT_Y 670
#define MUGEN_SCRIPT_CHOISE_BOX_LEFT 400
#define MUGEN_SCRIPT_CHOISE_BOX_TOP 380
#define MUGEN_SCRIPT_CHOISE_BOX_HEIGHT 60
#define MUGEN_SCRIPT_CHOISE_BOX_WIDTH 120
#define MUGEN_SCRIPT_KEYINPUT_LEFT  500
#define MUGEN_SCRIPT_KEYINPUT_TOP 500
#define MUGEN_SCRIPT_PICTURE_POS_RIGHT 1000
#define MUGEN_SCRIPT_PICTURE_POS_Y 600
#define MUGEN_SCRIPT_PICTURE_POS_LEFT 150
#define MUGEN_SCRIPT_PICTURE_POS_CENTER 550
#define MUGEN_SCRIPT_BACKGROUND_X 0
#define MUGEN_SCRIPT_BACKGROUND_Y 0

namespace MugenScript
{
	enum MugenScriptControlState
	{
		MugenScriptControlState_Awake,
		MugenScriptControlState_Init,
		MugenScriptControlState_Update,
		MugenScriptControlState_Choise,
		MugenScriptControlState_Input,
	};

	enum MugenScriptTextBoxState
	{
		MugenScriptTextBoxState_Update,
		MugenScriptTextBoxState_Last,
		MugenScriptTextBoxState_Next
	};

	enum MugenScriptPictureFacial
	{
		MugenScriptPictureFacial_Fun,
		MugenScriptPictureFacial_Angry,
		MugenScriptPictureFacial_Sad,
		MugenScriptPictureFacial_Happy,
		MugenScriptPictureFacial_Shock,
		MugenScriptPictureFacial_NumFacial,
		MugenScriptPictureFacial_None,
	};

	enum MugenScriptPicturePos
	{
		MugenScriptPicturePos_None,
		MugenScriptPicturePos_Left,
		MugenScriptPicturePos_Right,
		MugenScriptPicturePos_Center,
		MugenScriptPicturePos_Back,
		MugenScriptPicturePos_NumPos
	};

	enum MugenScriptSoundRequest
	{
		MugenScriptSoundRequest_Play,
		MugenScriptSoundRequest_PlayLoop,
		MugenScriptSoundRequest_Pause,
		MugenScriptSoundRequest_Stop
	};

	class MugenScriptDxLibKeyInput
	{
	public:

		int InputKeyDecide();
		int InputKeyCancel();
		int InputKeyMenu();
		int InputKeyRight();
		int InputKeyLeft();
		int InputKeyUp();
		int InputKeyDown();
		int InputKeyEnter();
		void Key_Update();
		static MugenScriptDxLibKeyInput& instance();

	private:

		int Key_Get(int KeyCode);
		int mKey[256];
	};

	class MugenScriptSelector
	{
	public:

		void Init(size_type numRow, size_type numColumn);
		void SetSelect(size_type row, size_type column, MugenScriptContainer::string_t name, int returnValue);
		MugenScriptContainer::string_t GetSelectName(size_type row, size_type column);
		int GetSelectValue(size_type row, size_type column);


	private:

		size_type row;
		size_type column;
		MugenScriptContainer::array_t<MugenScriptContainer::array_t<MugenScriptContainer::string_t>> selector;
		MugenScriptContainer::array_t<MugenScriptContainer::array_t<int>> value;
	};

	class MugenScriptSelectorBox
	{
	public:
		using position_t = MugenScriptContainer::Vector2;

		void SetSelectorPos(size_type numRow, size_type numColumn, size_type sizeRow, size_type sizeColumn);
		void GetSelectorPosSizeDivNum(size_type row, size_type column, const position_t base, position_t& pos);
		void GetSelectorPosSizeMulNum(size_type row, size_type column, const position_t base, position_t& pos);

	private:

		size_type numRow;
		size_type numColumn;
		size_type sizeRow;
		size_type sizeColumn;
	};

	class MugenScriptSelectorIndex
	{
	public:

		void Init(size_type numRow, size_type numColumn);
		void IncrementRow();
		void DecrementRow();
		void IncrementColumn();
		void DecrementColumn();
		int GetIndexRow();
		int GetIndexColumn();
		void SetIndex(int value);

	private:
		size_type numRow;
		size_type numColumn;
		int indexRow;
		int indexColumn;
	};

	class MugenScriptInputText
	{
	public:

		void Update();
		void Draw()const;
		void Active();
		bool IsActive();
		char* GetStr();
	private:
		int inputKeyHandle;
		char buffer[16];
	};

	class MugenScriptCodeBuffer
	{
	public:

		MugenScriptCode* code()const;
		int size()const;
		void clear();

	protected:
		void set(int capacity, MugenScriptCode* code);

	private:
		MugenScriptCode* codePtr;
		int capacity;
	};

	template<int buffSize>
	class MugenScriptCodeBufferStatic :public MugenScriptCodeBuffer
	{
	public:
		MugenScriptCodeBufferStatic() { set(buffSize, codeBuffer); };
	private:
		MugenScriptCode codeBuffer[buffSize];
	};


	class MugenScriptTextBox
	{
	public:
		void Update(int speed);
		void SetIndexZero();
		void SetIndexMax();
		void SetText(MugenScriptContainer::string_t);
		MugenScriptContainer::string_t GetText();
		int GetIndex();
		int GetTextLen();
	private:

		MugenScriptContainer::string_t text;
		int textOutputIndex;
	};

	class MugenScriptTextDrawer
	{
	public:
		void Draw(MugenScriptContainer::string_t str);
	};

	class MugenScriptMachineInput
	{
	public:
		void Input();
		bool CheckDownDecide()const;
		bool CheckDownChancel()const;
		bool CheckDownEnter()const;
		bool CheckDownUpKey()const;
		bool CheckDownDownKey()const;
	private:
	};

	class MugenScriptMachineLoader
	{
	public:

		void LoadScript(MugenScriptContainer::string_t path, MugenScriptCodeBuffer& buffer);
		int GetNumPage() const;
		int GetSizeProg() const;
	private:
		int numPage;
		int sizeProg;
	};


	class MugenScriptCommandInputText :public MugenScriptMachineCommandIO
	{
	public:
		void Init();
		void Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)override;
		bool IsActive()const;
		bool EmptyInputString()const;
		MugenScriptContainer::string_t PopInputRegisterName();
		MugenScriptCommandInputText(MugenScriptContainer::stack_t<MugenScriptOperand>* stack) :MugenScriptMachineCommandIO(stack), inputKeyHandle(), buffer() {};
	private:

		int inputKeyHandle;
		char buffer[16];
		MugenScriptContainer::string_t registerName;
	};

	class MugenScriptCommandChoise :public MugenScriptMachineCommandIO
	{
	public:
		struct ChoiseData
		{
			MugenScriptOperand choiseName;
			MugenScriptOperand jumpLabel;
		};

		void Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)override;
		ChoiseData PopChoiseData();
		ChoiseData GetCanelData();
		bool Empty();
		int GetNumChoise();
		MugenScriptCommandChoise(MugenScriptContainer::stack_t<MugenScriptOperand>* stack) :MugenScriptMachineCommandIO(stack), count() {};
	private:
		int count;
		MugenScriptContainer::queue_t<ChoiseData> choiseQueue;
		ChoiseData cancel;
	};

	class MugenScriptPictureLoader
	{
	public:
		static MugenScriptPictureLoader& instance();
		int GetPicture(MugenScriptContainer::string_t name, MugenScriptPictureFacial facial);

	private:
		MugenScriptPictureLoader();
		MugenScriptContainer::map_t<MugenScriptContainer::string_t, int[MugenScriptPictureFacial_NumFacial]> pictureMap;
	};

	class MugenScriptSoundLoader
	{
	public:
		struct SoundData
		{
			int handle;
			int loopSample;
		};
		void GetSoundData(MugenScriptContainer::string_t fileName, int& handle, int& loopSample);
		static MugenScriptSoundLoader& instance();
	private:
		MugenScriptSoundLoader();
		MugenScriptContainer::map_t<MugenScriptContainer::string_t, SoundData> soundMap;
	};

	class MugenScriptCommandPicture :public MugenScriptMachineCommandIO
	{
	public:
		struct PictureData
		{
			MugenScriptPicturePos pos;
			int handle;
		};

		void Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)override;
		bool Empty();
		PictureData PopPictureData();
		MugenScriptCommandPicture(MugenScriptContainer::stack_t<MugenScriptOperand>* stack) :MugenScriptMachineCommandIO(stack), facial(), pos(), pictureQueue() {};

	private:
		MugenScriptPictureFacial GetFacial(const char* str);
		MugenScriptPicturePos GetPos(const char*);
		MugenScriptPictureFacial facial;
		MugenScriptPicturePos pos;
		MugenScriptContainer::queue_t<PictureData> pictureQueue;
	};

	class MugenScriptCommandSound :public MugenScriptMachineCommandIO
	{
	public:
		void Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)override;
		bool Empty();
		MugenScriptSoundRequest PopRequest();
		int GetHandle() const;
		int GetLoopSample()const;
		MugenScriptCommandSound(MugenScriptContainer::stack_t<MugenScriptOperand>* stack) :MugenScriptMachineCommandIO(stack), handle(), loopSample() {}
	private:
		int handle;
		int loopSample;
		MugenScriptContainer::queue_t<MugenScriptSoundRequest> requestQueue;
	};

	class MugenScriptCommandToDatabaseIO 
	{
	public:
		void Open(const Mugenshuen::string_t database);
		void Close(const Mugenshuen::string_t database);
		void SetDatabase(const Mugenshuen::string_t database);
		void SetTable(const Mugenshuen::string_t table);
		void Clear();
		void SetColumn(const Mugenshuen::string_t column);
		void SeekRecord(const Mugenshuen::string_t column, const MugenScriptDatabaseValue id);
		void SeekRelation(const Mugenshuen::string_t column, const MugenScriptDatabaseValue id);

		const MugenScriptDatabaseValue GetValue()const;
		void SetValue(const MugenScriptDatabaseValue);
		void WriteRecord();

		MugenScriptCommandToDatabaseIO();
	private:
		void MessageDatabaseIO(Mugenshuen::string_t message);
		Mugenshuen::string_t tableName;
		int recordID;
		int columnID;
		int relationColumnID;
		int relationRecordID;
		int tablePos;

		MugenScriptDatabaseValue relationRecordIDValue;
		MugenScriptDatabaseFile file;
		Mugenshuen::btree_t<MugenScriptDatabaseTableMapData> map;
		//MugenScriptDatabaseEditor editor;
		MugenScriptDatabaseTableEx* table;
		MugenScriptDatabaseTableRelationEx::RelationData* relation;
		Mugenshuen::vector_t<MugenScriptDatabaseValue> record;
		MugenScriptDatabaseColumn column;
		MugenScriptDatabaseIndex index;
		MugenScriptDatabaseRecord writeRecord;
	};

	class MugenScriptCommandDatabase :public MugenScriptMachineCommandIO
	{
	public:
		void Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)override;
		void EndScript()override;
		MugenScriptCommandDatabase(MugenScriptContainer::stack_t<MugenScript::MugenScriptMachineEx::StackType>*, MugenScriptCommandRegisterIO* io);
	private:
		bool accessDB;
		MugenScriptCommandRegisterIO* registerIO;
		MugenScriptCommandToDatabaseIO db;

	};

	class MugenScriptCommandManager
	{
	public:

		void Update();
		void SetState();
		void PushLoadQueue(MugenScriptContainer::string_t path);
		void StartDebugging();
		void UpdateDebugging();
		MugenScriptCommandManager();
	private:
		MugenScriptTextBoxState GetState();
		void UpdateMachine();
		void InputTextBox();
		void UpdateTextBox();
		void UpdateInputText();
		void UpdateChoise();
		void UpdatePicture();
		void UpdateSound();

		void DrawTextBox();
		void DrawChoise();
		void DrawInputText();

		MugenScriptMachineEx machine;
		MugenScriptMachineInput input;
		MugenScriptTextBox textbox;
		MugenScriptTextDrawer textDrawer;
		MugenScriptInputText inputText;
		MugenScriptMachineLoader loader;
		MugenScriptCodeBufferStatic<1000> buffer;

		MugenScriptCommandWriter* writer;
		MugenScriptCommandRegisterIO* registerIO;
		MugenScriptCommandDatabase databaseCommand;
		MugenScriptCommandInputText inputTextCommand;
		MugenScriptCommandChoise choiseCommand;
		MugenScriptCommandPicture pictureCommand;
		MugenScriptCommandSound soundCommand;
		MugenScriptControlState state;
		MugenScriptSelector selector;
		MugenScriptSelectorBox selectorBox;
		MugenScriptSelectorIndex selectorIndex;
		MugenScriptContainer::queue_t<MugenScriptContainer::string_t> outputText;
		MugenScriptContainer::queue_t<MugenScriptContainer::string_t> inputLoadQueue;
		MugenScriptContainer::queue_t<MugenScriptContainer::string_t> inputTextRegister;
		MugenScriptContainer::queue_t<MugenScriptContainer::string_t> inputJumpLabelRequest;
		MugenScriptContainer::vector_t<MugenScriptCommandChoise::ChoiseData> choiseList;
		MugenScriptContainer::map_t<int, int> pictureList;

		MugenScriptContainer::queue_t<int> inputPageRequest;
		int progSize;
		int numPage;

		int handleUICursor;
		int handleUIMessageBox;
		int handleUIselectWindow;
	};
}