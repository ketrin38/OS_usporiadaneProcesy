#          Semestralna praca
#       21. Usporiadane procesy
#    autor : Katarina Pilarcikova, 5ZI03B

#
# Vypise informacie o semestralnej praci, meno a priezvisko autora
#
function vypisInfo() {
  printf "*******************************************************\n"
  printf  "                 Semestralna praca\n\n"
  printf  "                USPORIADANE PROCESY\n\n"
  printf  "             Katarina Pilarcikova, 5ZI03B\n\n"
  printf  "*******************************************************\n\n"
}

#
# Vypise podrobnosti zadania semestralnej prace
#
function vypisZadanie() {
  printf "       ZADANIE SEMESTRALNEJ PRACE - Usporiadane procesy\n\n"
  printf "  POPIS :\nNapiste s pouzitim semaforov programovu strukturu    
piatich procesov, ktorych vykonanie bude usporiadane v case 
podla orientovaneho grafu, ktoreho struktura je zadana v subore.\n
  Struktura je nasledovná:\n
       .->(P2)--->(P3)-.
      /                 \\
  (P1)----->(P4)---------*->(P5)\n\n"

  printf  "Každý proces sa spusti az vtedy,ked sa jeho predchodca 
skonci (pre nazornost proces by mal pouzivat pre svoj vypocet 
vysledky svojho/svojich predchodcu/ov). Navrhnite vhodne cinnosti procesov, 
aby z vystupu bolo zrejme, ze poradie vykonavania bolo dodrzane.\n\n"

  printf  "  VSTUP :\nNazov suboru struktury orientovaneho grafu.\n\n"
  printf  "  VYSTUP :\nVypis vstupu a vysledku spracovania dat po ukonceni kazdeho procesu.\n\n"
  printf  "  TESTOVANIE  :\nVysledok po ukonceni piateho procesu musi zodpovedať ocakavanému vysledku.\n\n"
  
}

#
# Spristupnuje prezeranie dokumentacie
#
function spustiVolbuDokumentacia() {
 printf "Prajete si prezriet DOKUMENTACIU ?    ano/nie\n"
 read volba 
 case "$volba" in
        "ano") vypisDokumentaciu;;
        "nie") printf "Pokracuje sa prelozenim programu ....\n\n";;
        *) echo "Zadali ste nespravne. Opakujte volbu menu"
           spustiVolbuDokumentacia;;
 esac

}

#
# Vypise dokumentaciu k semestralnej praci
#
function vypisDokumentaciu() {
  printf "TU vypisem nadhernu dokumentaciu\n\n"
}

function spustiProgram() {
	make
	.bin/usp_procesy.o
	return 0
}

function zobrazZdrojKod() {
	echo "Zoznam zdrojovych suborov : \n"
	find ./src -type f -perm /a=x 2>/dev/null | xargs ls
	read -p "Zdajte nazov suboru :" nazov
	# najst subor + otvorit a nastrankovat
	find ./src -type f -name $nazov ! -name ".*" 2>/dev/null | xargs cat | more
} 



#----------------------- HLAVNY PROGRAM --------------------------

vypisInfo
vypisZadanie
spustiVolbuDokumentacia
spustiProgram
zobrazZdrojKod
spustiVolbuDokumentacia
  


