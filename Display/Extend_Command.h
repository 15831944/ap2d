
#ifndef _TIAN_DISPLAY_CAD_EXTEND_COMMAND_H_
#define _TIAN_DISPLAY_CAD_EXTEND_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{


class Extend_Command : public Cad_Command
{
public:
  Extend_Command()MCT_INIT1("Extend_Command"){}
  virtual ~Extend_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
	virtual bool is_reset_begin(){return true;}//	������Ҫ����ָ��begin_
	
private:
	MCT_DEF
};

}

#endif//FILE
