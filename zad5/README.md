# Testy do zadania 5

W folderze `tests` znajdują się programy c, które będą przesyłane na minixa, 
a w folderze `ssh-tests` znajdują się właściwe testy,
które mają być wykonywane na hoście.

## Wstępna konfiguracja
  1. Zainstaluj na swoim systemie `sshpass`.
  1. Wpisz w pliku `config.sh` na jakim porcie działa MINIX,
  3. Nadaj uprawnienia wykonywalne wszystkim plikom `*.sh` w folderze `ssh-tests`.

## Przy resetowaniu minixa

Aby dodać nowego użytkownika `foo`, można uruchomić `add_user.sh`.
Można również dopisać sobie dodawanie nowego użytkownika do swojego skryptu patchującego, aby działo się to automatycznie.

## Uruchamianie testów

Testy uruchamia się wywołując `run_tests.sh` z folderu `ssh-tests`. Skrypt kopiuje folder `tests` na MINIXa i kompiluje programy, które są w środku. 
Następnie uruchamia wszystkie testy w postaci `test*.sh`. Można również odpalić każdy test osobno.

Krótkie opisy testów znajdują się w poszczególnych plikach `test*.sh`. Należy mieć mieć na uwadze, że po nieudanych testach, pojawiają się problemy takie jak:

- nieudane odblokowania plików itd., mogą powodować, że kolejne testy przekroczą `NR_EXCLUSIVE = 8`
- powtórne uruchomienie testów dzieje się na tych samych plikach, blokady nie są resetowane (można je zresetować rebootem)

## Dodawanie nowych testów
Na ten moment brakuje testów do:
- wszystkich do `FEXCLUSIVE`,
- `LOCK_NO_OTHERS`,
- blokada operacji write/read,
- pewnie wielu innych, można tutaj sporo potestować.
