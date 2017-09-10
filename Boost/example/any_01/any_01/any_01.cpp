// any_01.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <boost/any.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// any : 어떤 자료형이든 다 넣을 수 있는 그런 컨테이너
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
			// 저장된 데이터에 접근하기 위해서는 any_cast를 사용
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

	// 변수 초기화는 요렇게???
	boost::any all = 1;
	all = boost::any();
	if (all.empty())
	{
		cout << "아무것도 없네요" << endl;
	}

	///////////////////////////////////////////////////////////////////////////////

	try
	{
		boost::any a = 1;
		a = 3.14;
		a = true;
		a = string("Hello, world!");	// boost::any는 한가지 전제조건을 요구하는데, 즉 복사생성자를 지원해야 한다.
										// 그런 이유로 문자 스트링을 저장하기 위해서는 그냥 대입은 안되고, std::string을 명시적으로 사용할 필요가 있다.

		cout << boost::any_cast<float>(a) << endl;
	}
	catch (boost::bad_any_cast &e)
	{
		cout << "bad_any_cast 예외발생" << endl;
	}

	return 0;
}
