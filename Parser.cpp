#include "Imports.cpp"
#include "FileHandler.cpp"
#include "Printer.cpp"

class CounterRetainer {

protected:

	string* countersArr = nullptr;
	int countersSize = 7;

public:

	int getCountersSize() {
		return this->countersSize;
	}

	void countersArrCreate() {
		delete[] this->countersArr;
		this->countersArr = new string[this->countersSize];
	}

	string getCountersValues(FileHandler& handlingFile) {
		return handlingFile.inputFromFile("HistoryCounters.txt");
	}

	void setCountersValues(string countersValues) {
		cout << "setCountersValues ENTERED" << endl;
		int j = 0;
		const char comparisonSpace = ' ';
		string tempVal = "";

		for (unsigned int i = 0; i < countersValues.length(); i++) {
			if (countersValues[i] == comparisonSpace) {
				this->countersArr[j] = tempVal;
				tempVal = "";
				j++;
			}
			else tempVal += countersValues[i];
		}
		cout << endl << endl << endl;

		cout << "CountersTable: " << countersValues << endl;
		// cout << "CountersSize: " << this->countersSize << endl;
		cout << "The counters values are: ";
		for (int z = 0; z < j; z++) cout << this->countersArr[z] << " ";
		cout << endl;
	}

	void LogicCountersArrayStorage(FileHandler& handlingFile) {
		countersArrCreate();
		string countersValues = handlingFile.inputFromFile("HistoryCounters.txt");
		cout << "LogicCountersArrayStorage: " << countersValues << endl;
		setCountersValues(countersValues);
	}

	void dataSaver(FileHandler& handlingFile) {
		// Calling for historyCounters array

		handlingFile.suprascriptionTable(this->countersArr, "HistoryCounters", getCountersSize());
		cout << "Data SAVED" << endl;
	}

	void dataReloader(FileHandler& handlingFile) {

		LogicCountersArrayStorage(handlingFile);
		cout << "Data RELOADED" << endl;

	}
};


class CreateTable : public CounterRetainer
{
	// atoi(countersArr[0].c_str())
	static int CREATE_COUNTER;

public:

	/*CreateTable(string* countersArr): CounterRetainer(string* countersArr) {
		this->CREATE_COUNTER = countersArr[0];
		cout << "HELLO -> CREATE CLASS ENTERED" << endl;
		cout << countersArr[0] << endl;
	}*/

	bool testCreateTable(string const input) {
		bool createTable = regex_match(input.c_str(), regex("[[:blank:]]*create[[:blank:]]+table[[:blank:]]+(?!table)\\w+[[:blank:]]*(if[[:blank:]]+not[[:blank:]]+exists[[:blank:]]*)?(\\([[:blank:]]*(\\(\\s*\\w+\\s*,\\s*((integer)|(text)|(float))\\s*,\\s*[0-9]+\\s*,\\s*(('[0-9_a-z]+')|('[0-9]+.[0-9]+')|([0-9]+.[0-9]+)|(\")|([0-9]+))\\s*\\))(\\s*,\\s*\\(\\s*\\w+\\s*,\\s*((integer)|(text)|(float))\\s*,\\s*[0-9]+\\s*,\\s*(('[0-9_a-z]+')|('[0-9]+\\.[0-9]+')|([0-9]+\\.[0-9]+)|(\")|([0-9]+))\\s*\\))+\\))|[[:blank:]]*create[[:blank:]]+table[[:blank:]]+(?!table)\\w+[[:blank:]]*(if[[:blank:]]+not[[:blank:]]+exists[[:blank:]]*)?[[:blank:]]*(\\(\\s*\\w+\\s*,\\s*((integer)|(text)|(float))\\s*,\\s*[0-9]+\\s*,\\s*(('[0-9_a-z]+')|('[0-9]+\\.[0-9]+')|([0-9]+\\.[0-9]+)|(\")|([0-9]+))\\s*\\))[[:blank:]]*"));
		return createTable;
	}

	int returnCounterCreate() {
		return this->CREATE_COUNTER;
	}

	void SET_CREATE_COUNTER(int value) {
		this->CREATE_COUNTER = value;
	}
};

class DropTable : public CounterRetainer
{
	static int DROP_COUNTER;

public:

	bool testDropTable(string const input) {
		bool dropTable = regex_match(input.c_str(), regex("[[:blank:]]*drop[[:blank:]]+table[[:blank:]]+\\w+[[:blank:]]*"));
		return dropTable;
	}

	int returnCounterDrop() {
		return this->DROP_COUNTER;
	}

	void SET_DROP_COUNTER(int value) {
		this->DROP_COUNTER = value;
	}
};

class Select : public CounterRetainer
{
	static int SELECT_COUNTER;

public:
	bool testSelect(string const input)
	{
		bool selectColumns = regex_match(input.c_str(), regex("[[:blank:]]*select+[[:blank:]]+((all)|(\\((?!all)([^)]+)\\)))[[:blank:]]+from[[:blank:]]+(?!where)\\w+([[:blank:]]+(where(?!where)[[:blank:]]+\\w+[[:blank:]]*=[[:blank:]]*(([0-9]+\\.[0-9]+)|([0-9]+)|(\"(\\w*)\"))))?[[:blank:]]*"));
		return selectColumns;
	}

	int returnCounterSelect() {
		return this->SELECT_COUNTER;
	}

	void SET_SELECT_COUNTER(int value) {
		this->SELECT_COUNTER = value;
	}
};

class DisplayTable : public CounterRetainer
{
	static int DISPLAY_COUNTER;

public:
	bool testDisplayTable(string const input)
	{
		bool displayTable = regex_match(input.c_str(), regex("[[:blank:]]*display[[:blank:]]+table[[:blank:]]+\\w+[[:blank:]]*"));
		return displayTable;
	}

	int returnCounterDisplay() {
		return this->DISPLAY_COUNTER;
	}

	void SET_DISPLAY_COUNTER(int value) {
		this->DISPLAY_COUNTER = value;
	}
};

class DeleteTable : public CounterRetainer
{
	static int DELETE_COUNTER;

public:
	bool testDeleteTable(string const input)
	{
		bool deleteTable = regex_match(input.c_str(), regex("[[:blank:]]*delete[[:blank:]]+from[[:blank:]]+\\w+[[:blank:]]+where[[:blank:]]+\\w+[[:blank:]]*=[[:blank:]]*((\"\\w+\"|([0-9]+\\.[0-9]+)|[0-9]+))[[:blank:]]*"));
		return deleteTable;
	}

	int returnCounterDelete() {
		return this->DELETE_COUNTER;
	}

	void SET_DELETE_COUNTER(int value) {
		this->DELETE_COUNTER = value;
	}
};

class UpdateTable : public CounterRetainer
{
	static int UPDATE_COUNTER;

public:
	bool testUpdateTable(string const input)
	{
		bool updateTable = regex_match(input.c_str(), regex("[[:blank:]]*update[[:blank:]]+\\w+[[:blank:]]+set[[:blank:]]+\\w+[[:blank:]]*=[[:blank:]]*((\"\\w+\"|[0-9]+))[[:blank:]]+where[[:blank:]]+\\w+[[:blank:]]*=[[:blank:]]*((\"\\w+\"|([0-9]+\\.[0-9]+)|[0-9]+))[[:blank:]]*"));
		return updateTable;
	}

	int returnCounterUpdate() {
		return this->UPDATE_COUNTER;
	}

	void SET_UPDATE_COUNTER(int value) {
		this->UPDATE_COUNTER = value;
	}
};

class Insert : public CounterRetainer
{
	static int INSERT_COUNTER;

public:
	bool InsertIntoTable(string const input)
	{
		bool insertIntoTable = regex_match(input.c_str(), regex("[[:blank:]]*insert[[:blank:]]+into[[:blank:]]+\\w+[[:blank:]]+values[[:blank:]]*\\(\\s*((\"\\w+\"|([0-9]+\\.[0-9]+)|([0-9]+))\\s*,\\s*(\"\\w+\"|([0-9]+\\.[0-9]+)|([0-9]+))*)*\\s*,\\s*((\"\\w+\")|([0-9]+\\.[0-9]+)|[0-9]+)\\s*\\)[[:blank:]]*"));
		return insertIntoTable;
	}

	int returnCounterInsert() {
		return this->INSERT_COUNTER;
	}

	void SET_INSERT_COUNTER(int value) {
		this->INSERT_COUNTER = value;
	}

};

 int CreateTable::CREATE_COUNTER = 0;
 int DropTable::DROP_COUNTER = 0;
 int Select::SELECT_COUNTER = 0;

 int DisplayTable::DISPLAY_COUNTER = 0;
 int DeleteTable::DELETE_COUNTER = 0;
 int UpdateTable::UPDATE_COUNTER = 0;
 int Insert::INSERT_COUNTER = 0;


class Parser {
public:
	// The method returns the first given input word
	string getFirstInputElement(string input) {
		unsigned int i = 0;
		string word = "";

		for (i; i < input.length(); i++) if (input[i] != ' ') break;
		for (unsigned int index = i; i < input.length(); i++) {
			if (input[i] == ' ') break;
			word += input[i];
		}
		return word;
	}

	// The method returns the input given to lowercase
	string lowerCaseInput(string input) {
		return formatInput(input);
	}

	// The method formats the input given to lowercase
	string formatInput(string input) {
		for (unsigned int i = 0; input[i] != '\0'; i++) if (input[i] >= 'A' && input[i] <= 'Z') input[i] = input[i] + 32;
		return input;
	}
	
	// The method checks for correctness of input syntax
	void parse(string cleanInput) {

		cout << endl << "PARSER PHASE ENTERED." << endl;

		CounterRetainer counterRetainer = CounterRetainer();
		Printer printer = Printer();
		FileHandler fileHandle = FileHandler();

		// counterRetainer.dataReloader(fileHandle);

		CreateTable createTable = CreateTable();
		DropTable dropTable = DropTable();
		Select selectTable = Select();
		DisplayTable displayTable = DisplayTable();
		DeleteTable deleteTable = DeleteTable();
		UpdateTable updateTable = UpdateTable();
		Insert insertTable = Insert();
		
		bool createCheck = createTable.testCreateTable(cleanInput);

		if (createCheck) {
			int counter = createTable.returnCounterCreate() + 1;
			fileHandle.createHistoryFile(getFirstInputElement(cleanInput), cleanInput, counter);
			
			createTable.SET_CREATE_COUNTER(counter);
			printer.returnStatement(1);
		}

		bool dropCheck = dropTable.testDropTable(cleanInput);

		if (dropCheck) {
			int counter = dropTable.returnCounterDrop() + 1;
			fileHandle.createHistoryFile(getFirstInputElement(cleanInput), cleanInput, counter);
			
			dropTable.SET_DROP_COUNTER(counter);
			printer.returnStatement(2);
		}

		bool selectCheck = selectTable.testSelect(cleanInput);

		if (selectCheck) {
			int counter = selectTable.returnCounterSelect() + 1;
			fileHandle.createHistoryFile(getFirstInputElement(cleanInput), cleanInput, counter);
			
			selectTable.SET_SELECT_COUNTER(counter);
			printer.returnStatement(3);
		}

		bool displayCheck = displayTable.testDisplayTable(cleanInput);

		if (displayCheck) {
			int counter = displayTable.returnCounterDisplay() + 1;
			fileHandle.createHistoryFile(getFirstInputElement(cleanInput), cleanInput, counter);
			
			displayTable.SET_DISPLAY_COUNTER(counter);
			printer.returnStatement(4);
		}

		bool deleteCheck = deleteTable.testDeleteTable(cleanInput);

		if (deleteCheck) {
			int counter = deleteTable.returnCounterDelete() + 1;
			fileHandle.createHistoryFile(getFirstInputElement(cleanInput), cleanInput, counter);
			
			deleteTable.SET_DELETE_COUNTER(counter);
			printer.returnStatement(5);
		}

		bool updateCheck = updateTable.testUpdateTable(cleanInput);

		if (updateCheck) {
			int counter = updateTable.returnCounterUpdate() + 1;
			fileHandle.createHistoryFile(getFirstInputElement(cleanInput), cleanInput, counter);
			
			updateTable.SET_UPDATE_COUNTER(counter);
			printer.returnStatement(6);
		}

		bool insertCheck = insertTable.InsertIntoTable(cleanInput);

		if (insertCheck) {
			int counter = insertTable.returnCounterInsert() + 1;
			fileHandle.createHistoryFile(getFirstInputElement(cleanInput), cleanInput, counter);

			insertTable.SET_INSERT_COUNTER(counter);
			printer.returnStatement(7);
		}
		// counterRetainer.dataSaver(fileHandle);

		if (!(createCheck || dropCheck || selectCheck || displayCheck || deleteCheck || updateCheck || insertCheck)) throw  "Syntax error.";
		else cout << endl << "Parsing phase passed!" << endl << endl;
	}

	~Parser() {}
};