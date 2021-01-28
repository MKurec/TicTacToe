#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>

// Funkcja czyszcąca planszę
void clearBoard(char board[3][3])
{
    int row, col;
    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            board[row][col] = ' ';

}

/// Funkcja rysująca planszę na ekranie 
void printBoard(char board[3][3])
{
    system("cls"); // czyszczenie ekranu ekran
    printf("********************************************************************************\n");
    printf("-============================== KOLKO I KRZYZYK ================================\n");
    printf("********************************************************************************\n");
    printf("    [ ][1][2][3]\n");
    printf("    [1][%c][%c][%c]\n", board[0][0], board[0][1], board[0][2]);
    printf("    [2][%c][%c][%c]\n", board[1][0], board[1][1], board[1][2]);
    printf("    [3][%c][%c][%c]\n", board[2][0], board[2][1], board[2][2]);
}

int isBoardFull(char board[3][3])
{
    int row, col;
    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            if (board[row][col] == ' ')
                return 0;
    return 1;

}

//Funkcja playerMove i secondPlayerMove:
//wyswietla plansze,
//wczytuje ruch gracza,
//jeśli wczytane są dane spoza zakresu lub pole jest zajęte prosi o wzkazanie poprawnego pola.
void playerMove(char board[3][3])
{
    unsigned int row , col;
    printBoard(board);
    printf("Podaj wiersz i kolumne w ktorej chcesz wstawic krzyzyk\n");
    scanf_s("%u %u", &row, &col);
    --row;
    --col;
    while ((row > 2) || (col > 2) || (board[row][col] != ' '))
    {
        printf("Podano niepoprawny wiersz lub kolumne\n");
        printf("Podaj wiersz i kolumne w ktorej chcesz wstawic krzyzyk\n");
        scanf_s("%u %u", &row, &col);
        --row;
        --col;

    }
    board[row][col] = 'x';
}
void secondPlayerMove(char board[3][3])
{
    unsigned int row, col;
    printBoard(board);
    printf("Podaj wiersz i kolumne w ktorej chcesz wstawic kolko\n");
    scanf_s("%u %u", &row, &col);
    --row;
    --col;
    while ((row > 2) || (col > 2) || (board[row][col] != ' '))
    {
        printf("Podano niepoprawny wiersz lub kolumne\n");
        printf("Podaj wiersz i kolumne w ktorej chcesz wstawic kolko\n");
        scanf_s("%u %u", &row, &col);
        --row;
        --col;

    }
    board[row][col] = 'o';
}
//Funkcja checkBoard sprawdza czy:
//na planszy nie ma trzech takich samych znaków lezacych w jednej linii (zwraca zwycięski znak),
//plansza jest pełna (remis zwraca 1),
//w przeciwnych wypadkach zwraca 0
char checkBoard(char board[3][3])
{
    int line;
    for (line = 0; line < 3; line++)
    {
        if ((board[line][0] != ' ')
            && (board[line][0] == board[line][1])
            && (board[line][0] == board[line][2]))
            return board[line][0];
        if ((board[0][line] != ' ')
            && (board[0][line] == board[1][line])
            && (board[0][line] == board[2][line]))
            return board[0][line];

    } 

    if ((board[0][0] != ' ')
        && (board[0][0] == board[1][1])
        && (board[0][0] == board[2][2]))
        return board[0][0];

    if ((board[2][0] != ' ')
        && (board[2][0] == board[1][1])
        && (board[2][0] == board[0][2]))
        return board[2][0];

    if (isBoardFull(board) == 1)
        return 1;
    return 0;

} 

//Funkcja fill gap wstawia znak 'c' w puste miejsce gdy w danej lini znajdują się dwa takie same znaki 
int fillGap(char board[3][3], char c)
{
    int row, col;
    for (row = 0; row < 3; row++)
    {
        for (col = 0; col < 3; col++)
        {
            //Sprawdza czy w danym rzędzie nie ma dwóch takich samych zanków, jeśli tak wstawia znak
            if ((board[row][col] == c) && (board[row][(col + 1) % 3] == c)
                && (board[row][(col + 2) % 3] == ' '))
            {
                board[row][(col + 2) % 3] = 'o';
                return 1;
            } 
            //Sprawdza czy w danej kolumnie nie ma dwóch takich samych zanków, jeśli tak wstawia znak
            if ((board[col][row] == c) && (board[(col + 1) % 3][row] == c)
                && (board[(col + 2) % 3][row] == ' '))
            {
                board[(col + 2) % 3][row] = 'o';
                return 1;
            } 
        }
        //Sprawdza czy po przekątnej nie ma dwóch takich samych zanków, jeśli tak wstawia znak
        if ((board[row][2 - row] == c)
            && (board[(row + 1) % 3][2 - (row + 1) % 3] == c)
            && (board[(row + 2) % 3][2 - (row + 2) % 3] == ' ')) {
            board[(row + 2) % 3][2 - (row + 2) % 3] = 'o';
            return 1;
        }
        if ((board[row][row] == c)
            && (board[(row + 1) % 3][(row + 1) % 3] == c)
            && (board[(row + 2) % 3][(row + 2) % 3] == ' ')) {
            board[(row + 2) % 3][(row + 2) % 3] = 'o';
            return 1;
        }
    }

    return 0;
}

//W trybie prostym komputer losuje pole, jeśli jest zajęte losujemy kolejne itd...
//W trybie zaawansowanym komputer w pierwszej kolejnści stara poruszać się po narożnikach, co w połączeniu z zapobieganiem postawieniu krzyżyka na środku prowadzi do remisu lub wygranej
//Komputer zawsze stara w pierwszej kolejności uzupełnić znak w syruacji gdy w danej lini są dwa takie same znaki, zapewnia uzupełnienie do wygranej lub blokadę przeciwnika
//Aby komputer nie losował za kazdym razem tych samych wartosci w funkcji main zainicjowano generator liczb pseudolosowych poleceniem : srand(time(NULL)), w tym celu do programu dołączono:
//#include <stdlib.h>
//#include <time.h>
void aiMove(char board[3][3],char difficulty)
{

    //Funkcja fill gap wstawia znak w puste miejsce gdy w danej lini istnieją dwa takie same znaki, zapewnia uzupełnienie do wygranej lub blokadę przeciwnika
    unsigned int row, col, i;
    if (fillGap(board, 'o'))
        return;
    if (fillGap(board, 'x'))
        return;

    //zapobieganie postawieniu krzyżyka i sytuacji w której komputer nie będzie mógł nas zablokować z powodu powstania dwóch wyborów
    if (((board[0][1] == 'x' && board[1][0] == 'x') || (board[1][0] =='x'&& board[2][1] == 'x') || (board[2][1] == 'x'&& board[1][2] == 'x') || (board[1][2] == 'x' && board[0][1] == 'x'))&&board[1][1]==' ')
    {
        board[1][1] = 'o';
        return;
    }
    
    //Strategia w której komputer próbuje poruszać sie w naroznikach, działa w trybie trudnym gdy gracz wybierze ('T' lub 't') jest to optymalna strategia zapewniająca wygraną lub remis.
    while ((difficulty == 't' || difficulty == 'T')&&(board[0][0]==' '|| board[0][2] == ' ' || board[2][0] == ' ' || board[2][2] == ' '))
    {
        row = rand() % 2;
        col = rand() % 2;
        if (board[2 * row][2 * col] == ' ')
        {
            board[2 * row][2 * col] = 'o';
            return;
        }
    }

    //losowe wybieranie pól przez komputer, działa gdy nie ma luk do wypełnienia i narożniki są zajęte lub w trybie łatwym 'e' lub 'E'
    do
    {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');
    board[row][col] = 'o';

}


//Program będzie wykonywał dopuki nie zostanie wciśnięty 'Z' na początku i po każdej skończnej grze będzie pojawiać się menu wyboru
//Gra wykonuje się w pętli która jest przerywana z zakończniem gry , gracze wykonują swoe ruch naprzemiennie, zmienna move typu bool pozwala określić kolejkę gracza
//przed każdą grą zmienna score przyjmuje wartosc 0,zmiana jej wartości powoduje koniec gry i powrót do menu wyboru.
//Stan gry ocenia funkcja checkBoard, zmienia ona wartość zmiennej score.
//Zmienna score przyjmuje wartośći:
//0 – gra nie zakonczona,
//1 – remis,
//’x’ – wygrały krzyzyki,
//’o’ – wygrały kółka
//Dla uproszczenia przyjmujemy, ze człowiek zawsze gra
//krzyzykami a komputer kółkami.
//Funkcja printBoard rysuje planszę
//Zmienna selectGame pozwala na wybór trybu gry

int main(int argc, char* argv[])
{
    bool move ;
    char score,selectGame;
    char board[3][3];
    srand(time(NULL));
    do
    {
        move = 1;
        score = 0;
        clearBoard(board);
        system("cls"); // czyśc ekran. 
        printf("********************************************************************************\n");
        printf("-============================== KOLKO I KRZYZYK ================================\n");
        printf("********************************************************************************\n");
        printf("M-Gra z druga osoba., E-Z komputerem, poziom latwy T-Z komputerem, poziom trudny\n");
        printf("Naciśnij 'Z' aby zakończyć program *********************************************\n");
        selectGame = getchar();
        switch (selectGame)
        {
        case 'T':
        case 't':
        case 'e':
        case 'E':
            while (score == 0)
            {
                if (move == 0) playerMove(board);
                else aiMove(board,selectGame);
                move=!move;
                score = checkBoard(board);
            }
            printBoard(board);
            if (score == 1)
                printf("Remis\n");
            else
                if (score == 'x') printf("Wygrales!!! :-) \n");
                else printf("Przegrales :( \n");
            printf("Nacisnij klawisz aby kontynowac gre\n");
            getchar();
            selectGame = getchar();
            break;
        case 'M':
        case 'm':
            while (score == 0)
            {
                if (move == 0) playerMove(board);
                else secondPlayerMove(board);
                move = !move;
                score = checkBoard(board);
            }
            printBoard(board);
            if (score == 1)
                printf("Remis\n");
            else
                if (score == 'x') printf("Wygral gracz 1 (krzyzyk) :-) \n");
                else printf("Wygral gracz 2 (kolko) :-) \n");
            printf("Nacisnij klawisz aby kontynowac gre\n");
            getchar();
            selectGame = getchar();
            break;

        default:
            break;
        }     
    }while ((selectGame != 'Z')&& (selectGame !='z'));
   

    return 0;
}