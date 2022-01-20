# Update procedure for a new firmware or application version

Only tested on Windows 10!

This description is just valid, if you successfuly built and installed a firmware and application the first time according to the [dev setup](https://github.com/mumpf/knx-sensor/blob/release/doc/knx-dev-setup.md) instructions.

Open Visual Studio Code. It opens with the last project you used.

In case the opened project is not the sensormodule project, open "Sensormodul (Workplace)", you will find it in File->Open Recent menu.

Press Ctrl-Shift-G (Opens Source Control).

Below "SOURCE CONTROL PROVIDERS" you will find all projects necessary for the firmware:

* knx-sensor
* knx-wire
* knx-logic
* knx-common
* knx

Do for each of them the following:

Click on the project name (i.e. knx-sensor).

There is an additional area called "knx-sensor Git", having a text box below with a text "Message". At the end of the Git-Area you see 3 dots (...) indicating a menu. Click on these 3 dots.

In the upcomming menu click on the topmost entry "Pull".

As said, do this for each project.

As soon as all 5 pulls are finished, continue with the build steps form the initial documentation:

The current board version from MASIFI is v3.1. Due to the fact, that I have to test the release with diferent versions, it might happen, that the firmware is released for any of the tested versions v2, v3 or v3.1.

**Please ensure always - with each update - that the released version fits to your hardware!** To do this, do the following:
Find the version of your hardware board (v1, v2, v3 or v3.1).

    In knx-sensor, edit the file platformio.ini:  
    - there is a line 
            -DBOARD_MASIFI_V... 
    - change the line to the according version of your hardware
            -DBOARD_MASIFI_V31 
      or 
            -DBOARD_MASIFI_V3 
      or 
            -DBOARD_MASIFI_V2 
      or 
            -DBOARD_MASIFI_V1
      or (for the outdoor module)
            -DBOARD_MASIFI_AUSSEN_V13

    - there exist different versions with CRYSTALLESS setting.
      Ensure that
            -DCRYSTALLESS 
      is always  
            ;-DCRYSTALLESS
      or the line is removed.

    - NEW for firmware version >= 2.5: You can enable watchdog-support. 
      With the setting
            -DWATCHDOG
      the watchdog functionality is enabled. The default is
            ;-DWATCHDOG
      which disables watchdog functionality.

Press Ctrl-Shift-B, select the "**Build PlatformIO** knx-sensor" build task and press enter.

Now the compiler starts, this may take a while, there will be many yellow warnings, they can be ignored.

At the end, there should be a message like

    Linking .pio\build\build\firmware.elf
    Building .pio\build\build\firmware.bin
    Checking size .pio\build\build\firmware.elf
    Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
    RAM:   [==        ]  22.0% (used 7216 bytes from 32768 bytes)
    Flash: [======    ]  55.7% (used 145892 bytes from 262144 bytes)
    ============================ [SUCCESS] Took 34.60 seconds ======

Now you successfully build the updated Firmware for the Sensormodule.

## How to upload the Firmware to your Hardware

Connect your device via USB to your PC

Open (again) the file Sensormodul/src/Sensormodul.cpp

Press Ctrl-Shift-B, select "**Upload USB** knx-sensor" build task and press enter.

Wait until file is uploaded.

Afterwards you have to reprogram physical address (PA) and Application from ETS.

## How to build a knxprod for this firmware

Here you have to do exactly the same steps as desribed in the according chapter in the knx-dev-setup.pdf document.
