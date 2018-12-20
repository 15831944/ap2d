// Replace_String.cpp: implementation of the Replace_String class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Replace_String.h"

#include "Text.h"
#include "Entity.h"
#include "Circle.h"
#include "Rectentity.h"


using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


namespace dlhml
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Replace_String::Replace_String()
{

}

Replace_String::~Replace_String()
{

}
//**new*******************************************************************************
void Replace_String::draw_circle(Text *t,std::vector<Entity*>& es)
{
	Rect rect = t->box2d();
	Point center((rect.xmax()+rect.xmin())/2.0f,(rect.ymax()+rect.ymin())/2.0f);


	float r = t->dxf_height()/2.0f + t->dxf_height()/6.0f;

	dlhml::Circle *cir = dlhml::Circle::create_me();

	cir->color_index(t->color_index());
	cir->setdata(center,r);

	es.push_back(cir);



}
void Replace_String::draw_rect(Text *t,std::vector<Entity*>& es)
{
	Rect rect = t->box2d();	
	Rectentity *rc = Rectentity::create_me();
	rc->color_index(t->color_index());
	rc->rect(rect);
	es.push_back(rc);

}
void Replace_String::draw_frame_style(Text *t,std::string style,std::vector<Entity*>& es)
{
	if(strcmp(style.c_str(),"Circle") == 0){
		draw_circle(t,es);
	}else if(strcmp(style.c_str(), "Rect") == 0){
		draw_rect(t,es);
	}else if(strcmp(style.c_str(),"Hide")==0){

	}else{
		
	}

	
}
void Replace_String::replace_text(Text *t,std::string style,std::string sign,std::vector<Entity*>& es)
{
	t->text(sign);
	//�˴�������С���֣����Կ����������2018-11-9
	t->dxf_height(t->dxf_height());//��Сһ������
	t->re_calc_box2d();
	//��������
	draw_frame_style(t,style,es);
}
void Replace_String::add_postfix(Text *t,std::string right,std::string postfix,std::vector<Entity*>& es)
{
	Text *post_t = (Text *)t->clone();
	Rect rect = t->box2d();	
	double t_width = rect.width();
	post_t->position(Point(post_t->position().x + t_width,post_t->position().y));
	std::string str;
	if(strcmp(t->text().c_str(),"")==0)
		if(strcmp(postfix.c_str(),"")==0 ){
			str = right;
		}else{
			str = postfix + " " + right;
		}
	else{
		if(strcmp(postfix.c_str(),"")==0 ){
			str = " " + right;
		}else{
			str = " " + postfix + " " + right;
		}
	}

	str.erase(0,str.find_first_not_of(" "));
	if(strcmp(t->text().c_str(),"")!=0)
		str = " "+str;
	
	post_t->text(str);
	es.push_back(post_t);

}

//SS400
void Replace_String::deal_equal(Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es)
{
	//����SS400
	replace_text(t,style,sign,es);
	//��ȵ��ַ���right="",����ֱ�Ӹ��Ƽ��ɡ�
	add_postfix(t,"",postfix,es);
}
void Replace_String::deal_null_sign(Text *t,std::string right,std::string postfix,std::vector<Entity*>& es)
{

}
//SS400 H100*199*8*10
void Replace_String::deal_head(std::string right,std::string rep_str,Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es)
{
//	if(sign == ""){
//		deal_null_sign(t,right,postfix,es);
//	}else{
		//����SS400
		replace_text(t,style,sign,es);
		//��t������õĺ�׺�ַ�����ע����������t�����ԣ�������Text���Ѻ�׺���ֺ�ԭ��ʣ�������������������
		add_postfix(t,right,postfix,es);
		//��t������õĺ�׺�ַ���
//	}

}
//H100*199*8*10 SS400
void Replace_String::deal_tail(std::string left,std::string right,std::string rep_str,Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es)
{
	//������ֵ
	t->text(left);
	//����t�Աߵģ�λ�ñ仯������һ��Text = ��SS400��
	Text *rep_t = (Text *)t->clone();
	Rect rect = t->box2d();	
	double t_width = rect.width();
	rep_t->position(Point(rep_t->position().x + t_width,rep_t->position().y));
	std::string merge_str = rep_str + " " +right;
	if(strcmp(rep_str.c_str(),"") == 0)
	{
		merge_str = right;
	}else{
		merge_str = rep_str + " " +right;
	}
	rep_t->text(merge_str);
	es.push_back(rep_t);
	//����deal_head�������ָ�ʽ���ַ��������ɡ�

	deal_head(right,rep_str,rep_t,style,sign,postfix,es);

}

void Replace_String::deal_include(std::string rep_str,Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es)
{
	//�������
	std::string val = t->text().c_str();
	std::string left,right;

	int pos = val.find(rep_str);
	if(pos == -1)
		return;
	if(pos == 0){
		left = "";
		right = val.substr(pos+rep_str.length());
	}else{
		right = val.substr(pos+rep_str.length());
		left =val.assign(val.c_str(),pos);
	}




	
	if(left !=""){
		//H100*100*8*19 SS400 IFC
		deal_tail(left,right,rep_str,t,style,sign,postfix,es);

	}else{
		//SS400  H100*100*8*19
		deal_head(right,rep_str,t,style,sign,postfix,es);
	}


}

void Replace_String::rep_text(std::string rep_str,Text *t ,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es)
{
	if(strcmp(t->text().c_str(),rep_str.c_str()) == 0){
		//������ȵ��ַ���
		deal_equal(t,style,sign,postfix,es);
	}else{
		//����������ַ���
		deal_include(rep_str,t,style,sign,postfix,es);
	}
}


}


