#include <iostream>
using namespace std;

template <typename T>
class SinglyLinkedList
{
private:
	struct Node
	{
		T data;
		Node* next;

		Node(const T& data)
		{
			this->data = data;
			next = nullptr;
		}
	};

	Node* head;
	Node* tail;

public:
	SinglyLinkedList();
	SinglyLinkedList(std::initializer_list<T>);
	
	SinglyLinkedList(const SinglyLinkedList<T>& other);
	SinglyLinkedList(SinglyLinkedList<T>&& other) noexcept;

	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
	SinglyLinkedList<T>& operator=(SinglyLinkedList<T>&& other) noexcept;

	~SinglyLinkedList();

private:
	void copyFrom(const SinglyLinkedList<T>& other);
	void moveFrom(SinglyLinkedList<T>&& other);

	void free();

public:
	void push_front(const T& el);
	void push_back(const T& el);

	void pop_front();

	const T& front();
	const T& back();

	bool empty() const;

	template <typename U>
	friend SinglyLinkedList<U> concat(SinglyLinkedList<U>& lhs, SinglyLinkedList<U>& rhs);

	template <typename U>
	friend std::ostream& operator<<(std::ostream&, const SinglyLinkedList<U>&);
};

template <typename T>
void SinglyLinkedList<T>::push_front(const T& el)
{
	Node* newNode = new Node(el);

	if (!head)
	{
		head = tail = newNode;
		return;
	}

	newNode->next = head;
	head = newNode;
}
template <typename T>
void SinglyLinkedList<T>::push_back(const T& el)
{
	Node* newNode = new Node(el);

	if (!tail)
	{
		head = tail = newNode;
		return;
	}

	tail->next = newNode;
	tail = newNode;
}

template <typename T>
void SinglyLinkedList<T>::pop_front()
{
	if (!head)
		throw length_error("Empty list!");

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
		return;
	}

	Node* toDelete = head;
	head = head->next;
	delete toDelete;
}

template <typename T>
const T& SinglyLinkedList<T>::front()
{
	if (!head)
		throw length_error("Empty list!");

	return head->data;
}
template <typename T>
const T& SinglyLinkedList<T>::back()
{
	if (!tail)
		throw length_error("Empty list!");

	return tail->data;
}

template <typename T>
bool SinglyLinkedList<T>::empty() const
{
	return head == nullptr;
}

template <typename T>
SinglyLinkedList<T> concat(SinglyLinkedList<T>& lhs, SinglyLinkedList<T>& rhs)
{
	SinglyLinkedList<T> result;

	if (!lhs.head)
	{
		result.head = rhs.head;
		result.tail = rhs.tail;
	}
	else if (!rhs.head)
	{
		result.head = lhs.head;
		result.tail = lhs.tail;
	}
	else
	{
		lhs.tail->next = rhs.head;
		result.head = lhs.head;
		result.tail = rhs.tail;
	}

	rhs.head = rhs.tail = lhs.head = lhs.tail = nullptr;

	return result;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
{
	head = tail = nullptr;
}
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(std::initializer_list<T> iList)
{
	for (const T& el : iList)
		push_back(el);
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
{
	copyFrom(other);
}
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	free();
}

template <typename T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList<T>& other)
{
	Node* iter = other.head;

	while (iter)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}
template <typename T>
void SinglyLinkedList<T>::moveFrom(SinglyLinkedList<T>&& other)
{
	this->head = other.head;
	other.head = other.tail = nullptr;
}

template <typename T>
void SinglyLinkedList<T>::free()
{
	Node* iter = head;

	while (iter)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}

	head = tail = nullptr;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& l)
{
	typename SinglyLinkedList<T>::Node* iter = l.head;

	while (iter)
	{
		os << iter->data << ' ';
		if (iter->next)
			os << "->" << ' ';
		iter = iter->next;
	}
	
	return os;
}
