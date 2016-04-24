#include <stdio.h>
#include <vector>
#include <list>
#include <set>
#include <typeinfo>


#include "ex/iterator"
#include "ex/cprint"
#include "ex/debug"
#include "ex/version"


using namespace std;
using namespace ex;


class TestForEach final
{
public:
	TestForEach()
	{
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(5);
	}

	IteratorAdapter<int> begin()
	{
		return IteratorAdapter<int>(vec.begin());
	}

	IteratorAdapter<int> end()
	{
		return IteratorAdapter<int>(vec.end());
	}

private:
	vector<int> vec;
};

void sep()
{
	static int i = 0 ;
	print("---------------------%02d--------------------\n", ++i);
	DEBUG_MSG("---------------------%02d--------------------\n", i);
}


// TODO: move it to an unit test

int main()
{
	sep();

	list<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	// .concr.ctor.move
	// .ctor.move.templ
	IteratorAdapter<int> i1(v.begin());
	print("%d\n", *i1);                           sep();

	// .concr.ctor.copy
	// .ctor.copy
	IteratorAdapter<int> i2(i1);
	++i1;
	print("%d %d\n", *i1, *i2);                   sep();

	// .ctor.move (i2 become invalid)
	IteratorAdapter<int> i3(std::move(i2));
	print("%d\n", *i3);                           sep();

	// .concr.ctor.copy
	// .ctor.copy
	// operator++ and .ctor.move
	IteratorAdapter<int> i4(i1++);
	print("%d %d\n", *i1, *i4);                   sep();

	// .concr.ctor.copy
	// .ctor.copy.templ
	auto j = v.begin();
	IteratorAdapter<int> i5(j);
	print("%d\n", *i5);                           sep();

	// concr.ctor.copy
	// .ctor.copy.templ
	auto i = v.begin();
	IteratorAdapter<int> i6 = i;
	print("%d\n", *i6);                           sep();

	// .concr.ctor.move
	// .ctor.move.templ
	IteratorAdapter<int> i7 = v.begin();
	print("%d\n", *i7);                           sep();

	// .concr.ctor.copy
	// .ctor.copy
	IteratorAdapter<int> i8 = i5;
	print("%d\n", *i8);                           sep();

	// .ctor.move -> optimization -> .ctor.move.templ
	IteratorAdapter<int> i9 = IteratorAdapter<int>(v.begin());
	print("%d\n", *i9);                           sep();

	// .assign.copy
	// .concr.ctor.copy
	IteratorAdapter<int> i10;
	i10 = i9;
	++i9;
	print("%d %d\n\n", *i9, *i10);               sep();

	// .assign.move
	IteratorAdapter<int> i11;
	i11 = std::move(i10);
	printf("%d\n\n", *i11);                       sep();

	// .assign.move.templ
	// .concr.ctor.move
	IteratorAdapter<int> i12;
	i12 = v.begin();
	print("%d\n\n", *i12);                       sep();

	// .assign.move.templ
	// .concr.ctor.move
	IteratorAdapter<int> i13;
	i13 = std::move(v.begin());
	print("%d\n\n", *i13);                       sep();

	// .assign.copy.templ:
	// .concr.ctor.copy
	auto k = v.begin();
	IteratorAdapter<int> i14;
	i14 = k;
	print("%d\n\n", *i14);                       sep();

	// test - range based for
	TestForEach i15;

	for (auto& val : i15)
		print("%d\n", val);

	sep();

	// unref test
	vector<int*> vec;

	int int1 = 1;
	int int2 = 2;
	int int3 = 3;
	int int4 = 4;

	vec.push_back(&int1);
	vec.push_back(&int2);
	vec.push_back(&int3);
	vec.push_back(&int4);

	IteratorAdapter<int*, int, unref<int*>> i16(vec.begin());
	++i16;
	print("%d\n", *i16);  sep();

	// special case with set (const T&)
	set<int> s;
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(4);

	IteratorAdapter<int, const int> i17(s.begin());

	while (i17 != s.end())
	{
		print("%d\n", *i17);
		++i17;
	}

	sep();

	// unref with set
	set<int*> s2;
	s2.insert(&int1);
	s2.insert(&int2);
	s2.insert(&int3);
	s2.insert(&int4);

	// ConstIterator
	IteratorAdapter<int*, const int, const_unref<int*>> i18(s2.begin());

	while (i18 != s2.end())
	{
		print("%d\n", *i18);
		++i18;
	}

	sep();

	return 0;
}
