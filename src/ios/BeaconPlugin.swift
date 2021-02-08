/********* BeaconPlugin.swift Cordova Plugin Implementation *******/

@objc(BeaconPlugin) class BeaconPlugin : CDVPlugin {
    @objc(initBeacon:)
    func initBeacon(_ command: CDVInvokedUrlCommand){
        var pluginResult = CDVPluginResult(status: CDVCommandStatus_ERROR, messageAs: "Not available");
        var resultMsg = "test";
        pluginResult = CDVPluginResult(status: CDVCommandStatus_OK, messageAs: resultMsg);
        commandDelegate.send(pluginResult, callbackId:command.callbackId);
    }
    
    @objc(startBeacon:)
    func startBeacon(_ command: CDVInvokedUrlCommand){
        var pluginResult = CDVPluginResult(status: CDVCommandStatus_ERROR, messageAs: "Not available");
        var resultMsg = "startBeacon test";
        pluginResult = CDVPluginResult(status: CDVCommandStatus_OK, messageAs: resultMsg);
        commandDelegate.send(pluginResult, callbackId:command.callbackId);
    }
    
    @objc(stopBeacon:)
    func stopBeacon(_ command: CDVInvokedUrlCommand){
        var pluginResult = CDVPluginResult(status: CDVCommandStatus_ERROR, messageAs: "Not available");
        var resultMsg = "stopBeacon test";
        pluginResult = CDVPluginResult(status: CDVCommandStatus_OK, messageAs: resultMsg);
        commandDelegate.send(pluginResult, callbackId:command.callbackId);
    }
}
