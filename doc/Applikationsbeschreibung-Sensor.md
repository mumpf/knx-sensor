# Applikationsbeschreibung Sensor

Die Applikation Sensor ist im File Sensormodul-v3.x.knxprod enthalten und erlaubt die Parametrisierung des Sensormoduls mittels der ETS.

Sie ist in die Bereiche

* Änderungshistorie
* Einführung
* Allgemeine Parameter
* Standardsensoren
* 1-Wire
* Logikdokumentation
* Logikkanäle

gegliedert.

Der Punkt 1-Wire ist in der Applikationsbeschreibung WireGateway beschrieben.
Die letzen beiden Punkte sind in der Applikationsbeschreibung Logik beschrieben.

## Änderungshistorie

17.04.2020: Firmware 1.1.0, Applikation 1.4 - 1.7

* Temperaturgrenzen in 'Temperatur anpassen (interner Messwert)' auf +-10°C erhöht. Auch für die anderen Messwerte wurden die Anpassungsintervalle erhöht.
* **inkompatible Änderung**: Statt dem Sensor HDC1080 wird jetzt der Sensor SHT3x unterstützt.
* Aktualisierung im Kapitel 'Update der Applikation'.
* Detailänderungen in der Logik, siehe Applikationsbeschreibung Logik.

01.02.2021 Firmware 2.0.0, Applikation 2.0 - 2.3

* Das Diagnoseobjekt ist jetzt Teil des Logikmoduls und wird auch in der Applikationsbeschreibung Logik dokumentiert. Es wird nicht mehr zusammen mit dem Fehlerobjekt ein- bzw. ausgeschaltet.
* **Inkompatible Änderung**: Zuordnungen zu Gruppenadressen gehen verloren, beschrieben im Kapitel 'Das "alte" Sensormodul aktualisieren'
* Anpassung im Kapitel 'Uhrzeit und Datum nach einem Neustart vom Bus lesen'
* Unterstützung vom neuen VOC-Sensor IAQCore, kann VOC- und (berechneten) CO2-Wert liefern
* Aktualisierung im Kapitel 'Update der Applikation'.

02.03.2021 Firmware 2.4.0, Applikation 2.4 - 2.7

* Dies ist ein reines Logik-Update, dokumentiert in der Applikationsbeschreibung Logik. Es gibt keine Auswirkungen auf die Funktionalität des Sensorteils.
* Ein update der Applikation (wie im entsprechenden Kapitel beschrieben) von einer vorherigen 2.x-Version funktioniert vollständig. Es gehen weder GA-Zuordnungen zu KO noch Parameter verloren.

05.03.2021: Firmware 2.4.1, Applikation 2.4 - 2.7

* FIX Logik: Das Blinkmodul hat fälschlicherweise den Ausgangszustand der Logik verändert. Das konnte bei "nur bei geändertem Ergebnis senden" auch zu unerwarteten Logik-Triggern führen. Immer wenn während des Blinkens am Eingang ein Signal ankam, dass invers zum Blinkstatus war, wurde unerwünscht getriggert.

29.03.2021 Firmware 2.5.0, Applikation 2.4 - 2.7

* Firmware-Update mit Watchdog-Unterstützung, neues Kapitel 'Watchdog-Unterstützung' hinzugefügt
* Für die Programmierung werden jetzt auch "Long Frames" unterstützt, sofern das die Schnittstelle und alle Koppler auf dem Programmierpfad unterstützen. Für 40 Logikkanäle sinkt die Programmierzeit von knapp 2 Minuten auf etwas mehr als eine halbe Minute (ist also um den Faktor 2.5 schneller). Getestet mit der MDT-IP-Schnittstelle.

05.04.2021 Firmware 2.5.1, Applikation 2.4 - 2.7

* Bugfix: Beim Programmieren des Sensormoduls ohne GA (also kein KO hat eine GA zugewiesen) konnte es passieren, dass danach das Modul so hängt, dass nur ein erneutes aufspielen der Firmware per USB das Problem beheben kann. Dies ist ein reines Firmware-Update.

09.04.2021 Firmware 3.0, Applikation 3.1

* Unterstützung des Helligkeitssensors OPT300x
* Unterstützung des Entfernungssensors VL53L1X (Time-of-flight Sensor)
* Neue Sensorauswahl bei "Allgemeine Parameter" mit mehr möglichen Sensorkombinationen. Das Kapitel "Vorhandene Hardware" wurde komplett überarbeitet.
* Bis zu 5 I2C-Sensoren werden ausgewertet
* 1-Wire-Unterstützung mit 30 Kanälen (Siehe Applikationsbeschreibung WireGateway)
* Unterstützung von Longframes beim Programmieren durch die ETS
* Unterstützung von partieller Programmierung durch die ETS, wobei nur die geänderten Parameter übertragen werden, dadurch wesentlich schnellere Programmierung
* Auch eine bestimmte Reiehnfolge der Programmierung (früher: erst PA, dann Applikationsprogramm, erst dann geht partiell) ist nicht mehr erforderlich. Alle Programmierfunktionen (z.B. "PA + Applikation", aber auch immer "Partiell") gehen jetzt, die ETS macht dann das "Richtige" draus.
* Bedingt durch die wesentlich schnellere Progrmmierung gibt es nur noch eine ETS Applikation mit 80 Logikkanälen
* Diese Firmware unterstützt auch den Aussensensor von Masifi über die Einstellung -DBOARD_MASIFI_AUSSEN_V13

12.04.2021: Firmware 3.1.0, Applikation 3.1

* FIX: Bei Zeitschaltuhren hat die Kombination "Feiertage wie Sonntage behandeln" und "Im Urlaub nicht schalten" nicht funktioniert.

17.05.2021 Firmware 3.1, Applikation 3.1.1

* Fix: Der Wert der Luftqualitätsampel wird jetzt auch bei einen VOC-Sensor korrekt berechnet.

24.05.2021: Firmware 3.2.0, Applikation 3.2

* Feature: Einfache Formeln in einer Logik (+, -, *, /, min, max und avg mit 2 Eingängen)
* Feature: Es können jetzt bis zu 30 Benutzerfunktionen im Coding definiert und in der ETS Applikation ausgewählt werden
* Feature: Eingangs-Konverter können jetzt für DPT5, DPT5.001, DPT6, DPT7 und DPT8 auch mit mehreren Einzelwerten definiert werden (ähnlich wie die bisherige Definition von Szenen-Convertern)
* Eingänge können jetzt auch einen DPT-Gerechten konstanten Wert enthalten, der dann in Formeln weiter verarbeitet oder direkt am Ausgang genutzt werden kann^
* Kapitel "Formeln" samt Unterkapiteln neu hinzugefügt.
* Kapitel "Wert für EIN senden" um Formelaufrufe ergänzt.
* Kapitel "Wert für AUS senden" um Formelaufrufe ergänzt.
* Kapitel "Einzelwert-Konverter" ergänzt.
* Kapitel "Konstanten" ergänzt.

11.01.2022: Firmware 3.8.0, Applikation 3.8

* Beta wird zu Release
* Feature: Es wird nicht nur ausgegeben, ob "Heute" bzw. "Morgen" ein Feiertag ist (DPT1), sondern welcher Feiertag es ist (DPT5)
* Kapitel "Feiertage auf dem Bus verfügbar machen" um das neue Feature ergänzt
* **Inkompatible Änderung** KO 5 und KO 6 sind jetzt DPT5.010 statt DPT1.001. **Vor einem Upgrade** müssen alle mit diesen KO verknüpften GA entfernt werden.
* Fix: Eingangskonverter "Differenzintervall" und "Differenzhysterese" für DPT9.x funktionierten nicht, ist jetzt korrigiert
* **Inkompatible Änderung** Bei einem Update gehen die Parameter für Von-/Bis- bzw. Einschalt-/Ausschalt-Wert bei Eingangskonvertern "Differenzintervall" und "Differenzhysterese" für DPT9 verloren. Diese müssen nach einem Update manuell nachgetragen werden.

<div style="page-break-after: always;"></div>

## Einführung

Die vorliegende Software ermöglicht es, ein Do-It-Yourself (DIY) KNX-Sensormodul zu erstellen, das mit der ETS5 programmiert werden kann. Sie besteht, wie bei KNX üblich, aus 2 Teilen:

* der Firmware, die in die Hardware geladen wird
* der ETS-Applikation (knxprod-Datei), die in die ETS geladen wird.

Ferner wird das gesamte Setup zur Entwicklung, Änderung und Erstellung der Software mitgeliefert.

### Hardware

Die bevorzugte Hardware (auf der auch die Entwicklung getestet wird), ist das Sensormodul von Masifi, beschrieben als [Raum Sensormodul](https://knx-user-forum.de/forum/%C3%B6ffentlicher-bereich/knx-eib-forum/diy-do-it-yourself/1479195-raum-sensormodul-hw-thread-f%C3%BCr-temp-hum-pres-voc-co2-1-wire-buzzer) im KNX-User-Forum.

Die Software kann recht einfach auf andere Hardware portiert werden, die auf einem SAMD21 basiert, die Kommunikation mit KNX kann über einen NCN5120/5130 erfolgen oder auch über eine Siemens BCU. Sensoren werden über I2C angeschlossen.

### Funktionsumfang

Die Applikation und die Firmware stellen sehr viele Funktionen in verschiedenen Bereichen zur Verfügung. Dabei ist zu betonen, dass diese verschiedenen Funktionalitäten nicht unbedingt in beliebiger Kombination auch funktionieren können. Gerade hardwareabhängige Funktionen sind nicht in beliebiger Kombinatorik gedacht und auch nicht immer möglich.

Das soll nicht von der Nutzung abhalten, es soll nur klar machen, dass die Intention der Software eine dezentrale ist: Es soll an verschiedensten Stellen im Haus die Möglichkeit gegeben werden, ein paar Kleinigkeiten zu machen (z.B. Temperatur+Luftfeuchte messen, Fensterkontakt abfragen, Sperren durch einen Piep zu bestätigen).

Falls versucht wird, mit dem Sensormodul alle Funktionen gleichzeitig zu nutzen, also:

* 6 Inputs (Fensterkontakte, Schalter)
* 5 iButtons
* 15 1-Wire-Temperatursensoren
* 5 1-Wire Temp-/Hum-Sensoren
* LED-Ausgabe
* Buzzer
* Temperaturmessung
* Luftfeuchtemessung
* Luftdruckmessung
* VOC-Messung
* CO2-Messung
* Helligkeitsmessung
* Entfernungsmessung

das alles z.B. pro Stockwerk anzuschließen und dann auch noch über 80 Logikkanäle das restliche Haus zu steuern, dann wird das potentiell nicht laufen. Eventuell macht es dann mehr Sinn, die Funktionen auf 2, 3 oder 4 Sensormodule aufzuteilen und die in die einzelnen Räume zu plazieren und in den Räumen nur die Funktionalitäten in Betrieb zu nehmen, die dort sinnvoll sind.

Es ist wichtig zu verinnerlichen, dass die vielen Funktionen nicht dafür da sind, alle in einem Gerät genutzt zu werden, sondern dass man in vielen Geräten eher einige Wenige Funktionen nutzen kann.

Hardwareunabhängige Funktionen, in diesem Fall das Logikmodul, sind allerdings so konzipiert, dass sie immer in beliebiger Kombination und in vollem Umfang mit den anderen Features funktionieren und können bzw. sollen auch so genutzt werden.

### Credits

Diese Software wäre ohne die Arbeiten und der Unetstützung einiger Leute aus dem KNX-User-Forum nicht möglich gewesen. Ich möchte mich an dieser Stelle besonders bedanken bei:

* **thesing** für den mit der ETS programmierbaren [KNX-Stack](https://knx-user-forum.de/forum/%C3%B6ffentlicher-bereich/knx-eib-forum/diy-do-it-yourself/1216828-esp8266-knx-mit-ets)
* **Masifi** für das [Raum-Sensormodul](https://knx-user-forum.de/forum/%C3%B6ffentlicher-bereich/knx-eib-forum/diy-do-it-yourself/1479195-raum-sensormodul-hw-thread-f%C3%BCr-temp-hum-pres-voc-co2-1-wire-buzzer) und für die vielen anregenden Diskussionen
* **proggerKA** und **OutOfSync** für die Diskussionen, wie man die Programmierung mit der ETS [schneller machen kann](https://knx-user-forum.de/forum/%C3%B6ffentlicher-bereich/knx-eib-forum/diy-do-it-yourself/1635521-wie-kommuniziert-die-ets-mit-knx-ger%C3%A4ten-z-b-beim-partiellen-programmieren).
* **Klaus Gütter** durch seine vielen Beiträge im Forum, die mich immer wieder zum nachdenken und zu Verbesserungsideen inspiriert haben.
* allen anderen im [KNX-User-Forum](https://knx-user-forum.de), die durch Beiträge direkt oder indirekt diese Software ermöglicht haben.

## Allgemeine Parameter

![Allgemeine Parameter](./AllgemeineParameter.png)
Hier werden Einstellungen getroffen, die die generelle Arbeitsweise des Sensormoduls bestimmen.

### Anzahl verfügbarer Logikkanäle

Dieses Feld gibt an, für wie viele Logikkanäle dieses Applikationsprogramm erstellt wurde.

Diese Angabe dient nur zur Information, sie wird wahrscheinlich in kommenden Versionen der Applikation entfernt werden. Es stehen immer 80 Logikkanäle zur Verfügung.

### Zeit bis das Gerät nach einem Neustart aktiv wird

Nach einem Neustart des Geräts, sei es durch Busspannungsausfall, Reset über den Bus oder auch durch ein Drücken der Reset-Taste, kann man hier festlegen, wie viele Sekunden vergehen sollen, bis das Gerät seine Funktion aufnimmt.

Da das Gerät prinzipiell (sofern parametriert) auch Lesetelegramme auf den Bus senden kann, kann mit dieser Einstellung verhindert werden, dass bei einem Busneustart von vielen Geräten viele Lesetelegramme auf einmal gesendet werden und so der Bus überlastet wird.

### In Betrieb senden alle

Das Gerät kann einen Status "Ich bin noch in Betrieb" über das KO 1 senden. Hier wird das Sendeintervall in Sekunden eingestellt.

### Uhrzeit und Datum nach einem Neustart vom Bus lesen

Dieses Gerät kann Uhrzeit und Datum vom Bus empfangen. Nach einem Neustart können Uhrzeit und Datum auch aktiv über Lesetelegramme abgefragt werden. Mit diesem Parameter wird bestimmt, ob Uhrzeit und Datum nach einem Neustart aktiv gelesen werden.

Wenn dieser Parameter auf "Ja" gesetzt ist, wird die Uhrzeit und das Datum alle 20-30 Sekunden über ein Lesetelegramm vom Bus gelesen, bis eine entsprechende Antwort kommt. Falls keine Uhr im KNX-System vorhanden ist oder die Uhr nicht auf Leseanfragen antworten kann, sollte dieser Parameter auf "Nein" gesetzt werden.

Die im Modul enthaltenen Zeitschaltuhren beginnen erst zu funktionieren, wenn eine gültige Uhrzeit und ein gültiges Datum empfangen wurde. Wenn dieser Prameter auf "Nein" gesetzt wird, kann es sehr lange dauern, bis Zeitschaltuhren nach einem Neustart ihre Funktion aufnehmen.

### Vorhandene Hardware

Die Firmware im Sensormodul unterstützt eine Vielzahl an Hardwarevarianten. Um nicht für jede Hardwarekombination ein eigenes Applikationsprogramm zu benötigen, kann über die folgenden Felder die Hardwareausstattung des Sensormoduls dem Applikationsprogramm mitgeteilt werden.

**Die Angaben in diesem Teil müssen der vorhandenen Hardware entsprechen**, da sie das Verhalten der Applikation und auch der Firmware bestimmen. **Das Applikationsprogramm hat keine Möglichkeit, die Korrektheit der Angaben zu überprüfen.**

Falsche Angaben können zu falschern Konfigurationen der Applikation und somit zum **Fehlverhalten des Sensormoduls** führen.

Das Sensormodul kann 7 verschiedene Standardmesswerte liefern, die von verschiedenen Hardware-Sensoren ermittelt werden können:

* Temperatur (in °C)
* Luftfeuchte (in %)
* Luftdruck (in mBar)
* VOC (einheitenlos)
* CO<sub>2</sub> (in ppm)
* Helligkeit (in Lux)
* Entfernung (in mm)

Es werden bestimmte Hardware-Sensoren unterstützt, deren Messwerte gelesen und entsprechend auf den Bus geschickt werden können.

Die unterstützten Sensoren liefern folgende Messwerte:

Sensorauswahl | Temperatur | Luftfeuchte | Luftdruck | VOC | CO<sub>2</sub> | Helligkeit | Entfernung
---|:---:|:---:|:---:|:---:|:---:|:---:|:---:
SHT3x   | X | X |   |   |   |
BME280  | X | X | X |   |   |
BME680  | X | X | X | X | X<sup>2)</sup>
SCD30   | X | X |   |   | X |
SCD41<sup>1)</sup>   | X | X |   |   | X |
SGP30<sup>1)</sup>   | X | X | | X | X<sup>2)</sup>
IAQCore | | | | X | X<sup>2)</sup>
OPT300x | | | | | | | X
VL53L1X | | | | | | | | X

<sup>1)</sup>Noch in Entwicklung, die ETS Applikation unterstützt bereits die Einstellungen, die Firmware kann diese Sensoren noch nicht auswerten.

<sup>2)</sup>Bei diesem Sensor wird der CO<sub>2</sub>-Wert nicht gemessen, sondern aus dem VOC-Wert berechnet. Die Berechnung findet nicht im Sensormodul, sondern im Sensor selbst statt.

#### Sensorkombination

Das Auswahlfeld **Sensorkombination** ist nur aus Kompatibilität zu früheren Versionen dieser Applikation vorhanden. Es muss unbedingt vom Benutzer auf den Wert "Einzelauswahl" gestellt werden, da dies beim Update nicht automatisch geht. Anschließend bitte diesen Wert nicht mehr ändern. In zukünftigen Versionen dieser Applikation wird es dieses Feld nicht mehr geben.

Dieser manuelle Schritt ist nur nach einem Update aus einer früheren Version dieser Applikation notwendig. Neu in die ETS eingefügte Applikatinen haben bereits den Wert "Einzelauswahl" im Feld stehen.

Falls dieses Feld bei einem zuküftigen Update der Applikation einen anderen Wert als "Einzelauswahl" hat, werden nach diesem zukünftigen Update alle Sensoreinstellungen und alle zugehörigen Gruppenadressen verloren gehen.

In den folgenden Auswahlfeldern kann man für jeden Standardmesswert bestimmen, von welchem Sensor dieser Messwert geliefert werden soll. Dabei können verschiedene Sensoren kombiniert werden. Bestimmte Kombinatinen beeinflussen die Funktionsweise weiterer am Sensormodul angeschlossener Hardware. Solche Kombinationen führen zu Warnmeldungen.

Die Kombination vom BME280 und BME680 ist nicht möglich, da diese Sensoren die gleiche physikalische Adresse haben und somit nicht beide gleichzeitig angeschlossen werden können. Es ist aber keine Einschränkung, da der BME680 auch alle Messwerte liefern kann, die der BME280 liefert.

Sollten beide Sensoren BME280 und BME680 ausgewählt worden sein, erscheint folgende Fehlermeldung:
![Fehler beide BME-Sensoren](FehlerBeideBME.png)

**Achtung**:

Die neue Möglichkeit, Sensoren für Standardmesswerte auszuwählen ermöglicht viele Sensor-Messwert-Kombinationen, die nicht alle vor einem Release getestet werden können. In der folgenden Tabelle werden Sensor-Messwert-Kombinationen angegeben, die bereits erfolgreich geprüft wurden und funktionieren. Ferner können weitere funktioniertende Sensor-Messwert-Kombinationen im KNX-User-Forum ausgetascht werden.

Messwerte | Kombi 1 | Kombi 2 | Kombi 3 | Kombi 4 | Kombi 5 | Kombi 6 | Kombi 7
---|:---:|:---:|:---:|:---:|:---:|:---:|:---:
Temperatur     | SHT3x | BME280 | BME680 |  |         |         |         |
Luftfeuchte    | SHT3x | BME280 | BME680 | SCD30 |         |         |         |
Luftdruck      |       | BME280 | BME680 |       |         |         |         |
VOC            |       |        | BME680 |       | IAQCore |         |         |
CO<sub>2</sub> |       |        | BME680 | SCD30 |         |         |         |
Helligkeit     |       |        |        |       |         | OPT300x |         |
Entfernung     |       |        |        |       |         |         | VL53L1X |
---
Messwerte | Kombi 8 | Kombi 9 | Kombi 10 | Kombi 11 | Kombi 12 | Kombi 13 | Kombi 14
---|:---:|:---:|:---:|:---:|:---:|:---:|:---:
Temperatur     | SHT3x   | SHT3x   | BME280  | BME280 | BME680 | SCD30  | SCD30  |
Luftfeuchte    | SHT3x   | SHT3x   | BME280  | BME280 | BME680 | SCD30  | SCD30  |
Luftdruck      |         |         | BME280  | BME280 | BME680 | BME280 | BME680 |
VOC            |         | IAQCore | IAQCore |        | BME680 |        | BME680 |
CO<sub>2</sub> |         |         |         | SCD30  | SCD30  | SCD30  | SCD30  |
Helligkeit     | OPT300x |         |         |        |        |        |        |
Entfernung     |         |         |         |        |        |        |        |
---

Diese Tabellen werden fortlauend erweitert, sobald neue getestete Kombinationen hinzukommen.

Die in den Tabellen angegebenen Kombinationen sagen nichts daürber aus, ob die Sensoren direkt an das Sensormodul angeschlossen werden können. Stellenweise wurde mit zusätzlicher Hardware getestet, die einen Sensoranschluss ermöglichte.

Die Verwendung von SCD30 als Sensor, vor allem in Kombination mit weiteren Sensoren, wird nur mit eingeschaltetem Watchdog empfohlen, da der Betrieb vom SCD30 manchmal zu unerwünschten "Hängern" des Sensormoduls führt.

#### Temperatursensor

Dieses Auswahlfeld erlaubt die Auswahl des Sensors, der die Temperatur liefern soll. Ein entsprechendes Kommunikationsobjekt (KO) zum lesen bzw. senden erscheint in der Liste der Kommunikationsobjekte.

Wird "Kein Sensor" ausgewählt, wird die Temperatur nicht ermittelt.

Nur wenn ein Sensor für die Temperaturermittlung ausgewählt wurde, können auch im Abschnitt "Standardsensoren->Temperatur" entsprechende Einstellungen zum senden der Temperatur gemacht werden.

#### Luftfeuchtesensor

Dieses Auswahlfeld erlaubt die Auswahl des Sensors, der die Luftfeuchte liefern soll. Ein entsprechendes Kommunikationsobjekt (KO) zum lesen bzw. senden erscheint in der Liste der Kommunikationsobjekte.

Wird "Kein Sensor" ausgewählt, wird die Luftfeuchte nicht ermittelt.

Nur wenn ein Sensor für die Luftfeuchteermittlung ausgewählt wurde, können auch im Abschnitt "Standardsensoren->Luftfeuchte" entsprechende Einstellungen zum senden der Luftfeuchte gemacht werden.

#### Luftdrucksensor

Dieses Auswahlfeld erlaubt die Auswahl des Sensors, der den Luftdruck liefern soll. Ein entsprechendes Kommunikationsobjekt (KO) zum lesen bzw. senden erscheint in der Liste der Kommunikationsobjekte.

Wird "Kein Sensor" ausgewählt, wird der Luftdruck nicht ermittelt.

Nur wenn ein Sensor für die Luftdruckermittlung ausgewählt wurde, können auch im Abschnitt "Standardsensoren->Luftdruck" entsprechende Einstellungen zum senden des Luftdrucks gemacht werden.

#### Voc-Sensor

Dieses Auswahlfeld erlaubt die Auswahl des Sensors, der den Messwert für flüchtige organischen Verbindungen (engl. volatile organic compounds, kurz Voc) liefern soll. Ein entsprechendes Kommunikationsobjekt (KO) zum lesen bzw. senden erscheint in der Liste der Kommunikationsobjekte.

Wird "Kein Sensor" ausgewählt, wird der Voc-Wert nicht ermittelt.

Nur wenn ein Sensor für die Voc-Ermittlung ausgewählt wurde, können auch im Abschnitt "Standardsensoren->Voc" entsprechende Einstellungen zum senden des Voc-Wertes gemacht werden.

#### Co2-Sensor

Dieses Auswahlfeld erlaubt die Auswahl des Sensors, der den Messwert für Kohlendioxid (CO<sub>2</sub>) liefern soll. Ein entsprechendes Kommunikationsobjekt (KO) zum lesen bzw. senden erscheint in der Liste der Kommunikationsobjekte.

Wird "Kein Sensor" ausgewählt, wird der CO<sub>2</sub>-Wert nicht ermittelt.

Nur wenn ein Sensor für die CO<sub>2</sub>-Ermittlung ausgewählt wurde, können auch im Abschnitt "Standardsensoren->CO2" entsprechende Einstellungen zum senden des CO<sub>2</sub>-Wertes gemacht werden.

Bei der Auswahl vom BME680, IAQCore oder SGP30 ist anzumerken, dass diese Sensoren nur ein berechnetes CO<sub>2</sub>-Äquivalent passend zum gemessenen Voc-Wert ausgeben und keinen gemessenen CO<sub>2</sub>-Wert.

#### Helligkeitssensor

Dieses Auswahlfeld erlaubt die Auswahl des Sensors, der die Helligkeit liefern soll. Ein entsprechendes Kommunikationsobjekt (KO) zum lesen bzw. senden erscheint in der Liste der Kommunikationsobjekte.

Wird "Kein Sensor" ausgewählt, wird die Helligkeit nicht ermittelt.

Nur wenn ein Sensor für die Helligkeitsermittlung ausgewählt wurde, können auch im Abschnitt "Standardsensoren->Helligkeit" entsprechende Einstellungen zum senden der Helligkeit gemacht werden.

#### Entfernungssensor

Dieses Auswahlfeld erlaubt die Auswahl des Sensors, der die Entfernung liefern soll. Ein entsprechendes Kommunikationsobjekt (KO) zum lesen bzw. senden erscheint in der Liste der Kommunikationsobjekte.

Wird "Kein Sensor" ausgewählt, wird die Entfernung nicht ermittelt.

Nur wenn ein Sensor für die Entfernungsermittlung ausgewählt wurde, können auch im Abschnitt "Standardsensoren->Entfernung" entsprechende Einstellungen zum senden der Entfernung gemacht werden.

#### 1-Wire aktivieren?

Dieses Eingabefeld kann bei jedem Sensor zusätzlich ausgewählt werden, falls an das Sensormodul auch 1-Wire-Sensoren angeschlossen sind. Eine weitere Seite zur Detaileinstellungen für 1-Wire-Sensoren wird dann verfügbar.

1-Wire-Sensoren erfordern eine fortlaufende Abfrage ihrer Werte und können speziell bei Input-Output-Bausteinen (IO) oder iButtons sehr zeitkritisch sein. Deswegen wird für diese zeitkritischen Abfragen in einem besonders schnellen Modus geschaltet. Bestimmte Sensoren, wie z.B. der IAQCore, der SCD30 und der SCD41, können dieses schnellen Modus nicht unterstützen und behindern die Kommunikation mit dem 1-Wire-Sensor. In solchen Fällen erscheint folgende Meldung:
![Info One-Wire](OneWire.png)
Die Abfragen von 1-Wire-IO und iButtons passieren dann in normaler Geschwindigkeit, was dazu führen kann, dass die Reaktionszeiten auf Eingaben größer 1 Sekunde werden oder gar dass Eingaben verpasst werden. Dies ist kein Fehler des Sensormoduls oder der Firmware, sondern eine Hardwarebeschränkung der verwendeten Bauteile, hier der beteiligten Sensoren.

Anmerkung: Die Einstellungen und die Abfrage von 1-Wire-Sensoren können in der Applikationsbeschreibung WireGateway nachgelesen werden.

#### Akustischer Signalgeber vorhanden (Buzzer)?

Das Sensormodul unterstützt auch die Ausgabe von Pieptönen mittels eines Buzzers. Mit einem Haken in diesem Feld wird angegeben, ob ein Buzzer installiert ist.

#### Optischer Signalgeber vorhanden (RGB-LED)?

Das Sensormodul unterstützt auch die Ausgabe eines Lichtsignals mittels einer RGB-LED. Mit einem Haken in diesem Feld wird angegeben, ob eine RGB-LED installiert ist.

Wird eine RGB-LED und ein CO<sub>2</sub>-Sensor ausgewählt, erscheint folgende Information:
![Info RGB-LED](InfoRgbLed.png)

Diese Information besagt, dass der Betrieb einer RBG-LED und eines CO<sub>2</sub>-Sensors gleichzeitig nicht empfohlen wird, sofern das Sensormodul vom KNX-Bus gespeist werden soll. Da der vom KNX-Bus gelieferte Strom nicht für den Betrieb beider ausreicht, kann es zu Funktionsstörungen kommen, bis hin zu Resets des Sensormoduls und zum Funktionsausfall. Falls das Sensormodul über eine zusätzliche Stromversorgung verfügt (z.B. USB), kann diese Einstellung so belassen werden. Die Applikation wird bei dieser Einstellung nicht weiter eingeschränkt.

#### Nichtflüchtiger Speicher vorhanden (EEPROM)

Ein EEPROM ist ein Speicher, der seine Informationen auch nach einem Stromausfall nicht verliert. Ein solches EEPROM wird von der Firmware genutzt, um Werte von bestimmten Kommunikationsobjekten zu speichern und die Kalibrierungsdaten vom Voc-Sensor.

Ist kein EEPROM auf dem Board vorhanden, können diese Informationen nicht gespeichert werden. Die Applikation wird dann alle Einstellungen, die ein Speichern erlauben, nicht anbieten. In einem solchen Fall erscheinen eine oder zwei der folgenden Informationen:
![Info EEPROM](InfoEeprom.png)

#### Zusatzhardware abschaltbar (z.B. mit dem NCN5130)?

Damit bei einem Stromausfall Daten in einem EEPROM gespeichert werden können, muss nicht nur ein EEPROM vorhanden sein, sondern auch genügend lange Strom zum Speichern vorhanden sein. Angeschlossene Hardware (Sensoren, LED, Buzzer, 1-Wire-Busmaster) verbrauchen aber viel Strom und verhindern somit die Speicherung bei Stromausfall.

Die Firmware unterstützt aber eine Abschaltung der Hardware, falls der Strom ausfällt. Derzeit wird die Abschaltung nur über den NCN5130 (KNX-Bus-Interface) unterstützt, kann aber bei Bedarf entsprechend um weitere Abschaltmöglichkeiten erweitert werden.

Ist keine Möglichkeit zur Abschaltung vorhanden, wird die Speicherung ins EEPROM unterbunden. Die Applikation wird dann alle Einstellungen, die ein Speichern erlauben, nicht anbieten. In einem solchen Fall erscheint die folgende Information:
![Info Stromabschaltung](InfoPower.png)

### Fehlerobjekt anzeigen

Das Fehlerobjekt (KO 11) meldet bitweise Sensorfehler.

* Bit 0: Fehler in der Logik (zyklus, der nicht aufgelöst werden kann)
* Bit 1: Fehler bei der Messung der Temperatur
* Bit 2: Fehler bei der Messung der Luftfeuchte
* Bit 3: Fehler bei der Messung des Luftdrucks
* Bit 4: Fehler bei der Messung der Voc
* Bit 5: Fehler bei der Messung vom CO<sub>2</sub>
* Bit 6: Derzeit nicht belegt
* Bit 7: Fehler im 1-Wire-Busmaster
* Bit 8-15: Fehler des jeweiligen 1-Wire-Sensors

### Diagnoseobjekt anzeigen

Das Diagnoseobjekt (KO 7) ist derzeit für interne Verwendung (für Debug-Zwecke) vorgesehen und sollte in der Praxis nicht mit einer GA belegt werden.

### Watchdog aktivieren

Das Modul unterstützt auch einen Watchdog. Dies ist eine Schaltung, die dafür sorgt, dass ein undefinierter Modulzustand, in dem das Modul nicht mehr auf KNX-Telegramme reagiert, zu einem Modul-Neustart führt.

Für reine Sensoren sind Watchdogs eine gute Lösung, um Hänger zu vermeiden. Ein solcher Neutstart geht schnell und der Sensor liefert wieder seine Werte. Nach dem Neustart werden wie gewohnt alle Messwerte auf den Bus gesendet. Somit kommt ein Messwert außer der Reihe, also z.B. schon nach 2 Minuten und erst dann wieder alle 5 Minuten. Da man normalerweise auch Messwerte bei bestimmten Abweichungen senden lässt, die dann auch außer der Reihe kommen, ist das vertretbar.

Wenn man Logiken nutzt, muss man diese so aufbauen, dass sie stabil gegenüber einem Neustart sind, der ja jederzeit vorkommen kann. Keiner will mitten in der Nacht vom Buzzer geweckt werden. Das Logikmodul erlaubt sehr viele "Startup-Einstellungen", um das möglichst feingranular steuern zu können. Allerdings muss man das auch machen! Wenn man also Logiken macht und den Watchdog benutzt, muss man die Logiken nicht nur auf Funktion, sondern auch auf Neustartverhalten testen. Der komfortabelste Weg hier ist in der ETS "Gerät zurücksetzen". Man kann diesen Befehl aber auch über eine Logik auslösen und z.B. auf eine Taste legen. So kann man in der Testphase jederzeit spontan das Gerät zurücksetzen und sehen, ob es Seiteneffekte bei Neustart gibt.

Der Watchdog kann mit dieser Einstellung aktiviert werden.

Derzeit wird der Watchdog bei der Verwendung vom SCD30 (CO<sub>2</sub>-Sensor) empfohlen, da dessen API zu sporadischen Hängern führt.

## Standardsensoren

Zu den Standardsensoren zählen die Sensoren, die im Kapitel "Hardwareeinstellungen" in der Tabelle aufgelistet sind. Diese Sensoren werden von der Applikation bestens unterstützt. Alle Messwerte von Standardsensoren (Temperatur, Luftfeuchte, Luftdruck, Voc, CO<sub>2</sub>, Helligkeit und Entfernung) erlauben die gleichen Einstellungen, die im Folgenden detailliert für die Temperatur beschrieben werden. Für die weiteren Messwerte werden dann nur noch die Einheiten genannt, in den die Eingaben zu erfolgen sind.

![Standardsensoren](./Standardsensoren.png)

### Temperatur anpassen (interner Messwert)

Mit dieser Einstellung kann der Sensor kalibriert werden. Der eingegebene Wert wird zum gemessenen Wert addiert. Man kann die Temperatur um -10°C absenken und bis zu +10°C erhöhen. Die Werte werden in  0.1°C angegeben, so dass die Eingabe von -100 bis +100 in ganzen Zahlen zu erfolgen hat.

### Externe Messwerte berücksichtigen

Es können bis zu 2 externe Temperatur-Messwerte mit dem intern gemessenen verrechnet werden und als Gesamtmesswert ausgegeben werden. Dabei kann angegeben werden, in welchem Verhätnis die externen und der intere Messwert zueinander stehen. Eine Angabe von 60:30:10 würde bedeuten, dass der intere Messwert zu 60%, der externe Messwert 1 zu 30% und der externe Messwert 2 zu 10% in den Gesamtmesswert einfließt. Es sind aber auch durchaus Angaben wie 12:6:2 möglich (gleichbedeutend zu 60:30:10).

Solange ein externer Messwert noch nicht empfangen wurde, ist sein Anteil (nicht sein Wert) 0, wird also beim Gesamtergebnis nicht berücksichtigt.

In der Auswahlbox wird angegeben, ob 0, 1 oder 2 externe Messwerte berücksichtigt werden sollen.

#### Anteil interner Messwert

Erscheint nur, wenn externe Werte berücksichtigt werden sollen. Gibt den Anteil des internen Messwerts am Gesamtmesswert an.

#### Anteil externer Messwert 1

Erscheint nur, wenn externe Werte berücksichtigt werden sollen. Gibt den Anteil des ersten externen Messwerts am Gesamtmesswert an.

#### Anteil externer Messwert 2

Erscheint nur, wenn 2 externe Werte berücksichtigt werden sollen. Gibt den Anteil des zweiten externen Messwerts am Gesamtmesswert an.

#### Externe Messwerte beim Start lesen

Erscheint nur, wenn externe Werte berücksichtigt werden sollen. Ein "Ja" führt zu einem Lesen der externen Werte beim Neustart des Gerätes. Siehe hier auch Allgeimeine Einstellungen -> Zeit bis das Gerät nach einem Neustart aktiv wird.

### Temperatur zyklisch senden (0 = nicht senden)

Die Temperatur kann in bestimmten Zeitintervallen auf den Bus gesendet werden. Hier wird das Zeitintervall in Sekunden angegeben.

Wird eine 0 angegeben, wird die Temperatur nicht zyklisch gesendet.

### Temperatur bei absoluter Abweichung senden (0 = nicht senden)

Die Temperatur kann auch gesendet werden, wenn der aktuell gemessene Wert um eine festgelegte Temperatur von dem zuletzt gesendeten Wert nach oben oder unten abweicht.

Hier wird die Abweichung in 0.1°C angegeben. Soll also bei einer Abweichung von 0.5°C gesendet werden, muss hier eine 5 angegeben werden.

Wird eine 0 angegeben, wird bei einer absoluten Abweichung nicht gesendet.

### Temperatur bei relativer Abweichung senden (0 = nicht senden)

Die Tempeartur kann auch gesendet werden, wenn der aktuell gemessene Wert um einen bestimmten Prozentsatz von dem zuletzt gesendeten Wert nach oben oder unten abweicht.

Hier wird die Abweichung in % angegeben. Bei einem zuletzt gesendeten Wert von 20°C und einen angegebenen Abweichung von 5% wird erneut gesendet, wenn die gemessene Temperatur 21°C überschreitet oder 19°C unterschreitet (5% von 20°C sind 1°C).

Wird eine 0 angegeben, wird bei einer relativen Abweichung nicht gesendet.

### Temperatur glätten: P =

Falls der Sensor zu emfpindlich ist und man starke Schwankungen im Temperaturmesswert hat, kann man eine Glättungsfunktion nutzen, um starke Messwertschwankungen abzumildern. Die hier verwendete Funktion ist vergleichbar mit einer Durchschnittsberechnung über eine gewisse Anzahl vergangener Messwerte, funktioniert aber im Detail anders.

Es wird folgende Glättungsformel verwendet:

X<sub>neu</sub> = X<sub>alt</sub> + (M - X<sub>alt</sub>) / P

wobei

* X<sub>neu</sub> der geglättete Wert,
* X<sub>alt</sub> der zuvor ermittelte geglättete Wert,
* M der aktuelle Messwert und
* P der einzugebende Glättungsfaktor

ist. Intern wird alle 5 Sekunden ein neuer Messwert ermittelt, der dann mittels dieser Formel geglättet wird. Ein P von 1 führt zu keiner Glättung, jeder Messwert wird übernommen. Ein Wert von 12 führt zu einer Glättung über die Werte einer Minute (5s * 12 = 60s), ein Wert von 120 zu einer Glättung von 10 Minuten und 720 zu einer Glättung von einer Stunde.

Die Glättung wird durchgeführt, bevor eine Sendebedingung für die absolute oder relative Abweichung ermittelt wird.

Der neu ermittelete Wert wird alle 5 Sekunden auf das entsprechende KO geschrieben, ganz egal, ob das KO diesen Wert sendet oder nicht. Somit können vom Sensormdul alle 5 Sekunden aktuelle Sensorwerte gelesen werden, unabhängig von parametriesierten Sendebedingungen.

## Standardsensoren - Temperatur

Die Temperatureinstellungen sind wie unter Standardsensoren beschrieben. Alle Temperaturangaben werden in 0.1°C vorgenommen.

## Standardsensoren - Luftfeuchte

Einstellungen für Luftfeuchte werden wie unter Standardsensoren beschrieben vorgenommen. Alle Angaben für Luftfeuchte werden in % vorgenommen.

## Standardsensoren - Luftdruck

Erscheint nur, wenn der angeschlossene Sensor auch einen Messwert für Luftdruck liefert.

Einstellungen für Luftdruck werden wie unter Standardsensoren beschrieben vorgenommen. Alle Angaben für Luftdruck werden in Millibar (mBar) vorgenommen.

## Standardsensoren - Voc

Erscheint nur, wenn der angeschlossene Sensor auch einen Messwert für Voc liefert.

Einstellungen für Voc werden wie unter Standardsensoren beschrieben vorgenommen. Alle Angaben für Voc sind einheitenlos und werden in ganzen Zahlen vorgenommen.

## Standardsensoren - CO<sub>2</sub>

Erscheint nur, wenn der angeschlossene Sensor auch einen Messwert für CO<sub>2</sub> liefert.

Einstellungen für CO<sub>2</sub> werden wie unter Standardsensoren beschrieben vorgenommen. Alle Angaben für CO<sub>2</sub> werden in Parts-Per-Million (ppm) vorgenommen.

Anmerkung zum BME680: Dieser Sensor liefert nur ein berechnetes CO<sub>2</sub>-Äquivalent passend zum gemessenen Voc-Wert und keinen gemessenen CO<sub>2</sub>-Wert. Dieser berechnete CO<sub>2</sub>-Wert wird über ein zusätzliches KO 20 ausgegeben.

Ist die Sensorkombination BME680+SCD30 installiert, werden beide CO<sub>2</sub>-Werte augegeben, der gemessene und der berechnete.

Anmerkung zum SDC30: Derzeit wird bei diesem Sensor die Nutzung vom Watchdog empfohlen (Siehe Kapitel Watchdog-Unterstützung). Mit diesem Sensor kommt es zu sporadischen "Hängern", deren Ursache noch nicht bekannt ist.

## Standardsensoren - Helligkeit

Erscheint nur, wenn der angeschlossene Sensor auch einen Messwert für Helligkeit liefert.

Einstellungen für Helligkeit werden wie unter Standardsensoren beschrieben vorgenommen. Alle Angaben für Helligkeit werden in Lux vorgenommen.

## Standardsensoren - Entfernung

Erscheint nur, wenn der angeschlossene Sensor auch einen Messwert für Entfernung liefert.

Einstellungen für Entfernung werden wie unter Standardsensoren beschrieben vorgenommen. Alle Angaben für Entfernung werden in Millimetern (mm) vorgenommen.

## Standardsensoren - Zusatzfunktionen

Das Sensormodul kann neben gemessenen Werten auch noch einige berechnete Werte liefern. Dazu zählen der Taupunkt, Behaglichkeit, Luftqualitäsampel und Messgenauigkeit.

### Taupunkt berechnen

![Taupunkt](Taupunkt.png)
Wenn man hier "Ja" auswählt, kann man für den Taupunkt Einstellungen wie unter Standardsensoren beschrieben vornehmen. Alle Angaben für den Taupunkt werden in 0.1°C vorgenommen.

### Behaglichkeitszone ausgeben

![Behaglichkeit](Behaglichkeit.png)
Wenn man hier "Ja" auswählt, wird anhand der Temperatur und Luftfeuchte eine Behaglichkeitszone berechnet und über KO 22 ausgegeben. Die Behaglichkeitszone kann jederzeit gelesen werden, wird aber nur bei Änderungen gesendet.

Falls zyklisches Senden gewünscht wird, kann man dies über die im Sensormodul enthaltenen Logikkanäle realisieren. Beispiele sind in der Applikationsbeschreibung Logik enthalten.

Folgende Behaglichkeitszonen werden berechnet:

* 2 - behaglich
* 1 - noch behaglich
* 0 - unbehaglich

### Luftqualitätsampel ausgeben

![Luftqualitätsampel](Luftqualitätsampel.png)
Dieser Punkt ist nur sichtbar, wenn ein angeschlossener Sensor Messwerte zur Luftqualität liefert, also nur beim BME680 oder SCD30.

Wenn man hier "Ja" auswählt, wird anhand des gemessenen Voc-Werts (beim BME680) oder des gemessenen CO<sub>2</sub>-Werts eine Luftqualitätsampel berechnet und über KO 23 ausgegeben. Die Luftqualitätsampel kann jederzeit gelesen werden, wird aber nur bei Änderungen gesendet.

Falls zyklisches Senden gewünscht wird, kann man dies über die im Sensormodul enthaltenen Logikkanäle realisieren. Beispiele sind in der Applikationsbeschreibung Logik enthalten.

Es gibt 6 Luftqualitätsgrade, entsprechend deutschen Schulnoten:

* 1 - sehr gut
* 2 - gut
* 3 - befriedigend (bei Gelegenheit lüften)
* 4 - ausreichend (lüften empfohlen)
* 5 - mangelhaft (lüften)
* 6 - ungenügend (unbedingt lüften)

### Kalibrierungsfortschritt ausgeben

![Kalibrierung](Kalibrierung.png)
Wird nur sichtbar, wenn als Sensor BME680 ausgewählt ist.

Manche Sensoren benötigen eine Klaibrierung, bevor sie zuverlässige Werte ausgeben können. Dies ist besonders für die Erfassung von Voc-Werten notwendig. Das Sensormodul hat für den BME680 eine Selbstkalibrierung implementiert, die ununterbrochen parallel zur Messwerterfassung läuft und alle 6 Stunden die bisher ermittelten Kalibrierungswerte in einem eigens hierfür eingebauten EEPROM speichert. Somit wird verhindert, dass nach einem Neustart des Gerätes eine erneute Kalibrierung notwendig wird.

Bei einer Erstinbetriebnahme, nach dem Einspielen einen neuen Firmware oder in seltenen Fällen auch im normalen Betrieb ist es notwendig, dass sich der Sensor BME680 neu kalibriert. Dies ist daran zu erkennen, dass der Sensor für den Voc-Wert konstant eine 25 liefert und als Kalibrierungsfortschritt über das KO 24 der Wert 0% geliefert wird.

Nach ca. 5 Minuten werden die ersten Voc-Werte ungleich 25 geliefert mit einem Kalibrierungsfortschritt von 33%. Diese ersten Werte sind noch immer nicht sinnvoll zu verwenden.

Nach einiger Zeit (hängt von der Raumgröße, Luftqualität, Lüftungszustand etc. ab) geht der Kalibrierungsfortschritt auf 66%, gefolgt von einem Wert von 100%. Dies kann insgesamt 6 bis 48 Stunden dauern und entspricht einer normalen Funktion des BME680.

Der Kalibrierungsfortschritt kann mit dieser Einstellung zur Information über KO 24 ausgegeben werden, hat aber auf die Funktion keinerlei Einfluss.

### Kalibrierungsdaten löschen

![Bild Kalibrierungsdaten löschen](KalibrierungLoeschen.png)

Die Applikation erlaubt auch ein explizitel Löschen der Kalibrierungsdaten. Allerdings wäre es sinnlos, hierfür einen Ja-Nein-Parameter eingzführen, da dieser, einmal auf Ja gestellt, nach jedem Neustart des Gerätes die Kalibrierungsdaten löschen würde. Insofern funktioniert dieser Parameter anders!

Eine Änderung des Wertes von 17 auf 23 führt nach den nächsten Upload der Applikation zum Löschen der Kalibrierungsdaten. Diese werden dann automatisch wieder aufgebaut und bleiben auch erhalten, egal wie oft die Applikation danach wieder hochgeladen wird. Die Firmaware des Gerätes verbindet die aktuellen Kalibrierungsdaten mit dem Wert des Parameters, solange der Parameter seinen Wert behält, sind auch die Applikationsdaten gültig.

Wird irgendwann einmal der Wert wieder von 23 auf 17 geändert, werden die Kalibrierungsdaten wieder gelöscht, neu aufgebaut und mit dem Wert 17 verbunden. Will man somit wieder löschen, ändert man wieder auf 23 u.s.w.

Im Allgemeinen sollte es nicht nötig sein, die Kalibrierungsdaten zu löschen. Somit sollte dieser Parameter einfach unverändert bleiben.

## Update der Applikation

Ab dieser Applikationsversion ist das Update einfacher geworden, da es nur noch eine Version mit 80 Kanälen gibt. Die bisherige Notwendigkeit, verschiedene Applikationen anzubieten, war der langen Programmierzeit mit der ETS geschuldet. Diese Applikation und deren Firmware unterstützt nun partielles Programmieren mit einem sehr effektiven Delta-Modus, der nur die geänderten Parameter an das Sensormodul schickt und so die Programmierzeiten unabhängig von der Kanalanzahl kurz hält.

Egal welche Applikation (v2.4 - v2.7) man bisher in Benutzung hatte, man kann sie vollständig auf die v3.1 aktualisieren. Alle Einstellungen bei den Sensoren und den Logiken bleiben erhalten. Hat man bisher 10, 20 oder 40 Logikkanäle genutzt, stehem einen nach dem Update 80 Logikkanäle zur Verfügung. Die Programmierzeiten sind im Schnitt (trotz mehr Kanäle) gesunken. Falls die Schnittstelle zum Bus auch einen Long-Frame-Support bietet, wird das auch vom Sensormodul unterstützt und automatisch genutzt (ohne dass man etwas einstellen muss).

Wird von einer Version kleiner 2.4 ein Update auf 3.1 gemacht, so ist dies technisch möglich. Allerdings muss man dann manuell alle Schritte nachziehen, die auch bei einem Update auf 2.4 notwendig gewesen wären.

Im folgenden werden die Schritte beschrieben, die notwendig sind, um mit der ETS ein Update durchzuführen, ohne dass die Parameter und zugeordneten GA gelöscht werden.

### Neue knxprod in den Produktkatalog importieren

In der Annahme, dass eine 10-Kanal-knxprod (z.B. Sensormodul-v2.4-10.knxprod oder Sensormodul-v2.0-10.knxprod) bereits genutzt wird und das Gerät alle 10 Logikkanäle belegt hat, wollen wir auf die aktuelle Version mit 80 Kanälen wechseln.

Wir gehen in der ETS auf die Katalogansicht und importieren die Datei "Sensormodul-v3.1.knxprod" in die ETS.

Nach erfolgreichem Import hat man ein Produkt mit dem Namen "WP-Sensormodul" mit der Version 3.1. Das bereits genutzte "WP-Sensormodul" mit der Version 2.4 steht auch da.

## Das neue Sensormodul ins eigene Projekt einfügen

Als nächstes wird das Produkt "WP-Sensormodul" ins eigene Projekt eingefügt. Das neue Produkt **muss nicht** parametriert werden, es muss nur im eigenen Projekt existieren.

## Das "alte" Sensormodul aktualisieren

Jetzt wählt man im eigenen Projekt das bereits benutzte und parametrierte "WP-Sensormodul" v2.4. Daraufhin clickt man in den Eigenschaften auf "Information", dann auf "Applikationsprogramm". Auf dieser Seite sieht man dann unten ein Dropdown, in dem die aktuelle Version der Applikation steht "WP-Sensor-Logic V2.4". Wenn man die Dropdown aufklappt, wird man auch ein "WP-Sensor-OneWire-Logic-beta V3.1" finden. **Auf keinen fall diesen Eintrag in der Dropdown auswählen.**

Stattdessen clickt man auf den "Aktualisieren"-Button darunter. Jetzt wird die Applikation von der ETS aktualisiert und alle Parameter bzw. GA-Zuordnungen übernommen.

Anschließend kann man die neuen Funktionen der neuen Version nutzen.

Man muss alle "alten" Sensormodule einzeln aktualisieren, aber nur **einmal** das neue Produkt in die ETS importieren.

**Achtung - Inkompatibilität beim Übergang von Version 1.0 bis 1.3 auf Version 1.4 bis 1.7:**

Beim Update von Version kleiner 1.4 auf eine Version 1.4 bis 1.7 gehen für Logikkanäle die Zuordnungen von Kommunikationsobjekten zu Gruppeenadressen verloren. Diese Gruppenadressen muss man nach dem Update erneut manuell zuordnen. Alle Parameter und auch alle Gruppenadressen für die jeweiligen Sensor-Messwerte bleiben erhalten.

Damit man sich nicht alle zugeordneten Kommunikationsobjekte merken muss, kann man sich in der ETS das Gerät **vor dem Update** kopieren und dabei die Option "Gruppenadressen beibehalten" nutzen. Nach dem Update kann man das alte (kopierte) und das neue (aktualisierte) Gerät in der Ansicht "Kommunikationsobjekte" öffnen und die Gruppenadressen erneut zuordnen.

**Achtung - Inkompatibilität beim Übergang von Version 1.x auf Version 2.x:**

Beim Update von Version 1.x auf eine Version 2.x gehen fast alle Zuordnungen von Kommunikationsobjekten zu Gruppeenadressen verloren (Ausnahmen sind hier nur KO 1-3). Diese Gruppenadressen muss man nach dem Update erneut manuell zuordnen. Fast alle Parameter bleiben erhalten, im fogenden werden die Änderungen bzw. Erweiterungen nochmal aufgeführt. Detailbeschreibungen gibt es in den jeweiligen Kapiteln der Applikationsbeschreibung.

* Früher wurde das Diagnoseobjekt zusammen mit dem Fehlerobjekt eingeschaltet. Inzwischen gibt es einen eigenen Parameter für das Diagnoseobjekt, der speziell eingeschaltet werden muss. In der Applikationsbeschreibung Logik ist das Diagnoseobjekt ausführlich beschrieben.

* Alle weiteren eventuellen Parameteränderungen liegen im Logikmodul und sind im Kapitel **Upgrade der Applikation** in der Applikationsbeschreibung Logik enthalten.

**Achtung - Manueller Schritt notwendig nach dem Update von Version 2.x auf Version 3.1:**

Beim Update bleiben alle Sensoreinstellungen erhalten. Auf der Seite "Allgemeine Parameter" bei der Hardwareauswahl steht im Auswahlfeld "Sensorkombination" noch der Eintrag, der in der Applikation v2.x ausgewählt worden ist. Der Wert in diesem Auswahlfeld muss manuell auf "Einzelauswahl" gestellt werden. Ohne diese Einstellung gehen bei zukünftigen Update der Applikation alle Sensoreinstellungen und zugeordnete Kommunikationsobjekte verloren.

## Hardware

Dieses Kapital beschreibt die von dieser Firmware unterstützte Hardware
(noch nicht ausgearbeitet)

Sensormodul Masifi

SHT3x (neu)

BME280

BME680

SCD30

IAQCore

OPT300x (neu)

VL53L1X (neu)

SGP30 (in Entwicklung)

SCD41 (in Entwicklung)

Buzzer

RGB-LED

NCN5130

DS2484

## Übersicht der vorhandenen Kommunikationsobjekte

Die Liste zeigt nur die Kommunikationsobjekte (KO) der neuesten version 3.x. Es gibt noch weitere KO, die logisch betrachtet zum Logikmodul gehören, diese werden hier nicht aufgelistet, sondern nur auf das Logikmodul verwiesen.

KO | Name | DPT | Bedeutung
:---:|:---|---:|:--
1 | bis 49 | | beschrieben im Logikmodul
50 | Sensorwerte anfordern | 1.016 | Beim Empfang vom Trigger (1) werden alle Sensorwerte auf den Bus gesendet. So kann man mehrere Leseanforderungen sparen.
51 | Sensorfehler | 7.001 | Gibt über eine Bitleiste an, welche Messwerte aufgrund eines aufgetretenen Fehlers nicht erfasst werden können. Falls ein ganzer Sensor ausfällt, werden mehrere Bits gleichzeitig gesetzt
60 | Temperatur | 9.001 | Temperaturmesswert (in °C)
61 | Luftfeuchte | 9.007 | Luftfeuchte (in %)
62 | Luftdruck | 9.006 | Luftdruck (in mBar, nicht Pa!!! mBar = Pa / 100)
63 | VOC | 9.* | Voc-Messwert (einheitenlos)
64 | CO2 | 9.008 | CO2-Messwert (in ppm)
65 | CO2-VOC | 9.008 | Berechneter CO2-Messwert vom VOC (in ppm)
66 | Taupunkt | 9.001 | Berechneter Taupunkt (in °C)
67 | Behaglichkeit | 5.005 | Behaglichkeitswert, errechnet aus Luftfeuchte im Verhältnis zur Temperatur (0-2)
68 | Luftqualitätsampel | 5.005 | Luftgüte entsprechend deutscher Schulnoten (1-6)
69 | Kalibrierungsgrad | 5.001 | Kalibrierungsfortschritt vom BME680 (in %)
70 | Externe Temperatur 1 | 9.001 | Eingang für externe Temperatur 1 (in °C)
71 | Externe Temperatur 2 | 9.001 | Eingang für externe Temperatur 2 (in °C)
72 | Externe Luftfeuchte 1 | 9.007 | Eingang für externe Luftfeuchte 1 (in %)
73 | Externe Luftfeuchte 2 | 9.007 | Eingang für externe Luftfeuchte 2 (in %)
74 | Externer Lufttdruck 1 | 9.006 | Eingang für externen Luftdruck 1 (in mBar)
75 | Externer Lufttdruck 2 | 9.006 | Eingang für externen Luftdruck 2 (in mBar)
76 | Externer VOC 1 | 9.* | Eingang für externen VOC-Wert 1 (einheitenlos)
77 | Externer VOC 2 | 9.* | Eingang für externen VOC-Wert 2 (einheitenlos)
78 | Externe CO2 1 | 9.008 | Eingang für externen CO<sub>2</sub>-Wert 1 (in ppm)
79 | Externe CO2 2 | 9.008 | Eingang für externen CO<sub>2</sub>-Wert 2 (in ppm)
80 | Externer Helligkeit 1 | 9.004 | Eingang für externe Helligkeit 1 (in Lux)
81 | Externer Helligkeit 2 | 9.004 | Eingang für externe Helligkeit 2 (in Lux)
82 | Externe Entfernung 1 | 7.011 | Eingang für externe Entfernung 1 (in mm)
83 | Externe Entfernung 2 | 7.011 | Eingang für externe Entfernung 2 (in mm)
87 | Helligkeit | 9.004 | Helligkeit (in Lux)
88 | Entfernung | 7.011 | Entfernung (in mm)
