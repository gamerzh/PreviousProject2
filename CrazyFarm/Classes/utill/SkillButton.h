/** 
    ʵ�ּ�����ȴЧ�� 

    Notice:����childʱҪע�����²��ϵ
    ���·��ǰ�ť ����ǰ�͸����ģ��ͼƬ ���Ϸ���CCProgressTimer����������
*/
#ifndef _SKILLBUTTON_H_
#define _SKILLBUTTON_H_
#include <cocos2d.h>
USING_NS_CC;
class SkillButton : public Node
{
public:
    SkillButton();
    virtual ~SkillButton();

    /** ����һ��SkillButton����
        */
    static SkillButton* createSkillButton(float cdTime,
                                        const char* stencil_file_name, 
                                        const char* button_normal_name, 
                                        const char* button_click_name,
										int propNum);

    /** CDʱ������
        */
    void    setCDTime(float time) { mCDTime = time; }
    float   getCDTime() const { return mCDTime; }

    /** ���ܰ�ť����ص� */
    void    skillClickCallBack(Ref* obj);

    /** ������ȴ��ϻص�*/
    void    skillCoolDownCallBack();

private:

    /** ��ʼ�� */
	bool    init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, int propNum);

private:
    MenuItemImage*   mItemSkill;     // ���ܰ�ť
    Menu*            mMenuSkill;     // ���ܰ�ť����menu
    Sprite*          mStencil;       // �ɰ徫��,��ɫ��͸��(�����Ϊ����ʾһ����ȴ��ʱЧ��)
    ProgressTimer*   mProgressTimer; // ʱ�����������(360����ת)
    float            mCDTime;          // CDʱ��
	int              mPropNum;       //��������
};


#endif