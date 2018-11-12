//컴파일러를 개발해라!
//제품별(sun , hp)
//TAttack,TDenfense,GENERATOR,OPTIMIZER
//클래스 구조, sun? hp= 동일한 작업이 진행
#include <iostream>
#include <memory>

int g_iType = 0;
#define WARRIOR 0
#define MAGICIAN 1


class TAttack {};
class TDenfense {};

class TSword :public TAttack {};
class TShield :public TDenfense {};

class TMagicainTAttack :public TAttack {};
class TMagicainTDenfense :public TDenfense {};

class TCharacter
{
public:
	virtual TAttack* CreateTAttack() = 0;
	virtual TDenfense* CreateTDenfense() = 0;
	TAttack* attack;
	TDenfense denfense;
};
class TWarrior : public TCharacter
{
public:
	TAttack * CreateTAttack() { return new TSword; };
	TDenfense* CreateTDenfense() { return new TShield; };

};
class TMagicain :public TCharacter
{
public:
	TAttack * CreateTAttack() { return new TMagicainTAttack; };
	TDenfense* CreateTDenfense() { return new TMagicainTDenfense; };
};


void mian()
{

	g_iType = MAGICIAN;
	//TCharacter* g_pFactory;
	std::shared_ptr<TCharacter> g_pFactory;
	if (g_iType == WARRIOR)
	{
		g_pFactory = std::make_shared<TWarrior>();

	}
	else
	{
		g_pFactory = std::make_shared<TMagicain>();
	}

	std::shared_ptr<TAttack>
		(g_pFactory->CreateTAttack());

	std::shared_ptr<TDenfense> a(new TDenfense);
	std::shared_ptr<TDenfense> b(g_pFactory->CreateTDenfense);
	//pScanner = std ::move(a);
	a.swap(b);

	auto temp = g_pFactory->CreateTDenfense();
	std::shared_ptr<TDenfense> pDenfense;

	pDenfense .reset(g_pFactory->CreateTDenfense());
	//print(pDenfense.get());

	//auto 

}