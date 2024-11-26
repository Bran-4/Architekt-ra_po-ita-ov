#include <stdio.h>
#include <windows.h>
#pragma warning(disable:4996)

        // Niektore verzie potrebuju globalne premenne

int uloha1() {
    int iCislo = 27;
    int iaCislo = 28;
    int iVysledok = 0;
    printf("\nCislo: %d  cislo: %d", iCislo, iaCislo);

    __asm {                          // zaciatok bloku asm
        MOV EAX, iCislo                  // do EAX vloz hodnotu premennej iCislo (z pamate)
        ADD EAX, iaCislo                          // pripocitaj 1
        MOV iVysledok, EAX                // do premennej iVysledok vloz vysledok z registra EAX
    }                                // koniec bloku asm

    printf("\nVysledok: %d", iVysledok);

    printf("\n\nStlac ENTER a skoncime...");
    scanf("?");
    return 0;
}

int uloha2() {
    int iCislo = 27;
    printf("\nCislo: %d", iCislo);
    __asm {            
        MOV EAX, iCislo
        SHL EAX,1
        MOV iCislo, EAX
    }
    printf("\nVysledok: %d", iCislo);
}

int uloha3() {
    int iCislo = 10;
    printf("\nCislo: %d", iCislo);
    __asm {
        MOV EAX, iCislo
        CMP EAX,9
        JG eax_je_vacsi
        ADD EAX, 48
        JMP done
        eax_je_vacsi:ADD EAX,55
        done:
        MOV iCislo, EAX
    }
    printf("\nVysledok: %c", iCislo);
}

int uloha4() {
    int veta;
    int vetaa;
    int vetab;
    __asm {
        MOV eax, 0
        CPUID
        MOV veta, ebx
        MOV vetaa,edx
        MOV vetab,ecx

    }
    printf("\nVysledok: %c%c%c%c", veta,veta>>8,veta>>16,veta>>24);
    printf("%c%c%c%c", vetaa, vetaa >> 8, vetaa >> 16, vetaa >> 24);
    printf("%c%c%c%c", vetab, vetab >> 8, vetab >> 16, vetab >> 24);
}


int uloha_2_2() {
    char veta[] = "architektura_pc_je_super";
    char * a =veta;
    printf("veta:%s\n", veta);
    printf("adresa je %p\n", a);
    a += 1;
    *a = 'X';
    printf("pointer je %p\n", a);
    printf("veta: %s\n", a);
    //strcpy(a, "pes");
    printf("veta:%s\n", veta);
    a += 45055555;
    //strcpy(a, "pes");
    return 0;
}

void uloha_2_5_1() {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int pocet = 1;
    for (int k = 0; k < 51; k++) {
        SetConsoleTextAttribute(hConsole, pocet);
        if (k%10==9) {
            pocet += 1;
        }
        printf("%03d\n", k);
    }
    int k = 2;
}

#include <stdlib.h>
#include <string.h>

int uloha2_3_1() {
    FILE* subor, *novy;
    char riadok[1000];
    subor = fopen("poviedka.html", "r");
    if (subor == NULL) {
        printf("Chyba pri otvarani suboru.\n");
        return 1;
    }
    novy = fopen("poviedka2.html", "w");
    while (fgets(riadok, sizeof(riadok), subor) != NULL) {
        for (int i = 0; riadok[i] != '\0'; i++) {
            if (riadok[i] == (char)165) riadok[i] = (char)188;
            switch (riadok[i]) {
            case char(165): // º v ISO-8859-2
                riadok[i] = char(188); // º v Windows-1250
                break;
            case char(169): // ä v ISO-8859-2
                riadok[i] = char(138);// ä v Windows-1250
                break;
            case char(171): // ç v ISO-8859-2
                riadok[i] = char(141);// ç v Windows-1250
                break;
            case char(174): // é v ISO-8859-2
                riadok[i] = char(142); // é v Windows-1250
                break;
            case char(181) : // æ v ISO-8859-2
                riadok[i] = char(190); // æ v Windows-1250
                break;
            case char(185): // ö v ISO-8859-2
                riadok[i] = char(154);// ö v Windows-1250
                break;
            case char(187): // ù v ISO-8859-2
                riadok[i] = char(157); // ù v Windows-1250
                break;
            case char(190): // û v ISO-8859-2
                riadok[i] = char(158); // û v Windows-1250
                break;
            default:
                //printf("%c ", riadok[i]);
                // Ak nie je znak z tabuæky, ponech· sa nezmenen˝
                break;
            }
        }
        //printf("%s", riadok);
        fprintf(novy, "%s", riadok);
    }
    fclose(subor);
    fclose(novy);
    printf("hotovo");
    return 1;
}

int uloha2_3_2() {
    FILE* subor,*novy;
    char riadok[1000];
    subor = fopen("koniec_poviedky.html", "rb");
    if (subor == NULL) {
        printf("Chyba pri otvarani suboru.\n");
        return 1;
    }
    novy = fopen("poviedka2.html", "w");
    while (fgets(riadok, sizeof(riadok), subor) != NULL) {
        for (int i = 0; riadok[i] != '\0'; i++) {
            riadok[i] = riadok[i]^ 27;
        }
        fprintf(novy, "%s", riadok);
    }
    fclose(subor);
    fclose(novy);
}
#include <stdio.h>
#include <conio.h>
#include <time.h>

int uloha2_6() {
    char klavesa;
    clock_t Start, Koniec;   // premenne typu clock_t
    float  Trvanie;          // tu bude vysledok merania
    long   i = 10000000L;
    while (1) {
        klavesa = getch();
        if (klavesa == 59) { // F1
            printf("----------------------\n");
            printf("Pravidla:\nAk stlacite F2 zacnete hrat:\nStlacajte velke pismena na obrazovke a program vypise vas cas\nPre ukoncenie: F10\n");
            printf("----------------------\n");
        }
        else if (klavesa == 60) { // F2
            printf("start\n");
            while (1) {
                int klav = rand() % (25) + 65;
                printf("\n%c", klav);
                Start = clock();
                // Vypocet dlzky trvania
                while (1) {
                    klavesa = getch();
                    if (klavesa == 68 || klavesa == 27) {
                        printf("\nKoniec");
                        return 0;
                    }
                    else if (klavesa == char(klav)) {
                        Koniec = clock();
                        Trvanie = (float)(Koniec - Start) / CLOCKS_PER_SEC;
                        printf("  %f sekund\n\n", Trvanie);
                        break;
                    }
                    else {
                        printf("zle");
                    }
                }
            }
        }
        else if (klavesa == 68 || klavesa == 27) {
            printf("Koniec\n");
            return 0;
        }
    }
    return 0;
}

int main()
{
    uloha1();
    uloha2();
    uloha3();
    uloha4();
    uloha_2_2();
    uloha_2_5_1();
    uloha2_3_1();
    uloha2_3_2();
    uloha2_6();
    return(0);
}