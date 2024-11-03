#include "MugenScriptDatabaseLoader.h"
#include "common/FileSystem.h"

void MugenScriptDatabase::MugenScriptDatabaseValueSlave::operator=(const MugenScriptDatabaseValueSlave& value)
{
	if (type == DATABASE_VALUE_TYPE_SLAVE_STR && this->value.string)
	{
		delete[] this->value.string;
		this->value.string = nullptr;
	}
	type = value.type;
	switch (type)
	{
	case DATABASE_VALUE_TYPE_SLAVE_INT:
		this->value.ivalue = value.value.ivalue;
		break;
	case DATABASE_VALUE_TYPE_SLAVE_DBL:
		this->value.dvalue = value.value.dvalue;
		break;
	case DATABASE_VALUE_TYPE_SLAVE_STR:
	{
		if (!value.value.string)
			return;
		auto len = strlen(value.value.string) + 1;
		this->value.string = new char[len];
		strcpy_s(this->value.string, len, value.value.string);
		break;
	}
	default:
		break;
	}
}

void MugenScriptDatabase::MugenScriptDatabaseValueSlave::operator=(MugenScriptDatabaseValueSlave&& value)
{
	memcpy_s(&this->value, sizeof(TableValue) + 1, &value.value, sizeof(TableValue));
	memset(&value.value, 0, sizeof(TableValue));
	type = value.type;
	value.type = DATABASE_VALUE_TYPE_SLAVE_INT;
}

int MugenScriptDatabase::MugenScriptDatabaseValueSlave::size() const
{
	switch (type)
	{
	case DATABASE_VALUE_TYPE_SLAVE_INT:
		return sizeof(int);
		break;
	case DATABASE_VALUE_TYPE_SLAVE_DBL:
		return sizeof(double);
		break;
	case DATABASE_VALUE_TYPE_SLAVE_STR:
		return strlen(value.string) + 1;
		break;
	default:
		break;
	}
	return -1;
}

MugenScriptDatabase::MugenScriptDatabaseValueSlave::MugenScriptDatabaseValueSlave(const char* string) :type(DATABASE_VALUE_TYPE_SLAVE_STR), value()
{
	auto len = strlen(string) + 1;
	this->value.string = new char[len];
	strcpy_s(this->value.string, len, string);
}

MugenScriptDatabase::MugenScriptDatabaseValueSlave::MugenScriptDatabaseValueSlave(const MugenScriptDatabaseValueSlave& o)
{
	*this = o;
}

MugenScriptDatabase::MugenScriptDatabaseValueSlave::MugenScriptDatabaseValueSlave(MugenScriptDatabaseValueSlave&& o)
{
	*this = std::move(o);
}

MugenScriptDatabase::MugenScriptDatabaseValueSlave::~MugenScriptDatabaseValueSlave()
{
	if (type == DATABASE_VALUE_TYPE_SLAVE_STR && value.string)
		delete[] value.string;
}

int MugenScriptDatabase::MugenScriptDatabaseTableDataMemWriterReaderSlave::WriteValue(char* dst, int buffDst, const MugenScriptDatabaseValueSlave* value) const
{
	auto type = value->type;
	char* write = dst;
	int size = 0;
	switch (type)
	{
	case DATABASE_VALUE_TYPE_SLAVE_INT:
		write = WriteMem(write, buffDst, &value->value.ivalue, sizeof(int));
		size = value->size();
		break;
	case DATABASE_VALUE_TYPE_SLAVE_DBL:
		write = WriteMem(write, buffDst, &value->value.dvalue, sizeof(double));
		size = value->size();
		break;
	case DATABASE_VALUE_TYPE_SLAVE_STR:
	{
		int len = value->size();
		if (value->value.string)
			write = WriteMem(write, buffDst, value->value.string, len);
		size = len;
		break;
	}
	default:
		break;
	}

	return size;
}

const char* MugenScriptDatabase::MugenScriptDatabaseTableDataMemWriterReaderSlave::ReadValue(DATABASE_VALUE_TYPE_SLAVE type, MugenScriptDatabaseValueSlave& dst, const char* src) const
{
	int size = 0;
	switch (type)
	{
	case DATABASE_VALUE_TYPE_SLAVE_INT:
		dst = *(int*)src;
		size = sizeof(int);
		break;
	case DATABASE_VALUE_TYPE_SLAVE_DBL:
		dst = *(double*)src;
		size = sizeof(double);
		break;
	case DATABASE_VALUE_TYPE_SLAVE_STR:
	{
		int len = strlen(src) + 1;
		dst = (const char*)src;
		size = len;
		break;
	}
	default:
		break;
	}

	return &src[size];
}

char* MugenScriptDatabase::MugenScriptDatabaseTableDataMemWriterReaderSlave::WriteMem(char* dst, int buffDst, const void* src, int size) const
{
	memcpy_s(dst, buffDst, src, size);
	return &((char*)dst)[size];
}


bool MugenScriptDatabase::MugenScriptDatabaseLoader::RecordData::operator<(const RecordData& o) const
{
	return strcmp(name, o.name) < 0;
}

bool MugenScriptDatabase::MugenScriptDatabaseLoader::RecordData::operator>(const RecordData& o) const
{
	return strcmp(name, o.name) > 0;
}

bool MugenScriptDatabase::MugenScriptDatabaseLoader::RecordData::operator<=(const RecordData& o) const
{
	return strcmp(name, o.name) <= 0;
}

bool MugenScriptDatabase::MugenScriptDatabaseLoader::RecordData::operator>=(const RecordData& o) const
{
	return strcmp(name, o.name) >= 0;
}

bool MugenScriptDatabase::MugenScriptDatabaseLoader::RecordData::operator==(const RecordData& o) const
{
	return strcmp(name, o.name) == 0;
}

void MugenScriptDatabase::MugenScriptDatabaseLoader::RecordData::operator=(const RecordData& o)
{
	if (name)
		delete[] name;
	auto len = strlen(o.name);
	name = new char[len+1];
	strcpy_s(name, len + 1, o.name);
	recordPos = o.recordPos;
}

void MugenScriptDatabase::MugenScriptDatabaseLoader::RecordData::operator=(RecordData&& o)
{
	name = o.name;
	recordPos = o.recordPos;
	o.name = nullptr;
	o.recordPos = 0;
}

MugenScriptDatabase::MugenScriptDatabaseLoader::RecordData::~RecordData()
{
	if (name)
		delete[]name;
}

void MugenScriptDatabase::MugenScriptDatabaseLoader::LoadDatabase(const char* databaseName)
{
	editor.LoadDatabase(databaseName);
}

void MugenScriptDatabase::MugenScriptDatabaseLoader::LoadTable(const char* tableName)
{
	auto tbl = editor.LoadTable(tableName);
	if(tbl)
		table.push_back(tbl);
}

void MugenScriptDatabase::MugenScriptDatabaseLoader::LoadValue(const char* tableName, const char* row, const char* column, void* dst)
{
	for (int i = 0; i < table.size(); ++i)
	{
		//if (table[i]->Name() == tableName)
		//	table[i]->ReadRelational();
	}

}
