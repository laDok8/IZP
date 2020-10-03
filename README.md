# Projekt 1 - Práce s textem

Motivační příklad

Snad všichni známe telefonní seznam v chytrých telefonech. Vyhledávání tam většinou funguje i za pomocí numerické klávesnice. Uživatel zadává posloupnosti číslic, ale každým stiskem klávesy myslí jeden ze znaků, které daná čislice reprezentuje (například číslo 5 reprezentuje samotnou 5 či jedno z písmen j, k nebo l). Telefon pak filtruje telefonní seznam podle dané posloupnosti, přičemž se snaží v seznamu najít libovolný kontakt, jehož jméno nebo telefonní číslo obsahuje sekvenci (nepřerušenou nebo rozdělenou) zadaných znaků.
Popis projektu

Cílem projektu je vytvořit program, který by emuloval zjednodušený algoritmus hledání kontaktů zadaných pomocí posloupnosti číslic. Vstupem programu je posloupnost číslic. Výstup programu bude obsahovat seznam kontaktů, které odpovídají zadanému číselnému filtru.
Detailní specifikace

Program implementujte ve zdrojovém souboru proj1.c. Vstupní data budou čtena ze standardního vstupu (stdin), výstup bude tisknut na standardní výstup (stdout).
Překlad a odevzdání zdrojového souboru

Odevzdání: Odevzdejte zdrojový soubor proj1.c prostřednictvím informačního systému.

Překlad: Program překládejte s následujícími argumenty

     $ gcc -std=c99 -Wall -Wextra -Werror proj1.c -o proj1

Syntax spuštění

Program se spouští v následující podobě: (./proj1 značí umístění a název programu):

    ./proj1 CISLO

CISLO zde představuje hledané kritérium, sekvenci číslic 0 až 9, které reprezentují sekvenci hledaných znaků.

Pokud je program spuštěn bez argumentů, program se bude chovat, jako by hledanému kritériu odpovídal každý kontakt se seznamu.
Implementační detaily
Vstupní telefonní seznam

Telefonní seznam jsou ASCII textová data. Každý záznam o kontaktu obsahuje dva řádky: jméno osoby a jeho telefonní číslo. Každý řádek obsahuje maximálně 100 znaků, jinak se jedná o neplatná data. Seznam kontaktů je neuspořádaný. U všech dat nezáleží na velikosti písmen (tzv. case insensitive). Program musí podporovat alespoň 42 kontaktů.
Kritérium nalezení kontaktu

Pro zjednodušení budeme v tomto projektu uvažovat hledání nepřerušené posloupnosti zadaných znaků/číslic v telefonním kontaktu. Nepřerušenou posloupností znaků se myslí takový podřetězec, u kterého se na každé pozici vyskytuje znak, který odpovídá jednomu ze znaků, které reprezentuje číslice na stejné pozici v zadaném řetězci. Každá číslice kromě sebe sama reprezentuje ještě následující znaky: 2 (abc), 3 (def), 4 (ghi), 5 (jkl), 6 (mno), 7 (pqrs), 8 (tuv), 9 (wxyz), 0 (+).
Výstup programu

Výstup programu může být dvojího druhu:

    žádný kontakt nenalezen,
    nalezen jeden a více kontaktů.

Kontakt nenalezen

    Not found

Pokud v telefonním seznamu neexistuje kontakt, u něhož by nějaká část odpovídala hledanému řetězci CISLO, vytiskne program toto hlášení.
Kontakt(y) nalezen(y)

Každý kontakt, který odpovídá hledanému kritériu, program vytiskne na jeden řádek ve formátu JMENO, TELCISLO, kde JMENO je jméno kontaktu z telefonního seznamu a TELCISLO je záznam o telefonním čísle. Program tiskne všechny kontakty, které kritériu odpovídají. Na pořadí řádků nezáleží. Stejně tak nezáleží ani na velikosti písmen.
Omezení v projektu

Je zakázané použít následující funkce:

    volání z rodiny malloc a free - práce s dynamickou pamětí není v tomto projektu zapotřebí,
    volání z rodiny fopen, fclose, fscanf, ... - práce se soubory (dočasnými) není v tomto projektu žádoucí,
    volání qsort, lsearch, bsearch a hsearch - cílem je zamyslet se nad algoritmizací a strukturou dat.

Neočekávané chování

Na chyby za běhu programu reagujte obvyklým způsobem: Na neočekávaná vstupní data, formát vstupních dat nebo chyby při volání funkcí reagujte přerušením programu se stručným a výstižným chybovým hlášením na příslušný výstup a odpovídajícím návratovým kódem. Hlášení budou v kódování ASCII česky nebo anglicky.
Příklady vstupů a výstupů

Pomocný soubor telefonního seznamu:

    $ cat seznam.txt
    Petr Dvorak
    603123456
    Jana Novotna
    777987654
    Bedrich Smetana ml.
    541141120

Příklad hledání (pro demonstraci jsou nalezená písmena ve jméně jako velká):

    $ ./proj1 <seznam.txt
    petr dvorak, 603123456
    jana novotna, 777987654
    bedrich smetana ml., 541141120

    $ ./proj1 12 <seznam.txt
    petr dvorak, 603123456
    bedrich smetana ml., 541141120

    $ ./proj1 686 <seznam.txt
    jana nOVOtna, 777987654

    $ ./proj1 38 <seznam.txt
    pETr DVorak, 603123456
    bedrich smETana ml., 541141120

    $ ./proj1 111 <seznam.txt
    Not found

Hodnocení

Na výsledném hodnocení mají hlavní vliv následující faktory:

    přeložitelnost zdrojového souboru,
    formát zdrojového souboru (členění, zarovnání, komentáře, vhodně zvolené identifikátory),
    dekompozice problému na podproblémy (vhodné funkce, vhodná délka funkcí a parametry funkcí),
    správná volba datových typů, případně tvorba nových typů,
    správná funkcionalita vyhledání kláves a
    ošetření chybových stavů.

Priority funkcionality:

- Vyhledání kontaktů, jejichž telefonní čísla začínají zadaným číslem.
- Vyhledání kontaktů, jejichž jména začínají znaky, které zadané číslo reprezentuje.
- (prémiové) Hledání přerušených posloupností znaků. Program najde i takové kontakty, u který mezi každými dvěma nalezenými znaky může být libovolná posloupnost jiných znaků. Důležité je, že nalezený řetězec (jména nebo telefonního čísla) musí obsahovat všechny znaky, které číslovky reprezentují, a ve stejném pořadí.

# Projekt 2 - Iterační výpočty

Popis projektu

Najděte pracovní bod diody.

Mějme jednoduché sériové zapojení diody a rezistoru. Známe Shockleyovu rovnici a jeho konstanty. Napište funkci, která pro dané vstupní napětí U_0 a odpor rezistoru R najde pracovní napětí diody odpovídající zadané přesnosti. Dále napište program, který na základě těchto vstupních parametrů na výstup vytiskne pracovní bod diody, tedy napětí a proud.
Detailní specifikace
Překlad a odevzdání zdrojového souboru

Odevzdání: Program implementujte ve zdrojovém souboru proj2.c. Zdrojový soubor odevzdejte prostřednictvím informačního systému.

Překlad: Program překládejte s následujícími argumenty:

    $ gcc -std=c99 -Wall -Wextra -Werror proj2.c -lm -o proj2

Spuštění a výstup programu

Vstupní data programu budou zadána jako jeho argumenty:

    $ ./proj2 U0 R EPS
    Up=XXXX V
    Ip=YYYY A

kde:

    U0 je hodnota vstupního napětí ve Voltech,
    R je odpor rezistoru v Ohmech a
    EPS je absolutní chyba/přestnost/odchylka (epsilon),
    XXXX je hodnota napětí pracovního bodu diody a
    YYYY je hodnota proudu pracovního bodu diody.

Formát číselného výstupu XXXX a YYYY odpovídá formátovací značce %g.
Nápověda a vzorce

Voltampérová charakteristika diody v sériovém zapojení s rezistorem:

Proud v rezistoru:

Napětí na rezistoru:

Proud v diodě (Shockleyova rovnice):

Přičemž uvažujme, že závěrný saturační proud a tepelné napětí mají tyto hodnoty:

Protože je obvod uzavřený, platí 1. Kirchhoffův zákon:

1. podúkol

Vyjádřete poslední rovnici pomocí napětí U_p, U_0 a R.
2. podúkol

Implementujte algoritmické schema pro výpočet posloupnosti využívající metodu půlení intervalu. Ukončující podmínka bude odpovídat absolutní požadované přesnosti výsledku (epsilon).
3. podúkol

Napište funkci diode, která pomocí schematu z 2. podúkolu a vzorce z 1. podúkolu hledá hodnotu napětí U_p. Počáteční interval napětí bude od 0 do U_0.

    double diode(double u0, double r, double eps);

Ve funkci je u0 hodnota vstupního napětí, r je odpor rezistoru a eps je absolutní přesnost (maximální požadovaná odchylka). Funkce v návratové hodnotě vrací nalezené napětí U_p.
Příklady výstupů

    $ ./proj2 12 47 1e-2
    Up=0.673828 V
    Ip=0.207937 A

    $ ./proj2 12 47 1e-7
    Up=0.677633 V
    Ip=0.240902 A

    $ ./proj2 24 330 1e-7
    Up=0.64596 V
    Ip=0.0707696 A

    $ ./proj2 24 330 1e-20
    Up=0.64596 V
    Ip=0.0707698 A

    $ ./proj2 inf 5 .5
    Up=inf V
    Ip=inf A

    $ ./proj2 -33 5 .1
    error: invalid arguments

Hodnocení

Na výsledném hodnocení mají hlavní vliv následující faktory:

- implementace algoritmického schematu pro iterační výpočet,
- implementace metody půlení intervalu a výpočet pracovního bodu,
- ošetření neočekávaných stavů.

# Projekt 3 - Průchod bludištěm

Popis projektu

Vytvořte program, který v daném bludišti a jeho vstupu najde průchod ven. Bludiště je uloženo v textovém souboru ve formě obdélníkové matice celých čísel. Cílem programu je výpis souřadnic políček bludiště, přes které vede cesta z vchodu bludiště do jeho východu.
Detailní specifikace
Překlad a odevzdání zdrojového souboru

Odevzdání: Program implementujte ve zdrojovém souboru proj3.c. Zdrojový soubor odevzdejte prostřednictvím informačního systému.

Překlad: Pro vyzkoušení překládejte program s následujícími argumenty

    $ gcc -std=c99 -Wall -Wextra -Werror proj3.c -o proj3

Syntax spuštění

Program se spouští v následujících podobách:

    ./proj3 --help
    ./proj3 --test soubor.txt
    ./proj3 --rpath R C soubor.txt
    ./proj3 --lpath R C soubor.txt

nebo (nepovinné, prémiové)

    ./proj3 --shortest R C soubor.txt

Argumenty programu:

    --help způsobí, že program vytiskne nápovědu používání programu a skončí.
    --test pouze zkontroluje, že soubor daný druhým argumentem programu obsahuje řádnou definici mapy bludiště. V případě, že formát obrázku odpovídá definici (viz níže), vytiskne Valid. V opačném případě (např. ilegálních znaků, chybějících údajů nebo špatných hodnot) program tiskne Invalid.
    --rpath hledá průchod bludištěm na vstupu na řádku R a sloupci C. Průchod hledá pomocí pravidla pravé ruky (pravá ruka vždy na zdi).
    --lpath hledá průchod bludištěm na vstupu na řádku R a sloupci C, ale za pomoci pravidla levé ruky.
    --shortest (prémiové řešení) hledá nejkratší cestu z bludiště při vstupu na řádku R a sloupci C.

Bludiště je aproximováno do mapy trojúhelníkových políček. Mapa bludiště je uložena v textovém souboru. Jméno souboru s mapu je zadáno v argumentu programu. Soubor obsahuje číselné údaje oddělené bílými znaky. První dva číselné údaje reprezentují velikost obrázku v počtu trojúhelníkových políček (výška a šířka mapy - tedy počet řádků a počet sloupců). Následují definice jednotlivých řádků (oddělené bílým znakem), kde každý řádek obsahuje hodnoty jednotlivých políček. 3 bitová hodnota každého políčka definuje, jak vypadá hranice daného políčka. Bit s hodnotou 1 značí, že dané poličko má neprůchozí stěnu na dané hranici, bit s hodnotou 0 značí, že daná hranice je průchozí:

    nejnižší bit popisuje levou šikmou hranici,
    druhý nejnižší bit popisuje pravou šikmou hranici,
    třetí nejnižší bit popisuje buď horní nebo spodní hranici (závisí na typu políčka).

Mapa bludiště je validní, pokud popisuje všechny políčka a všechny sousedící políčka mají stejný typ sdílené hranice.

Příklad: Nechť políčko na souřadnici 2,3 má stěnu na levé a spodní hranici. Potom jeho hodnota v matici bude 1+0+4=5.
Implementační detaily

Cesta bude tištěna jako posloupnost souřadnic políček, přes které cesta vede. Každá souřadnice bude vypsána na jeden řádek ve formátu řádek,sloupec. Čísla řádků a sloupců začínají od 1.
1. podúkol

Mapu implementujte pomocí dvojrozměrného pole s využitím následujícího datového typu:

    typedef struct {
      int rows;
      int cols;
      unsigned char *cells;
    } Map;

kde rows je počet řádků, cols je počet sloupců a cells je ukazatel na pole buňek (celkem rows*cols buněk) - řádky jsou v paměti uloženy za sebou, každý řádek je pole jeho buňek. Buňka je typu unsigned char. Implementujte podpůrné funkce tohoto typu (inicializace mapy, načtení mapy, uvolnění mapy).
2. podúkol

Ve vámi implementovaných algoritmech pro hledání cesty bludištěm neprovádějte dotazy na typ hranice přímým přístupem do paměti (tj. do struktury Map a položky cells), ale striktně pomocí mapovací funkce s následujícím prototypem (její definici implementujte sami):

    bool isborder(Map *map, int r, int c, int border);

Parametr map je platný ukazatel na strukturu mapy, dvojice r a c udává souřadnici (řádek a sloupec) požadovaného políčka a border označuje dotazovanou hranici políčka (hodnoty a jejich významy hranic si definujte své). Funkce vrací true, pokud na zmíněné hranici políčka stojí stěna.
3. podúkol

Implementujte funkci, která vrátí, která hranice se má po vstupu do bludiště následovat (tj. která má být vedena rukou).

    int start_border(Map *map, int r, int c, int leftright);

Parametr map je platný ukazatel na strukturu mapy, r a c je souřadnice vstupního políčka a leftright udává, které pravidlo se při průchodu aplikuje (hodnoty si definujte sami). Funkce vrací hodnotu identifikující danou hranici na vstupním políčku (konkrétní hodnoty si definujte sami). V případě hledání cesty podle pravé ruky bude počáteční hranice:

    pravá při vstupu zleva do bludiště na lichém řádku,
    dolní při vstupu zleva do bludiště na sudém řádku,
    levá při vstupu shora do bludiště,
    pravá při vstupu zespodu do bludiště,
    horní při vstupu zprava do bludiště, pokud má políčko horní hranici a
    levá při vstupu zprava do bludiště, pokud má políčko dolní hranici.

Pokud by nějaké políčko odpovídalo více případům, priorita jednotlivých případů je následující: 1,2,5,6,3,4.

Přirozeně a obdobně pro hledání pomocí pravidla levé ruky (u daných případů jen adekvátně změňte pravá, levá, horní, dolní).
Příklady vstupů a výstupů

Nechť je mapa vyobrazená v předcházejícím obrázku uložena v souboru bludiste.txt s následujícím obsahem (plné hrany na obrázku značí stěnu, čárkované volný prostor):


    6 7
    1 4 4 2 5 0 6
    1 4 4 0 4 0 2
    1 0 4 0 4 6 1
    1 2 7 1 0 4 2
    3 1 4 2 3 1 2
    4 2 5 0 4 2 5
Příklad nalezení cesty pravidlem levé ruky (na obrázku zobrazená červenou křivkou):

    $ ./proj3 --lpath 6 1 bludiste.txt
    6,1
    6,2
    5,2
    5,3
    5,4
    6,4
    6,5
    6,6
    5,6
    5,7
    4,7
    4,6
    4,5
    5,5
    4,5
    4,4
    3,4
    3,3
    3,2
    4,2
    4,1
    5,1
    4,1
    4,2
    3,2
    3,1
    2,1
    2,2
    2,3
    2,4
    1,4
    1,3
    1,2
    1,1

    $ ./proj3 --lpath 6 7 bludiste.txt
    6,7

Příklad nalezení cesty pravidlem pravé ruky (na obrázku zobrazená modrou křivkou):

    $ ./proj3 --rpath 6 1 bludiste.txt
    6,1
    6,2
    5,2
    5,3
    5,4
    6,4
    6,3
    6,4
    6,5
    6,6
    5,6
    5,7
    4,7
    4,6
    4,5
    4,4
    3,4
    3,5
    3,6
    3,5
    3,4
    3,3
    3,2
    3,1
    2,1
    2,2
    2,3
    2,4
    2,5
    2,6
    2,7
    3,7

    $ ./proj3 --rpath 6 7 bludiste.txt
    6,7

Hodnocení

Na výsledném hodnocení mají hlavní vliv následující faktory:

- přesné dodržení implementačních detailů,
- implementace požadovaných operací nad datovým typem Map,
- implementace jednotlivých funkcí,
- správný algoritmus hledání požadované cesty,
- správné řešení neočekávaných stavů.

V případě implementace hledání nejkratší cesty z bludiště je možné získat 1-4 prémiové body. Získání prémiových bodů je podmíněno správnou implementací algoritmů hledání pomocí pravidla pravé a levé ruky a dodržením implementačních detailů. 
