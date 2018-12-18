#include "xCore.h"
class Sample : public xCore
{
public:
	xBoxShape		m_ObjBox;
	xPlaneShape		m_ObjPlane;
	xLineShape		m_ObjLine;
	xSphereShape	m_ObjSphere;
public:
	Sample() {}
	~Sample() {}
};
GAME_RUN("Sample", 800, 600)
