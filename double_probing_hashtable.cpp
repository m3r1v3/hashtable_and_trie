#include <iostream>
#include <vector>

using namespace std;

const int CAPABILITY = 9;
const int EMPTY = -1;

struct HashTable {
	vector<int> table;
	int count;

	HashTable() {
		table.resize(CAPABILITY, EMPTY);
	}

	int get_hash1(int k) {
		return k % CAPABILITY;
	}

	int get_hash2(int k) {
		return 1 + (k % (CAPABILITY - 1));
	}

	void insert(int key) {
		int h1 = get_hash1(key);
		int h2 = get_hash1(key);

		int i = 0;
		int index;

		while (i < CAPABILITY) {
			index = (h1 + i * h2) % CAPABILITY;
			if (table[index] == EMPTY) {
				table[index] = key;
				return;
			}
			i++;
		}

		cout << "Table is filled.\n";
	}

	void print() {
		for (int i = 0; i < CAPABILITY; i++) {
			if (table[i] != EMPTY)
				cout << i << ": " << table[i] << "\n";
			else
				cout << i << ": " << "empty\n";
		}
	}
};

int main() {
	HashTable table;
	int n; cin >> n;

	for (int i = 0; i < n; i++) {
		int v; cin >> v; table.insert(v);
	}

	table.print();
}