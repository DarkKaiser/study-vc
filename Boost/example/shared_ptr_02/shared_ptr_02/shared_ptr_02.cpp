// shared_ptr_02.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include "memory"			// for shared_ptr
#include "iostream"
#include <vector>

using namespace std;

class User;
typedef shared_ptr<User> UserPtr;

class Party
{
public:
	Party()
	{
		cout << "Party  생성자" << endl;
	}
	~Party()
	{
		m_MemberList.clear();

		cout << "Party  소멸자" << endl;
	}

public:
	void AddMember(const UserPtr& member)
	{
		m_MemberList.push_back(member);
	}

private:
	typedef vector<UserPtr> MemberList;
	MemberList m_MemberList;
};
typedef shared_ptr<Party> PartyPtr;

class User
{
public:
	void SetParty(const PartyPtr& party)
	{
		m_Party = party;
	}

private:
	PartyPtr m_Party;
};

// 다음과 같은 형태로 shared_ptr이 서로를 참조하고 있는 것은 circular reference라고 한다.
// 예제처럼, 그룹 객체 - 소속 객체간 상호 참조는 실무에서도 흔히 볼 수 있는 패턴이며, 
// 보통은 예제처럼 직접 참조 형식이 아니라, User는 PartyID를 들고 있고, Party 객체에 접근 필요시
// PartyManger(컬렉션)에 질의해서 유효한 Party 객체 포인터를 얻어오는 방식을 사용한다.
// 그렇다고, PartyManager에 일일히 ID로 검색하는 비용을 줄이고자, Party 포인터를 직접 들고 있으면, 들고 있던 포인터가 dangling pointer가 될 수 있는 위험이 있다.
// 이럴 때, User 객체가 Party 객체를 shared_ptr가 아닌 weak_ptr을 사용하여 들고 있다면, 검색 비용 회피와 dangling pointer의 위험에서 모두 벗어날 수 있다.
// std::weak_ptr은 shared_ptr로부터 생성될 수 있고, shared_ptr이 가리키고 있는 객체를 똑같이 참조하지만, 참조만 할 뿐 reference counting은 하지 않아 위 예제의 목적에 가장 바람직한 대안이 될 수 있다 할 수 있다.
int _tmain(int argc, _TCHAR* argv[])
{
	PartyPtr party(new Party);

	for (int i = 0; i < 5; i++)
	{
		// 이 user는 이 스코프 안에서 소멸되지만,
		// 아래 party->AddMember로 인해 이 스코프가 종료되어도 user의 refCount = 1
		UserPtr user(new User);

		// 아래 과정에서 순환 참조가 발생한다.
		party->AddMember(user);
		user->SetParty(party);
	}

	// 여기에서 party.reset을 수행해 보지만,
	// 5명의 파티원이 party 객체를 물고 있어 아직 refCount = 5 의 상태
	// 따라서, party가 소멸되지 못하고, party의 vector에 저장된 user 객체들 역시 소멸되지 못한다.
	party.reset();

	return 0;
}
