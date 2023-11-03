#include<iostream>
#include<fstream>
#include"MyHashMap.cpp"
using namespace std;
class codeCompiler {
public:
	HashMap hm;
	bool getCode(const char*);
	bool getCode(const char);
	bool codeFetch(string fileName);
	bool codeOver(char c);
};

bool codeCompiler::getCode(const char* c)
{
	string s(c);
	hm.put(s, 1);
	return true;
}

bool codeCompiler::getCode(const char c)
{
	string s(c+"");
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
	if (file) {

		while (file.eof()==false) {
			int size = 0;
			char c = 0;
			file.get(c);
			buf[size++] = c;
			if (codeOver(c) == true) {
				getCode(c);
				cout << c;
				cout << endl;
				continue;
			}
		
			while(codeOver(c)==false) {
				file.get(c);
				if (codeOver(c) == false)
					buf[size++] = c;
				else
					break;
					
			}
			buf[size] = '\0';
			getCode(buf);
			cout << buf ;
			cout << endl;
			getCode(c);
			cout << c;
			cout << endl;
			
			
		}
		file.close();

	}


	file.close();
	return false;
}

bool codeCompiler::codeOver(const char c)
{
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