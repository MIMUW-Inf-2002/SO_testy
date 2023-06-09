# SO_testy

## Zadanie 1 - Odwracanie permutacji

Aby uruchomić testy umieść plik o nazwie `inverse_permutation.asm` w katalogu
`zad1`. Następnie wejdź do niego i skompiluj testy:

```
./build.sh
```

Aby uruchomić testy należy wykonać polecenie:

```
./main
```

#### Opisy testów

<details><summary>kwasow</summary>
  <ul>
    <li> test1 – źle: pusta permutacja jest niepoprawna</li>
    <li> test2 – źle: w tablicy brakuje 0 i jest liczba 3</li>
    <li> test3 – źle: w tablicy jest liczba ujemna, brakuje jedynki</li>
    <li> test4 – żle: jak test2 </li>
    <li> test5 – źle: w tablicy powtarza się jedynka, brakuje zera</li>
    <li> test6 – źle: w tablicy powtarza się zero, brakuje jedynki</li>
    <li> test7 – źle: zbyt duży parametr n, zero występuje trzy razy (**uwaga**: test powinien być szybki)</li>
    <li> test8 – dobrze: prosta, poprawna permutacja</li>
    <li> test9 – dobrze: duża, poprawna permutacja</li>
  </ul>
  
  **Uwaga!** Testy 7 i 9 są pomijane ze względu na duże zużycie pamięci. Czasami
  udaje się je odpalić, ale zazwyczaj failują. Jeśli masz dostępne ponad 4GB
  ramu, to możesz je odkomentować.
</details>

## Zadanie 2 - Rozproszona maszyna stosowa

Aby uruchomić testy umieść plik o nazwie `core.asm` w katalogu
`zad2`. Następnie wejdź do niego, skompiluj i odpal testy:

```
make
```

Przy tworzeniu testów najlepiej używać funkcji `core_test` zamiast `core`.
Zdefiniowana jest w pliku `core_test.asm` i ma taki sam interfejs jak `core`.

#### Opisy testów

<details><summary>kwasow</summary>
  <ul>
    <li> kwasow_simple – proste testy sprawdzające pojedyncze operacje</li>
    <li> kwasow_advanced (część 1) – dwa testy, które sprawdzają, czy funkcja
      core nie psuje się, jeśli funkcje get_value i put_value zmodyfikują
      wartości w rejestrach</li>
    <li> kwasow_advanced (część 2) – test sprawdza, czy funkcja core nie psuje
      (przywraca) wartości w rejestrach, w których powinna to zrobić</li>
  </ul>
</details>

## Zadanie 3

Jak odpalić basic testy:
<ol>
  <li> Skopiuj folder basic_tests/ na MINIX </li>
  <li> Wejdź do folderu i wywołaj </li>
</ol>
```        
make main
./main
```
UWAGA! Niektóre procesy czekają ileś sekund na to, żeby inne procesy im wysyłały kredyty (możliwe, że trzeba będzie zwiększyć te wartości).

## Zadanie 5

Testy opierają się na komunikacji przez ssh, szczegóły w pliku `README.md` w folderze `zad5`.