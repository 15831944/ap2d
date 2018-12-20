#ifndef _AFC_XLS_CELL_STYLE_H_
#define _AFC_XLS_CELL_STYLE_H_

#include "export.h"
#include "str.h"
#include "bool.h"
#include "../include/lua.hpp"

namespace afc{
namespace xls{

class AFCAPI Cell_Style
{
public:
	afc::string name;
	afc::string font;
	double size;
	int text_color;
	int back_color;
	BOOL blod;
	BOOL italic;
	int h_align;	//1���棬2��3�У�4�ң�5��䣬6���˶��룬7���о��У�8��ɢ����
	int v_align;	//1�ϣ�2�У�3�£�4���˶��룬5��ɢ����
	double precision;
	int bit;
	BOOL addends;

public:
	Cell_Style();
	void open_lua(lua_State * l, LPCTSTR key);
};

typedef Cell_Style CS;

}//namespace
}//namespace

#endif//FILE
