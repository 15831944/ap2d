
#ifndef _OBJECT_GEO2D_H_
#define _OBJECT_GEO2D_H_


#include <vector>

namespace dlhml{
	class Point;
}

namespace geo2d{
	
////��pts�о���pt����ĵ������
int min_dis(const std::vector<dlhml::Point>& pts, const dlhml::Point& pt);


}//namespace

#endif//FILE
