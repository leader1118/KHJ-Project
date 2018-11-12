#include <iostream>

class ImageWork {};
class Image {};
class ImageLoad {};
class ImageResult {};
// 핸들링 
class FacadeHandler //Facade 역할
{
public:
	void DoWork(ImageWork& image, ImageResult& result)
	{
		m_Image = ImageLoad(image.m_szName);
			//흑백 명암을 변경해라
			result = ImageWork.DoWork(m_Image);
			
	}
private:
	Image m_Image;
	
};

void main()
{
	ImageWork image("aaa.bmp",blank);
	ImageResult result;

	FacadeHandler work;
	work.DoWork(image,result);
}