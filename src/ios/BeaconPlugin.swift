import UIKit
/********* BeaconPlugin.swift Cordova Plugin Implementation *******/

@objc(BeaconPlugin) class BeaconPlugin : CDVPlugin {
    private var pnTADManager: PnTVestigoManager?
    private var centralManager: CBCentralManager!
    private var locationManager: CLLocationManager!
    var callbackCommand: CDVInvokedUrlCommand!
    /**
     사용자 식별자
     */
    var targetId: String!;  // 소문자,숫자 만 최대 20자 허용.
    var targetName: String!;

    //TODO: 아래 pnt 서버 인증정보는 현재 개발서버를 바라보고 있습니다. 추후 실서버 정보로 변경될 것입니다.
    /**
     필수 파라미터 set (APIAuthentication) : SDK 사용을 위한 API 사용 인증관련 정보
     */
    var oAuthDomain: String!; // oAuth 인증서버
    var apiDomain: String!; // api 서버
    var client_id: String!;
    var client_secret: String!;
    var scope: String!;
    var resultMsg: String!;
    var locationFlag:Bool!;
    var bluetoothFlag:Bool!;
    
    func callbackResult(){
        var pluginResult = CDVPluginResult(status: CDVCommandStatus_ERROR, messageAs: "Not available")
        var resultDict: [String:String] = ["result":"success"]
        
        if(resultMsg != nil && !resultMsg.isEmpty){
            resultDict["result"] = "fail";
            resultDict["message"] = resultMsg;
            
            let jsonData = try! JSONSerialization.data(withJSONObject: resultDict, options: [])
            let decoded = String(data: jsonData, encoding: .utf8)!
            pluginResult = CDVPluginResult(status: CDVCommandStatus_ERROR, messageAs: decoded);
        }else{
            let jsonData = try! JSONSerialization.data(withJSONObject: resultDict, options: [])
            let decoded = String(data: jsonData, encoding: .utf8)!
            
            pluginResult = CDVPluginResult(status: CDVCommandStatus_OK, messageAs: decoded);
        }
        
        
       
        commandDelegate.send(pluginResult, callbackId:callbackCommand.callbackId);
    }
    
    @objc(initBeacon:)
    func initBeacon(_ command: CDVInvokedUrlCommand){
        var pluginResult = CDVPluginResult(status: CDVCommandStatus_ERROR, messageAs: "Not available");
        callbackCommand = command;
        resultMsg = "";
        
        print("initBeacon");
        
        locationFlag = true;
        bluetoothFlag = true;
        
        // oAuthDomain = "https://dev-oauth.indoorplus.io"; // oAuth 인증서버
        // apiDomain = "http://3.35.182.33:8401"; // api 서버
        // client_id = "cmcep";
        // client_secret = "4c0d875631284405c82523523885effe";
        // scope = "706E7430-F5F8-466E-AFF9-25556B571111";

        oAuthDomain = "https://seoulauth.cmcnu.or.kr"; // oAuth 인증서버
        apiDomain = "https://seoulapi.cmcnu.or.kr"; // api 서버
        client_id = "cmcseoul";
        client_secret = "a92eddf22a8a890767d3e1d36e633b98";
        scope = "6C57AFE5-764D-44CB-BDE5-43DFA5549E50";
        
        pnTADManager = PnTVestigoManager.sharedInstance();
        
        //(**필수) 콘솔로그 유무, 기본값 true
        pnTADManager?.setDebugEnable(true);
        //(*선택) PnT Vestigo monitoring 기능을 앱 포그라운드에서 사용 유무 기본값 :true
        pnTADManager?.setVestigoForegroundEnable(true);
        self.showBluetoothAuthAlert();
    }
    
    @objc(startBeacon:)
    func startBeacon(_ command: CDVInvokedUrlCommand){
        resultMsg = "";
        callbackCommand = command;
        let params:String = command.arguments[0] as? String ?? "";
        let data = Data(params.utf8);
       
        print("startBeacon")
        
        // data
        if let json = try! JSONSerialization.jsonObject(with: data, options: []) as? [String : Any] {
          if let mmrId = json["mmrId"] as? Int {
            print(mmrId);
            targetId = String(mmrId);
            targetName = String(mmrId);
          }else if let mmrId = json["mmrId"] as? String {
            print(mmrId);
            targetId = mmrId;
            targetName = mmrId;
          }else{
            resultMsg = "mmrId는 필수값입니다.";
          }
//
//          if let mmrNm = json["mmrNm"] as? String {
//            print(mmrNm);
////            targetName = mmrNm;
//          }
        }
        // SDK 실행 결과 피드백을 위한 delegate 등록 (PnTVestigoDelegate)
        PnTVestigoManager.sharedInstance()?.pntVestigoDelegate = self
        
        /**
         필수 파라미터 set (APIAuthentication) : SDK 사용을 위한 인증관련 정보
         */
        let authenticationInfo:APIAuthentication = APIAuthentication()
        authenticationInfo.oAuthDomain = oAuthDomain
        authenticationInfo.apiDomain =  apiDomain
        authenticationInfo.client_id =  client_id
        authenticationInfo.client_secret =  client_secret
        authenticationInfo.scope =  scope
        
        /**
         필수 파라미터 set (UserIdentity) : 백엔드 시스템에서 현 단말을 구분하기 위한 구분자 / 이름
         */
        let userIdentity: UserIdentity = UserIdentity()
        
        if(targetId == nil){
            targetId = "";
            targetName = "";
        }
        userIdentity.targetId =  targetId// 소문자만, 20자이하
        userIdentity.targetName =  targetName

        let settings: VestigoSettings = VestigoSettings()
        settings.autoStartWhenEnter = true
        settings.autoStopWhenExit = true
        settings.boundaryRadius = 100.0

        let externalParams: Dictionary = [
            "categoryCode" : "outpatient"
        ]

        // pnTADManager?.addSettings(settings)

        // 필수파라미터들을 셋.
        pnTADManager?.setParameterInfoWith(authenticationInfo, userIdentity: userIdentity);
        pnTADManager?.addExternalParameters(externalParams)
        pnTADManager?.startVestigoService()
    }
    
    @objc(stopBeacon:)
    func stopBeacon(_ command: CDVInvokedUrlCommand){
        resultMsg = "";
        callbackCommand = command;
        
        pnTADManager?.stopVestigoService()

        print("stopBeacon")
    }
    
    func showBluetoothAuthAlert() {
//        showSimpleAlert(msg: "Vestigo 서비스를 위해선 bluetooth 기능이 필요합니다. bluetooth 기능이 enable 상태인지 체크합니다. (bluetooth 기능 권한관련 시스템 팝업이 나타나면 '확인'을 선택해주세요.)") { action in
//            // bluetooth central
//            self.pretendBluetoothEnable()
//        }
        self.pretendBluetoothEnable()
    }
    
    func showLocationAuthAlert() {
        // check location auth
        print("isLocationAuthAlways : " + String(isLocationAuthAlways()));
        if(!self.isLocationAuthAlways()) {
            showSimpleAlert(msg: "스마트병원 출입통제 및 관리를 위해 위치권한 '항상허용'으로 상태 변경이 필요합니다."/*위치서비스 권한을 확인합니다. ((위치서비스 기능 권한관련 시스템 팝업이 나타나면 '앱을 사용하는 동안' 을 먼저 선택하세요. 이후 두번째 팝업에서는 '항상 허용'을 선택해주세요.)"*/) { action in
                self.checkLocationAuthorizationAlways()
            }
        }else {
            self.callbackResult()
        }
    }
    
    func showSimpleAlert(msg : String, handler: ((UIAlertAction) -> Void)? = nil) {
        let topMostViewController = UIApplication.shared.keyWindow?.rootViewController
        let alert = UIAlertController(title: "알림", message: msg, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "확인", style: .default, handler: handler))
        DispatchQueue.main.async {
            topMostViewController?.present(alert, animated: true, completion: nil)
        }
    }
}

// MARK: for the permissions
extension BeaconPlugin {
    /**
     사용자에게 bluetooth enable  을 유도하게 하는 에제 입니다.
     Vestigo Service  는  ble 를 통한 location manager 를 사용합니다. 허나 이를 위해선 bluetooth enable이 필수적이기 때문에 이 예제가 제안되어 있습니다.
     IOS 에서의 bluetooth 는 퀵메뉴(대기화면에서 드래그를 통한 퀵메뉴) 를 통한 blutetooth off 는 실제로 bluetooth 기능 자체를 off 하는 것이 아님에 주의.
     */
    private func pretendBluetoothEnable(){
        print("pretendBluetoothEnable")
        
        if(centralManager != nil) {
            centralManager = nil
        }
        
        if #available(iOS 13.0, *) {
            centralManager = CBCentralManager(delegate: self, queue: nil, options: [CBCentralManagerOptionShowPowerAlertKey: false])
        }else {
            centralManager = CBCentralManager(delegate: self, queue: nil, options: [CBCentralManagerOptionShowPowerAlertKey: true])
        }
    }
    /**
     PnT Vestigo Service 는 location manager 권한이 always 로 유지되어야 합니다. 이에 App  단에서 필히 처음 시작 시 권한을 확보할 수 있도록 하기 위해 아래 예제를 구현해두었습니다.
     */
    private func checkLocationAuthorizationAlways() {
        print("checkLocationAuthorizationAlways")
        locationManager = CLLocationManager()
        self.locationManager.delegate = self
        requestLocationAuthorization()
    }
    
    //* 위치동의 권한 필수***(항상허용 권한 필요)
    private func requestLocationAuthorization() {
        let currentStatus = CLLocationManager.authorizationStatus()
        print("requestLocationAuthorization  currentStatus:\(currentStatus.rawValue)")
        
        switch currentStatus {
            case .denied:
                self.locationFlag = false
                self.resultMsg = "위치서비스 권한을 거부하셨습니다."
                callbackResult()
                break;
            case .notDetermined:                
                DispatchQueue.main.async{
                    self.locationManager.requestWhenInUseAuthorization()
                }
                break;
            case .restricted:
                self.locationFlag = false
                self.resultMsg = "위치 정보를 사용한다고 말을 하지 않은 앱"
                DispatchQueue.main.async{
                    self.locationManager.requestWhenInUseAuthorization()
                }
                break;
            case .authorizedWhenInUse:
                DispatchQueue.main.async{
                    self.locationManager.requestAlwaysAuthorization()
                }
                
                self.callbackResult()
                break;
            case .authorizedAlways:
                callbackResult()
                break;
            @unknown default:
                DispatchQueue.main.async{
                    self.locationManager.requestWhenInUseAuthorization()
                }
        }
    }
    
    private func isLocationAuthAlways() -> Bool {
        let currentStatus = CLLocationManager.authorizationStatus()
        if(currentStatus == .authorizedAlways) {
            return true
        }
        return false
    }
}

// MARK: PnTVestigoDelegate
extension BeaconPlugin: PnTVestigoDelegate {
    
    func onVestigoResult(_ result: VestigoResult!) {
        
        let type = result.resultType
        let success = result.success
        let state = result.state
        let message = result.message
        
        print("onVestigoResult: type: \(type) success:\(success), state: \(state), message: \(String(describing: message))")
        
        switch type {
            case .start:
                if(success) {
                }else{
                    self.resultMsg = message;
                }
                break;
            case .stop:
                if(success) {
                }else{
                    self.resultMsg = message;
                }
                break;
            default :
                break;
        }
        self.callbackResult()
    }
}

// MARK: CBCentralManagerDelegate
extension BeaconPlugin: CBCentralManagerDelegate {
    //(*선택)블루투스 상태 예시, ' '블루투스 동의는 필수' '
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        print("CBCentralManager.state : \(central.state.rawValue)")
        switch central.state {
        case .unknown, .unauthorized, .poweredOff, .resetting:
            showSimpleAlert(msg: "서비스를 위해선 bluetooth 기능이 필요합니다. bluetooth 기능을 enable 해주세요.") { action in
                // User denied bluetooth enable.
                self.bluetoothFlag = false
                self.showLocationAuthAlert()
            }
            break
        case .unsupported:
            print("This device couldn't use the Service!!!")
            self.bluetoothFlag = false
            //showSimpleAlert(msg: "이 기기에서는 서비스 사용을 할수 없습니다. 관리자에게 문의 하세요.")
            callbackResult()
            break
        case .poweredOn:
            self.showLocationAuthAlert()
            break
            
        @unknown default:
            callbackResult()
            break
        }
    }
}

// MARK: CLLocationManagerDelegate
extension BeaconPlugin: CLLocationManagerDelegate {
    //(**필수) 위치권한 동의 '항상허용'Delegate
    public func locationManager(_ manager: CLLocationManager,
        didChangeAuthorization status: CLAuthorizationStatus) {
        print("didChangeAuthorization  \(status.rawValue)")
        
        if(status == .notDetermined || status == .authorizedWhenInUse) { //인증요청
            self.requestLocationAuthorization()
        }else if(status == .authorizedAlways) {//항상허용에 동의한 경우
//            callbackResult()
        }else { //그 외
            self.locationFlag = false
            self.resultMsg = "사용자가 위치서비스 항상허용을 선택하지 않음."
            callbackResult()
        }
    }
}

