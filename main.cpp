#include <iostream>
#include <cstdlib>
#include <Windows.h>

using namespace std;

void matr(int *arr, int N, int wdt = 6){                   // matrix declaration(объявление матрицы)
    for(int i = 0; i < N * N; i = i + N){
        for(int j = i; j < i + N; j++){
            cout.width(wdt);                          // set width(задать ширину)
            cout << arr[j];
        }
        putchar('\n');
    }
}


int randInt(int a, int b) {
    return a + rand() % b;
}



void fillZr(int *arr, int N){                               // zero fill(нулевое поле)
    for(int i = 0; i < N * N; ++i){
        *(arr++) = 0;
    }
}


void fillSnk(int *arr, int N){                              // creating a snake(создание змейки)
    
    matr(arr, N);

    int *pArr = arr;
    int c = N;
    for (int i = 0; i < N; i++){
        int *pR = (c > 0) ? pArr + N*N - N : pArr - N * N + N;
        while(pArr - c != pR){
            *pArr = randInt(1, N * N);
            pArr = pArr + c;
        }
        pArr = pArr - c - 1;
        c = -c;
    }
}


void fillSpr(int *arr, int N){

    matr(arr, N);


    int *pArr = arr;
    int size = N;
    for(int sq = 0; sq < N / 2; sq++){
        int c = 1;
        for(int dir = 0; dir < 4; dir++){
            for(int i = 0; i < size - 1; i++){
                *pArr = randInt(1, N * N);
                pArr = pArr + c;
            }
            c = abs(c) == 1 ? N : 1;
            c = dir < 1 ? + c : -c;
        }
        size = size - 2;
        pArr = pArr + N + 1;
    }
}


int *pointQ(int *arr, int N, int quaN) {
    switch(quaN){
        case 1:{
            return (arr);
        }    
        case 2:{
            return (arr + N / 2);
        }    
        case 3:{
            return (arr + N * N / 2);
        }    
        case 4:{
            return (arr + N * N / 2 + N / 2);
        }    
    }
}


void swapQ(int *arr, int N, int q1, int q2){

    int *pQ1 = pointQ(arr, N, q1);
    int *pQ2 = pointQ(arr, N, q2);

    for(int i = 0; i < N / 2; i++){                        // swap(меняем)
        for(int j = 0; j < N / 2; j++){
            swap(*(pQ1++), *(pQ2++));
        }
        pQ1 = pQ1 + N - N / 2;
        pQ2 = pQ2 + N - N / 2;
    }
}


void insertSort(int *arr, int N){
    for(int *p1 = arr + 1; p1 < arr + N * N; p1++){
        for(int *p2 = p1; p2 > arr && *(p2 - 1) > *p2; p2--){
            swap(*(p2 - 1), *p2);
        }
    }
}


void matrV(int *arr, int N, int op, int df){
    for(int *pArr = arr; pArr < arr + N * N; pArr++){
        switch(op){
            case '+':{
                *pArr = *pArr + df;
                break;
            }
            case '-': {
                *pArr = *pArr - df;
                break;
            }
            case '*': {
                *pArr = *pArr * df;
                break;
            }
            case '/': {
                *pArr = *pArr / df;
                break;
            }
        }
    }
}


int main() {

    const int N = 6;
    int mtrx[N][N];
    int *ptrMatr = &mtrx[0][0];
    cout << "Zero fill array: \n";
    fillZr(ptrMatr, N);

    fillSnk(ptrMatr, N);

                                               // output snake array()
    cout << "Snake array: \n";
    
    fillSpk(ptrMatr, N);


    cout << "Spiral array: \n";                // output spiral array
    fillSpr(ptrMatr, N);
    cout << "\n" << "\n";



    char us;
    cout << "Enter 'a' or 'b' or 'c' or 'd': \n";
    cin >> us;
    cin.sync();

    cout << "Matrix:\n";
    matr(ptrMatr, N);
    switch(us){
        case 'a':{
            swapQ(ptrMatr, N, 1, 2);
            swapQ(ptrMatr, N, 2, 4);
            swapQ(ptrMatr, N, 4, 3);
            swapQ(ptrMatr, N, 3, 1);
            break;
        }
        case 'b':{
            swapQ(ptrMatr, N, 1, 4);
            swapQ(ptrMatr, N, 2, 3);
            break;
        }
        case 'c':{
            swapQ(ptrMatr, N, 1, 3);
            swapQ(ptrMatr, N, 2, 4);
            break;
        }
        case 'd':{
            swapQ(ptrMatr, N, 1, 2);
            swapQ(ptrMatr, N, 3, 4);
            break;
        }
    }
    cout << "Swap matrix:\n";
    matr(ptrMatr, N);
    cout << "\n" << "\n";



    // Insertion sort
    cout << "Matrix:\n";
    matr(ptrMatr, N);
    insertSort(ptrMatr, N);
    cout << "Sorted matrix:\n";
    matr(ptrMatr, N);



    // Decreasing, increasing, multiplying, dividing a matrix by the entered number
    int num;
    cout << "Enter number:\n";
    cin >> num;
    cin.sync(); // removes unread characters from the input stream(убирает непрочитанные символы из входного потока)

    char oper;
    cout << "Enter operation('+' or '-' or '*' or '/'):\n";
    cin >> oper;
    cin.sync();

    cout << "Matrix:\n";
    matr(ptrMatr, N);
    matrV(ptrMatr, N, oper, num);
    cout << "Matrix after:\n";
    matr(ptrMatr, N);

}
