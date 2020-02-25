#pragma once
#ifndef _ITERATOR_H_
#define _ITERATOR_H_
#include<cstddef> //for size_t,ptrdii_t
/*����STL�ĵ�������Ӧ�ü̳���iterator��������ȡiteratorָ��Ķ�������
STLҲ�ṩ����һ�ļ�������ͨ�����´���ʹ�����õ�iterator�ļ�

#include<iterator>
template<typename T>
struct MyIterator:
    public std::iterator<std::forward_iterator_tag, T>
{
        
};
*/
//���ֵ��������ͣ����룬���������˫�����������  ������++��--��+n�ȵ�֧�ֲ�һ����
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag:public input_iterator_tag {};
struct bidirectional_tag : public forward_iterator_tag {};
struct random_access_iterator_tag:public bidirectional_tag {};

//������
template<
    typename Category, 
    typename T,
    typename Distance = ptrdiff_t,
    typename Pointer = T*,
    typename Reference = T& >
struct iterator
{
    using iterator_category = Category;        //������������
    using value_type = T;                      //��������ָ���������
    using difference_type = Distance;          //ָ�����������
    using pointer = Pointer;                  //ָ�������
    using reference = Reference;              //���õ�����
};
#endif // !_ITERATOR_H_

