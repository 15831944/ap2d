// Dimension.h: interface for the Dimension class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_DIMENSION_H__D1E47E1C_1A1D_4093_BFC0_E47658D0A00B__INCLUDED_
#define AFX_DIMENSION_H__D1E47E1C_1A1D_4093_BFC0_E47658D0A00B__INCLUDED_


#include "Entity.h"
#include "Point.h"
#include "Text.h"
#include "Dimension_Style.h"
#include "Text_Style.h"


namespace dlhml{



const int MAXSIZE_DIM_TEXT = 512;
const int ARROW_LINE_COUNT = 32;

class Database;
class Rect;
class Text;
class Line;
class Circle;
class RArc;
class Normal;

class OBJECT_API Dimension : public Entity
{
	MY_DECLARE_RUNTIME(Dimension)
	static Object* createob();
protected:
	Dimension();
	Dimension(const Dimension& rhs);
	Dimension& operator=(const Dimension& rhs);
	virtual ~Dimension();

public:

  void  dim_text(std::string text);
  void  text_rotation(Float rot);
  void  text_position(const Point& pos);
  void  text_normal(const Normal& nor);


  std::string dim_text() const					  {return dim_text_;}
  Float text_rotation() const				  {return text_rotation_;}
  Point text_position() const					{return text_position_;}

	void          align_point(Text::AlignPt align);
	Text::AlignPt align_point() const			        ;

public:
  void dim_style_name(std::string         style_name);
  void dim_style_val (Dimension_Style style_val );
  std::string         dim_style_name()const	{return dim_style_name_;}
  Dimension_Style dim_style_val ()const {return dim_style_val_;}

  void set_dim_style(const Dimension_Style& style);
  void set_dim_style(std::string style_name);
  void get_dim_style(Dimension_Style& style)const;
  void get_dim_style(std::string& style_name)const;


	//void text_style_val(Text_Style text_style){text_style_val_ = text_style;}
	//Text_Style text_style_val(){return text_style_val_;}

  virtual void	color_index(int index);
  int				color_index() const	;
  
public:
  Float text_height()const    {return dim_style_val_.text_height();}
  Float text_gdi_height()const{return text_height() * gdi_scale();}


protected:
  Text::AlignPt get_text_align()const;
  

protected:
  ////TEXT
  std::string dim_text_;       ////�ı�����
  Float  text_rotation_;  ////�ı���ת�����ȣ�
  Point  text_position_;  ////�ı�λ��
  ////STYLE
	std::string          dim_style_name_ ; ////��ע��ʽ������
  Dimension_Style dim_style_val_  ; ////��ע��ʽ��ֵ��
  ////NOTHING
	Text::AlignPt align_point_;     ////��ʱû�ã�dim_style_������/��/�¾���
	Text_Style text_style_val_;     ////��ʱû��

	virtual void save_luame(std::ofstream &out,int tab_num);
  virtual void open_luame(lua_State *l);

	
	virtual void get_strme(char *out){;}
	virtual void set_from_strme(char *in){;}
	void get_str_dim();
	void set_from_str_dim();
	
	void get_str_dim_sub(char *name);
	void set_from_str_dim_sub(char *name);

protected:
  void txt_record(const Text& txt)const;
  void txt_change(bool b)const;
protected:
  Text txt_record_;
  bool txt_change_;
  
protected:
  virtual void intersectme(const Entity& e , std::vector<Point>& pts)const;
  virtual void intersectme(const Line  & ln, std::vector<Point>& pts)const;
  virtual void intersectme(const RArc  & ac, std::vector<Point>& pts)const;
  virtual void intersectme(const Circle& cr, std::vector<Point>& pts)const;


protected:
	////��dimʵ��
	virtual void drawme(Draw_Entity& out) const;
	virtual void xor_drawme(Draw_Entity& out) const;
  virtual Rect calc_box2d() const;

  virtual bool intersectme(const Rect& rect) const;
  virtual bool envelopme(const Rect& rect) const;

protected:
	////�����Լ�ʵ��
	virtual void load_me(File& in);
	virtual void save_me(const File& out) const;
  virtual void Dimension::transformbyme(const Matrix& mat);

private:
	void init();
	//void calc_box2d(){}



public:
  ////�õ��乹�ɵĻ���������LINE/ARC/CIRCLE��
  virtual void get_line(std::vector<Entity*>& es)const=0;
  virtual void get_show(std::vector<Entity*>& es)const{};

public:
  ////�ڲ������ڴ棬���ⲿ�ͷ�
	void get_text_show(Text& text) const;
	void get_text_frame_show  (Text& text,      std::vector<Entity*>& es  ) const;
	int  get_text_line_show   (const Text& text,std::vector<Line  *>& lns ) const;
	int  get_text_circle_show (const Text& text,std::vector<Circle*>& cirs) const;
	int  get_text_arc_show    (const Text& text,std::vector<RArc  *>& arcs) const;


  ////�������ͼԪ
protected:
  void show_change(bool b)const;
  void show_record()const;
  std::vector<Entity*>& get_show_record()const;
private:
  std::vector<Entity*> show_record_;
  bool show_change_;

private:
	MCT_DEF
};

//namespace
}
#endif // !defined(AFX_DIMENSION_H__D1E47E1C_1A1D_4093_BFC0_E47658D0A00B__INCLUDED_)
