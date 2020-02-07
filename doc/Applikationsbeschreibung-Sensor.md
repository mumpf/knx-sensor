# Applikationsbeschreibung Sensor

Die Applikation Sensor ist im File Sensormodul.knxprod enthalten und erlaubt die Parametrisierung des Sensormoduls mittels der ETS.

Sie ist in die Bereiche

* Allgemeine Parameter
* Standardsensoren
* Logikdokumentation
* Logikkanäle

gegliedert.

Die letzeren beiden sind in der Applikationsbeschreibung Logik beschrieben.

## Allgemeine Parameter

![Allgemeine Parameter](./AllgemeineParameter.png)
Hier werden Einstellungen getroffen, die die genere
lle Arbeitsweise des Sensormoduls bestimmen. 

### Zeit bis das Gerät nach einem Neustart aktiv wird

Nach einem Neustart des Geräts, sei es durch Busspannungsausfall, Reset über den Bus oder auch durch ein Drücken der Reset-Taste, kann man hier festlegen, wie viele Sekunden vergehen sollen, bis das Gerät seine Funktion aufnimmt.

Da das Gerät prinzipiell (sofern parametriert) auch Lesetelegramme auf den Bus senden kann, kann mit dieser Einstellung verhindert werden, dass bei einem Busneustart von vielen Geräten viele Lesetelegramme auf einmal gesendet werden und so der Bus überlastet wird.

### In Betrieb senden alle ...

Das Gerät kann einen Status "Ich bin noch in Betrieb" über das KO 1 senden. Hier wird das Sendeintervall in Sekunden eingestellt.

### Sensor

Mit dem Auswahlfeld Sensor wird der angeschlossene Sensor ausgewählt. In den folgenden Anzeigefeldern wird angezeigt, welche Messungen von dem Sensor vorgenommen werden. Um alle unterstützten Messungen vornehmen zu können, muss man Sensorkombinationen (CO2 + BME280 oder CO2 + BME680) benutzen.

Die Auswahl von 1-Wire-Sensoren ist auch möglich, wird aber derzeit weder von der Applikation noch von der Firmware im Sensormodul unterstützt (zukünftige Erweiterung).

#### Temperatur

Dieses Anzeigefeld zeigt einen Haken, wenn der ausgewählte Sensor eine Temperaturmessung unterstützt.

#### Luftfeuchte

Dieses Anzeigefeld zeigt einen Haken, wenn der ausgewählte Sensor eine Messung der Luftfeuchtigkeit unterstützt.

#### Luftdruck

Dieses Anzeigefeld zeigt einen Haken, wenn der ausgewählte Sensor eine Messung des Luftdrucks unterstützt.

#### Voc

Dieses Anzeigefeld zeigt einen Haken, wenn der ausgewählte Sensor eine Messung von flüchtigen organischen Verbindungen (engl. volatile organic compounds, kurz Voc) unterstützt.

#### CO2

Dieses Anzeigefeld zeigt einen Haken, wenn der ausgewählte Sensor eine Messung von Kohlendioxid (CO<sub>2</sub>) unterstützt.

Bei der Auswahl vom BME680 wird auch CO2 angezeigt. Hier ist anzumerken, dass der BME680 nur ein berechnetes CO<sub>2</sub>-Äquivalent passend zum gemessenen Voc-Wert ausgibt und keinen gemessenen CO<sub>2</sub>-Wert.

#### 1-Wire

Dieses Eingabefeld kann bei jedem Sensor zusätzlich ausgewählt werden, falls an das Sensormodul auch 1-Wire-Sensoren angeschlossen sind. Eine weitere Seite zur Detaileinstellungen für 1-Wire-Sensoren wird dann verfügbar.

Anmerkung: Die Einstellungen und die Abfrage von 1-Wire-Sensoren sind derzeit noch nicht unterstützt.

### Logikfunktionen freischalten

Mit einem "Ja" können hier die vom Sensormodul unterstützten Logikkanäle zur Benutzung freigeschaltet werden. Es werden weitere Konfigurationsseiten für die einzelnen Logikkanäle freigeschatet.

Die Anzahl der verfügbaren Logikkanäle hängt von der verwendeten ETS-Applikation ab. Es stehen ETS-Applikationen mit 10, 20, 40 und 60 Logikkanälen zur Verfügung. Für die Sensorapplikation macht die Anzahl der Logikkanäle keinen funktionalen Unterschied. Allerdings beeinflußt die Anzahl der Logikkanäle wesentlich die Programmierzeit mit der ETS. Ein Sensormodul mit 10 Logikkanälen braucht ca. 30 Sekunden für die Programmierung, mit 60 Logikkanälen ca. 3 Minuten. Die Programmierzeit hängt immer von der Anzahl der verfügbaren Logikkanälen ab, nicht von der Anzahl der genutzen.

Diese Einstellung dient nur der Übersichtlichkeit der ETS-Applikation und hat keine funktionalen Auswrikungen.

### Fehler- und Diagnoseobjekt anzeigen

Das Fehlerobjekt (KO 2) meldet bitweise Sensorfehler. 

* Bit 0: Fehler in der Logik (zyklus, der nicht aufgelöst werden kann)
* Bit 1: Fehler bei der Messung der Temperatur
* Bit 2: Fehler bei der Messung der Luftfeuchte
* Bit 3: Fehler bei der Messung des Luftdrucks
* Bit 4: Fehler bei der Messung der Voc
* Bit 5: Fehler bei der Messung vom CO<sub>2</sub>
* Bit 6: Derzeit nicht belegt
* Bit 7: Fehler im 1-Wire-Busmaster
* Bit 8-15: Fehler des jeweiligen 1-Wire-Sensors

Das Diagnoseobjekt (KO 3) ist derzeit für interne Verwendung (für Debug-Zwecke) vorgesehen und sollte in der Praxis nicht mit einer GA belegt werden.

## Standardsensoren

Zu den Standardsensoren zählen die Sensoren, die unter den Allgemeinen Einstellungen im Feld "Sensor" ausgewählt werden können. Diese Sensoren werden von der Applikation bestens unterstützt. Alle Messwerte vom Standardsensoren (Temperatur, Luftfeuchte, Luftdruck, Voc und CO<sub>2</sub>) erlauben die gleichen Einstellungen, die im Folgenden detailliert für die Temperatur beschrieben werden. Für die weiteren Messwerte werden dann nur noch die Einheiten genannt, in den die Eingaben zu erfolgen sind.

![Standardsensoren](./Standardsensoren.png)

### Temperatur anpassen (interner Messwert)

Mit dieser Einstellung kann der Sensor kalibriert werden. Der eingegebene Wert wird zum gemessenen Wert addiert. Man kann die Temperatur um -5°C absenken und bis zu +5°C erhöhen. Die Werte werden in  1/10°C angegeben, so dass die Eingabe von -50 bis +50 in ganzen Zahlen zu erfolgen hat.

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

Hier wird die Abweichung in 1/10°C angegeben. Soll also bei einer Abweichung von 0.5°C gesendet werden, muss hier eine 5 angegeben werden.

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

Die Temperatureinstellungen sind wie unter Standardsensoren beschrieben. Alle Temperaturangaben werden in 1/10°C vorgenommen.

## Standardsensoren - Luftfeuchte

Einstellungen für Luftfeuchte werden wie unter Standardsensoren beschrieben vorgenommen. Alle Angaben für Luftfeuchte werden in % vorgenommen.

## Standardsensoren - Luftdruck

Erscheint nur, wenn der angeschlossene Sensor auch einen Messwert für Luftdruck liefert.

Einstellungen für Luftdruck werden wie unter Standardsensoren beschrieben vorgenommen. Alle Angaben für Luftdruck werden in Pascal (Pa) vorgenommen.

## Standardsensoren - Voc

Erscheint nur, wenn der angeschlossene Sensor auch einen Messwert für Voc liefert.

Einstellungen für Voc werden wie unter Standardsensoren beschrieben vorgenommen. Alle Angaben für Voc sind einheitenlos und werden in ganzen Zahlen vorgenommen.

## Standardsensoren - CO<sub>2</sub>

Erscheint nur, wenn der angeschlossene Sensor auch einen Messwert für CO<sub>2</sub> liefert.

Einstellungen für CO<sub>2</sub> werden wie unter Standardsensoren beschrieben vorgenommen. Alle Angaben für CO<sub>2</sub> werden in Parts-Per-Million (ppm) vorgenommen.

Anmerkung zum BME680: Dieser Sensor liefert nur ein berechnetes CO<sub>2</sub>-Äquivalent passend zum gemessenen Voc-Wert und keinen gemessenen CO<sub>2</sub>-Wert.

## Standardsensoren - Zusatzfunktionen

Das Sensormodul kann neben gemessenen Werten auch noch einige berechnete Werte liefern. Dazu zählen der Taupunkt, Behaglichkeit, Luftqualitäsampel und Messgenauigkeit.

### Taupunkt berechnen

![Taupunkt](Taupunkt.png)
Wenn man hier "Ja" auswählt, kann man für den Taupunkt Einstellungen wie unter Standardsensoren beschrieben vornehmen. Alle Angaben für den Taupunkt werden in 1/10°C vorgenommen.

### Behaglichkeitszone ausgeben

![Behaglichkeit](Behaglichkeit.png)
Wenn man hier "Ja" auswählt, wird anhand der Temperatur und Luftfeuchte eine Behaglichkeitszone berechnet und über KO 12 ausgegeben. Die Behaglichkeitszone kann jederzeit gelesen werden, wird aber nur bei Änderungen gesendet.

Falls zyklisches Senden gewünscht wird, kann man dies über die im Sensormodul enthaltenen Logikkanäle realisieren. Beispiele sind in der Applikationsbeschreibung Logik enthalten.

Folgende Behaglichkeitszonen werden berechnet:

* 2 - behaglich
* 1 - noch behaglich
* 0 - unbehaglich

### Luftqualitätsampel ausgeben

![Luftqualitätsampel](Luftqualitätsampel.png)
Dieser Punkt ist nur sichtbar, wenn ein angeschlossener Sensor Messwerte zur Luftqualität liefert, also nur beim BME680 oder CO<sub>2</sub>.

Wenn man hier "Ja" auswählt, wird anhand des gemessenen Voc-Werts (beim BME680) oder des gemessenen CO<sub>2</sub>-Werts eine Luftqualitätsampel berechnet und über KO 13 ausgegeben. Die Luftqualitätsampel kann jederzeit gelesen werden, wird aber nur bei Änderungen gesendet.

Falls zyklisches Senden gewünscht wird, kann man dies über die im Sensormodul enthaltenen Logikkanäle realisieren. Beispiele sind in der Applikationsbeschreibung Logik enthalten.

Es gibt 6 Luftqualitätsgrade, entsprechend deutschen Schulnoten:

* 1 - sehr gut
* 2 - gut
* 3 - befriedigend (bei Gelegenheit lüften)
* 4 - ausreichend (lüften empfohlen)
* 5 - ungenügend (lüften)
* 6 - mangelhaft (unbedingt lüften)

### Kalibrierungsfortschritt ausgeben

![Kalibrierung](Kalibrierung.png)
Wird nur sichtbar, wenn als Sensor BME680 ausgewählt ist.

Manche Sensoren benötigen eine Klaibrierung, bevor sie zuverlässige Werte ausgeben können. Dies ist besonders für die Erfassung von Voc-Werten notwendig. Das Sensormodul hat für den BME680 eine Selbstkalibrierung implementiert, die ununterbrochen parallel zur Messwerterfassung läuft und alle 6 Stunden die bisher ermittelten Kalibrierungswerte in einem eigens hierfür eingebauten EEPROM speichert. Somit wird verhindert, dass nach einem Neustart des Gerätes eine erneute Kalibrierung notwendig wird.

Bei einer Erstinbetriebnahme, nach dem Einspielen einen neuen Firmware oder in seltenen Fällen auch im normalen Betrieb ist es notwendig, dass sich der Sensor BME680 neu kalibriert. Dies ist daran zu erkennen, dass der Sensor für den Voc-Wert konstant eine 25 liefert und als Kalibrierungsfortschritt über das KO 14 der Wert 0% geliefert wird.

Nach ca. 5 Minuten werden die ersten Voc-Werte ungleich 25 geliefert mit einem Kalibrierungsfortschritt von 33%. Diese ersten Werte sind noch immer nicht sinnvoll zu verwenden.

Nach einiger Zeit (hängt von der Raumgröße, Luftqualität, Lüftungszustand etc. ab) geht der Kalibrierungsfortschritt auf 66%, gefolgt von einem Wert von 100%. Dies kann insgesamt 6 bis 48 Stunden dauern und entspricht einer normalen Funktion des BME680.

Der Kalibrierungsfortschritt kann mit dieser Einstellung zur Information über KO 14 ausgegeben werden, hat aber auf die Funktion keinerlei Einfluss.

## Hardware

Buzzer
RGB-LED

## Übersicht der vorhandenen Kommunikationsobjekte

KO | Name | DPT | Bedeutung
:---:|:---|---:|:--
1 | in Betrieb | 1.002 | Meldet zyklisch auf den Bus, dass das Gerät noch funktioniert
2 | Sensorfehler | 7.001 | Gibt über eine Bitleiste an, welche Messwerte aufgrund eines aufgetretenen Fehlers nicht erfasst werden können. Falls ein ganzer Sensor ausfällt, werden mehrere Bits gleichzeitig gesetzt
3 | Diagnose | 16.001 | Nur für internen Gebrauch (Debug)
5 | Temperatur | 9.001 | Temperaturmesswert
6 | Luftfeuchte | 9.007 | Luftfeuchte
7 | Luftdruck | 9.006 | Luftdruck
8 | VOC | 9.* | Voc-Messwert
9 | CO2 | 9.008 | CO2-Messwert
11 | Taupunkt | 9.001 | Berechneter Taupunkt
12 | Behaglichkeit | 5.005 | Behaglichkeitswert, errechnet aus Luftfeuchte im Verhältnis zur Temperatur
13 | Luftqualitätsampel | 5.005 | Luftgüte entsprechend deutscher Schulnoten (1-6)
14 | Kalibrierungsgrad | 5.001 | Kalibrierungsfortschritt vom BME680 in %
15 | Sensorwerte anfordern | 1.016 | Beim Empfang vom Trigger (1) werden alle Sensorwerte auf den Bus gesendet. So kann man mehrere Leseanforderungen sparen.


