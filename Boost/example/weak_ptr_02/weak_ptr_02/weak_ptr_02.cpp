// weak_ptr_02.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
		cout << "Party ������" << endl;
	}
	~Party()
	{
		m_MemberList.clear();
		cout << "Party �Ҹ���" << endl;
	}

public:
	void AddMember(const UserPtr& member)
	{
		m_MemberList.push_back(member);
	}

	void RemoveMember()
	{
		// ���� �ڵ�
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
			// shared_ptr�� convert �� ��, ��Ƽ���� ����
			// ����, Party Ŭ������ RemoveMember�� �� User�� ���� ���� ����Ǿ�����,
			// m_Party�� expired ����
			PartyPtr partyPtr = m_Party.lock();
			if (partyPtr)
			{
				partyPtr->RemoveMember();
			}
		}
	}

private:
	// PartyPtr m_Party;
	PartyWeakPtr m_Party;    // weak_ptr�� ��������ν�, ��ȣ ���� ȸ��
};

// weak_ptr�� shared_ptr�� ���� �����ϴ� ���� ī��Ʈ�� ������ �������� �ʽ��ϴ�.
// ���� weak_ptr�� ��� expired()�� ���ؼ� �ν��Ͻ��� �ҽ��� �� �� �ֽ��ϴ�.
int _tmain(int argc, _TCHAR* argv[])
{
	// strong refCount = 1;
	PartyPtr party(new Party);

	for (int i = 0; i < 5; i++)
	{
		// �� UserPtr user�� �� ������ �ȿ��� �Ҹ������,
		// �Ʒ� party->AddMember�� ���� �� �������� ����Ǿ user�� refCount = 1
		UserPtr user(new User);

		party->AddMember(user);

		// weak_ptr�� �����ϱ⿡ party�� strong refCount = 1
		user->SetParty(party);
	}
	// for ���� ���� strong refCount = 1, weak refCount = 5

	// ���⿡�� party.reset�� �����ϸ�, strong refCount = 0
	// ��, ��Ƽ�� �Ҹ�ǰ� �� �������� m_MemberList�� clear -> user���� strong RefCount = 0 -> user �Ҹ�
	// party�� 5���� user ��� ���������� �Ҹ�
	party.reset();

	return 0;
}
