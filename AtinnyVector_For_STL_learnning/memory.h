#pragma once
#ifndef _MEMORY_H_
#define _MEMORY_H_            
//��construct��destroy��unintialized_fill_n,unintialized_copy,unintialized_fill ����ڴ�����������
/*
construct����������ڴ��Ͻ�������
destory�������ڴ��ϵĶ���
unintialized_fill_n(ForwardIterator start, size_type n, const value_type& x)����ʼ���ڴ棬���n������
unintialized_fill(ForwardIterator start, ForwardIterator end, const value_type& x)����ʼ��[start,end)����ڴ�Ϊx
unintialized_copy(ForwardIterator start, ForwardIterator end, ForwardIterator output)����[start,end)��Ķ����ʼ���ڴ�output
*/
#include<algorithm>  //for copy
#include "type_traits.h"
#include "iterator_traits.h"
//construct����ʼ��pointer�����ڴ�Ϊvalue
namespace LH                
{
	template<typename T1, typename T2>
	inline void construct(T1* pointer, const T2& value) { ::new(pointer) T1(value); }     //�ٶ�placement new 

}
//destory���������󣬰��������汾������һ�����������[start��end)�����еĶ���
namespace LH
{
	//����һ������
	template<typename T>
	inline void destory(T* pointer) { pointer->~T(); }

	//֧��_destory����������[start��end)�����еĶ���
	//_true_type Ϊ��trivial_destructor�����ͣ���ԭ�����ͣ�
	//_false_type Ϊû��trivial_destructor�����ͣ����û��Զ�������ͣ�
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
	//֧��destory����������[start��end)�����еĶ���
	template<typename ForwardIterator, typename T>
	inline void _destory(ForwardIterator start, ForwardIterator end, T*)
	{
		using trivial_destructor = typename type_traites<T>::has_trivial_destructor;
		_destory_aux(start, end, trivial_destructor());
	}

	//����[start��end)�����еĶ���
	template<typename ForwardIterator>
	inline void destory(ForwardIterator start, ForwardIterator end)
	{
		_destory(start, end, value_type(start));
	}
}
//unintialized_fill_n����ʼ���ӵ�����start��ʼ��n���ڴ�Ϊx��
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

	//��ʼ��������start��n���ڴ�Ϊx��
	template<typename ForwardIterator, typename Size,typename T>
	inline ForwardIterator unintialized_fill_n(ForwardIterator start, Size n, const T& x)
	{
		return _unintialized_fill_n(start, n, x, value_type(start));
	}
}
//unintialized_fill����ʼ��[start��end)�����еĶ���Ϊx��
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
	//��ʼ��[start��end)�����еĶ���Ϊx��
	template<typename ForwardIterator, typename T>
	inline void unintialized_fill(ForwardIterator start, ForwardIterator end, const T& x)
	{
		_unintialized_fill(start, end, x, value_type(start));
	}
}
//unintialized_copy��ʹ��[start��end)����ָ��������ʼ��result��
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
	//ʹ��[start��end)����ָ��������ʼ��result��
	template<typename InputIterator,typename OutputIterator>
	inline OutputIterator unintialized_copy(InputIterator start, InputIterator end, OutputIterator result)
	{
		return _unintialized_copy(start, end, result, value_type(start));
	}
}
#endif // !_MEMORY_H_
