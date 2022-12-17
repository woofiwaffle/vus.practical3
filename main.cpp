#include <iostream>
#include <cstdlib>
#include <cmath>
#include <Windows.h>

using namespace std;

int det(int* *a, int n){                      //idz 10
    if (n == 1){
        return a[0][0];
    }
    else if(n == 2){
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }
    else{
        int d = 0;
        for(int k = 0; k < n; k++){
            int* *m = new int*[n - 1];
            for(int i = 0; i < n - 1; i++) {
                m[i] = new int[n - 1];
            }
            for(int i = 1; i < n; i++){
                int t = 0;
                for(int j = 0; j < n; j++){
                    if(j == k){
                        continue;
                    }
                    m[i-1][t] = a[i][j];
                    t++;
                }
            }
            d = d + pow(-1, k + 2) * a[0][k] * det(m, n - 1);
        }
        return d;
    }
}



bool ort(int **A, int **E, int n);                      //idz 7



void matr(int *arr, int N, int wdt = 6){                   // matrix declaration(объявление матрицы)
    for(int i = 0; i < N * N; i = i + N){
        for(int j = i; j < i + N; j++){
            cout.width(wdt);                          // set width(задать ширину)
            cout << arr[j];
        }
        putchar('\n');
    }
}



int getCursorPositionY() {
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo = {};
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBufferInfo);
    return screenBufferInfo.dwCursorPosition.Y;
}



int randInt(int a, int b) {
    return a + rand() % b;
}



int lengthInt(int l) {
    if(l == 0){
        return 1;
    }
    int m = 0;
    while(l){
        l = l / 10;
        m++;
    }
    return m;
}



void matrUpd(int x, int y, int v, int wdt = 6) {
    COORD coord;
    coord.X = (x + 1) * wdt - lengthInt(v);
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    cout << v << '\r';
    cout.flush();
    Sleep(100);
}



void fillZr(int *arr, int N){                               // zero fill(нулевое поле)
    for(int i = 0; i < N * N; i++){
        *(arr++) = 0;
    }
}



void fillSpr(int *arr, int N){         // creating a snake(создание змейки)
    int CursorY = getCursorPositionY();
    matr(arr, N);

    int *pArr = arr;
    int cr = N;
    for(int i = 0; i < N; i++){
        int *pR = (cr > 0) ? pArr + N * N - N : pArr - N * N + N;
        while(pArr - cr != pR){
            *pArr = randInt(1, N * N);
            matrUpd((pArr - arr) % N, CursorY + (pArr - arr) / N, *pArr);
            pArr = pArr + cr;
        }
        pArr = pArr - (cr - 1);
        cr = -cr;
    }
    for(int i = 0; i < N; i++){
        putchar('\n');
    }
}


void fillSnk(int *arr, int N){
    int CursorY = getCursorPositionY();
    matr(arr, N);

    int *pArr = arr;
    int size = N;
    for(int s = 0; s < N / 2; s++){
        int c = 1;
        for(int d = 0; d < 4; d++){
            for(int i = 0; i < size - 1; i++){
                *pArr = randInt(1, N * N);
                matrUpd((pArr - arr) % N, CursorY + (pArr - arr) / N, *pArr);
                pArr = pArr + c;
            }
            c = abs(c) == 1 ? N : 1;
            c = d < 1 ? + c : -c;
        }
        size = size - 2;
        pArr = pArr + N + 1;
    }
    for(int i = 0; i < N / 2; i++){
        putchar('\n');
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
    for(int i = 0; i < N / 2; ++i){                        // swap(меняем)
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
            case '-':{
                *pArr = *pArr - df;
                break;
            }
            case '*':{
                *pArr = *pArr * df;
                break;
            }
            case '/':{
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
    fillZr(ptrMatr, N);

    while(true) {
        char number;
        cout << "\nEnter a number from 1 to 5(the number is a task in practice), 6 - idz(10), 7 - idz(7)\n";
        cin.sync();
        cin >> number;

        switch (number) {

            case '1': {
                cout << "Snake array: \n";
                fillSnk(ptrMatr, N);
                cout << "\n\n";
                break;
            }

            case '2': {
                cout << "Spiral array: \n";                // output spiral array
                fillSpr(ptrMatr, N);
                cout << "\n\n";
                break;
            }

            case '3': {
                char us;
                cout << "Enter 'a' or 'b' or 'c' or 'd': \n";
                cin >> us;
                cin.sync();

                cout << "Matrix:\n";
                matr(ptrMatr, N);
                switch (us) {
                    case 'a': {
                        swapQ(ptrMatr, N, 1, 2);
                        swapQ(ptrMatr, N, 2, 4);
                        swapQ(ptrMatr, N, 4, 3);
                        swapQ(ptrMatr, N, 3, 1);
                        break;
                    }
                    case 'b': {
                        swapQ(ptrMatr, N, 1, 4);
                        swapQ(ptrMatr, N, 2, 3);
                        break;
                    }
                    case 'c': {
                        swapQ(ptrMatr, N, 1, 3);
                        swapQ(ptrMatr, N, 2, 4);
                        break;
                    }
                    case 'd': {
                        swapQ(ptrMatr, N, 1, 2);
                        swapQ(ptrMatr, N, 3, 4);
                        break;
                    }
                }
                cout << "Swap matrix:\n";
                matr(ptrMatr, N);
                cout << "\n" << "\n";
                break;
            }

            case '4': {
                // Insertion sort
                cout << "Matrix:\n";
                matr(ptrMatr, N);
                insertSort(ptrMatr, N);
                cout << "Sorted matrix:\n";
                matr(ptrMatr, N);
                break;
            }

            case '5': {
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
                break;
            }

            case '6': {
                cout << "\nFound determinant:\n";                   // ИДЗ № 3 (10)
                                                               /* Создайте матрицу 3 на 3, заполните ее случайными
                                                                 числами (-30 до 30). Найдите определитель матрицы */
                srand(time(NULL));
                int n = 0;
                cout << "Enter 3:";
                cin >> n;
                int **a = new int *[n];

                for (int i = 0; i < n; i++) {
                    a[i] = new int[n];
                }

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        a[i][j] = rand() % 60 - 30;
                        cout.width(3);
                        cout << a[i][j] << " ";
                    }
                    cout << endl;
                }
                cout << "found determinant: " << det(a, n) << "\n";
                break;
            }
            case '7':{
                int n, **A = new int *[n], **E = new int *[n];
                ort (A, E, n);
                break;
            }
            default:{
                cout << "Error\n";
            }
        }
    }
}



bool ort (int **A, int **E, int n){                           //ИДЗ 7
    bool res = 1;                                    // Заполнить матрицу случайными числами (от 1 до 100)
    cout << "Matrix size: ";                        // Определить, является ли матрица ортогональной
    cin >> n;
    A = new int*[n], E = new int*[n];

    for (int i = 0; i < n; i++){
        A[i] = new int[n];
        E[i]= new int[n];
    }
    for (int i = 0; i < n; i++){
        cout <<"\n";
        for(int j = 0; j < n; j++) {
            A[i][j] = rand() % 90;
            cout << A[i][j] << "\t";
        }
    }
    int el = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                el = el + A[i][k] * A[j][k];
            }
            E[i][j] = el;
            if((i == j && el != 1) || (i != j && el != 0)){
                res=0;
                break;
            }
        }
    }
    if(res){
        cout << "\nMatrix is orthogonal.\n";
    }
    else{
        cout << "\nMatrix is not orthogonal.\n";
    }
    return res;
}
