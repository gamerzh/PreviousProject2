package org.cocos2dx.cpp;

import com.b.a.AppApplication;
import com.d.event.EventCallBack;
import com.d.event.EventResult;
import com.tbu.androidtools.Debug;

import android.app.Activity;
import android.util.Log;

public class PayService {
	
	private static Activity activity;

	public static void init(Activity activity) {
		PayService.activity = activity;
	}

	public static void pay(final int id) {
		Debug.e("event id="+id);
//		JniPayCallbackHelper.eventSuccess(id);
		boolean result=AppApplication.getInstance().doPEvent(activity, id+"", new EventCallBack(){
			@Override
			public void setEventResult(EventResult eventResult) {
				// TODO Auto-generated method stub
				Log.i("LLK",eventResult.getPResult()?"true":"false");
				if(eventResult.getPResult()){
					if(eventResult.getReward()==null){
						Log.i("LLK","getReward is null");
					}else{
						Integer[] propIds = eventResult.getReward().keySet().toArray(new Integer[] {});  
						Log.i("LLK",propIds.length+"");
						int[] propNum=new int[propIds.length];
						int[] propId=new int[propIds.length];
						for(int i=0;i<propIds.length;i++){
							propId[i]=propIds[i];
							propNum[i]=eventResult.getReward().get(propIds[i]);
						}
						JniPayCallbackHelper.eventSuccess(id,propId,propNum);
					}
				
				}else{
					Debug.e("event pay false id="+id);
					JniPayCallbackHelper.eventFail(id);
				}
		}});
				
		if(!result){
			Debug.e("event pay is close id="+id);
			JniPayCallbackHelper.eventClose(id);
		}
	}
	
	
}