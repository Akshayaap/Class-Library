#pragma once




#define CHAINING 1000
#define L_PROBING 1001
#define Q_PROBING 1002
#define D_HASHING 1003

#define D_EMPTY 2000
#define D_INT 2001
#define D_FLOAT 2002
#define D_DOUBLE 2003
#define D_CHAR 2004
#define D_STR 2005
#define D_DELETED 2100
#define D_CHAIN 2101


/**
 *
 * Namespace for data structures
 * */
namespace _structures //<editor-fold>
{
    /********************************
     *		Linked List Node		*
     *********************************/
    /**
     *
     * Data structure to hold entries in Linked List
     */
    struct Node
    {
        int *data; // change it to void *
        struct Node *next;
    };
    struct Node *createNode(int *);
    /********************************
     *		Linked List Node		*
     *********************************/

    /********************************
     *		Linked List Class		*
     *********************************/

    /**
     *
     * Linked List class
     * */
    class LinkedList
    {
    private:
        struct Node *head;
        struct Node *last;
        int nodeCount;
        struct Node *iterator;

    public:
        LinkedList(/*void*/);
        ~LinkedList();
        void deleteList();
        void destroyList();
        void insert(int *);
        void insertF(int *);
        void *getLast() const;
        void *getFirst() const;
        void *pop();
        void *popF();
        void deleteFirst();
        void deleteLast();
        int getNodeCount() const;
        void *iterate();          // returns current and increment pointer
        void *getCurrent() const; // returns current
        void seekNext();          // increments pointer
        void seekBegin();         // set pointer to first element;
        void seekLast();          // set pointer to last element;
        void removeCurrent();
#ifdef DEBUG
        void print() const;

        void list() const;
#endif
#ifdef DEBUG
        void (*printCustom)();
#endif
    };
    /********************************
     *       Linked List Class       *
     *********************************/



     /********************************
      *       Class Hash       *
      *********************************/

    struct HashItem
    {
        void* data;
        int type;
        long long key;
    };

    class Hash
    {
    private:
        long long* key;
        void** data;
        int* type;
        int hashType;
        int size;
        int numElem;
        int hash(long long) const;

    public:
        Hash(const int, const int);
        ~Hash();
        void insert(long long, void*, int);
        void* get(long long) const;
#ifdef DEBUG

        void print() const;
#endif // DEBUG

        void remove(long long);
        int getSize();
        void destroyHash();
        long long getHashKey(int);
        void* getHashData(int);
        int getHashType(int);
        void* operator[](int)const;
        // auto get();
    };



    /********************************
     *       Class Hash       *
     *********************************/


     /********************************
      *       Class Dictionay       *
      *********************************/





    class Dictionary {
    private:
        Hash* hash;
        int size;
        int numElem;
    public:
        Dictionary(int size);
        ~Dictionary();
        void insert(const char*, void*);
        void* get(const char*)const;
        static long long calcWeight(const char* key);
        static char* calcKey(long long weight);
#ifdef DEBUG
        void print()const;
#endif
        int getSize()const;
        void remove(const char* key);
        void* operator[](const char* key)const;

    };



    /********************************
     *       Class Dictionay       *
     *********************************/



    /********************************
     *	Data Structure Exception	*
     *********************************/

    class DSException : public std::exception
    {
    private:
        std::string msg;
        int line;
        std::string file;

    public:
        DSException(std::string &msg, std::string &file, int line);
        ~DSException();
        const char *what() const noexcept;
    };

    /********************************
     *	Data Structure Exception	*
     *********************************/
};
// </editor-fold> namespace DS
