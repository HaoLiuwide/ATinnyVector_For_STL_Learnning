#pragma once
#ifndef _VECTOR_H_
#define _VECTOR_H_
#include<cstddef>   //for size_t, ptrdiff_t
#include "allocator.h"
#include "memory.h"
namespace LH
{
	template<typename T>
	class vector
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using iterator = value_type*;
		using reference = value_type&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
	private:
		iterator _start;
		iterator _finish;
		iterator _endOfStorage;
	private:          //初始化时需要
		//通过allocator申请n个value_type大小的内存，初始化为x
		using data_allocator = allocator<value_type> ;
		iterator allocate_fill(size_type n, const T& x)  
		{
			iterator result = data_allocator::allocate(n);
			unintialized_fill_n(result, n, x);
			return result;
		}
		//初始化_start,_finish,_endOfStorage;
		void fill_initialize(size_type n, const T& value)
		{
			_start = allocate_fill(n, value);
			_finish = _start + n;
			_endOfStorage = _finish;
		}
		//释放申请的空间
		void deallocate()
		{
			if (_start) data_allocator::deallocate(begin(), size());
		}
	public://常见的接口函数
		iterator begin() const { return _start; }
		iterator end() const { return _finish; }
		size_type size() const { return size_type(end() - begin()); }
		size_type capacity() const { return size_type(_endOfStorage - begin()); }
		bool empty() const { return begin() == end(); }
		reference operator[](size_type n) { return *(begin() + n); }

	public://构造函数和析构函数
		vector() :_start(0), _finish(0), _endOfStorage(0) {}
		vector(size_type n, const T& value) { fill_initialize(n, value); }
		explicit vector(size_type n) { fill_initialize(n, T()); }
		vector(const vector& in)
		{
			_start = data_allocator::allocate(in.size());
			_finish = unintialized_copy(in.begin(), in.end(), _start);
			_endOfStorage = _finish;
		}
		vector(std::initializer_list<value_type> ilist)
		{
			_start = data_allocator::allocate(ilist.size());
			_finish = unintialized_copy(ilist.begin(), ilist.end(), _start);
			_endOfStorage = _finish;
		}
		~vector()
		{
			destory(_start, _finish);
			deallocate();
		}
	private://push_back时空间不足处理函数
		void insert_aux(value_type value)
		{
			const size_type old_size = size();
			const size_type new_size = old_size == 0 ? 1 : 2 * old_size;    //空间不足，重新申请2倍大的空间，copy原空间到新空间
			iterator new_start = data_allocator::allocate(new_size * sizeof(T));
			iterator new_finish = new_start;
			new_finish = unintialized_copy(_start, _finish, new_start);
			construct(new_finish, value);
			++new_finish;

			destory(begin(), end());
			deallocate();

			_start = new_start;
			_finish = new_finish;
			_endOfStorage = _start + new_size;
		}
	public://push_back,pop_back
		void push_back(value_type value)
		{
			if (_finish != _endOfStorage)
			{
				construct(_finish, value);
				++_finish;
			}
			else
			{
				insert_aux(value);
			}
		}
		void pop_back()
		{
			--_finish;
			destory(_finish);
		}

	};
}
#endif // !_VECTOR_H_

