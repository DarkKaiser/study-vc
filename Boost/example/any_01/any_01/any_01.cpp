// any_01.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <boost/any.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// any : � �ڷ����̵� �� ���� �� �ִ� �׷� �����̳�
using boost::any;
using boost::any_cast;

typedef struct foo
{
	int m_nVal;
}foo;

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 10;
	bool b = true;
	foo f;

	vector<any> av;
	vector<any>::iterator it;

	f.m_nVal = 100;

	av.push_back(n);
	av.push_back(b);
	av.push_back(string("string"));
	av.push_back(f);

	for (it = av.begin(); it != av.end(); ++it)
	{
		any& a = *it;

		if (a.type() == typeid(int))
		{
			// ����� �����Ϳ� �����ϱ� ���ؼ��� any_cast�� ���
			int *val = any_cast<int>(&a);
			cout << "int : " << *val << endl;
		}
		else if (a.type() == typeid(bool))
		{
			const bool *val = any_cast<bool>((const any*)&a);
			cout << "bool : " << *val << endl;
		}
		else if (a.type() == typeid(string))
		{
			string val = any_cast<string>(a);
			cout << "str : " << val << endl;
		}
		else if (a.type() == typeid(struct foo))
		{
			struct foo val = any_cast<struct foo>(a);
			cout << "foo : " << val.m_nVal << endl;
		}
	}

	///////////////////////////////////////////////////////////////////////////////

	// ���� �ʱ�ȭ�� �䷸��???
	boost::any all = 1;
	all = boost::any();
	if (all.empty())
	{
		cout << "�ƹ��͵� ���׿�" << endl;
	}

	///////////////////////////////////////////////////////////////////////////////

	try
	{
		boost::any a = 1;
		a = 3.14;
		a = true;
		a = string("Hello, world!");	// boost::any�� �Ѱ��� ���������� �䱸�ϴµ�, �� ��������ڸ� �����ؾ� �Ѵ�.
										// �׷� ������ ���� ��Ʈ���� �����ϱ� ���ؼ��� �׳� ������ �ȵǰ�, std::string�� ��������� ����� �ʿ䰡 �ִ�.

		cout << boost::any_cast<float>(a) << endl;
	}
	catch (boost::bad_any_cast &e)
	{
		cout << "bad_any_cast ���ܹ߻�" << endl;
	}

	return 0;
}
