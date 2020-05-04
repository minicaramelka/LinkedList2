#include <iostream>
#include "LinkedList2.h"
#include <cassert>

using namespace std;

LinkedList2::Node::Node(const ValueType& value, Node* next, Node* last){
	this->value = value;
	this->next = next;
	this->last = last;
}

LinkedList2::Node::~Node(){
	// ничего не удаляем, т.к. агрегация
}

void LinkedList2::Node::insertNext(const ValueType& value){
	Node* newNode = new Node(value, this->next);
	this->next = newNode;
}

void LinkedList2::Node::removeNext(){
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
}

LinkedList2::LinkedList2():
_size(0), _head(nullptr), _tail(nullptr)
{
}

LinkedList2::LinkedList2(const LinkedList2& copyList){
    this->_size = copyList._size;
    if (this->_size == 0){
        this->_head = nullptr;
        this->_tail = nullptr;
        return;
    }
    this->_head = new Node(copyList._head->value);
    this->_tail = new Node(copyList._tail->value);
    Node* currentNode = this->_head;
    Node* currentCopyNode = copyList._head->next;
    while (currentCopyNode){
        currentNode->next = new Node(currentCopyNode->value);
        currentCopyNode = currentCopyNode->next;
        currentNode = currentNode->next;
    }
}

LinkedList2& LinkedList2::operator=(const LinkedList2& copyList){
	if (this == &copyList){
		return *this;
	}
	LinkedList2 bufList(copyList);
	this->_size = bufList._size;
	this->_head = bufList._head;
	this->_tail = bufList._tail;
	return *this;
}

LinkedList2::LinkedList2(LinkedList2&& moveList) noexcept{
	this->_size = moveList._size;
	this->_head = moveList._head;
	this->_tail = moveList._tail;
	moveList._size = 0;
	moveList._head = nullptr;
	moveList._tail = nullptr;
}

LinkedList2& LinkedList2::operator=(LinkedList2&& moveList) noexcept{
	if (this == &moveList){
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;
	this->_tail = moveList._tail;
	moveList._size = 0;
	moveList._head = nullptr;
	moveList._tail = nullptr;
	return *this;
}

LinkedList2::~LinkedList2(){
	forceNodeDelete(_head);
}

ValueType& LinkedList2::operator[](const size_t pos) const{
	return getNode(pos)->value;
}

LinkedList2::Node* LinkedList2::getNode(const size_t pos) const{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->_size) {
		assert(pos >= this->_size);
	}
	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}
	return bufNode;
}

void LinkedList2::insert(const size_t pos, const ValueType& value){
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos > this->_size) {
		assert(pos > this->_size);
	}
	if (pos == 0) {
		pushFront(value);
	}
	else if(pos == _size){
	    pushBack(value);
	}
	else {
		Node* bufNode = this->_head;
		for (size_t i = 0; i < pos-1; ++i) {
			bufNode = bufNode->next;
		}
		bufNode->insertNext(value);
		++_size;
	}
}

void LinkedList2::insertAfterNode(Node* node, const ValueType& value){
	node->insertNext(value);
	_size++;
}

void LinkedList2::pushBack(const ValueType& value){
    Node *nd = new Node(value, nullptr, _tail);
    if(_tail != 0){
        _tail->next = nd;
        _tail = nd;
    }
    if(_size == 0){
        _head = _tail = nd;
    }
    _size++;
    
}

void LinkedList2::pushFront(const ValueType& value){
    Node *nd = new Node(value, _head, nullptr); 
    if(_head != 0){
        _head->last = nd;
        _head = nd;
    }
    if(_size == 0)
        _head = _tail = nd;
    _size++;
}

void LinkedList2::remove(const size_t pos){
    if(_head){
        if(pos > 0 && pos < _size - 1){
            int counter = 0;
            Node *tmp = _head;
            while(counter <= pos){
                tmp = tmp->next;
                counter++;
            }
            counter=0;
            Node *nd = _head;
            while(counter < pos-1){
                nd = nd->next;
                counter++;
            }
            _size--;
            nd->next = tmp;
        }
        else if(pos == 0){
            Node *tmp = _head;
            tmp = tmp->next;
            delete _head;
            _size--;
            _head = tmp;
        }
        else{
            Node *tmp = _tail;
            tmp = tmp->last;
            delete _tail;
            _size--;
            _tail = tmp;
        }
    }
    else{
        cout<<"The list is empty!" << endl;
    }
}

void LinkedList2::removeNextNode(Node* node){
    Node* removeNode = node->next; 
    node->next = node->next->next; 
    delete removeNode; 
    _size--; 
}

void LinkedList2::removeFront(){
    remove(0);
}

void LinkedList2::removeBack(){
    remove(_size - 1);
}

long long int LinkedList2::findIndex(const ValueType& value) const{
    Node* tmp = _head; 
    size_t i = 0; 
    size_t j = 0; 
    while(i<_size){ 
        i++; 
        if(tmp->value == value){ 
            j = i; 
            i = _size; 
            return j; 
        } 
        tmp = tmp->next;
    } 
    if(j==0){ 
        return 0; 
    } 
}

LinkedList2::Node* LinkedList2::findNode(const ValueType& value) const{
    size_t i = 0; 
    size_t j = 0; 
    Node* tmp = _head; 
    while(i < _size){ 
        i++; 
        if(tmp->value == value){ 
            i=_size; 
            j=1; 
            return tmp; 
        } 
        tmp = tmp->next;
    } 
    if(j==0){ 
        return nullptr; 
    }
}

void LinkedList2::reverse(){
    Node *tmp = _head;
    Node *next = nullptr;
    Node *last = nullptr;
    while(tmp->next){
        next = tmp->next;
        tmp->next = last;
        last = tmp;
        tmp = next;
    }
    _head = last;
}

LinkedList2 LinkedList2::reverse() const{
    if(_size == 0){
        return LinkedList2();
    }
    else{
    	LinkedList2 buf(*this);
    	buf.reverse();
    	return buf;
    }
}

LinkedList2 LinkedList2::getReverseList() const{
	if(_size == 0){
        return LinkedList2();
    }
    else{
    	LinkedList2 buf(*this);
    	buf.reverse();
    	return buf;
    }
}

size_t LinkedList2::size() const{
	return _size;
}

void LinkedList2::forceNodeDelete(Node* node){
	if (node == nullptr){
		return;
	}
	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}

