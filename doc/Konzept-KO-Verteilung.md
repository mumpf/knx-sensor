# Konzept zur Verzeitlung von Kommunikationsobjekten

## Generische KO (in jedem meiner Module)

KO | Name | DPT | Bedeutung
:---:|:---|---:|:--
1 | in Betrieb | 1.002 | Meldet zyklisch auf den Bus, dass das Gerät noch funktioniert
2 | Uhrzeit | 10.001 | Eingnang zum empfangen der Uhrzeit
3 | Datum | 11.001 | Eingang zum empfangen des Datums

Die KO 1-9 sind für generische KO reserviert. In weiteren Modulen darf das kleinste KO mit der Nummer 10 anfangen.

## Sensormodul

KO | Name | DPT | Bedeutung
:---:|:---|---:|:--
10 | Sensorwerte anfordern | 1.016 | Beim Empfang vom Trigger (1) werden alle Sensorwerte auf den Bus gesendet. So kann man mehrere Leseanforderungen sparen.
11 | Sensorfehler | 7.001 | Gibt über eine Bitleiste an, welche Messwerte aufgrund eines aufgetretenen Fehlers nicht erfasst werden können. Falls ein ganzer Sensor ausfällt, werden mehrere Bits gleichzeitig gesetzt
12 | Diagnose | 16.001 | Nur für internen Gebrauch (Debug)
15 | Temperatur | 9.001 | Temperaturmesswert (in °C)
16 | Luftfeuchte | 9.007 | Luftfeuchte (in %)
17 | Luftdruck | 9.006 | Luftdruck (in mBar, nicht Pa!!! mBar = Pa / 100)
18 | VOC | 9.* | Voc-Messwert (einheitenlos)
19 | CO2 | 9.008 | CO2-Messwert (in ppm)
20 | CO2-VOC | 9.008 | Berechneter CO2-Messwert vom VOC (in ppm)
21 | Taupunkt | 9.001 | Berechneter Taupunkt (in °C)
22 | Behaglichkeit | 5.005 | Behaglichkeitswert, errechnet aus Luftfeuchte im Verhältnis zur Temperatur (0-2)
23 | Luftqualitätsampel | 5.005 | Luftgüte entsprechend deutscher Schulnoten (1-6)
24 | Kalibrierungsgrad | 5.001 | Kalibrierungsfortschritt vom BME680 (in %)
30 | Externe Temperatur 1 | 9.001 | Eingang für externe Temperatur 1 (in °C)
31 | Externe Temperatur 2 | 9.001 | Eingang für externe Temperatur 2 (in °C)
32 | Externe Luftfeuchte 1 | 9.007 | Eingang für externe Luftfeuchte 1 (in %)
33 | Externe Luftfeuchte 2 | 9.007 | Eingang für externe Luftfeuchte 2 (in %)
34 | Externer Lufttdruck 1 | 9.006 | Eingang für externen Luftdruck 1 (in mBar)
35 | Externer Lufttdruck 2 | 9.006 | Eingang für externen Luftdruck 2 (in mBar)
36 | Externer VOC 1 | 9.* | Eingang für externen VOC-Wert 1 (einheitenlos)
37 | Externer VOC 2 | 9.* | Eingang für externen VOC-Wert 2 (einheitenlos)
38 | Externe CO2 1 | 9.008 | Eingang für externen CO<sub>2</sub>-Wert 1 (in ppm)
39 | Externe CO2 2 | 9.008 | Eingang für externen CO<sub>2</sub>-Wert 2 (in ppm)

## Logikmodul

KO | Name | DPT | Bedeutung
:---:|:---|---:|:--
n | Eingang 1 | *) | Eingang 1 für einen Logikkanal
n+1 | Eingang 2 | *) | Eingang 2 für einen Logikkanal
n+2 | Ausgang | **) | Ausgang eines Logikkanals

Beim Sensormodul in n=50 und bei 100 Kanälen gehen die KO bis 349.

## OneWire

KO | Name | DPT | Bedeutung
:---:|:---|---:|:--
n | Gruppe 1 | DPT 1.001 | iButton Gruppe 1
n+1 | Gruppe 2 | DPT 1.001 | iButton Gruppe 2
n+2 | Gruppe 3 | DPT 1.001 | iButton Gruppe 3
n+3 | Gruppe 4 | DPT 1.001 | iButton Gruppe 4
n+4 | Gruppe 5 | DPT 1.001 | iButton Gruppe 5
n+5 | Gruppe 6 | DPT 1.001 | iButton Gruppe 6
n+6 | Gruppe 7 | DPT 1.001 | iButton Gruppe 7
n+7 | Gruppe 8 | DPT 1.001 | iButton Gruppe 8
n+10 | OW-Gerät 1 iButton-Ausgang | DPT1.001 | Gerät ist ein iButton und sendet sein Existenz-Signal
n | OW-Gerät 1 Sensor-Ausgang | DPT9.xxx | Gerät ist ein Sensor und sendet sein Messwert
n | OW-Gerät 1 IO-Ein-/Ausgang | DPT5.010 | Gerät ist ein I/O und sendet den Status. Wenn dieses KO beschrieben wird, wird der Wert am Ausgang gesetzt.

Beim Sensormodul können 30 OneWire-Geräte verwaltet werden. Die KO beginnen mit 350 und gehen dann bis 379 (30 KO).

Beim OneWire-Gateway können 120 OneWire-Geräte verwaltet werden. Die KO beginnen mit 10 und enden mit 129 (120 KO). Logikkanäle beginnen dann mit 130 und enden bei 329.

### Wie ist ein OW-Gerät-Ausgang zu interpretieren

Das KO n ist mehrfach belegt und funktioniert unterschiedlich, je nachdem, welches OneWire-Gerät angeschlossen ist. Das KO wird folgerndermaßen genutzt:

#### iButton

Wird beim DS18x20 als DPT1.001 genutzt. Sendet ein true, wenn der iButton am OneWire-Bus hängt, false sonst.

#### Sensor

Wird beim DS18x20 oder DS2438 als DPT9.xxx genutzt. Gibt den gemessenen Sensorwert aus.

#### I/O

Wird beim DS2408 oder DS2413 als DPT5.010 genutzt. Der Wert sendet den Status des IO-Gerätes, wobei jedes Bit im DPT5 einem Bit am Ausgang des OneWire-Devices entspricht.

Wird dieses KO beschrieben, wird der Wert an den Ausgängen des OneWire-Gerätes ausgegeben.

### Beispiel

Bei einem DS2408 sind Bits 0-3 als Input geschaltet, an den 4 Eingängen sind z.B. Fensterkontakte dran. Ferner sind die Bits 4-7 als Output geschaltet, da ist z.B. je eine LED dran, die anzeigt, ob das Fenster offen ist.
Für einen Eingang heißt ein offener Schalter eine 1 und ein geschlossener Schalter eine 0. Für einen Ausgang heißt 1 eine leuchtene LED und eine 0 eine augeschaltete LED.
Fenster 1 ist an Bit 0 (Fensterkontakt) und an Bit 4 (LED). Entsprechend ist Fenster 2 an Bit 1;5 usw.

Wie sieht jetzt eine Kommunikation mit dem KO n aus? Ausgangssituation ist im Beispiel so, dass alle Fenster geschlossen sind und alle LED aus. Der DS2408 würde somit die Bitfolge 

    BIT  76543210
    Wert 00000000 = 0x00

an seinen Pins haben. Das KO n würde genau diesen Wert liefern, wenn man es lesen würde. Es ist der Status dieses OneWire-Gerätes.

Jetzt wird Fenster 0 geöffnet, damit geht Bit 0 auf den Wert 1. Das KO n sendet diesen Wert auf den Bus:

    BIT  76543210
    Wert 00000001 = 0x01

Die Logik, die diese Information auswertet, will mittels der LED anzeigen, dass das Fenster offen ist. Diese Logik schreibt nun auf das KO n den Wert

    BIT  76543210
    Wert 00010000 = 0x10

Der DS2408 schaltet seinen Ausgang entsprechend und bekommt folgende Bitfolge an seinen Pins:

    BIT  76543210
    Wert 00010001 = 0x11

Sobald der Wert am Pin anliegt, der DS2408 also meldet, dass er den Wert übernommen hat, wird der Status über das KO n gesendet. Der gesendete Wert ist somit

    BIT  76543210
    Wert 00010001 = 0x11
