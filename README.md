knx-sensor
===

Impelemtation of an knx sensor module combined with an 80 channel knx logic module based on the [knx stack](https://github.com/thelsing/knx) from thelsing. The used knx stack allows a parametrization via ETS in general, this project requires ETS 5.6 or higher.

Itis implemented for the SAMD21 version of the knx stack. Currently it uses my fork of the [knx stack](https://github.com/mumpf/knx), this will change in future.

It is a PlatformIO project and needs a working ETS 5.6 (or higher) installed on the same PC.

Initial installation and build instructions can be found in the [project itself](https://github.com/mumpf/knx-sensor/blob/release/doc/knx-dev-setup.md).

Update instruction (for an updated firmware or application build) can be also found in the [project documentation](https://github.com/mumpf/knx-sensor/blob/release/doc/knx-update-setup.md)

This project depends on following projects:

* [knx-wire](https://github.com/mumpf/knx-wire)
* [knx-logic](https://github.com/mumpf/knx-logic)
* [knx-common](https://github.com/mumpf/knx-common)
* [knx](https://github.com/mumpf/knx)

Hardware to use the software with is described in [knx-user-forum/KONNEKTING](https://knx-user-forum.de/forum/projektforen/konnekting/1114105-konnekting-raum-sensormodul-temp-hum-voc-co2-onewire-buzzer?p=1460098#post1460098).

With small changes it should be possible to use it on any SAMD21 board.

There are application descriptions available:

* [Applicasion Sensor](https://github.com/mumpf/knx-sensor/blob/release/doc/Applikationsbeschreibung-Sensor.pdf) describes features of the sensor part of application and firmware (in German).
* [Application WireGateway](https://github.com/mumpf/knx-wire/blob/release/doc/Applikationsbeschreibung-Wire.pdf) describes features of the one wire part of application and firmware (in German).
* [Application Logic](https://github.com/mumpf/knx-logic/blob/release/doc/Applikationsbeschreibung-Logik.pdf) describes features of the logic part of application and firmware (in German).

Thanks to all, who made this project successful.
