#ifndef _OBJECT_LINE_DIM_H_
#define _OBJECT_LINE_DIM_H_

#include "export.h"
#include "complex.h"

#include <vector>

namespace dlhml{


class OBJECT_API Line_Dim : public Complex
{


private:
  class Item
  {
    Point s_;                 //  �ߴ������ߣ����
  //Float h_;                 //  �ߴ������ߣ�������߶�
    Float e_;                 //  �ߴ������ߣ��յ�߶�
  };
private:
  std::vector<Item> item_;  //  �ߴ�����ʼ��
  Float dim_degree_;        //  ��ע�߷���
  Float datum_h_;           //  ������߶Ȼ�׼�����¼���ʱ�Դ�Ϊ��׼�߶ȣ�
  int   org_id_;            //  0��ߴ���id
  bool  org_fixed_;         //  0��ߴ����Ƿ�ʹ�ù̶�ֵ��h_,e_���������¼��㣩
};
//  ע���߶���dim_degree_��ʱ����ת90��(+90)����Ϊ������

}//namespace

#endif//FILE

