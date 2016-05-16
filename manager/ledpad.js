var serialport = require('serialport');
var SerialPort = serialport.SerialPort;

// list serial ports:
serialport.list(function (err, ports) {
    ports.forEach(function (port) {
        console.log(port.comName);
    });
});

var portName = "/dev/cu.usbmodem1421";
function Ledpad() {
    var myPort = new SerialPort(portName, {
        baudRate: 9600,
        // look for return and newline at the end of each data packet:
        parser: serialport.parsers.readline("\n")
    });
    myPort.on('open', showPortOpen);
    myPort.on('data', sendSerialData);
    myPort.on('close', showPortClose);
    myPort.on('error', showError);

    function showPortOpen() {
        console.log('port open. Data rate: ' + myPort.options.baudRate);
    }

    function sendSerialData(data) {
        console.log(data);
    }

    function showPortClose() {
        console.log('port closed.');
    }

    function showError(error) {
        console.log('Serial port error: ' + error);
    }

    var data = "0" + "10".repeat(128);
    myPort.open(function (error) {
        myPort.write(data);
    });
};
module.exports = new Ledpad();