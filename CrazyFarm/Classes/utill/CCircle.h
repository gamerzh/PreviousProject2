#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CCircle
{
public:
	CCircle(void);
	CCircle(Point& center, float radius); //�ṩԲ����뾶 ��ʼ��Բ
	~CCircle(void);

	bool intersectsRect(Rect& rect) const;//�Ƿ��볤���������ཻ
	bool intersectsCircle(CCircle& circle) const;//�Ƿ���Բ�������ཻ

private:
	CC_SYNTHESIZE(Point, m_center, MCenter);//Բ��
	CC_SYNTHESIZE(float, m_radius, MRadius);//�뾶
};

#define CCCircMake(Point, radius) CCircle::CCircle(Point, (float)(radius))