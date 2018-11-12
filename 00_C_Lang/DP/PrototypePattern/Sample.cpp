#include <iostream>
#include <list>
#include <map>
using namespace std;
template<class T> class Tsingleton
{
public:
	static T& GetInstance()// 참조 중요 ..지역변수에 참조로 넘긴다
	{
		static T inst;
		return inst;
	}
};
class TPosition
{
public:
	TPosition() {}
	TPosition(int ix, int iy)
	{
		m_ix = ix;
		m_iy = iy;
	}
	int m_ix;
	int m_iy;
};

class TGraphic
{
public:
	virtual TGraphic* Clone() = 0;
	virtual void Draw(TPosition pos) = 0;
};
class TTriangle : public TGraphic
{
public:
	TGraphic * Clone()
	{
		return new TTriangle(*this);
	};
	void Draw(TPosition pos)
	{
		std::cout << pos.m_ix << pos.m_iy;
	};

};
class TRectangle : public TGraphic
{
public:
	TGraphic * Clone()
	{
		return new TRectangle(*this);
	};
	void Draw(TPosition pos)
	{
		std::cout << pos.m_ix << pos.m_iy;
	};

};
class TGraphicComposite : public TGraphic
{
public:
	void Draw(TPosition pos)
	{
		std::cout << pos.m_ix << pos.m_iy;
	};
	// Composite pattern
	std::list<TGraphic*>m_components;
	TGraphic * Clone()
	{
		TGraphicComposite* pGC =
			new TGraphicComposite(*this);

		//데이터는 같지만 메모리는 다르다
		std::list<TGraphic*>::iterator iterSrc;
		for (iterSrc = m_components.begin();
			iterSrc != m_components.end();
			iterSrc++)
		{
			TGraphic* pNewGraphic = (*iterSrc)->Clone();
			pGC->m_components.push_back(pNewGraphic);
		}

		return pGC;
	};

};

class TMouse
{
public:
	TPosition m_pos;
	bool      m_bLeftButton[3];
public:
	bool IsLeftButtonPushed()
	{
		return m_bLeftButton[0];
	}
	TPosition GetPosition()
	{
		return m_pos;
	}
};

TMouse g_Mouse;

class TDocument
{
public:
	list<TGraphic*>m_docList;

public:
	void Add(TGraphic* pobj)
	{
		m_docList.push_back(pobj);
	}
};
class TGraphicEditor
{
public:

	TDocument m_doc;
public:
	void AddNewGraphic(TGraphic* pSelected)
	{
		TGraphic* pobj = pSelected->Clone();
		while (g_Mouse.IsLeftButtonPushed())
		{

			pobj->Draw(g_Mouse.GetPosition());
		}
		m_doc.Add(pobj);
	}
private:
};

class TPalette : public Tsingleton<TPalette>
{
private:
	friend class Tsingleton<TPalette>;
	std::map<int, TGraphic*> m_items;
public:
	void Draw() {}
	/*static TPalette* g_pPlette;
	static TPalette* GetInstance()
	{
		if (g_pPlette == NULL)
		{
			g_pPlette = new TPalette;
		}
		return g_pPlette;
	}*/
	//원시 모델 추가등록
	void RegisterNewGraphic(TGraphic* pGraphic)
	{
		m_items[m_items.size() + 1] = pGraphic;
	}

	TGraphic* GetSelectedobj()
	{
		return m_items[GetItemOrder()];
	}
	int GetItemOrder()
	{
		int iItem = -1;
		//g_Mouse.GetPosition();
		return iItem;
	}

protected:
	TPalette()
	{
		//원시 모델
		TGraphic* pGraphicA = new TTriangle;
		m_items[0] = pGraphicA;

		TGraphic* pGraphicB = new TRectangle;
		m_items[1] = pGraphicB;
	}
	
};
#define I_Palette TPalette::GetInstance()

void main()
{
	TPalette palette= I_Palette;
	TPalette paletteA=TPalette::GetInstance();
	I_Palette.Draw();
	TGraphicEditor editer;
	editer.AddNewGraphic(I_Palette.GetSelectedobj());

	TGraphicComposite etc;
	list<TGraphic*>::iterator iter;
	for (iter = editer.m_doc.m_docList.begin();
		iter != editer.m_doc.m_docList.end();
		iter++)
	{
		TGraphic* pData = (*iter);
		etc.m_components.push_back(pData);
	}
	I_Palette.RegisterNewGraphic(&etc);


	//components 패턴
	/*  TTriangle tri;
	  TRectangle rec;
	  TGraphicComposite etc;
	  etc.m_components.push_back(&tri);
	  etc.m_components.push_back(&rec);
	  palette.RegisterNewGraphic(&etc);


	  TRectangle rec1;
	  TRectangle rec2;
	  TGraphicComposite etc;
	  etc.m_components.push_back(&rec1);
	  etc.m_components.push_back(&rec2);
	  palette.RegisterNewGraphic(&etc);


	  TGraphicComposite etc3;
	  TGraphicComposite etc4;
	  etc.m_components.push_back(&etc3);
	  etc.m_components.push_back(&etc4);
	  palette.RegisterNewGraphic(&etc);*/

	  //siggle Pattern 유일성mgr 종류들
}