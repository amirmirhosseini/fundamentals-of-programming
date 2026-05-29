#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define ms 20

void hide_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int food_pos(int* snake1, int len_snake1, int* snake2 , int len_snake2) {
    int pos, valid;
    while (1) {
        pos = rand() % (ms * ms);
        valid = 1;
        for (int i = 0; i < len_snake1; i++) {
            if (pos == snake1[i]) {
                valid = 0;
                break;
            }
        }
        for (int i = 0; i < len_snake2; i++) {
            if (pos == snake2[i]) {
                valid = 0;
                break;
            }
        }
        if (valid) break;
    }
    return pos;
}

int encode_coord(int i, int j) {
    return i * ms + j;
}

int* decode_coord(int code) {
    static int pos[2];
    pos[0] = code / ms;
    pos[1] = code % ms;
    return pos;
}

void place_food(char map[ms][ms], int foodpos) {
    int* pos = decode_coord(foodpos);
    map[pos[0]][pos[1]] = '$';
}

void players_point(int num, int len_snake){
    int pts = (len_snake-1)*10;
    printf("PLAYER <%d> SCORE: %d\n",num,pts);
}

void display_map(char map[ms][ms],int len_snake1, int len_snake2, double time) {
    for (int i = 0; i < ms + 2; i++) printf("#");
    for (int i = 0; i < ms; i++) {
        printf("\n#");
        for (int j = 0; j < ms; j++) {
            printf("%c", map[i][j]);
        }
        printf("#");
    }
    printf("\n");
    for (int i = 0; i < ms + 2; i++) printf("#");
    printf("\n");
    players_point(1,len_snake1);
    players_point(2,len_snake2);
    printf("time: %ds\n",(int)floor(time));
}

void initialize_map(char map[ms][ms]) {
    for (int i = 0; i < ms; i++)
        for (int j = 0; j < ms; j++)
            map[i][j] = ' ';
}

void snake_on_map(char map[ms][ms], int* snake, int len_snake, int num) {
    int* pos = decode_coord(snake[0]);
    if(num==1){
    map[pos[0]][pos[1]] = 'O';
    for (int i = 1; i < len_snake; i++) {
        int* pos = decode_coord(snake[i]);
        map[pos[0]][pos[1]] = i == 0 ? 'O' : 'o';
    }}
    else{
    map[pos[0]][pos[1]] = 'X';
    for (int i = 1; i < len_snake; i++) {
        int* pos = decode_coord(snake[i]);
        map[pos[0]][pos[1]] = i == 0 ? 'X' : 'x';
    }
    }
}

void movement_snake(char direction, int* snake, int len_snake) {
    for (int i = len_snake - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    switch (direction) {
        case 'w': snake[0] -= encode_coord(1, 0); break;
        case 's': snake[0] += encode_coord(1, 0); break;
        case 'd': snake[0] += encode_coord(0, 1); break;
        case 'a': snake[0] -= encode_coord(0, 1); break;
    }
}

int* snake_resize(int* snake, int* len_snake) {
    (*len_snake)++;
    int* temp = realloc(snake, (*len_snake) * sizeof(int));
    if (temp == NULL) return snake; // fallback
    temp[*len_snake - 1] = temp[*len_snake - 2];
    return temp;
}

void check_eat(int** snake1, int* foodpos, int* len_snake1, int** snake2 , int* len_snake2  ) {
    if ((*snake1)[0] == *foodpos) {
        *snake1 = snake_resize(*snake1, len_snake1);
        *foodpos = food_pos(*snake1, *len_snake1,*snake2 , *len_snake2);
    }

    if ((*snake2)[0] == *foodpos) {
        *snake2 = snake_resize(*snake2, len_snake2);
        *foodpos = food_pos(*snake1, *len_snake1,*snake2 , *len_snake2);
    }
}

void changing_direction(char* direction, char* direction2) {
    if (GetAsyncKeyState('W') & 0x8000) {
        if (*direction == 'a' || *direction == 'd') *direction = 'w';
    } else if (GetAsyncKeyState('S') & 0x8000) {
        if (*direction == 'a' || *direction == 'd') *direction = 's';
    } else if (GetAsyncKeyState('A') & 0x8000) {
        if (*direction == 'w' || *direction == 's') *direction = 'a';
    } else if (GetAsyncKeyState('D') & 0x8000) {
        if (*direction == 'w' || *direction == 's') *direction = 'd';
    }

    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        if (*direction2 == 'a' || *direction2 == 'd') *direction2 = 'w';
    } else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        if (*direction2 == 'a' || *direction2 == 'd') *direction2 = 's';
    } else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        if (*direction2 == 'w' || *direction2 == 's') *direction2 = 'a';
    } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        if (*direction2 == 'w' || *direction2 == 's') *direction2 = 'd';
    }
}

void hit_wall(int* loser, int snake, char direction, int num) {
    int* pos = decode_coord(snake);
    if ((direction == 'w' && pos[0] == 0) ||
        (direction == 's' && pos[0] == ms - 1) ||
        (direction == 'a' && pos[1] == 0) ||
        (direction == 'd' && pos[1] == ms - 1)) {
        *loser = num;
    }
}

void who_won(int loser, int len1 , int len2) {
    if (loser == 1) {
        printf("\nPLAYER 2 WON.\n");
    }
    else if (loser == 2){
        printf("\nPLAYER 1 WON.\n");
    }
    else if (loser == 3){
        if(len1 > len2){
            printf("\nPLAYER 1 WON.\n");
        }
        else if(len2 > len1){
            printf("\nPLAYER 2 WON.\n");
        }
        else{
            printf("\nIT'S A DRAW.\n");
        }
    }
}


void hit_self(int* loser, int* snake, int len_snake, int num){
    for(int i = 1; i < len_snake; i++){
        if(snake[0] == snake[i]){
            *loser = num;
            break;
        }
    }
}

void hit_enemy(int* loser, int* snake, int len_snake, int hitted_by_num, int* hitted_snake , int len_hitted_snake){
        for(int i = 1; i < len_hitted_snake; i++){
        if(snake[0] == hitted_snake[i]){
            *loser = hitted_by_num;
            break;
        }
    }
}
void check_head(int* loser, int* snake1, int* snake2) {

    if (snake1[0] == snake2[0]) {
    *loser = 3;
    }}

void check_time(int*loser, double time){
if(time>50)
{
    *loser=3;
    printf("TIME IS UP!\n");
}
}

void map_managing(char map[ms][ms], char* direction, int** snake1, int* foodpos, int* game_running, int* loser, int* len_snake1,
                  char* direction2, int** snake2, int* len_snake2, clock_t start) {
    clock_t current = clock();
    double time = (double)(current - start) / CLOCKS_PER_SEC;

    changing_direction(direction, direction2);
    check_time(loser, time);
    hit_wall(loser, (*snake1)[0], *direction,1);
    hit_wall(loser, (*snake2)[0], *direction2,2);
    if (*loser != 0) {
        *game_running = 0;
        return;
    }

    movement_snake(*direction, *snake1, *len_snake1);
    movement_snake(*direction2, *snake2, *len_snake2);

    check_head(loser, *snake1, *snake2);
    hit_self(loser, *snake1, *len_snake1,1);
    hit_self(loser, *snake2, *len_snake2,2);
    hit_enemy(loser, *snake1, *len_snake1, 1, *snake2, *len_snake2);
    hit_enemy(loser, *snake2, *len_snake2, 2, *snake1, *len_snake1);

    if (*loser != 0) {
        *game_running = 0;
        return;
    }

    initialize_map(map);
    snake_on_map(map, *snake1, *len_snake1,1);
    snake_on_map(map, *snake2, *len_snake2,2);
    check_eat(snake1, foodpos, len_snake1, snake2, len_snake2);

    place_food(map, *foodpos);
    system("cls");
    display_map(map, *len_snake1, *len_snake2, time);
}


int main() {
    srand(time(NULL));
    hide_cursor();

    char map[ms][ms];
    initialize_map(map);

    int len_snake1 = 1 , len_snake2=1;
    int loser = 0;
    int start_pos[2] = {10, 4};
    int start_pos2[2] = {11, 15};

    int* snake1 = malloc(sizeof(int));
    snake1[0] = encode_coord(start_pos[0], start_pos[1]);

    int* snake2 = malloc(sizeof(int));
    snake2[0] = encode_coord(start_pos2[0], start_pos2[1]);

    char direction = 0 , direction2 = 0;
    int foodpos = food_pos(snake1, len_snake1,snake2,len_snake2);
    place_food(map, foodpos);
    map[start_pos[0]][start_pos[1]] = 'O';
    map[start_pos2[0]][start_pos2[1]] = 'X';

    display_map(map,len_snake1,len_snake2,0);
    printf("PRESS DIRECTION KEYS TO START.\n");
    printf("controlling 1st snake (O) with: [W A S D] keys. controlling 2nd snake (X) with: arrow keys.\n$ is the food that increases your score and lengthens your snake.\n");
    printf("If the game lasts more than 50 seconds, the player with the higher score wins.\n");

    do {
        if (GetAsyncKeyState('W') & 0x8000) direction = 'w';
        else if (GetAsyncKeyState('A') & 0x8000) direction = 'a';
        else if (GetAsyncKeyState('S') & 0x8000) direction = 's';
        else if (GetAsyncKeyState('D') & 0x8000) direction = 'd';
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) direction = 'a';
        else if (GetAsyncKeyState(VK_UP) & 0x8000) direction = 'w';
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) direction = 's';
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) direction = 'd';
        direction2 = direction;



        Sleep(50);
    } while (direction == 0);
    clock_t start = clock();
    int game_running = 1;
    while (game_running) {
        map_managing(map, &direction, &snake1, &foodpos, &game_running, &loser, &len_snake1, &direction2, &snake2, &len_snake2, start);
        Sleep(150);
    }

    who_won(loser, len_snake1, len_snake2);
    Sleep(10000);
    free(snake1);
    free(snake2);
    return 0;
}
