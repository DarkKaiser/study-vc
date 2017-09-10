// circular_buffer_01.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <iostream>
#include <boost/circular_buffer.hpp>
#include <boost/assert.hpp>
#include <assert.h>
#include <numeric>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	// 3개 int용량으로 환원버퍼를 만든다
	boost::circular_buffer<int> cb(3);
	assert(cb.capacity() == 3);
	assert(cb.size() == 0);
	assert(cb.empty());

	// 버퍼안에 몇개의 요소를 삽입한다.
	cb.push_back(1);
	cb.push_back(2);
	assert(!cb.full());
	cb.push_back(3);
	assert(cb.full());

	boost::circular_buffer<int>::iterator it = cb.begin();
	assert(*it == 1);

	int a = cb[0];  // a == 1
	int b = cb[1];  // b == 2
	int c = cb[2];  // c == 3

	int sum = std::accumulate(cb.begin(), cb.end(), 0);
	assert(sum == 6);

	// 버퍼는 지금 가득찼다, 뒤이은 요소들을 넣는것은 가장 앞의 요소를 덮어쓸 것이다
	// (역자 : push_back을 해보면 알 수 있는데 값 뿐만이 아니라 begin 이 가르키는
	//        곳 또한 다음 요소를 가르키게된다, 꽉찬 상태에서 덮어쓰면 첫번째 요소는 
	//         새로운 값으로 덮어씌워지고 그것이 마지막 요소가 됨으로 )

	cb.push_back(4);  // 1을 4로 덮어쓴다.
	cb.push_back(5);  // 2를 5로 덮어쓴다

	// 이제 버퍼는 3,4,그리고 5를 담는다

	a = cb[0];  // a == 3
	b = cb[1];  // b == 4
	c = cb[2];  // c == 5


	// 요소들은 다른 front또는 back으로부터 pop 되어진다.
	// (역자 : pop_back, pop_front는 컨테이너의 사이즈도 같이 줄게된다 )
	cb.pop_back();  // 5가 지워진다.
	cb.pop_front(); // 3이 지워진다.

	int d = cb[0];  // d == 4

	//////////////////////////////////////////////////////////////////////////

	typedef boost::circular_buffer<int> circular_buffer;
	circular_buffer cbuffer{ 3 };

	cbuffer.push_back(0);
	cbuffer.push_back(1);
	cbuffer.push_back(2);
	cbuffer.push_back(3);

	// 버퍼가 정규화되어있는지 확인한다.
	// 버퍼가 다 차서 다시 처음으로 옮겨가면 정규화되지 않은거임!
	std::cout << std::boolalpha << cbuffer.is_linearized() << '\n';

	circular_buffer::array_range ar1, ar2;

	ar1 = cbuffer.array_one();	// 원형버퍼에서 출력시작부터 원형버퍼 끝까지
	ar2 = cbuffer.array_two();	// 원형버퍼에서 처음부터 출력끝까지
	std::cout << ar1.second/* 개수 */ << ";" << ar2.second/* 개수 */ << '\n';

	for (int i : cbuffer)
		std::cout << i << '\n';

	// 버퍼를 정규화한다.
	cbuffer.linearize();

	ar1 = cbuffer.array_one();
	ar2 = cbuffer.array_two();
	std::cout << ar1.second << ";" << ar2.second << '\n';

	return 0;
}
