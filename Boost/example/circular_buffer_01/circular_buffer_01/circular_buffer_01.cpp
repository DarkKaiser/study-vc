// circular_buffer_01.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	// 3�� int�뷮���� ȯ�����۸� �����
	boost::circular_buffer<int> cb(3);
	assert(cb.capacity() == 3);
	assert(cb.size() == 0);
	assert(cb.empty());

	// ���۾ȿ� ��� ��Ҹ� �����Ѵ�.
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

	// ���۴� ���� ����á��, ������ ��ҵ��� �ִ°��� ���� ���� ��Ҹ� ��� ���̴�
	// (���� : push_back�� �غ��� �� �� �ִµ� �� �Ӹ��� �ƴ϶� begin �� ����Ű��
	//        �� ���� ���� ��Ҹ� ����Ű�Եȴ�, ���� ���¿��� ����� ù��° ��Ҵ� 
	//         ���ο� ������ ��������� �װ��� ������ ��Ұ� ������ )

	cb.push_back(4);  // 1�� 4�� �����.
	cb.push_back(5);  // 2�� 5�� �����

	// ���� ���۴� 3,4,�׸��� 5�� ��´�

	a = cb[0];  // a == 3
	b = cb[1];  // b == 4
	c = cb[2];  // c == 5


	// ��ҵ��� �ٸ� front�Ǵ� back���κ��� pop �Ǿ�����.
	// (���� : pop_back, pop_front�� �����̳��� ����� ���� �ٰԵȴ� )
	cb.pop_back();  // 5�� ��������.
	cb.pop_front(); // 3�� ��������.

	int d = cb[0];  // d == 4

	//////////////////////////////////////////////////////////////////////////

	typedef boost::circular_buffer<int> circular_buffer;
	circular_buffer cbuffer{ 3 };

	cbuffer.push_back(0);
	cbuffer.push_back(1);
	cbuffer.push_back(2);
	cbuffer.push_back(3);

	// ���۰� ����ȭ�Ǿ��ִ��� Ȯ���Ѵ�.
	// ���۰� �� ���� �ٽ� ó������ �Űܰ��� ����ȭ���� ��������!
	std::cout << std::boolalpha << cbuffer.is_linearized() << '\n';

	circular_buffer::array_range ar1, ar2;

	ar1 = cbuffer.array_one();	// �������ۿ��� ��½��ۺ��� �������� ������
	ar2 = cbuffer.array_two();	// �������ۿ��� ó������ ��³�����
	std::cout << ar1.second/* ���� */ << ";" << ar2.second/* ���� */ << '\n';

	for (int i : cbuffer)
		std::cout << i << '\n';

	// ���۸� ����ȭ�Ѵ�.
	cbuffer.linearize();

	ar1 = cbuffer.array_one();
	ar2 = cbuffer.array_two();
	std::cout << ar1.second << ";" << ar2.second << '\n';

	return 0;
}
