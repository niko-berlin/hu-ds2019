# hu-ds2019
C-Projekt an der HU, Fach Digitale Systeme 2019; Dictonary / Hash in C

Digitale Systeme 2019 C-Programmierpraktikum

1 Aufgabenstellung

Leona ist Linguistik-Studentin und Conlangerin. In ihrer Bachelorarbeit beschäftigt sie sich mit einer Menge konstruierter ﬁktionaler 
Sprachen, die eine zum Deutschen äquivalente Grammatik besitzen, also mit Sprachen, deren Texte sich aus dem Deutschen durch eine 
Wort-für-WortÜbersetzung generieren lassen. Insbesondere möchte Leona für jede der von ihr betrachteten Sprachen eine Übersetzung 
der Einleitung ihrer Bachelorarbeit mit abdrucken. Ihre Mission ist es, Leona zu helfen und ein Übersetzungsprogramm zu schreiben, 
welches einen gegebenen Text in deutscher Sprache mit Hilfe eines ebenfalls gegebenen Wörterbuchs Wort für Wort in eine andere Sprache 
überträgt.

2 Ein- und Ausgabedaten
Ihr Programm soll ohne jegliche Interaktion und ohne Benutzeroberﬂäche mit einem einzelnen Aufruf ./loesung demo.wb von der Kommandozeile 
aus nutzbar sein. Das erste und einzige Kommandozeilenargument soll den Pfad zur Datei mit dem Wörterbuch enthalten. Der zu übersetzende 
Text soll von der Standardeingabe (stdin) gelesen werden. Jede dieser Eingaben ist in ASCII kodiert, Umlaute sowie „ß“ kommen also nicht 
vor. Das Wörterbuch enthält pro Zeile ein Wort sowie seine Übersetzung, getrennt durch einen Doppelpunkt. Die Standardeingabe enthält 
eine beliebige Sequenz druckbarer ASCII-Zeichen sowie Linefeeds. Ihr Programm soll jedes Wort in der Standardeingabe durch seine im 
Wörterbuch deﬁnierte Übersetzung ersetzen. Wörter, die nicht im Wörterbuch deﬁniert werden, sollen an der jeweiligen Stelle im Text 
in spitze Klammern gesetzt werden. Ein Wort sei hierbei eine Sequenz von Groß- und Kleinbuchstaben, getrennt durch beliebige andere 
Zeichen. Das Resultat soll Ihr Programm auf die Standardausgabe (stdout) schreiben. Der Einfachheit halber sei Groß- und Kleinschreibung 
in beiden Sprachen identisch und das Wörterbuch ausschließlich in Kleinbuchstaben deﬁniert. Der erste Buchstabe eines übersetzten Wortes 
sei genau dann ein Großbuchstabe, wenn der erste Buchstabe im Ursprungstext groß ist; alle übrigen Buchstaben des übersetzten Wortes sind 
immer klein.
