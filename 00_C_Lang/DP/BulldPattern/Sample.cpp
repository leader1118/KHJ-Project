//��ü�� �����ϴ� �κ��� ���� �����ϰ�
//�̸� �����Ͽ� ��ü�� �ϼ��Ѵ�.
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
class TDirector //�Ŵ��� ��Ȱ //�߰� ��Ȱ(����)
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