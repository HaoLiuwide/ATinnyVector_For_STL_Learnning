#pragma once
#ifndef _ITERATOR_H_
#define _ITERATOR_H_
#include<cstddef> //for size_t,ptrdii_t
/*所有STL的迭代器都应该继承自iterator，便于萃取iterator指向的对象类型
STL也提供了这一文件，可以通过以下代码使用内置的iterator文件

#include<iterator>
template<typename T>
struct MyIterator:
    public std::iterator<std::forward_iterator_tag, T>
{
        
};
*/
//五种迭代器类型，输入，输出，单向，双向，随机迭代器  （对于++，--，+n等的支持不一样）
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag:public input_iterator_tag {};
struct bidirectional_tag : public forward_iterator_tag {};
struct random_access_iterator_tag:public bidirectional_tag {};

//迭代器
template<
    typename Category, 
    typename T,
    typename Distance = ptrdiff_t,
    typename Pointer = T*,
    typename Reference = T& >
struct iterator
{
    using iterator_category = Category;        //迭代器的类型
    using value_type = T;                      //迭代器所指对象的类型
    using difference_type = Distance;          //指针相减的类型
    using pointer = Pointer;                  //指针的类型
    using reference = Reference;              //引用的类型
};
#endif // !_ITERATOR_H_

