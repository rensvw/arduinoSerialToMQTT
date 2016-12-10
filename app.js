const SerialPort = require("serialport");
const mqtt = require('mqtt');
const config = require('./config');

const serialport = new SerialPort(config.serialport, {
    baudrate: config.baudrate,
    parser: SerialPort.parsers.readline('\n')
});
const clientOutput = mqtt.connect('mqtt://' + config.mqtt.hostname);
const clientInput = mqtt.connect('mqtt://' + config.mqtt.hostname);

clientInput.on('connect', function() {
    clientInput.subscribe(config.mqtt.namespaceInput);
});

clientOutput.on('connect', function() {
    clientOutput.subscribe(config.mqtt.namespaceOutput);
});

serialport.on("open", function() {
    serialport.on('data', function(data) {
        clientOutput.publish(config.mqtt.namespaceOutput, data);
    });
    clientInput.on('message', function(topic, message) {
        serialport.write(message, function(err) {
            if (err) {
                return console.log('Error on write: ', err.message);
            }
        });
    });
});