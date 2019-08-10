# hu-ds2019
C-Projekt an der HU, Fach Digitale Systeme 2019; Dictonary / Hash in C

Digitale Systeme 2019 C-Programmierpraktikum

1 Aufgabenstellung:
ein Übersetzungsprogramm schreiben, welches einen gegebenen Text mit Hilfe eines ebenfalls gegebenen Wörterbuchs Wort für Wort in eine andere Sprache überträgt.

2 Ein- und Ausgabedaten:
- ohne GUI mit einem einzelnen Aufruf ./loesung demo.wb von der Kommandozeile aus nutzbar sein. Das erste und einzige Kommandozeilenargument soll den Pfad zur Datei mit dem Wörterbuch enthalten.
- der zu übersetzende Text soll von der Standardeingabe (stdin) gelesen werden. Jede dieser Eingaben ist in ASCII kodiert
- das Wörterbuch enthält pro Zeile ein Wort sowie seine Übersetzung, getrennt durch einen Doppelpunkt
- die Standardeingabe enthält eine beliebige Sequenz druckbarer ASCII-Zeichen sowie Linefeeds
- das Programm soll jedes Wort in der Standardeingabe durch seine im Wörterbuch deﬁnierte Übersetzung ersetzen. Wörter, die nicht im Wörterbuch deﬁniert werden, sollen an der jeweiligen Stelle im Text in spitze Klammern gesetzt werden. Ein Wort sei hierbei eine Sequenz von Groß- und Kleinbuchstaben, getrennt durch beliebige andere Zeichen
- das Resultat soll Ihr Programm auf die Standardausgabe (stdout) schreiben. Groß- und Kleinschreibung sind in beiden Sprachen identisch
- das Wörterbuch ist ausschließlich in Kleinbuchstaben deﬁniert
- der erste Buchstabe eines übersetzten Wortes sei genau dann ein Großbuchstabe, wenn der erste Buchstabe im Ursprungstext groß ist; alle übrigen Buchstaben des übersetzten Wortes sind immer klein



