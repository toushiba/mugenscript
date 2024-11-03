#pragma once
#include <string>
#include <fstream>
#include "common/Container.h"
#include "common/String.h"
#include "MugenScriptDatabase.h"

namespace MugenScriptDatabase
{
	enum DATABASE_VALUE_TYPE_SLAVE
	{
		DATABASE_VALUE_TYPE_SLAVE_INT,
		DATABASE_VALUE_TYPE_SLAVE_DBL,
		DATABASE_VALUE_TYPE_SLAVE_STR,
	};



	class MugenScriptDatabaseValueSlave
	{
	public:
		struct Relation
		{
			int id;
		};

		union TableValue
		{
			int ivalue;
			double dvalue;
			char* string;
			Relation relation;
			TableValue(int i) :ivalue(i) {}
			TableValue(double d) :dvalue(d) {}
			TableValue(char* s) :string(s) {}
			TableValue(Relation r) :relation(r) {}
			TableValue() :dvalue() {}
			~TableValue() {}
		};

		TableValue value;
		DATABASE_VALUE_TYPE_SLAVE type;

		void operator=(const MugenScriptDatabaseValueSlave&);
		void operator=(MugenScriptDatabaseValueSlave&&);
		int size()const;
		MugenScriptDatabaseValueSlave() :value(0.0), type(DATABASE_VALUE_TYPE_SLAVE_INT) {}
		MugenScriptDatabaseValueSlave(int ivalue) :value(ivalue), type(DATABASE_VALUE_TYPE_SLAVE_INT) {};
		MugenScriptDatabaseValueSlave(double dvalue) :value(dvalue), type(DATABASE_VALUE_TYPE_SLAVE_DBL) {};
		MugenScriptDatabaseValueSlave(const char* string);
		MugenScriptDatabaseValueSlave(const MugenScriptDatabaseValueSlave&);
		MugenScriptDatabaseValueSlave(MugenScriptDatabaseValueSlave&&);
		~MugenScriptDatabaseValueSlave();

	private:
	};
	class MugenScriptDatabaseTableDataMemWriterReaderSlave
	{
	public:
		int WriteValue(char* dst, int buffDst, const MugenScriptDatabaseValueSlave* value)const;
		const char* ReadValue(DATABASE_VALUE_TYPE_SLAVE type, MugenScriptDatabaseValueSlave& dst, const char* src)const;
	private:
		char* WriteMem(char* dst, int buffDst, const void* src, int size)const;
	};


	struct MugenScriptDatabaseProperty
	{
		int size;
		int startMap;
		int mapSize;
		int numRecord;
		int idColumn;
		DATABASE_VALUE_TYPE_SLAVE idType;
	};

	class MugenScriptDatabaseLoader
	{
	public:

		struct RecordData
		{
			char* name;
			int recordPos;
			bool operator<(const RecordData& o)const;
			bool operator>(const RecordData& o)const;
			bool operator<=(const RecordData& o)const;
			bool operator>=(const RecordData& o)const;
			bool operator==(const RecordData& o)const;
			void operator=(const RecordData& o);
			void operator=(RecordData&& o);
			~RecordData();
		};

		void LoadDatabase(const char* databaseName);
		void LoadTable(const char* tableName);
		void LoadValue(const char* tableName,const char* row,const char* column, void* dst);
	private:
		std::fstream file;
		Mugenshuen::btree_t<RecordData> recordMap;
		MugenScript::MugenScriptDatabaseEditor editor;
		Mugenshuen::vector_t<MugenScript::MugenScriptDatabaseEditor::table_t*> table;
	};
}