// Dimension_Style.h: interface for the Dimension_Style class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_DIMENSION_STYLE_H__C00010D8_0988_4241_8B1D_07C2F38A493E__INCLUDED_
#define AFX_DIMENSION_STYLE_H__C00010D8_0988_4241_8B1D_07C2F38A493E__INCLUDED_

#include "export.h"
#include <vector>
#include "Text.h"

namespace dlhml{
  
typedef int ROUNDING_TYPE;
const int ROUNDING_BE_DIVIDED_BY_1=1; 
const int ROUNDING_BE_DIVIDED_BY_2=2;
const int ROUNDING_BE_DIVIDED_BY_3=3;
typedef int ARROW_NUM;        ////��ͷ����
const int ARROW_NULL  = 0;    ////û�м�ͷ
const int ARROW_START = 1;    ////��ʼ�˼�ͷ
const int ARROW_END   = 2;    ////��ֹ�˼�ͷ
const int ARROW_DOUBLE= 3;    ////���˼�ͷ

class Point;
class Normal;
class Entity;
class Text;
class Line;
class Circle;
class RArc;
class Normal;
class OBJECT_API Dimension_Style  
{
public:
	enum Arrow {NO=10,LEAD,COMMON,CIRCLE};    ////One:lead, Two:comman, Pt:circle
	enum Txt_Frame {Only=1,Baseline,ArcEdge,ArrowEdge,RectEdge,CircleEdge};
	enum TextPos {UP=20,CENTER,DOWN};

public:
	Dimension_Style();
	Dimension_Style(const Dimension_Style& rhs);
	Dimension_Style& operator=(const Dimension_Style& rhs);
	~Dimension_Style();
	bool operator == (const Dimension_Style& rhs);

public:
	static Dimension_Style* create_me();
	bool close();
	void save_lua(std::ofstream &out,char *name,int tab_num);
  void open_lua(lua_State *l,char *name) ;

// 	void lua_load(iLua_File &fin);
// 	void lua_save(oLua_File &fout)const;
//property
public:
	void	name(std::string n)		          {name_=n;}
	void  text_style_name(std::string n)  {text_style_=n;}
	void  text_pos(TextPos pos);					
	void  arrow_style(Arrow style)	  {arrowstyle_ = style;}
	void  txt_frame(Txt_Frame style)	{tf_=style;}
  void  arrow_num(ARROW_NUM n)      {arrow_num_=n;}
	std::string	  name            ()const {return name_;}
	std::string   text_style_name ()const {return text_style_;}
	TextPos   text_pos        ()const {return tp_;}
	Txt_Frame txt_frame      ()const {return tf_;}
	Arrow     arrow_style     ()const {return arrowstyle_;}
  ARROW_NUM arrow_num       ()const {return arrow_num_;}
public:
  void text_precision(double d);
  double text_precision()const;
  void decimal_place(int n);
  int decimal_place()const;
  void decimal_addends(bool b);
  bool decimal_addends()const;
  //   void  rounding_type(ROUNDING_TYPE t){rounding_type_ =t;}
  //   void  text_precision(int  n)         {text_precision_ =n;}
  //   void  text_fill  (bool b)         {text_fill_   =b;}
  //   ROUNDING_TYPE  rounding_type()      {return rounding_type_;}
  //   int   text_precision()              {return text_precision_;}
  //   bool  text_fill  ()                 {return text_fill_  ;}
  //   int   text_precision() const		    {return text_precision_;}
public:
	void  extend_start_off(Float f)		  {extendstartoff_=f;}
	void  extend_end_off(Float f)				{extendendoff_ = f;}
	void  start_dim_length(Float f)			{start_dim_length_ = f;}
	void  end_dim_length(Float f)				{end_dim_length_ = f;}
	void  arrow_size(Float f)						{arrowsize_ = f;}
	void  text_height(Float height)			{text_hight_=height;}

	Float extend_start_off() const			{return extendstartoff_;}
	Float extend_end_off() const				{return extendendoff_;}
	Float start_dim_length() const			{return start_dim_length_;}
	Float end_dim_length() const				{return end_dim_length_;}
	Float arrow_size() const						{return arrowsize_;}
	Float text_height() const						{return text_hight_;}
  Float text_gdi_height()const        {return text_height() * gdi_scale();}

public:
	void  text_frame_color(int color)   {text_frame_color_ = color;}
	void  text_color(int color)         {text_color_ = color;}
	void  line_color(int color);
	int   text_frame_color()const       {return text_frame_color_;}
	int   text_color()const             {return text_color_;}
	int   line_color()const             {return line_color_;}


//calculate
public:
  void get_arrow(const Line& ln, ARROW_NUM an, std::vector<Entity*>& es)const;
  void get_arrow(const RArc& ar, ARROW_NUM an, std::vector<Entity*>& es)const;
  void get_arrow(const Line& ln, std::vector<Entity*>& es)const;
  void get_arrow(const RArc& ar, std::vector<Entity*>& es)const;
  void get_arrow(const Point& pt, const Normal& nor, std::vector<Entity*>& es)const;
	void get_arrow_line     (const Point& real_dimpt,const Normal& nor,std::vector<Line*>& lines) const;
	void get_arrow_circle   (const Point& real_dimpt,std::vector<Circle*>& circles) const;
	//void get_two_arrow_line (const Point& real_dimpt,const Normal& nor,std::vector<Line*>& lines) const;

  Point get_extend_base(const Point& basept,const Point& dimpt) const;
	Point get_extend_end (const Point& basept,const Point& dimpt) const;

	Point get_start_dim_length(const Point& real_dimpt,const Normal& nor) const;
	Point get_end_dim_length  (const Point& real_dimpt,const Normal& nor) const;
	Point get_dim_length      (const Point& real_dimpt,const Normal& nor, const Text& text) const;

	void get_text(Text& text) const;
	void get_text_frame (      Text& text,std::vector<Entity*>& es      ) const;
	void get_text_line  (const Text& text,std::vector<Line  *>& lines   ) const;
	void get_text_circle(const Text& text,std::vector<Circle*>& circles ) const;
	void get_text_arc   (const Text& text,std::vector<RArc  *>& arcs    ) const;

private:
	std::string name_;	        //��ʽ��
	std::string text_style_;   //������ʽ
	//int text_precision_;  //���־���
//   ROUNDING_TYPE rounding_type_;     ////ȡ�᷽ʽ
//   int  					text_precision_;    ////С�������λ��
//   bool 					text_fill_  ;       ////С��λ���Ƿ��룬���Ƿ���ʾβ����0
   double text_precision_;    // ���־���
   int    decimal_place_;    // С��λ��
   bool   decimal_addends_;   // ��ʾС����β��0
  


	//����������
	Float extendstartoff_;
	Float extendendoff_;
	//�ĵ��ע����ע�߳���
	Float start_dim_length_;
	Float end_dim_length_;
	//��ͷ����
	Arrow arrowstyle_;          ////��ͷ��ʽ
	Float arrowsize_;           ////��ͷ��С
  ARROW_NUM arrow_num_;       ////��ͷ����
	////��������
	Txt_Frame tf_;              ////�ı�(���)��ʽ
	TextPos   tp_;              ////�ı�λ��
	Float text_hight_;          ////�ı��߶�
  ////��ɫ����
	int text_frame_color_;      ////�����ɫ
	int text_color_;            ////�ı���ɫ
	int line_color_;            ////����ɫ


private:
	void init();
	bool numeric_char(TCHAR ch) const;
	bool numeric_str(std::string str) const;

  std::string get_rounding_text(std::string str)const; 

	static void* operator new(size_t size){
		return ::operator new(size);
	}
	static void operator delete(void* ptr){
		::operator delete(ptr);
	}

private:
	MCT_DEF
};
}
#endif // !defined(AFX_DIMENSION_STYLE_H__C00010D8_0988_4241_8B1D_07C2F38A493E__INCLUDED_)
