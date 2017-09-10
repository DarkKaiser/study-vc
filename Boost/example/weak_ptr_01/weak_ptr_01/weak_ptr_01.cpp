// weak_ptr_01.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <memory>    //for shared_ptr/weak_ptr
#include <iostream>

using namespace std;

// weak_ptr은 shared_ptr가 보관 유지하는 참조 카운트의 증감에 관여하지 않습니다.
// 또한 weak_ptr의 멤버 expired()에 의해서 인스턴스의 소실을 알 수 있습니다.
int _tmain(int argc, _TCHAR* argv[])
{
	// strong refCount = 1
	shared_ptr<int> sp1(new int(5));

	// shared_ptr sp1으로부터 복사 생성
	// weak_ptr이 참조하여, strong refCount = 1, weak refCount = 1
	weak_ptr<int> wp1 = sp1;
	{
		// wp1이 참조하고 있던 sp1을 weak_ptr::lock 메써드를 이용해 sp2가 참조
		// string refCount = 2, weak refCount = 1
		shared_ptr<int> sp2 = wp1.lock();
		if (sp2)
		{
			// weak_ptr<_Ty>의 _Ty 포인터에 엑세스 하려면
			// 이렇게 shared_ptr로 convert하는 방법 밖에 없다
		}
		// sp2가 여기에서 소멸, strong RefCount = 1, weak refCount = 1
	}

	// sp1.reset으로 인해 strong refCount = 0, 즉 sp1 소멸
	// wp1이 참조하고 있던 sp1이 소멸되었으므로, wp1은 expired
	sp1.reset();

	// expired된 wp1은 참조하고 있는 shared_ptr이 없다.
	// 따라서, sp3도 empty
	shared_ptr<int> sp3 = wp1.lock();
	if (sp3)
	{
		// 여기 문장은 실행되지 않는다
		cout << "### 1" << endl;
	}

	cout << "### 2" << endl;

	return 0;
}
