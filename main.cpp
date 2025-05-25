// main.cpp
#include <iostream>
#include <string>
using namespace std;

// Node struct representing each slot in the hash table
struct Node {
    string key;      // The stored key (lower-case English word)
    bool isDeleted;  // True if the slot is a tombstone (i.e., logically deleted)

    // Constructor to initialize a new node with a given key
    Node(const string& k) : key(k), isDeleted(false) {}
};

// Hash table implementation with linear probing
class HashTable {
private:
    static const int TABLE_SIZE = 26; // Fixed size, one for each letter a-z
    Node* table[TABLE_SIZE];          // Array of pointers to nodes

    // Hash function: based on the last character of the key
    int hash(const string& key) {
        return key.back() - 'a';
    }

public:
    // Constructor: initialize all slots to nullptr (never used)
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    // Insert a key into the hash table
    void insert(const string& key) {
        if (search(key)) return; // If key already exists, do nothing

        int idx = hash(key);     // Get starting index from hash
        int probes = 0;

        // Linear probing to find an available slot
        while (probes < TABLE_SIZE) {
            // If slot is unused or marked deleted, we can insert here
            if (table[idx] == nullptr || table[idx]->isDeleted) {
                delete table[idx];               // Clean up any old node (if tombstone)
                table[idx] = new Node(key);      // Insert new node
                return;
            }
            idx = (idx + 1) % TABLE_SIZE; // Move to next slot (wrap around)
            ++probes;
        }
    }

    // Remove a key from the hash table
    void remove(const string& key) {
        int idx = hash(key);   // Start from the hash index
        int probes = 0;

        while (probes < TABLE_SIZE) {
            // Stop searching if slot was never used
            if (table[idx] == nullptr) return;

            // If key matches and it's not already deleted, mark it as deleted
            if (!table[idx]->isDeleted && table[idx]->key == key) {
                table[idx]->isDeleted = true; // Set tombstone flag
                return;
            }

            idx = (idx + 1) % TABLE_SIZE;
            ++probes;
        }
    }

    // Search for a key in the table
    bool search(const string& key) {
        int idx = hash(key);
        int probes = 0;

        while (probes < TABLE_SIZE) {
            if (table[idx] == nullptr) return false; // Key not found

            if (!table[idx]->isDeleted && table[idx]->key == key) {
                return true; // Key found and not deleted
            }

            idx = (idx + 1) % TABLE_SIZE;
            ++probes;
        }

        return false; // Full loop and not found
    }

    // Print all keys currently in the table (in order from index 0 to 25)
    void print() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i] && !table[i]->isDeleted) {
                cout << table[i]->key << " ";
            }
        }
    }

    // Destructor: free all allocated memory
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            delete table[i];
        }
    }
};

// Main program: reads a line of operations and applies them to the hash table
int main() {
    HashTable ht;
    string input;
    getline(cin, input); // Read entire input line

    size_t start = 0;

    // Parse and apply each operation in the input
    while (start < input.length()) {
        size_t end = input.find(' ', start);
        if (end == string::npos) end = input.length();

        string token = input.substr(start, end - start);

        if (token.length() >= 2) {
            char op = token[0];              // Operation type: 'A' or 'D'
            string key = token.substr(1);    // Extract the key

            if (op == 'A') ht.insert(key);   // Insert operation
            else if (op == 'D') ht.remove(key); // Delete operation
        }

        start = end + 1;
    }

    ht.print(); // Display final hash table state
    return 0;
}
