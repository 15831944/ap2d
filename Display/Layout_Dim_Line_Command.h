
#ifndef _TIAN_DISPLAY_CAD_LAYOUT_DIM_LINE_COMMAND_H_
#define _TIAN_DISPLAY_CAD_LAYOUT_DIM_LINE_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Layout_Dim_Line_Command : public Cad_Command
{
public:
  Layout_Dim_Line_Command()MCT_INIT1("Layout_Dim_Line_Command"){}
  virtual ~Layout_Dim_Line_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
	
private:
	MCT_DEF
};

}

#endif//FILE
