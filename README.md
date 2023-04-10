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
