//@main
@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
    /**
     PnTVestigoManager 는 singtone 객체이지만 필히 AppDelegate  에서 instance참조가 되어야 있어야 background task 가 원활히 동작합니다.
     이 곳의 예제를 참고 부탁드립니다.
     */
    var pnTADManager: PnTVestigoManager?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        
        pnTADManager = PnTVestigoManager.sharedInstance()
        //(**필수) 콘솔로그 유무
        pnTADManager?.setDebugEnable(true)
        //(*선택) PnT Vestigo monitoring 기능을 앱 포그라운드에서 사용 유무 기본값 :true
        pnTADManager?.setVestigoForegroundEnable(true)
        
        return true
    }
}