// shared_ptr_01.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
		cout << "Car  생성자" << endl;
	}

	virtual ~Car()
	{
		cout << "Car  소멸자" << endl;
	}
};

class Truck : public Car
{
};

// Deleter 클래스 정의
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
	// 최초 생성시 초기 참조 카운트는 당연히 '1'
	std::shared_ptr<Car> Car1(new Car());
	// 복사 -> 참조 카운트 '2'
	std::shared_ptr<Car> Car2(Car1);
	// 대입 -> 참조 카운트 '3'
	std::shared_ptr<Car> Car3 = Car1;



	// function( std::shared_ptr<Car> _car )값에 의한 전달, 복사에 의한 임시객체 생성
	// 이로 인한 참조 카운트 증가 -> '4'
	function(Car3);
	// 함수 호출 후엔 임시객체 소멸되므로 참조 카운트 감소 -> '3'

	// reset 함수는 shared_ptr이 참조하는 객체를 새로운 녀석으로 바꿀 수 있는 함수이다.
	// 내부적으로 shared_ptr::swap 함수가 사용됨
	// http://msdn.microsoft.com/ko-kr/library/bb982757.aspx
	// 인자를 주지 않으면 참조 포기가 되는 것이다. 따라서 참조 카운트 감소 -> '2'
	Car3.reset();
	// 인자를 주지 않으면 참조 포기가 되는 것이다. 따라서 참조 카운트 감소 -> '1'
	Car2.reset();



	std::shared_ptr<Car> newCar1(new Car());
	// newCar1이 참조하던 Car* 는 더 이상 참조자가 존재하지 않아, delete가 호출된다.
	// 대신 Car1이 참조하던 객체를 이제 newCar1 shared_ptr도 참조하므로 참조 카운트는 '2'
	newCar1 = Car1;
	



	// Deleter
	// shared_ptr 생성시 두 번째 인자로 deleter class를 넘기면...
	// 아무런 문제없이 객체 배열도 제대로 delete [] 처리가 된다.
	std::shared_ptr<int> spi(new int[1024], ArrayDeleter<int>());
		


	// 참조객체 형변환
	// Truck 타입의 객체를 Car 타입의 객체를 참조하는 shared_ptr에 초기화
	shared_ptr<Car> pCar(new Truck());
	// shared_ptr<Car>가 참조하고 있던 객체를 Truck 타입으로 static_cast하여 대입.
	// 대입 하였기에 참조 카운트는 '2'
	shared_ptr<Truck> pTruck = static_pointer_cast<Truck>(pCar);
	// 위처럼 대입하지 않고 스스로 형변환만 하여도 상관없음.
	// 참조 카운트는 당연히 변화가 없다.
	static_pointer_cast<Car>(pCar);



	return 0;
	// 함수 반환시 남아있던 shared_ptr 모두 소멸 -> 참조 카운트 '0'
	// 이제 shared_ptr이 참조하고 있던 Car * 에 대해 delete가 호출됨.
}
