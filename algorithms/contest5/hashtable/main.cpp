#include <iostream>
#include <list>

struct Hash {
  int sizeofbucket;
  std::list<int>* table;

 public:
  Hash(int size);
  int HashFunction(int index) { return (index % sizeofbucket); }
  void Insert(int key);
  void Delete(int key);
  bool Exists(int key);
  ~Hash() { delete[] table; }
};

Hash::Hash(int size) {
  sizeofbucket = size;
  table = new std::list<int>[sizeofbucket];
}

void Hash::Insert(int key) {
  int position = HashFunction(key);
  std::list<int>::iterator i;
  for (i = table[position].begin(); i != table[position].end(); ++i) {
    if (*i == key) {
      break;
    }
  }
  if (i == table[position].end()) {
    table[position].push_back(key);
  }
}

void Hash::Delete(int key) {
  int position = HashFunction(key);
  std::list<int>::iterator i;
  for (i = table[position].begin(); i != table[position].end(); ++i) {
    if (*i == key) {
      break;
    }
  }
  if (i != table[position].end()) {
    table[position].erase(i);
  }
}

bool Hash::Exists(int key) {
  int position = HashFunction(key);
  std::list<int>::iterator i;
  for (i = table[position].begin(); i != table[position].end(); ++i) {
    if (*i == key) {
      break;
    }
  }
  return (i != table[position].end());
}

int main() {
  int size;
  std::cin >> size;
  Hash hashtable(1000);
  for (int i = 0; i < size; ++i) {
    char instr;
    long long value;
    std::cin >> instr >> value;
    switch (instr) {
      case '?':
        if (hashtable.Exists(value)) {
          std::cout << "YES"
                    << "\n";
        } else {
          std::cout << "NO"
                    << "\n";
        }
        break;
      case '+':
        hashtable.Insert(value);
        break;
      case '-':
        hashtable.Delete(value);
        break;
    }
  }
  return 0;
}