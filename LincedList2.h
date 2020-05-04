#pragma once

// потом поменяем на шаблоны
using ValueType = double;

class LinkedList2

{

	// класс узла списка
	// по своей сути, может содержать любые данные,
	// можно реализовать и ассоциативный массив, просто добавив 
	// поле с ключем в узел и, с учетом этого, поменять методы LinkedList 
	// (доступ по ключу, поиск по ключу и т.д.)
	struct Node {
		Node(const ValueType& value, Node* next = nullptr, Node* last = nullptr); //+
		~Node(); //+

		void insertNext(const ValueType& value); //+
		void removeNext(); //+

		ValueType value;
		Node* next;
		Node* last;

	};

public:

	////

	LinkedList2(); //+
	LinkedList2(const LinkedList2& copyList);
	LinkedList2& operator=(const LinkedList2& copyList);

	LinkedList2(LinkedList2&& moveList) noexcept;
	LinkedList2& operator=(LinkedList2&& moveList) noexcept;

	~LinkedList2(); //+

	////

	// доступ к значению элемента по индексу
	ValueType& operator[](const size_t pos) const; //+

	// доступ к узлу по индексу
	LinkedList2::Node* getNode(const size_t pos) const; //+

	// вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
	void insert(const size_t pos, const ValueType& value); //+

	// вставка элемента после узла, (O(1))
	//static 
	void insertAfterNode(Node* node, const ValueType& value); //+

	// вставка в конец (О(n))
	void pushBack(const ValueType& value); //+

	// вставка в начало (О(1))
	void pushFront(const ValueType& value);  //+

	// удаление
	void remove(const size_t pos); //+
	void removeNextNode(Node* node);
	void removeFront(); 
	void removeBack();  

	// поиск, О(n)
	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	// разворот списка
	void reverse();						// изменение текущего списка       +
	LinkedList2 reverse() const;			// полчение нового списка (для константных объектов)
	LinkedList2 getReverseList() const;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список

	size_t size() const;

private:
	Node*	_head;
	Node*   _tail;
	size_t	_size;

	void forceNodeDelete(Node* node); //+
	
};
