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

	int get_hash(int k) {
		return k % CAPABILITY;
	}

	void insert(int key) {
		int index = get_hash(key);
		int i = 0;
		int new_index;

		while (i < CAPABILITY) {
			new_index = (index + i * i) % CAPABILITY;
			if (table[new_index] == EMPTY) {
				table[new_index] = key;
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