#define EXPORTBUILD

#include "test.h"

_DLLExport int add(int x, int y)
{
	return x + y;
}

_DLLExport bool getStructData(CppStruct& d)
{
	d.a = 10;
	d.b = 20;
	d.c = 30;

	return false;
}

 _DLLExport bool getStructDataPtr(CppStruct* d)
 {
  d->a = 10;
  d->b = 20;
  d->c = 30;

  return false;
 }

 _DLLExport void setArrayData(int count, CppStruct* d)
 {
	for (int i = 0; i < count; i++)
	{
		d[i].a = i;
		d[i].b = i;
		d[i].c = i;
	}
 }