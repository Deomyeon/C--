#pragma once

#include "list.hpp"

namespace std
{
	template <typename _Ty, class _Container = list<_Ty>>
	class queue
	{
	private:
		_Ty* _front;
		_Ty* _back;
		_Container _data;
	public:

		queue();
		queue(size_t size);
		queue(_Ty element, size_t size);
		~queue();

		inline size_t size() const { return this->_data.size(); }
		inline bool empty() const { return !this->_data.size(); }
		inline _Ty front() const { return *this->_front; }
		inline _Ty back() const { return *this->_back; }
		void push(_Ty element);
		void pop();

	};

	template <typename _Ty, class _Container>
	queue<_Ty, _Container>::queue()
	{
		this->_front = &this->_data.begin()->value;
		this->_back = &this->_data.end()->prev->value;
	}

	template <typename _Ty, class _Container>
	queue<_Ty, _Container>::queue(size_t size)
	{
		this->_data(size);
		this->_front = &this->_data.begin()->value;
		this->_back = &this->_data.end()->prev->value;
	}

	template <typename _Ty, class _Container>
	queue<_Ty, _Container>::queue(_Ty element, size_t size)
	{
		this->_data(element, size);
		this->_front = &this->_data.begin()->value;
		this->_back = &this->_data.end()->prev->value;
	}

	template <typename _Ty, class _Container>
	queue<_Ty, _Container>::~queue()
	{
		this->_front = (_Ty*)NULL;
		this->_back = (_Ty*)NULL;
	}

	template <typename _Ty, class _Container>
	void queue<_Ty, _Container>::push(_Ty element)
	{
		this->_data.push_back(element);
		this->_front = &this->_data.begin()->value;
		this->_back = &this->_data.end()->prev->value;
	}

	template <typename _Ty, class _Container>
	void queue<_Ty, _Container>::pop()
	{
		this->_data.pop_front();
		this->_front = &this->_data.begin()->value;
		this->_back = &this->_data.end()->prev->value;
	}
}