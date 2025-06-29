#include <iostream>

using namespace std;

const int TABLE_SIZE = 9;

struct HashTable {
	struct Node {
		int key;
		Node* next;

		Node(int i) : key(i), next(nullptr) {}
	};

	Node* table[TABLE_SIZE] = { nullptr };

	~HashTable() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			Node* current = table[i];
			while (current) {
				Node* temp = current;
				current = current->next;
				delete temp;
			}
		}
	}

	int get_hash(int k) {
		return k % TABLE_SIZE;
	}

	void insert(int i) {
		int index = get_hash(i);

		Node* new_node = new Node(i);
		new_node->next = table[index];
		table[index] = new_node;
	}

	void print() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			Node* current = table[i];
			if (current) {
				cout << i << ": ";
				while (current) {
					cout << current->key << " ";
					current = current->next;
				}
				cout << "\n";
			} else {
				cout << i << ": " << "empty" << "\n";
			}
		}
	}
};

int main() {
	HashTable table;

	int n; cin >> n;

	for (int i = 0; i < n; i++) {
		int k; cin >> k;
		table.insert(k);
	}

	table.print();
}