#include <iostream>
#include <vector>

using namespace std;

const int CAPABILITY = 16;
const int EMPTY = '\0';

struct HashTable {
	vector<char> table;

	HashTable() {
		table.resize(CAPABILITY, EMPTY);
	}

	int get_hash(char ch) {
		return (11 * (tolower(ch) - 'a' + 1)) % CAPABILITY;
	}

	void insert(char ch) {
		int hash = get_hash(ch);
		int i = 0;
		int index;

		while (i < CAPABILITY) {
			index = (hash+i) % CAPABILITY;
			if (table[index] == EMPTY) {
				table[index] = ch;
				return;
			}
			i++;
		}

		cout << "Table is full.\n";
	}

	void print() {
		for (int i = 0; i < CAPABILITY; i++)
			if (table[i] != EMPTY) {
				cout << i << ": " << table[i] << "\n";
			} else {
				cout << i << ": " << "empty" << "\n";
			}
	}
};

int main() {
	HashTable table;

	int n; cin >> n;

	for (int i = 0; i < n; i++) {
		char ch; cin >> ch;
		table.insert(ch);
	}

	table.print();
}