knx-sensor
===

Impelemtation of an knx sensor module combined with an 80 channel knx logic module based on the [knx stack](https://github.com/thelsing/knx) from thelsing.

It supports the SAMD version of the stack. Currently it uses my fork of the [knx stack](https://github.com/mumpf/knx), this will change in future.

It is a PlatformIO project and needs a working ETS 5.6 (or higher) installed on the same PC.

Dependent Projects are:

* [knx-logic](https://github.com/mumpf/knx-logic)
* [knx-common](https://github.com/mumpf/knx-common)
* [knx](https://github.com/mumpf/knx)

Hardware to use the software with is described in [knx-user-forum/KONNEKTING](https://knx-user-forum.de/forum/projektforen/konnekting/1114105-konnekting-raum-sensormodul-temp-hum-voc-co2-onewire-buzzer?p=1460098#post1460098).

With small changes it should be possible to use it on any SAMD21 board.

Thanks to all, who made this project successful.
