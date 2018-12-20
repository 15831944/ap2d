
#ifndef _BLUE_FRAME_TOOLS_H_
#define _BLUE_FRAME_TOOLS_H_


#include "Paint_Entity_Tools.h"

namespace dlhml{
  class Scene;
  class Group_Ents;
  class Point;
}



namespace dlhml{

  
  class Blue_Frame_Tools : public Paint_Entity_Tools
  {
  public:
    Blue_Frame_Tools(Scene& scene, Group_Ents * blue);
    ~Blue_Frame_Tools();

  public:
    dlhml::Group_Ents * select_blue_frame(const dlhml::Point& pt) const;
    bool is_pt_in_blue_frame(const Point& pt, const Group_Ents* blue_frame) const;

  public:
    ////ͬʱ����ͬһ�������غϱ�ע���0��
    void hide_4pt_start_by_superposion(Ln_Dim_Block* block)const;
    ////���¼����غ�0�����ʾ����
    void reset_show_4pt_start()const;

  private:
    //const dlhml::Scene& scene_;
    const Group_Ents* blue_;
	private:
		MCT_DEF
  };

//namespace
}

#endif