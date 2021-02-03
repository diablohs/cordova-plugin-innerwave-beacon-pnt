function BeaconPlugin() {
    BeaconPlugin.prototype.ERRORS = {
        BAD_PADDING_EXCEPTION: "BAD_PADDING_EXCEPTION",
        CERTIFICATE_EXCEPTION: "CERTIFICATE_EXCEPTION",
        ILLEGAL_BLOCK_SIZE_EXCEPTION: "ILLEGAL_BLOCK_SIZE_EXCEPTION",
        INIT_CIPHER_FAILED: "INIT_CIPHER_FAILED",
        INVALID_ALGORITHM_PARAMETER_EXCEPTION: "INVALID_ALGORITHM_PARAMETER_EXCEPTION",
        IO_EXCEPTION: "IO_EXCEPTION",
        JSON_EXCEPTION: "JSON_EXCEPTION",
        MINIMUM_SDK: "MINIMUM_SDK",
        MISSING_ACTION_PARAMETERS: "MISSING_ACTION_PARAMETERS",
        MISSING_PARAMETERS: "MISSING_PARAMETERS",
        NO_SUCH_ALGORITHM_EXCEPTION: "NO_SUCH_ALGORITHM_EXCEPTION",
        SECURITY_EXCEPTION: "SECURITY_EXCEPTION"
    }
}

BeaconPlugin.prototype.initBeacon = function (arg0, success, error) {
    cordova.exec(success, error, 'BeaconPlugin', 'initBeacon', [arg0]);
};

BeaconPlugin.prototype.startBeacon = function (arg0, success, error) {
    cordova.exec(success, error, 'BeaconPlugin', 'startBeacon', [arg0]);
};

BeaconPlugin.prototype.stopBeacon = function (arg0, success, error) {
    cordova.exec(success, error, 'BeaconPlugin', 'stopBeacon', [arg0]);
};

BeaconPlugin = new BeaconPlugin();
module.exports = BeaconPlugin;