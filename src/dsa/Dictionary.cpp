#include <cmath>
#include"Structures.h"


using namespace _structures;

Dictionary::Dictionary(int size) {
    this->size = size;
    this->hash = new Hash(this->size, L_PROBING);
    this->numElem = 0;
}

Dictionary::~Dictionary() {
    delete this->hash;
}

void Dictionary::insert(const char* key, void* data) {
    if (this->numElem < this->size) {
        this->hash->insert(Dictionary::calcWeight(key), data, D_INT);
        this->numElem++;
    }
}

void* Dictionary::get(const char* key)const {
    long long weight = Dictionary::calcWeight(key);
    return this->hash->get(weight);
}
#ifdef DEBUG

void Dictionary::print()const {
    std::cout << "Dictionary Having " << this->numElem << " elements out of " << this->size << "\n";
    std::cout << "Key\t\tValues\n\n";
    char* key;
    long long weight;
    for (int i = 0; i < this->size; i++) {
        if ((weight = this->hash->getHashKey(i)) > -1) {
            key = Dictionary::calcKey(weight);
            std::cout << key << "\t\t" << *(int*) hash->getHashData(i) << "\n";
            delete[] key;
        }
    }
    //this->hash->print();
}

#endif // DEBUG

void Dictionary::remove(const char* key) {
    long long weight = Dictionary::calcWeight(key);
    hash->remove(weight);
    this->numElem--;
}

long long Dictionary::calcWeight(const char* key) {
    long long base = 128;
    int i = 0;
    long long weight = 0;
    char ch = 0;
    while (ch = key[i++]) {
        weight *= base;
        weight += ch;
    }
    return weight;
}

int Dictionary::getSize()const {
    return this->size;
}

char* Dictionary::calcKey(long long weight) {
    int lenght = (int) (log2(weight) / 7) + 1;
    int base = 128;
    char* key = new char[(long long) lenght + 1];
    for (int i = lenght - 1; i >= 0; i--) {
        key[i] = weight % base;
        weight /= 128;
    }
    key[lenght] = NULL;
    return key;
}

void* Dictionary::operator[](const char* key)const {
    return this->get(key);
}