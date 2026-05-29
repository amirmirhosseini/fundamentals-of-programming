#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
char map1[100];
char map2[100];
char map4[100]; // mape ma k comp tkrri nzne.
char map3[100]; // mape comp k ma tkrri nznim.
char const SSym = 'S';
char const diR = 'R', diD = 'D', diU = 'U', diL = 'L';
// int sp,si;
// char di;
// int flag=0;
// int  turns; //external
// int S2L , S1L; //external
// int q;
// int n;

void TarifeMap(char map[])
{
    for (int i = 0; i < 100; i++)
        map[i] = '-';
}

void NamayesheMap(char map1[], char map3[])
{
    printf("===============================\n");
    for (int i = 0; i < 100; i = i + 10)
    {
        for (int c = 0; c < 10; c++)
            printf("%c", map1[i + c]);
        printf("    | |    ");
        for (int c = 0; c < 10; c++)
            printf("%c", map3[i + c]);

        printf("\n");
    }
    printf("===============================\n");
}

void GozashtanKeshti1(char map0[100])
{
    int si1 = 4, si2 = 3, si3 = 2, si4 = 1;

    int z, i, n, flag;
    char di;
    int sp, si;
    while (1)
    {

        for (flag = 0, z = 0; z < 10; z++)
        {
            scanf("%d %d %c", &sp, &si, &di);
      //      if (di=='R' || di=='D' || di='U' || di='L')
          //      n=0;
         //   else
           //     flag = 1 ;

            if (sp >= 0 && sp < 100)
                n = 0;
            else
                flag = 1;

            if (si == 1)
                si1--;
            if (si == 2)
                si2--;
            if (si == 3)
                si3--;
            if (si == 4)
                si4--;

            if (si != 1 && si != 2 && si != 3 && si != 4)
                flag = 1;

            if (si1 < 0 || si2 < 0 || si3 < 0 || si4 < 0)
                flag = 1;

            // if(di != 'R' || di != 'L' || di != 'U' || di != 'D')
            //    flag=1;

            // for (i = 0; i < si ; ++i)
            //        if (map1[sp+i] ==  SSym)
            //        flag=1; // ???? ??????
            if (di == 'D')
            {
                // printf("upcheck\n");
                for (i = 0; i < si; i++)
                {
                    if (map0[sp + (i * 10)] == SSym)
                    {
                        //  printf("u1");
                        flag = 1;
                    }
                } // ???? ??????
                if ((sp + ((si - 1) * 10)) < 0)
                {
                    //  printf("u");
                    flag = 1;
                }
                else
                {
                    for (i = 0; i <= si - 1; i = i + 1)
                        map0[sp + (i * 10)] = 'S';
                }
            }
            else if (di == 'U')
            {
                // printf("upcheck\n");
                for (i = 0; i < si; i++)
                {
                    if (map0[sp - i * 10] == SSym)
                    {
                        //  printf("u1");
                        flag = 1;
                    }
                } // ???? ??????
                if ((sp - ((si - 1) * 10)) < 0)
                {
                    //  printf("u");
                    flag = 1;
                }
                else
                {
                    for (i = 0; i <= si - 1; i = i + 1)
                        map0[sp - (i * 10)] = 'S';
                }
            }
            else if (di == diR)
            {
                for (i = 0; i < si; i++)
                {
                    if (map0[sp + i] == SSym)
                        flag = 1;
                } // ???? ??????
                if (((sp + si - 1) / 10) != (sp / 10))
                    flag = 1;

                else
                {
                    for (i = 0; i <= si - 1; i++)
                        map0[sp + i] = 'S';
                }
            }

            else if (di == diL)
            {
                for (i = 0; i < si; i++)
                {
                    if (map0[sp - i] == SSym)
                        flag = 1;
                } // ???? ??????
                if ((((sp - si + 1) / 10) != (sp / 10)) || ((sp - si + 1) < 0))
                    flag = 1;

                else
                {
                    for (i = 0; i <= si - 1; i++)
                        map0[sp - i] = 'S';
                }
            }
            else
                flag=1;
        }
        // printf("flag is= %d", flag);
        // map1[sp]='S'

        // printf("flag is= %d", flag);
        if (flag == 1)
        {
            for (i = 0; i < 100; i++)
            {
                map0[i] = '-';
            }
            printf("Wrong Placement. Do it again.\n");
            si1 = 4, si2 = 3, si3 = 2, si4 = 1;
            continue;
        }

        if (z == 10)
            break;
    }
}

/*
    void levelchoice(){
        int s1=0 , s2=0;
    printf("Your Team:     %d\nComputer Team: %d\nEnter a level (easy, normal, hard, unbeatable):" , s1 , s2);
    char answer[15];
scanf("%s", &answer);
if (strcmp(answer, "easy")==0) {
    int result = easygame();
    if (result/100 == 1)
        s2=s2+result-100;
    else
        s1=s1+result;
    system("cls");
    //printf("%d\n", result);
    printf("Your Team:     %d\nComputer Team: %d\n" , s1 , s2);
    TarifeMap(map1);
    TarifeMap(map2);
    TarifeMap(map3);
    TarifeMap(map4);
    break;
   // system("cls");
}
else
    continue;
    } */

int normalgame()
{
    int s[20];
    int o[80];
    int b = 0, c = 0;
    int SPL = 20;
    int SCL = 20;
    int ATC = 1;
    int fr = 100;
    int flag = 0;
    int ATP = 1;
    int flagAT = 0;
    int flagAP = 0;
    int turns = 1001;
    srand(time(NULL));
    printf("Enter your ships in 10 lines. each line includes there\n        start spot (from 0 to 99)\n       and direction of the ship (U, R, D, L)\nfor example: 11 3 R\n");
    GozashtanKeshti1(map1);
    printf("Enter computer's ships in 10 lines. each line includes there\n        start spot (from 0 to 99)\n       and direction of the ship (U, R, D, L)\nfor example: 11 3 R\n");
    GozashtanKeshti1(map2);
    NamayesheMap(map1, map3);
    for (int i = 0; i < 100; i++)
    {
        if (map1[i] == 'S')
        {
            s[b] = i;
            b++;
        }
        else
        {
            o[c] = i;
            c++;
        }
    }
    // for (int q=0 ; q<b ; q++)
    // printf("%d ", s[q] );
    // printf("\n");
    // for (int j=0 ; j<c ; j++)
    // printf("%d ", o[j] );

    while (SPL > 0 && SCL > 0)
    {
        flag = 0;
        // printf("check1\n");
        // fflush(stdout);
        //  usleep(300000);
        if ((turns % 2) == 1)
        {
            printf("Your turn:\n");
            char bombc[4];
            scanf("%3s", bombc);
            if (bombc[0] == '*')
            {
                if (ATP == 1)
                {
                    int bomba;
                    bomba = atoi(bombc + 1);
                    if ((bomba >= 11 && bomba <= 18) || (bomba >= 21 && bomba <= 28) || (bomba >= 31 && bomba <= 38) || (bomba >= 41 && bomba <= 48) || (bomba >= 51 && bomba <= 58) || (bomba >= 61 && bomba <= 68) || (bomba >= 71 && bomba <= 78) || (bomba >= 81 && bomba <= 88))
                    {
                        if (map2[bomba] != 'R')
                        {
                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba - 11 + k] == 'S')
                                {
                                    map3[bomba - 11 + k] = 'X';
                                    map2[bomba - 11 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba - 11 + k] == '-')
                                {
                                    map3[bomba - 11 + k] = 'O';
                                    map2[bomba - 11 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba - 1 + k] == 'S')
                                {
                                    map3[bomba - 1 + k] = 'X';
                                    map2[bomba - 1 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba - 1 + k] == '-')
                                {
                                    map3[bomba - 1 + k] = 'O';
                                    map2[bomba - 1 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba + 9 + k] == 'S')
                                {
                                    map3[bomba + 9 + k] = 'X';
                                    map2[bomba + 9 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba + 9 + k] == '-')
                                {
                                    map3[bomba + 9 + k] = 'O';
                                    map2[bomba + 9 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            ATP--;
                            // printf("%d", SCL);

                            if (flagAP == 1)
                            {
                                printf("you hit!\n");
                                if (SCL <= 0)
                                {
                                    NamayesheMap(map1, map3);
                                    break;
                                }
                                else
                                {
                                    NamayesheMap(map1, map3);
                                    continue;
                                }
                            }
                            else
                            {
                                printf("you missed!\n");
                                NamayesheMap(map1, map3);
                                turns--;
                                continue;
                            }
                        }
                        else
                        {
                            printf("wrong input.\n");
                            continue;
                        }
                    }
                    else
                    {
                        printf("wrong input.\n");
                        continue;
                    }
                }
                else
                {
                    printf("ERROR. You already used your Nuclear bomb.\n");
                    continue;
                }
            }
            else
            {
                int bomb;
                bomb = atoi(bombc);

                if (bomb >= 0 && bomb < 100)
                    ;
                else
                {
                    //  printf("problem is here");
                    flag = 1;
                }
                if (map2[bomb] == 'R')
                {
                    //  printf("prolem is there");
                    flag = 1;
                }

                if (flag == 1)
                {
                    printf("wrong input.\n");
                    continue;
                }
                else
                {
                    if (map2[bomb] == 'S')
                    {
                        map3[bomb] = 'X';
                        map2[bomb] = 'R';
                        printf("You Hit!\n");
                        SCL--;
                        NamayesheMap(map1, map3);
                        if (SCL == 0)
                            break;
                        // exit(0);
                        // /// kar darad

                        else
                            continue;
                    }
                    else
                    {
                        map2[bomb] = 'R';
                        map3[bomb] = 'O';
                        turns--;
                        printf("You missed!\n");
                        NamayesheMap(map1, map3);
                        continue;
                    }
                }
            }
        }

        else
        {
            //      printf("check2\n");
            fflush(stdout);
            usleep(700000);
            int randm;
            int bomba;
            int randbomba = rand() % 64;
            bomba = 11 + (randbomba / 8) * 10 + (randbomba % 8);
            printf("Computer's Turn:\n");
            // printf("%d", bomb);
            if (ATC == 1)
            {

                for (int k = 0; k < 3; k++)
                {
                    map4[bomba - 11 + k] = 'R';
                    if (map1[bomba - 11 + k] == 'S')
                    {
                        map1[bomba - 11 + k] = 'X';
                        map4[bomba - 11 + k] = 'R';
                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba - 11 + k] == '-')
                    {
                        map1[bomba - 11 + k] = 'O';
                        map4[bomba - 11 + k] = 'R';
                    }
                    else
                        ;
                }

                for (int k = 0; k < 3; k++)
                {
                    map4[bomba - 1 + k] = 'R';
                    if (map1[bomba - 1 + k] == 'S')
                    {
                        map1[bomba - 1 + k] = 'X';
                        map4[bomba - 1 + k] = 'R';
                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba - 1 + k] == '-')
                    {
                        map1[bomba - 1 + k] = 'O';
                        map4[bomba - 1 + k] = 'R';
                    }
                    else
                        ;
                }

                for (int k = 0; k < 3; k++)
                {
                    map4[bomba + 9 + k] = 'R';
                    if (map1[bomba + 9 + k] == 'S')
                    {
                        map1[bomba + 9 + k] = 'X';
                        map4[bomba + 9 + k] = 'R';
                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba + 9 + k] == '-')
                    {
                        map1[bomba + 9 + k] = 'O';
                        map4[bomba + 9 + k] = 'R';
                    }
                    else
                        ;
                }

                ATC--;

                if (flagAT == 1)
                {
                    printf("computer hit!\n");
                    NamayesheMap(map1, map3);

                    continue;
                }
                else
                {
                    printf("computer missed!\n");
                    NamayesheMap(map1, map3);
                    turns--;
                }
            }

            else
            {
                // printf("check3\n");
                randm = rand() % 3;
                //       printf("check4\n");
                // printf("randm is %d\n", randm);
                if (randm == 0)
                {
                    while (1)
                    {
                        int randshot = rand() % 20;
                        if (map4[s[randshot]] != 'R')
                        {
                            map4[s[randshot]] = 'R';
                            map1[s[randshot]] = 'X';
                            SPL--;
                            // printf("spot is: %d and spl is %d and randshot is %d\n", s[randshot], SPL, randshot );
                            printf("computer hit!\n");
                            NamayesheMap(map1, map3);
                            break;
                        }
                        else
                            continue;
                    }

                    continue;
                }

                else
                {
                    while (1)
                    {
                        int randshot = rand() % 80;
                        if (map4[o[randshot]] != 'R')
                        {
                            map4[o[randshot]] = 'R';
                            map1[o[randshot]] = 'O';
                            turns--;
                            //  printf("spot is: %d and spl is %d and randshot is %d\n", o[randshot], SPL, randshot );
                            printf("computer missed!\n");
                            NamayesheMap(map1, map3);
                            break;
                        }
                        else
                            continue;
                    }
                    continue;
                }
            }
        }
        /*
        if (map4[bomb]=='R')
            continue;
        else if (map1[bomb]=='S') {
            map1[bomb]='X';
            map4[bomb]='R';
            printf("Computer Hit!\n");
            NamayesheMap(map1 , map3);
            SPL--;
            if(SPL==0)
                break;
               // return SCL;
              //  /// payane bazi.
            else
            continue; }
        else{
            map1[bomb]='O';
            map4[bomb]='R';
            turns--;
            printf("Computer missed!\n");
            NamayesheMap(map1 , map3);
            continue;
        } */
    }

    //

    if (SPL > SCL)
    {

        return SPL;
    }
    else
    {
        fr = fr + SCL;
        return fr;
    }

    //   }
}

int hardgame()
{
    int s[20];
    int o[80];
    int b = 0, c = 0;
    int SPL = 20;
    int SCL = 20;
    int ATC = 1;
    int fr = 100;
    int ATP = 1;
    int flagAT = 0;
    int flag = 0;
    int flagAP = 0;
    int turns = 1001;
    srand(time(NULL));
    printf("Enter your ships in 10 lines. each line includes there\n        start spot (from 0 to 99)\n       and direction of the ship (U, R, D, L)\nfor example: 11 3 R\n");
    GozashtanKeshti1(map1);
    printf("Enter computer's ships in 10 lines. each line includes there\n        start spot (from 0 to 99)\n       and direction of the ship (U, R, D, L)\nfor example: 11 3 R\n");
    GozashtanKeshti1(map2);
    NamayesheMap(map1, map3);
    for (int i = 0; i < 100; i++)
    {
        if (map1[i] == 'S')
        {
            s[b] = i;
            b++;
        }
        else
        {
            o[c] = i;
            c++;
        }
    }
    // for (int q=0 ; q<b ; q++)
    // printf("%d ", s[q] );
    // printf("\n");
    // for (int j=0 ; j<c ; j++)
    // printf("%d ", o[j] );

    while (SPL > 0 && SCL > 0)
    {
        flag = 0;
        //    printf("check1\n");
        // fflush(stdout);
        //  usleep(300000);
        if ((turns % 2) == 1)
        {
            printf("Your turn:\n");
            char bombc[4];
            scanf("%3s", bombc);
            if (bombc[0] == '*')
            {
                if (ATP == 1)
                {
                    int bomba;
                    bomba = atoi(bombc + 1);
                    if ((bomba >= 11 && bomba <= 18) || (bomba >= 21 && bomba <= 28) || (bomba >= 31 && bomba <= 38) || (bomba >= 41 && bomba <= 48) || (bomba >= 51 && bomba <= 58) || (bomba >= 61 && bomba <= 68) || (bomba >= 71 && bomba <= 78) || (bomba >= 81 && bomba <= 88))
                    {
                        if (map2[bomba] != 'R')
                        {
                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba - 11 + k] == 'S')
                                {
                                    map3[bomba - 11 + k] = 'X';
                                    map2[bomba - 11 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba - 11 + k] == '-')
                                {
                                    map3[bomba - 11 + k] = 'O';
                                    map2[bomba - 11 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba - 1 + k] == 'S')
                                {
                                    map3[bomba - 1 + k] = 'X';
                                    map2[bomba - 1 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba - 1 + k] == '-')
                                {
                                    map3[bomba - 1 + k] = 'O';
                                    map2[bomba - 1 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba + 9 + k] == 'S')
                                {
                                    map3[bomba + 9 + k] = 'X';
                                    map2[bomba + 9 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba + 9 + k] == '-')
                                {
                                    map3[bomba + 9 + k] = 'O';
                                    map2[bomba + 9 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            ATP--;
                            // printf("%d", SCL);

                            if (flagAP == 1)
                            {
                                printf("you hit!\n");
                                if (SCL <= 0)
                                {
                                    NamayesheMap(map1, map3);
                                    break;
                                }
                                else
                                {
                                    NamayesheMap(map1, map3);
                                    continue;
                                }
                            }
                            else
                            {
                                printf("you missed!\n");
                                NamayesheMap(map1, map3);
                                turns--;
                                continue;
                            }
                        }
                        else
                        {
                            printf("wrong input.\n");
                            continue;
                        }
                    }
                    else
                    {
                        printf("wrong input.\n");
                        continue;
                    }
                }
                else
                {
                    printf("ERROR. You already used your Nuclear bomb.\n");
                    continue;
                }
            }
            else
            {
                int bomb;
                bomb = atoi(bombc);

                if (bomb >= 0 && bomb < 100)
                    ;
                else
                {
                    //  printf("problem is here");
                    flag = 1;
                }
                if (map2[bomb] == 'R')
                {
                    //  printf("prolem is there");
                    flag = 1;
                }

                if (flag == 1)
                {
                    printf("wrong input.\n");
                    continue;
                }
                else
                {
                    if (map2[bomb] == 'S')
                    {
                        map3[bomb] = 'X';
                        map2[bomb] = 'R';
                        printf("You Hit!\n");
                        SCL--;
                        NamayesheMap(map1, map3);
                        if (SCL == 0)
                            break;
                        // exit(0);
                        // /// kar darad

                        else
                            continue;
                    }
                    else
                    {
                        map2[bomb] = 'R';
                        map3[bomb] = 'O';
                        turns--;
                        printf("You missed!\n");
                        NamayesheMap(map1, map3);
                        continue;
                    }
                }
            }
        }

        else
        {
            //  printf("check2\n");
            fflush(stdout);
            usleep(700000);
            int randm;
            int bomba;
            int randbomba = rand() % 64;
            bomba = 11 + (randbomba / 8) * 10 + (randbomba % 8);
            printf("Computer's Turn:\n");
            // printf("%d", bomb);
            if (ATC == 1)
            {

                for (int k = 0; k < 3; k++)
                {
                    map4[bomba - 11 + k] = 'R';
                    if (map1[bomba - 11 + k] == 'S')
                    {
                        map1[bomba - 11 + k] = 'X';
                        map4[bomba - 11 + k] = 'R';
                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba - 11 + k] == '-')
                    {
                        map1[bomba - 11 + k] = 'O';
                        map4[bomba - 11 + k] = 'R';
                    }
                    else
                        ;
                }

                for (int k = 0; k < 3; k++)
                {
                    map4[bomba - 1 + k] = 'R';
                    if (map1[bomba - 1 + k] == 'S')
                    {
                        map1[bomba - 1 + k] = 'X';
                        map4[bomba - 1 + k] = 'R';
                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba - 1 + k] == '-')
                    {
                        map1[bomba - 1 + k] = 'O';
                        map4[bomba - 1 + k] = 'R';
                    }
                    else
                        ;
                }

                for (int k = 0; k < 3; k++)
                {
                    map4[bomba + 9 + k] = 'R';
                    if (map1[bomba + 9 + k] == 'S')
                    {
                        map1[bomba + 9 + k] = 'X';
                        map4[bomba + 9 + k] = 'R';
                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba + 9 + k] == '-')
                    {
                        map1[bomba + 9 + k] = 'O';
                        map4[bomba + 9 + k] = 'R';
                    }
                    else
                        ;
                }

                ATC--;

                if (flagAT == 1)
                {
                    printf("computer hit!\n");
                    NamayesheMap(map1, map3);
                    continue;
                }
                else
                {
                    printf("computer missed!\n");
                    NamayesheMap(map1, map3);
                    turns--;
                }
            }

            else
            {
                // printf("check3\n");
                randm = rand() % 3;
                //     printf("check4\n");
                //  printf("randm is %d\n", randm);
                if (randm != 2)
                {
                    while (1)
                    {
                        int randshot = rand() % 20;
                        if (map4[s[randshot]] != 'R')
                        {
                            map4[s[randshot]] = 'R';
                            map1[s[randshot]] = 'X';
                            SPL--;
                            //  printf("spot is: %d and spl is %d and randshot is %d\n", s[randshot], SPL, randshot );
                            printf("computer hit!\n");
                            NamayesheMap(map1, map3);
                            break;
                        }
                        else
                            continue;
                    }

                    continue;
                }

                else
                {
                    while (1)
                    {
                        int randshot = rand() % 80;
                        if (map4[o[randshot]] != 'R')
                        {
                            map4[o[randshot]] = 'R';
                            map1[o[randshot]] = 'O';
                            turns--;
                            //      printf("spot is: %d and spl is %d and randshot is %d\n", o[randshot], SPL, randshot );
                            printf("computer missed!\n");
                            NamayesheMap(map1, map3);
                            break;
                        }
                        else
                            continue;
                    }
                    continue;
                }
            }
        }
        /*
        if (map4[bomb]=='R')
            continue;
        else if (map1[bomb]=='S') {
            map1[bomb]='X';
            map4[bomb]='R';
            printf("Computer Hit!\n");
            NamayesheMap(map1 , map3);
            SPL--;
            if(SPL==0)
                break;
               // return SCL;
              //  /// payane bazi.
            else
            continue; }
        else{
            map1[bomb]='O';
            map4[bomb]='R';
            turns--;
            printf("Computer missed!\n");
            NamayesheMap(map1 , map3);
            continue;
        } */
    }

    //

    if (SPL > SCL)
    {

        return SPL;
    }
    else
    {
        fr = fr + SCL;
        return fr;
    }

    //   }
}

int unbeatablegame()
{
    int s[20];
    int o[80];
    int b = 0, c = 0;
    int SPL = 20;
    int SCL = 20;
    int ATC = 1;
    int fr = 100;
    int ATP = 1;
    int flag = 0;
    int flagAT = 0;
    int flagAP = 0;
    int turns = 1001;
    srand(time(NULL));
    printf("Enter your ships in 10 lines. each line includes there\n        start spot (from 0 to 99)\n       and direction of the ship (U, R, D, L)\nfor example: 11 3 R\n");
    GozashtanKeshti1(map1);
    printf("Enter computer's ships in 10 lines. each line includes there\n        start spot (from 0 to 99)\n       and direction of the ship (U, R, D, L)\nfor example: 11 3 R\n");
    GozashtanKeshti1(map2);
    NamayesheMap(map1, map3);
    for (int i = 0; i < 100; i++)
    {
        if (map1[i] == 'S')
        {
            s[b] = i;
            b++;
        }
        else
        {
            o[c] = i;
            c++;
        }
    }
    // for (int q=0 ; q<b ; q++)
    // printf("%d ", s[q] );
    // printf("\n");
    // for (int j=0 ; j<c ; j++)
    // printf("%d ", o[j] );

    while (SPL > 0 && SCL > 0)
    {
        flag = 0;
        //      printf("check1\n");
        // fflush(stdout);
        //  usleep(300000);
        if ((turns % 2) == 1)
        {
            printf("Your turn:\n");
            char bombc[4];
            scanf("%3s", bombc);
            if (bombc[0] == '*')
            {
                if (ATP == 1)
                {
                    int bomba;
                    bomba = atoi(bombc + 1);
                    if ((bomba >= 11 && bomba <= 18) || (bomba >= 21 && bomba <= 28) || (bomba >= 31 && bomba <= 38) || (bomba >= 41 && bomba <= 48) || (bomba >= 51 && bomba <= 58) || (bomba >= 61 && bomba <= 68) || (bomba >= 71 && bomba <= 78) || (bomba >= 81 && bomba <= 88))
                    {
                        if (map2[bomba] != 'R')
                        {
                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba - 11 + k] == 'S')
                                {
                                    map3[bomba - 11 + k] = 'X';
                                    map2[bomba - 11 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba - 11 + k] == '-')
                                {
                                    map3[bomba - 11 + k] = 'O';
                                    map2[bomba - 11 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba - 1 + k] == 'S')
                                {
                                    map3[bomba - 1 + k] = 'X';
                                    map2[bomba - 1 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba - 1 + k] == '-')
                                {
                                    map3[bomba - 1 + k] = 'O';
                                    map2[bomba - 1 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba + 9 + k] == 'S')
                                {
                                    map3[bomba + 9 + k] = 'X';
                                    map2[bomba + 9 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba + 9 + k] == '-')
                                {
                                    map3[bomba + 9 + k] = 'O';
                                    map2[bomba + 9 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            ATP--;
                            // printf("%d", SCL);

                            if (flagAP == 1)
                            {
                                printf("you hit!\n");
                                if (SCL <= 0)
                                {
                                    NamayesheMap(map1, map3);
                                    break;
                                }
                                else
                                {
                                    NamayesheMap(map1, map3);
                                    continue;
                                }
                            }
                            else
                            {
                                printf("you missed!\n");
                                NamayesheMap(map1, map3);
                                turns--;
                                continue;
                            }
                        }
                        else
                        {
                            printf("wrong input.\n");
                            continue;
                        }
                    }
                    else
                    {
                        printf("wrong input.\n");
                        continue;
                    }
                }
                else
                {
                    printf("ERROR. You already used your Nuclear bomb.\n");
                    continue;
                }
            }
            else
            {
                int bomb;
                bomb = atoi(bombc);

                if (bomb >= 0 && bomb < 100)
                    ;
                else
                {
                    //  printf("problem is here");
                    flag = 1;
                }
                if (map2[bomb] == 'R')
                {
                    //  printf("prolem is there");
                    flag = 1;
                }

                if (flag == 1)
                {
                    printf("wrong input.\n");
                    continue;
                }
                else
                {
                    if (map2[bomb] == 'S')
                    {
                        map3[bomb] = 'X';
                        map2[bomb] = 'R';
                        printf("You Hit!\n");
                        SCL--;
                        NamayesheMap(map1, map3);
                        if (SCL == 0)
                            break;
                        // exit(0);
                        // /// kar darad

                        else
                            continue;
                    }
                    else
                    {
                        map2[bomb] = 'R';
                        map3[bomb] = 'O';
                        turns--;
                        printf("You missed!\n");
                        NamayesheMap(map1, map3);
                        continue;
                    }
                }
            }
        }

        else
        {
            // printf("check2\n");
            fflush(stdout);
            usleep(700000);
            int randm;
            //  int bomba;
            //  int randbomba = rand()%64;
            //   bomba = 11 + (randbomba / 8) * 10 + (randbomba % 8);
            printf("Computer's Turn:\n");
            // printf("%d", bomb);
            if (ATC == 1)
            {
                int count[100];
                int i;
                for (i = 0; i < 64; i++)
                {
                    int z = (((i / 8) * 10) + (i % 8) + 11);
                    //	printf("%d\n", z);
                    //	fflush(stdout);
                    //	usleep(400000);
                    int counts = 0;
                    if (map1[z - 11] == 'S')
                        counts++;
                    if (map1[z - 10] == 'S')
                        counts++;
                    if (map1[z - 9] == 'S')
                        counts++;
                    if (map1[z - 1] == 'S')
                        counts++;
                    if (map1[z] == 'S')
                        counts++;
                    if (map1[z + 1] == 'S')
                        counts++;
                    if (map1[z + 9] == 'S')
                        counts++;
                    if (map1[z + 10] == 'S')
                        counts++;
                    if (map1[z + 11] == 'S')
                        counts++;
                    count[z] = counts;
                }
                int max = count[11];
                int bomba;
                for (i = 1; i < 64; i++)
                {
                    int x = (((i / 8) * 10) + (i % 8) + 11);
                    if (count[x] > max)
                    {
                        max = count[x];
                        bomba = x;
                    }
                }
                // printf("THE BOMB IS: %d\n" , bomba);
                if (ATC == 1)
                {

                    for (int k = 0; k < 3; k++)
                    {
                        map4[bomba - 11 + k] = 'R';
                        if (map1[bomba - 11 + k] == 'S')
                        {
                            map1[bomba - 11 + k] = 'X';
                            map4[bomba - 11 + k] = 'R';
                            flagAT = 1;
                            SPL--;
                        }
                        else if (map1[bomba - 11 + k] == '-')
                        {
                            map1[bomba - 11 + k] = 'O';
                            map4[bomba - 11 + k] = 'R';
                        }
                        else
                            ;
                    }

                    for (int k = 0; k < 3; k++)
                    {
                        map4[bomba - 1 + k] = 'R';
                        if (map1[bomba - 1 + k] == 'S')
                        {
                            map1[bomba - 1 + k] = 'X';
                            map4[bomba - 1 + k] = 'R';
                            flagAT = 1;
                            SPL--;
                        }
                        else if (map1[bomba - 1 + k] == '-')
                        {
                            map1[bomba - 1 + k] = 'O';
                            map4[bomba - 1 + k] = 'R';
                        }
                        else
                            ;
                    }

                    for (int k = 0; k < 3; k++)
                    {
                        map4[bomba + 9 + k] = 'R';
                        if (map1[bomba + 9 + k] == 'S')
                        {
                            map1[bomba + 9 + k] = 'X';
                            map4[bomba + 9 + k] = 'R';
                            flagAT = 1;
                            SPL--;
                        }
                        else if (map1[bomba + 9 + k] == '-')
                        {
                            map1[bomba + 9 + k] = 'O';
                            map4[bomba + 9 + k] = 'R';
                        }
                        else
                            ;
                    }

                    ATC--;

                    if (flagAT == 1)
                    {
                        printf("computer hit!\n");
                        NamayesheMap(map1, map3);
                        continue;
                    }
                    else
                    {
                        printf("computer missed!\n");
                        NamayesheMap(map1, map3);
                        turns--;
                    }
                }
                for (int k = 0; k < 3; k++)
                {
                    map4[bomba - 11 + k] = 'R';
                    if (map1[bomba - 11 + k] == 'S')
                    {
                        map1[bomba - 11 + k] = 'X';
                        map4[bomba - 11 + k] = 'R';
                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba - 11 + k] == '-')
                    {
                        map1[bomba - 11 + k] = 'O';
                        map4[bomba - 11 + k] = 'R';
                    }
                    else
                        ;
                }

                for (int k = 0; k < 3; k++)
                {
                    map4[bomba - 1 + k] = 'R';
                    if (map1[bomba - 1 + k] == 'S')
                    {
                        map1[bomba - 1 + k] = 'X';
                        map4[bomba - 1 + k] = 'R';
                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba - 1 + k] == '-')
                    {
                        map1[bomba - 1 + k] = 'O';
                        map4[bomba - 1 + k] = 'R';
                    }
                    else
                        ;
                }

                for (int k = 0; k < 3; k++)
                {
                    map4[bomba + 9 + k] = 'R';
                    if (map1[bomba + 9 + k] == 'S')
                    {
                        map1[bomba + 9 + k] = 'X';
                        map4[bomba + 9 + k] = 'R';
                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba + 9 + k] == '-')
                    {
                        map1[bomba + 9 + k] = 'O';
                        map4[bomba + 9 + k] = 'R';
                    }
                    else
                        ;
                }

                ATC--;

                if (flagAT == 1)
                {
                    printf("computer hit!\n");
                    NamayesheMap(map1, map3);
                    continue;
                }
                else
                {
                    printf("computer missed!\n");
                    NamayesheMap(map1, map3);
                    turns--;
                }
            }

            else
            {
                //       printf("check3\n");
                randm = rand() % 3;
                //             printf("check4\n");
                //    printf("randm is %d\n", randm);
                if (randm != 3)
                {
                    while (1)
                    {
                        int randshot = rand() % 20;
                        if (map4[s[randshot]] != 'R')
                        {
                            map4[s[randshot]] = 'R';
                            map1[s[randshot]] = 'X';
                            SPL--;
                            //         printf("spot is: %d and spl is %d and randshot is %d\n", s[randshot], SPL, randshot );
                            printf("computer hit!\n");
                            NamayesheMap(map1, map3);
                            break;
                        }
                        else
                            continue;
                    }

                    continue;
                }

                else
                {
                    while (1)
                    {
                        int randshot = rand() % 80;
                        if (map4[o[randshot]] != 'R')
                        {
                            map4[o[randshot]] = 'R';
                            map1[o[randshot]] = 'O';
                            turns--;
                            //        printf("spot is: %d and spl is %d and randshot is %d\n", o[randshot], SPL, randshot );
                            printf("computer missed!\n");
                            NamayesheMap(map1, map3);
                            break;
                        }
                        else
                            continue;
                    }
                    continue;
                }
            }
        }
        /*
        if (map4[bomb]=='R')
            continue;
        else if (map1[bomb]=='S') {
            map1[bomb]='X';
            map4[bomb]='R';
            printf("Computer Hit!\n");
            NamayesheMap(map1 , map3);
            SPL--;
            if(SPL==0)
                break;
               // return SCL;
              //  /// payane bazi.
            else
            continue; }
        else{
            map1[bomb]='O';
            map4[bomb]='R';
            turns--;
            printf("Computer missed!\n");
            NamayesheMap(map1 , map3);
            continue;
        } */
    }

    //

    if (SPL > SCL)
    {

        return SPL;
    }
    else
    {
        fr = fr + SCL;
        return fr;
    }

    //   }
}

int easygame()
{
    int SPL = 20;
    int SCL = 20;
    int ATC = 1;
    int fr = 100;
    int flag = 0;
    int ATP = 1;
    int flagAT = 0;
    int flagAP = 0;
    int turns = 1001;
    srand(time(NULL));
    printf("Enter your ships in 10 lines. each line includes there\n        start spot (from 0 to 99)\n       and direction of the ship (U, R, D, L)\nfor example: 11 3 R\n");
    GozashtanKeshti1(map1);
    printf("Enter computer's ships in 10 lines. each line includes there\n        start spot (from 0 to 99)\n       and direction of the ship (U, R, D, L)\nfor example: 11 3 R\n");
    GozashtanKeshti1(map2);
    NamayesheMap(map1, map3);
    while (SPL > 0 && SCL > 0)
    {
        flag = 0;
        fflush(stdout);
        usleep(300000);
        if ((turns % 2) == 1)
        {
            printf("Your turn:\n");
            char bombc[4];
            scanf("%3s", bombc);
            if (bombc[0] == '*')
            {
                if (ATP == 1)
                {
                    int bomba;
                    bomba = atoi(bombc + 1);
                    if ((bomba >= 11 && bomba <= 18) || (bomba >= 21 && bomba <= 28) || (bomba >= 31 && bomba <= 38) || (bomba >= 41 && bomba <= 48) || (bomba >= 51 && bomba <= 58) || (bomba >= 61 && bomba <= 68) || (bomba >= 71 && bomba <= 78) || (bomba >= 81 && bomba <= 88))
                    {
                        if (map2[bomba] != 'R')
                        {
                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba - 11 + k] == 'S')
                                {
                                    map3[bomba - 11 + k] = 'X';
                                    map2[bomba - 11 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba - 11 + k] == '-')
                                {
                                    map3[bomba - 11 + k] = 'O';
                                    map2[bomba - 11 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba - 1 + k] == 'S')
                                {
                                    map3[bomba - 1 + k] = 'X';
                                    map2[bomba - 1 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba - 1 + k] == '-')
                                {
                                    map3[bomba - 1 + k] = 'O';
                                    map2[bomba - 1 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            for (int k = 0; k < 3; k++)
                            {
                                if (map2[bomba + 9 + k] == 'S')
                                {
                                    map3[bomba + 9 + k] = 'X';
                                    map2[bomba + 9 + k] = 'R';
                                    flagAP = 1;
                                    SCL--;
                                }
                                else if (map2[bomba + 9 + k] == '-')
                                {
                                    map3[bomba + 9 + k] = 'O';
                                    map2[bomba + 9 + k] = 'R';
                                }
                                else
                                    ;
                            }

                            ATP--;
                            // printf("%d", SCL);

                            if (flagAP == 1)
                            {
                                printf("you hit!\n");
                                if (SCL <= 0)
                                {
                                    NamayesheMap(map1, map3);
                                    break;
                                }
                                else
                                {
                                    NamayesheMap(map1, map3);
                                    continue;
                                }
                            }
                            else
                            {
                                printf("you missed!\n");
                                NamayesheMap(map1, map3);
                                turns--;
                                continue;
                            }
                        }
                        else
                        {
                            printf("wrong input.\n");
                            continue;
                        }
                    }
                    else
                    {
                        printf("wrong input.\n");
                        continue;
                    }
                }
                else
                {
                    printf("ERROR. You already used your Nuclear bomb.\n");
                    continue;
                }
            }
            else
            {
                int bomb;
                bomb = atoi(bombc);

                if (bomb >= 0 && bomb < 100)
                    ;
                else
                {
                    //  printf("problem is here");
                    flag = 1;
                }
                if (map2[bomb] == 'R')
                {
                    //  printf("prolem is there");
                    flag = 1;
                }

                if (flag == 1)
                {
                    printf("wrong input.\n");
                    continue;
                }
                else
                {
                    if (map2[bomb] == 'S')
                    {
                        map3[bomb] = 'X';
                        map2[bomb] = 'R';
                        printf("You Hit!\n");
                        SCL--;
                        NamayesheMap(map1, map3);
                        if (SCL == 0)
                            break;
                        // exit(0);
                        // /// kar darad

                        else
                            continue;
                    }
                    else
                    {
                        map2[bomb] = 'R';
                        map3[bomb] = 'O';
                        turns--;
                        printf("You missed!\n");
                        NamayesheMap(map1, map3);
                        continue;
                    }
                }
            }
        }

        else
        {
            fflush(stdout);
            usleep(700000);
            int bomb;
            int bomba;
            int randbomba = rand() % 64;
            bomba = 11 + (randbomba / 8) * 10 + (randbomba % 8);
            printf("Computer's Turn:\n");
            // printf("%d", bomb);
            if (ATC == 1)
            {

                for (int k = 0; k < 3; k++)
                {
                    map4[bomba - 11 + k] = 'R';
                    if (map1[bomba - 11 + k] == 'S')
                    {
                        map1[bomba - 11 + k] = 'X';
                        map4[bomba - 11 + k] = 'R';

                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba - 11 + k] == '-')
                    {
                        map1[bomba - 11 + k] = 'O';
                        map4[bomba - 11 + k] = 'R';
                    }
                    else
                        ;
                }

                for (int k = 0; k < 3; k++)
                {
                    map4[bomba - 1 + k] = 'R';
                    if (map1[bomba - 1 + k] == 'S')
                    {
                        map1[bomba - 1 + k] = 'X';
                        map4[bomba - 1 + k] = 'R';
                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba - 1 + k] == '-')
                    {
                        map1[bomba - 1 + k] = 'O';
                        map4[bomba - 1 + k] = 'R';
                    }
                    else
                        ;
                }

                for (int k = 0; k < 3; k++)
                {
                    map4[bomba + 9 + k] = 'R';
                    if (map1[bomba + 9 + k] == 'S')
                    {
                        map1[bomba + 9 + k] = 'X';
                        map4[bomba + 9 + k] = 'R';
                        flagAT = 1;
                        SPL--;
                    }
                    else if (map1[bomba + 9 + k] == '-')
                    {
                        map1[bomba + 9 + k] = 'O';
                        map4[bomba - 11 + k] = 'R';
                    }
                    else
                        ;
                }

                ATC--;

                if (flagAT == 1)
                {
                    printf("computer hit!\n");
                    NamayesheMap(map1, map3);
                    continue;
                }
                else
                {
                    printf("computer missed!\n");
                    NamayesheMap(map1, map3);
                    turns--;
                }
            }

            else
            {
                while (1)
                {
                    bomb = rand() % 100;
                    //  printf("bomb is %d\n" , bomb);
                    if (map4[bomb] == 'R')
                        continue;
                    else if (map1[bomb] == 'S')
                    {
                        map1[bomb] = 'X';
                        map4[bomb] = 'R';
                        printf("Computer Hit!\n");
                        NamayesheMap(map1, map3);
                        SPL--;
                        if (SPL == 0)
                            break;
                        // return SCL;
                        //  /// payane bazi.
                        else
                            break;
                    }
                    else
                    {
                        map1[bomb] = 'O';
                        map4[bomb] = 'R';
                        turns--;
                        printf("Computer missed!\n");
                        NamayesheMap(map1, map3);
                        break;
                    }
                }
                continue;
            }
        }
    }
    //

    if (SPL > SCL)
    {

        return SPL;
    }
    else
    {
        fr = fr + SCL;
        return fr;
    }

    //   }
}

void menu()
{
    int s1 = 0, s2 = 0;
    while (1)
    {
        printf("Menu\n1/Start_round\n2/Exit\nEnter your choice:\n");

        char answer[15];
        scanf("%s", &answer);
        if (strcmp(answer, "Start_round") == 0)
        {
            while (1)
            {
                // level choice
                printf("Your Team:     %d\nComputer Team: %d\nEnter a level (easy, normal, hard, unbeatable):", s1, s2);
                char answer[15];
                scanf("%s", &answer);
                if (strcmp(answer, "normal") == 0)
                {
                    int result = normalgame();
                    if (result / 100 == 1)
                        s2 = s2 + result - 100;
                    else
                        s1 = s1 + result;
                    system("cls");
                    // printf("%d\n", result);
                    printf("Your Team:     %d\nComputer Team: %d\n", s1, s2);
                    TarifeMap(map1);
                    TarifeMap(map2);
                    TarifeMap(map3);
                    TarifeMap(map4);
                    break;
                    // system("cls");
                }
                else if (strcmp(answer, "hard") == 0)
                {
                    int result = hardgame();
                    if (result / 100 == 1)
                        s2 = s2 + result - 100;
                    else
                        s1 = s1 + result;
                    system("cls");
                    // printf("%d\n", result);
                    printf("Your Team:     %d\nComputer Team: %d\n", s1, s2);
                    TarifeMap(map1);
                    TarifeMap(map2);
                    TarifeMap(map3);
                    TarifeMap(map4);
                    break;
                    // system("cls");
                }
                else
                {
                    if (strcmp(answer, "unbeatable") == 0)
                    {
                        int result = unbeatablegame();
                        if (result / 100 == 1)
                            s2 = s2 + result - 100;
                        else
                            s1 = s1 + result;
                        system("cls");
                        // printf("%d\n", result);
                        printf("Your Team:     %d\nComputer Team: %d\n", s1, s2);
                        TarifeMap(map1);
                        TarifeMap(map2);
                        TarifeMap(map3);
                        TarifeMap(map4);
                        break;
                        // system("cls");
                    }
                    else if (strcmp(answer, "easy") == 0)
                    {
                        int result = easygame();
                        if (result / 100 == 1)
                            s2 = s2 + result - 100;
                        else
                            s1 = s1 + result;
                        system("cls");
                        // printf("%d\n", result);
                        printf("Your Team:     %d\nComputer Team: %d\n", s1, s2);
                        TarifeMap(map1);
                        TarifeMap(map2);
                        TarifeMap(map3);
                        TarifeMap(map4);
                        break;
                        // system("cls");
                    }
                    else
                        continue;
                }
            }
        }
        else if (strcmp(answer, "Exit") == 0)
        {
            system("cls");
            printf("Your Team:     %d\nComputer Team: %d\n", s1, s2);
            if (s1 > s2)
                printf("YOU WIN THE GAME.\n");
            else if (s2 > s1)
                printf("COMPUTER WIN THE GAME.\n");
            else
                printf("IT'S A DRAW.\n");
            exit(0);
        }
        else
            menu();
    }
}

int main()
{
    TarifeMap(map1);
    TarifeMap(map2);
    TarifeMap(map3);
    TarifeMap(map4);
    menu();
    //   printf("alright your placement turn\n");

    // GozashtanKeshti1(map1);
    //    printf("alright computer's placement turn\n");

    // GozashtanKeshti1(map2);
    // NamayesheMap(map1 , map3);
}
