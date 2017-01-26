var config = {};

config.debug = process.env.DEBUG || false;

config.serialport = process.env.SERIAL_PORT || "/dev/ttyACM2";
config.baudrate = process.env.BAUD_RATE || 9600;

config.mqtt = {};
config.mqtt.namespaceOutput = process.env.MQTT_NAMESPACE_OUTPUT || 'legoHouseWoonkamerOutput';
config.mqtt.namespaceInput = process.env.MQTT_NAMESPACE_INPUT || 'legoHouseWoonkamerInput';
config.mqtt.hostname = process.env.MQTT_HOSTNAME || '94.211.191.154';
config.mqtt.port = process.env.MQTT_PORT || 1883;

module.exports = config;