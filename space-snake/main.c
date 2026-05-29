#include <stdio.h>
#include <SDL2/SDL.h>
#include<time.h>
#include <math.h>


void handle_events(SDL_Event* e, int* running, char* direction, char* direction2){
    while(SDL_PollEvent(e)){
        if (e->type == SDL_QUIT){
            *running=0;
        }
        else if (e->type == SDL_KEYDOWN){
            switch(e->key.keysym.sym){
                case SDLK_w:
                    if (*direction == 'a' || *direction == 'd') *direction = 'w';
                    break;
                case SDLK_s:
                    if (*direction == 'a' || *direction == 'd') *direction = 's';
                    break;
                case SDLK_a:
                    if (*direction == 'w' || *direction == 's') *direction = 'a';
                    break;
                case SDLK_d:
                    if (*direction == 'w' || *direction == 's') *direction = 'd';
                    break;
                
                
                case SDLK_UP:
                    if (*direction2 == 'a' || *direction2 == 'd') *direction2 = 'w';
                    break;
                case SDLK_DOWN:
                    if (*direction2 == 'a' || *direction2 == 'd') *direction2 = 's';
                    break;
                case SDLK_LEFT:
                    if (*direction2 == 'w' || *direction2 == 's') *direction2 = 'a';
                    break;
                case SDLK_RIGHT:
                    if (*direction2 == 'w' || *direction2 == 's') *direction2 = 'd';
                    break;
            }
        }
    }
}

void show_points(SDL_Renderer* renderer, SDL_Texture** digits, int len_snake, int len_snake2, SDL_Texture* head, SDL_Texture* head2)
{
    int point1 = (len_snake-1)*10;
    int point2 = (len_snake2-1)*10;
    char p1[5];
    char p2[5];
    sprintf(p1, "%04d", point1);
    sprintf(p2, "%04d", point2);
    SDL_Rect s1 ={29, 687-39 , 29 , 29};
    SDL_Rect s2= {29*12, 687-39 , 29 , 29};
    SDL_RenderCopy(renderer, head, NULL, &s1);
    SDL_RenderCopy(renderer, head2, NULL, &s2);
    for(int i = 0 ; i<4 ; i++){
        SDL_Rect num = {29*(i+3), 687-39, 29, 29};
        int j = p1[i] - '0';
        SDL_RenderCopy(renderer, digits[j], NULL, &num);
    }

    for(int i = 0 ; i<4 ; i++){
        SDL_Rect num = {29*(i+14), 687-39, 29, 29};
            int j = p2[i] - '0';
        SDL_RenderCopy(renderer, digits[j], NULL, &num);
    }
}

void set_rect_position(SDL_Rect* rect, int x, int y) {
    rect->x = x;
    rect->y = y;
}

void movement_snake(SDL_Rect* head, SDL_Rect* body, char direction, int len_snake){
    if(len_snake>1){
        for(int i = len_snake - 1 ; i>0; i--)
        {
            set_rect_position(&body[i], body[i-1].x , body[i-1].y);
        }
        set_rect_position(&body[0], head->x , head->y);

    }
    switch(direction){
        case 'w': head->y-=29; break;
        case 'a': head->x-=29; break;
        case 's': head->y+=29; break;
        case 'd': head->x+=29; break;
    }
}

void food_pos(SDL_Rect* head, SDL_Rect* head2, SDL_Rect* body, SDL_Rect* body2, SDL_Rect* food , int len_snake , int len_snake2){
    int posx, posy, valid;
    while(1){
        posx = 29*(rand()%20+1);
        posy = 29*(rand()%20+1);
        valid=1;
        for(int i = 0 ; i<len_snake-1 ; i++){
            if((posx == body[i].x)&&(posy == body[i].y)){
                valid = 0;
            }
        }
        for(int i = 0 ; i<len_snake2-1 ; i++){
            if((posx == body2[i].x)&&(posy == body2[i].y)){
                valid = 0;
            }
        }
        if((posx == head->x)&&(posy == head->y)){
                valid = 0;
        }
        if((posx == head2->x)&&(posy == head2->y)){
                valid = 0;
        }

        if (valid) break;
    }
    food->x= posx;
    food->y= posy;
}

SDL_Rect* body_resize(SDL_Rect* body, int* len_snake, SDL_Rect* head){
    *len_snake+=1;
    body = (SDL_Rect*)realloc(body, (*len_snake-1) * sizeof(SDL_Rect));
    if(*len_snake>2){
        body[*len_snake-2] = body[*len_snake-3];
    }
    else{
        body[0].w = 29; body[0].h=29;
        body[0].x = head->x;
        body[0].y = head->y;
    }
    return body;
}

void check_enemy(SDL_Rect* head, SDL_Rect* head2, SDL_Rect* body, SDL_Rect* body2, int* loser, int len_snake, int len_snake2){
    for(int i = 0 ; i<len_snake2-1 ; i++){
        if((head->x==body2[i].x)&&(head->y==body2[i].y)){
            *loser=1;
            printf("lol enemy.\n");
            break;
        }
    }
    for(int i = 0 ; i<len_snake-1 ; i++){
        if((head2->x==body[i].x)&&(head2->y==body[i].y)){
            *loser=2;
            printf("lol enemy2.\n");
            break;
        }
    }    
}

void check_self(SDL_Rect* head, SDL_Rect* body, int* loser, int len_snake, int num){
    for(int i = 0 ; i < len_snake-1 ; i++){
        if((head->x==body[i].x)&&(head->y==body[i].y)){
            printf("lol self %d.\n",num);
            *loser = num;
            break;
        }
    }
}

void check_wall(SDL_Rect* head, int num, int *loser, SDL_Rect* ghost){
    for(int i = 0 ; i<84 ; i++){
        if((ghost[i].x==head->x)&&(ghost[i].y==head->y)){
            printf("lol wall %d.\n",num);
            *loser = num;
            break;
        }
    }
}

void check_head(SDL_Rect* head, SDL_Rect* head2, int *loser){
        if((head2->x==head->x)&&(head2->y==head->y)){
            printf("lol head.\n");
        *loser = 3;
    }
}

void check_eat(SDL_Rect* head, SDL_Rect* head2, SDL_Rect** body, SDL_Rect** body2, SDL_Rect* food, int* len_snake, int* len_snake2) {
    if ((head->x == food->x) && (head->y == food->y)) {
        *body = body_resize(*body, len_snake, head); 
        food_pos(head, head2, *body, *body2, food, *len_snake, *len_snake2);
    } else if ((head2->x == food->x) && (head2->y == food->y)) {
        *body2 = body_resize(*body2, len_snake2, head2); 
        food_pos(head, head2, *body, *body2, food, *len_snake, *len_snake2);
    }
}

void check_time(int*loser, double time){

    printf("current time: %d s\n",(int)floor(time));

if(time>50)
{
    *loser=4;
}
}

int main(int argc, char *argv[])
{
 /*   int width = 640 , height = 480, scale = 2;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    */
   
    const int WIDTH = 638, HEIGHT = 687;
    srand(time(NULL));
    int len_snake1 = 1 , len_snake2 = 1;
    int loser = 0;
    int start_pos[2] = {29*6,29*6}; int start_pos2[2] = {29*15,29*15};
    char direction = 0 , direction2 = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Player BMP",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    

    SDL_Surface* prebgSurface = SDL_LoadBMP("prebackground.bmp");
    SDL_Texture* prebgTexture = SDL_CreateTextureFromSurface(renderer, prebgSurface);
    SDL_FreeSurface(prebgSurface);

    SDL_Surface* bgSurface = SDL_LoadBMP("background.bmp");

    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    SDL_Surface* head1 = SDL_LoadBMP("head1.bmp");
    SDL_Surface* body1 = SDL_LoadBMP("body1.bmp");
    SDL_Surface* food = SDL_LoadBMP("food.bmp");
    SDL_Surface* ghost = SDL_LoadBMP("ghost.bmp");
    SDL_Surface* body2 = SDL_LoadBMP("body2.bmp");
    SDL_Surface* head2 = SDL_LoadBMP("head2.bmp");


    Uint32 colorkey = SDL_MapRGB(head1->format, 255, 255, 255);
    SDL_SetColorKey(head1, SDL_TRUE, colorkey);
    
    colorkey = SDL_MapRGB(body1->format, 255, 255, 255);
    SDL_SetColorKey(body1, SDL_TRUE, colorkey);

    colorkey = SDL_MapRGB(ghost->format, 255, 255, 255);
    SDL_SetColorKey(ghost, SDL_TRUE, colorkey);

    colorkey = SDL_MapRGB(food->format, 255, 255, 255);
    SDL_SetColorKey(food, SDL_TRUE, colorkey);

    colorkey = SDL_MapRGB(head2->format, 255, 255, 255);
    SDL_SetColorKey(head2, SDL_TRUE, colorkey);

    colorkey = SDL_MapRGB(body2->format, 255, 255, 255);
    SDL_SetColorKey(body2, SDL_TRUE, colorkey);

    char digitfilename[10];
    SDL_Texture* digits[10];
    for (int i = 0 ; i<10 ; i++){
        sprintf(digitfilename , "%d.bmp", i);
        SDL_Surface* randomsurface = SDL_LoadBMP(digitfilename);
        colorkey = SDL_MapRGB(randomsurface->format, 255,255,255);
        SDL_SetColorKey(randomsurface, SDL_TRUE, colorkey);
        digits[i] = SDL_CreateTextureFromSurface(renderer, randomsurface);
        SDL_FreeSurface(randomsurface);
    }

    SDL_Texture* head1Texture = SDL_CreateTextureFromSurface(renderer, head1);
    SDL_Texture* body1Texture = SDL_CreateTextureFromSurface(renderer, body1);
    SDL_Texture* ghostTexture = SDL_CreateTextureFromSurface(renderer, ghost);
    SDL_Texture* foodTexture = SDL_CreateTextureFromSurface(renderer, food);
    SDL_Texture* head2Texture = SDL_CreateTextureFromSurface(renderer, head2);
    SDL_Texture* body2Texture = SDL_CreateTextureFromSurface(renderer, body2);

    SDL_Rect playerHead1 = { start_pos[0], start_pos[1], head1->w, head1->h };
   // SDL_Rect playerBody1 = { 480, 100, body1->w , body1->h };
    SDL_Rect FOOD = { 550, 100, food->w , food->h };
    SDL_Rect playerHead2 = { start_pos2[0], start_pos2[1], head2->w, head2->h };
    //SDL_Rect playerBody2 = { 480, 200, body2->w , body2->h };
    SDL_Rect* playerBody1 = NULL;
    SDL_Rect* playerBody2 = NULL;

    food_pos(&playerHead1, &playerHead2, playerBody1, playerBody2, &FOOD, len_snake1, len_snake2); 

    const int GHOST_COUNT = 84;
    SDL_Rect GHOST[GHOST_COUNT];
    

    for(int i = 0 ; i<22 ; i++)
    {
        GHOST[i].x=29*i;
        GHOST[i].y=0;
        GHOST[i].w = ghost->w;
        GHOST[i].h = ghost->h;
    }
    for(int i = 22 ; i<42 ; i++)
    {
        GHOST[i].y=29*(i-21);
        GHOST[i].x=0;
        GHOST[i].w = ghost->w;
        GHOST[i].h = ghost->h;
    }
    for(int i = 42 ; i<64 ; i++)
    {

        GHOST[i].y=29*21;
        GHOST[i].x=29*(i-42);
        GHOST[i].w = ghost->w;
        GHOST[i].h = ghost->h;
    }
    for(int i = 64 ; i<84 ; i++)
    {

        GHOST[i].x=29*21;
        GHOST[i].y=29*(i-63);
        GHOST[i].w = ghost->w;
        GHOST[i].h = ghost->h;
    }

    // Free surfaces
    SDL_FreeSurface(head1);
    SDL_FreeSurface(ghost);
    SDL_FreeSurface(body1);
    SDL_FreeSurface(food);
    SDL_FreeSurface(head2);
    SDL_FreeSurface(body2);

    SDL_Rect bgRect = { 0, 0, WIDTH, HEIGHT };


    SDL_Event e;
    int running = 1 , firstLoop=1;
    while ((running==1)&&(firstLoop==1)) {
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running=0;
            }
            else if (e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case(SDLK_SPACE):
                        firstLoop = 0;
                        break;
                }
            }
        }
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, prebgTexture, NULL, &bgRect);

        SDL_RenderPresent(renderer);

        SDL_Delay(100); 

    }
    do{
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running=0;
            }
            else if (e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case(SDLK_UP):
                        direction='w';
                        break;
                    case(SDLK_w):
                        direction='w';
                        break;
                    case(SDLK_DOWN):
                        direction='s';
                        break;
                    case(SDLK_s):
                        direction='s';
                        break;
                    case(SDLK_RIGHT):
                        direction='d';
                        break;
                    case(SDLK_d):
                        direction='d';
                        break;
                    case(SDLK_LEFT):
                        direction='a';
                        break;
                    case(SDLK_a):
                        direction='a';
                        break;
                    default:
                        break;
                }
            }
        }
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, bgTexture, NULL, &bgRect);

        for(int i = 0; i < GHOST_COUNT; i++) {
            SDL_RenderCopy(renderer, ghostTexture, NULL, &GHOST[i]);
        }

        SDL_RenderCopy(renderer, head1Texture, NULL, &playerHead1);
        SDL_RenderCopy(renderer, head2Texture, NULL, &playerHead2);

        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    } while ((direction == 0)&&(running == 1));
    direction2 = direction;

    food_pos(&playerHead1, &playerHead2, playerBody1, playerBody2, &FOOD, len_snake1, len_snake2); 
    clock_t start = clock();
    clock_t current;
    while (running) {
        current = clock();
        double time = (double)(current - start) / CLOCKS_PER_SEC;

        handle_events(&e, &running, &direction, &direction2);
        movement_snake(&playerHead1, playerBody1, direction, len_snake1);
        movement_snake(&playerHead2, playerBody2, direction2, len_snake2);

        check_enemy(&playerHead1, &playerHead2, playerBody1, playerBody2, &loser, len_snake1, len_snake2);
        check_head(&playerHead1, &playerHead2, &loser);
        check_self(&playerHead1, playerBody1, &loser, len_snake1, 1);
        check_self(&playerHead2, playerBody2, &loser, len_snake2, 2);
        check_wall(&playerHead1, 1, &loser, GHOST);
        check_wall(&playerHead2, 2, &loser, GHOST);
        check_time(&loser, time);

        if(loser!=0){
            running=0;
            continue;
        }
        check_eat(&playerHead1, &playerHead2, &playerBody1, &playerBody2, &FOOD, &len_snake1, &len_snake2);

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, bgTexture, NULL, &bgRect);


        for(int i = 0; i < GHOST_COUNT; i++) {
            SDL_RenderCopy(renderer, ghostTexture, NULL, &GHOST[i]);
        }


        SDL_RenderCopy(renderer, head1Texture, NULL, &playerHead1);
        if(len_snake1>1)
        {
        for (int i = 0; i < len_snake1 - 1; i++) {
            SDL_RenderCopy(renderer, body1Texture, NULL, &playerBody1[i]);
        }
        }
        SDL_RenderCopy(renderer, head2Texture, NULL, &playerHead2);
        if(len_snake2>1)
        {
        for (int i = 0; i < len_snake2 - 1; i++) {
            SDL_RenderCopy(renderer, body2Texture, NULL, &playerBody2[i]);
        }
        }
        SDL_RenderCopy(renderer, foodTexture, NULL, &FOOD);
        show_points(renderer, digits, len_snake1, len_snake2, head1Texture, head2Texture);

        SDL_RenderPresent(renderer);
        
        SDL_Delay(150); 
    }

    if(loser!=0){
        SDL_Texture* ending[6];
        char endingfile[6];
        for(int j = 0 ; j<4 ; j++)
        {
            sprintf(endingfile,"e%d.bmp",j+1);
            SDL_Surface* randomsurf = SDL_LoadBMP(endingfile);
            colorkey = SDL_MapRGB(randomsurf->format, 0,0,0);
            SDL_SetColorKey(randomsurf, SDL_TRUE, colorkey);
            ending[j] = SDL_CreateTextureFromSurface(renderer, randomsurf);
            SDL_FreeSurface(randomsurf);
            SDL_Rect endingRect = {WIDTH/2-150,HEIGHT/2-75,300,150};
            if(loser==j+1)
            {
                SDL_RenderCopy(renderer, ending[j], NULL, &endingRect);
                if(loser==4){
                    endingRect.y+=150;
                    if(len_snake1>len_snake2){
                        SDL_RenderCopy(renderer, ending[1], NULL, &endingRect);
                    }
                    else if(len_snake2>len_snake1){
                        SDL_Surface* randomsurf = SDL_LoadBMP("e1.bmp");
                        colorkey = SDL_MapRGB(randomsurf->format, 0,0,0);
                        SDL_SetColorKey(randomsurf, SDL_TRUE, colorkey);
                        ending[0] = SDL_CreateTextureFromSurface(renderer, randomsurf);
                        SDL_FreeSurface(randomsurf);
                        SDL_RenderCopy(renderer, ending[0], NULL, &endingRect);
                    }
                    else{
                        SDL_Surface* randomsurf = SDL_LoadBMP("e5.bmp");
                        colorkey = SDL_MapRGB(randomsurf->format, 0,0,0);
                        SDL_SetColorKey(randomsurf, SDL_TRUE, colorkey);
                        ending[4] = SDL_CreateTextureFromSurface(renderer, randomsurf);
                        SDL_FreeSurface(randomsurf);
                        SDL_RenderCopy(renderer, ending[4], NULL, &endingRect);
                    }
                }
                SDL_RenderPresent(renderer);
            }
        }
        SDL_Delay(1500);
    }

    free(playerBody1);
    free(playerBody2);

    SDL_DestroyTexture(head1Texture);
    SDL_DestroyTexture(body1Texture);
    SDL_DestroyTexture(head2Texture);
    SDL_DestroyTexture(body2Texture);
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyTexture(prebgTexture);
    SDL_DestroyTexture(ghostTexture);
    SDL_DestroyTexture(foodTexture);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


    /* 1st video
    int width = 420 , height = 360, scale = 2;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width*scale, height*scale, 0, &window, &renderer);
    SDL_RenderSetScale(renderer , scale , scale);

    SDL_SetRenderDrawColor(renderer, 0 , 0 , 0 , 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawPoint(renderer, width/2 , height/2);

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    return 0;
    */

    /* 2nd video 1st half
        int width = 420 , height = 360, scale = 2;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0 , 0 , 0 , 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    rect.w = 100; rect.h=100; rect.x=100; rect.y=200;

    SDL_Rect rect2;
    rect2.w=200 ; rect2.h=75; rect2.x=25 ; rect2.y=150;

    SDL_Rect intersection;

    SDL_IntersectRect(&rect, &rect2, &intersection);

    SDL_SetRenderDrawColor(renderer,0,0,255,255);
    SDL_RenderDrawRect(renderer , &rect);

    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderDrawRect(renderer , &rect2);

    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    SDL_RenderFillRect(renderer , &intersection);   

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawPoint(renderer, width*0.9 , height/2);

    SDL_RenderPresent(renderer);
    SDL_Delay(7000);

    
    */

    /* 2nd video 2nd half
        int poses[150];
    // int rect[75];

    for(int i = 0 ; i<150 ; i++){
        if(i%2==0)
        poses[i] = rand()%width;

        if(i%2==1)
        poses[i] = rand()%height;
    }
    
    SDL_Rect rects[75];
    for(int i = 0 ; i<75 ; i++){
        rects[i].x = poses[2*i];
        rects[i].y = poses[2*i+1];
        rects[i].w = 10;
        rects[i].h = 10;

    }


    for(int i=0 ; i<75 ; i++){
    SDL_SetRenderDrawColor(renderer, rand()%256 , rand()%256 , rand()%256 , 255);
    SDL_RenderFillRect(renderer, &rects[i]);
    }

    /*
    for(int i = 0 ; i<150 ; i++){
        if(i%2==0)
        poses[i] = rand()%width;

        if(i%2==1)
        poses[i] = rand()%height;
    }

    SDL_SetRenderDrawColor(renderer, 255 , 255 , 0 , 255);

    for(int i=0 ; i<75 ; i++){
    SDL_RenderDrawPoint(renderer, poses[2*i], poses[2*i+1]);
    }
*/

/*
    int width = 640 , height = 480, scale = 2;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

   // SDL_SetRenderDrawColor(renderer, 0 , 0 , 0 , 255);
   // SDL_RenderClear(renderer); 

    SDL_Event e;
    int running = 1;
    SDL_Rect r;
    r.w = 15; r.h=15; r.x=50; r.y=50;

    while(running){
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                running=0;
            }
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        printf("right key was pushed.\n");
                        r.x += 50;
                        break;
                    case SDLK_DOWN:
                        r.y += 50;
                        printf("down key was pushed.\n");
                        break;                        
                    case SDLK_LEFT:
                        r.x -= 50;
                        printf("left key was pushed.\n");
                        break;  
                    case SDLK_UP:
                        r.y -= 50;
                        printf("up key was pushed.\n");
                        break;  
                    default:
                        printf("random key was pushed.\n");
                        break;                          
                }
            }
            else if(e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                default:
                printf("key was released\n");
                    break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255 , 255 , 255 , 255);
        SDL_RenderFillRect(renderer, &r);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
*/