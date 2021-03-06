Pragmatica della luminosita' applicata al volo notturno
**********************************************************

Elementi disponibili
=====================


* lampeggi
* fade (up / down / UD)
* accensioni / spegnimenti sequenziali di segmenti (knight rider)
* RGB: quanto sopra + cambio dei colori


Lampeggi
------------
Dettaglio:

* velocita' tempi HI / LOW
* Variazione tempo HI / tempo LOW
* Lampeggi sequenziali con una pausa LOW piu' lunga

Considerazioni: un lampeggio con rapporto H/L 1/3 dimostra lo stesso consumo di segmento sequenziale a 3 unita'.


Fade
-----

* E' difficile distinguere tra un UP e un DOWN
* Le variazioni della luminosita', sopratutto ai valori bassi, sono poco percettibili. Un movimento sequenziale con velocita' variabile e' piu' evidente


RGB
----

* si puo' usare un solo PWM sul catodo comune per pilotare l'intensita' di tutti i colori


Sequenziali
--------------


* il minimo per un sequenziale e' 3 segmenti
  * questi si potrebbero mettere in serie a 3 canali RGB
* I segmenti posso essere ripetuti
* I segmenti posso essere messi in mirror (es. dal centro all'esterno per le ali)
* si puo' variare il rapporto tra accesi / spenti
* I neopixels sono i migliori per i sequenziali


Considerazioni
================

* Piu' il LED e' acceso (White per RGB) piu' consuma: limitare tempo e luminosita'
* Il binaco freddo e' il LED piu' luminoso
* il contrasto acceso / spento e' il piu' evidente, il fade e' piu' subdolo.
* la visibilita' delle estremita' permette la massima visibilita' della sagoma e delle rotazioni.

Pragmatica
================

* la maggior parte del tempo l'aereo e' visibile da sotto
* se l'aereo e' in orientamento normale e' ok, se in volo rovesciato e' allarme
  * per un acrobatico si potrebbe indicare ogni orientamento con RGB
* se l'aereo e' pari e' ok, se picchia e' allarme, se cabra puo' essere segnalato.


Lessico
----------
* il lampeggio indica allarme
* il fade UD indica riposo  / stazionario
* il sequenziale ha una connotazione di attivita' in corso


Orientamento
============

Serve distinguere principalmente tra sopra e sotto, davanti e dietro. Secondariamente tra destra e sinistra.

Quindi prevalentemente usare il bianco per il sotto e per le estremita'.
Il rosso essendo il secondo colore predominante (purche' si disponga di LED con una luminosita' adeguata) si puo' usare per il sopra. In genere sui multicotteri su usa indicare in bianco il davanti e in rosso il dietro, gli aerei avendo un'unica direzione di movimento ed essendo sempre in movimento non danno problemi a identificarla direzione. Comunque si puo' usare una bussola digitale (vedi esempi) per indicare l'orientamento nei 3 assi dell'aereo.
Verde e blu per i lati.

Per dare un'indicazione della direzione usare segmenti sequenziali: sotto l'aereo per indicare il moto orizzontale, la velocia' di aggiornamento puo' essere proporzionale al throttle. Per i tutt'ala (fusoliera corta) si puo ottenere effetto analogo con due segmenti in mirror dall'interno all'esterno delle ali.

Il roll si puo' indicare con una striscia RGB per la lunghezza delle ali, un colore per il volo piatto, colori differenti per i roll (vedi esempi / ailerons_state_rgb ).

Hardware
=============

Sensori
-----------

* per rilevare l'inclinazione basta una bussola HMC5883L
* per rilevare lo stato della carica delle batterie bastano le entrate A. 5v di un Arduino
* il throttle e' in genere l'unico che non prevede trim, per gli altri bisognerebbe compensare i trim con una autocalibrazione iniziale per fissare lo 0


Hardware
========

* SMD 2835: 40-60mAh, 25lm, ~1e/m
  * consigliato per il rosso, 120' di diffusione, ottimo dissipatore
* SMD3528: 20mA, 6lm, 0.e/m
  * Il bianco e' adeguato, 90' di diffusione, ottimo con alta densita'
* SMD 5050: triplo chip, adatto per RGB, molto calore. 

Links:

* https://www.flexfireleds.com/pages/Comparison-between-3528-LEDs-and-5050-LEDs.html
