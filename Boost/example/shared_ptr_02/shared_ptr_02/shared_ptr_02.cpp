// shared_ptr_02.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
		cout << "Party  ������" << endl;
	}
	~Party()
	{
		m_MemberList.clear();

		cout << "Party  �Ҹ���" << endl;
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

// ������ ���� ���·� shared_ptr�� ���θ� �����ϰ� �ִ� ���� circular reference��� �Ѵ�.
// ����ó��, �׷� ��ü - �Ҽ� ��ü�� ��ȣ ������ �ǹ������� ���� �� �� �ִ� �����̸�, 
// ������ ����ó�� ���� ���� ������ �ƴ϶�, User�� PartyID�� ��� �ְ�, Party ��ü�� ���� �ʿ��
// PartyManger(�÷���)�� �����ؼ� ��ȿ�� Party ��ü �����͸� ������ ����� ����Ѵ�.
// �׷��ٰ�, PartyManager�� ������ ID�� �˻��ϴ� ����� ���̰���, Party �����͸� ���� ��� ������, ��� �ִ� �����Ͱ� dangling pointer�� �� �� �ִ� ������ �ִ�.
// �̷� ��, User ��ü�� Party ��ü�� shared_ptr�� �ƴ� weak_ptr�� ����Ͽ� ��� �ִٸ�, �˻� ��� ȸ�ǿ� dangling pointer�� ���迡�� ��� ��� �� �ִ�.
// std::weak_ptr�� shared_ptr�κ��� ������ �� �ְ�, shared_ptr�� ����Ű�� �ִ� ��ü�� �Ȱ��� ����������, ������ �� �� reference counting�� ���� �ʾ� �� ������ ������ ���� �ٶ����� ����� �� �� �ִ� �� �� �ִ�.
int _tmain(int argc, _TCHAR* argv[])
{
	PartyPtr party(new Party);

	for (int i = 0; i < 5; i++)
	{
		// �� user�� �� ������ �ȿ��� �Ҹ������,
		// �Ʒ� party->AddMember�� ���� �� �������� ����Ǿ user�� refCount = 1
		UserPtr user(new User);

		// �Ʒ� �������� ��ȯ ������ �߻��Ѵ�.
		party->AddMember(user);
		user->SetParty(party);
	}

	// ���⿡�� party.reset�� ������ ������,
	// 5���� ��Ƽ���� party ��ü�� ���� �־� ���� refCount = 5 �� ����
	// ����, party�� �Ҹ���� ���ϰ�, party�� vector�� ����� user ��ü�� ���� �Ҹ���� ���Ѵ�.
	party.reset();

	return 0;
}
