#pragma once

template<typename _Ty>
class node
{
public:
	_Ty value;
	node<_Ty>* prev;
	node<_Ty>* next;
};