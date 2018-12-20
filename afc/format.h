#ifndef _AFC_FORMAT_H_
#define _AFC_FORMAT_H_

#include "export.h"
#include "str.h"

namespace afc{


// ��������
AFCAPI int round_off(double d);
// ���⾫������
AFCAPI double round(double d, double precision);
// ��ʽ��������
// precision  :���ȣ�����ģ����
// bit        :��ʾС��λ��
// addends    :��ʾС������β��0
AFCAPI string format(double d, double precision, int bit, bool addends);
AFCAPI string format(double d, int bit = 6, bool addends = true);
AFCAPI string format(int i);



}//namespace

#endif//FILE
