#pragma once
#ifndef _TYPE_TRAITES_H_
#define _TYPE_TRAITES_H_
namespace LH
{
	struct _true_type {};
	struct _false_type {};

	//默认所有类型的参数均为_false_type；
	template<typename T> 
	struct type_traites
	{
		using this_dummy_member_nust_be_first = _true_type;


		using has_trivial_default_constructor = _false_type;
		using has_trivial_copy_constructor = _false_type;
		using has_trivial_assignment_operator = _false_type;
		using has_trivial_destructor = _false_type;
		using is_POD_type = _false_type;
		
	};
	//以下特化char，int，double等常见类型为_true_type
	template<>
	struct type_traites<char>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traites<signed char>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traites<unsigned char>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traites<short>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traites<unsigned short>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traites<int>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traites<unsigned int>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traites<long>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traites<unsigned long>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traites<float>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traites<double>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traites<long double>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

	template<typename T>
	struct type_traites<T*>
	{
		using has_trivial_default_constructor = _true_type;
		using has_trivial_copy_constructor = _true_type;
		using has_trivial_assignment_operator = _true_type;
		using has_trivial_destructor = _true_type;
		using is_POD_type = _true_type;
	};

}
#endif // !_TYPE_TRAITES_H_

