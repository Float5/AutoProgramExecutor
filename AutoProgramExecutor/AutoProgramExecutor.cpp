#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <windows.h>

using namespace std;
namespace fs = std::filesystem;


const string runningPath = fs::current_path().string();
const string executorsPath = runningPath + "\\executors";
vector<string> commandList = {"help", "exit", "clear", "ls", "mkexe", "rmexe", "modexe", "exels", "run"};



vector<string> GetInput();
bool CheckArgsCnt(vector<string> command, int argsCnt);

bool Command(vector<string> command);
void CommandHelp();
void CommandClear();
void CommandLs();
void CommandMkexe(string exeName);
void CommandRmexe(string exeName);
void CommandModexe(vector<string> command);
void CommandExels(string exeName);
void CommandRun(string exeName);



vector<string> GetInput() {
	cout << "> ";
	string answer;

	getline(cin, answer);

	if (answer.empty()) return {};

	vector<string> result;
	vector<int> spaces;

	int index = 0;
	while (true) {
		if (answer.find(" ", index) != string::npos) {
			index = answer.find(" ", index);
			spaces.push_back(index++);
		}
		else {
			break;
		}
	}

	for (int i = 0; i < answer.size(); i++) {
		if (answer[i] == '#') {
			answer[i] = ' ';
		}
	}

	if (spaces.empty()) return { answer };

	string temp;
	index = 0;
	for (int i = 0; i < spaces.size(); i++) {
		temp = answer.substr(index, spaces[i] - index);
		if(!temp.empty())
			result.push_back(temp);
		index = spaces[i] + 1;
	}
	temp = answer.substr(index);
	if (!temp.empty())
		result.push_back(temp);

	return result;
}

bool CheckArgsCnt(vector<string> command, int argsCnt) {
	if (command.size() != argsCnt + 1) {
		cout << "Command [" + command[0] + "] needs " + to_string(argsCnt) + " arguments" << endl;
		return false;
	}
	else {
		return true;
	}
}



bool Command(vector<string> command) {

	if (command[0] == "help") {
		if (!CheckArgsCnt(command, 0)) return false;
		CommandHelp();
	}
	else if (command[0] == "exit") {
		return true;
	}
	else if (command[0] == "clear") {
		if (!CheckArgsCnt(command, 0)) return false;
		CommandClear();
	}
	else if (command[0] == "ls") {
		if (!CheckArgsCnt(command, 0)) return false;
		CommandLs();
	}
	else if (command[0] == "mkexe") {
		if (!CheckArgsCnt(command, 1)) return false;
		CommandMkexe(command[1]);
	}
	else if (command[0] == "rmexe") {
		if (!CheckArgsCnt(command, 1)) return false;
		CommandRmexe(command[1]);
	}
	else if (command[0] == "modexe") {
		if (!CheckArgsCnt(command, 3)) return false;
		CommandModexe(command);
	}
	else if (command[0] == "exels") {
		if (!CheckArgsCnt(command, 1)) return false;
		CommandExels(command[1]);
	}
	else if (command[0] == "run") {
		if (!CheckArgsCnt(command, 1)) return false;
		CommandRun(command[1]);
	}
	else {
		cout << "Can't Find Command: [" << command[0] << "]\n";
	}

	return false;
}

void CommandHelp() {
	cout << "Command List\n\n";

	for(int i = 0; i < commandList.size(); i++){
		cout << commandList[i] << endl;
	}
}

void CommandClear() {
	system("cls");
}

void CommandLs() {
	try {
		for (const auto& entry : fs::directory_iterator(executorsPath)) {
			if (!fs::is_directory(entry)) {
				string fileName = entry.path().filename().string();
				fileName = fileName.substr(0, fileName.size() - 4);
				cout << fileName << endl;
			}
		}
	}
	catch (const fs::filesystem_error e) {
		std::cerr << "filesystem_error: " << e.what() << endl;
	}
}

void CommandMkexe(string exeName) {
	ofstream fout(executorsPath + "\\" + exeName + ".txt");
	fout.close();
	cout << "Successfully created [" << exeName << "]" << endl;
}

void CommandRmexe(string exeName) {
	if (remove((executorsPath + "\\" + exeName + ".txt").c_str()) == 0) {
		cout << "Successfully removed [" << exeName << "]" << endl;
	}
	else {
		cout << "Failed to remove [" << exeName << "]" << endl;
	}
}

void CommandModexe(vector<string> command) {
	string exeName = command[1];
	string option = command[2];
	string content = command[3];

	ifstream fin(executorsPath + "\\" + exeName + ".txt");

	if (!fin.is_open()) {
		cout << "Failed to open [" << exeName << "]" << endl;
		return;
	}

	vector<string> contents;

	string line;
	while (getline(fin, line)) {
		contents.push_back(line);
	}

	fin.close();

	if (!(content.substr(0, 2) == "W-" || content.substr(0, 2) == "P-")) {
		cout << "W- or P-" << endl;
		return;
	}

	if (option == "-a") {
		for (int i = 0; i < contents.size(); i++) {
			if (contents[i] == content) {
				cout << "[" << content << "] already exist" << endl;
				return;
			}
		}

		contents.push_back(content);
		cout << "Successfully added [" << content << "] on [" << exeName << "]" << endl;
	}
	else if (option == "-r") {
		bool found = false;
		for (int i = 0; i < contents.size(); i++) {
			if (contents[i] == content) {
				found = true;
				contents.erase(contents.begin() + i);
			}
		}

		if (!found) {
			cout << "[" << content << "] not exist" << endl;
			return;
		}

		cout << "Successfully removed [" << content << "] on [" << exeName << "]" << endl;
	}
	else {
		cout << "You can use options [-a or -r]" << endl;
		return;
	}

	remove((executorsPath + "\\" + exeName + ".txt").c_str());
	ofstream fout(executorsPath + "\\" + exeName + ".txt");
	
	for (int i = 0; i < contents.size(); i++) {
		fout << contents[i] << endl;
	}
	
	fout.close();
}

void CommandExels(string exeName) {
	ifstream fin(executorsPath + "\\" + exeName + ".txt");

	if (!fin.is_open()) {
		cout << "Failed to open [" << exeName << "]" << endl;
		return;
	}

	string line;
	while (getline(fin, line)) {
		cout << line << endl;
	}

	fin.close();
}

void CommandRun(string exeName) {
	ifstream fin(executorsPath + "\\" + exeName + ".txt");

	if (!fin.is_open()) {
		cout << "Failed to open [" << exeName << "]" << endl;
		return;
	}

	vector<string> contents;
	string line;
	while (getline(fin, line)) {
		contents.push_back(line);
	}

	fin.close();

	for (int i = 0; i < contents.size(); i++) {
		string content = contents[i];
		char type = content[0];

		if (type == 'P') {
			string exePath = content.substr(2, content.size() - 2);
			HINSTANCE result = ShellExecuteA(
				NULL,
				"open",
				exePath.c_str(),
				NULL,
				NULL,
				SW_SHOWNORMAL
			);

			if ((int)result > 32) {
				std::cout << "Successfully executed [" << exePath << "]" << std::endl;
			}
			else {
				std::cerr << "Failed to execute [" + exePath + "] (error code: " << (int)result << ")" << std::endl;
			}
		}
		else if (type == 'W') {
			string url = content.substr(2, content.size() - 2);
			HINSTANCE result = ShellExecuteA(
				NULL,
				"open",
				url.c_str(),
				NULL,
				NULL,
				SW_SHOWNORMAL
			);

			if ((int)result > 32) {
				std::cout << "Successfully executed [" << url << "]" << std::endl;
			}
			else {
				std::cerr << "Failed to execute [" + url + "] (error code: " << (int)result << ")" << std::endl;
			}
		}
	}
}




int main() {
	cout << "Auto Program Executor" << endl;
	cout << "running in : " << runningPath << endl << endl;

	if (!fs::exists(executorsPath)) {
		cout << "executors directory not founded" << endl;
		try {
			if (fs::create_directory(executorsPath)) {
				cout << "Successfully Created executors directory: " << executorsPath << endl << endl;
			}
		}
		catch (const fs::filesystem_error& e) {
			cerr << "Failed to create directory: " << e.what() << endl;
			return 0;
		}
	}

	while (true) {
		vector<string> answer = GetInput();

		if (answer.empty()) continue;
		bool exit = Command(answer);

		if (exit) break;
	}

	return 0;
}