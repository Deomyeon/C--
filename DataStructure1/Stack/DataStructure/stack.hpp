#pragma once
#include "vector.hpp"

namespace std
{
    template <typename _Ty, class _Container = vector<_Ty>>
    class stack
    {
    private:
        _Container _data;
        _Ty* _top;
        _Ty* _bottom;
    public:
        stack();
        stack(size_t size);
        stack(_Ty element, size_t size);
        ~stack();

        inline _Ty top() const { return *this->_top; }
        void push(_Ty element);
        void pop();
    };


    template <typename _Ty, class _Container>
    stack<_Ty, _Container>::stack()
    {
        this->_bottom = this->_data.start();
        this->_top = this->_data.end() - 1;
    }

    template <typename _Ty, class _Container>
    stack<_Ty, _Container>::stack(size_t size)
    {
        this->_data(size);
        this->_bottom = this->_data.start();
        this->_top = this->_data.end() - 1;
    }

    template <typename _Ty, class _Container>
    stack<_Ty, _Container>::stack(_Ty element, size_t size)
    {
        this->_data(element, size);
        this->_bottom = this->_data.start();
        this->_top = this->_data.end() - 1;
    }

    template <typename _Ty, class _Container>
    stack<_Ty, _Container>::~stack()
    {
        this->_bottom = (_Ty*)NULL;
        this->_top = (_Ty*)NULL;
    }

    template <typename _Ty, class _Container>
    void stack<_Ty, _Container>::push(_Ty element)
    {
        this->_data.push_back(element);
        this->_bottom = this->_data.start();
        this->_top = this->_data.end() - 1;
    }

    template <typename _Ty, class _Container>
    void stack<_Ty, _Container>::pop()
    {
        this->_data.pop_back();
        this->_top = this->_data.end() - 1;
    }
}