// shared_ptr_01.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include "memory"			// for shared_ptr
#include "iostream"

using namespace std;

class Car
{
public:
	Car()
	{
		cout << "Car  ������" << endl;
	}

	virtual ~Car()
	{
		cout << "Car  �Ҹ���" << endl;
	}
};

class Truck : public Car
{
};

// Deleter Ŭ���� ����
template<typename T>
struct ArrayDeleter
{
	void operator () (T* p)
	{
		cout << "ArrayDeleter" << endl;

		delete[] p;
	}
};

void function(std::shared_ptr<Car> _car)
{

}

int _tmain(int argc, _TCHAR* argv[])
{
	// ���� ������ �ʱ� ���� ī��Ʈ�� �翬�� '1'
	std::shared_ptr<Car> Car1(new Car());
	// ���� -> ���� ī��Ʈ '2'
	std::shared_ptr<Car> Car2(Car1);
	// ���� -> ���� ī��Ʈ '3'
	std::shared_ptr<Car> Car3 = Car1;



	// function( std::shared_ptr<Car> _car )���� ���� ����, ���翡 ���� �ӽð�ü ����
	// �̷� ���� ���� ī��Ʈ ���� -> '4'
	function(Car3);
	// �Լ� ȣ�� �Ŀ� �ӽð�ü �Ҹ�ǹǷ� ���� ī��Ʈ ���� -> '3'

	// reset �Լ��� shared_ptr�� �����ϴ� ��ü�� ���ο� �༮���� �ٲ� �� �ִ� �Լ��̴�.
	// ���������� shared_ptr::swap �Լ��� ����
	// http://msdn.microsoft.com/ko-kr/library/bb982757.aspx
	// ���ڸ� ���� ������ ���� ���Ⱑ �Ǵ� ���̴�. ���� ���� ī��Ʈ ���� -> '2'
	Car3.reset();
	// ���ڸ� ���� ������ ���� ���Ⱑ �Ǵ� ���̴�. ���� ���� ī��Ʈ ���� -> '1'
	Car2.reset();



	std::shared_ptr<Car> newCar1(new Car());
	// newCar1�� �����ϴ� Car* �� �� �̻� �����ڰ� �������� �ʾ�, delete�� ȣ��ȴ�.
	// ��� Car1�� �����ϴ� ��ü�� ���� newCar1 shared_ptr�� �����ϹǷ� ���� ī��Ʈ�� '2'
	newCar1 = Car1;
	



	// Deleter
	// shared_ptr ������ �� ��° ���ڷ� deleter class�� �ѱ��...
	// �ƹ��� �������� ��ü �迭�� ����� delete [] ó���� �ȴ�.
	std::shared_ptr<int> spi(new int[1024], ArrayDeleter<int>());
		


	// ������ü ����ȯ
	// Truck Ÿ���� ��ü�� Car Ÿ���� ��ü�� �����ϴ� shared_ptr�� �ʱ�ȭ
	shared_ptr<Car> pCar(new Truck());
	// shared_ptr<Car>�� �����ϰ� �ִ� ��ü�� Truck Ÿ������ static_cast�Ͽ� ����.
	// ���� �Ͽ��⿡ ���� ī��Ʈ�� '2'
	shared_ptr<Truck> pTruck = static_pointer_cast<Truck>(pCar);
	// ��ó�� �������� �ʰ� ������ ����ȯ�� �Ͽ��� �������.
	// ���� ī��Ʈ�� �翬�� ��ȭ�� ����.
	static_pointer_cast<Car>(pCar);



	return 0;
	// �Լ� ��ȯ�� �����ִ� shared_ptr ��� �Ҹ� -> ���� ī��Ʈ '0'
	// ���� shared_ptr�� �����ϰ� �ִ� Car * �� ���� delete�� ȣ���.
}
