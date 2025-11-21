#!/bin/bash

# Pliki źródłowe
BRUTE="brutal.cpp"
WZORC="wzorcowe.cpp"
GEN="gen_input.cpp"

# Pliki wykonywalne
BRUTE_EXE="brute"
WZORC_EXE="wzorc"
GEN_EXE="gen"

# Kompilacja
g++ -O3 -static $BRUTE -std=c++23 -o $BRUTE_EXE || { echo "Błąd kompilacji brutalnego"; exit 1; }
g++ -O3 -static $WZORC -std=c++23 -o $WZORC_EXE || { echo "Błąd kompilacji wzorcowego"; exit 1; }
g++ -O3 -static $GEN -std=c++23 -o $GEN_EXE || { echo "Błąd kompilacji generatora"; exit 1; }

# Liczba testów
TESTS=100

echo "Start testowania"

for ((i=1; i<=TESTS; i++)); do
    echo "Test $i"

    # Generowanie wejścia
    ./$GEN_EXE > input.txt

    # Uruchomienie programów
    ./$BRUTE_EXE < input.txt > output_brute.txt
    ./$WZORC_EXE < input.txt > output_wzorc.txt

    # Porównanie z ignorowaniem niektórych whitespace
    if ! diff -bew output_brute.txt output_wzorc.txt >/dev/null; then
        echo "Błąd na teście $i"
        echo ""
        echo "Wejście:"
        cat input.txt
        echo ""
        echo "Output brutal:"
        cat output_brute.txt
        echo ""
        echo "Output wzorcowe:"
        cat output_wzorc.txt
        echo ""
        exit 1
    fi
done

echo "Wszystkie testy poprawne"
