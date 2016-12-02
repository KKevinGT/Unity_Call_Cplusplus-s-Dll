#define EXPORTBUILD

#include "test.h"
#include <iostream>

_DLLExport int cpp_get_int_value()
{
	return 51;
}

_DLLExport void cpp_get_int_ptr(int* value)
{
	*value = 52;
}

_DLLExport void cpp_get_int_ref(int& value)
{
	value = 53;
}

_DLLExport float cpp_get_float_value()
{
	return 51.1f;
}

_DLLExport void cpp_get_float_ptr(float* value)
{
	*value = 52.1f;
}

_DLLExport void cpp_get_float_ref(float& value)
{
	value = 53.1f;
}

_DLLExport void cpp_get_string_value(char** str_ptr)
{
	char* str = "hello world";
	strcpy(*str_ptr, str);
	return;
}

struct cpp_struct_one
{
	int value1;
	float value2;
};

_DLLExport void cpp_get_struct_one_value(cpp_struct_one* stu)
{
	stu->value1 = 10;
	stu->value2 = 10.1f;
	return;
}

_DLLExport void cpp_get_struct_one_value2(cpp_struct_one& stu)
{
	stu.value1 = 11;
	stu.value2 = 11.1f;
	return;
}

_DLLExport void cpp_get_struct_one_value3(cpp_struct_one* stu)
{
	stu->value1 = 12;
	stu->value2 = 12.1f;
	return;
}

struct cpp_struct_two
{
	int value1[10];
	float value2;
};

_DLLExport void cpp_get_struct_two_value(cpp_struct_two* stu, int count)
{
	for (int i = 0; i < count; i++)
	{
		stu->value1[i] = i;
	}
	stu->value2 = 10.1f;
	return;
}

_DLLExport void cpp_get_int_arr1(int* arr, int count)
{
	for (int i = 0; i < count; i++)
	{
		arr[i] = i;
	}
	return;
}

_DLLExport void cpp_get_int_arr2(int* arr, int count)
{
	for (int i = 0; i < count; i++)
	{
		arr[i] = i;
	}
	return;
}

_DLLExport void cpp_get_int_arr3(int* arr, int count)
{
	for (int i = 0; i < count; i++)
	{
		arr[i] = i;
	}
	return;
}

_DLLExport void cpp_set_string_value(char* s)
{
	std::string str = s;
	printf("str %s length %d", str.c_str(), str.length());
	return;
}