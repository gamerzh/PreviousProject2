#pragma once
#include <cocos2d.h>
#include "utill/SkillButton.h"
#include "config/ConfigSkill.h"
#include "skillManager.h"
USING_NS_CC;
class SkillBombButton : public SkillButton
{
public:
	static SkillBombButton* createSkillBombButton();
protected:
    /** 技能按钮点击回调 */
    virtual void    skillClickCallBack(Ref* obj);

    /** 技能冷却完毕回调*/
   virtual void    skillCoolDownCallBack();

};

