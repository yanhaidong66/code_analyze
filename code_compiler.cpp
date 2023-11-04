#include<iostream>
#include<fstream>
#include"MyHashMap.cpp"
using namespace std;
class codeCompiler {
public:
	HashMap hm;
	bool codeFetch(string fileName);
private:
	int commandState;
	int commandSwitch(const char);
	bool getCode(const char*);
	bool codeOver(char c);
};

int codeCompiler::commandSwitch(const char cmd)
{
	if (cmd == '*') {
		commandState = 1;
		return 1;
	}
		
	return 0;
}

bool codeCompiler::getCode(const char* c)
{
	string s(c);
	hm.put(s, 1);
	return true;
}


bool codeCompiler::codeFetch( string fileName)
{
	char* buf=new char[200];
	ifstream file(fileName.c_str());

	if (!file) {
		std::cerr << "文件无法打开" << std::endl;
		return 1;
	}
	
	int size = 0;
	char c[2] = { 0 };
	c[1] = '\0';
	while (file.eof()==false) {
		file.get(c[0]);
		if (c[0] == '\\'||c[0]=='/') {
			file.get(c[0]);
			commandSwitch(c[0]);
			continue;
		}
		switch (commandState) {

		case 0: {
			if (codeOver(c[0]) == true) {
				buf[size++] = '\0';
				getCode(buf);
				getCode(c);
				size = 0;
			}
			else {
				buf[size++] = c[0];
			}
		}break;

		case 1: {
			char commentOver[2] = { 0 };
			while (!(commentOver[0] == '*' && commentOver[1] == '/')) {
				commentOver[0] = commentOver[1];
				file.get(commentOver[1]);
				
			}
			commandState = 0;
			break;
		}

		default: {
			break;
		}

		}
			
	}
		
		
		file.close();


	return false;
}

bool codeCompiler::codeOver(const char c)
{
	if (c == '/') {
		commandState = true;
		return false;
	}
		
	
	if (c >= 'A' && c <= 'Z'|| c >= 'a' && c <= 'z' || c>='0'&&c<='9')
		return false;
	return true;
}



int main() {
	codeCompiler codeC;
	codeC.codeFetch("c.c");
	string keys[200];
	int values[200];
	int size=codeC.hm.getAll(keys, values, 200);
	cout << "size:" << size << endl;
	for (int i = 0; i < size; i++) {
		cout << "key:" << keys[i];
		cout << "           value:" << values[i]<< endl;
	}
}