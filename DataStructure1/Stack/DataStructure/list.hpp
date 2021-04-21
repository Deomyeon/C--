#pragma once

#include <stdlib.h>
#include "node.hpp"

namespace std
{
	template <typename _Ty>
	class list
	{
	private:
		node<_Ty>* _begin;
		node<_Ty>* _end;
		size_t _size;
	public:

		list();
		list(size_t size);
		list(_Ty element, size_t size);
		~list();

		inline size_t size() const { return this->_size; }
		inline node<_Ty>* begin() const { return this->_begin; }
		inline node<_Ty>* end() const { return this->_end; }
		void push_back(_Ty element);
		void pop_back();
		void push_front(_Ty element);
		void pop_front();
		void insert(size_t index, _Ty element);
		void erase(size_t index);
		_Ty operator [](size_t index);
		_Ty operator *(node<_Ty>* address);

	};

	template <typename _Ty>
	list<_Ty>::list()
	{
		this->_size = 0;
		this->_begin = (node<_Ty>*)NULL;
		this->_end = (node<_Ty>*)malloc(sizeof(node<_Ty>));
		this->_end->prev = this->_begin;
	}

	template <typename _Ty>
	list<_Ty>::list(size_t size)
	{
		this->_size = size;
		node<_Ty>* _node = (node<_Ty>*)malloc(sizeof(node<_Ty>));
		_node->value = 0;
		this->_begin = _node;
		_node->prev = (node<_Ty>*)NULL;
		for (size_t i = 0; i < size - 1; i++)
		{
			node<_Ty>* temp = _node;
			_node = (node<_Ty>*)malloc(sizeof(node<_Ty>));

			temp->next = _node;
			_node->prev = temp;
			_node->value = 0;

			if (i == size - 2)
			{
				_node->next = (node<_Ty>*)NULL;
				this->_end = (node<_Ty>*)malloc(sizeof(node<_Ty>));
				this->_end->prev = _node;
			}
		}
	}

	template <typename _Ty>
	list<_Ty>::list(_Ty element, size_t size)
	{
		this->_size = size;
		node<_Ty>* _node = (node<_Ty>*)malloc(sizeof(node<_Ty>));
		_node->value = element;
		this->_begin = _node;
		_node->prev = (node<_Ty>*)NULL;
		for (size_t i = 0; i < size - 1; i++)
		{
			node<_Ty>* temp = _node;
			_node = (node<_Ty>*)malloc(sizeof(node<_Ty>));

			temp->next = _node;
			_node->prev = temp;
			_node->value = element;

			if (i == size - 2)
			{
				_node->next = (node<_Ty>*)NULL;
				this->_end = (node<_Ty>*)malloc(sizeof(node<_Ty>));
				this->_end->prev = _node;
			}
		}
	}

	template <typename _Ty>
	list<_Ty>::~list()
	{
		node<_Ty>* temp = this->_begin;
		node<_Ty>* del = temp;
		for (size_t i = 0; i < this->_size; i++)
		{
			del = temp;
			temp = temp->next;
			free(del);
		}
		free(this->_end);
	}

	template <typename _Ty>
	void list<_Ty>::push_back(_Ty element)
	{
		node<_Ty>* _node = (node<_Ty>*)malloc(sizeof(node<_Ty>));
		if (this->_end->prev == (node<_Ty>*)NULL)
		{
			this->_end->prev = _node;
			_node->prev = (node<_Ty>*)NULL;
			_node->next = (node<_Ty>*)NULL;
			this->_begin = _node;
		}
		else
		{
			this->_end->prev->next = _node;
			_node->prev = this->_end->prev;
			_node->next = (node<_Ty>*)NULL;
			this->_end->prev = _node;
		}
		_node->value = element;
		this->_size++;
	}

	template <typename _Ty>
	void list<_Ty>::push_front(_Ty element)
	{
		node<_Ty>* _node = (node<_Ty>*)malloc(sizeof(node<_Ty>));
		if (this->_begin == (node<_Ty>*)NULL)
		{
			this->_end->prev = _node;
			_node->prev = (node<_Ty>*)NULL;
			_node->next = (node<_Ty>*)NULL;
			this->_begin = _node;
		}
		else
		{
			this->_begin->prev = _node;
			_node->next = this->_begin;
			_node->prev = (node<_Ty>*)NULL;
			this->_begin = _node;
		}
		_node->value = element;
		this->_size++;
	}

	template <typename _Ty>
	void list<_Ty>::pop_back()
	{
		if (this->_size == 0)
			return;
		node<_Ty>* temp = this->_end->prev;
		if (this->_size == 1)
		{
			this->_begin = (node<_Ty>*)NULL;
			this->_end->prev = (node<_Ty>*)NULL;
		}
		else
		{
			temp->prev->next = (node<_Ty>*)NULL;
			this->_end->prev = temp->prev;
		}
		free(temp);
		this->_size--;
	}

	template <typename _Ty>
	void list<_Ty>::pop_front()
	{
		if (this->_size == 0)
			return;
		node<_Ty>* temp = this->_begin;
		if (this->_size == 1)
		{
			this->_begin = (node<_Ty>*)NULL;
			this->_end->prev = (node<_Ty>*)NULL;
		}
		else
		{
			temp->next->prev = (node<_Ty>*)NULL;
			this->_begin = temp->next;
		}
		free(temp);
		this->_size--;
	}

	template <typename _Ty>
	void list<_Ty>::insert(size_t index, _Ty element)
	{
		node<_Ty>* pivot = this->_begin;
		for (size_t i = 0; i < index; i++)
		{
			pivot = pivot->next;
		}
		if (pivot == (node<_Ty>*)NULL)
			return;
		node<_Ty>* _node = (node<_Ty>*)malloc(sizeof(node<_Ty>));
		if (pivot->prev == (node<_Ty>*)NULL)
		{
			this->_begin = _node;
			_node->prev = (node<_Ty>*)NULL;
		}
		else
		{
			pivot->prev->next = _node;
			_node->prev = pivot->prev;
		}
		pivot->prev = _node;
		_node->next = pivot;
		_node->value = element;
		this->_size++;
	}

	template <typename _Ty>
	void list<_Ty>::erase(size_t index)
	{
		node<_Ty>* pivot = this->_begin;
		for (size_t i = 0; i < index; i++)
		{
			pivot = pivot->next;
		}
		pivot->prev->next = pivot->next;
		pivot->next->prev = pivot->prev;
		free(pivot);
		this->_size--;
	}



	template <typename _Ty>
	_Ty list<_Ty>::operator [](size_t index)
	{
		if (index <= this->_size)
		{
			node<_Ty>* pivot = this->_begin;
			for (size_t i = 0; i < index; i++)
			{
				pivot = pivot->next;
			}
			return pivot->value;
		}
		else
			return _Ty();
	}

	template <typename _Ty>
	_Ty list<_Ty>::operator *(node<_Ty>* address)
	{
		bool isExist = false;
		node<_Ty>* pivot = this->_begin;
		for (size_t i = 0; i < this->_size; i++)
		{
			if (pivot == address)
				isExist = true;
			pivot = pivot->next;
		}
		if (isExist)
			return address->value;
		else
			return _Ty();
	}
}