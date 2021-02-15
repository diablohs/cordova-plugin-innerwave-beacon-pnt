package com.innerwave.beacon.pnt;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.pm.PackageManager;
import android.provider.Settings;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.DialogInterface.OnClickListener;
import android.content.SharedPreferences.Editor;
import android.net.Uri;
import android.os.Bundle;
import android.os.PowerManager;
import android.os.Build;
import android.os.Build.VERSION;
import android.text.Editable.Factory;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AlertDialog.Builder;
import android.app.AlertDialog;
import androidx.core.content.ContextCompat;

import com.pnt.sdk.vestigo.PnTVestigoManager;
import com.pnt.sdk.vestigo.classes.APIAuthentication;
import com.pnt.sdk.vestigo.classes.UserIdentity;
import com.pnt.sdk.vestigo.classes.VestigoResult;
import com.pnt.sdk.vestigo.classes.geofence.VestigoSettings;
import com.pnt.sdk.vestigo.common.CommonConst;
import com.pnt.sdk.vestigo.common.Enum.TYPE;

import java.io.Serializable;

import kotlin.Metadata;
import kotlin.Unit;
import kotlin.jvm.functions.Function2;
import kotlin.jvm.internal.Intrinsics;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import android.util.Log;
/**
 * This class echoes a string called from JavaScript.
 */
public class BeaconPlugin extends CordovaPlugin {
    private final int REQUEST_PERMISSION_LOCATION = 1111;
    private final int REQUEST_APP_SETTINGS = 1111;
    private final int REQUEST_IGNORE_BATTERY_OPTIMIZATIONS = 2222;
    private final SimpleDateFormat dateFormat = new SimpleDateFormat("[HH:mm:ss]", Locale.KOREAN);
    // 아래 정보들은 Vestigo SDK 를 사용하기 위해 PnT 로 부터 발급 받는 인증관련 정보입니다. 추후 실서버 가 준비되면 변경되어질 것입니다.
    private final String oAuthDomain = "https://dev-oauth.indoorplus.io";
    private String apiDomain = "http://13.125.33.143:8401";
    private final String clientId = "nhimc";
    private final String clientSecret = "c3420b3bf4bf0c498ae689e81f600ab3";
    private final String scope = "706E7430-F5F8-466E-AFF9-25556B57FE11";
    private final BroadcastReceiver mVestigoResultReceiver;
    private boolean locationFlag = true;
    private boolean batteryFlag = true;
    private boolean startFlag = false;

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        if (action.equals("initBeacon")) {
            this.initBeacon(callbackContext);
            return true;
        }else if (action.equals("startBeacon")) {
            String message = args.getString(0);
            this.startBeacon(message, callbackContext);
            return true;
        }else if (action.equals("stopBeacon")) {
            this.stopBeacon(callbackContext);
            return true;
        }
        return false;
    }

    /**
     * bluetooth enable 상태를 확인. enable 이 아니면 enable.
     * @return
     */
    private final boolean checkBluetooth() {
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        return !bluetoothAdapter.isEnabled() ? bluetoothAdapter.enable() : true;
    }

     /**
     * 위치 서비스 : 항상 허용 을 체크 및 받을 때 까지 재귀 호출.
     */
    private final void checkPermissions() {
        Context context=cordova.getActivity().getApplicationContext();
        BeaconPlugin self = this;

        if (VERSION.SDK_INT >= 23 && VERSION.SDK_INT < 29) {
           if (ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED) {
              startFlag = true;
              this.ignoreBatteryOptimizations();
           } else {
              cordova.requestPermissions(this, this.REQUEST_PERMISSION_LOCATION, new String[]{Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION});
           }
        } else if (VERSION.SDK_INT >= 29 && VERSION.SDK_INT < 30) {
           if (ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED 
           && ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_GRANTED && ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_BACKGROUND_LOCATION) == PackageManager.PERMISSION_GRANTED) {
            startFlag = true;  
            this.ignoreBatteryOptimizations();
           } else {
              cordova.requestPermissions(this, this.REQUEST_PERMISSION_LOCATION, new String[]{Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION, Manifest.permission.ACCESS_BACKGROUND_LOCATION});
           }
        } else if (VERSION.SDK_INT >= 30) {
           if (ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED && ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_GRANTED && ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_BACKGROUND_LOCATION) == PackageManager.PERMISSION_GRANTED) {
            startFlag = true;  
            this.ignoreBatteryOptimizations();
           } else {
                if(ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED
                    || ContextCompat.checkSelfPermission(context,Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED){
                    cordova.requestPermissions(this, REQUEST_PERMISSION_LOCATION, new String[]{Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION});
                }else{
                    if (ContextCompat.checkSelfPermission(context,Manifest.permission.ACCESS_BACKGROUND_LOCATION) == PackageManager.PERMISSION_GRANTED) {
                        // granted all
                    } else {
                        String alertMsg = "스마트병원 출입통제 및 관리를 위해 위치권한 '항상허용'으로 상태 변경이 필요합니다. (권한 > 위치 > 항상 허용 선택)";
                        if(locationFlag){
                            AlertDialog.Builder builder = new AlertDialog.Builder(this.cordova.getActivity());

                            AlertDialog dialog = builder.setTitle("알림").setMessage(alertMsg).setCancelable(false).setPositiveButton("확인", new DialogInterface.OnClickListener(){
                                // 확인 버튼 클릭시 설정
                                public void onClick(DialogInterface dialog, int whichButton){
                                    Intent intent = new Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
                                    intent.setData(Uri.parse("package:" + cordova.getActivity().getPackageName()));
                                    cordova.startActivityForResult(self, intent, REQUEST_APP_SETTINGS);
                                }
                            }).setNegativeButton("취소", new DialogInterface.OnClickListener(){
                                // 확인 버튼 클릭시 설정
                                public void onClick(DialogInterface dialog, int whichButton){
                                    locationFlag = false;
                                    dialog.dismiss();
                                }
                            }).show();
                        }
                    }
                }
           }
        }  
    }

    private final void ignoreBatteryOptimizations() {
        Context context=cordova.getActivity().getApplicationContext();
        BeaconPlugin self = this;

        if (VERSION.SDK_INT >= 23) {
           PowerManager powerManager = (PowerManager) cordova.getActivity().getSystemService(Context.POWER_SERVICE);

           if (!powerManager.isIgnoringBatteryOptimizations(cordova.getActivity().getPackageName())){
                startFlag = false;
                String alertMsg = "스마트병원 출입통제 및 관리를 위해 배터리 최적화 앱 제외가 필요합니다. (전체 > 앱 검색 > 해당 앱 off)";
 
                if(batteryFlag){
                    AlertDialog.Builder builder = new AlertDialog.Builder(this.cordova.getActivity());
                    builder.setTitle("알림").setMessage(alertMsg).setCancelable(false).setPositiveButton("확인", new DialogInterface.OnClickListener(){
                        // 확인 버튼 클릭시 설정
                        public void onClick(DialogInterface dialog, int whichButton){
                            Intent intent = new Intent();
                            intent.setAction("android.settings.IGNORE_BATTERY_OPTIMIZATION_SETTINGS");
                            cordova.startActivityForResult(self, intent, REQUEST_IGNORE_BATTERY_OPTIMIZATIONS);
                        }
                    }).setNegativeButton("취소", new DialogInterface.OnClickListener(){
                        // 확인 버튼 클릭시 설정
                        public void onClick(DialogInterface dialog, int whichButton){
                            batteryFlag = false;
                            dialog.dismiss();
                        }
                    }).show();
                }
            }else{
                startFlag = true;
            }
        }
    }

    @Override
    public void onRequestPermissionResult(int requestCode, String[] permissions, int[] grantResults) {
        // super.onRequestPermissionResult(requestCode, permissions, grantResults);
        Log.e("BEACONPlugin", "requestCode : " + requestCode);
        Context context=cordova.getActivity().getApplicationContext();
        if (requestCode == this.REQUEST_PERMISSION_LOCATION) {
           if (grantResults[0] != 0) {
            //   String toastMsg = "Service couldn\'t run without permission of location service!";
            //   Toast.makeText(context, toastMsg, 0).show();
              this.checkPermissions();
           } else {
              this.checkPermissions();
           }
        }
    }

    private final void showSimpleAlert(String msg, OnClickListener listener) {
        Context context=cordova.getActivity().getApplicationContext();
        (new Builder(context)).setTitle((CharSequence)"알림").setMessage((CharSequence)msg).setCancelable(false).setPositiveButton((CharSequence)"확인", listener).show();
     }

     //응답 
    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
         super.onActivityResult(requestCode, resultCode, data);

         if (requestCode == this.REQUEST_APP_SETTINGS) {
            this.checkPermissions();
         } else if (requestCode == this.REQUEST_IGNORE_BATTERY_OPTIMIZATIONS) {
            this.ignoreBatteryOptimizations();
         }
    }

    public BeaconPlugin(){
        this.mVestigoResultReceiver = (BroadcastReceiver)(new BroadcastReceiver() {
            public void onReceive(@NotNull Context context, @NotNull Intent intent) {
               Intrinsics.checkNotNullParameter(context, "context");
               Intrinsics.checkNotNullParameter(intent, "intent");
               if (Intrinsics.areEqual(intent.getAction(), CommonConst.ACTION_VESTIGO_SDK_RESULT)) {
                //   boolean success = intent.getBooleanExtra(CommonConst.EXTRA_KEY_SUCCESS, false);
                //   String key = intent.getStringExtra(CommonConst.EXTRA_KEY_STATE);
                //   String message = intent.getStringExtra(CommonConst.EXTRA_KEY_MESSAGE);
                Serializable serializable = intent.getSerializableExtra("VestigoResult");
                VestigoResult vestigoResult = (VestigoResult)serializable;
                String key = vestigoResult.state;
                
                  if (key != null) {
                     switch(key) {
                        case CommonConst.STATE_GOT_TOKEN:
                            if (key.equals("STATE_GOT_SPEC")) {
                            }
                            break;
                        case CommonConst.STATE_GOT_SPEC:
                            if (key.equals("STATE_ERROR")) {
                            }
                            break;
                        case CommonConst.STATE_MONITORING:
                            if (vestigoResult.resultType == TYPE.START && vestigoResult.success) {
                                Log.i("BEACONPlugin","[ACTION_VESTIGO_SDK_RESULT: success] state : STATE_MONITORING, message: " + vestigoResult.message);
                            }
                            break;
                        case CommonConst.STATE_ERROR:
                            if (key.equals("STATE_GOT_TOKEN")) {
                            }
                     }
                  }
   
                  if (!vestigoResult.success) {
                    Log.i("BEACONPlugin","[ACTION_VESTIGO_SDK_RESULT: fail] state : " + key + ", message: " + vestigoResult.message);
                  }
               }   
            }
        });
    }

    private void initBeacon(CallbackContext callbackContext) {
        JSONObject json = new JSONObject();

        checkBluetooth();
        checkPermissions();
        try {
            json.put("result", "success");
        }catch (JSONException e) {
            try {
                json.put("result", "fail");
                json.put("message", e.toString());
            }catch (JSONException ex) {}
            callbackContext.error(json.toString());
        }
        callbackContext.success(json.toString());
    }

    private void startBeacon(String message, CallbackContext callbackContext) {
        JSONObject json = new JSONObject();

        if(startFlag){            
            Context context=cordova.getActivity().getApplicationContext();
            cordova.getActivity().registerReceiver(this.mVestigoResultReceiver, new IntentFilter("ACTION_VESTIGO_SDK_RESULT"));
            String targetId = "test_android_01";
            String targetName = "test_android_01";

            try {
                json = new JSONObject(message);               
                targetId = json.getString("mmrId");
                targetName = json.getString("mmrNm");

                json = new JSONObject();
                json.put("result", "success");
            }catch (JSONException e) {
                Log.e("BEACONPlugin", e.toString());
                try {
                    json.put("result", "fail");
                    json.put("message", e.toString());
                }catch (JSONException ex) {
                }
                callbackContext.error(json.toString());
            }            

            PnTVestigoManager pnTVestigoManager = PnTVestigoManager.getInstance();
            APIAuthentication apiAuthentication = new APIAuthentication(oAuthDomain, apiDomain, clientId, clientSecret, scope);
            pnTVestigoManager.setParameterInfo(apiAuthentication, new UserIdentity(targetId, targetId));
            PnTVestigoManager.getInstance().addSettings(new VestigoSettings(true, true, 1000f));
            pnTVestigoManager.getInstance().startPnTVestigoService(context);   
            
            callbackContext.success(json.toString());
        }else{
            try {
                json.put("result", "fail");
                json.put("message", "권한 설정이 완료되지 않았습니다.");
            }
            catch (JSONException ex) {
            }
            callbackContext.error(json.toString());
        }
    }

    private void stopBeacon(CallbackContext callbackContext) {
        JSONObject json = new JSONObject();
        
        try {
            if(startFlag){   
                PnTVestigoManager.getInstance().stopPnTVestigoService(cordova.getActivity().getApplicationContext());
                json.put("result", "success");
                callbackContext.success(json.toString());
            }else{
                json.put("result", "fail");
                json.put("message", "Beacon Plugin이 Start 되지 않아서 중지 할 수 없습니다.");
                callbackContext.error(json.toString());
            }
            
        }
        catch (JSONException ex) {
        }
    }   
}