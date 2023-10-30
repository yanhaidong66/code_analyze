#include<string>
#include<iostream>
using namespace std;
class HashTable {
private:
	typedef struct pair {
		string key;
		int value;
	}pair;
	typedef struct vNode {
		bool isEmpty;
		pair p;
		struct vNode* next;
	}vNode;

	vNode** table;//Ö¸ÕëÊý×é
	vNode** table1;
	int buketSize;
	int valueAmount;
	bool init1(int bs);
	bool put1(string k, int v);

	
public:
	HashTable();
	bool put(string k, int v);
	bool delet(string k);
	bool isContain(string k);
	int getValue(string k);
	int getAll(string k[], int v[]);
	int hash(const string k);
	bool init(int bs);
	bool rehash(int newBucketSize);
	
};

HashTable::HashTable()
{
	init(10);
}

bool HashTable::rehash(int newBucketSize) {
	init1(newBucketSize);


}
bool HashTable::put(string k, int v)
{
	int position = hash(k);
	vNode* ptr = table[position];
	if (ptr->isEmpty == false) {
		if (ptr->p.key == k) {
			ptr->p.value += v;
			return true;
		}
		while (ptr->next != NULL) {
			if (ptr->p.key == k) {
				ptr->p.value += v;
				return true;
			}
			else {
				ptr = ptr->next;
			}
		}
		vNode* listNode = (vNode*)calloc(1, sizeof(vNode));
		if (listNode == NULL)
			return false;
		listNode->isEmpty = false;
		(string)listNode->p.key = k.substr(0);
		listNode->p.value = v;
		ptr->next = listNode;
		listNode->next = NULL;
	}
	else {
		ptr->isEmpty = false;
		ptr->p.key = k.substr(0);
		ptr->p.value = v;
	}
	valueAmount++;
	return true;
}

bool HashTable::delet(string k)
{
	int position = hash(k);
	vNode* ptr = table[position];
	if (ptr->next == NULL)
		ptr->isEmpty = true;
	else {
		while (ptr->next!=NULL&&ptr->next->p.key != k)
				ptr = ptr->next;
		ptr->next = ptr->next->next;
	}
	
	return true;
}

bool HashTable::isContain(string k)
{
	int position = hash(k);
	vNode* ptr = table[position];
	if(ptr->next==NULL)
		return ptr->isEmpty;
	else {
		while (ptr!=NULL && ptr->p.key != k)
			ptr = ptr->next;
		if (ptr == NULL)
			return false;
		else
			return true;
	}
}

int HashTable::getValue(string k)
{
	int position = hash(k);
	vNode* ptr = table[position];
	if (ptr->isEmpty == true)
		return 0;
	while (ptr!=NULL && ptr->p.key != k)
		ptr = ptr->next;
	return ptr->p.value;

}

int HashTable::getAll(string k[],int v[])
{
	int pairSize = 0;
	for (int i = 0; i < buketSize; i++) {
		vNode* ptr = table[i];
		if (ptr->isEmpty == true)
			continue;
		else {
			while ((ptr->next) != NULL) {
				k[pairSize] = ptr->p.key;
				v[pairSize] = ptr->p.value;
				pairSize++;
				ptr = ptr->next;
			}
			k[pairSize] = ptr->p.key;
			v[pairSize] = ptr->p.value;
			pairSize++;
		}
	}
	return valueAmount;
}



int HashTable::hash(const string k)
{
	const char* ck = k.c_str();
	unsigned int v=0;
	while (*ck != '\0') {
		v = (v << 5) + *ck;
		ck++;
	}
	return v % buketSize;
}

bool HashTable::init(int bs)
{
	vNode** newTable = (vNode**)calloc(bs, sizeof(vNode*));
	for (int i = 0; i < bs; i++) {
		newTable[i] = (vNode*)calloc(1, sizeof(vNode));
		newTable[i]->isEmpty = true;
		newTable[i]->next = NULL;
	}
	if (newTable == NULL)
		return false;
	table = newTable;
	buketSize = bs;
	valueAmount = 0;
	return true;
}

int main() {
	HashTable* ht = new HashTable();
	ht->put("haidong", 3);
	ht->put("haidong", 2);
	ht->put("ewbnr", 23);
	ht->put("wenb23", 23);
	ht->put("hh", 2);
	ht->put("df", 2);
	ht->put("weu4r", 5);
	string s[20];
	int v[20];
	int si=ht->getAll(s, v);
	for (int i = 0; i < si; i++) {
		cout<<"k:" << s[i];
		cout <<"         v:" << v[i]<<endl;
	}

}