#include "Maze.h"
// ���� Ŭ���������� �ν��Ͻ��� ����� ����� �����ϰ�, ��ü���� Ŭ���� �̸��� �ڷ� �̷��.
// � Ŭ������ �ν��Ͻ��� ������ ���� ���� ������ ���� Ŭ������ �����Ѵ�.
//1) � Ŭ������ �ڽ��� �����ؾ� �ϴ� ��ü�� Ŭ������ ������ �� ���� ��
//2)������ ��ü�� ����ϴ� å���� �ڽ��� ����Ŭ������ ���������� �� ��
//3)��ü ������ å���� �� ���� ���� ����Ŭ���� ��� �ϳ����� �����ϰ�
// � ����Ŭ������ ������������ ���� ������ ����ȭ ��Ű�� ���� ��

class Spell
{
public:
	Spell() {};
};
class EnchantedRoom :public Room
{
public:
	EnchantedRoom(int n, Spell*) :Room(n)
	{

	}
};
class BombedWall : public Wall
{
public:
	BombedWall(){}
};
class BombedWithRoom : public Room
{
public:
	BombedWithRoom(int n): Room(n){}
};
class DoorNeedingSpell :public Door
{
public:
	DoorNeedingSpell(Room* r1, Room* r2) :Door(r1, r2)
	{

	}
};
class MazeGame
{
public:
	Maze * CreateMaze()
	{
		Maze* aMaze = MakeMaze();
		Room* r1 = MakeRoom(1);
		Room* r2 = MakeRoom(2);
		Door* theDoor = MakeDoor(r1, r2);
		aMaze->AddRoom(r1);
		aMaze->AddRoom(r2);

		r1->SetSide(North, MakeWall());
		r1->SetSide(East, theDoor);
		r1->SetSide(South, MakeWall());
		r1->SetSide(West, MakeWall());

		r2->SetSide(North, MakeWall());
		r2->SetSide(East, MakeWall());
		r2->SetSide(South, MakeWall());
		r2->SetSide(West, theDoor);
		return aMaze;
	}
	// Factory Method
	virtual Maze* MakeMaze() { return new Maze; }
	virtual Room* MakeRoom(int n) { return new Room(n); }
	virtual Wall* MakeWall() { return new Wall; }
	virtual Door* MakeDoor(Room* r1, Room* r2) { return new Door(r1, r2); }
};

class BombedMazeGame :public MazeGame
{
public:
	virtual Wall* MakeWall()
	{
		return new BombedWall;
	}
	virtual Room* MakeRoom(int n)
	{
		return new BombedWithRoom(n);
	}
};
class EnchantedMazeGame : public MazeGame
{
public:
	virtual Door* MakeDoor(Room* r1, Room* r2)
	{
		return new DoorNeedingSpell(r1, r2);
	}
	virtual Room* MakeRoom(int n)
	{
		return new EnchantedRoom(n, CastSpell());
	}
protected:
	Spell * CastSpell() { return 0; };
};
void main()
{
	MazeGame mg;
	Maze* pMaze1 = mg.CreateMaze();

	BombedMazeGame bombedGame;
	Maze* pMaze2 = bombedGame.CreateMaze();
	EnchantedMazeGame EnchantedGame;
	Maze* pMaze3 = EnchantedGame.CreateMaze();
}