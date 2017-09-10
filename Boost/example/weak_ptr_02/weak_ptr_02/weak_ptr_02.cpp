// weak_ptr_02.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <memory>    //for shared_ptr/weak_ptr
#include <iostream>
#include <vector>

using namespace std;

class User;
typedef shared_ptr<User> UserPtr;

class Party
{
public:
	Party()
	{
		cout << "Party 생성자" << endl;
	}
	~Party()
	{
		m_MemberList.clear();
		cout << "Party 소멸자" << endl;
	}

public:
	void AddMember(const UserPtr& member)
	{
		m_MemberList.push_back(member);
	}

	void RemoveMember()
	{
		// 제거 코드
	}

private:
	typedef vector<UserPtr> MemberList;
	MemberList m_MemberList;
};
typedef shared_ptr<Party> PartyPtr;
typedef weak_ptr<Party> PartyWeakPtr;

class User
{
public:
	void SetParty(const PartyPtr& party)
	{
		m_Party = party;
	}

	void LeaveParty()
	{
		if (m_Party.expired())
		{
			// shared_ptr로 convert 한 뒤, 파티에서 제거
			// 만약, Party 클래스의 RemoveMember가 이 User에 대해 먼저 수행되었으면,
			// m_Party는 expired 상태
			PartyPtr partyPtr = m_Party.lock();
			if (partyPtr)
			{
				partyPtr->RemoveMember();
			}
		}
	}

private:
	// PartyPtr m_Party;
	PartyWeakPtr m_Party;    // weak_ptr을 사용함으로써, 상호 참조 회피
};

// weak_ptr은 shared_ptr가 보관 유지하는 참조 카운트의 증감에 관여하지 않습니다.
// 또한 weak_ptr의 멤버 expired()에 의해서 인스턴스의 소실을 알 수 있습니다.
int _tmain(int argc, _TCHAR* argv[])
{
	// strong refCount = 1;
	PartyPtr party(new Party);

	for (int i = 0; i < 5; i++)
	{
		// 이 UserPtr user는 이 스코프 안에서 소멸되지만,
		// 아래 party->AddMember로 인해 이 스코프가 종료되어도 user의 refCount = 1
		UserPtr user(new User);

		party->AddMember(user);

		// weak_ptr로 참조하기에 party의 strong refCount = 1
		user->SetParty(party);
	}
	// for 루프 이후 strong refCount = 1, weak refCount = 5

	// 여기에서 party.reset을 수행하면, strong refCount = 0
	// 즉, 파티가 소멸되고 그 과정에서 m_MemberList가 clear -> user들의 strong RefCount = 0 -> user 소멸
	// party와 5개의 user 모두 정상적으로 소멸
	party.reset();

	return 0;
}
