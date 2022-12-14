#include "ClassesImports.cpp"

int main(int argc, char* argv[]) {
	system("color 0D"); // For purple color of the text.

	CounterRetainer counterRetainer = CounterRetainer();
	string input = "";
	string executableName = argv[0];
	int counter = 1;

	Parser parser = Parser();
	LogicHandler logicHandler = LogicHandler();
	Printer printer = Printer(); 
	ErrorHandler errorHandler = ErrorHandler();
	FileHandler fileHandle = FileHandler();

	printer.intro();

	
	
	//for (int i = 0; i < argc; i++) {
	//	cout << "ELEMENT: " << argv[i] << endl;
	//}
	//cout << executableName << " sql-database.exe" << endl 
	//	 << "argc: " << argc << endl;

	//if (executableName == "sql-database.exe" && argc <= 6) 
	{
		while (true) {
			// logicHandler.dataReloader();
			if (input != "exit") logicHandler.LogicTableNamesArrayModifier(fileHandle, true);
			if (counter < argc) {
				string currentTextFile = argv[counter];
				input = fileHandle.inputFromCommandPrompt(currentTextFile);
				counter++;
			}
			if (input != "")
			{  
				if (input == "exit") break;
				if (input == "clear") {
					for (int i = 0; i < 50; i++) cout << endl << endl;
					input = "";
					continue;
				}
				try {
					
					string lowerCaseInput = parser.lowerCaseInput(input);
					parser.parse(lowerCaseInput);

					logicHandler.LogicCurrentArrayModifier(input);

					string firstElement = parser.getFirstInputElement(lowerCaseInput);
					string tableName = logicHandler.getTableName();
					logicHandler.tableLogicalChecks(firstElement, tableName);

					// Command details down
					// printer.print(input);
				}
				catch (exception const& e) {
					
				}
			}
			if (counter >= argc) {
				cout << "Enter a command: ";
				getline(cin, input);
			}
		}
		printer.goodByeModel();
	

		
	}
}