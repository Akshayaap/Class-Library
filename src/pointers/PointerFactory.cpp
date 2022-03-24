#include <iostream>
#include <exception>
#include <vector>
#include <unordered_map>
#include "PointerFactory.h"

using namespace pointers;

template<class T>
Pointer<T>::Pointer(Factory* factory, T* target) {
	this->factory = factory;
	this->ptr = target;
	factory->AddRef(ptr);
}

template<class T>
Pointer<T>::Pointer(const Pointer& ptr) {
	this->factory = ptr->factory;
	this->ptr = ptr->ptr;
	factory->AddRef(ptr);
}

template<class T>
Pointer<T>& Pointer<T>::operator=(const Pointer& ptr) {
	this->factory = ptr->factory;
	this->ptr = ptr->ptr;
	factory->AddRef(ptr);
	return *this;
}

template<class T>
Pointer<T>::~Pointer() {
	factory->DecRef(ptr);
}




/***********************************************************************
								Factory
************************************************************************/

Factory::Factory() {
}


Factory::~Factory() {

}

template<class T>
Pointer<T> Factory::MakePtr(T* target) {
	return Pointer<T>(this, target);
}

Factory& Factory::getInstance() {
	if (factory) {
		return *factory;
	}
}


void Factory::AddRef(unsigned long long index) {
	if (map.find(index) == map.end()) {
		this->map[index] = 1;
	}
	this->map[index]++;
}

template<class T>
void Factory::DecRef(unsigned long long index) {
	this->map[index]--;
	if (map[index] == 0) {
		map.erase(index);
		delete(T*) index;
	}
}
