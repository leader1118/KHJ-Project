//������ �����Ǿ� �ִ� Ŭ����(�ձ� ����� ��) �� �׶� �׋� �ʿ��� ���(���ݸ�, ġ��, ��ũ��)��
//�߰�(���,����)�س����� ���� ������ decorator�����̶�� �Ѵ�.
//�̰��� ��� Ȯ���� �ʿ��� �� ����� ������� ����Ѵ�.

#include <iostream>
using namespace std;

////�Ʒ��� �ڵ�� �⺻�ڵ�
//class Airplane
//{
//public:
//	void Additem(item* pltem)
//	{
//		direction_ += pltem->GetDirection();
//	}
//	void Attack()
//	{
//		if (direction_ &SIDE_DIRECTION)
//		{
//			//--���� ���� ����
//			cout << "���� ����" << endl;
//		}
//		if(direction_&REAR_DIRECTION)
//		{
//			//-- �Ĺ� ���� ����
//			cout << "�Ĺ� ����" << endl;
//		}
//		// -- ���� ���� ����
//		cout << "���� ����" << endl;
//	}
//private:
//	int direction_;
//};

class Airplane
{
public:
	virtual void Attack() = 0;
};

class FrontAttackAirplane : public Airplane
{
public:
	void Attack()
	{
		// --���� ���� ����
		cout << "���� ����" << endl;
	}
};

class Decorator : public Airplane
{
public:
	Decorator(Airplane* pObj) { pComponent_ = pObj; }
	virtual ~Decorator() = 0;

	virtual void Attack()
	{
		if (pComponent_ != 0)
			pComponent_->Attack();
	}
private:
	Airplane * pComponent_;
};

Decorator::~Decorator() {}

class SideAttackAirplane : public Decorator
{
public:
	SideAttackAirplane(Airplane* pObj) : Decorator(pObj) {}

	void Attack()
	{
		Decorator::Attack();
		//--���� ���� ����
		cout << "���� ����" << endl;
	}
};

class RearAttackAirplane : public Decorator
{
public:
	RearAttackAirplane(Airplane* pObj) : Decorator(pObj) {}

	void Attack()
	{
		Decorator::Attack();
		//--�Ĺ� ���� ����
		cout << "�Ĺ� ����" << endl;
	}
};

void main()
{
	Airplane* pFrontAttackAirplane = new FrontAttackAirplane;
	Airplane* pSideAttackAirplane = new SideAttackAirplane(pFrontAttackAirplane);
	Airplane* pRearAttackAirplane = new RearAttackAirplane(pSideAttackAirplane);

	pRearAttackAirplane->Attack();
	delete pRearAttackAirplane;

	pSideAttackAirplane->Attack();
}