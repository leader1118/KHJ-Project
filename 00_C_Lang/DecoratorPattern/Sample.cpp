//기존에 구현되어 있는 클래스(둥근 모양의 빵) 에 그때 그떄 필요한 기능(초콜릿, 치즈, 생크림)을
//추가(장식,포장)해나가는 설계 패턴을 decorator패턴이라고 한다.
//이것은 기능 확장이 필요할 때 상속의 대안으로 사용한다.

#include <iostream>
using namespace std;

////아래의 코드는 기본코드
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
//			//--측방 공격 수행
//			cout << "측방 공격" << endl;
//		}
//		if(direction_&REAR_DIRECTION)
//		{
//			//-- 후방 공격 수행
//			cout << "후방 공격" << endl;
//		}
//		// -- 전방 공격 수행
//		cout << "전방 공격" << endl;
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
		// --전방 공격 수행
		cout << "전방 공격" << endl;
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
		//--측방 공격 수행
		cout << "측방 공격" << endl;
	}
};

class RearAttackAirplane : public Decorator
{
public:
	RearAttackAirplane(Airplane* pObj) : Decorator(pObj) {}

	void Attack()
	{
		Decorator::Attack();
		//--후방 공격 수행
		cout << "후방 공격" << endl;
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