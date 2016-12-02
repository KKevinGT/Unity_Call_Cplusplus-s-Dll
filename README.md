### 摘要
unity用的很普遍，现在很多代码还是用c++写的，需要用unity去调用c++的代码。这里介绍了一种unity调用c++ dll的方法，希望有所帮助。
**我采用的软件是<font color=Red>Visual Studio 2015</font>和<font color=Red> Unity 5.3.4</font>**
![](http://images2015.cnblogs.com/blog/1014091/201609/1014091-20160913120622539-49874596.png)

------------

## 1. 建立VS DLL 工程
![](http://images2015.cnblogs.com/blog/1014091/201609/1014091-20160913120631867-909184150.png)
![](http://images2015.cnblogs.com/blog/1014091/201609/1014091-20160913120644336-2084234893.png)

------------

## 2. cpp代码编辑
**<font color=Green>test.cpp</font>**
```cpp
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
```

## 3. 构建Dll 文件
![](http://images2015.cnblogs.com/blog/1014091/201609/1014091-20160913141901398-1198271649.png)

## 4. unity 工程创建
在unity在 Assets文件下文件Plugins目录，在目录下方放入Dll文件。要是没有Plugins文件夹，就新建一个。
![](http://images2015.cnblogs.com/blog/1014091/201609/1014091-20160913142040430-1093884713.png)

## 5. unity 代码编辑
这里注意，**<font color=Red>Dll文件不需要加后缀 .dll</font>**
```cpp
using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System.Text;
using System;

public class NewBehaviourScript : MonoBehaviour {
    [DllImport("cppDll")]
    private static extern int cpp_get_int_value();

    [DllImport("cppDll")]
    private static extern void cpp_get_int_ptr(ref int value);

    [DllImport("cppDll")]
    private static extern void cpp_get_int_ref(ref int value);


    [DllImport("cppDll")]
    private static extern float cpp_get_float_value();

    [DllImport("cppDll")]
    private static extern void cpp_get_float_ptr(ref float value);

    [DllImport("cppDll")]
    private static extern void cpp_get_float_ref(ref float value);

    [DllImport("cppDll")]
    private static extern void cpp_get_string_value(ref StringBuilder ptrStr);

    [StructLayout(LayoutKind.Sequential)]
    public struct cpp_struct_one
    {
        public int value1;
        public float value2;
    };

    [DllImport("cppDll")]
    private static extern void cpp_get_struct_one_value(ref cpp_struct_one stu);


    [DllImport("cppDll")]
    private static extern void cpp_get_struct_one_value2(ref cpp_struct_one stu);

    [DllImport("cppDll")]
    private static extern void cpp_get_struct_one_value3(IntPtr stu);


    [StructLayout(LayoutKind.Sequential)]
    public struct cpp_struct_two
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public int[] value1;
        public float value2;
    };

    [DllImport("cppDll")]
    private static extern void cpp_get_struct_two_value(IntPtr stu, int count);

    [DllImport("cppDll")]
    private static extern void cpp_get_int_arr1(ref int arr, int count);

    [DllImport("cppDll")]
    private static extern void cpp_get_int_arr2(int[] arr, int count);

    [DllImport("cppDll")]
    private static extern void cpp_get_int_arr3(IntPtr arr, int count);

    [DllImport("cppDll")]
    private static extern void cpp_set_string_value(string s);
    // Use this for initialization
    void Start () {
        // 获取int类型
        int int_value = cpp_get_int_value();
        Console.WriteLine("cpp_get_int_value\t " + int_value);

        // 获取int类型 指针
        int int_ptr = new int();
        cpp_get_int_ptr(ref int_ptr);
        Console.WriteLine("cpp_get_int_ptr\t " + int_ptr);

        // 获取int类型 引用
        int int_ref = new int();
        cpp_get_int_ref(ref int_ref);
        Console.WriteLine("cpp_get_int_ref\t " + int_ref);

        // 获取float类型
        float float_value = cpp_get_float_value();
        Console.WriteLine("cpp_get_float_value\t " + float_value);

        // 获取float类型 指针
        float float_ptr = new float();
        cpp_get_float_ptr(ref float_ptr);
        Console.WriteLine("cpp_get_float_ptr\t " + float_ptr);

        // 获取float类型 引用
        float float_ref = new float();
        cpp_get_float_ref(ref float_ref);
        Console.WriteLine("cpp_get_float_ref\t " + float_ref);

        // 获取结构体类型
        cpp_struct_one stu = new cpp_struct_one();
        cpp_get_struct_one_value(ref stu);
        Console.WriteLine("cpp_get_struct_one_value " + stu.value1 + " " + stu.value2);

        // 获取结构体类型 方法2
        cpp_struct_one stu2 = new cpp_struct_one();
        cpp_get_struct_one_value2(ref stu2);
        Console.WriteLine("cpp_get_struct_one_value2 " + stu2.value1 + " " + stu2.value2);

        // 获取结构体类型 方法3
        // 使用非托管内存
        int cpp_struct_one_size = Marshal.SizeOf(typeof(cpp_struct_one));
        IntPtr cpp_struct_one_buffer = Marshal.AllocHGlobal(cpp_struct_one_size);
        cpp_get_struct_one_value3(cpp_struct_one_buffer);
        cpp_struct_one stu3 = (cpp_struct_one)Marshal.PtrToStructure(cpp_struct_one_buffer, typeof(cpp_struct_one));
        Console.WriteLine("cpp_get_struct_one_value3 " + stu3.value1 + " " + stu3.value2);

        // 获取结构体类型2(带数组结构体)
        // 使用非托管内存
        int cpp_struct_two_size = Marshal.SizeOf(typeof(cpp_struct_two));
        IntPtr cpp_struct_two_buffer = Marshal.AllocHGlobal(cpp_struct_two_size);
        cpp_get_struct_two_value(cpp_struct_two_buffer, 10);
        cpp_struct_two stu4 = (cpp_struct_two)Marshal.PtrToStructure(cpp_struct_two_buffer, typeof(cpp_struct_two));
        Console.WriteLine("cpp_get_struct_two_value " + stu4.value1[5] + " " + stu3.value2);

        // 获取字符串
        StringBuilder str = new StringBuilder();
        cpp_get_string_value(ref str);
        Console.WriteLine("cpp_get_string_value " + str.ToString());

        // 获取int型数组 方法1
        int[] arr1 = new int[10];
        cpp_get_int_arr1(ref arr1[0], arr1.Length);
        Console.WriteLine("cpp_get_int_arr1  5 " + arr1[5]);

        // 获取int型数组 方法2
        int[] arr2 = new int[10];
        cpp_get_int_arr2(arr2, arr2.Length);
        Console.WriteLine("cpp_get_int_arr2  5 " + arr2[5]);

        // 获取int型数组 方法3
        int arr3_length = 10;
        int arr3_size = Marshal.SizeOf(typeof(int)) * arr3_length;
        IntPtr arr3_buffer = Marshal.AllocHGlobal(arr3_size);
        cpp_get_int_arr3(arr3_buffer, arr3_length);
        int arr3_test_value = (int)Marshal.PtrToStructure(arr3_buffer + 5 * Marshal.SizeOf(typeof(int)), typeof(int));
        Console.WriteLine("cpp_get_int_arr3 " + arr3_test_value);

        // 传入字符串
        string s = "hello world";
        cpp_set_string_value(s);
    }
	
	// Update is called once per frame
	void Update () {

    }
}
```
unity运行结果
![](http://images2015.cnblogs.com/blog/1014091/201612/1014091-20161202122647693-553210622.png)
**<font color=Blue>项目地址</font>**
https://github.com/caimagic/Unity_Call_Cplusplus-s-Dll.git