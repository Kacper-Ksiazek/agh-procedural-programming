#include "stdio.h"
#include "char_stack.h"
#include "int_stack.h"
#include "stdlib.h"
#include "tools.h"

int main(){
    char *userInput = getMathEquationFromUser();
    CharStackItem **equationAsStack = transformUserInputIntoStack(userInput);

    CharStackItem **operators = createCharStack();
    IntStackItem **numbers = createIntStack();

    char equationElement;
    int t=-1; // Zmienna pomocnicza do zczytywania liczb; defaultowo -1
    int power = 1; // Potegi liczby 10, zeby moc dodac liczby wieksze niz 9 do stosu liczbowego

    // Lecimy po wszystkich znakach w rownaniu od prawej do lewej strony (zgodnie z idea stosu)
    while(isEmpty_char(equationAsStack)== 0){
        equationElement = pop_char(equationAsStack);
        // Jezeli obecny znak jest operatorem matematycznym, sprawdzamy, czy czasem nie bylismy
        // w trakcie czytania jakies liczby
        if(isSimpleMathOperator(equationElement)){
            push_char(operators,equationElement);
            // W momencie, w ktorym t nie rowna sie wartosci domyslnej, dodajemy do stosu liczowego wartosc zmiennej t
            if(t != -1) {
                push_int(numbers, t);
                // I resetujemy wartosci pomocniczne do czytania liczb:
                t = -1;
                power = 1;
            }
            // Gdybysmy nie mieli zadnej liczby przed operatorzem, oznaczaloby to, ze uzytkownik
            // podal 2 operatory jeden za drugim, a tak nie mozna nie nie
            else{
                 // Wywalamy blad
                 printf("Podano 2 operatory jeden za drugim! \nNalezy rowniez pamietac, ze kalkulator mial nie uwzledniac znakow liczb, wiec wszystkie minusy przed liczbami nie wchodza w gre");
                 exit(1);
            }
        }
        // Jezeli nie jest operatorem, to jest liczba
        else {
            if(t == -1) t=0; // Zebysmy nie mieli o 1 za malo
            // Czytamy liczb OD PRAWEJ DO LEWEJ!
            t += charToInt(equationElement) * power;
            power*=10;
        }
    }
    // Po zakonczeniu petli musimy dodac jeszcze ostatnia liczbe
    push_int(numbers,t);
    free(equationAsStack); // Nie potrzebujemy juz tego stosu, wiec go kasujemy

    // Sprawdzamy, czy przypadkiem nie jest taka sytuacja, ze user podal jedynie jedna liczbe
    // bez zadnego operatora
    if(isEmpty_char(operators)){
        printf("Nie moze istniec dzialanie matematyczne bez zadnego operatora!!!\nWynikiem jest, to co podales");
        exit(1);
    }

    // W tym momencie mamy 2 stosy:
    // 1. stos samych operatorow
    // 2. stos samych liczb

    // Zeby rozwiazac rownanie, musimy liczyc OD LEWEJ DO PRAWEJ, tak nakazuje kolejnosc wykonywania dzialan
    // idea stosu to FIRST IN LAST OUT, wiec, zeby liczyc od lewej do prawej musimy:
    // 1. wszystkie ZNAKI rownania (z pominieciem spacji ) wrzucic na stos znakow rownania
    // 2. nastepnie sciagac kolejne elementy tego stosu i segregowac je w zaleznosci od tego,
    //    czy sa one liczba, czy operatorem, na 2 inne stosy

    // Wtedy, gdy bedziemy mogli sciagac elementy ze stosu z kolejnoscia z jaka one zostaly one podane przez uzytkownika

    float result = 0;
    float arg1 = (float) pop_int(numbers); // Rzutujemy na float'a
    float arg2 = (float) pop_int(numbers);
    char operator = pop_char(operators);
    char nextOperator;

    while(isEmpty_int(numbers) == 0 && isEmpty_char(operators) == 0){
        nextOperator = pop_char(operators);
        // Na koncu kazdego scenariusza dzieje sie 2 te same rzeczy:
        // 1. argument drugi- kolejny element sciagniety ze stosu liczbowego
        // 2. operator- kolejny element sciagniety ze stosu znakowego

        // Jezeli mamy operator wyzszego priorytegu, to wykonujemy operacje od razu
        if(operator == '*' || operator == '/'){
            // ale nie dodajemy wyniku operacji do ogolnego wyniku, bo gdybysmy mieli 5*3*3,
            // to wynik z dzialania 5*3 musimy jeszcze przemnozyc przez 3
            //
            // zamiast tego, scalamy 2 argumenty w jeden
            arg1 = executeSimpleMathOperation(operator,arg1,arg2);
        }
        // W przeciwnym wypadku mamy albo dodawanie albo mnozenie
        else {
            // Sprawdzamy czy nastepny operator nie jest z wyzszym priorytetem
            if(nextOperator == '*' || nextOperator == '/'){
                // Jezeli jest to, pierwszy argument obecnej operacji jest dodawany do wyniku ogolnego
                result+= arg1;
                // drugi argument staje sie pierwszym
                // DODATKOWO: Jezeli obecna operacja (ta nie nastepna) to odejmowanie,
                //            to musimy zmienic znak ktoregos z argumentow
                arg1 = operator == '-' ? (-1) * arg2 : arg2;
            }
            // W przeciwnym razie nastepna operacja to dodawanie albo odejmowanie
            else{
                // Wiec podobnie laczymy 2 argumenty w 1
                arg1 = executeSimpleMathOperation(operator,arg1,arg2);
            }
        }

        // Koniec kazdego scenariusza
        arg2= (float) pop_int(numbers);
        operator = nextOperator;
    }
    // Na koncu petli zostajemy z jeszcze 1 operacja do wykonania
    result += executeSimpleMathOperation(operator,arg1,arg2);

    printf("\nWYNIK: %f", result);

    return 0;
}