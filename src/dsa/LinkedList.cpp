#include <exception>
#include <string>

#ifdef DEBUG
#include <iostream>
#endif
#include "DSException.h"
#include "Structures.h"

/****************************************************************************************
 *								List Node Operation										*
 *****************************************************************************************/

/**
 *
 * function that creates linked list Node for data
 * */
struct _structures::Node *_structures::createNode(int *data)
{
    struct _structures::Node *node = new struct _structures::Node;
    node->data = data;
    node->next = nullptr;
    return node;
}
/****************************************************************************************
 *                                List Node Operation                                    *
 *****************************************************************************************/

/****************************************************************************************
 *                                List Class Operation                                   *
 *****************************************************************************************/

/**
 *
 * invoked at creation of Linked List
 **/
_structures::LinkedList::LinkedList(/*void* printCustom*/)
{
    this->nodeCount = 0;
    this->head = nullptr;
    this->last = nullptr;
    this->iterator = nullptr;
}

/**
 *
 * Invoked at deletion of List
 **/

_structures::LinkedList::~LinkedList()
{
    this->deleteList();
}

/***
 *
 * delete all node in list
 * */
void _structures::LinkedList::deleteList()
{
    struct _structures::Node *temp;
    while (head)
    {
        temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
    this->nodeCount = 0;
}

/**
 *
 * delete all node as well as all data pointed by pointer stored in list
 * */
void _structures::LinkedList::destroyList()
{
    struct _structures::Node *temp;
    while (this->head)
    {
        temp = this->head;
        this->head = this->head->next;
        delete temp->data;
        delete temp;
    }
    this->nodeCount = 0;
}

/**
 *
 *
 * inserts a new element  in at the last of list
 * */
void _structures::LinkedList::insert(int *data)
{
    if (this->nodeCount == 0)
    {
        this->head = _structures::createNode(data);
        this->last = this->head;
        this->nodeCount = 1;
        this->iterator = head;
    }
    else
    {
        this->last->next = _structures::createNode(data);
        this->last = this->last->next;
        this->nodeCount++;
    }
}

/**
 *
 * inserts an element at front of list
 **/
void _structures::LinkedList::insertF(int *data)
{
    if (this->nodeCount == 0)
    {
        this->head = _structures::createNode(data);
        this->last = this->head;
        this->iterator = this->head;
    }
    else
    {
        struct _structures::Node *temp = createNode(data);
        temp->next = this->head;
        this->head = temp;
    }
    this->nodeCount++;
}

/**
 *
 * this function returns a last eelement of list
 */
void *_structures::LinkedList::getLast() const
{
    if (this->head)
    {
        return this->last->data;
    }
    throw DSException("Cant find Last Element, List is Empty", __FILE__, __LINE__);
}

/**
 *
 * this function retruns  a first element of list
 * */
void *_structures::LinkedList::getFirst() const
{
    if (this->nodeCount == 0)
    {
        throw _structures::DSException("Cant find First Element. List is Empty", __FILE__, __LINE__);
    }
    return this->head->data;
}

/**
 *
 * this function delets First element of List
 * */
void _structures::LinkedList::deleteFirst()
{
    int flag = 0;
    if (this->iterator == head)
    {
        flag = 1;
    }
    if (this->nodeCount == 0)
    {
        throw _structures::DSException("Cant delete First Element. List is Empty", __FILE__, __LINE__);
    }
    struct _structures::Node *temp = this->head;
    this->head = this->head->next;
    delete temp;
    this->nodeCount--;
    if (flag)
    {
        this->iterator = head;
    }
}

/**
 *
 * this function delets Last element of List
 * */
void _structures::LinkedList::deleteLast()
{
    int flag = 0;
    if (this->iterator == last)
    {
        flag = 1;
    }
    if (this->nodeCount == 0)
    {
        throw DSException("Cant delete Last Element. List is Empty", __FILE__, __LINE__);
    }
    struct _structures::Node *temp = this->head;
    while (temp->next->next)
    {
        temp = temp->next;
    }
    this->last = temp;
    delete this->last->next;
    this->last->next = nullptr;
    this->nodeCount--;
    if (flag)
    {
        this->iterator = nullptr;
    }
}

/**
 *
 * this function pop off last element of list from last
 * */
void *_structures::LinkedList::pop()
{
    if (this->nodeCount < 1)
    {
        throw _structures::DSException("Cant Pop Last Element, List is Empty", __FILE__, __LINE__);
    }
    void *temp = this->last->data;
    this->deleteLast();
    return temp;
}

/**
 *
 *
 * this function pop off frist element from list
 * */
void *_structures::LinkedList::popF()
{
    if (this->nodeCount < 1)
    {
        throw _structures::DSException("Cant Pop First Element, List is Empty", __FILE__, __LINE__);
    }
    void *temp = this->head->data;
    this->deleteFirst();
    return temp;
}

/**
 *
 * this function returns node count of linked list
 * */
int _structures::LinkedList::getNodeCount() const
{
    return this->nodeCount;
}

/**
 *
 * this function returns current iterator
 */
void *_structures::LinkedList::getCurrent() const
{
    if (this->nodeCount < 1)
    {
        throw DSException("Cant get first Element, List is Empty", __FILE__, __LINE__);
    }
    return this->iterator->data;
}

/**
 *
 * this function returns a current iterator pointer and seek to next pointer
 * */
void *_structures::LinkedList::iterate()
{
    if (!this->iterator)
    {
        return nullptr;
    }
    void *temp = this->iterator->data;

    this->iterator = this->iterator->next;
    return temp;
}

/**
 *
 * this fucntion moves iterator to next element
 * */
void _structures::LinkedList::seekNext()
{
    this->iterator = this->iterator->next;
}

/**
 *
 * this function moves iterator pointer to first element
 * */
void _structures::LinkedList::seekBegin()
{
    this->iterator = this->head;
}

/**
 *
 * this function moves iterator pointer to last element
 */
void _structures::LinkedList::seekLast()
{
    this->iterator = this->last;
}

/**
 *
 * this function prints the while linked list
 * */

#ifdef DEBUG

void _structures::LinkedList::print() const
{
    struct _structures::Node *temp = this->head;
    std::cout << "\nList containing " << this->nodeCount << " Elements\n";
    while (temp)
    {
        std::cout << *(int *)temp->data << "\n";
        temp = temp->next;
    }
    std::cout << std::endl;
}

/**
 *
 * this function lists out all nodes without formation
 */

void _structures::LinkedList::list() const
{
    _structures::Node *temp = this->head;
    while (temp)
    {
        std::cout << *(int *)temp->data << " ";
        temp = temp->next;
    }
}

#endif
/**
 *
 * this function removes current element (pointed by iterator) remove from list
 * */
void _structures::LinkedList::removeCurrent()
{
    if (this->iterator)
    {
        if (this->iterator == this->last)
        {
            this->deleteLast();
            this->iterator = nullptr;
            return;
        }
        this->iterator->data = this->iterator->next->data;
        struct _structures::Node *temp = this->iterator->next;
        this->iterator->next = this->iterator->next->next;
        delete temp;
    }
}

/****************************************************************************************
 *								List Class Operation									*
 *****************************************************************************************/