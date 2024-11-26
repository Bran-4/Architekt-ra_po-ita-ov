// blok3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)
////bonus

#include <string.h>
#include <stdlib.h>
#define MEMORY_SIZE 64

char* memory[MEMORY_SIZE];

void initializuj_pamat() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = (char*)malloc(sizeof(char) * 10);
        strcpy(memory[i], "NOP");
    }
}

void fetchInstruction(int PC) {
    if (PC < 0 || PC >= MEMORY_SIZE) {
        printf("Error\n");
        return;
    }
    char* instrukcia = memory[PC];
    printf("Instrukcia na adrese %d: %s\n", PC, instrukcia);
}
///////

char* prvocislo(char slovo[]) {
    int zoznam[100];
    char nove_slovo[200];
    zoznam[0] = 2;
    int a = 3;
    int i = 1;
    int je;
    while (1) {
        if (strlen(slovo) < a) {
            break;
        }
        else {
            je = 1;
            for (int j = 0; j < i; j++) {
                if (a % zoznam[j] == 0) {
                    //printf("\n%d  %d",a%zoznam[j],a);
                    je = 0;
                    break;
                }
            }
            if (je == 1) {
                zoznam[i] = a;
                i++;
            }
            a++;
        }
    }
    for (int j = 0; j < i; j++) {
        nove_slovo[j] = slovo[zoznam[j] - 1];
    }
    nove_slovo[i] = '\0';
    return strdup(nove_slovo);
}

int main()
{
    //uvodne nastavovacky

    WSADATA wsaData;    //struktura WSADATA pre pracu s Winsock
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);     //zakladna inicializacia
    if (iResult != 0)     //kontrola, ci nestala chyba
    {
        printf("WSAStartup failed : % d\n", iResult);
        return 1;
    }

    struct addrinfo* result = NULL, * ptr = NULL;     //struktura pre pracu s adresami
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;     //pracujeme s protokolom TCP/IP

    // Resolve the server address and port
    iResult = getaddrinfo("147.175.115.34", "777", &hints, &result);
    if (iResult != 0)     //kontrola, ci nenastala chyba
    {
        printf("getaddrinfo failed : % d\n", iResult);
        WSACleanup();
        return 1;
    }
    else
        printf("getaddrinfo didn't fail...\n");

    ////////////////////////

    //vytvorenie socketu a pripojenie sa

    SOCKET ConnectSocket = INVALID_SOCKET;

    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    ptr = result;

    // Create a SOCKET for connecting to server => pokus o vytvorenie socketu
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)     //kontrola, ci nenastala chyba 
    {
        printf("Error at socket() : % ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    else
        printf("Error at socket DIDN'T occur...\n");

    // Connect to server. => pokus o pripojenie sa na server

    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)     //kontrola, ci nenastala chyba
        printf("Not connected to server...\n");
    else
        printf("Connected to server!\n");

    if (iResult == SOCKET_ERROR)    //osetrenie chyboveho stavu
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        WSACleanup();
        return 1;
    }

    Sleep(250);
    //////////////////////////////////////////
    FILE* subor;//praca so suborom
    subor = fopen("sprava.txt", "w");

    char id[] = "126813";
    int sucet = 0;
    for (int j = 0; j < 4; j++) {
        sucet += (int)id[j];
    }
    sucet-= '0';
    sucet %= (int)id[4]-'0';
    char slovo_sucet[2]; slovo_sucet[1] = '\0';
    slovo_sucet[0] = (char)sucet + '0';

    SetConsoleOutputCP(1250);
    HANDLE  hConsole;//priprava na graficke upravy
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int consoleWidth = consoleInfo.dwSize.X;
    int polka = consoleWidth / 2;
    COORD suradnice_kurzora;

#define DEFAULT_BUFLEN 4096 //makro, kde definujeme velkost prijimacieho buffera

    const char *spravy[] = {" ",id,"áno?","844848","753422",slovo_sucet,"333222334","123","ano","27","86","M.E.","PRIMENUMBER"," ","Trinity","NIE","polyadicke","BONUS","halo","ano"};
    char sendbuf[100];
    int i = 0;
    while (1){
        //posielanie
        SetConsoleTextAttribute(hConsole, 1);
        strcpy(sendbuf, spravy[i]);
        iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed : % d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }

        printf("Bytes Sent : % ld\n", iResult);
        printf("%s\n", sendbuf);
        fprintf(subor, "JA: %s\n", sendbuf);
        //prijimanie
     
        int recvbuflen = DEFAULT_BUFLEN;
        char recvbuf[DEFAULT_BUFLEN];

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);     //funkcia na príjimanie

        if (iResult > 0) {
            printf("Bytes received : % d\n", iResult);
        }//prisli validne data, vypis poctu
        else if (iResult == 0) {
            printf("Connection closed\n");
        }//v tomto pripade server ukoncil komunikaciu
        else {
            printf("recv failed with error : % d\n", WSAGetLastError());
        }
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        suradnice_kurzora = consoleInfo.dwCursorPosition;
        suradnice_kurzora.X = polka;
        SetConsoleCursorPosition(hConsole, suradnice_kurzora);
        SetConsoleTextAttribute(hConsole, 2);


        for (int j = 0; j < iResult; j++) {//vypisovanie spravy a rozdelovanie na pravu stranu
            GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
            suradnice_kurzora = consoleInfo.dwCursorPosition;
            if (i == 7) {
                recvbuf[j] = recvbuf[j] ^ 55;
            }
            if (suradnice_kurzora.X > consoleInfo.dwSize.X - 13 && recvbuf[j]==' ') {
                suradnice_kurzora.X = polka;
                if (suradnice_kurzora.Y > consoleInfo.dwSize.Y - 2) {
                    printf("\n");
                }
                else {
                    suradnice_kurzora.Y++;
                }
                SetConsoleCursorPosition(hConsole, suradnice_kurzora);
            }
            //Sleep(2);
            printf("%c", recvbuf[j]);
        }
        if (i == 12) {
            spravy[13]= prvocislo(recvbuf);
        }
        recvbuf[iResult] = '\0';
        fprintf(subor, "MORFEUS: %s\n", recvbuf);//zapisovanie do txt suboru
        printf("\n");
        i++;
        if (i > 19) {
            break;
        }
    }


    //zavretie socketu
    fclose(subor);
    closesocket(ConnectSocket);
    WSACleanup();

    /////bonus
    initializuj_pamat();
    int PC = 0;
    while (PC < MEMORY_SIZE) {
        fetchInstruction(PC);
        PC++;
    }
    for (int i = 0; i < MEMORY_SIZE; i++) {
        free(memory[i]);
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

