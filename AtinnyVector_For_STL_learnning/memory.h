#pragma once
#ifndef _MEMORY_H_
#define _MEMORY_H_            
//由construct，destroy，unintialized_fill_n,unintialized_copy,unintialized_fill 五个内存操作工具组成
/*
construct：在申请的内存上建立对象
destory：销毁内存上的对象
unintialized_fill_n(ForwardIterator start, size_type n, const value_type& x)：初始化内存，填充n个对象
unintialized_fill(ForwardIterator start, ForwardIterator end, const value_type& x)：初始化[start,end)间的内存为x
unintialized_copy(ForwardIterator start, ForwardIterator end, ForwardIterator output)：用[start,end)间的对象初始化内存output
*/
#include<algorithm>  //for copy
#include "type_traits.h"
#include "iterator_traits.h"
//construct：初始化pointer处的内存为value
namespace LH                
{
	template<typename T1, typename T2>
	inline void construct(T1* pointer, const T2& value) { ::new(pointer) T1(value); }     //百度placement new 

}
//destory：析构对象，包括两个版本（析构一个对象和析构[start，end)间所有的对象）
namespace LH
{
	//析构一个对象
	template<typename T>
	inline void destory(T* pointer) { pointer->~T(); }

	//支持_destory函数（析构[start，end)间所有的对象）
	//_true_type 为有trivial_destructor的类型（即原生类型）
	//_false_type 为没有trivial_destructor的类型（即用户自定义的类型）
	template<typename ForwardIterator>
	inline void _destory_aux(ForwardIterator start, ForwardIterator end, _true_type) {}

	template<typename ForwardIterator>
	inline void _destory_aux(ForwardIterator start, ForwardIterator end, _false_type)
	{
		while (start != end)
		{
			destory(&*start);
			start++;
		}
	}
	//支持destory函数（析构[start，end)间所有的对象）
	template<typename ForwardIterator, typename T>
	inline void _destory(ForwardIterator start, ForwardIterator end, T*)
	{
		using trivial_destructor = typename type_traites<T>::has_trivial_destructor;
		_destory_aux(start, end, trivial_destructor());
	}

	//析构[start，end)间所有的对象
	template<typename ForwardIterator>
	inline void destory(ForwardIterator start, ForwardIterator end)
	{
		_destory(start, end, value_type(start));
	}
}
//unintialized_fill_n：初始化从迭代器start开始的n块内存为x；
namespace LH
{
	template<typename ForwardIterator, typename Size, typename T>
	inline ForwardIterator _unintialized_fill_n_aux(ForwardIterator start, Size n, const T& value, _true_type)
	{
		ForwardIterator cur = start;
		for (; n > 0; --n, ++cur)
		{
			*cur = value;
		}
		return start;
	}
	template<typename ForwardIterator, typename Size, typename T>
	inline ForwardIterator _unintialized_fill_n_aux(ForwardIterator start, Size n, const T& x, _false_type)
	{
		ForwardIterator cur = start;
		for (; n > 0; --n, ++cur)			    
		{
			construct(&*cur, x);
		}
		return cur;
	}

	template<typename ForwardIterator, typename Size, typename T>
	inline ForwardIterator _unintialized_fill_n(ForwardIterator start, Size n, const T& x, T*)
	{
		using is_POD = typename type_traites<T>::is_POD_type;
		return _unintialized_fill_n_aux(start, n, x, is_POD());
	}

	//初始化迭代器start后n个内存为x；
	template<typename ForwardIterator, typename Size,typename T>
	inline ForwardIterator unintialized_fill_n(ForwardIterator start, Size n, const T& x)
	{
		return _unintialized_fill_n(start, n, x, value_type(start));
	}
}
//unintialized_fill：初始化[start，end)间所有的对象为x；
namespace LH
{
	template<typename ForwardIterator, typename T>
	inline void _unintialized_fill_aux(ForwardIterator start, ForwardIterator end, const T& value, _true_type)
	{
		for (; start != end; ++start)
			*start = value;
	}
	template<typename ForwardIterator, typename T>
	inline void _unintialized_fill_aux(ForwardIterator start, ForwardIterator end, const T& x, _false_type)
	{
		for (; start != end; ++start)
			construct(&*start, x);
	}
	template<typename ForwardIterator, typename T>
	inline void _unintialized_fill(ForwardIterator start, ForwardIterator end, const T& x, T*)
	{
		using is_POD = typename type_traites<T>::is_POD_type;
		_unintialized_fill_aux(start, end, x, is_POD());
	}
	//初始化[start，end)间所有的对象为x；
	template<typename ForwardIterator, typename T>
	inline void unintialized_fill(ForwardIterator start, ForwardIterator end, const T& x)
	{
		_unintialized_fill(start, end, x, value_type(start));
	}
}
//unintialized_copy：使用[start，end)间所指对象来初始化result；
namespace LH
{
	template<typename InputIterator, typename OutputIterator>
	inline OutputIterator _unintialized_copy_aux(InputIterator start, InputIterator end, OutputIterator result, _true_type)
	{
		while (start != end)
		{
			construct(&*result, *start);
			++start;
			++result;
		}
		return result;
	}
	template<typename InputIterator, typename OutputIterator>
	inline OutputIterator _unintialized_copy_aux(InputIterator start, InputIterator end, OutputIterator result, _false_type)
	{
		return std::copy(start, end, result);
	}
	template<typename InputIterator, typename OutputIterator, typename T>
	inline OutputIterator _unintialized_copy(InputIterator start, InputIterator end, OutputIterator result, T*)
	{
		using is_POD = typename type_traites<T>::is_POD_type;
		return _unintialized_copy_aux(start, end, result, is_POD());
	}
	//使用[start，end)间所指对象来初始化result；
	template<typename InputIterator,typename OutputIterator>
	inline OutputIterator unintialized_copy(InputIterator start, InputIterator end, OutputIterator result)
	{
		return _unintialized_copy(start, end, result, value_type(start));
	}
}
#endif // !_MEMORY_H_
