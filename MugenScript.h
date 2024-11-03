#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>
#include "common/Container.h"

#define MUGEN_SCRIPT_MAX_NUM_OPERATOR 16
#define MUGEN_SCRIPT_MAX_NUM_KEYWORD 16
#define MUGEN_SCRIPT_DATABASE_MAX_LEN_TABLE_NAME 56
#define MUGEN_SCRIPT_DATABASE_MAX_DATA_SIZE_BYTE_FOR_MEM (1<<20)


namespace MugenScriptContainer
{
	template<class T>
	using vector_t = std::vector<T>;
	using string_t = std::string;
	template<class Key,class T>
	using map_t = std::unordered_map<Key,T>;
	//template<class T>
	//using freelist_t = Container::AsyncFreeListEx<T>;
	template<class T>
	using array_t = std::vector<T>;
	template<class T>
	using queue_t = std::queue<T>;
	template<class T>
	using stack_t = std::stack<T>;
	template<class T>
	using deque_t = std::deque<T>;

	struct Vector2
	{
		int x;
		int y;
	};
};

namespace MugenScript
{
	struct Token;
	struct Tree;
	struct TreeNode;
	class MugenScriptCode;
	enum KEYWORD_KIND;
	using ScriptString = MugenScriptContainer::string_t;
	using ScriptToken = Token;
	using ScriptTree = Tree;
	using ScriptTreeNode = TreeNode;
	using MugenScriptTokenType = KEYWORD_KIND;
	using MugenScriptMachinePictureCommand = size_type;

	enum MugenScriptCommand
	{
		MugenScriptCommand_None,
		MugenScriptCommand_Comma,
		MugenScriptCommand_Access,
		MugenScriptCommand_Relation,
		MugenScriptCommand_SharpOperator,
		MugenScriptCommand_LabelOperator,
		MugenScriptCommand_CalcOperator,
		MugenScriptCommand_Puls,
		MugenScriptCommand_Minus,
		MugenScriptCommand_PulsEqual,
		MugenScriptCommand_MinusEqual,
		MugenScriptCommand_Equal,
		MugenScriptCommand_Equality,
		MugenScriptCommand_PulsUnary,
		MugenScriptCommand_MinusUnary,
		MugenScriptCommand_EqualUnary,
		MugenScriptCommand_OR,
		MugenScriptCommand_AND,
		MugenScriptCommand_Greater,
		MugenScriptCommand_Lesser,
		MugenScriptCommand_GreaterEqual,
		MugenScriptCommand_LesserEqual,
		MugenScriptCommand_If,
		MugenScriptCommand_Start,
		MugenScriptCommand_Choise,
		MugenScriptCommand_Select,
		MugenScriptCommand_InputString,
		MugenScriptCommand_Cancel,
		MugenScriptCommand_To,
		MugenScriptCommand_Newline,
		MugenScriptCommand_Newpage,
		MugenScriptCommand_SwapString,
		MugenScriptCommand_PictureFun,
		MugenScriptCommand_PictureSad,
		MugenScriptCommand_PictureAngry,
		MugenScriptCommand_PictureHappy,
		MugenScriptCommand_PictureCry,
		MugenScriptCommand_PictureShock,
		MugenScriptCommand_PictureBackGround,
		MugenScriptCommand_PictureDelete,
		MugenScriptCommand_PicturePosRight,
		MugenScriptCommand_PicturePosLeft,
		MugenScriptCommand_PicturePosCenter,
		MugenScriptCommand_SetPicture,
		MugenScriptCommand_SetPictureBright,
		MugenScriptCommand_Function,
		MugenScriptCommand_Argment,
		MugenScriptCommand_Register,
		MugenScriptCommand_Number,
		MugenScriptCommand_LoadScript,
		MugenScriptCommand_BGM,
		MugenScriptCommand_SE,
		MugenScriptCommand_Play,
		MugenScriptCommand_Pause,
		MugenScriptCommand_Stop,
		MugenScriptCommand_Auto_Start,
		MugenScriptCommand_Auto_Stop,
		MugenScriptCommand_Database_Load,
		MugenScriptCommand_Table_Load,
		MugenScriptCommand_Database_UnLoad,
		MugenScriptCommand_Ending,
		MugenScriptCommand_String = -1
	};

	enum MugenScriptMachineOperandTag
	{
		MSM_TAG_INT,
		MSM_TAG_DBL,
		MSM_TAG_STRING,
	};

	enum MugenScriptMachineRequestType
	{
		MugenScriptMachineRequestType_Decide,
		MugenScriptMachineRequestType_Choise,
		MugenScriptMachineRequestType_InputKey,
	};

	enum MugenScriptMachinePictureCommand_
	{
		MugenScriptMachinePictureCommand_Fun,
		MugenScriptMachinePictureCommand_Happy,
		MugenScriptMachinePictureCommand_Sad,
		MugenScriptMachinePictureCommand_Angry,
		MugenScriptMachinePictureCommand_Cry,
		MugenScriptMachinePictureCommand_Shock,
		MugenScriptMachinePictureCommand_NumFacial,
		MugenScriptMachinePictureCommand_Back,
		MugenScriptMachinePictureCommand_Disp,
		MugenScriptMachinePictureCommand_Delete,
		MugenScriptMachinePictureCommand_Blackout,
		MugenScriptMachinePictureCommand_Bright,
		MugenScriptMachinePictureCommand_PositionRight,
		MugenScriptMachinePictureCommand_PositionLeft,
		MugenScriptMachinePictureCommand_PositionCenter,
	};

	enum MugenScriptMachineSoundCommand_
	{
		MugenScriptMachineSoundCommand_BGM,
		MugenScriptMachineSoundCommand_SE,
		MugenScriptMachineSoundCommand_Play,
		MugenScriptMachineSoundCommand_Pause,
		MugenScriptMachineSoundCommand_Stop,
	};

	enum MugenScriptMachineBehavior
	{
		MSM_NONE,
		MSM_PUSH,
		MSM_POP,
		MSM_JUMP,
		MSM_JUMP_PAGE,
		MSM_READ,
		MSM_READ_STRING,
		MSM_FUNCTION,
		MSM_WRITE,
		MSM_WRITE_SAME_LINE,
		MSM_BRANCH,
		MSM_BRANCH_NOT,
		MSM_PULS,
		MSM_MINUS,
		MSM_STORE,
		MSM_AND,
		MSM_OR,
		MSM_EQUAL,
		MSM_GREATER,
		MSM_GREATER_EQUAL,
		MSM_LESSER,
		MSM_LESSER_EQUAL,
		MSM_YIELD,
		MSM_YIELD_ONE,
		MSM_REQUEST_INPUT_TEXT,
		MSM_REQUEST_INPUT_CHOISE_KEY,
		MSM_REQUEST_INPUT_VALUE,
		MSM_REQUEST_INPUT_LINK_REGISTER,
		MSM_REQUEST_OUTPUT_TEXT,
		MSM_REQUEST_OUTPUT_VALUE,
		MSM_REQUEST_OUTPUT_PICTURE,
		MSM_REQUEST_OUTPUT_PICTURE_FACIAL,
		MSM_REQUEST_OUTPUT_PICTURE_BRIGHT,
		MSM_REQUEST_OUTPUT_PICTURE_VALISH,
		MSM_REQUEST_OUTPUT_PICTURE_POS,
		MSM_REQUEST_OUTPUT_SOUND,
		MSM_REQUEST_OUTPUT_SET_BGM,
		MSM_REQUEST_OUTPUT_PLAY_BGM,
		MSM_REQUEST_OUTPUT_PAUSE_BGM,
		MSM_REQUEST_OUTPUT_STOP_BGM,
		MSM_REQUEST_OUTPUT_PLAY_SE,
		MSM_REQUEST_OUTPUT_AUTO_START,
		MSM_REQUEST_OUTPUT_AUTO_STOP,
		MSM_REQUEST_OUTPUT_CHOISE,
		MSM_REQUEST_OUTPUT_CHOISE_DEFINE,
		MSM_REQUEST_LOAD_SCRIPT,
		MSM_REQUEST_LOAD_DATABASE,
		MSM_REQUEST_LOAD_TABLE,
		MSM_REQUEST_UNLOAD_DATABASE,
		MSM_REQUEST_ACCESS_TABLE,
		MSM_REQUEST_ACCESS_RELATION,
		MSM_REQUEST_ACCESS_COLUMN,
		MSM_LABEL,
		MSM_CLEAR,
		MSM_QUERY,
		MSM_PAGE,
	};

	enum OPERATOR_PRIORITY
	{
		OPERATOR_PRIORITY_1 = 1,
		OPERATOR_PRIORITY_2,
		OPERATOR_PRIORITY_3,
		OPERATOR_PRIORITY_4,
		OPERATOR_PRIORITY_5,
		OPERATOR_PRIORITY_6,
		OPERATOR_PRIORITY_7,
		OPERATOR_PRIORITY_8,
		OPERATOR_PRIORITY_NUM
	};

	enum KEYWORD_KIND
	{
		KEYWORD_KIND_NONE,
		KEYWORD_KIND_OPERATOR,
		KEYWORD_KIND_PARENTHES,
		KEYWORD_KIND_STATEMENT,
		KEYWORD_KIND_COMMAND,
		KEYWORD_KIND_INDENT,
		KEYWORD_KIND_HEADER,
	};

	enum PARSER_MODE
	{
		PARSER_MODE_NONE,
		PARSER_MODE_DEFAULT,
		PARSER_MODE_HEADER,
		PARSER_MODE_PARENTHES,
		PARSER_MODE_CALC,
	};

	enum PARSER_KIND
	{
		PARSER_KIND_PARSE_HEADER,
		PARSER_KIND_PARSE_ARGMENT,
		PARSER_KIND_PARSE_CONNECTOR,
		PARSER_KIND_PARSE_PARENTHES,
		PARSER_KIND_PARSE_PARENTHES_CALC,
		PARSER_KIND_PARSE_FUNCTION,
		PARSER_KIND_PARSE_STATEMENT,
		PARSER_KIND_PARSE_CALCRATOR,
		PARSER_KIND_PARSE_ELEMENT,
		PARSER_KIND_PARSE_LINE_TOKEN,
		PARSER_KIND_PARSE_END_TERM,
		PARSER_KIND_PARSE_NONE,
	};

	enum PARSER_STATEMENT
	{
		PARSER_STATEMENT_NONE = 0,
		PARSER_STATEMENT_KEYWORD_STATEMENT = (1 << 0),
		PARSER_STATEMENT_KEYWORD_CHARACTOR = (1 << 1),
		PARSER_STATEMENT_PARSER_KIND = (1 << 2),
	};

	enum GENERATOR_KIND
	{
		GENERATOR_KIND_NONE,
		GENERATOR_KIND_HEADER,
		GENERATOR_KIND_CONNECTOR,
		GENERATOR_KIND_OPERATOR,
		GENERATOR_KIND_PARENTHES,
		GENERATOR_KIND_STATEMENT,
		GENERATOR_KIND_COMMAND,
		GENERATOR_KIND_PRIORITY_ARGMENT,
		GENERATOR_KIND_PARSE_END_TERM,
	};


	size_type GetCharactorLen(const char*);

	struct Token
	{
		int type = 0;
		Token* next = nullptr;
		char* str = nullptr;
		size_t size = 0;
		OPERATOR_PRIORITY priority;
	};

	struct TreeNode
	{
		TreeNode* lhs = nullptr;
		TreeNode* rhs = nullptr;
		char* str = nullptr;
		size_t size = 0;
		int type;
	};

	struct Tree
	{
		TreeNode* node = nullptr;
		Tree* next = nullptr;
	};

	union ParserStatementData
	{
		char charactor;
		PARSER_KIND kind;
		void operator=(const ParserStatementData&);
		ParserStatementData(PARSER_KIND kind) :kind(kind) {}
		ParserStatementData(char charactor) :charactor(charactor) {}
		ParserStatementData() :kind() {}
		~ParserStatementData() {}
	};

	struct ParserStatement
	{
		ParserStatementData data;
		PARSER_STATEMENT kind;
		void operator=(const ParserStatement&);
		ParserStatement() :kind(PARSER_STATEMENT_NONE), data() {}
		ParserStatement(PARSER_STATEMENT statement) :kind(PARSER_STATEMENT_KEYWORD_STATEMENT) {}
		ParserStatement(PARSER_KIND parser) :kind(PARSER_STATEMENT_PARSER_KIND), data(parser) {}
		ParserStatement(char charactor) :kind(PARSER_STATEMENT_KEYWORD_CHARACTOR), data(charactor) {}
	};

	struct ConfigrateData
	{
		KEYWORD_KIND kind;
		PARSER_KIND parser;
		GENERATOR_KIND generator;
		PARSER_MODE mode;
		ParserStatement statement;
		char str[16];
		size_type size;
		int type;
		OPERATOR_PRIORITY priority;

		void operator=(const ConfigrateData&);
		ConfigrateData(KEYWORD_KIND kind, PARSER_KIND parser, GENERATOR_KIND generator, const char* str, int type,  OPERATOR_PRIORITY priority = OPERATOR_PRIORITY_1, ParserStatement statement = ParserStatement(), PARSER_MODE mode = PARSER_MODE_NONE);
		ConfigrateData(const ConfigrateData&);
		ConfigrateData() :kind(), str(), size(),mode(),generator(),statement() {}
		~ConfigrateData();
	};

	struct TokenizerApi
	{
		Token* Tokenize(size_type numConfig, const ConfigrateData* config, size_type strLen, const char* str);
		virtual int IsOperator(size_type numConfig, const ConfigrateData* config, const char* str);
		virtual int IsKeyword(size_type numConfig, const ConfigrateData* config, const char* str);
		virtual int IsStatement(size_type numConfig, const ConfigrateData* config, const char* str);
		virtual int IsParenthes(size_type numConfig, const ConfigrateData* config, const char* str, int& open_close);
		virtual int IsHeader(size_type numConfig, const ConfigrateData* config, const char* str);
		virtual int IsIndent(size_type numConfig, const ConfigrateData* config, const char* str);
		virtual Token* CreateToken(int type, const char* str, size_t strSize) = 0;
		virtual void DeleteToken(Token*) = 0;
	protected:
		int GetTokenType(size_type numConfig, const ConfigrateData* config, size_type strSize, const char* str);
		size_t StrLenOneToken(size_type numConfig, const ConfigrateData* config, const char* str);
		size_type StrLenNextOperatorOrIndent(size_type numConfig, const ConfigrateData* config, const char* str);
	};

	struct ParserApi
	{
		Tree* Parse(size_type numConfig, const ConfigrateData* config, Token* token);
		virtual TreeNode* ParseOneTree(size_type numConfig, const ConfigrateData* config, Token*& token, OPERATOR_PRIORITY, PARSER_MODE mode, ParserStatement statement);
		virtual Tree* CreateTree() = 0;
		virtual TreeNode* CreateTreeNode(int type, const char* str, size_type len) = 0;
		virtual void DeleteTree(Tree*) = 0;
		virtual void DeleteTreeNode(TreeNode*) = 0;
	private:


		KEYWORD_KIND GetKeywordKind(size_type numConfig, const ConfigrateData* config, Token* token);
		PARSER_KIND GetParserKind(size_type numConfig, const ConfigrateData* config, Token* token);
		PARSER_MODE GetParserMode(size_type numConfig, const ConfigrateData* config, Token* token);
		ParserStatement GetParserStatement(size_type numConfig, const ConfigrateData* config, Token* token, ParserStatement current);
		size_type GetConfigIndex(size_type numConfig, const ConfigrateData* config, const char* str, size_type size);
		TreeNode* ParseOneTreeModeDefault(size_type numConfig, const ConfigrateData* config, Token*& token, OPERATOR_PRIORITY, PARSER_MODE mode, ParserStatement statement);
		TreeNode* ParseOneTreeModeCalcrate(size_type numConfig, const ConfigrateData* config, Token*& token, OPERATOR_PRIORITY);
		TreeNode* ParseTreeParenthes(size_type numConfig, const ConfigrateData* config, Token*& token, OPERATOR_PRIORITY priority, size_type index, PARSER_MODE mode);
		TreeNode* CreateTreeNode(TreeNode* lhs, TreeNode* rhs, Token* token);
		Token* ComsumeToken(Token*& token);
		void SetTokenNext(Token*& token);
		bool IsStatement(Token* toke, PARSER_KIND kind, ParserStatement statement);
	};

	struct ParserFileStream
	{
		void Open(MugenScriptContainer::string_t filepath);
		void Write(size_type numConfig, const ConfigrateData* config, Tree* tree);
	private:

	};

	struct GeneratorApi
	{
		void Genrate(size_type numConfig, const ConfigrateData* config, MugenScriptCode* code, Tree* tree);
		virtual TreeNode* GenerateCode(size_type numConfig, const ConfigrateData* config, MugenScriptCode* code, TreeNode*& node) = 0;
		virtual void WriteHeader(MugenScriptCode* code) {};
		virtual void WriteStatement(MugenScriptCode* code) {};
		virtual void SetHeader(TreeNode* node) = 0;
		GENERATOR_KIND GetGeneratorKind(size_type numConfig, const ConfigrateData* config, TreeNode* node);
		int GetHeaderType();
	private:
		int type;
	};

	class MugenScriptTokenizer :public TokenizerApi
	{
	public:

		Token* CreateToken(int type, const char* str, size_t strSize)override;
		void DeleteToken(Token* head)override;
	private:
		MugenScriptCommand nextTokenType;
	};

	class MugenScriptParser : public ParserApi
	{
	public:
		Tree* CreateTree()override;
		TreeNode* CreateTreeNode(int type, const char* str, size_type len)override;
		void DeleteTree(Tree*)override;
		void DeleteTreeNode(TreeNode*)override;

	private:
	};

	class MugenScriptGeneratorEx :public GeneratorApi
	{
	public:
		struct MugenScriptScope
		{
			MugenScriptCommand command;
			int pos;
		};
		void SetHeader(TreeNode*)override;
		void WriteHeader(MugenScriptCode*)override;
		void WriteStatement(MugenScriptCode* code)override;
		void WriteTokenTypeNone(TreeNode* node,MugenScriptCode* code);
		void WriteTokenTypeArgment(TreeNode* node, MugenScriptCode* code);
		TreeNode* GenerateCode(size_type numConfig, const ConfigrateData* config, MugenScriptCode* code, TreeNode*& node)override;
		int GetNumPage();
		int GetProgSize();
	private:
		int count;
		int page;
		MugenScriptCommand mode;
		MugenScriptContainer::stack_t<MugenScriptScope> scope;
	};

	class MugenScriptConfigration
	{
	public:

		MugenScriptContainer::array_t <ConfigrateData>& GetKeywordData();
		static MugenScriptConfigration& instance();
		MugenScriptConfigration();
	private:

		void Init();
		MugenScriptContainer::array_t<ConfigrateData> keywordData;
	};


	struct MugenScriptOperand
	{

		union MSOperand
		{
			int ivalue;
			double dvalue;
			char* str;
			MSOperand(int i) :ivalue(i) {}
			MSOperand(double d) :dvalue(d) {}
			MSOperand(char* s) :str(s) {}
			MSOperand() :dvalue() {}
			~MSOperand() {}
		};
		MugenScriptMachineOperandTag tag;
		MSOperand value;

		bool operator<=(const MugenScriptOperand& o)const;
		bool operator>=(const MugenScriptOperand& o)const;
		bool operator<(const MugenScriptOperand& o)const;
		bool operator>(const MugenScriptOperand& o)const;
		bool operator!=(const MugenScriptOperand& o)const;
		bool operator==(const MugenScriptOperand& o)const;
		MugenScriptOperand operator+(const MugenScriptOperand& o)const;
		MugenScriptOperand operator-(const MugenScriptOperand& o)const;

		void operator=(const MugenScriptOperand& operand);
		void operator=(MugenScriptOperand&& operand);
		MugenScriptOperand() :value(0.0), tag(MSM_TAG_INT) {}
		MugenScriptOperand(int ivalue) :value(ivalue), tag(MSM_TAG_INT) {};
		MugenScriptOperand(double dvalue) :value(dvalue), tag(MSM_TAG_DBL) {};
		MugenScriptOperand(const char* string);
		MugenScriptOperand(const MugenScriptOperand&);
		MugenScriptOperand(MugenScriptOperand&&);
		~MugenScriptOperand();

		bool QueryDataTypeFunctionCompare(
			const MugenScriptOperand& o,
			bool(*ifunc)(const MugenScriptOperand&, const MugenScriptOperand&),
			bool(*dfunc)(const MugenScriptOperand&, const MugenScriptOperand&),
			bool(*sfunc)(const MugenScriptOperand&, const MugenScriptOperand&)
		)const;
	};

	struct MugenScriptCode
	{
		MugenScriptMachineBehavior opecode;
		MugenScriptOperand operand;
		void operator=(const MugenScriptCode& o);
		void operator=(MugenScriptCode&& o);
		MugenScriptCode() :opecode(), operand(0) {};
		MugenScriptCode(MugenScriptMachineBehavior behavior, MugenScriptOperand operand) :opecode(behavior), operand(operand) {};
		MugenScriptCode(const MugenScriptCode&);
		MugenScriptCode(MugenScriptCode&&);
		~MugenScriptCode(){}
	};

	template<class Behavior>
	class MugenScriptCodeT
	{
		Behavior opecode;
		MugenScriptOperand operand;
		MugenScriptCodeT() :opecode(), operand(0) {};
		MugenScriptCodeT(Behavior opecode, MugenScriptOperand operand) :opecode(opecode), operand(operand) {};
	};

	class MugenScriptMachineCommandIO
	{
	public:

		virtual void Execute(MugenScriptMachineBehavior opecode,MugenScriptOperand& operand) = 0;
		virtual void EndScript(){}
		MugenScriptOperand PopStack();
		void PushStack(MugenScriptOperand);
		MugenScriptMachineCommandIO(MugenScriptContainer::stack_t<MugenScriptOperand>* stack):stack(stack){}
	private:
		MugenScriptContainer::stack_t<MugenScriptOperand>* stack;
	};

	class MugenScriptCommandWriter final :public MugenScriptMachineCommandIO
	{
	public:
		void Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)override;
		MugenScriptContainer::string_t PopString();
		bool Empty();
		void Clear();
		using MugenScriptMachineCommandIO::MugenScriptMachineCommandIO;
	private:
		MugenScriptContainer::deque_t<MugenScriptContainer::string_t> strQueue;
	};

	class MugenScriptCommandRegisterIO final :public MugenScriptMachineCommandIO
	{
	public:
		void Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)override;
		void SetRegister(MugenScriptContainer::string_t, MugenScriptOperand operand = MugenScriptOperand(0));
		void SetRegisterParam(MugenScriptContainer::string_t param, MugenScriptContainer::string_t charactor, MugenScriptOperand operand = MugenScriptOperand(0));
		MugenScriptOperand GetRegister(MugenScriptContainer::string_t);
		using MugenScriptMachineCommandIO::MugenScriptMachineCommandIO;
	private:

		MugenScriptContainer::map_t<MugenScriptContainer::string_t, MugenScriptOperand> registerMap;
	};

	class MugenScriptMachineEx
	{
	public:
		using Register = MugenScriptOperand;
		using StackType = MugenScriptOperand;

		void Init(MugenScriptContainer::vector_t<MugenScriptMachineBehavior> behabiors = {}, MugenScriptContainer::vector_t<MugenScriptMachineCommandIO*> commands = {});
		void Read(MugenScriptCode* code, size_type size);
		void SetPage(int numberPage,size_type progSize,MugenScriptCode* code);
		void SetLavel(MugenScriptContainer::string_t label, size_type progSize, MugenScriptCode* code);
		int GetCurrentPage();
		int GetCurrentPC();
		MugenScriptContainer::stack_t<StackType>* GetStack();
		MugenScriptCommandWriter* GetWriter();
		MugenScriptCommandRegisterIO* GetRegisterIO();
		void EndScript();
		MugenScriptMachineEx();
	private:
		void PushStack(StackType);
		StackType PopStack();
		int FindPageFromPC(size_type size, MugenScriptCode* code);
		int FindLavel(size_type size, MugenScriptCode* code, MugenScriptOperand operand);
		void RequestIO(MugenScriptMachineBehavior opecode,MugenScriptOperand operand);
		MugenScriptContainer::map_t<MugenScriptMachineBehavior, MugenScriptMachineCommandIO*> cmdIO;
		MugenScriptContainer::stack_t<StackType> stack;
		MugenScriptCommandWriter writer;
		MugenScriptCommandRegisterIO registerIO;
		int pc;
		int page;
	};


}
