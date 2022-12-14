#pragma once
#pragma warning ( disable : 4018 )

#include "Imports.cpp"
#include "FileHandler.cpp"

class LogicHandler {
protected:

	string* tableNames = nullptr;
	int tableSize = 0;

	string* currentArr = nullptr;
	int currentSize = 0;

public:

	LogicHandler() {

	}

	LogicHandler() {

	}

	// The method removes spaces from the given input
	string removeSpaces(string input) {
		char comparison = ' ';
		string removeSpacesArr = "";
		int startingIndex = 0;

		for (unsigned int i = 0; i < input.length() + 1; i++) {
			if (input[i] != comparison) {
				startingIndex = i;
				break;
			}
		}
		for (unsigned int i = startingIndex; i < input.length() + 1; i++) {
			if (input[i] != comparison) removeSpacesArr += input[i];
			else {
				if (i == input.length() + 1) break;
				if (input[i - 1] != ',' && input[i - 1] != '(' && input[i + 1] != ',' && input[i + 1] != ')') {
					if (input[i] == comparison && input[i + 1] != comparison) removeSpacesArr += input[i];
				}
			}
		}

		input = comparison = startingIndex = NULL;
		return removeSpacesArr;
	}

	// The method find the size of a given input
	int sizeDiscovery(string input) {
		int size = 0;

		for (unsigned int i = 0; i < input.length() + 1; i++) {
			if (input[i] == ' ' || input[i] == ',') size++;
		}

		return size;
	}

	// The method creates a dynamic size current array
	void currentArrCreate(int size) {
		if (this->currentArr != nullptr) {
			delete[] this->currentArr;
			this->currentArr = nullptr;
		}
		this->currentArr = new string[size];
	}

	// The method sets the current array values
	void setCurrentArr(string input) {
		int j = 0;
		string tempStr = "";

		for (unsigned int i = 0; i < input.length() - 1; i++) {
			if (input[i] != '(' && input[i] != ')') {
				if (input[i] == ' ' || input[i] == ',') {
					this->currentArr[j] = tempStr;
					tempStr = "";
					j++;
				}
				else tempStr += input[i];
			}
		}
		this->currentArr[j] = tempStr;
	}
	string stringToUpper(string input)
	{
		string response = "";
		for (unsigned int i = 0; i < input.length(); i++)
		{
			if (input[i] >= 'a' && input[i] <= 'z')response += (input[i] - 32);
			else response += input[i];
		}
		return response;
	}


	// The method finds the table name
	string findTableName(int size) {
		string tableName = "";
		string firstCheck = stringToUpper(currentArr[0]);

		if ((firstCheck) == "SELECT") 
		{
		for (int i = 0; i < size; i++) {
			string secondCheck = stringToUpper(this->currentArr[i]);
			if (secondCheck == "FROM") {
				tableName = this->currentArr[i + 1];
			      }
		    }
	    }
		
		else if (firstCheck == "UPDATE" || firstCheck =="IMPORT") tableName = this->currentArr[1];
		else tableName = this->currentArr[2];
		return tableName;
	}

	// The method gets the table name
	string getTableName() {
		return findTableName(getCurrentArrSize());
	}

	// The method gets the current array size
	int getCurrentArrSize() {
		return this->currentSize;
	}

	// The method creates a dynamic current array with the given input values words on each index position							-> Main method
	void LogicCurrentArrayModifier(string input) {
		cout << endl << "LOGIC PHASE ENTERED." << endl;

		// Input cleaning and size finding of currentArr

		string RemoveSpacesFromInput = removeSpaces(input);
		this->currentSize = sizeDiscovery(RemoveSpacesFromInput) + 1;
		
		// Setting the array

		currentArrCreate(this->currentSize);
		setCurrentArr(RemoveSpacesFromInput);

		// Printing part
		cout << "\tThe table name is: " << getTableName() << endl;
		cout << "\tCurrentArray Formed! It is:  ";
		for (int i = 0; i < this->currentSize; i++) cout << this->currentArr[i] << " ";
		cout << endl;
	}



	// The method returns the size of table names
	int getTableSize() {
		return this->tableSize;
	}
	
	 bool checkTabelExists(string tableName)
	 {
		
		for (int i = 0; i < getTableSize(); i++)
		{
			if (this->tableNames[i] == tableName)
				return true;
		}
		return false;


	}

	// The method gets all the table names in the project
	string getTableNames(FileHandler& handlingFile) {
		return handlingFile.inputFromFile("TableNames.txt");
	}

	// The method find the size of the table names
	void setTableNamesSize(FileHandler& handlingFile, string tableNames) {

		this->tableSize = 0;
		const char comparisonSpace = ' ';

		for (unsigned int i = 0; i < tableNames.length(); i++) {
			if (tableNames[i] == comparisonSpace) this->tableSize++;
		}
	}

	// The method creates a dynamic size current array
	void tableNameArrCreate() {
		delete[] this->tableNames;
		this->tableNames = new string[getTableSize()];
	}

	// The method sets the tableNames array values
	void setTableNames(string tableNames) {
		int j = 0;
		const char comparisonSpace = ' ';
		string tempStr = "";

		for (int i = 0; i < tableNames.length(); i++) {
			if (tableNames[i] == comparisonSpace) {
				this->tableNames[j] = tempStr;
				tempStr = "";
				j++;
			}
			else tempStr += tableNames[i];
		}
	}

	// The method creates a dynamic array containing a table name on each index position											-> Main method
	void LogicTableNamesArrayModifier(FileHandler& handlingFile, bool writeStatus = false) {
		string tableNames = getTableNames(handlingFile);
		setTableNamesSize(handlingFile, tableNames);
		tableNameArrCreate();
		setTableNames(tableNames);

		// Printing tableNames array 
		if (writeStatus == true) {
			cout << endl << "The table list from which to choose is this one now -> | ";
			if (!(getTableSize())) cout << "No list items |";
			else for (int z = 0; z < getTableSize(); z++) cout << this->tableNames[z] << " | ";
			cout << endl << "The table list size is this one now -> " << getTableSize() << endl << endl;
		}
	}



	void LogicalCheckingsCreate() {
		int i = 3;
		cout << this->currentArr[3] << endl;
		if (this->currentArr[3] == "IF" || this->currentArr[3] == "if" || this->currentArr[3] == "If" || this->currentArr[3] == "iF") i = 6;

		for (i; i < this->currentSize; i = i + 4) {

			int dimension = atoi(this->currentArr[i + 2].c_str());
			int introducedValue = this->currentArr[i+3].length();
			string expression3 = "[0-9]+\\.[0-9]+"; // Float Check
			
			// Checking if the name fits it's set dimension

			if (introducedValue > dimension) {
				cout << "ERROR:  " <<" "<< this->currentArr[i + 3].length() <<" "<<this->currentArr[i + 2] << endl;
			}

			// Checking the type match if type is integer (or int).

			if (this->currentArr[i + 1] == "integer") {

				string firstLength = to_string(this->currentArr[i + 3].length());
				int number = atoi(this->currentArr[i + 3].c_str());
				string secondLength = to_string(to_string(number).length());

				if (firstLength != secondLength) {
					cout << firstLength << " " << secondLength << endl;
					cout << "ERROR: The value you have introduced is not of integer type" << endl;
				}
			}
			else if (this->currentArr[i + 1] == "float")
			{bool isFloatCurrentArr = regex_match(this->currentArr[i + 3].c_str(), regex(expression3));
			if (!isFloatCurrentArr) cout << "ERROR! The value you have introduced is not of float type" << endl;

			}
			


			// Checking the type match if type is text (or string).

			else if (this->currentArr[i + 1] == "text") {

				const char quoteCheck = (this->currentArr[i + 3].c_str())[0];
				string quotesCheck = this->currentArr[i + 3];

				if (quoteCheck != '\'' && quotesCheck != "\"") {
					cout << "ERROR" << this->currentArr[i + 3] << endl;
				}
			}
		}
	}

	// The method requests the logic of command CREATE and continues the process based on the response
	void createTableElement(string tableName) {

		// Searching for element ( We don't want to find it )

		for (int i = 0; i < getTableSize(); i++) {
			if (tableName == this->tableNames[i]) throw "Elementul cautat exista deja!";
		}

		// Element not found, so continue

		FileHandler fileHandle = FileHandler();

		LogicalCheckingsCreate();
		fileHandle.tableNameToFile(tableName);
		fileHandle.createTableFile(this->currentArr, getCurrentArrSize(), tableName);
		
	}

	// The method requests the logic of command DROP and continues the process based on the response
	void dropTableElement(string tableName) {

		bool finderState = false;

		// Searching for element ( We want to find it. )

		for (int i = 0; i < getTableSize(); i++) {
				
			if (tableName == this->tableNames[i]) {
				// Element found, so continue 

				finderState = true;

				for (int j = i; j < getTableSize() - 1; j++) {
					this->tableNames[j] = this->tableNames[j + 1];
				}

				this->tableNames[getTableSize() - 1] = "";

				FileHandler fileHandle = FileHandler();
				
				// Calling for TableNames array

				fileHandle.suprascriptionTable(this->tableNames, "TableNames", getTableSize());
				fileHandle.dropTableFile(tableName);
			}
		}

		if (!finderState) throw "Elementul cautat nu exista!";
	}

	// The method requests the logic of command DISPLAY and continues the process based on the response
	void displayTableElement(string tableName) {

		bool finderState = false;

		// Searching for element ( We want to find it. )

		for (int i = 0; i < getTableSize(); i++) {
			if (tableName == this->tableNames[i]) {
				// Element found, so continue 

				finderState = true;

				FileHandler fileHandle = FileHandler();
				fileHandle.displayTableFile(tableName);
			}
		}

		if (!finderState) throw "Elementul cautat nu exista!";
	}

	void logicInsertInto(string tableName)
	{
		if (checkTabelExists(tableName) == true)
		{
			FileHandler check = FileHandler();
			int noOfColumnsCreate = check.noOfColumnsCreate(tableName);
			int counter = 4;
			int position = 0;
			string auxString;
			string columnValues = check.getCreateColumnValues(tableName);
			const char tempCompare = ' ';
			//put elements in this array of strings 
			string* columnValuesArray=new string[noOfColumnsCreate * 4];
			

			for (int i = 0; i < columnValues.length()-1; i++)
			{
				
				if (columnValues[i] == tempCompare)
				{
					columnValuesArray[position] = auxString;
					auxString = "";
					position++;

				}
				else
				{
	               auxString += columnValues[i];
				}

			}
		
			columnValuesArray[noOfColumnsCreate * 4 - 1] = auxString;
			
		
			if ((getCurrentArrSize() - 4) == noOfColumnsCreate)
			{
				for (int i = 3; i < (noOfColumnsCreate * 4); i = i + 4)
				{
					string expression1 = "[0-9]+"; // Number Check
					string expression2 = "'[a-zA-Z0-9_]+'"; // String Check
					string expression3 = "[0-9]+\\.[0-9]+"; // Float Check


					bool isIntegerCurrentArr = regex_match(this->currentArr[counter].c_str(), regex(expression1));
					bool isIntegerValues = regex_match(columnValuesArray[i].c_str(), regex(expression1));

					bool isStringCurrentArr = regex_match(this->currentArr[counter].c_str(), regex(expression2));
					bool isStringValues = regex_match(columnValuesArray[i].c_str(), regex(expression2));

					bool isFloatCurrentArr = regex_match(this->currentArr[counter].c_str(), regex(expression3));
					bool isFloatValues = regex_match(columnValuesArray[i].c_str(), regex(expression3));

					if ((isIntegerCurrentArr && isIntegerValues) || (isStringCurrentArr && isStringValues) || (isFloatCurrentArr && isFloatValues))
					{
						cout << "Succes!" << endl;
						columnValuesArray[i] = this->currentArr[counter];
					}
					else cout << "error.typeProblem" << endl;

					counter++;
				}
				check.suprascriptionTable(columnValuesArray, tableName, (noOfColumnsCreate * 4) + 1);

			}
			else cout << "The values sequence is not correlated with the  columns sequence from " << tableName << endl;
			delete[] columnValuesArray;
			columnValuesArray = nullptr;
		}

		else cout << "Table name doesn't exist!" << endl;
		
		
	}
	string lowerCaseInput(string input) {
		for (unsigned int i = 0; input[i] != '\0'; i++) if (input[i] >= 'A' && input[i] <= 'Z') input[i] = input[i] + 32;
		return input;
	}

	void logicSelect(string tableName)
	{
		if (checkTabelExists(tableName) == true) {
			FileHandler check = FileHandler();

			int noOfColumnsCreate = check.noOfColumnsCreate(tableName);
			int noOfElementsCreate = noOfColumnsCreate * 4;
			string* columnValuesArray = new string[noOfElementsCreate];

			int position = 0;
			int j = 1;
			int k = 0;

			string auxString;
			string createValues = check.getCreateColumnValues(tableName);

			string comparisonStrAll = "ALL";
			string comparisonStrFrom = "FROM";
			string comparisonStrWhere = "WHERE";

			const char tempCompare = ' ';


			for (int i = 0; i < createValues.length() - 1; i++) {
				if (createValues[i] == tempCompare) {
					columnValuesArray[position] = auxString;
					auxString = "";
					position++;
				}
				else auxString += createValues[i];
			}
			columnValuesArray[noOfElementsCreate - 1] = auxString;
			if (stringToUpper(this->currentArr[1]) != comparisonStrAll) {
				if (stringToUpper(this->currentArr[getCurrentArrSize() - 4]) == comparisonStrWhere) {
					for (int i = 0; i < noOfElementsCreate; i = i + 4) {
						
						if (columnValuesArray[i] == this->currentArr[getCurrentArrSize() - 3]) {
							
							if (columnValuesArray[i + 3] == this->currentArr[getCurrentArrSize() - 1]) {
								
								int checkerEveryColumn = 0;
								while (stringToUpper(this->currentArr[j]) != comparisonStrFrom) {
									for (int i = 0; i < noOfElementsCreate; i = i + 4) {
										
										if (this->currentArr[j] == columnValuesArray[i]) {
											checkerEveryColumn++;
										}
									}
									j++;
								}
								j = 1;
								if (checkerEveryColumn != noOfColumnsCreate) cout << "ERROR: The name of column(s) doesn't exists in the table " + tableName << endl;
								while (stringToUpper(this->currentArr[j]) != comparisonStrFrom) {
									for (int i = 0; i < noOfElementsCreate; i = i + 4) {
										
										if (this->currentArr[j] == columnValuesArray[i]) {
											cout << columnValuesArray[i] << " = " << columnValuesArray[i + 3] << endl;
										}
									}
									j++;
								}
								return;
							}
							cout << "ERROR: The value of identifier is inexistent in the table." << endl;
							return;
						}
					}
					cout << "ERROR: The where identifier is inexistent in the table." << endl;
				}
				else {
					int checkerEveryColumn = 0;
					while (stringToUpper(this->currentArr[j]) != comparisonStrFrom) {
						for (int i = 0; i < noOfElementsCreate; i = i + 4) {
							
							if (this->currentArr[j] == columnValuesArray[i]) {
								checkerEveryColumn++;
							}
						}
						j++;
					}
					j = 1;
					if (checkerEveryColumn != noOfColumnsCreate) cout << "ERROR: The name of column(s) doesn't exists in the table " + tableName << endl;
					while (stringToUpper(this->currentArr[j]) != comparisonStrFrom) {
						for (int i = 0; i < noOfElementsCreate; i = i + 4) {
							
							if (this->currentArr[j] == columnValuesArray[i]) {
								cout << columnValuesArray[i] << " = " << columnValuesArray[i + 3] << endl;
							}
						}
						j++;
					}
					return;
				}
			}
			else {
				cout << stringToUpper(this->currentArr[getCurrentArrSize() - 4]) << " " << comparisonStrWhere << endl;
				if (stringToUpper(this->currentArr[getCurrentArrSize() - 4]) == comparisonStrWhere) {
					
					for (int i = 0; i < noOfElementsCreate; i = i + 4) {
						cout << columnValuesArray[i] << " " << this->currentArr[getCurrentArrSize() - 3] << endl;
						if (columnValuesArray[i] == this->currentArr[getCurrentArrSize() - 3]) {
							
							cout << columnValuesArray[i + 3] << " " << this->currentArr[getCurrentArrSize() - 1] << endl;
							if (columnValuesArray[i + 3] == this->currentArr[getCurrentArrSize() - 1]) {
								
								check.displayTableFile(tableName);
								return;
							}
							else {
								cout << "ERROR: The column name in where condition doesn't contain something similar with the table " + tableName << endl;
								return;
							}
						}
					}
					cout << "ERROR: The column name in where condition is inexistent in table " + tableName << endl;
					return;
				}
				else check.displayTableFile(tableName);
			}

			delete[] columnValuesArray;
			columnValuesArray = nullptr;
		}
		else cout << "Table name doesn't exist!" << endl;
	}


	void logicDelete(string tableName)
	{ 
		if (checkTabelExists(tableName) == true)
		{
			int position = 0;
			int breaker = 0;
			FileHandler check = FileHandler();
			int noOfColumnsCreate = check.noOfColumnsCreate(tableName);
			int noElementsCreate = noOfColumnsCreate * 4;
			string auxString;
			string createValues = check.getCreateColumnValues(tableName);
			const char tempCompare = ' ';
			string* columnValuesArray = new string[noOfColumnsCreate * 4];
			int retainIndex = 0;
			FileHandler fileHandle = FileHandler();
			int number = 0;

			for (int i = 0; i < createValues.length()-1; i++) {
				if (createValues[i] == tempCompare)
				{
					columnValuesArray[position] = auxString;
					auxString = "";
					position++;
				}
				else auxString += createValues[i];
			}
			columnValuesArray[noElementsCreate-1] = auxString;

			for (int i = 0; i < noElementsCreate; i = i + 4) {
				if ((columnValuesArray[i] == currentArr[4]) && (breaker == 0)) {
					breaker = 1;
					retainIndex = i;
				}
				if ((currentArr[6] == columnValuesArray[retainIndex+3]) && (breaker == 1))
				{
					number = 1;
					//'pushes' the column 'out'
                    for (int j = retainIndex; j < noElementsCreate - 4; j++){

						columnValuesArray[j] = columnValuesArray[j + 4];
				    }
					cout << "The new table is: " << endl;
					fileHandle.suprascriptionTable(columnValuesArray, tableName, noElementsCreate - 3);
				}
			}
			if ((breaker != 1) || (number != 1))
			{
				cout << "error! the column name or value is wrong.";
			}
			delete[] columnValuesArray;
			columnValuesArray = nullptr;
		}
		else cout << "Table name doesn't exist";
	}


	int checkSetDataType(string tableName)
	{
		string expression1 = "[0-9]+$"; // integer Check
		string expression2 = "'[^']+'"; // text Check
		string expression3 = "([0-9]*[.])+[0-9]+"; // Float Check
		int typeIdSet=0;
		bool isIntegerCurrentArr = regex_match(this->currentArr[5].c_str(), regex(expression1));
		bool isStringCurrentArr = regex_match(this->currentArr[5].c_str(), regex(expression2));
		bool isFloatCurrentArr = regex_match(this->currentArr[5].c_str(), regex(expression3));
		if (isIntegerCurrentArr==true) typeIdSet = 1;
		else if (isStringCurrentArr==true) typeIdSet = 2;
	    else if (isFloatCurrentArr==true) typeIdSet = 3;

		return typeIdSet;
	}
	int checkColumnArrayDataType(string tableName)
	{
		int position = 0;
		int breaker = 0;
		FileHandler fileHandle = FileHandler();
		int noOfColumnsCreate = fileHandle.noOfColumnsCreate(tableName);
		int noElementsCreate = noOfColumnsCreate * 4;
		string auxString;
		string createValues = fileHandle.getCreateColumnValues(tableName);
		const char tempCompare = ' ';
		string* columnValuesArray = new string[noOfColumnsCreate * 4];
		int retainIndex = 0;
		int typeIdColumn = 0;
		for (int i = 0; i < createValues.length() - 1; i++) {
			if (createValues[i] == tempCompare)
			{
				columnValuesArray[position] = auxString;
				auxString = "";
				position++;
			}
			else auxString += createValues[i];

		}
		for (int i = 0; i < noElementsCreate; i = i + 4) {
			if ((columnValuesArray[i] == currentArr[3]) && (breaker == 0)) {
				breaker = 1;
				retainIndex = i;
			}
		}
		if (breaker == 1) {
			string expression1 = "integer"; // Number Check
			string expression2 = "text"; // String Check
			string expression3 = "float"; // Float Check
			bool isIntegerCurrentArr = regex_match(columnValuesArray[retainIndex + 1].c_str(), regex(expression1));
			bool isStringCurrentArr = regex_match(columnValuesArray[retainIndex + 1].c_str(), regex(expression2));
			bool isFloatCurrentArr = regex_match(columnValuesArray[retainIndex + 1].c_str(), regex(expression3));
			if (isIntegerCurrentArr == true) typeIdColumn = 1;
			else if (isStringCurrentArr == true) typeIdColumn = 2;
			else if (isFloatCurrentArr == true) typeIdColumn = 3;
			delete[] columnValuesArray;
			columnValuesArray = nullptr;
			return typeIdColumn;
		}
		else {
			delete[] columnValuesArray;
			columnValuesArray = nullptr;
			return 100;
		}
	}
	void LogicUpdate(string tableName)
	{   
		if (checkTabelExists(tableName) == true)
		{
			int position = 0;
			int breaker = 0;
			FileHandler fileHandle = FileHandler();
			int noOfColumnsCreate = fileHandle.noOfColumnsCreate(tableName);
			int noElementsCreate = noOfColumnsCreate * 4;
			string auxString;
			string createValues = fileHandle.getCreateColumnValues(tableName);
			const char tempCompare = ' ';
			string* columnValuesArray = new string[noOfColumnsCreate * 4];
			int retainIndex1 = 0;
			int retainIndex2 = 0;
			int valueAfterWhere = 0;
			int dataTypeColumn = checkColumnArrayDataType(tableName);
			int dataTypeSet = checkSetDataType(tableName);
			
			for (int i = 0; i < createValues.length() - 1; i++) {
				if (createValues[i] == tempCompare)
				{
					columnValuesArray[position] = auxString;
					auxString = "";
					position++;
				}
				else auxString += createValues[i];
			}
			columnValuesArray[noElementsCreate - 1] = auxString;
			for (int i = 0; i < noElementsCreate; i = i + 4) {
				if ((columnValuesArray[i] == currentArr[7]) && (breaker == 0)) {
					breaker = 1;
					retainIndex1 = i;
					//aici dau checking sa vad ca exista coloana de dupa where : where id = 7
				}
				if ((currentArr[9] == columnValuesArray[retainIndex1 + 3]) && (breaker == 1) && (valueAfterWhere ==0))
				{
					valueAfterWhere = 1;
				}
				// aici gasesc retain value si schimb cu update
				if ((columnValuesArray[i] == currentArr[3]) && (breaker == 1)&&(valueAfterWhere==1)) {
					retainIndex2 = i;
					//set nume = 'ok'
				}

			}
			if ((breaker == 1) && (valueAfterWhere == 1) && (dataTypeColumn==dataTypeSet))
			{
				columnValuesArray[retainIndex2+3] = currentArr[5];
				fileHandle.suprascriptionTable(columnValuesArray, tableName, (noElementsCreate)+1);
			}
			else if ((breaker != 1) || (valueAfterWhere != 1))
			{
				cout << "error! column name or value is wrong";
			}
			else if ((dataTypeColumn != dataTypeSet))
			{
				cout << "error! the data type you tried to set is not correct or the column doesn't exist";
			}
			delete[] columnValuesArray;
			columnValuesArray = nullptr;
		}
		else cout << "The table name doesn't exist!";
	}
	int csvFileLength(string csvFileName) {
		char separator = '|';
		FileHandler fileHandler = FileHandler();
		string csvFileContent = fileHandler.csvFileContent(csvFileName);
		int csvFileLength = 0;
		for (int i = 0; i < csvFileContent.length(); i++) {
			if (csvFileContent[i] == separator)csvFileLength++;
		}
		csvFileLength++; //" a | b | c ", this is for c
		return csvFileLength;
	}
	string* getCsvFileContentArray(string csvFileName) {
		FileHandler fileHandler = FileHandler();
		int csvLength = csvFileLength(csvFileName);
		string csvFileContent = fileHandler.csvFileContent(csvFileName);
		string* csvFileContentArray = new string[csvLength];
		string tempStr;
		char separator = '|';
		for (int i = 0, j = 0; i < csvFileContent.length(); i++) {
			if (csvFileContent[i] != separator) tempStr += csvFileContent[i];
			else {
				csvFileContentArray[j] = tempStr;
				tempStr = "";
				j++;
			}
		}
		csvFileContentArray[csvLength - 1] = tempStr;
		return csvFileContentArray;
	}

	void logicImport(string tableName, string csvFileName) {
		FileHandler fileHandler = FileHandler();
		bool csvFileExists = fileHandler.csvFileExists(csvFileName);
		cout << "!!!!!!!!!" << csvFileExists << "     " << endl;
		cout << tableName << endl;
		cout << " nume tabel : "<<checkTabelExists(tableName) << endl;
		char separator = '|';
		if (checkTabelExists(tableName) && csvFileExists) {
			int csvLength = csvFileLength(csvFileName);
			string* csvFileContentArray = getCsvFileContentArray(csvFileName);
			int noOfColumnsCreate = fileHandler.noOfColumnsCreate(tableName);
			int noOfCreateElements = noOfColumnsCreate * 4;
			string columnValues = fileHandler.getCreateColumnValues(tableName);
			string* columnValuesArray = new string[noOfCreateElements];
			int counter = 0;
			int position = 0;
			string auxString;
			const char tempCompare = ' ';

			for (int i = 0; i < columnValues.length() - 1; i++) {
				if (columnValues[i] == tempCompare) {
					columnValuesArray[position] = auxString;
					auxString = "";
					position++;
				}
				else auxString += columnValues[i];
			}
			columnValuesArray[noOfCreateElements - 1] = auxString;
			if (csvLength == noOfColumnsCreate) {
				for (int i = 3; i < (noOfColumnsCreate * 4); i = i + 4)
				{
					string expression1 = "[0-9]+$"; // Number Check
					string expression2 = "'[^']+'"; // String Check
					string expression3 = "([0-9]*[.])+[0-9]+"; // Float Check

					bool isIntegerCurrentArr = regex_match(this->currentArr[counter].c_str(), regex(expression1));
					bool isIntegerValues = regex_match(columnValuesArray[i].c_str(), regex(expression1));

					bool isStringCurrentArr = regex_match(this->currentArr[counter].c_str(), regex(expression2));
					bool isStringValues = regex_match(columnValuesArray[i].c_str(), regex(expression2));

					bool isFloatCurrentArr = regex_match(this->currentArr[counter].c_str(), regex(expression3));
					bool isFloatValues = regex_match(columnValuesArray[i].c_str(), regex(expression3));

					if ((isIntegerCurrentArr && isIntegerValues) || (isStringCurrentArr && isStringValues) || (isFloatCurrentArr && isFloatValues))
					{
						cout << "Succes!" << endl;
						columnValuesArray[i] = csvFileContentArray[counter];
					}
					else cout << "error.typeProblem" << endl;

					counter++;
				}
				fileHandler.suprascriptionTable(columnValuesArray, tableName, noOfCreateElements + 1);
			}
			else cout << " The values sequence is not correlated with the  columns sequence from " << tableName << endl;
			delete[] columnValuesArray;
			columnValuesArray = nullptr;
			delete[] csvFileContentArray;
			csvFileContentArray = nullptr;
		}
		else cout << "Csv file name doesnt't exist or table name is wrong ";
	}

	// The method, based on the command, checks it's respective logic																-> Main method
	void tableLogicalChecks(string firstElement, string tableName) {
		if (firstElement == "create") createTableElement(tableName);
		else if (firstElement == "drop") dropTableElement(tableName);
		else if (firstElement == "display") displayTableElement(tableName);
		else if (firstElement == "insert")logicInsertInto(tableName);
		else if (firstElement == "select")logicSelect(tableName);
		else if (firstElement == "delete")logicDelete(tableName);
		else if (firstElement == "update")LogicUpdate(tableName);
		else if (firstElement == "import")logicImport(tableName,currentArr[getCurrentArrSize()-1]);

		cout << endl << "Logical & File phases Passed" << endl;
	} 
	

	// Avoids memory leaks
	~LogicHandler() {
		delete[] this->currentArr;
		this->currentArr = nullptr;

		delete[] this->tableNames;
		this->tableNames = nullptr;
	
	}
};