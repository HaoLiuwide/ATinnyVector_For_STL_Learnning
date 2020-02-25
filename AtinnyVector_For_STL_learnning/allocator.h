#pragma once
#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include<cstddef>     //for size_t,ptrdiff_t
#include "simpleAlloc.h"
namespace LH
{
	template<typename T, class Alloc = simpleAlloc<T>>  //默认使用simpleAlloc配置器，可自定义
	class allocator
	{
	public:
		using value_type = T;           
		using pointer = value_type*;
		using iterator = value_type*;
		using reference = value_type&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
	public:    //传递调用simpleAlloc
		static value_type* allocate(size_type n) {return n == 0 ? 0 : (T*)Alloc::allocate(n * sizeof(T)); }
		static value_type* allocate(void) { return (T*)Alloc::allocate(sizeof(T)); }
		static void deallocate(T* p, size_type n) { if (n != 0) Alloc::deallocate(p, n * sizeof(T)); }
		static void deallocate(T * p) { Alloc::deallocate(p, sizeof(T)); }
	};
}
#endif // !_ALLOCATOR_H_

