//객체를 구성하는 부분을 먼저 생성하고
//이를 조합하여 객체를 완성한다.
#include <iostream>

class Product {};
class TAttack : public Product{};
class TDenfense : public Product{};
//class Door : public Product{};
class TCharacter 
{
	Product product[2];
};
class TBuilder
{
	TCharacter* m_pMaze;
	virtual void BuildAttack();
	virtual void BuildDefense();
public:
	virtual TCharacter* GetMaze() = 0;
	
};
class TWarrior : public TBuilder
{
	std::vector<TAttack> a;
	std::vector<TDenfense> b;

	TCharacter* GetMaze()
	{
		return NULL;
	}
};
class TMagicain : public TBuilder
{
	Product a;
};
class TDirector //매니저 역활 //중개 역활(외주)
{
public:
	TCharacter * CreateMaze(TBuilder& pBuilder)
	{
		int iWork = 0;
		while (iWork>=2)
		{
			iWork+= pBuilder.BuildAttack();
			iWork+= pBuilder.BuildDefense();
		}
		return pBuilder->GetMaze();
	};

};
void main()
{
	TDirector director;
	TWarrior build;
	director.CreateMaze(build);
	TCharacter* maze = director.GetTCharacter();
}