/********* BeaconPlugin.m Cordova Plugin Implementation *******/

@objc(BeaconPlugin) class BeaconPlugin : CDVPlugin {
    @objc(initBeacon:)
    func initBeacon(_ command: CDVInvokedUrlCommand){
        var pluginResult = CDVPluginResult(status: CDVCommandStatus_ERROR, messageAs: "Not available");
        var resultMsg = "test";
        pluginResult = CDVPluginResult(status: CDVCommandStatus_OK, messageAs: resultMsg);
        commandDelegate.send(pluginResult, callbackId:command.callbackId);
    }
  // Member variables go here.
}