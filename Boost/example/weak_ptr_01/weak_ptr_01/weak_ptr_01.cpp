// weak_ptr_01.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <memory>    //for shared_ptr/weak_ptr
#include <iostream>

using namespace std;

// weak_ptr�� shared_ptr�� ���� �����ϴ� ���� ī��Ʈ�� ������ �������� �ʽ��ϴ�.
// ���� weak_ptr�� ��� expired()�� ���ؼ� �ν��Ͻ��� �ҽ��� �� �� �ֽ��ϴ�.
int _tmain(int argc, _TCHAR* argv[])
{
	// strong refCount = 1
	shared_ptr<int> sp1(new int(5));

	// shared_ptr sp1���κ��� ���� ����
	// weak_ptr�� �����Ͽ�, strong refCount = 1, weak refCount = 1
	weak_ptr<int> wp1 = sp1;
	{
		// wp1�� �����ϰ� �ִ� sp1�� weak_ptr::lock �޽�带 �̿��� sp2�� ����
		// string refCount = 2, weak refCount = 1
		shared_ptr<int> sp2 = wp1.lock();
		if (sp2)
		{
			// weak_ptr<_Ty>�� _Ty �����Ϳ� ������ �Ϸ���
			// �̷��� shared_ptr�� convert�ϴ� ��� �ۿ� ����
		}
		// sp2�� ���⿡�� �Ҹ�, strong RefCount = 1, weak refCount = 1
	}

	// sp1.reset���� ���� strong refCount = 0, �� sp1 �Ҹ�
	// wp1�� �����ϰ� �ִ� sp1�� �Ҹ�Ǿ����Ƿ�, wp1�� expired
	sp1.reset();

	// expired�� wp1�� �����ϰ� �ִ� shared_ptr�� ����.
	// ����, sp3�� empty
	shared_ptr<int> sp3 = wp1.lock();
	if (sp3)
	{
		// ���� ������ ������� �ʴ´�
		cout << "### 1" << endl;
	}

	cout << "### 2" << endl;

	return 0;
}
