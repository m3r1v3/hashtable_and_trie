#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 26;

struct Trie {
private:
    struct Node {
        Node* children[ALPHABET_SIZE];
        bool is_leaf;

        Node() : is_leaf(false) {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                children[i] = nullptr;
            }
        }
    } *root;

    void delete_subtree(Node* node) {
        if (!node) return;

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                delete_subtree(node->children[i]);
            }
        }

        delete node;
    }

    bool remove(Node* node, string word, int depth) {
        if (depth == word.length()) {
            if (node->is_leaf) {
                node->is_leaf = false;
                return is_empty(node);
            } else {
                return false;
            }
        }

        if (!isalpha(word[depth)) return false;

        int index = tolower(word[depth]) - 'a';
        if (node->children[index] && remove(node->children[index], word, depth + 1)) {
            delete node->children[index];
            node->children[index] = nullptr;
            return node->is_leaf && is_empty(node);
        } else {
            return false;
        }
    }

    void print(Node* node, string current) {
        if (node->is_leaf) cout << current << "\n";

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) 
                print(node->children[i], current + (char)('a' + i));
        }
    }

    bool is_empty(Node* node) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i])
                return false;
        }
        return true;
    }

    void get_words(Node* node, string current, vector<string>& words) {
        if (node->is_leaf) {
            words.push_back(current);
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i])
                get_words(node->children[i], current+(char)('a'+i), words);
        }
    }

public:
    Trie() : root(new Node()) {
    
    }

    ~Trie() {
        delete_subtree(root);
    }

    void insert(string word) {
        Node* current = root;
        for (char ch : word) {
            if (!isalpha(ch)) continue;

            int index = tolower(ch) - 'a';
            if (current->children[index] == nullptr)
                current->children[index] = new Node();
            current = current->children[index];
        }
        current->is_leaf = true;
    }

    bool search(string word) {
        Node* current = root;
        for (char ch : word) {
            if (!isalpha(ch)) return false;

            int index = tolower(ch) - 'a';
            if (current->children[index] == nullptr) 
                return false;
            current = current->children[index];
        }
        return current->is_leaf;
    }

    void print() {
        print(root, "");
    }

    bool is_empty() {
        return is_empty(root);
    }

    void remove(string word) {
        remove(root, word, 0);
    }

    vector<string> get_words() {
        vector<string> words;
        get_words(root, "", words);
        return words;
    }
};

int main() {
    Trie tree;
    int n; cout << "Enter count of words > "; cin >> n;

    for (int i = 0; i < n; i++) {
        string word; cin >> word;
        tree.insert(word);
    }

    tree.print();

    string sub; cout << "Enter a substring > "; cin >> sub;
    for (string word : tree.get_words()) {
        if (word.find(sub) != string::npos) {
            tree.remove(word);
            cout << "`" << word << "` is deleted.\n";
        }
    }

    string word; cout << "Enter a word to find > "; cin >> word;
    cout << "`" << word << "`" << ((tree.search(word)) ? " found.\n" : " not found.\n");
}
