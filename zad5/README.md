# Testy do zadania 5

W folderze `tests` znajdują się programy c, które będą przesyłane na minixa, 
a w folderze `ssh-tests` znajdują się właściwe testy,
które mają być wykonywane na hoście.

## Wstępna konfiguracja
  1. Wpisz w pliku `config.sh` na jakim porcie działa MINIX,
  2. Upewnij się, że masz jakikolwiek klucz publiczny do komunikacji przez ssh. 
        Podaj ścieżkę do klucza w pliku `config.sh`
  2. Nadaj uprawnienia wykonywalne wszystkim plikom `.sh` w folderze `ssh-tests`.

## Przy resetowaniu minixa

Aby dodać nowego użytkownika `foo`, można uruchomić `do_config.sh`. Można również skopiować linijkę z poleceniem dodawania do skryptu patchującego lub wpisać ją ręcznie.

## Uruchamianie testów

Testy uruchamia się wywołując `run_tests.sh` z folderu `ssh-tests`. Skrypt kopiuje folder `tests` na MINIXa i kompiluje programy, które są w środku. Następnie uruchamia testy `.sh`.

Krótkie opisy testów znajdują się w poszczególnych plikach `.sh`. Należy mieć mieć na uwadze, że po nieudanych testach, pojawiają się problemy takie jak:

- nieudane odblokowanie plik itd., mogą powodować, że kolejne testy przekroczą `NR_EXCLUSIVE = 8`
- powtórne uruchomienie testów dzieje się na tych samych plikach, blokady nie są resetowane (można je zresetować rebootem)

## Dodawanie nowych testów
Na ten moment brakuje testów do:
- wszystkich do `FEXCLUSIVE`,
- `LOCK_NO_OTHERS`,
- blokada operacji write/read,
- pewnie wielu innych, można tutaj sporo potestować.