// Matrix.cpp: implementation of the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Matrix_d.h"

#include "Entity.h"
#include "Point.h"
#include "Line.h"
#include "Normal.h"
//#include "..\DrawDll\reitrace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#pragma warning(push)
	#pragma warning(disable:4244)

namespace dlhml{
void Matrix::init()
{
	//x
	mat[0][0]=1;
	mat[1][0]=0;
	mat[2][0]=0;
	mat[3][0]=0;

	//y
	mat[0][1]=0;
	mat[1][1]=1;
	mat[2][1]=0;
	mat[3][1]=0;

	//z
	mat[0][2]=0;
	mat[1][2]=0;
	mat[2][2]=1;
	mat[3][2]=0;

	//
	mat[0][3]=0;
	mat[1][3]=0;
	mat[2][3]=0;
	mat[3][3]=1;

//  init_type();
}

//void Matrix::init_type()
//{
//  type_ = NONE_MAT;
//  rota_radian_ = 0;
//  scale_times_ = 1;
//}

Matrix::Matrix()
MCT_INIT1("Matrix")
{
	init();
}
Matrix::Matrix(const Matrix& rhs)
MCT_INIT1("Matrix")
{
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j] = rhs.mat[i][j];
		}
	}
}
Matrix& Matrix::operator=(const Matrix& rhs)
{
	if(this == &rhs)
		return *this;
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j] = rhs.mat[i][j];
		}
	}
	return *this;
}
Matrix& Matrix::operator=(Float (&m)[4][4])
{
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j] = m[i][j];
		}
	}
	return *this;
}
Matrix::~Matrix()
{

}
Matrix Matrix::operator+(const Matrix& rhs) const
{
	Matrix m;
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			m.mat[i][j]=mat[i][j]+rhs.mat[i][j];
		}
	}
	return m;
}
Matrix Matrix::operator-(const Matrix& rhs) const
{
	Matrix m;
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			m.mat[i][j]=mat[i][j]-rhs.mat[i][j];
		}
	}
	return m;
}
Matrix Matrix::operator*(const Matrix& rhs) const
{
	Matrix m;
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			Float sum = 0;
			for(int k=0;k<4;++k)
				sum += mat[i][k]*rhs.mat[k][j];
			m.mat[i][j] = sum;
		}
	}
	return m;
}
Matrix Matrix::operator*(Float val) const
{
	Matrix m;
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			m.mat[i][j]=mat[i][j]*val;
		}
	}
	return m;
}
Matrix& Matrix::operator+=(const Matrix& rhs)
{
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j]+=rhs.mat[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs)
{
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j]-=rhs.mat[i][j];
		}
	}
	return *this;
}
Matrix& Matrix::operator*=(const Matrix& rhs)
{
	Matrix m;
	m = *this * rhs;
	*this = m;
	return *this;
}
Matrix& Matrix::operator*=(Float val)
{
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j]*=val;
		}
	}
	return *this;
}

void Matrix::set_move(const Point & st, const Point& ed)
{
  set_move(Normal(st,ed));
}
void Matrix::set_move(const Normal& nor)
{
  set_move(nor.x(), nor.y(), nor.z());
}
void Matrix::set_move(const Point & pt )
{
  set_move(pt.x, pt.y, pt.z);
}
void Matrix::set_move(const Line & ln )
{
  Normal nor;
  nor.set_data(ln.start(),ln.end());
  set_move(nor);
}
void Matrix::set_move(Float dx, Float dy, Float dz)
{
	init();
	mat[3][0]=dx;
	mat[3][1]=dy;
	mat[3][2]=dz;
//  type_=MOVE_MAT;
}
void Matrix::set_scale(Float dx, Float dy, Float dz)
{
	init();
	mat[0][0]=dx;
	mat[1][1]=dy;
	mat[2][2]=dz;
//  type_=SCALE_MAT;
}

void Matrix::set_rotation_degree(Float alpha, Float beta, Float gamma)
{
  Float a_rad = dlhml::degree_2_radian(alpha);
  Float b_rad = dlhml::degree_2_radian(beta);
  Float g_rad = dlhml::degree_2_radian(gamma);
  set_rotation_radian(a_rad, b_rad, g_rad);
}

void Matrix::set_rotation_radian(Float alpha, Float beta, Float gamma)
{
	init();
	//x
	mat[0][0]=cos(beta)*cos(gamma);
	mat[1][0]=sin(alpha)*sin(beta)*cos(gamma)-cos(alpha)*sin(gamma);
	mat[2][0]=cos(alpha)*sin(beta)*cos(gamma)+sin(alpha)*sin(gamma);
	//y
	mat[0][1]=cos(beta)*sin(gamma);
	mat[1][1]=sin(alpha)*sin(beta)*sin(gamma)+cos(alpha)*cos(gamma);
	mat[2][1]=cos(alpha)*sin(beta)*sin(gamma)-sin(alpha)*cos(gamma);
	//z
	mat[0][2]=-sin(beta);
	mat[1][2]=sin(alpha)*cos(beta);
	mat[2][2]=cos(alpha)*cos(beta);

//  type_=ZRAOTA_MAT;
//  rota_radian_ = gamma;
}

void Matrix::set_x_rotation_degree(Float alpha)
{
  Float rad = dlhml::degree_2_radian(alpha);
  set_x_rotation_radian(rad);
}

void Matrix::set_x_rotation_radian(Float alpha)
{
	init();
	//y
	mat[1][1]=cos(alpha);
	mat[2][1]=-sin(alpha);
	//z
	mat[1][2]=sin(alpha);
	mat[2][2]=cos(alpha);
//  type_=RAOTA_MAT;
}

void Matrix::set_y_rotation_degree(Float beta)
{
  Float rad = dlhml::degree_2_radian(beta);
  set_y_rotation_radian(rad);
}

void Matrix::set_y_rotation_radian(Float beta)
{
	init();
	//x
	mat[0][0]=cos(beta);
	mat[2][0]=sin(beta);
	//z
	mat[0][2]=-sin(beta);
	mat[2][2]=cos(beta);
//  type_=RAOTA_MAT;
}

void Matrix::set_z_rotation_degree(Float gamma)
{
  Float rad = dlhml::degree_2_radian(gamma);
  set_z_rotation_radian(rad);
}

void Matrix::set_z_rotation_radian(Float gamma)
{
//	ReiTrace::out("gamma = ",gamma);
	init();
	//x
	mat[0][0]=cos(gamma);
	mat[1][0]=-sin(gamma);
	//y
	mat[0][1]=sin(gamma);
	mat[1][1]=cos(gamma);
//  type_=ZRAOTA_MAT;
//  rota_radian_ = gamma;
}
void Matrix::set_x_axis_mirror()
{
	init();
	mat[1][1]=-1;
//  type_=MIRROR_MAT;
}
void Matrix::set_y_axis_mirror()
{
	init();
	mat[0][0]=-1;
//  type_=MIRROR_MAT;
}

//�������棬�㷨�������ϡ�
//���ò�����Ԫ���ĸ�˹��ȥ������������
void Matrix::inverse()
{
	int i,j,k;
	Float lMax,temp;

	Float B[4][4];
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(i != j)
				B[i][j] = 0.0;
			else
				B[i][j] = 1.0;
		}
	}

	for(i=0;i<4;i++){
		//Ѱ����Ԫ
		lMax = mat[i][i];
		k = i;
		for(j=i+1;j<4;j++){ //ɨ���i+1��n�ĸ���
			if( fabs(mat[j][i]) > fabs(lMax)){
				lMax = mat[j][i];
				k = j;
			}
		}
		//�����Ԫ�����в��ǵ�i�У������н���
		if(k!=i){
			for(j=0;j<4;j++){
				temp = mat[i][j] ;
				mat[i][j] = mat[k][j];
				mat[k][j] = temp;
				//B�������
				temp = B[i][j];
				B[i][j] = B[k][j];
				B[k][j] = temp;
			}
		}
		//�ж���Ԫ�Ƿ���0������ǣ������A�������Ⱦ��󣬲����������
		if(mat[i][i] == 0) return ;
		//��ȥA�ĵ�i�г�ȥi������ĸ���Ԫ��
		temp = mat[i][i];
		for(j=0;j<4;j++){
			mat[i][j] = mat[i][j] / temp; //���Խ�����Ԫ�ر��1
			B[i][j] = B[i][j] / temp; //�������
		}

		for(j=0;j<4;j++){ //�� 0 -> n
			if(j!=i){  //���ǵ�i��
				temp = mat[j][i];
				for(k=0;k<4;k++){ // j��Ԫ�� - i��Ԫ��* j��i��Ԫ��
					mat[j][k] = mat[j][k] - mat[i][k] * temp;
					B[j][k] = B[j][k] - B[i][k] * temp;
				}
			}
		}
	}

	Matrix t;
	t = B;
	*this *= t;

}

}//namespace
#pragma warning(pop)

/*
��Թ��㣨x��y����x������н�Ϊa��ֱ�ߵĶԳƱ任
cosa*cosa-sina*sina					2*sina*cosa							0
2*sina*cosa							sina*sina-cosa*cosa					0
x(sinasina-cosacosa)-2ysinacosa+x	y(cosacosa-sinasina)-2xsinacosa+y	1
*/
