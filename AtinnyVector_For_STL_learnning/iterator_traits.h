#pragma once
#ifndef _ITERATOR_TRAITS_H_
#define _ITERATOR_TRAITS_H_
#include"iterator.h"
namespace LH
{
	template<typename Iterator>
	struct iterator_traits
	{
		using iterator_category = typename Iterator::iterator_category;
		using  value_type = typename Iterator::value_type;
		using difference_type = typename Iterator::difference_type;
		using pointer = typename Iterator::pointer;
		using reference = typename Iterator::reference;
	};
	//����ԭ��ָ����ػ�
	template<typename T>
	struct iterator_traits<T*>
	{
		using iterator_category = random_access_iterator_tag;
		using  value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;
	};
	//���constԭ��ָ����ػ�
	template<typename T>
	struct iterator_traits<const T*>
	{
		using iterator_category = random_access_iterator_tag;
		using  value_type = T;           //����const T
		using difference_type = ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;
	};

	//��������õ�����������
	template<typename Iterator>
	inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&)
	{
		using category = typename iterator_traits<Iterator>::iterator_category;
		return category();
	}
	//��������õ�������ָ���������
	template<typename Iterator>
	inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}
}
#endif // !_ITERATOR_TRAITS_H_

