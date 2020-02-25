#pragma once
#ifndef _SIMPLEALLOC_H_
#define _SIMPLEALLOC_H_
#include<cstddef> //for size_t,ptrdiff_t
#include<new>    //for malloc,free
#include<cstdlib>  //for exit()
#include<iostream>  //for cerr
namespace LH
{
	template<typename T>
	class simpleAlloc
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using iterator = value_type*;
		using reference = value_type&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
	public://对于malloc和free的简单封装
		static void* allocate(size_type n)
		{
			void* result = malloc(n);
			if (result == 0)
			{
				std::cerr << "out of memmory" << std::endl;
				exit(1);
			}
			return result;
		}
		static void deallocate(T* p, size_type) { free(p); }

	};
}
#endif // !_SIMPLEALLOC_H_
