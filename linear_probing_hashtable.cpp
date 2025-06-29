#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 16;
const int EMPTY = '\0';

struct HashTable {
	vector<char> table;

	HashTable() {
		table.resize(SIZE, EMPTY);
	}

	int get_hash(char ch) {
		return (11 * (tolower(ch) - 'a' + 1)) % SIZE;
	}

	void insert(char ch) {
		int index = get_hash(ch);
		int i = 0;

		while (table[(index+i) % SIZE] != EMPTY && i < SIZE) {
			i++;
		}

		if (i < SIZE) table[(index + i) % SIZE] = ch;
		else cout << "Table is full.\n";
	}

	void print() {
		for (int i = 0; i < SIZE; i++)
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