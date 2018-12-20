#ifndef __CADMATRIX_H__
#define __CADMATRIX_H__
#include "declare.h"
template<class T>
class CMatrix
{
public:
	CMatrix();
	CMatrix(const CMatrix& Matrix);
	~CMatrix();
	BOOL SetMatrix(DWORD dwRowNum, DWORD dwColNum);

	enum{INITSIZE = 256};

	BOOL IsEmpty() const{return !(m_dwRowNum && m_dwColNum);}	//�жϾ����Ƿ�Ϊ��,
																//���Ϊ��,����TRUE,���򷵻�FALSE
																
	DWORD GetRowNum() const{return m_dwRowNum;}		//�õ����������
	DWORD GetColNum() const{return m_dwColNum;}		//�õ����������

	T* operator [](DWORD dwRow) const{return (dwRow < m_dwRowNum && dwRow >= 0) ? (m_pAddress + dwRow * m_dwColNum) : NULL;}	//���ؾ����е��׵�ַ��
	CMatrix operator +(const CMatrix &matrix)const ;
	CMatrix operator -(const CMatrix &matrix)const ;
	CMatrix operator *(const CMatrix &matrix)const ;
	CMatrix operator *(const CADDOUBLE& value)const ;
	CMatrix& operator +=(const CMatrix &matrix);
	CMatrix& operator -=(const CMatrix &matrix);
	CMatrix& operator *=(const CMatrix &matrix);
	CMatrix& operator *=(const CADDOUBLE& Number);
//	BOOL operator==(const CMatrix& matrix)const ;
//	BOOL operator!=(const CMatrix& matrix)const ;
	CMatrix& operator=(const CMatrix& Other);
private:
	WORD	m_dwRowNum;		//��ʾ�����������
	WORD	m_dwColNum;		//��ʾ�����������

	HANDLE	m_hHeap;		//�Ѿ��
	T		*m_pAddress;	//��ʾ�������������ʼ��ַ��
};

template<class T>
CMatrix<T>::CMatrix()
:m_dwRowNum(0), m_dwColNum(0), m_pAddress(NULL)
{
	m_hHeap = ::HeapCreate(HEAP_NO_SERIALIZE, 0, 0);
	m_pAddress = (T*)::HeapAlloc(m_hHeap, HEAP_NO_SERIALIZE, 0);
}

template<class T>
CMatrix<T>::~CMatrix()
{
	::HeapDestroy(m_hHeap);
}


// ��������		: CMatrix<T>::CMatrix
// ����˵��		: �������캯��
// ����ֵ����	: ��
// ����			: const CMatrix<T> &Matrix
template<class T>
CMatrix<T>::CMatrix(const CMatrix<T> &Matrix)
{
	m_hHeap = ::HeapCreate(HEAP_NO_SERIALIZE, 0, 0);
	int nSize = Matrix.m_dwColNum * Matrix.m_dwRowNum * sizeof(T);
	m_pAddress = (T*)::HeapAlloc(m_hHeap, HEAP_NO_SERIALIZE, nSize);
	if(m_pAddress == NULL)
	{
		::MessageBox(NULL, TEXT("ϵͳ�ڴ治�㣬�����Ƴ�!"),
			TEXT("�ڴ治��"), MB_OK | MB_ICONERROR);
		::ExitProcess(-1);
	}
	::CopyMemory(m_pAddress, Matrix.m_pAddress, nSize);
	m_dwColNum = Matrix.m_dwColNum;
	m_dwRowNum = Matrix.m_dwRowNum;
}


// ��������		: CMatrix<T>::SetMatrix
// ����˵��		: �����趨�����������������
// ����ֵ����	: BOOL ������þ������������ɹ�������ֵTRUE�����򷵻�FALSE
// ����			: DWORD dwRowNum ��������
// ����			: DWORD dwColNum ��������
template<class T>
BOOL CMatrix<T>::SetMatrix(DWORD dwRowNum, DWORD dwColNum)
{
	m_pAddress = (T*)::HeapReAlloc(m_hHeap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY,
						m_pAddress, dwRowNum * dwColNum * sizeof(T));
	if(NULL == m_pAddress)
	{
		m_dwRowNum = 0;
		m_dwColNum = 0;
		return FALSE;
	}
	m_dwRowNum = dwRowNum;
	m_dwColNum = dwColNum;
	return TRUE;
}


//// ��������		: CMatrix<T>::operator[]
//// ����˵��		: 
//// ����ֵ����	: T* 
//// ����			: DWORD dwRow ����
//template<class T>
//T* CMatrix<T>::operator[](DWORD dwRow) const
//{
////	if(NULL == m_pAddress || dwRow >= m_dwRowNum || dwRow < 0)
////		return NULL;
//
//	return m_pAddress + dwRow * m_dwColNum;
//}


// ��������		: CMatrix<T>::operator+
// ����˵��		: 
// ����ֵ����	: CMatrix<T> 
// ����			: const CMatrix& matrix
template<class T>
CMatrix<T> CMatrix<T>::operator+(const CMatrix& matrix) const
{
	CMatrix<T> tmpMatrix;

	if(matrix.IsEmpty() || IsEmpty())
		return tmpMatrix;
	if(matrix.GetColNum() != m_dwColNum || matrix.GetRowNum() != m_dwRowNum)
		return tmpMatrix;

	tmpMatrix.SetMatrix(m_dwRowNum, m_dwColNum);
	int i, nLength;
	T *pTmp, *pM;
	pTmp = tmpMatrix[0];
	pM = matrix[0];
	nLength = m_dwRowNum * m_dwColNum;
	for(i = 0; i < nLength; i++)
	{
		*(pTmp + i) = *(m_pAddress + i) + *(pM + i);
	}
	return tmpMatrix;
}


// ��������		: CMatrix<T>::operator-
// ����˵��		: 
// ����ֵ����	: CMatrix<T> 
// ����			: const CMatrix& matrix
template<class T>
CMatrix<T> CMatrix<T>::operator-(const CMatrix& matrix) const
{
	CMatrix<T> tmpMatrix;

	if(matrix.IsEmpty() || IsEmpty())
		return tmpMatrix;
	if(matrix.GetColNum() != m_dwColNum || matrix.GetRowNum() != m_dwRowNum)
		return tmpMatrix;

	tmpMatrix.SetMatrix(m_dwRowNum, m_dwColNum);
	int i, nLength;
	T *pTmp, *pM;
	pTmp = tmpMatrix[0];
	pM = matrix[0];
	nLength = m_dwRowNum * m_dwColNum;
	for(i = 0; i < nLength; i++)
	{
		*(pTmp + i) = *(m_pAddress + i) - *(pM + i);
	}
	return tmpMatrix;
}


// ��������		: CMatrix<T>::operator*
// ����˵��		: 
// ����ֵ����	: CMatrix<T> 
// ����			: const CMatrix& matrix
template<class T>
CMatrix<T> CMatrix<T>::operator*(const CMatrix& matrix) const
{
	CMatrix<T> tmpMatrix;

	if(matrix.IsEmpty() || IsEmpty())
		return tmpMatrix;
	if(matrix.GetRowNum() != m_dwColNum)
		return tmpMatrix;

	tmpMatrix.SetMatrix(m_dwRowNum, matrix.GetColNum());

	DWORD i, j, nCounter;
	T Sum;
	for(i = 0; i < m_dwRowNum; i++)
	{
		for(j = 0; j < matrix.GetColNum(); j++)
		{
			Sum = 0;
			for(nCounter = 0; nCounter < m_dwColNum; nCounter++)
			{
				Sum += (*(m_pAddress + i*m_dwColNum + nCounter)) * (matrix[nCounter][j]);
			}
			tmpMatrix[i][j] = Sum;
		}
	}

	return tmpMatrix;
}


// ��������		: CMatrix<T>::operator*
// ����˵��		: 
// ����ֵ����	: CMatrix<T> 
// ����			: const CADDOUBLE& value
template<class T>
CMatrix<T> CMatrix<T>::operator*(const CADDOUBLE& value) const
{
	CMatrix<T> tmpMatrix;

	DWORD i, dwSize;
	dwSize = m_dwColNum * m_dwRowNum * sizeof(T);
	tmpMatrix.SetMatrix(m_dwRowNum ,m_dwColNum);
	T *pAdd = tmpMatrix[0];
	for(i = 0; i < dwSize; i++)
	{
		*(pAdd + i) *= value;
	}

	return tmpMatrix;
}


// ��������		: CMatrix<T>::operator+=
// ����˵��		: 
// ����ֵ����	: CMatrix<T>& 
// ����			: const CMatrix& matrix
template<class T>
CMatrix<T>& CMatrix<T>::operator+=(const CMatrix& matrix)
{
	if(matrix.IsEmpty() || IsEmpty())
		return *this;
	if(matrix.GetColNum() != m_dwColNum || matrix.GetRowNum() != m_dwRowNum)
		return *this;

	int i, nLength;
	T *pM;
	pM = matrix[0];
	nLength = m_dwRowNum * m_dwColNum;
	for(i = 0; i < nLength; i++)
	{
		*(m_pAddress + i) = *(m_pAddress + i) + *(pM + i);
	}
	return *this;
}


// ��������		: CMatrix<T>::operator-=
// ����˵��		: 
// ����ֵ����	: CMatrix<T>& 
// ����			: const CMatrix& matrix
template<class T>
CMatrix<T>& CMatrix<T>::operator-=(const CMatrix& matrix)
{
	if(matrix.IsEmpty() || IsEmpty())
		return *this;
	if(matrix.GetColNum() != m_dwColNum || matrix.GetRowNum() != m_dwRowNum)
		return *this;

	int i, nLength;
	T *pM;
	pM = matrix[0];
	nLength = m_dwRowNum * m_dwColNum;
	for(i = 0; i < nLength; i++)
	{
		*(m_pAddress + i) = *(m_pAddress + i) - *(pM + i);
	}
	return *this;
}


// ��������		: CMatrix<T>::operator*
// ����˵��		: 
// ����ֵ����	: CMatrix<T> 
// ����			: const CMatrix& matrix
template<class T>
CMatrix<T>& CMatrix<T>::operator*=(const CMatrix& matrix)
{
	CMatrix<T> tmpMatrix;

	if(matrix.IsEmpty() || IsEmpty())
		return *this;
	if(matrix.GetRowNum() != m_dwColNum)
		return *this;

	tmpMatrix.SetMatrix(m_dwRowNum, matrix.GetColNum());

	DWORD i, j, nCounter;
	T Sum;
	for(i = 0; i < m_dwRowNum; i++)
	{
		for(j = 0; j < matrix.GetColNum(); j++)
		{
			Sum = 0;
			for(nCounter = 0; nCounter < m_dwColNum; nCounter++)
			{
				Sum += (*(m_pAddress + i*m_dwColNum + nCounter)) * (matrix[nCounter][j]);
			}
			tmpMatrix[i][j] = Sum;
		}
	}

	SetMatrix(m_dwRowNum, matrix.GetColNum());
	*this = tmpMatrix;

	return *this;
}


// ��������		: CMatrix<T>::operator*=
// ����˵��		: 
// ����ֵ����	: CMatrix<T> 
// ����			: const double& value
template<class T>
CMatrix<T>& CMatrix<T>::operator*=(const CADDOUBLE& value)
{
	DWORD i, j;
	for(i = 0; i < m_dwRowNum; i++)
	{
		for(j = 0; j < GetColNum(); j++)
		{
			m_pAddress[i * m_dwColNum + j] *= value;
		}
	}

	return *this;
}

//
//// ��������		: ==
//// ����˵��		: 
//// ����ֵ����	: BOOL CMatrix<T>::operator 
//// ����			: const CMatrix& matrix
//template<class T>
//BOOL CMatrix<T>::operator ==(const CMatrix& matrix) const
//{
//	if(m_dwRowNum != matrix.GetRowNum() || m_dwColNum != matrix.GetColNum())
//		return FALSE;
//
//	DWORD nLength, i;
//	nLength = m_dwRowNum * m_dwColNum;
//	CADDOUBLE *p = matrix[0];
//	int nOffset;
//
//	for(i = 0; i < nLength; i++)
//	{
//		nOffset = i * m_dwColNum;
//		if(UEqu(m_pAddress + nOffset, p + nOffset))
//			break;
//	}
//	return i >= nLength;
//}
//
//
//// ��������		: !=
//// ����˵��		: 
//// ����ֵ����	: BOOL CMatrix<T>::operator 
//// ����			: const CMatrix& matrix
//template<class T>
//BOOL CMatrix<T>::operator !=(const CMatrix& matrix) const
//{
//	return !operator==(matrix);
////	if(m_dwRowNum != matrix.GetRowNum() || m_dwColNum != matrix.GetColNum())
////		return TRUE;
////
////	DWORD nLength, i;
////	nLength = m_dwRowNum * m_dwColNum;
////	CADDOUBLE *p = matrix[0];
////	int nOffset;
////
////	for(i = 0; i < nLength; i++)
////	{
////		nOffset = i * m_dwColNum;
////		if(UEqu(m_pAddress + nOffset, p + nOffset))
////			break;
////	}
////	return i < nLength;
//}

// ��������		: CMatrix<T>::operator=
// ����˵��		: 
// ����ֵ����	: CMatrix<T>& 
// ����			: const CMatrix& matrix
template<class T>
CMatrix<T>& CMatrix<T>::operator=(const CMatrix& matrix)
{
	if(this != &matrix)
	{
		SetMatrix(matrix.GetRowNum(), matrix.GetColNum());
		::CopyMemory(m_pAddress, matrix[0],
			sizeof(T) * matrix.GetRowNum() * matrix.GetColNum());
	}
	return *this;
}

#endif //__CADMATRIX_H__
