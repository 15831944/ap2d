#ifndef _OBJECT_DIM_H_
#define _OBJECT_DIM_H_

#include "export.h"
#include "style.h"

namespace dlhml{

class OBJECT_API Dim
{

protected:
  Style style_;
  std::string fixed_;   //  �������(�������ݣ���ǿ��ʹ�ø���������)
};


}//namespace

#endif//FILE
