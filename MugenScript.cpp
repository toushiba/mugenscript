#include <mbstring.h>
#include "MugenScript.h"
#define MUGEN_SCRIPT_CONFIGRATION_PARENTHES_OPEN 1
#define MUGEN_SCRIPT_CONFIGRATION_PARENTHES_CLOSE 2

void MugenScript::MugenScriptConfigration::Init()
{
	ConfigrateData configData[] =
	{
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CONNECTOR,GENERATOR_KIND_CONNECTOR,",",MugenScriptCommand_Comma,OPERATOR_PRIORITY_1},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CONNECTOR,GENERATOR_KIND_CONNECTOR,".",MugenScriptCommand_Access,OPERATOR_PRIORITY_6},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CONNECTOR,GENERATOR_KIND_CONNECTOR,"->",MugenScriptCommand_Relation,OPERATOR_PRIORITY_6},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,"+",MugenScriptCommand_Puls,OPERATOR_PRIORITY_4},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,"-",MugenScriptCommand_Minus,OPERATOR_PRIORITY_4},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,"=",MugenScriptCommand_Equal,OPERATOR_PRIORITY_5},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,"==",MugenScriptCommand_Equality,OPERATOR_PRIORITY_4},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,"+=",MugenScriptCommand_PulsEqual,OPERATOR_PRIORITY_5},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,"-=",MugenScriptCommand_MinusEqual,OPERATOR_PRIORITY_5},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,"||",MugenScriptCommand_OR,OPERATOR_PRIORITY_4},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,"&&",MugenScriptCommand_AND,OPERATOR_PRIORITY_4},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,"<",MugenScriptCommand_Greater,OPERATOR_PRIORITY_4},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,"<=",MugenScriptCommand_GreaterEqual,OPERATOR_PRIORITY_4},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,">",MugenScriptCommand_Lesser,OPERATOR_PRIORITY_4},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_CALCRATOR,GENERATOR_KIND_OPERATOR,">=",MugenScriptCommand_LesserEqual,OPERATOR_PRIORITY_4},
		{KEYWORD_KIND_PARENTHES,PARSER_KIND_PARSE_PARENTHES_CALC,GENERATOR_KIND_PARENTHES,"{}",MugenScriptCommand_SwapString,OPERATOR_PRIORITY_1,ParserStatement(),PARSER_MODE_CALC},
		{KEYWORD_KIND_PARENTHES,PARSER_KIND_PARSE_PARENTHES,GENERATOR_KIND_PARENTHES,"[]",MugenScriptCommand_SetPicture},
		{KEYWORD_KIND_PARENTHES,PARSER_KIND_PARSE_FUNCTION,GENERATOR_KIND_PARENTHES,"()",MugenScriptCommand_Function},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_LINE_TOKEN,GENERATOR_KIND_NONE,"if",MugenScriptCommand_If,OPERATOR_PRIORITY_1,ParserStatement(),PARSER_MODE_CALC},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"select",MugenScriptCommand_Select},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_LINE_TOKEN,GENERATOR_KIND_NONE,"choice",MugenScriptCommand_Choise},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"cancel",MugenScriptCommand_Cancel},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"input",MugenScriptCommand_InputString},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"to",MugenScriptCommand_To},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"fun",MugenScriptCommand_PictureFun},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"sad",MugenScriptCommand_PictureSad},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"angry",MugenScriptCommand_PictureAngry},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"happy",MugenScriptCommand_PictureHappy},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"cry",MugenScriptCommand_PictureCry},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"shock",MugenScriptCommand_PictureShock},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"delete",MugenScriptCommand_PictureDelete},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"L",MugenScriptCommand_PicturePosLeft},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"R",MugenScriptCommand_PicturePosRight},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"C",MugenScriptCommand_PicturePosCenter},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"back",MugenScriptCommand_PictureBackGround},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_COMMAND,"BGM",MugenScriptCommand_BGM},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_COMMAND,"SE",MugenScriptCommand_SE},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"play",MugenScriptCommand_Play},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"pause",MugenScriptCommand_Pause},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"stop",MugenScriptCommand_Stop},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"auto_start",MugenScriptCommand_Auto_Start},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"auto_stop",MugenScriptCommand_Auto_Stop},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"load_database",MugenScriptCommand_Database_Load},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"load_table",MugenScriptCommand_Table_Load},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"unload_database",MugenScriptCommand_Database_UnLoad},
		{KEYWORD_KIND_COMMAND,PARSER_KIND_PARSE_ARGMENT,GENERATOR_KIND_NONE,"end",MugenScriptCommand_Ending},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_END_TERM,GENERATOR_KIND_PARSE_END_TERM,"\n",MugenScriptCommand_Newline},
		{KEYWORD_KIND_OPERATOR,PARSER_KIND_PARSE_STATEMENT,GENERATOR_KIND_STATEMENT,"\n\n",MugenScriptCommand_Newpage},
		{KEYWORD_KIND_INDENT,PARSER_KIND_PARSE_NONE,GENERATOR_KIND_NONE," ",MugenScriptCommand_None},
		{KEYWORD_KIND_INDENT,PARSER_KIND_PARSE_NONE,GENERATOR_KIND_NONE,"	",MugenScriptCommand_None},
		{KEYWORD_KIND_HEADER,PARSER_KIND_PARSE_HEADER,GENERATOR_KIND_HEADER,"#",MugenScriptCommand_SharpOperator,},
		{KEYWORD_KIND_HEADER,PARSER_KIND_PARSE_HEADER,GENERATOR_KIND_HEADER,"%",MugenScriptCommand_CalcOperator,OPERATOR_PRIORITY_1,ParserStatement(),PARSER_MODE_CALC},
		{KEYWORD_KIND_HEADER,PARSER_KIND_PARSE_HEADER,GENERATOR_KIND_HEADER,"!",MugenScriptCommand_LoadScript},
		{KEYWORD_KIND_HEADER,PARSER_KIND_PARSE_HEADER,GENERATOR_KIND_HEADER,"@",MugenScriptCommand_LabelOperator},

	};

	keywordData.resize(_countof(configData));
	for (int i = 0; i < _countof(configData); ++i)
		keywordData[i] = configData[i];
}

void MugenScript::ConfigrateData::operator=(const ConfigrateData& data)
{
	kind = data.kind;
	size = data.size;
	type = data.type;
	parser = data.parser;
	generator = data.generator;
	priority = data.priority;
	statement = data.statement;
	mode = data.mode;
	for (int i = 0; i < 16; ++i)
		str[i] = data.str[i];
}

MugenScript::ConfigrateData::ConfigrateData(KEYWORD_KIND kind, PARSER_KIND parser, GENERATOR_KIND generator, const char* str, int type, OPERATOR_PRIORITY priority, ParserStatement statement,  PARSER_MODE mode) :kind(kind), str(), size(), type(type), priority(priority), mode(mode), parser(parser), generator(generator), statement(statement)
{
	size = strlen(str);
	strncpy_s(this->str, size + 1, str, size);
	//this->str[size] = '\0';
}

MugenScript::ConfigrateData::ConfigrateData(const ConfigrateData& data)
{
	*this = data;
}

MugenScript::ConfigrateData::~ConfigrateData()
{
}


MugenScriptContainer::array_t<MugenScript::ConfigrateData>& MugenScript::MugenScriptConfigration::GetKeywordData()
{
	return keywordData;
}

MugenScript::MugenScriptConfigration& MugenScript::MugenScriptConfigration::instance()
{
	static MugenScriptConfigration config;
	return config;
}

MugenScript::MugenScriptConfigration::MugenScriptConfigration()
{
	Init();
}


MugenScript::Token* MugenScript::MugenScriptTokenizer::CreateToken(int type, const char* str, size_t strSize)
{
	auto token = new Token;
	token->type = type;
	token->str = new char[strSize + 1];
	token->size = strSize;
	strncpy_s(token->str, strSize + 1, str, strSize);
	return token;
}

void MugenScript::MugenScriptTokenizer::DeleteToken(MugenScript::Token* head)
{
	auto node = head;
	if (node->next)
		DeleteToken(node->next);
	char* delStr = node->str;
	if (delStr)
		delete[] delStr;
	delete node;
}

size_type MugenScript::GetCharactorLen(const char* ptr)
{
	char c = *ptr;
	if ((c & 0x80) == 0) {
		return 1;
	}
	if ((c & 0xe0) == 0xc0) {
		return 2;
	}
	if ((c & 0xf0) == 0xe0) {
		return 3;
	}
	return 4;
	//return mblen((const char*)ptr,MB_CUR_MAX);
}


bool MugenScript::MugenScriptOperand::operator<=(const MugenScriptOperand& o) const
{

	auto ifunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.ivalue <= o.value.ivalue; };
	auto dfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.dvalue <= o.value.dvalue; };
	auto sfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return strcmp(t.value.str, o.value.str) <= 0; };
	return QueryDataTypeFunctionCompare(o, ifunc, dfunc, sfunc);
}

bool MugenScript::MugenScriptOperand::operator>=(const MugenScriptOperand& o) const
{

	auto ifunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.ivalue >= o.value.ivalue; };
	auto dfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.dvalue >= o.value.dvalue; };
	auto sfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return strcmp(t.value.str, o.value.str) >= 0; };
	return QueryDataTypeFunctionCompare(o, ifunc, dfunc, sfunc);
}
bool MugenScript::MugenScriptOperand::operator<(const MugenScriptOperand& o) const
{

	auto ifunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.ivalue < o.value.ivalue; };
	auto dfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.dvalue < o.value.dvalue; };
	auto sfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return strcmp(t.value.str, o.value.str) < 0; };
	return QueryDataTypeFunctionCompare(o, ifunc, dfunc, sfunc);
}
bool MugenScript::MugenScriptOperand::operator>(const MugenScriptOperand& o) const
{

	auto ifunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.ivalue > o.value.ivalue; };
	auto dfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.dvalue > o.value.dvalue; };
	auto sfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return strcmp(t.value.str, o.value.str) > 0; };
	return QueryDataTypeFunctionCompare(o, ifunc, dfunc, sfunc);
}

bool MugenScript::MugenScriptOperand::operator==(const MugenScriptOperand& o) const
{

	auto ifunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.ivalue == o.value.ivalue; };
	auto dfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.dvalue == o.value.dvalue; };
	auto sfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return strcmp(t.value.str, o.value.str) == 0; };
	return QueryDataTypeFunctionCompare(o, ifunc, dfunc, sfunc);
}

MugenScript::MugenScriptOperand MugenScript::MugenScriptOperand::operator+(const MugenScriptOperand& o) const
{

	auto ifunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o)
		{
			switch (o.tag)
			{
			case MSM_TAG_INT:
				return MugenScriptOperand(t.value.ivalue + o.value.ivalue);
				break;
			case MSM_TAG_DBL:
				return MugenScriptOperand(t.value.ivalue + o.value.dvalue);
				break;
			case MSM_TAG_STRING:
				assert(false);
				break;

			default:
				break;
			}
			return MugenScriptOperand();
		};
	auto dfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o)
		{
			switch (o.tag)
			{
			case MSM_TAG_INT:
				return MugenScriptOperand(t.value.dvalue + o.value.ivalue);
				break;
			case MSM_TAG_DBL:
				return MugenScriptOperand(t.value.dvalue + o.value.dvalue);
				break;
			case MSM_TAG_STRING:
				assert(false);
				break;

			default:
				break;
			}
			return MugenScriptOperand();
		};

	switch (tag)
	{
	case MugenScript::MSM_TAG_INT:
		return ifunc(*this, o);
		break;
	case MugenScript::MSM_TAG_DBL:
		return dfunc(*this, o);
		break;
	default:
		break;
	}
}

MugenScript::MugenScriptOperand MugenScript::MugenScriptOperand::operator-(const MugenScriptOperand& o) const
{
	auto ifunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o)
		{
			switch (o.tag)
			{
			case MSM_TAG_INT:
				return MugenScriptOperand(t.value.ivalue - o.value.ivalue);
				break;
			case MSM_TAG_DBL:
				return MugenScriptOperand(t.value.ivalue - o.value.dvalue);
				break;
			case MSM_TAG_STRING:
				assert(false);
				break;

			default:
				break;
			}
			return MugenScriptOperand();
		};
	auto dfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o)
		{
			switch (o.tag)
			{
			case MSM_TAG_INT:
				return MugenScriptOperand(t.value.dvalue - o.value.ivalue);
				break;
			case MSM_TAG_DBL:
				return MugenScriptOperand(t.value.dvalue - o.value.dvalue);
				break;
			case MSM_TAG_STRING:
				assert(false);
				break;

			default:
				break;
			}
			return MugenScriptOperand();
		};

	switch (tag)
	{
	case MugenScript::MSM_TAG_INT:
		return ifunc(*this, o);
		break;
	case MugenScript::MSM_TAG_DBL:
		return dfunc(*this, o);
		break;
	default:
		break;
	}
}

bool MugenScript::MugenScriptOperand::operator!=(const MugenScriptOperand& o) const
{

	auto ifunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.ivalue != o.value.ivalue; };
	auto dfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return t.value.dvalue != o.value.dvalue; };
	auto sfunc = [](const MugenScriptOperand& t, const MugenScriptOperand& o) {return strcmp(t.value.str, o.value.str) != 0; };
	return QueryDataTypeFunctionCompare(o, ifunc, dfunc, sfunc);
}

void MugenScript::MugenScriptOperand::operator=(const MugenScriptOperand& operand)
{
	if (this->tag == MSM_TAG_STRING && value.str)
		delete value.str;
	auto tag = operand.tag;
	this->tag = tag;


	switch (tag)
	{
	case MugenScript::MSM_TAG_INT: 
		value.ivalue = operand.value.ivalue;
		break;
	case MugenScript::MSM_TAG_DBL:
		value.dvalue = operand.value.dvalue;
		break;
	case MugenScript::MSM_TAG_STRING:
	{
		auto len = strlen(operand.value.str) + 1;
		value.str = new char[len];
		strcpy_s(value.str, len, operand.value.str);

	}
		break;
	default:
		assert(false);
		break;
	}
}

void MugenScript::MugenScriptOperand::operator=(MugenScriptOperand&& operand)
{
	auto tag = operand.tag;
	this->tag = tag;

	switch (tag)
	{
	case MugenScript::MSM_TAG_INT:
		value.ivalue = std::move(operand.value.ivalue);
		operand.value.ivalue = 0;
		break;
	case MugenScript::MSM_TAG_DBL:
		value.dvalue = std::move(operand.value.dvalue);
		operand.value.dvalue = 0.0;
		break;
	case MugenScript::MSM_TAG_STRING:
		value.str = std::move(operand.value.str);
		operand.value.str = nullptr;
		break;
	default:
		assert(false);
		break;
	}
}


MugenScript::MugenScriptOperand::MugenScriptOperand(const char* string):tag(MSM_TAG_STRING),value(nullptr)
{
	auto len = strlen(string) + 1;
	value.str = new char[len];
	strcpy_s(value.str, len, string);
}

MugenScript::MugenScriptOperand::MugenScriptOperand(const MugenScriptOperand& operand) :tag(MSM_TAG_INT), value(nullptr)
{
	*this = operand;
}

MugenScript::MugenScriptOperand::MugenScriptOperand(MugenScriptOperand&& operand) : tag(MSM_TAG_INT), value(nullptr)
{
	*this = std::move(operand);
}

MugenScript::MugenScriptOperand::~MugenScriptOperand()
{
	if (tag == MSM_TAG_STRING && value.str)
		delete value.str;
}
bool MugenScript::MugenScriptOperand::QueryDataTypeFunctionCompare(const MugenScriptOperand& o, bool(*ifunc)(const MugenScriptOperand&, const MugenScriptOperand&), bool(*dfunc)(const MugenScriptOperand&, const MugenScriptOperand&), bool(*sfunc)(const MugenScriptOperand&, const MugenScriptOperand&)) const
{
	switch (tag)
	{
	case MugenScript::MSM_TAG_INT:
		return ifunc(*this, o);
		break;
	case MugenScript::MSM_TAG_DBL:		
		return dfunc(*this, o);
		break;
	case MugenScript::MSM_TAG_STRING:
		return sfunc(*this, o);
		break;
	default:
		assert(false);
		break;
	}
}

int MugenScript::TokenizerApi::GetTokenType(size_type numConfig, const ConfigrateData* config, size_type strSize, const char* str)
{
	for (size_type i = 0; i < numConfig; ++i)
		if (config[i].kind != KEYWORD_KIND_PARENTHES && config[i].size == strSize && strncmp(config[i].str, str, config[i].size) == 0)
			return config[i].type;
		else if (config[i].kind == KEYWORD_KIND_PARENTHES && (config[i].str[0] == str[0] || config[i].str[1] == str[0]))
			return config[i].type;
	return -1;
}

size_t MugenScript::TokenizerApi::StrLenOneToken(size_type numConfig, const MugenScript::ConfigrateData* config, const char* str)
{
	int strLen = strlen(str);
	const char* ptr = str;
	while (1)
	{
		int result = IsIndent(numConfig, config, ptr);
		if (result == -2)
			return 0;
		else if (result != -1)
			ptr += GetCharactorLen(ptr);
		else
			break;
	}

	auto operatorIndex = IsOperator(numConfig, config, str);
	if (operatorIndex != -1)
		return config[operatorIndex].size;

	auto headerIndex = IsHeader(numConfig, config, str);
	if (headerIndex != -1)
		return config[headerIndex].size;

	auto keywordIndex = IsKeyword(numConfig, config, str);
	if (keywordIndex != -1)
		return config[keywordIndex].size;

	auto statementIndex = IsStatement(numConfig, config, str);
	if (statementIndex != -1)
		return config[statementIndex].size;

	int open_close = 0;
	auto parenthesIndex = IsParenthes(numConfig, config, ptr, open_close);
	if (parenthesIndex != -1)
	{
		return config[parenthesIndex].size / 2;
	}

	size_type count = 0;
	size_type size = 0;
	while (count < strLen && IsParenthes(numConfig, config, ptr, open_close) == -1 && IsIndent(numConfig, config, ptr) == -1 && IsStatement(numConfig, config, ptr) == -1 && operatorIndex == -1)
	{
		size = GetCharactorLen(ptr);
		ptr += size;
		count += size;
		operatorIndex = IsOperator(numConfig, config, ptr);
	}
	if (count == 0)
		return 1;
	return count;
}

size_type MugenScript::TokenizerApi::StrLenNextOperatorOrIndent(size_type numConfig, const ConfigrateData* config, const char* str)
{
	auto p = str;
	size_type len = strlen(str);
	size_type count = 0;
	while (count<len&&IsIndent(numConfig, config, p) == -1 && IsOperator(numConfig, config, str) == -1)
	{
		++p;
		++count;
	}
	return count;
}


MugenScript::Tree* MugenScript::ParserApi::Parse(size_type numConfig, const ConfigrateData* config, Token* token)
{
	Tree* treeHead = CreateTree();
	Tree* tree = treeHead;
	Token* currentToken = token;
	Token* parseHead = token;
	Token* next = nullptr;
	auto statement = GetParserStatement(numConfig, config, token, ParserStatement());
	//auto mode = GetParserMode(numConfig, config, token);
	auto mode = PARSER_MODE_DEFAULT;
	

	while (currentToken)
	{
		parseHead = currentToken;
		while (currentToken)
		{
			if (GetParserKind(numConfig, config, currentToken) == PARSER_KIND_PARSE_STATEMENT)
			{
				next = currentToken->next;
				currentToken->next = nullptr;
				break;
			} 
			currentToken = currentToken->next;
		}
		tree->node = ParseOneTree(numConfig, config, parseHead, OPERATOR_PRIORITY_1, mode, statement);
		tree->next = CreateTree();
		tree = tree->next;
		if (currentToken)
		{
			currentToken->next = next;
			currentToken = next;
		}
	}
	return treeHead;
}

MugenScript::TreeNode* MugenScript::ParserApi::ParseOneTree(size_type numConfig, const ConfigrateData* config, Token*& token, OPERATOR_PRIORITY priority, PARSER_MODE mode, ParserStatement statement)
{
	TreeNode* node = nullptr;
	if (!token)
		return node;

	if (mode == PARSER_MODE_CALC)
	{
		node = ParseOneTreeModeCalcrate(numConfig, config, token, priority);
		if (GetParserKind(numConfig, config, token) == PARSER_KIND_PARSE_END_TERM)
			SetTokenNext(token);
	}
	else
		node = ParseOneTreeModeDefault(numConfig, config, token, priority, mode, statement);
	return node;
}

MugenScript::KEYWORD_KIND MugenScript::ParserApi::GetKeywordKind(size_type numConfig, const ConfigrateData* config, Token* token)
{
	for (size_type i = 0; i < numConfig; ++i)
		if (strcmp(config[i].str, token->str) == 0)
			return config[i].kind;
	return KEYWORD_KIND_NONE;
}

MugenScript::PARSER_KIND MugenScript::ParserApi::GetParserKind(size_type numConfig, const ConfigrateData* config, Token* token)
{
	if (!token)
		return PARSER_KIND_PARSE_STATEMENT;
	for (size_type i = 0; i < numConfig; ++i)
		if (strncmp(config[i].str, token->str, token->size) == 0)
			return config[i].parser;
		else if (config[i].kind == KEYWORD_KIND_PARENTHES && (config[i].str[0] == token->str[0] || config[i].str[1] == token->str[0]))
			return config[i].parser;
	return PARSER_KIND_PARSE_NONE;
}

MugenScript::PARSER_MODE MugenScript::ParserApi::GetParserMode(size_type numConfig, const ConfigrateData* config, Token* token)
{
	if (!token)
		return PARSER_MODE_NONE;

	for (size_type i = 0; i < numConfig; ++i)
		if (strcmp(config[i].str, token->str) == 0)
			return config[i].mode;
	return PARSER_MODE_NONE;
}

MugenScript::ParserStatement MugenScript::ParserApi::GetParserStatement(size_type numConfig, const ConfigrateData* config, Token* token, ParserStatement current)
{
	auto index = GetConfigIndex(numConfig, config, token->str, token->size);
	if (!token || current.kind == PARSER_STATEMENT_NONE || index == -1)
		return current;
	return config[index].statement;
}

size_type MugenScript::ParserApi::GetConfigIndex(size_type numConfig, const ConfigrateData* config, const char* str, size_type size)
{
	for (size_type i = 0; i < numConfig; ++i)
		if (config[i].kind != KEYWORD_KIND_PARENTHES && strncmp(config[i].str, str, size) == 0)
			return i;
		else if (config[i].kind == KEYWORD_KIND_PARENTHES && (config[i].str[0] == str[0] || config[i].str[1] == str[0]))
			return i;
	return -1;
}

MugenScript::TreeNode* MugenScript::ParserApi::ParseOneTreeModeDefault(size_type numConfig, const ConfigrateData* config, Token*& token, OPERATOR_PRIORITY priority, PARSER_MODE mode, ParserStatement statement)
{
	auto kind = GetParserKind(numConfig, config, token);
	auto keyword = GetKeywordKind(numConfig, config, token);
	auto currentStatement = GetParserStatement(numConfig, config, token, statement);
	//auto mode = keyword == KEYWORD_KIND_HEADER ? GetParserMode(numConfig, config, token->next) : PARSER_MODE_DEFAULT;
	TreeNode* node = nullptr;
	TreeNode* lhs = nullptr;
	TreeNode* rhs = nullptr;

	if (IsStatement(token, kind, currentStatement))
		return nullptr;

	if (token && token->type == -1)
	{
		node = CreateTreeNode(token->type, token->str, token->size);
		SetTokenNext(token);
		kind = GetParserKind(numConfig, config, token);
		if (kind == PARSER_KIND_PARSE_STATEMENT)
		{
			//node->lhs = ParseOneTree(numConfig, config, token, priority, mode, currentStatement);
			return node;
		}
		else if (kind == PARSER_KIND_PARSE_END_TERM&&mode==PARSER_MODE_DEFAULT)
			rhs = ParseOneTree(numConfig, config, token, priority, mode, currentStatement);
		lhs = ParseOneTree(numConfig, config, token, priority, mode, currentStatement);
		node->lhs = lhs;
		node->rhs = rhs;
		return node;
	}

	switch (kind)
	{
	case MugenScript::PARSER_KIND_PARSE_HEADER:
	{
		auto m = GetParserMode(numConfig, config, token);
		return CreateTreeNode(ParseOneTree(numConfig, config, token, priority, mode, currentStatement), ParseOneTree(numConfig, config, token, priority, m, currentStatement), ComsumeToken(token));
		break;
	}
	case MugenScript::PARSER_KIND_PARSE_ARGMENT:
		return CreateTreeNode(ParseOneTree(numConfig, config, token, priority, mode, currentStatement), nullptr, ComsumeToken(token));
		break;
	case MugenScript::PARSER_KIND_PARSE_CONNECTOR:
		return CreateTreeNode(ParseOneTree(numConfig, config, token, priority, mode, currentStatement), nullptr, ComsumeToken(token));
		break;
	case MugenScript::PARSER_KIND_PARSE_PARENTHES_CALC:
		if (token&& *token->str==config[GetConfigIndex(numConfig,config,token->str,token->size)].str[1])
		{
			SetTokenNext(token);
			return ParseOneTree(numConfig, config, token, priority, mode, statement);
		}
		return CreateTreeNode(ParseOneTree(numConfig, config, token, priority, mode, currentStatement), ParseOneTree(numConfig, config, token, priority, PARSER_MODE_CALC, currentStatement), ComsumeToken(token));
		break;
	case MugenScript::PARSER_KIND_PARSE_PARENTHES:
		if (mode == PARSER_MODE_PARENTHES)
		{
			node = CreateTreeNode(nullptr, nullptr, ComsumeToken(token));
			if (GetParserKind(numConfig, config, token) == PARSER_KIND_PARSE_END_TERM)
				node->rhs = CreateTreeNode(nullptr, nullptr, ComsumeToken(token));
			return node;
		}
		return CreateTreeNode(ParseOneTree(numConfig, config, token, priority, mode, currentStatement), ParseOneTree(numConfig, config, token, priority, PARSER_MODE_PARENTHES, currentStatement), ComsumeToken(token));
		break;
	case MugenScript::PARSER_KIND_PARSE_STATEMENT:
		return CreateTreeNode(nullptr, nullptr, ComsumeToken(token));
		break;
	case MugenScript::PARSER_KIND_PARSE_END_TERM:
		return CreateTreeNode(nullptr, nullptr, ComsumeToken(token));
		break;

	case MugenScript::PARSER_KIND_PARSE_LINE_TOKEN:
	{
		auto m = GetParserMode(numConfig, config, token);
		return CreateTreeNode(ParseOneTree(numConfig, config, token, priority, mode, currentStatement), ParseOneTree(numConfig, config, token, priority, m, currentStatement), ComsumeToken(token));
		break;
	}case MugenScript::PARSER_KIND_PARSE_CALCRATOR:
		return CreateTreeNode(ParseOneTree(numConfig, config, token, priority, mode, currentStatement), nullptr, ComsumeToken(token));
		break;
	case MugenScript::PARSER_KIND_PARSE_ELEMENT:
		return CreateTreeNode(ParseOneTree(numConfig, config, token, priority, mode, currentStatement), nullptr, ComsumeToken(token));
		break;
	case MugenScript::PARSER_KIND_PARSE_NONE:
		return CreateTreeNode(ParseOneTree(numConfig, config, token, priority, PARSER_MODE_NONE, currentStatement), nullptr, ComsumeToken(token));
		break;
	default:
		break;
	}

	return nullptr;
}

MugenScript::TreeNode* MugenScript::ParserApi::ParseOneTreeModeCalcrate(size_type numConfig, const ConfigrateData* config, Token*& token, OPERATOR_PRIORITY priority)
{
	auto nextPriority = (OPERATOR_PRIORITY)(priority + 1);
	TreeNode* node = nullptr;
	TreeNode* lhs = nullptr;
	TreeNode* rhs = nullptr;
	if (priority != OPERATOR_PRIORITY_NUM - 1)
		node = ParseOneTreeModeCalcrate(numConfig, config, token, nextPriority);
	auto keyword = GetKeywordKind(numConfig, config, token);
	auto mode = keyword == KEYWORD_KIND_HEADER ? GetParserMode(numConfig, config, token->next) : PARSER_MODE_CALC;

	auto parserKind = GetParserKind(numConfig, config, token);
	if (parserKind == PARSER_KIND_PARSE_FUNCTION)
	{
		auto idx = GetConfigIndex(numConfig, config, token->str, token->size);
		if (config[idx].str[0] == token->str[0] && node)
		{
			auto f = CreateTreeNode(token->type, token->str, token->size);
			SetTokenNext(token);
			f->lhs = ParseOneTreeModeCalcrate(numConfig, config, token, OPERATOR_PRIORITY_1);
			node->rhs = f;
			node->type = f->type;
			return node;
		}
		else if (config[idx].str[1] == token->str[0]&&priority==OPERATOR_PRIORITY_1)
		{
			auto end = node;
			while (end && end->lhs)
				end = end->lhs;
			if (end)
				end->lhs = CreateTreeNode(token->type, token->str, token->size);
			else
				node = CreateTreeNode(token->type, token->str, token->size);
			SetTokenNext(token);
		}
	}

	for (size_type i = 0; i < numConfig; ++i)
	{
		if (keyword == KEYWORD_KIND_NONE || parserKind == PARSER_KIND_PARSE_END_TERM || parserKind == PARSER_KIND_PARSE_STATEMENT)
			break;
		if (config[i].priority != priority || strcmp(config[i].str, token->str) != 0)
			continue;
		lhs = node;
		node = CreateTreeNode(token->type, token->str, token->size);
		SetTokenNext(token);
		rhs = ParseOneTreeModeCalcrate(numConfig, config, token, nextPriority);
		node->rhs = rhs;
		node->lhs = lhs;
		//return node;
	}

	if (keyword == KEYWORD_KIND_NONE && priority == OPERATOR_PRIORITY_NUM - 1)
	{
		node = CreateTreeNode(token->type, token->str, token->size);
		SetTokenNext(token);
	}
	return node;
}

MugenScript::TreeNode* MugenScript::ParserApi::ParseTreeParenthes(size_type numConfig, const ConfigrateData* config, Token*& token, OPERATOR_PRIORITY priority, size_type index, PARSER_MODE mode)
{
	if (!token || index == -1 || token->type == PARSER_KIND_PARSE_END_TERM)
		return nullptr;
	if (token->type == KEYWORD_KIND_PARENTHES && *token->str != config[index].str[1])
		assert(false);

	Token* currentToken = ComsumeToken(token);
	TreeNode* node = nullptr;
	node = ParseTreeParenthes(numConfig, config, currentToken, priority, index, mode);

	return nullptr;
}

MugenScript::TreeNode* MugenScript::ParserApi::CreateTreeNode(TreeNode* lhs, TreeNode* rhs, Token* token)
{
	auto node = CreateTreeNode(token->type, token->str, token->size);
	node->lhs = lhs;
	node->rhs = rhs;
	return node;
}

MugenScript::Token* MugenScript::ParserApi::ComsumeToken(Token*& token)
{
	auto pre = token;
	token = token->next;
	return pre;
}

void MugenScript::ParserApi::SetTokenNext(Token*& token)
{
	token = token->next;
}

bool MugenScript::ParserApi::IsStatement(Token* token, PARSER_KIND kind, ParserStatement statement)
{
	auto statementKind = statement.kind;
	switch (statementKind)
	{
	case MugenScript::PARSER_STATEMENT_NONE:
		break;
	case MugenScript::PARSER_STATEMENT_KEYWORD_STATEMENT:
		if (kind == PARSER_KIND_PARSE_STATEMENT)
			return true;
		break;
	case MugenScript::PARSER_STATEMENT_KEYWORD_CHARACTOR:
		if (statement.data.charactor == token->str[0])
			return true;
		break;
	case MugenScript::PARSER_STATEMENT_PARSER_KIND:
		if (kind == statement.data.kind)
			return true;
		break;
	default:
		break;
	}

	return false;
}

void MugenScript::GeneratorApi::Genrate(size_type numConfig, const ConfigrateData* config, MugenScriptCode* code, Tree* tree)
{
	auto t = tree;
	auto node = tree->node;
	WriteHeader(code);
	while (node)
	{
		auto line = node;
		type = 0;
		while (line)
		{
			SetHeader(line);
			GenerateCode(numConfig, config, code, line);
			line = line->lhs;
		}
		WriteStatement(code);
		t = t->next;
		node = t->node;
	}
}


MugenScript::GENERATOR_KIND MugenScript::GeneratorApi::GetGeneratorKind(size_type numConfig, const ConfigrateData* config, TreeNode* node)
{
	for (size_type i = 0; i < numConfig; ++i)
		if (config[i].kind != KEYWORD_KIND_PARENTHES)
		{
			if (strcmp(config[i].str, node->str) == 0)
				return config[i].generator;
		}
		else
			if (config[i].str[0] == node->str[0] || config[i].str[1] == node->str[0])
				return config[i].generator;

	return GENERATOR_KIND_NONE;
}

int MugenScript::GeneratorApi::GetHeaderType()
{
	return type;
}


MugenScript::Token* MugenScript::TokenizerApi::Tokenize(size_type numConfig, const ConfigrateData* config, size_type strLen, const char* str)
{
	const char* ptr = str;
	const char* end = str + strLen;
	MugenScript::Token* head = nullptr;
	MugenScript::Token* t = head;

	while (ptr < end)
	{
		while (1)
		{
			int result = IsIndent(numConfig, config, ptr);
			if (result == -2)
				return head;
			else if (result != -1)
				++ptr;
			else 
				break;
		}
		size_type tokenStrSize = 0;
		int tokenType = 0;
		tokenStrSize = StrLenOneToken(numConfig, config, ptr);
		tokenType = GetTokenType(numConfig, config, tokenStrSize, ptr);
		if (end < ptr + tokenStrSize || tokenStrSize == 0)
			break;
		if (!head)
		{
			head = CreateToken(tokenType, ptr, tokenStrSize);
			t = head;
		}
		else
		{
			t->next = CreateToken(tokenType, ptr, tokenStrSize);
			t = t->next;
		}
		ptr += tokenStrSize;
	}

	return head;
}

int MugenScript::TokenizerApi::IsOperator(size_type numConfig, const ConfigrateData* config, const char* str)
{
	int ret = -1;
	size_type retSize = 0;

	for (size_type i = 0; i < numConfig; ++i)
	{
		if (config[i].kind != KEYWORD_KIND_OPERATOR)
			continue;

		//オペレーターの検索
		if (strncmp(config[i].str, str, config[i].size) == 0)
		{
			//既に見つかっている物よりサイズが大きければ変更
			if (retSize < config[i].size)
			{
				ret = i;
				retSize = config[i].size;
			}
		}
	}
	return ret;
}

int MugenScript::TokenizerApi::IsKeyword(size_type numConfig, const ConfigrateData* config, const char* str)
{
	size_t strSize = StrLenNextOperatorOrIndent(numConfig, config, str);
	for (size_t i = 0; i < numConfig; ++i)
	{
		if (config[i].kind != KEYWORD_KIND_COMMAND)
			continue;
		auto len = strSize > config[i].size ? strSize : config[i].size;
		if (strncmp(config[i].str, str, len) == 0)
		{
			return i;
		}
	}

	return -1;
}

int MugenScript::TokenizerApi::IsStatement(size_type numConfig, const ConfigrateData* config, const char* str)
{
	for (size_t i = 0; i < numConfig; ++i)
	{
		if (config[i].kind != KEYWORD_KIND_STATEMENT)
			continue;

		if (strncmp(config[i].str, str, config[i].size) == 0)
		{
			return i;
		}
	}

	return -1;
}

int MugenScript::TokenizerApi::IsParenthes(size_type numConfig, const ConfigrateData* config, const char* str, int& open_close)
{
	char chr = *str;
	for (size_t i = 0; i < numConfig; ++i)
	{
		if (config[i].kind != KEYWORD_KIND_PARENTHES)
			continue;

		if (chr == config[i].str[0])
		{
			open_close = MUGEN_SCRIPT_CONFIGRATION_PARENTHES_OPEN;
			return i;
		}
		if (chr == config[i].str[1])
		{
			open_close = MUGEN_SCRIPT_CONFIGRATION_PARENTHES_CLOSE;
			return i;
		}
	}
	return -1;
}

int MugenScript::TokenizerApi::IsHeader(size_type numConfig, const ConfigrateData* config, const char* str)
{
	for (size_t i = 0; i < numConfig; ++i)
	{
		if (config[i].kind != KEYWORD_KIND_HEADER)
			continue;


		if (strncmp(config[i].str, str, config[i].size) == 0)
			return i;
	}
	return -1;
}

int MugenScript::TokenizerApi::IsIndent(size_type numConfig, const ConfigrateData* config, const char* str)
{
	for (size_t i = 0; i < numConfig; ++i)
	{
		if (config[i].kind != KEYWORD_KIND_INDENT)
			continue;

		if (strncmp(config[i].str, str, config[i].size) == 0)
		{
			return i;
		}
	}
	if (strncmp("\0", str, 1) == 0)
		return -2;

	return -1;
}

MugenScript::Tree* MugenScript::MugenScriptParser::CreateTree()
{
	return new Tree;
}

MugenScript::TreeNode* MugenScript::MugenScriptParser::CreateTreeNode(int type, const char* str, size_type len)
{
	auto node = new TreeNode;
	node->type = type;
	node->str = new char[len + 1];
	node->size = len;
	strcpy_s(node->str, len + 1, str);
	return node;
}

void MugenScript::MugenScriptParser::DeleteTree(Tree* tree)
{
	delete (tree);
}

void MugenScript::MugenScriptParser::DeleteTreeNode(TreeNode* node)
{
	if (node)
	{
		if (node->str)
			delete node->str;
		delete node;
	}
}

void MugenScript::ParserStatementData::operator=(const ParserStatementData& o)
{
	kind = o.kind;
}

void MugenScript::ParserStatement::operator=(const ParserStatement& o)
{
	data = o.data;
	kind = o.kind;
}

MugenScript::MugenScriptOperand MugenScript::MugenScriptMachineCommandIO::PopStack()
{
	assert(stack);
	auto ret = stack->top();
	stack->pop();
	return ret;
}

void MugenScript::MugenScriptMachineCommandIO::PushStack(MugenScriptOperand o)
{
	assert(stack);
	stack->push(o);
}

void MugenScript::MugenScriptGeneratorEx::SetHeader(TreeNode* node)
{
	MugenScriptCommand cmd = (MugenScriptCommand)node->type;

	mode = (MugenScriptCommand)node->type;
}

void MugenScript::MugenScriptGeneratorEx::WriteHeader(MugenScriptCode* code)
{
	code[count++] = { MSM_PAGE,page++ };
}

void MugenScript::MugenScriptGeneratorEx::WriteStatement(MugenScriptCode* code)
{
	code[count++] = { MSM_PAGE,page++ };
}

void MugenScript::MugenScriptGeneratorEx::WriteTokenTypeNone(TreeNode* node, MugenScriptCode* code)
{
	if (node->type != MugenScriptCommand_String)
		return;
	MugenScriptOperand operand;
	if ('0' < node->str[0] && node->str[0] < '9')
		code[count++] = { MSM_PUSH,atoi(node->str) };
	else
		code[count++] = { MSM_PUSH,node->str };
	
}

void MugenScript::MugenScriptGeneratorEx::WriteTokenTypeArgment(TreeNode* node, MugenScriptCode* code)
{
	if (node->rhs)
		WriteTokenTypeArgment(node->rhs, code);
	if (node->lhs)
		WriteTokenTypeArgment(node->lhs, code);

	if (node->type == MugenScriptCommand_String)
		code[count++] = { MSM_PUSH,node->str };
}

MugenScript::TreeNode* MugenScript::MugenScriptGeneratorEx::GenerateCode(size_type numConfig, const ConfigrateData* config, MugenScriptCode* code, TreeNode*& node)
{
	auto genCode = [](GeneratorApi* p, size_type numConfig, const ConfigrateData* config, MugenScriptCode* code,TreeNode* node)
		{
			if (node->rhs)
				p->GenerateCode(numConfig, config, code, node->rhs);
			if (node->lhs)
				p->GenerateCode(numConfig, config, code, node->lhs);
		};


	MugenScriptCommand cmd = (MugenScriptCommand)node->type;
	switch (cmd)
	{
	case MugenScript::MugenScriptCommand_String:
		WriteTokenTypeNone(node, code);
		if (mode == MugenScriptCommand_String)
			code[count++] = { MSM_WRITE ,1 };

		break;
	case MugenScript::MugenScriptCommand_Comma:
		genCode(this, numConfig, config, code, node);
		break;
	case MugenScript::MugenScriptCommand_SharpOperator:
		GenerateCode(numConfig, config, code, node->rhs);
		break;
	case MugenScript::MugenScriptCommand_LabelOperator:
		code[count++] = { MSM_LABEL,node->rhs->str };
		break;
	case MugenScript::MugenScriptCommand_CalcOperator:
		GenerateCode(numConfig, config, code, node->rhs);
		break;
	case MugenScript::MugenScriptCommand_Puls:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_PULS,0 };
		break;
	case MugenScript::MugenScriptCommand_Minus:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_MINUS,0 };
		break;
	case MugenScript::MugenScriptCommand_PulsEqual:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_READ,0 };
		code[count++] = { MSM_PULS,0 };
		GenerateCode(numConfig, config, code, node->lhs);
		code[count++] = { MSM_STORE,0 };
		break;
	case MugenScript::MugenScriptCommand_MinusEqual:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_READ,0 };
		code[count++] = { MSM_MINUS,0 };
		GenerateCode(numConfig, config, code, node->lhs);
		code[count++] = { MSM_STORE,0 };
		break;
	case MugenScript::MugenScriptCommand_Equal:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_STORE,0 };
		break;
	case MugenScript::MugenScriptCommand_Equality:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_EQUAL,0 };
		break;
	case MugenScript::MugenScriptCommand_OR:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_OR,0 };
		break;
	case MugenScript::MugenScriptCommand_AND:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_AND,0 };
		break;
	case MugenScript::MugenScriptCommand_Greater:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_GREATER,0 };
		break;
	case MugenScript::MugenScriptCommand_Lesser:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_LESSER,0 };
		break;
	case MugenScript::MugenScriptCommand_GreaterEqual:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_GREATER_EQUAL,0 };
		break;
	case MugenScript::MugenScriptCommand_LesserEqual:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_LESSER_EQUAL,0 };
		break;
	case MugenScript::MugenScriptCommand_If:
	{
		GenerateCode(numConfig, config, code, node->rhs);
		auto branchPos = count;
		code[count++] = { MSM_BRANCH,0 };
		SetHeader(node->lhs);
		GenerateCode(numConfig, config, code, node->lhs);
		code[branchPos].operand = count;
		code[count++] = { MSM_LABEL,"end_branch" };
		break;
	}
	case MugenScript::MugenScriptCommand_Start:
		break;
	case MugenScript::MugenScriptCommand_Choise:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_REQUEST_OUTPUT_CHOISE_DEFINE,0 };

		break;
	case MugenScript::MugenScriptCommand_Select:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_REQUEST_OUTPUT_CHOISE,0 };
		break;
	case MugenScript::MugenScriptCommand_InputString:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_REQUEST_INPUT_TEXT,0 };
		break;
	case MugenScript::MugenScriptCommand_Cancel:
	{
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_REQUEST_INPUT_CHOISE_KEY,0 };
		break;
	}
	case MugenScript::MugenScriptCommand_To:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_JUMP,0 };
		break;
	case MugenScript::MugenScriptCommand_Newline:
		break;
	case MugenScript::MugenScriptCommand_Newpage:
		break;
	case MugenScript::MugenScriptCommand_SwapString:
		if (node->rhs && node->rhs->type != MugenScriptCommand_SwapString)
			GenerateCode(numConfig, config, code, node->rhs);
		else
			code[count++] = { MSM_PUSH,0 };
		code[count++] = { MSM_READ,0 };
		code[count++] = { MSM_WRITE_SAME_LINE,0 };
		break;
	case MugenScript::MugenScriptCommand_PictureFun:
		code[count++] = {MSM_PUSH,"fun"};
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE_FACIAL,0 };
		break;
	case MugenScript::MugenScriptCommand_PictureSad:
		code[count++] = { MSM_PUSH,"sad" };
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE_FACIAL,0 };
		break;
	case MugenScript::MugenScriptCommand_PictureAngry:
		code[count++] = { MSM_PUSH,"angry" };
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE_FACIAL,0 };
		break;
	case MugenScript::MugenScriptCommand_PictureHappy:
		code[count++] = { MSM_PUSH,"happy" };
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE_FACIAL,0 };
		break;
	case MugenScript::MugenScriptCommand_PictureCry:
		code[count++] = { MSM_PUSH,"cry" };
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE_FACIAL,0 };
		break;
	case MugenScript::MugenScriptCommand_PictureShock:
		code[count++] = { MSM_PUSH,"shock" };
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE_FACIAL,0 };
		break;

	case MugenScript::MugenScriptCommand_PictureBackGround:
		code[count++] = { MSM_PUSH,"back" };
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE_POS,0 };
		break;
	case MugenScript::MugenScriptCommand_PicturePosRight:
		code[count++] = { MSM_PUSH,"right" };
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE_POS,0 };
		break;
	case MugenScript::MugenScriptCommand_PicturePosLeft:
		code[count++] = { MSM_PUSH,"left" };
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE_POS,0 };
		break;
	case MugenScript::MugenScriptCommand_PicturePosCenter:
		code[count++] = { MSM_PUSH,"center" };
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE_POS,0 };
		break;

	case MugenScript::MugenScriptCommand_PictureDelete:
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE_VALISH,0 };
		break;

	case MugenScript::MugenScriptCommand_SetPicture:
	{
		auto n = node->rhs;
		while (n->type!=(MugenScriptCommand_SetPicture))
		{
			while (n->type == MugenScriptCommand_Comma)
				n = n->lhs;
			auto lhs = n->lhs;
			n->lhs = nullptr;
			GenerateCode(numConfig, config, code, n);
			n->lhs = lhs;
			n = n->lhs;
		}
		code[count++] = { MSM_REQUEST_OUTPUT_PICTURE,0 };
		break;
	}
	case MugenScript::MugenScriptCommand_SetPictureBright:
		break;
	
	case MugenScript::MugenScriptCommand_BGM:
		genCode(this, numConfig, config, code, node);
		if(code[count-1].opecode==MSM_PUSH)
			code[count++] = { MSM_REQUEST_OUTPUT_SET_BGM,0 };
		break;
	case MugenScript::MugenScriptCommand_SE:
		code[count++] = { MSM_REQUEST_OUTPUT_PLAY_SE,0 };
		break;
	case MugenScript::MugenScriptCommand_Play:
		code[count++] = { MSM_REQUEST_OUTPUT_PLAY_BGM,0 };
		break;
	case MugenScript::MugenScriptCommand_Pause:
		code[count++] = { MSM_REQUEST_OUTPUT_PAUSE_BGM,0 };
		break;
	case MugenScript::MugenScriptCommand_Stop:
		code[count++] = { MSM_REQUEST_OUTPUT_STOP_BGM,0 };
		break;
	case MugenScript::MugenScriptCommand_Auto_Start:
		code[count++] = { MSM_REQUEST_OUTPUT_AUTO_START,0 };
		break;
	case MugenScript::MugenScriptCommand_Auto_Stop:
		code[count++] = { MSM_REQUEST_OUTPUT_AUTO_STOP,0 };
		break;
	case MugenScript::MugenScriptCommand_Ending:
		break;
	case MugenScript::MugenScriptCommand_Database_Load:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_REQUEST_LOAD_DATABASE,0 };
		break;
	case MugenScript::MugenScriptCommand_Table_Load:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_REQUEST_LOAD_TABLE,0 };
		break;

	case MugenScript::MugenScriptCommand_Database_UnLoad:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_REQUEST_UNLOAD_DATABASE,0 };
		break;

	case MugenScript::MugenScriptCommand_Access:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_REQUEST_ACCESS_COLUMN,0 };
		break;

	case MugenScript::MugenScriptCommand_Relation:
		genCode(this, numConfig, config, code, node);
		code[count++] = { MSM_REQUEST_ACCESS_RELATION,0 };
		break;

	case MugenScript::MugenScriptCommand_Function:
	{
 		int preCount = count;
		int numArg = 0;
		WriteTokenTypeArgment(node->rhs, code);
		numArg = count - preCount;
		code[count++] = { MSM_PUSH,node->str };
		code[count++] = { MSM_REQUEST_ACCESS_TABLE,numArg };
		break;
	}
	case MugenScript::MugenScriptCommand_Register:
		break;
	case MugenScript::MugenScriptCommand_Number:
		break;
	case MugenScript::MugenScriptCommand_LoadScript:
		break;
	default:
		break;
	}

	return nullptr;
}

int MugenScript::MugenScriptGeneratorEx::GetNumPage()
{
	return page;
}

int MugenScript::MugenScriptGeneratorEx::GetProgSize()
{
	return count;
}

void MugenScript::MugenScriptMachineEx::Init(MugenScriptContainer::vector_t<MugenScriptMachineBehavior> behabiors, MugenScriptContainer::vector_t<MugenScriptMachineCommandIO*> commands)
{
	while (!stack.empty())
		stack.pop();

	cmdIO.clear();
	for (int i = 0; i < behabiors.size(); ++i)
		if (cmdIO.find(behabiors[i]) == cmdIO.end())
			cmdIO[behabiors[i]] = commands[i];
		else
			assert(false);

	//cmdIO[MSM_READ] = &registerIO;
	cmdIO[MSM_FUNCTION] = &registerIO;
	//cmdIO[MSM_STORE] = &registerIO;
	cmdIO[MSM_WRITE] = &writer;
	cmdIO[MSM_WRITE_SAME_LINE] = &writer;

	pc = 0;
}

void MugenScript::MugenScriptMachineEx::Read(MugenScriptCode* code, size_type size)
{

	while (pc < size)
	{
		auto& pc = this->pc;
		auto& opecode = code[pc].opecode;
		auto& operand = code[pc].operand;

		switch (opecode)
		{
		case MugenScript::MSM_NONE:
			return;
			break;

		case MugenScript::MSM_JUMP:

			pc = FindLavel(size, code, PopStack());
			page = FindPageFromPC(size, code);
			break;

		case MugenScript::MSM_JUMP_PAGE:
			SetPage(PopStack().value.ivalue, size, code);
			break;

		case MugenScript::MSM_PUSH:
			stack.push(operand);
			pc++;
			break;

		case MugenScript::MSM_POP:
			stack.pop();
			pc++;
			break;

		case MugenScript::MSM_LABEL:
			pc++;
			break;

		case MugenScript::MSM_BRANCH:
			if (!PopStack().value.ivalue)
				pc = operand.value.ivalue;
			pc++;
			break;

		case MugenScript::MSM_BRANCH_NOT:
			if (PopStack().value.ivalue)
				pc = operand.value.ivalue;
			pc++;
			break;

		case MugenScript::MSM_YIELD:
			return;
			break;

		case MugenScript::MSM_YIELD_ONE:
			pc++;
			return;
			break;

		case MugenScript::MSM_PAGE:
			return;
			break;

		case MugenScript::MSM_EQUAL:
			if (PopStack() == operand)
				PushStack(true);
			else
				PushStack(false);
			pc++;
			break;
		case MugenScript::MSM_PULS:
		{
			auto value1 = PopStack();
			auto value2 = PopStack();
			PushStack(value1 + value2);
			pc++;
			break;
		}

		case MugenScript::MSM_MINUS:
		{

			auto value1 = PopStack();
			auto value2 = PopStack();
			PushStack(value1 - value2);
			pc++;
			break;
		}

		case MugenScript::MSM_AND:
		{
			int value1 = PopStack().value.ivalue;
			int value2 = PopStack().value.ivalue;
			PushStack(value1 && value2);
			pc++;
			break;
		}


		case MugenScript::MSM_OR:
		{
			int value1 = PopStack().value.ivalue;
			int value2 = PopStack().value.ivalue;
			PushStack(value1 || value2);
			pc++;
			break;
		}

		case MugenScript::MSM_GREATER:
		{
			int value1 = PopStack().value.ivalue;
			int value2 = PopStack().value.ivalue;
			PushStack(value1 < value2);
			pc++;
			break;
		}

		case MugenScript::MSM_GREATER_EQUAL:
		{
			int value1 = PopStack().value.ivalue;
			int value2 = PopStack().value.ivalue;
			PushStack(value1 <= value2);
			pc++;
			break;
		}

		case MugenScript::MSM_LESSER:
		{
			int value1 = PopStack().value.ivalue;
			int value2 = PopStack().value.ivalue;
			PushStack(value1 >= value2);
			pc++;
			break;
		}

		case MugenScript::MSM_LESSER_EQUAL:
		{
			int value1 = PopStack().value.ivalue;
			int value2 = PopStack().value.ivalue;
			PushStack(value1 >= value2);
			pc++;
			break;
		}
		case MugenScript::MSM_READ:
		case MugenScript::MSM_FUNCTION:
		case MugenScript::MSM_WRITE:
		case MugenScript::MSM_WRITE_SAME_LINE:
		case MugenScript::MSM_STORE:
		case MugenScript::MSM_REQUEST_INPUT_TEXT:
		case MugenScript::MSM_REQUEST_INPUT_CHOISE_KEY:
		case MugenScript::MSM_REQUEST_INPUT_VALUE:
		case MugenScript::MSM_REQUEST_INPUT_LINK_REGISTER:
		case MugenScript::MSM_REQUEST_OUTPUT_TEXT:
		case MugenScript::MSM_REQUEST_OUTPUT_VALUE:
		case MugenScript::MSM_REQUEST_OUTPUT_PICTURE:
		case MugenScript::MSM_REQUEST_OUTPUT_PICTURE_POS:
		case MugenScript::MSM_REQUEST_OUTPUT_PICTURE_BRIGHT:
		case MugenScript::MSM_REQUEST_OUTPUT_PICTURE_VALISH:
		case MugenScript::MSM_REQUEST_OUTPUT_SOUND:
		case MugenScript::MSM_REQUEST_OUTPUT_SET_BGM:
		case MugenScript::MSM_REQUEST_OUTPUT_PLAY_BGM:
		case MugenScript::MSM_REQUEST_OUTPUT_PAUSE_BGM:
		case MugenScript::MSM_REQUEST_OUTPUT_STOP_BGM:
		case MugenScript::MSM_REQUEST_OUTPUT_PLAY_SE:
		case MugenScript::MSM_REQUEST_OUTPUT_AUTO_START:
		case MugenScript::MSM_REQUEST_OUTPUT_AUTO_STOP:
		case MugenScript::MSM_REQUEST_OUTPUT_CHOISE:
		case MugenScript::MSM_REQUEST_OUTPUT_CHOISE_DEFINE:
		case MugenScript::MSM_REQUEST_LOAD_DATABASE:
		case MugenScript::MSM_REQUEST_LOAD_SCRIPT:
		case MugenScript::MSM_REQUEST_LOAD_TABLE:
		case MugenScript::MSM_REQUEST_UNLOAD_DATABASE:
		case MugenScript::MSM_REQUEST_ACCESS_TABLE:
		case MugenScript::MSM_REQUEST_ACCESS_RELATION:
		case MugenScript::MSM_REQUEST_ACCESS_COLUMN:
			RequestIO(opecode, operand);
			pc++;
			break;


		default:
			assert(false);
			break;
		}
	}
}

void MugenScript::MugenScriptMachineEx::SetPage(int numberPage, size_type progSize, MugenScriptCode* code)
{
	for (int i = 0; i < progSize; ++i)
		if (code[i].opecode == MSM_PAGE && code[i].operand.value.ivalue == numberPage)
		{
			pc = i + 1;
			page = numberPage;
			break;
		}
}

void MugenScript::MugenScriptMachineEx::SetLavel(MugenScriptContainer::string_t label, size_type progSize, MugenScriptCode* code)
{
	for (int i = 0; i < progSize; ++i)
		if (code[i].opecode == MSM_LABEL && label==code[i].operand.value.str)
		{
			pc = i;
			page = FindPageFromPC(progSize, code);
			break;
		}
}

int MugenScript::MugenScriptMachineEx::GetCurrentPage()
{
	return page;
}

int MugenScript::MugenScriptMachineEx::GetCurrentPC()
{
	return pc;
}

MugenScriptContainer::stack_t<MugenScript::MugenScriptMachineEx::StackType>* MugenScript::MugenScriptMachineEx::GetStack()
{
	return &stack;
}

MugenScript::MugenScriptCommandWriter* MugenScript::MugenScriptMachineEx::GetWriter()
{
	return &writer;
}

MugenScript::MugenScriptCommandRegisterIO* MugenScript::MugenScriptMachineEx::GetRegisterIO()
{
	return &registerIO;
}

void MugenScript::MugenScriptMachineEx::EndScript()
{
	for (auto& n : cmdIO)
		if (n.second)
			n.second->EndScript();
}

MugenScript::MugenScriptMachineEx::MugenScriptMachineEx():
	cmdIO(),
	stack(),
	writer(&stack),
	registerIO(&stack),
	pc(),
	page()
{
}

void MugenScript::MugenScriptMachineEx::PushStack(StackType o)
{
	stack.push(o);
}

MugenScript::MugenScriptMachineEx::StackType MugenScript::MugenScriptMachineEx::PopStack()
{
	auto ret = stack.top();
	stack.pop();
	return ret;
}

int MugenScript::MugenScriptMachineEx::FindPageFromPC(size_type size, MugenScriptCode* code)
{
	int ret = -1;
	for (int i = 0; i < pc; ++i)
	{
		if (code[i].opecode == MSM_PAGE)
			ret = code[i].operand.value.ivalue;
	}
	return ret;
}

int MugenScript::MugenScriptMachineEx::FindLavel(size_type size,MugenScriptCode* code,MugenScriptOperand operand)
{
	for (size_type i = 0; i < size; ++i)
		if (code[i].opecode == MSM_LABEL && code[i].operand == operand)
			return i;
	assert(false);
	return -1;
}

void MugenScript::MugenScriptMachineEx::RequestIO(MugenScriptMachineBehavior opecode, MugenScriptOperand operand)
{
	auto reg = cmdIO[opecode];
	if (reg)
		reg->Execute(opecode,operand);
}

void MugenScript::MugenScriptCode::operator=(const MugenScriptCode& o)
{
	opecode = o.opecode;
	operand = o.operand;
}

void MugenScript::MugenScriptCode::operator=(MugenScriptCode&& o)
{
	opecode = std::move(o.opecode);
	operand = std::move(o.operand);
}

MugenScript::MugenScriptCode::MugenScriptCode(const MugenScriptCode& o)
{
	*this = o;
}

MugenScript::MugenScriptCode::MugenScriptCode(MugenScriptCode&& o)
{
	*this = std::move(o);
}

void MugenScript::MugenScriptCommandWriter::Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)
{
	auto data = PopStack();
	MugenScriptContainer::string_t str;
	switch (opecode)
	{
	case MugenScript::MSM_WRITE:
		str += data.value.str;
		str += '\n';
		break;
	case MugenScript::MSM_WRITE_SAME_LINE:
	{
		if (!strQueue.empty())
			strQueue.back().pop_back();
		auto type = data.tag;
		switch (type)
		{
		case MugenScript::MSM_TAG_INT:
			str += std::to_string(data.value.ivalue);
			break;
		case MugenScript::MSM_TAG_DBL:
			str += std::to_string(data.value.dvalue);
			break;
		case MugenScript::MSM_TAG_STRING:

			if (data.value.str)
				str += data.value.str;
			else
				str += "";
			break;
		default:
			break;
		}
	}
	default:
		break;
	}
	strQueue.push_back(str);
}

MugenScriptContainer::string_t MugenScript::MugenScriptCommandWriter::PopString()
{
	auto str = strQueue.front();
	strQueue.pop_front();
	return str;
}

bool MugenScript::MugenScriptCommandWriter::Empty()
{
	return strQueue.empty();
}

void MugenScript::MugenScriptCommandWriter::Clear()
{
	while (!strQueue.empty())
		strQueue.pop_front();
}

void MugenScript::MugenScriptCommandRegisterIO::Execute(MugenScriptMachineBehavior opecode, MugenScriptOperand& operand)
{
	switch (opecode)
	{
	case MugenScript::MSM_READ:
	{
		auto name = PopStack();
		if (name.value.str)
		{
			auto& val = registerMap[name.value.str];
			PushStack(val);
		}
		else
		{
			PushStack(registerMap[""]);
		}
		break;
	}
	case MugenScript::MSM_FUNCTION:
	{
		MugenScriptContainer::string_t regName;
		auto numArg = operand.value.ivalue;
		auto name = PopStack();
		regName = name.value.str;
		for (int i = 0; i < numArg; ++i)
			regName += PopStack().value.str;
		PushStack(regName.c_str());
		break;
	}
	case MugenScript::MSM_STORE:
	{
		auto& lhs = registerMap[PopStack().value.str];
		lhs = PopStack();
		break;
	}
	default:
		break;
	}
}

void MugenScript::MugenScriptCommandRegisterIO::SetRegister(MugenScriptContainer::string_t name, MugenScriptOperand operand)
{
	registerMap[name] = operand;
}

void MugenScript::MugenScriptCommandRegisterIO::SetRegisterParam(MugenScriptContainer::string_t param, MugenScriptContainer::string_t charactor, MugenScriptOperand operand)
{
	registerMap[param + charactor] = operand;
}

MugenScript::MugenScriptOperand MugenScript::MugenScriptCommandRegisterIO::GetRegister(MugenScriptContainer::string_t name)
{
	return registerMap[name];
}
