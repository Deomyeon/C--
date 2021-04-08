#pragma once
#include <stdlib.h>

namespace std
{
    template <typename _Ty>
    class vector
    {
    private:
        _Ty* _data;
        size_t _size;
        size_t _realSize;
        _Ty* _begin;
        _Ty* _end;
    public:
        vector();
        vector(size_t size);
        vector(_Ty element, size_t size);
        ~vector();

        inline size_t size() const { return this->_size; }
        bool reserve(size_t size);
        bool push_back(_Ty element);
        void pop_back();
        inline _Ty* const begin() { return this->_begin; }
        inline _Ty* const end() { return this->_end; }

        _Ty operator [](size_t index) const;
        _Ty operator *(_Ty* address) const;
    };

    template <typename _Ty>
    vector<_Ty>::vector()
    {
        this->_data = (_Ty*)malloc(0);
        this->_begin = (_Ty*)NULL;
        this->_end = this->_data;
        this->_size = 0;
        this->_realSize = 0;
    }

    template <typename _Ty>
    vector<_Ty>::vector(size_t size)
    {
        this->_data = (_Ty*)malloc(sizeof(_Ty) * size);
        this->_begin = (this->_data);
        this->_end = (this->_data + size);
        this->_size = size;
        this->_realSize = size;
        for (_Ty* point = this->_begin; point < this->_end; point++)
        {
            *point = _Ty();
        }
    }

    template <typename _Ty>
    vector<_Ty>::vector(_Ty element, size_t size)
    {
        this->_data = (_Ty*)malloc(sizeof(_Ty) * size);
        this->_begin = (this->_data);
        this->_end = (this->_data + size);
        this->_size = size;
        this->_realSize = size;
        for (_Ty* point = this->_begin; point < this->_end; point++)
        {
            *point = element;
        }
    }

    template <typename _Ty>
    vector<_Ty>::~vector()
    {
        this->_begin = (_Ty*)NULL;
        this->_end = (_Ty*)NULL;
        free(this->_data);
        this->_data = (_Ty*)NULL;
        this->_size = 0;
        this->_realSize = 0;
    }

    template <typename _Ty>
    bool vector<_Ty>::reserve(size_t size)
    {
        void* temp = realloc((void*)this->_data, sizeof(_Ty) * size);
        if (temp != NULL)
        {
            this->_data = (_Ty*)temp;
            this->_begin = (this->_data);
            this->_end = (this->_data + size);
            if (this->_size > size)
                this->_size = size;
            this->_realSize = size;
            for (_Ty* point = this->_begin + this->_size; point < this->_end; point++)
            {
                *point = _Ty();
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename _Ty>
    bool vector<_Ty>::push_back(_Ty element)
    {
        this->_size++;
        if (this->_realSize == this->_size - 1)
        {
            void* temp = realloc((void*)this->_data, sizeof(_Ty) * this->_size);
            if (temp != NULL)
            {
                this->_data = (_Ty*)temp;
                this->_begin = (this->_data);
                this->_realSize = this->_size;
            }
            else
            {
                this->_size--;
                return false;
            }
        }
        this->_end = (this->_begin + this->_size);
        this->_data[this->_size - 1] = element;
        return true;
    }

    template <typename _Ty>
    void vector<_Ty>::pop_back()
    {
        this->_size--;
        this->_end = (this->_begin + this->_size);
        *(this->_end) = _Ty();
    }

    template <typename _Ty>
    _Ty vector<_Ty>::operator[](size_t index) const
    {
        if (index < this->_size)
        {
            return this->_data[index];
        }
        else
        {
            return _Ty();
        }
    }

    template <typename _Ty>
    _Ty vector<_Ty>::operator *(_Ty* address) const
    {
        if (address < this->_end)
        {
            return this->_data[address - this->_begin];
        }
        else
        {
            return _Ty();
        }
    }
}