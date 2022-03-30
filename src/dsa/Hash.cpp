#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include "Structures.h"

/**
 *
 * I just Hate Documentation
 * */

using namespace _structures;

Hash::Hash(int size, int hashType) {
    this->numElem = 0;
    this->size = size;
    this->hashType = hashType;
    this->data = new void* [size];
    if (hashType != CHAINING) {
        this->type = new int[size];
        this->key = new long long[size];
        for (int i = 0; i < this->size; i++) {
            this->type[i] = D_EMPTY;
            this->key[i] = -1;
        }
    } else {
        this->key = nullptr;
        this->type = nullptr;
    }

    if (hashType == CHAINING) {
        for (int i = 0; i < size; i++) {
            ((LinkedList**)(this->data))[i] = new LinkedList();
        }
    } else {
        for (int i = 0; i < this->size; i++) {
            ((void**) (this->data))[i] = nullptr;
        }
    }

}

Hash::~Hash() {
    this->destroyHash();
}

void Hash::insert(long long key, void* data, int type) {
    int hkey;
    switch (this->hashType) {

        case CHAINING:
        {
            hkey = key % this->size;
            struct HashItem* hItem = new HashItem;
            hItem->type = type;
            hItem->key = key;
            hItem->data = data;
            ((LinkedList**)(this->data))[hkey]->insertF((int*) hItem); //do remove int*
            this->numElem++;
            ((LinkedList**)(this->data))[hkey]->seekBegin();
        }
            break;
        case L_PROBING:
        {
            if (this->numElem < this->size) {
                hkey = key % this->size;
                int i = 0;
                int tmp;
                do {
                    hkey = (key + i++) % this->size;
                    //tmp = this->type[hkey];		//debug code
                    if (this->key[hkey] == key) {
                        throw DSException("Element Already pressent",__FILE__,__LINE__);
                    }
                } while (this->type[hkey] != D_EMPTY && this->type[hkey] != D_DELETED);
                this->key[hkey] = key;
                this->data[hkey] = data;
                this->type[hkey] = type;
                this->numElem++;
            } else {
                throw DSException("Hash is full",__FILE__, __LINE__);
            }
            69;
        }
            break;
        case Q_PROBING:
        {
            if (this->numElem < this->size) {
                int hkey1 = key % this->size;
                hkey = hkey1;
                int i = 0;
                if (this->type[hkey1] != D_EMPTY && this->type[hkey1] != D_DELETED) {
                    do {
                        i++;
                        hkey = (key + i * i) % this->size;
                        if (hkey == hkey1) {
                            throw DSException("Hash is not full but cyclic locked", __FILE__, __LINE__);
                            return;
                        }
                        if (this->key[hkey] == key) {
                            throw DSException("Element Already Present", __FILE__, __LINE__);
                        }
                    } while (this->type[hkey] != D_EMPTY && this->type[hkey] != D_DELETED);
                }
                ((void**) this->data)[hkey] = data;
                this->key[hkey] = key;
                this->type[hkey] = type;
                this->numElem++;

            } else {
                throw DSException("Hash is full", __FILE__, __LINE__);
            }
        }
            break;
        case D_HASHING:
            break;
        default:
            throw DSException("Invalid operation", __FILE__, __LINE__);
            break;
    }

}

void* Hash::get(long long key) const {
    int hkey;
    switch (this->hashType) {
        case CHAINING:
            HashItem* hItem;
            hkey = key % this->size;
            while (true) {
                hItem = (HashItem*) ((LinkedList**)data)[hkey]->iterate();
                if (!hItem) {
                    return nullptr;
                }
                if (hItem->key == key) {
                    return hItem->data;
                }
            }
            break;
        case L_PROBING:
            if (this->numElem == 0) {
                return nullptr;
            } else {
                hkey = key % this->size;
                int hkey1 = hkey;
                int i = 1;
                if (this->key[hkey] == key) {
                    return this->data[hkey];
                } else {
                    while (true) {
                        hkey = (hkey + i) % this->size;
                        if (type[hkey] == D_EMPTY) {
                            return nullptr;
                        }
                        if (hkey == hkey1) {
                            return nullptr;
                        }
                        if (this->key[hkey] == key) {
                            return data[hkey];
                        }
                    }
                }
            }
            break;
        case Q_PROBING:
            if (this->numElem == 0) {
                return nullptr;
            } else {
                hkey = key % this->size;
                int hkey1 = hkey;
                int i = 1;
                if (this->key[hkey] == key) {
                    return this->data[hkey];
                } else {
                    while (true) {
                        hkey = (key + i * i) % this->size;
                        if (type[hkey] == D_EMPTY) {
                            return nullptr;
                        }
                        if (hkey == hkey1) {
                            return nullptr;
                        }
                        if (this->key[hkey] == key) {
                            return data[hkey];
                        }
                    }
                }
            }
            break;
        case D_HASHING:
            break;
        default:
            throw DSException("Invalid Hash operation", __FILE__, __LINE__);
            break;
    }
}

int Hash::hash(long long key)const {
    return 0;
}
#ifdef DEBUG
void Hash::print()const {


    std::cout << "\nHash Having Size " << this->size << " and having " << this->numElem << " Elements in it\n";
    switch (this->hashType) {
        case CHAINING:
            std::cout << "\n";
            struct HashItem* hItem;

            for (int i = 0; i < this->size; i++) {
                std::cout << i;
                ((LinkedList**)this->data)[i]->seekBegin();
                while (hItem = (struct HashItem*) (((LinkedList**)this->data)[i])->iterate()) {
                    std::cout << "\t" << hItem->key << "  " << *(int*) hItem->data << "\n";

                }
                std::cout << "\n";
                ((LinkedList**)this->data)[i]->seekBegin();
            }
            break;
        case L_PROBING:
        case Q_PROBING:
        case D_HASHING:
            //int* ptr;              //debug code
            for (int i = 0; i < this->size; i++) {
                //ptr = (int*)this->data[i];           //debug code
                if (this->type[i] == D_EMPTY || this->type[i] == D_DELETED) {
                    std::cout << i << "\n";
                } else {
                    std::cout << i << "\t" << this->key[i] << "\t" << *(int*) this->data[i] << "\n";
                }
            }
            break;
        default:
            throw DSException("Unsupported Operation", __FILE__, __LINE__);
            break;
    }
}


#endif // DEBUG

void Hash::remove(long long key) {
    if (this->numElem <= 0) {
        throw DSException("Element not present", __FILE__, __LINE__);
        return;
    }
    int hkey = key % this->size;
    int i = 0;
    int hkey1 = hkey;
    switch (this->hashType) {
        case CHAINING:

            struct HashItem* hItem;
            ((LinkedList**)data)[hkey]->seekBegin();
            while (hItem = (HashItem*) ((LinkedList**)data)[hkey]->getCurrent()) {
                if (hItem->key == key) {
                    ((LinkedList**)data)[hkey]->removeCurrent();
                    delete hItem->data;
                    delete hItem;
                    this->numElem--;
                    return;
                    break;
                }
                ((LinkedList**)data)[hkey]->seekNext();
            }
            ((LinkedList**)data)[hkey]->seekBegin();
            throw DSException("Element Cannot be removed", __FILE__, __LINE__);
            break;
        case L_PROBING:


            while (true) {
                hkey = (key + i++) % this->size;
                if (this->key[hkey] == key) {
                    this->data[hkey] = nullptr;
                    this->key[hkey] = -1;
                    this->type[hkey] = D_DELETED;
                    return;
                    break;
                }
                if (this->type[hkey] == D_EMPTY || i >= this->size) {
                    throw DSException("Element does not exist", __FILE__, __LINE__);
                    return;
                    break;
                }
            }
            break;
        case Q_PROBING:

            if (this->numElem <= 0) {
                throw DSException("Hash is Empty", __FILE__, __LINE__);
                return;
            } else {
                hkey = key % this->size;

                if (this->key[hkey] == key) {
                    this->data[hkey] = nullptr;
                    this->key[hkey] = -1;
                    this->type[hkey] = D_DELETED;
                } else {
                    while (true) {
                        i++;
                        hkey = (key + i * i) % this->size;
                        if (type[hkey] == D_EMPTY) {
                            throw DSException("Element not pressent in Hash", __FILE__, __LINE__);
                            return;
                            break;
                        }
                        if (this->key[hkey] == key) {
                            this->data[hkey] = nullptr;
                            this->key[hkey] = -1;
                            this->type[hkey] = D_DELETED;
                            return;
                            break;
                        }
                        if (hkey == hkey1) {
                            throw DSException("Element not pressent in Hash", __FILE__, __LINE__);
                        }
                    }
                }
                break;
                case D_HASHING:
                //complicated
                break;
                default:
                break;
            }

    }
}

void Hash::destroyHash() {
    if (this->hashType == CHAINING) {
        struct HashItem* hItem;
        for (int i = 0; i < this->size; i++) {
            ((LinkedList*)this->data[i])->seekBegin();
            while (hItem = (HashItem*) ((LinkedList*)this->data[i])->iterate()) {
                delete hItem->data;
            }
            ((LinkedList*)this->data[i])->destroyList();
            delete ((LinkedList*)this->data[i]);
        }
    } else {
        for (int i = 0; i < this->size; i++) {
            delete ((void*) this->data[i]);
        }
        delete[] this->key;
        delete[] this->type;
    }
    delete[] this->data;

}

int Hash::getSize() {
    return this->size;
}

long long Hash::getHashKey(int index) {
    return this->key[index];
}

void* Hash::getHashData(int index) {
    return this->data[index];
}

int Hash::getHashType(int index) {
    return this->type[index];
}

void* _structures::Hash::operator[](int key) const
{
    return this->get(key);
}
