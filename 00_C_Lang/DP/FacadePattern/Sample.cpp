#include <iostream>

class ImageWork {};
class Image {};
class ImageLoad {};
class ImageResult {};
// �ڵ鸵 
class FacadeHandler //Facade ����
{
public:
	void DoWork(ImageWork& image, ImageResult& result)
	{
		m_Image = ImageLoad(image.m_szName);
			//��� ����� �����ض�
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