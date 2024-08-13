Esta Libreria fue creada por juanmcassillas
https://github.com/juanmcasillas/ESP32-BLE-Combo

Para que fuera compatible con nuestro proyecto se realizan 3 cambios al código en BleCombo.cpp

Linea 24
static const char *LOG_TAG = "BLEDevice"; --> static const char *LOG_TAG = "EasyPlay";
Está es la Linea que tienes que cambiar si le quieres poner el nombre que tu quieras a tu dispositivo!

Linea 211
BLEDevice::init(deviceName); --> BLEDevice::init(String(deviceName.c_str()));

Linea 228
hid->manufacturer()->setValue(deviceManufacturer); --> hid->manufacturer()->setValue(String(deviceManufacturer.c_str()));
