#include<ncursesw/ncurses.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<math.h>
#include<locale.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <wchar.h>
#define MAP_HEIGHT 50
#define MAP_WIDTH 200
typedef enum {
    DEAMON,
    FIRE,
    GIANT,
    SNAKE,
    UNDEAD
} EnemyType;
typedef struct{
    int normal;
    int special;
    int speed;
}Food;
typedef struct{
    int H;
    int S;
    int G;
}Spell;
typedef struct{
    int mace;
    int dagger;
    int magic_wand;
    int arrow;
    int sword;
}Weapon;
typedef struct{
    char password[50];
    char email[50];
    char username[50];
    int score;
    int game;
    int gold;
    int health;
    int power;
    int difficulty;
    int color;
    int level_num;
    Food food_bar;
    Spell spell_bar;
    Weapon weapon_bar;
    char current_weapon;
    int kills1;
    int kills2;
    int hunger;
}User;
typedef struct{
    int x,y;
    int color;
    int difficulty;
    char prev_char;
}Player;
typedef struct {
    int y, x;
    int health;
    int damage;
    int following_distance;
    int damage_distance;
    int following;
    char face;
    char perv;
    int exe;
    EnemyType type;  
} Enemy;

char map1[MAP_HEIGHT][MAP_WIDTH];
char map2[MAP_HEIGHT][MAP_WIDTH];
char map3[MAP_HEIGHT][MAP_WIDTH];
char map4[MAP_HEIGHT][MAP_WIDTH];
char battle_room[MAP_HEIGHT][MAP_WIDTH];
char war_house[MAP_HEIGHT][MAP_WIDTH];

int memory_map1[MAP_HEIGHT][MAP_WIDTH];
int memory_map2[MAP_HEIGHT][MAP_WIDTH];  
int memory_map3[MAP_HEIGHT][MAP_WIDTH];  
int memory_map4[MAP_HEIGHT][MAP_WIDTH];

Enemy enemies_map1[10];
Enemy enemies_map2[10];
Enemy enemies_map3[10];
Enemy enemies_map4[10];
Enemy enemies_war[12];
Enemy enemies[12];
int inwar=0;
int fmsign=0;
int gmsign1=0;
int gmsign2=0;
int sign_d=0;
int sign_w=0;
int sign_a=0;
int night=0;
int wandon=0;
User p_user;
User l_user;
User s_user;
int is_logged_in=0;
int show_count = 0;
int full_food =0;
int full_spell=0;
int pace=1;
int pace_counter1=0;
int pace_counter2=0;
int Hspell;
int Sspell;
int Gspell;
int Hspellc=0;
int Sspellc=0;
int Gspellc=0;
int play;
int cp=0;
char main_music[300];
char current_music[300];
int killna;
void main_menu();
void log_in();
void sign_up();
int username_check(char *username);
int pass_check(char *password);
int email_check(char *email);
void play_game();
void show_table();
void profile();
void eexit();
void save_user();
void play_as_guest();
void start_new_game();
void continue_last_game();
void show_score_table();
void show_profile_status();
void settings_menu();
void start_new_game();
void start_level2();
void start_level3();
void start_level4();
void continue_last_game();
void show_profile_status(); 
void select_difficulty(int *current_difficulty);
void change_character_color(int *current_color);
int create_map1();
int create_map2();
int create_map3();
int create_map4();
void draw_path(int x1, int y1, int x, int y2,char map[MAP_HEIGHT][MAP_WIDTH]);
void draw_player(Player *player);
int handle_input(Player *player);
void clear_player(Player *player);
int is_valid_move(int x, int y,char map[MAP_HEIGHT][MAP_WIDTH]);
void initialize_memory_map(int memory_map[MAP_HEIGHT][MAP_WIDTH]);
void draw_visible_map(int player_x, int player_y,int memory_map[MAP_HEIGHT][MAP_WIDTH],char map[MAP_HEIGHT][MAP_WIDTH]);
void update_memory_map(int player_x, int player_y,int memory_map[MAP_HEIGHT][MAP_WIDTH]);
int is_in_room(int x, int y);
int get_room_id(int x, int y);
void refresh_map(Player *player,int memory_map[MAP_HEIGHT][MAP_WIDTH],char map[MAP_HEIGHT][MAP_WIDTH]);
void show_full_map_temporarily(Player *player);
char *generate_code();
void show_code(const char *code);
char *enter_code();
int check_code(const char *entered_code, const char *correct_code);
void draw_bar(int y, int x, int width, int value, int max_value, const char* label);
int food_manager(char food);
void food_table();
int gold_manager(char gold);
int spell_manager(char spell);
int spell_table();
char message(int height, int width);
int is_valid_enemy(int y , int x,char map[MAP_HEIGHT][MAP_WIDTH]);
void clear_enemy(Enemy enemy);
void damage_player(Enemy *enemy,Player *player);
int weapon_manager(char weapon);
int weapon_table();
int damage_enemy(int level,int room,char weapon,Player *player);
void create_battle_room();
Enemy create_random_enemy(int y, int x);
void clear_player2(Player *player);
int move_player(Player *player);
int enemy_checker(Player *player, Enemy *enemy);
int is_valid_move2(int x, int y);
int start_battle();
void draw_battle_room();
void refresh_map2(Player *player);
int damage_enemy2(char weapon,Player *player);
void music();
void displayMusicList(const char *musicFiles[], int count);
void final_result(int x);
void draw_robot_art(int start_y, int start_x);
void save_map(char map[MAP_HEIGHT][MAP_WIDTH]);
int save_info();
int read_users(const char *filename, User users[], int *num_users);
int write_users(const char *filename, User users[], int num_users);
User* find_user(User users[], int num_users, const char *username);
int telesm(Player *player);
int enemy_checker2(Player *player);
int save_info2();
char* pass_generator(char *password);
int robot_checker();
bool init_sdl();
void play_music(const char* file_path);
void stop_music();
bool is_music_playing();
int create_war_house();
void draw_war_house();
void start_war();
void refresh3(Player *player);
void guide();

int main(){
    setlocale(LC_ALL, "en_US.UTF-8");   
    initscr(); 
    noecho();       
    cbreak();         
    keypad(stdscr, TRUE);
    start_color();
    srand(time(NULL));
    init_color(8,600, 500, 0);
    init_color(9,300, 500, 200);
    init_color(10,1000, 500, 0);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7,COLOR_CYAN,COLOR_BLACK);
    init_pair(8,8,COLOR_BLACK);
    init_pair(9,9,COLOR_BLACK);
    init_pair(10,10,COLOR_BLACK);
    init_pair(11, COLOR_WHITE, COLOR_RED);
    init_sdl();
    main_menu();
    getch();
    endwin();
}

void main_menu() {
    curs_set(0);
    char *menu_items[] = {
        "    Sign up",
        "    Log in",
        "   Play game",
        "Play as a guest",
        "    Profile",
        "    Scores",
        "  Play music",
        "     Exit"
    };
    int n_items = sizeof(menu_items) / sizeof(menu_items[0]);
    int choice = 0;
    int key;
    int rows, cols;

    while (1) {
        clear();
        getmaxyx(stdscr, rows, cols);
        attron(COLOR_PAIR(6));
        for (int i = 0; i < rows ; i++) {
            mvprintw(i, 0, "|");
            mvprintw(i, cols -1, "|");
        }
        for (int j = 0; j < cols; j++) {
            mvprintw(0, j, "=");
            mvprintw(rows - 1, j, "=");
        }
        mvprintw(0, 0, "+");
        mvprintw(0, cols - 1, "+");
        mvprintw(rows - 1, 0, "+");
        mvprintw(rows - 1, cols - 1, "+");
        attroff(COLOR_PAIR(6));
        draw_robot_art(2, cols / 2 - 12);

        attron(COLOR_PAIR(10) | A_BOLD);
        mvprintw(rows / 2 + 1, cols / 2 - 10, "ZRUN GAME MENU");
        attroff(COLOR_PAIR(10) | A_BOLD);
        for (int i = 0; i < n_items; i++) {
            if (i == choice) {
                attron(COLOR_PAIR(3) | A_BOLD);
            } else {
                attron(COLOR_PAIR(7));
            }
            mvprintw(rows / 2 + 2 + i, cols / 2 - 10 , "%s", menu_items[i]);
            if (i == choice) {
                attroff(COLOR_PAIR(3) | A_BOLD);
            } else {
                attroff(COLOR_PAIR(7));
            }
        }

        attron(COLOR_PAIR(10));
        if (is_logged_in) {
            mvprintw(rows - 1, 1, "Logged in as: %s | Score: %d", l_user.username, l_user.score);
        } else {
            mvprintw(rows - 1, 1, "Not logged in. Please log in or sign up.");
        }
        attroff(COLOR_PAIR(10));

        key = getch();
        switch (key) {
            case KEY_UP:
                choice = (choice - 1 + n_items) % n_items;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % n_items;
                break;
            case '\n':
                clear();
                switch (choice) {
                    case 0: sign_up(); break;
                    case 1: log_in(); break;
                    case 2: play_game(); break;
                    case 3: play_as_guest(); break;
                    case 4: profile(); break;
                    case 5: show_table(); break;
                    case 6: music(); break;
                    case 7: eexit(); return;
                }
                break;
            default:
                break;
        }
    }
}
void sign_up(){
    int check = robot_checker();
    if(check==0){
        return;
    }
    int sign = 0;
    int start_y = LINES / 2 - 8;  
    int start_x;                  
    clear();
    attron(COLOR_PAIR(3));  
    start_x = COLS / 2 - 20;  
    mvprintw(start_y, start_x-5, "+========================================+");
    mvprintw(start_y + 1, start_x-5, "|          SIGN UP MENU                  |");
    mvprintw(start_y + 2, start_x-5, "+========================================+");
    attroff(COLOR_PAIR(3));

    while (1) {
        attron(COLOR_PAIR(1));  
        start_x = COLS / 2 - 20;  
        mvprintw(start_y + 4, start_x, "Enter your username: ");
        clrtoeol();
        echo();
        getstr(s_user.username);
        noecho();

        if (username_check(s_user.username)) {
            attron(COLOR_PAIR(2));  
            mvprintw(start_y + 5, start_x, "Username already exists. Try again.");
            clrtoeol();
            mvprintw(start_y + 6, start_x-5, "Press 'q' to exit or any other key to retry.");
            attroff(COLOR_PAIR(2));

            if (getch() == 'q') {
                return;
            } else {
                move(start_y + 5, start_x);
                clrtoeol();
                move(start_y + 6, start_x);
                clrtoeol();
            }
        } else {
            attron(COLOR_PAIR(10));  
            mvprintw(start_y + 5, start_x, "Username is OK ");
            clrtoeol();
            attroff(COLOR_PAIR(10));
            sign++;
            break;
        }
    }

    while (1) {
        attron(COLOR_PAIR(1));  
        start_x = COLS / 2 - 20;  
        mvprintw(start_y + 7, start_x,"Enter your password (or type 'gen' to generate one): ");
        clrtoeol();
        echo();
        getstr(s_user.password);
        noecho();
        if (strcmp(s_user.password, "gen") == 0) {
            pass_generator(s_user.password);
            mvprintw(start_y-1, start_x, "Generated Password: %s", s_user.password);
            refresh();
            napms(1000);
        }
        if (!pass_check(s_user.password)) {
            attron(COLOR_PAIR(2));  
            mvprintw(start_y + 8, start_x, "Password does not meet requirements. Try again.");
            clrtoeol();
            mvprintw(start_y + 9, start_x, "Press 'q' to exit or any other key to retry.");
            attroff(COLOR_PAIR(2));

            if (getch() == 'q') {
                mvprintw(start_y + 9, start_x, "                                            ");
                return;
            } else {
                move(start_y + 8, start_x);
                clrtoeol();
                move(start_y + 9, start_x);
                clrtoeol();
            }
        } else {
            attron(COLOR_PAIR(10));  
            mvprintw(start_y + 8, start_x, "Password is OK ");
            clrtoeol();
            attroff(COLOR_PAIR(10));
            sign++;
            break;
        }
    }

    while (1) {
        attron(COLOR_PAIR(1));  
        start_x = COLS / 2 - 20;  
        mvprintw(start_y + 10, start_x, "Enter your email: ");
        clrtoeol();
        echo();
        getstr(s_user.email);
        noecho();

        if (!email_check(s_user.email)) {
            attron(COLOR_PAIR(2));  
            mvprintw(start_y + 11, start_x, "Email format is incorrect. Try again.");
            clrtoeol();
            mvprintw(start_y + 12, start_x-5, "Press 'q' to exit or any other key to retry.");
            attroff(COLOR_PAIR(2));

            if (getch() == 'q') {
                return;
            } else {
                move(start_y + 11, start_x);
                clrtoeol();
                mvprintw(start_y + 12, start_x-5, "                                            ");
                move(start_y + 12, start_x);
                clrtoeol();
            }
        } else {
            mvprintw(start_y + 12, start_x-5, "                                            ");
            attron(COLOR_PAIR(10));  
            mvprintw(start_y + 11, start_x, "Email is OK ");
            clrtoeol();
            attroff(COLOR_PAIR(10));
            sign++;
            break;
        }
    }

     
    s_user.game = 0;
    s_user.gold = 0;
    s_user.score = 0;
    s_user.difficulty = 0;
    s_user.color = 0;
    s_user.level_num = 1;
    s_user.kills1 = 0;

    if (sign == 3) {
        save_user();
        attron(COLOR_PAIR(5));  
        start_x = COLS / 2 - 20;  
        mvprintw(start_y + 13, start_x-5, "+========================================+");
        mvprintw(start_y + 14, start_x-5, "|    ACCOUNT CREATED SUCCESSFULLY!       |");
        mvprintw(start_y + 15, start_x-5, "+========================================+");
        mvprintw(start_y + 16, start_x, "Press Enter to return to the menu.");
        attroff(COLOR_PAIR(5));

        while (1) {
            if (getch() == '\n') {
                break;
            }
        }
    }
}
void log_in(){
    int check = robot_checker();
    if(check==0){
        return;
    }
    if (is_logged_in == 1) {
        attron(COLOR_PAIR(3));
        mvprintw(LINES / 2, COLS / 2 - 15, "You are already logged in! Press any key to exit.");
        attroff(COLOR_PAIR(3));
        getch();
        return;
    } else {
        
        User user;
        int ch;
        
        while (1) {
            clear();
            curs_set(1);
            attron(COLOR_PAIR(3));
            mvprintw(LINES / 2 - 8, COLS / 2 - 30, "+========================================+");
            mvprintw(LINES / 2 - 7, COLS / 2 - 30, "|              LOG IN MENU               |");
            mvprintw(LINES / 2 - 6, COLS / 2 - 30, "+========================================+");
            attroff(COLOR_PAIR(3));
            mvprintw(LINES / 2 - 4, COLS / 2 - 30 , "Enter your username: ");
            clrtoeol();
            echo();
            getstr(l_user.username);
            FILE *fptr = fopen("users.txt", "r");
            if (fptr == NULL) {
                attron(COLOR_PAIR(2));
                mvprintw(LINES / 2, COLS / 2 - 20, "Error: Unable to open users file.");
                attroff(COLOR_PAIR(2));
                getch();
                curs_set(0);
                return;
            }
            int valid = 0;
            while (fscanf(fptr, "%s %s %s %d %d %d %d %d %d %d", user.username, user.password, user.email,
            &user.score, &user.gold, &user.game, &user.color, &user.difficulty , &user.kills1,&user.level_num) != EOF) {
                if(strcmp(l_user.username,user.username)==0){
                    strcpy(l_user.username, user.username);
                    strcpy(l_user.password, user.password);
                    strcpy(l_user.email, user.email);
                    l_user.score = user.score;
                    l_user.gold = user.gold;
                    l_user.game = user.game;
                    l_user.color = user.color;
                    l_user.difficulty = user.difficulty;
                    l_user.kills1 = user.kills1;
                    l_user.level_num = user.level_num;
                }
            }
            noecho();
            mvprintw(LINES / 2 - 2, COLS / 2 - 30, "Enter your password: (if forgotten Enter forget)");
            getch();
            clrtoeol();
            echo();
            char temp_pass[200];
            getstr(temp_pass);
            noecho();
            if(strcmp(temp_pass,"forgot")==0){
                mvprintw(LINES / 2-1, COLS / 2 - 30,"Enter your email :");
                char temp_email[200];
                echo();
                getstr(temp_email);
                if(strcmp(temp_email,l_user.email)==0){
                    mvprintw(LINES / 2, COLS / 2 - 30,"Your password is : %s",l_user.password);
                    getch();
                    continue;

                }
                else{
                    mvprintw(LINES / 2, COLS / 2 - 30,"Wrong email please try again later!");
                    getch();
                    continue;
                }
            }
            else if(strcmp(temp_pass,l_user.password)==0){
                valid=1;
            }

            fclose(fptr);

            if (valid) {
                attron(COLOR_PAIR(4)); 
                mvprintw(LINES / 2, COLS / 2 - 30, "Login successful! Press any key to return to the main menu.");
                attroff(COLOR_PAIR(4));
                strcpy(p_user.username,l_user.username);
                is_logged_in = 1;
                getch();
                curs_set(0);
                return;
            } else {
                attron(COLOR_PAIR(2)); 
                mvprintw(LINES / 2, COLS / 2 - 30, "Invalid username or password!");
                mvprintw(LINES / 2 + 2, COLS / 2 - 30, "Press 'r' to retry or any other key to return to the main menu.");
                attroff(COLOR_PAIR(2));

                ch = getch();
                if (ch != 'r' && ch != 'R') {
                    curs_set(0);
                    return;
                }
            }
        }
    }
}
int username_check(char *username){
    FILE *fptr = fopen("users.txt","r");
    if (fptr == NULL) {
        return 0;
    }
    User user;
    while (fscanf(fptr, "%s %s %s %d %d %d %d %d %d %d", user.username, user.password, user.email, &user.score,&user.gold,&user.game,&user.color,&user.difficulty, &user.kills1,&user.level_num) != EOF) {
        if (strcmp(user.username, username) == 0) {
            fclose(fptr);
            return 1;
        }
    }
    fclose(fptr);
    return 0;
}
int pass_check(char *password){
    int sign1=0;
    int sign2=0;
    int sign3=0;
    int sign4=0;
    int index = 0;
    while(password[index]!='\0'){
        if(password[index]>='A'&&password[index]<='Z'){
            sign1=1;
        }
        if(strlen(password)>=7){
            sign2=1;
        }
        if(password[index]>='0'&&password[index]<='9'){
            sign3=1;
        }
        if(password[index]>='a'&&password[index]<='z'){
            sign4=1;
        }
        index++;
    }
    return sign1 && sign2 && sign3 && sign4;
}
int email_check(char *email){
    int sign1=0;
    int sign2=0;
    int sign3=0;
    int index = 0;
    char *at = strchr(email, '@');
    char *dot = strrchr(email, '.');
    if(at == NULL || dot == NULL || at > dot){
        return 0;
    }
    for(int i = 0 ; i < at - email ; i++){
        if((email[i]>='A'&&email[i]<='Z')||(email[i]>='a'&&email[i]<='z')){
             sign1=1;
             break;
        }
    }
    for(int i = at - email + 1 ; i < dot - email; i++){
        if((email[i]>='A'&&email[i]<='Z')||(email[i]>='a'&&email[i]<='z')){
             sign2=1;
             break;
        }
    }
    for(int i = dot - email + 1; email[i]!='\0'; i++){
        if((email[i]>='A'&&email[i]<='Z')||(email[i]>='a'&&email[i]<='z')){
             sign3=1;
             break;
        }
    }
    return sign1 && sign2 && sign3;
}
void play_game(){
    init_color(8,600, 500, 0);
    init_color(9,300, 500, 200);
    init_color(10,1000, 500, 0);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7,COLOR_CYAN,COLOR_BLACK);
    init_pair(8,8,COLOR_BLACK);
    init_pair(9,9,COLOR_BLACK);
    init_pair(10,10,COLOR_BLACK);
    init_pair(11, COLOR_WHITE, COLOR_RED);
    char *play_menu_items[] = {
        "New Game",
        "Continue Your Last Game",
        "Score Table",
        "Profile Status",
        "Settings",
        "Back to Main Menu"
    };
    int n_items = sizeof(play_menu_items) / sizeof(play_menu_items[0]);
    int choice = 0;
    int key;
    int rows, cols;

    getmaxyx(stdscr, rows, cols);

    while (1) {
        clear();
        
        if (is_logged_in) {
            attron(COLOR_PAIR(1));
            mvprintw(2, (cols - 15) / 2, "Play Game Menu");
            attroff(COLOR_PAIR(1));

            mvprintw(rows - 2, 2, "Logged in as: %s | Score: %d", l_user.username, l_user.score);
        } else {
            attron(COLOR_PAIR(3));
            mvprintw(rows / 2, (cols - 30) / 2, "Not logged in. Please log in or sign up.");
            attroff(COLOR_PAIR(3));
            getch();
            endwin();
            return;
        }

        for (int i = 0; i < n_items; i++) {
            if (i == choice) {
                attron(COLOR_PAIR(2) | A_BOLD);
                mvprintw(rows / 2 - n_items / 2 + i, (cols - 25) / 2, " > %s ", play_menu_items[i]);
                attroff(COLOR_PAIR(2) | A_BOLD);
            } else {
                mvprintw(rows / 2 - n_items / 2 + i, (cols - 25) / 2, "   %s  ", play_menu_items[i]);
            }
        }

        key = getch();

        switch (key) {
            case KEY_UP:
                choice = (choice - 1 + n_items) % n_items;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % n_items;
                break;
            case '\n':
                switch (choice) {
                    case 0: start_new_game(); break;
                    case 1: continue_last_game(); break;
                    case 2: show_table(); break;
                    case 3: profile(); break;
                    case 4: settings_menu(); break;
                    case 5: return;
                }
                return;
        }
    }
}
void play_as_guest(){
    guide();
    clear();
    int rows,cols;
    getmaxyx(stdscr, rows, cols);
        attron(COLOR_PAIR(6));
        for (int i = 0; i < rows ; i++) {
            mvprintw(i, 0, "|");
            mvprintw(i, cols -1, "|");
        }
        for (int j = 0; j < cols; j++) {
            mvprintw(0, j, "=");
            mvprintw(rows - 1, j, "=");
        }
        mvprintw(0, 0, "+");
        mvprintw(0, cols - 1, "+");
        mvprintw(rows - 1, 0, "+");
        mvprintw(rows - 1, cols - 1, "+");
        attroff(COLOR_PAIR(6));
    play=0;
    cp=0;
    p_user.level_num=1;
    p_user.gold = 0;
    p_user.score=0;
    p_user.health=10000;
    p_user.power=100;
    p_user.difficulty=1;
    p_user.food_bar.normal=0;
    p_user.food_bar.special=0;
    p_user.spell_bar.H=0;
    p_user.spell_bar.S=0;
    p_user.spell_bar.G=0;
    p_user.weapon_bar.mace=1;
    p_user.weapon_bar.dagger=0;
    p_user.weapon_bar.arrow=0;
    p_user.weapon_bar.magic_wand=0;
    p_user.weapon_bar.sword=0;
    p_user.current_weapon='m';
    p_user.kills1=0;
    p_user.kills2=0;
    p_user.hunger=100;
    show_count = 0;
    memset(memory_map1,0,sizeof(memory_map1));
    create_map1();
    create_map2();
    create_map3();
    create_map4();
    Player player = {5, 4, '.'};
    refresh_map(&player,memory_map1,map1);  

    while (1) {
        handle_input(&player);
    }
}
void show_table(){
    clear();    
    int table_width = 70;   
    int start_x = (COLS - table_width) / 2;
    int start_y = 2;
    attron(COLOR_PAIR(7) | A_BOLD);
    mvprintw(start_y, start_x, "SCORE TABLE");
    attroff(COLOR_PAIR(7) | A_BOLD);
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        attron(COLOR_PAIR(1));
        mvprintw(start_y + 2, start_x, "Error: Unable to open users file.");
        attroff(COLOR_PAIR(1));
        getch();
        return;
    }
    User users[100];
    int user_count = 0;
    while (fscanf(file, "%s %s %s %d %d %d %d %d %d %d", users[user_count].username, users[user_count].password, 
    users[user_count].email, &users[user_count].score, &users[user_count].gold, &users[user_count].game, 
    &users[user_count].color, &users[user_count].difficulty ,&users[user_count].kills1,&users[user_count].level_num) != EOF) {
    user_count++;
    }
    fclose(file);
    for (int i = 0; i < user_count - 1; i++) {
        for (int j = 0; j < user_count - i - 1; j++) {
            if (users[j].score < users[j + 1].score) {
                User temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < user_count; i++) {
           
        
        if (i > 0) {
            attron(COLOR_PAIR(4));
            mvprintw(start_y + 3 + i * 2 - 1, start_x, "------------------------------------------------------");
            attroff(COLOR_PAIR(4));
        }  
        if (!strcmp(users[i].username, l_user.username)) {
            attron(COLOR_PAIR(1) | A_BOLD | A_ITALIC);
        } 
        if (i == 0) {
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(start_y + 3 + i * 2, start_x, "%d. %s - Score: %d | Gold: %d | Games Played: %d | kills : %d (THE GOAT)\U0001F947", i + 1, users[i].username, users[i].score, users[i].gold, users[i].game,users[i].kills1);
            attroff(COLOR_PAIR(3) | A_BOLD);
        } else if (i == 1) {
            attron(COLOR_PAIR(6) | A_BOLD);
            mvprintw(start_y + 3 + i * 2, start_x, "%d. %s - Score: %d | Gold: %d | Games Played: %d | kills : %d (ALMOST GOAT)\U0001F948", i + 1, users[i].username, users[i].score, users[i].gold, users[i].game,users[i].kills1);
            attroff(COLOR_PAIR(6) | A_BOLD);
        } else if (i == 2) {
            attron(COLOR_PAIR(5) | A_BOLD);
            mvprintw(start_y + 3 + i * 2, start_x, "%d. %s - Score: %d | Gold: %d | Games Played: %d | kills : %d (SEMI GOAT)\U0001F949", i + 1, users[i].username, users[i].score, users[i].gold, users[i].game,users[i].kills1);
            attroff(COLOR_PAIR(5) | A_BOLD);
        } else {
            attron(COLOR_PAIR(4));
            mvprintw(start_y + 3 + i * 2, start_x, "%d. %s - Score: %d | Gold: %d | Games Played: %d | kills : %d", i + 1, users[i].username, users[i].score, users[i].gold, users[i].game,users[i].kills1);
            attroff(COLOR_PAIR(4));
        }   
        if (!strcmp(users[i].username, l_user.username)) {
            attroff(COLOR_PAIR(1) | A_BOLD | A_ITALIC);
        }
    }
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(start_y + 5 + user_count * 2, start_x, "Press any key to return.");
    attroff(COLOR_PAIR(1) | A_BOLD);
    refresh();    
    getch();      
}
void profile(){
    clear();
    if (is_logged_in) {
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        int box_width = 40;
        int box_height = 14; 
        int start_y = (max_y - box_height) / 2;
        int start_x = (max_x - box_width) / 2;

        attron(COLOR_PAIR(7)); 
        for (int i = start_x; i < start_x + box_width; i++) {
            mvprintw(start_y, i, "-"); 
            mvprintw(start_y + box_height - 1, i, "-"); 
        }
        for (int i = start_y; i < start_y + box_height; i++) {
            mvprintw(i, start_x, "|"); 
            mvprintw(i, start_x + box_width - 1, "|"); 
        }
        mvprintw(start_y, start_x, "+");
        mvprintw(start_y, start_x + box_width - 1, "+");
        mvprintw(start_y + box_height - 1, start_x, "+");
        mvprintw(start_y + box_height - 1, start_x + box_width - 1, "+");
        attroff(COLOR_PAIR(7));

        attron(COLOR_PAIR(4));
        mvprintw(start_y + 2, start_x + 2, "Here is your information:");
        mvprintw(start_y + 4, start_x + 2, "Name: %s", l_user.username);
        mvprintw(start_y + 5, start_x + 2, "Password: %s", l_user.password);
        mvprintw(start_y + 6, start_x + 2, "Email: %s", l_user.email);
        mvprintw(start_y + 7, start_x + 2, "Score: %d", l_user.score);
        mvprintw(start_y + 8, start_x + 2, "Gold: %d", l_user.gold);
        mvprintw(start_y + 9, start_x + 2, "Kills: %d", l_user.kills1);
        mvprintw(start_y + 10, start_x + 2, "Games played: %d", l_user.game);
        attroff(COLOR_PAIR(4));
        attron(COLOR_PAIR(2));
        mvprintw(start_y + 12, start_x + 2, "Press Enter to exit");
        attroff(COLOR_PAIR(2));

        int ch = getch();
        if (ch == '\n') {
            return;
        }
    } 
    else {
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);

        int box_width = 40;  
        int box_height = 5;  

         
        int start_y = (max_y - box_height) / 2;
        int start_x = (max_x - box_width) / 2;

         
        attron(COLOR_PAIR(7));  
        for (int i = start_x; i < start_x + box_width; i++) {
            mvprintw(start_y, i, "-");  
            mvprintw(start_y + box_height - 1, i, "-");  
        }
        for (int i = start_y; i < start_y + box_height; i++) {
            mvprintw(i, start_x, "|");  
            mvprintw(i, start_x + box_width - 1, "|");  
        }
         
        mvprintw(start_y, start_x, "+");
        mvprintw(start_y, start_x + box_width - 1, "+");
        mvprintw(start_y + box_height - 1, start_x, "+");
        mvprintw(start_y + box_height - 1, start_x + box_width - 1, "+");
        attroff(COLOR_PAIR(7));

         
        attron(COLOR_PAIR(4));  
        mvprintw(start_y + 2, start_x + 2, "You are not logged in.");
        mvprintw(start_y + 3, start_x + 2, "Press Enter to exit.");
        attroff(COLOR_PAIR(4));

         
        int ch = getch();
        if (ch == '\n') {
            return;
        }
    }
}
void eexit(){
    mvprintw(22,90,"GOODBYE!");
    getch();
    return;
}
void save_user() {
    FILE *file = fopen("users.txt", "a");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    fprintf(file, "%s %s %s %d %d %d %d %d %d %d\n", s_user.username, s_user.password, s_user.email, s_user.score,s_user.gold,s_user.game,s_user.color,s_user.difficulty,s_user.kills1,s_user.level_num);
    fclose(file);
}
void settings_menu() {
    clear();
    char *settings_items[] = {
        "Select Difficulty Level",
        "Change Character Color",
        "Back to Play Menu"
    };
    int n_items = sizeof(settings_items) / sizeof(settings_items[0]);
    int choice = 0;
    int key;
    int rows, cols;
    static int current_difficulty = 0;  
    static int current_color = 1;       
    getmaxyx(stdscr, rows, cols);

    while (1) {
        clear();
        
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(rows / 2 - n_items - 2, (cols - 15) / 2, "Settings Menu");
        attroff(COLOR_PAIR(1) | A_BOLD);
        for (int i = 0; i < n_items; i++) {
            if (i == choice) {
                attron(COLOR_PAIR(2) | A_BOLD);
                mvprintw(rows / 2 - n_items / 2 + i, (cols - 30) / 2, " > %s ", settings_items[i]);
                attroff(COLOR_PAIR(2) | A_BOLD);
            } else {
                mvprintw(rows / 2 - n_items / 2 + i, (cols - 30) / 2, "   %s ", settings_items[i]);
            }
        }

        key = getch();

        switch (key) {
            case KEY_UP:
                choice = (choice - 1 + n_items) % n_items;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % n_items;
                break;
            case '\n':
                switch (choice) {
                    case 0:  
                        select_difficulty(&current_difficulty);
                        break;
                    case 1:  
                        change_character_color(&current_color);
                        break;
                    case 2:
                        play_game();
                        return;
                }
                break;
            case 27:  
                return;
        }
    }
}
void select_difficulty(int *current_difficulty) {
    clear();
    char *difficulty_levels[] = {
        "Easy",
        "Medium",
        "Hard"
    };
    int n_levels = sizeof(difficulty_levels) / sizeof(difficulty_levels[0]);
    int choice = *current_difficulty;
    int key;
    int rows, cols;


    getmaxyx(stdscr, rows, cols);

    while (1) {
        clear();
        
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(rows / 2 - n_levels - 2, (cols - 25) / 2, "Select Difficulty Level");
        attroff(COLOR_PAIR(1) | A_BOLD);
        for (int i = 0; i < n_levels; i++) {
            if (i == choice) {
                attron(COLOR_PAIR(2) | A_BOLD);
                mvprintw(rows / 2 - n_levels / 2 + i, (cols - 15) / 2, " > %s ", difficulty_levels[i]);
                attroff(COLOR_PAIR(2) | A_BOLD);
            } else {
                mvprintw(rows / 2 - n_levels / 2 + i, (cols - 15) / 2, "   %s  %s", 
                         difficulty_levels[i], (i == *current_difficulty) ? "(Selected)" : "");
            }
        }
        mvprintw(rows / 2 + n_levels + 2, (cols - 40) / 2, "Press ENTER to confirm, or ESC to cancel.");

        key = getch();

        switch (key) {
            case KEY_UP:
                choice = (choice - 1 + n_levels) % n_levels;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % n_levels;
                break;
            case '\n':  
                *current_difficulty = choice;
                attron(COLOR_PAIR(3) | A_BOLD);
                mvprintw(rows / 2 + n_levels + 4, (cols - 30) / 2, "Difficulty set to %s!", difficulty_levels[choice]);
                attroff(COLOR_PAIR(3) | A_BOLD);
                getch();
                return;
            case 27:  
                return;
        }
    }
}
void change_character_color(int *current_color) {
    clear();
    char *colors[] = {
        "White",
        "Red",
        "Green",
        "Blue",
        "Yellow"
    };
    int color_codes[] = {
        COLOR_WHITE, COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW
    };

    int n_colors = sizeof(colors) / sizeof(colors[0]);
    int choice = *current_color;
    int key;
    int rows, cols;
    for (int i = 0; i < n_colors; i++) {
        init_pair(i + 1, color_codes[i], COLOR_BLACK);
    }

    getmaxyx(stdscr, rows, cols);

    while (1) {
        clear();
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(rows / 2 - n_colors - 2, (cols - 25) / 2, "Change Character Color");
        attroff(COLOR_PAIR(1) | A_BOLD);
        for (int i = 0; i < n_colors; i++) {
            if (i == choice) {
                attron(COLOR_PAIR(i + 1) | A_BOLD);
                mvprintw(rows / 2 - n_colors / 2 + i, (cols - 15) / 2, " > %s ", colors[i]);
                attroff(COLOR_PAIR(i + 1) | A_BOLD);
            } else {
                mvprintw(rows / 2 - n_colors / 2 + i, (cols - 15) / 2, "   %s ", colors[i]);
            }
        }
        mvprintw(rows / 2 + n_colors + 2, (cols - 40) / 2, "Press ENTER to confirm, or ESC to cancel.");

        key = getch();

        switch (key) {
            case KEY_UP:
                choice = (choice - 1 + n_colors) % n_colors;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % n_colors;
                break;
            case '\n':  
                *current_color = choice;
                attron(COLOR_PAIR(choice + 1) | A_BOLD);
                mvprintw(rows / 2 + n_colors + 4, (cols - 30) / 2 + 7, "Color set to %s!", colors[choice]);
                attroff(COLOR_PAIR(choice + 1) | A_BOLD);

                getch();
                return;
            case 27:  
                return;
        }
    }
}
void start_new_game(){
    guide();
    clear();
    int rows,cols;
    getmaxyx(stdscr, rows, cols);
        attron(COLOR_PAIR(6));
        for (int i = 0; i < rows ; i++) {
            mvprintw(i, 0, "|");
            mvprintw(i, cols -1, "|");
        }
        for (int j = 0; j < cols; j++) {
            mvprintw(0, j, "=");
            mvprintw(rows - 1, j, "=");
        }
        mvprintw(0, 0, "+");
        mvprintw(0, cols - 1, "+");
        mvprintw(rows - 1, 0, "+");
        mvprintw(rows - 1, cols - 1, "+");
        attroff(COLOR_PAIR(6));
    p_user.level_num=1;
    p_user.gold = 0;
    p_user.score=0;
    p_user.health=10000;
    p_user.power=100;
    p_user.food_bar.normal=0;
    p_user.food_bar.special=0;
    p_user.spell_bar.H=0;
    p_user.spell_bar.S=0;
    p_user.spell_bar.G=0;
    p_user.weapon_bar.mace=1;
    p_user.weapon_bar.dagger=0;
    p_user.weapon_bar.arrow=0;
    p_user.weapon_bar.magic_wand=0;
    p_user.weapon_bar.sword=0;
    p_user.kills1=0;
    p_user.kills2=0;
    p_user.hunger=100;
    p_user.current_weapon='m';
    show_count = 0;
    l_user.game++;
    save_info();
    memset(memory_map1,0,sizeof(memory_map1));
    create_map1();
    create_map2();
    create_map3();
    create_map4();   
    Player player = {5, 4, '.'};
    refresh_map(&player,memory_map1,map1);  

    while (1) {
        handle_input(&player);
    }
}
void start_level2(){
    clear();
    int rows,cols;
    getmaxyx(stdscr, rows, cols);
        attron(COLOR_PAIR(3));
        for (int i = 0; i < rows ; i++) {
            mvprintw(i, 0, "|");
            mvprintw(i, cols -1, "|");
        }
        for (int j = 0; j < cols; j++) {
            mvprintw(0, j, "=");
            mvprintw(rows - 1, j, "=");
        }
        mvprintw(0, 0, "+");
        mvprintw(0, cols - 1, "+");
        mvprintw(rows - 1, 0, "+");
        mvprintw(rows - 1, cols - 1, "+");
        attroff(COLOR_PAIR(3));
    show_count = 0;
    cp=0;
    p_user.level_num=2;
    pace=1;
    pace_counter1=0;
    pace_counter2=0;
    memset(memory_map2,0,sizeof(memory_map2));
    Player player = {12,10, '.'};
    refresh_map(&player,memory_map2,map2);  

    while (1) {
        handle_input(&player);
    }
}
void start_level3(){
    clear();
    int rows,cols;
    getmaxyx(stdscr, rows, cols);
        attron(COLOR_PAIR(10));
        for (int i = 0; i < rows ; i++) {
            mvprintw(i, 0, "|");
            mvprintw(i, cols -1, "|");
        }
        for (int j = 0; j < cols; j++) {
            mvprintw(0, j, "=");
            mvprintw(rows - 1, j, "=");
        }
        mvprintw(0, 0, "+");
        mvprintw(0, cols - 1, "+");
        mvprintw(rows - 1, 0, "+");
        mvprintw(rows - 1, cols - 1, "+");
        attroff(COLOR_PAIR(10));
        cp=0;
    show_count = 0;
    p_user.level_num=3;
    pace=1;
    pace_counter1=0;
    pace_counter2=0;
    memset(memory_map3,0,sizeof(memory_map3)); 
    Player player = {20,26, '.'};
    refresh_map(&player,memory_map3,map3);  

    while (1) {
        handle_input(&player);
    }
}
void start_level4(){
    clear();
    int rows,cols;
    getmaxyx(stdscr, rows, cols);
        attron(COLOR_PAIR(2));
        for (int i = 0; i < rows ; i++) {
            mvprintw(i, 0, "|");
            mvprintw(i, cols -1, "|");
        }
        for (int j = 0; j < cols; j++) {
            mvprintw(0, j, "=");
            mvprintw(rows - 1, j, "=");
        }
        mvprintw(0, 0, "+");
        mvprintw(0, cols - 1, "+");
        mvprintw(rows - 1, 0, "+");
        mvprintw(rows - 1, cols - 1, "+");
        attroff(COLOR_PAIR(2));
        cp=0;
    show_count = 0;
    pace=1;
    pace_counter1=0;
    pace_counter2=0;
    p_user.level_num=4;
    memset(memory_map4,0,sizeof(memory_map4));
    Player player = {48,35, '.'};
    refresh_map(&player,memory_map4,map4);  

    while (1) {
        handle_input(&player);
    }
}
void continue_last_game(){
    p_user.gold = 0;
    p_user.score=0;
    p_user.health=10000;
    p_user.power=100;
    p_user.food_bar.normal=0;
    p_user.food_bar.special=0;
    p_user.spell_bar.H=0;
    p_user.spell_bar.S=0;
    p_user.spell_bar.G=0;
    p_user.weapon_bar.mace=1;
    p_user.weapon_bar.dagger=0;
    p_user.weapon_bar.arrow=0;
    p_user.weapon_bar.magic_wand=0;
    p_user.weapon_bar.sword=0;
    p_user.kills1=0;
    p_user.kills2=0;
    p_user.hunger=100;
    p_user.current_weapon='m';
    show_count = 0;
    if(l_user.level_num==1){
        create_map1();
        start_new_game();
    }
    else if(l_user.level_num==2){
        create_map2();
        start_level2();
    }
    else if(l_user.level_num==3){
        create_map3();
        start_level3();
    }
    else if(l_user.level_num==4){
        create_map4();
        start_level4();
    }
}
int is_valid_move(int x, int y,char map[MAP_HEIGHT][MAP_WIDTH]) {
    char ch = map[y][x];
    return ch == '.' || ch == '#' || ch == '+'||ch=='<'||ch=='&'||ch=='Q'||ch=='T'||ch=='Z'
    ||ch=='X'||ch=='%'|ch=='R'|ch=='H'|ch=='8'||ch=='3'||ch=='^'||ch=='L'||ch=='J'||ch=='/'
    ||ch=='*'||ch=='A'||ch=='V';
}
void draw_player(Player *player) {
    if(p_user.color==4){
        attron(COLOR_PAIR(4));
    }
    else if(p_user.color==2){
        attron(COLOR_PAIR(2));
    }
    else if(p_user.color==3){
        attron(COLOR_PAIR(3));
    }
    else if(p_user.color==5){
        attron(COLOR_PAIR(5));
    }
    else if(p_user.color==1){
        attron(COLOR_PAIR(1));
    }
    mvprintw(player->y, player->x, "@");
    if(p_user.color==4){
        attroff(COLOR_PAIR(4));
    }
    else if(p_user.color==2){
        attroff(COLOR_PAIR(2));
    }
    else if(p_user.color==3){
        attroff(COLOR_PAIR(3));
    }
    else if(p_user.color==5){
        attroff(COLOR_PAIR(5));
    }
    else if(p_user.color==1){
        attroff(COLOR_PAIR(1));
    }
}
void clear_player(Player *player) {
    if(fmsign==0){
       mvprintw(player->y, player->x, "%c", '.');
       fmsign++;
    }
    else if (p_user.level_num==1&&inwar==0)
    {
        if(player->prev_char=='3'){
            map1[player->y][player->x]='^';
        }
        else if(player->y==9 && player->x==100){
            map1[9][100]='|';
        } 
        else if(player->y==34 && player->x==110){
            map1[34][110]='|';
        }
        else{
            mvprintw(player->y, player->x, "%c", player->prev_char);
        }
    }
    else if (p_user.level_num==2&&inwar==0)
    {
        if(player->prev_char=='3'){
            map2[player->y][player->x]='^';
        }
        else if(player->y==7 && player->x==120){
            map2[7][120]='|';
        } 
        else if(player->y==17 && player->x==60){
            map2[17][60]='|';
        }
        else{
            mvprintw(player->y, player->x, "%c", player->prev_char);
        }
    }
    else if (p_user.level_num==3&&inwar==0)
    {
        if(player->prev_char=='3'){
            map3[player->y][player->x]='^';
        }
        else if(player->y==39 && player->x==160){
            map3[39][160]='|';
        } 
        else if(player->y==8 && player->x==158){
            map3[8][158]='-';
        }
        else{
            mvprintw(player->y, player->x, "%c", player->prev_char);
        }
    }
    else if (p_user.level_num==4&&inwar==0)
    {
        if(player->prev_char=='3'){
            map4[player->y][player->x]='^';
        }
        else if(player->y==32 && player->x==94){
            map4[32][94]='|';
        } 
        else if(player->y==12 && player->x==127){
            map4[12][127]='-';
        }
        else{
            mvprintw(player->y, player->x, "%c", player->prev_char);
        }
    }
    else if(inwar==1){
        war_house[player->y][player->x]='.';
    }
}
void draw_path(int x1, int y1, int x2, int y2,char map[MAP_HEIGHT][MAP_WIDTH]) {
    int cx = x1, cy = y1;

    while (cx != x2 || cy != y2) {
        map[cy][cx] = '#';

        int dx = (cx < x2) - (cx > x2);
        int dy = (cy < y2) - (cy > y2);

        if (rand() % 2 == 0 && map[cy][cx + dx] != '|' && map[cy][cx + dx] != '-') {
            cx += dx;
        } else if (map[cy + dy][cx] != '|' && map[cy + dy][cx] != '-') {
            cy += dy;
        } else if (map[cy + dy][cx + dx] != '|' && map[cy + dy][cx + dx] != '-') {
            cx += dx;
            cy += dy;
        } else {
            break;
        }
    }
}
int create_map1() {
    memset(map1, ' ', sizeof(map1));
    //room 1
    for (int i = 4; i < 9; i++) {
        map1[i][3] = '|';
        map1[i][23] = '|';
    }
    for (int i = 3; i <= 23; i++) {
        map1[3][i] = '-';
        map1[9][i] = '-';
    }
    for (int i = 4; i < 9; i++) {
        for (int j = 4; j < 23; j++) {
            map1[i][j] = '.';
        }
    }
    int n1 = rand() % 5 + 3;
    for (int i = 0 ; i < n1 ;i++){
        int x = rand() % 5 + 4;
        int y = rand() % 19 + 4;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='%';
    }
    int t1 = rand() % 3 + 1;
    for (int i = 0 ; i < t1 ;i++){
        int x = rand() % 5 + 4;
        int y = rand() % 19 + 4;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='T';
    }
    int q1 = rand() % 3 ;
    for (int i = 0 ; i < q1 ;i++){
        int x = rand() % 5 + 4;
        int y = rand() % 19 + 4;
        if(map1[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map1[x][y]='R';
        }
        else if(p==1){
            map1[x][y]='H';
        }
        else if(p==2){
            map1[x][y]='8';
        }
    }
    int s1 = rand() % 2 + 1 ;
    for (int i = 0 ; i < s1 ;i++){
        int x = rand() % 5 + 4;
        int y = rand() % 19 + 4;
        if(map1[x][y]!='.'){
            continue;
            i--;
        }
        int p = rand()%2;
        if(p==0){
            map1[x][y]='/';
        }
        else if(p==1){
            map1[x][y]='*';
        }
    }
    

    map1[5][23] = '+';
    //map1[7][5] = 'A';
    map1[5][15] = 'o';
    //map1[8][9] = '<';

    //  room ۲
    for (int i = 8; i < 20; i++) {
        map1[i][50] = '|';
        map1[i][65] = '|';
    }
    for (int i = 50; i <= 65; i++) {
        map1[7][i] = '-';
        map1[20][i] = '-';
    }
    for (int i = 8; i <= 19; i++) {
        for (int j = 51; j < 65; j++) {
            map1[i][j] = '.';
        }
    }
    int n2 = rand() % 5 + 4;
    for (int i = 0 ; i < n2 ;i++){
        int x = rand() % 12 + 8;
        int y = rand() % 14 + 51;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='%';
    }
    for(int i = 0 ; i < 1;i++){
        int x = rand() % 12 + 8;
        int y = rand() % 14 + 51;
        map1[x][y]='3';
    }

    int m2 = rand() % 3;
    for (int i = 0 ; i < m2 ;i++){
        int x = rand() % 12 + 8;
        int y = rand() % 14 + 51;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='T';
    }
    int q2 = rand() % 3 ;
    for (int i = 0 ; i < q2 ;i++){
        int x = rand() % 12 + 8;
        int y = rand() % 14 + 51;
        if(map1[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map1[x][y]='R';
        }
        else if(p==1){
            map1[x][y]='H';
        }
        else if(p==2){
            map1[x][y]='8';
        }
    }
    map1[7][58] = '+';
    map1[18][65] = '+';
    map1[14][55] = 'o';
    map1[8][56] = 'o';
    int s2 = rand() % 3 + 2;
    for (int i = 0 ; i < s2 ;i++){
        int x = rand() % 12 + 8;
        int y = rand() % 14 + 51;
        if(map1[x][y]!='.'){
            continue;
            i--;
        }
        int p = rand()%2;
        if(p==0){
            map1[x][y]='/';
        }
        else if(p==1){
            map1[x][y]='*';
        }
    }
    int x2 = rand() % 12 + 8;
    int y2 = rand() % 14 + 51;
    enemies_map1[0]=create_random_enemy(x2,y2);
    map1[x2][y2]=enemies_map1[0].face;
    //  room ۳
    for (int i = 6; i < 17; i++) {
        map1[i][100] = '|';
        map1[i][111] = '|';
    }
    for (int i = 100; i <= 111; i++) {
        map1[6][i] = '-';
        map1[16][i] = '-';
    }
    for (int i = 7; i < 16; i++) {
        for (int j = 101; j < 111; j++) {
            map1[i][j] = '.';
        }
    }
    int n3 = rand() % 4 + 3;
    for (int i = 0 ; i < n3 ;i++){
        int x = rand() % 9 + 7;
        int y = rand() % 10 + 101;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='%';
    }
    int m3 = rand() % 3;
    for (int i = 0 ; i < m3 ;i++){
        int x = rand() % 9 + 7;
        int y = rand() % 10 + 101;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='T';
    }
    int q3 = rand() % 3 ;
    for (int i = 0 ; i < q3 ;i++){
        int x = rand() % 9 + 7;
        int y = rand() % 10 + 101;
        if(map1[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map1[x][y]='R';
        }
        else if(p==1){
            map1[x][y]='H';
        }
        else if(p==2){
            map1[x][y]='8';
        }
    }
    for(int i = 0 ;i<2;i++){
        int x = rand() % 9 + 7;
        int y = rand() % 10 + 101;
        map1[x][y]='3';
    }

    map1[9][100] = '+';
    //map1[14][111] = '+';
    map1[10][105] = 'o';
    map1[14][102] = 'o';
    map1[15][109] = 'o';
    int s3 = rand() % 2 + 1 ;
    for (int i = 0 ; i < s3 ;i++){
        int x = rand() % 9 + 7;
        int y = rand() % 10 + 101;
        if(map1[x][y]!='.'){
            continue;
            i--;
        }
        int p = rand()%2;
        if(p==0){
            map1[x][y]='/';
        }
        else if(p==1){
            map1[x][y]='J';
        }
    }
    for(int i=1 ; i<3 ;i++){
        x2 = rand() % 9 + 7;
        y2 = rand() % 10 + 101;
        enemies_map1[i]=create_random_enemy(x2,y2);
        map1[x2][y2]=enemies_map1[i].face;
    }
    
    //  room ۴
    for (int i = 20; i < 30; i++) {
        map1[i][150] = '|';
        map1[i][159] = '|';
    }
    for (int i = 150; i <= 159; i++) {
        map1[20][i] = '-';
        map1[29][i] = '-';
    }
    for (int i = 21; i < 29; i++) {
        for (int j = 151; j < 159; j++) {
            map1[i][j] = '.';
        }
    }
    int n4 = rand() % 4 + 3;
    for (int i = 0 ; i < n4 ;i++){
        int x = rand() % 8 + 21;
        int y = rand() % 8 + 151;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='%';
    }
    int m4 = rand() % 3;
    for (int i = 0 ; i < m4 ;i++){
        int x = rand() % 8 + 21;
        int y = rand() % 8 + 151;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='T';
    }
    int a4 = rand() % 2+2;
    for (int i = 0 ; i < a4 ;i++){
        int x = rand() % 8 + 21;
        int y = rand() % 8 + 151;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='X';
    }
    int q4 = rand() % 2 + 1 ;
    for (int i = 0 ; i < q4 ;i++){
        int x = rand() % 8 + 21;
        int y = rand() % 8 + 151;
        if(map1[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map1[x][y]='R';
        }
        else if(p==1){
            map1[x][y]='H';
        }
        else if(p==2){
            map1[x][y]='8';
        }
    }
    map1[28][158] = '&';
    map1[20][152] = '+';
    map1[25][150] = '@';
    map1[22][152] = 'o';
    map1[28][156] = 'o';
    for(int i=3 ; i<4 ;i++){
        x2 = rand() % 8 + 21;
        y2 = rand() % 8 + 151;
        enemies_map1[i]=create_random_enemy(x2,y2);
        map1[x2][y2]=enemies_map1[i].face;
    }
    //  room ۵
    for (int i = 30; i < 36; i++) {
        map1[i][94] = '|';
        map1[i][110] = '|';
    }
    for (int i = 94; i <= 110; i++) {
        map1[30][i] = '-';
        map1[35][i] = '-';
    }
    for (int i = 31; i < 35; i++) {
        for (int j = 95; j < 110; j++) {
            map1[i][j] = '.';
        }
    }
    int n5 = rand() % 3 + 3;
    for (int i = 0 ; i < n5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='%';
    }
    int m5 = rand() % 3;
    for (int i = 0 ; i < m5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='T';
    }
    int q5 = rand() % 3 + 4 ;
    for (int i = 0 ; i < q5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map1[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map1[x][y]='R';
        }
        else if(p==1){
            map1[x][y]='H';
        }
        else if(p==2){
            map1[x][y]='8';
        }
    }
    int x = rand() % 4 + 31;
    int y = rand() % 15 + 95;
    map1[x][y]='3';
    //map1[32][94] = '+';
    map1[34][110] = '+';
    map1[31][99] = 'o';
    map1[33][107] = 'o';
    int s5 = rand() % 2;
    for (int i = 0 ; i < s5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map1[x][y]!='.'){
            continue;
            i--;
        }
        map1[x][y]='J';
    }
    // for(int i=4 ; i<5 ;i++){
    //     x2 = rand() % 4 + 31;
    //     y2 = rand() % 15 + 95;
    //     enemies_map1[i]=create_random_enemy(x2,y2);
    //     map1[x2][y2]=enemies_map1[i].face;
    // }
    //  room ۶
    for (int i = 28; i < 38; i++) {
        map1[i][10] = '|';
        map1[i][20] = '|';
    }
    for (int i = 10; i <= 20; i++) {
        map1[28][i] = '-';
        map1[37][i] = '-';
    }
    for (int i = 29; i < 37; i++) {
        for (int j = 11; j < 20; j++) {
            map1[i][j] = '.';
        }
    }
    int n6 = rand() % 3 + 2;
    for (int i = 0 ; i < n6 ;i++){
        int x = rand() % 8 + 29;
        int y = rand() % 9 + 11;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='%';
    }
    int m6 = rand() % 2+1;
    for (int i = 0 ; i < m6 ;i++){
        int x = rand() % 8 + 29;
        int y = rand() % 9 + 11;
        if(map1[x][y]!='.'){
            continue;
        }
        map1[x][y]='Z';
    }
    int q6 = rand() % 3 + 4 ;
    for (int i = 0 ; i < q6 ;i++){
        int x = rand() % 8 + 29;
        int y = rand() % 9 + 11;
        if(map1[x][y]!='.'){
            continue;
        }
        int p = rand()%2+1;
        if(p==0){
            map1[x][y]='R';
        }
        else if(p==1){
            map1[x][y]='H';
        }
        else if(p==2){
            map1[x][y]='8';
        }
    }
    map1[30][20] = '+';
    map1[30][12] = 'o';
    map1[36][17] = 'o';
    map1[36][13] = '<';
    int s6 = rand() % 3 + 4 ;
    for (int i = 0 ; i < s6 ;i++){
        int x = rand() % 8 + 29;
        int y = rand() % 9 + 11;
        if(map1[x][y]!='.'){
            continue;
            i--;
        }
        int p = rand()%2;
        if(p==0){
            map1[x][y]='*';
        }
        else if(p==1){
            map1[x][y]='/';
        }
    }
    for(int i = 0 ; i < 1 ; i++){
        int x = rand() % 8 + 29;
        int y = rand() % 9 + 11;
        map1[x][y]='3';
    }
    for(int i=4 ; i<5 ;i++){
        x2 = rand() % 8 + 29;
        y2 = rand() % 9 + 11;
        enemies_map1[i]=create_random_enemy(x2,y2);
        map1[x2][y2]=enemies_map1[i].face;
    }

    draw_path(24, 5, 59, 6,map1);
    draw_path(66,18, 100, 9,map1);
    draw_path(112, 14, 153, 19,map1);
    draw_path(149, 25, 110, 34,map1);
    draw_path(93, 32, 20, 30,map1);

    return 0;
}
int create_map2() {
    memset(map2, ' ', sizeof(map2));

    //  room ۱
    for (int i = 6; i < 15; i++) {
        map2[i][10] = '|';
        map2[i][18] = '|';
    }
    for (int i = 10; i <= 18; i++) {
        map2[6][i] = '-';
        map2[14][i] = '-';
    }
    for (int i = 7; i < 14; i++) {
        for (int j = 11; j < 18; j++) {
            map2[i][j] = '.';
        }
    }
    int q1 = rand() % 3 + 7;
    for (int i = 0 ; i < q1 ;i++){
        int x = rand() % 7 + 7;
        int y = rand() % 7 + 11;
        if(map2[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map2[x][y]='R';
        }
        else if(p==1){
            map2[x][y]='H';
        }
        else if(p==2){
            map2[x][y]='8';
        }
    }
    //map2[7][18] = '+';
    map2[10][12] = 'o';
    map2[8][16] = 'o';
    //map2[9][17] = '<';

    //  room ۲
    for (int i = 5; i < 14; i++) {
        map2[i][35] = '|';
        map2[i][48] = '|';
    }
    for (int i = 35; i <= 48; i++) {
        map2[5][i] = '-';
        map2[13][i] = '-';
    }
    for (int i = 6; i < 13; i++) {
        for (int j = 36; j < 48; j++) {
            map2[i][j] = '.';
        }
    }
    int n1 = rand() % 3 + 4;
    for (int i = 0 ; i < n1 ;i++){
        int x = rand() % 7 + 6;
        int y = rand() % 12 + 36;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='%';
    }
    int t1 = rand() % 2 + 1;
    for (int i = 0 ; i < t1 ;i++){
        int x = rand() % 7 + 6;
        int y = rand() % 12 + 36;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='T';
    }
    
    map2[6][36] = '&';
    map2[12][35] = '+';
    map2[9][48] = '@';
    map2[11][45] = 'o';
    map2[9][37] = 'o';
    int s1 = rand() % 3 + 2;
    for (int i = 0 ; i < s1 ;i++){
        int x = rand() % 7 + 6;
        int y = rand() % 12 + 36;
        if(map2[x][y]!='.'){
            continue;
            i--;
        }
        int p = rand()%2;
        if(p==0){
            map2[x][y]='/';
        }
        else if(p==1){
            map2[x][y]='*';
        }
    }
    int x2 = rand() % 7 + 6;
    int y2 = rand() % 12 + 36;
    for(int i=0 ; i<1 ;i++){
        enemies_map2[i]=create_random_enemy(x2,y2);
        map2[x2][y2]=enemies_map2[i].face;
    }
    //  room ۳
    for (int i = 3; i < 13; i++) {
        map2[i][120] = '|';
        map2[i][135] = '|';
    }
    for (int i = 120; i <= 135; i++) {
        map2[3][i] = '-';
        map2[12][i] = '-';
    }
    for (int i = 4; i < 12; i++) {
        for (int j = 121; j < 135; j++) {
            map2[i][j] = '.';
        }
    }
    int n3 = rand() % 3 + 4;
    for (int i = 0 ; i < n3 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='%';
    }
    int q3 = rand() % 3 +2;
    for (int i = 0 ; i < q3 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if(map2[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map2[x][y]='R';
        }
        else if(p==1){
            map2[x][y]='H';
        }
        else if(p==2){
            map2[x][y]='8';
        }
    }
    map2[7][120] = '+';
    map2[5][126] = 'o';
    map2[6][131] = 'o';
    map2[11][122] = 'o';
    for (int i = 0 ; i < 2 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if(map2[x][y]!='3'){
            continue;
        }
        map2[x][y]='%';
    }
    int s3 = rand() % 2 +2;
    for (int i = 0 ; i < s3 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if(map2[x][y]!='.'){
            i--;
            continue;
            
        }
        int p = rand()%3;
        if(p==0){
            map2[x][y]='J';
        }
        else if(p==1){
            map2[x][y]='L';
        }
        else if(p==2){
            map2[x][y]='*';
        }
    }
    for(int i=1 ; i<2 ;i++){
        x2 = rand() % 8 + 4;
        y2 = rand() % 14 + 121;
        enemies_map2[i]=create_random_enemy(x2,y2);
        map2[x2][y2]=enemies_map2[i].face;
    }
    //  room ۴
    for (int i = 30; i < 42; i++) {
        map2[i][160] = '|';
        map2[i][175] = '|';
    }
    for (int i = 160; i <= 175; i++) {
        map2[30][i] = '-';
        map2[41][i] = '-';
    }
    for (int i = 31; i < 41; i++) {
        for (int j = 161; j < 175; j++) {
            map2[i][j] = '.';
        }
    }
    int n2 = rand() % 3 + 2;
    for (int i = 0 ; i < n2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='%';
    }
    int t2 = rand() % 2 + 2;
    for (int i = 0 ; i < t2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='T';
    }
    int b2 = rand() % 2 + 2;
    for (int i = 0 ; i < b2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='V';
    }
    int q4 = rand() % 3 + 1;
    for (int i = 0 ; i < q4 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map2[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map2[x][y]='R';
        }
        else if(p==1){
            map2[x][y]='H';
        }
        else if(p==2){
            map2[x][y]='8';
        }
    }
    map2[30][167] = '+';
    map2[39][160] = '+';
    map2[35][169] = 'o';
    map2[40][163] = 'o';
    int s4 = rand() % 3 + 2;
    for (int i = 0 ; i < s4 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map2[x][y]!='.'){
            continue;
            i--;
        }
        int p = rand()%2;
        if(p==0){
            map2[x][y]='/';
        }
        else if(p==1){
            map2[x][y]='*';
        }
    }
    for(int i=2 ; i<4 ;i++){
        x2 = rand() % 10 + 31;
        y2 = rand()  % 14 + 161;
        enemies_map2[i]=create_random_enemy(x2,y2);
        map2[x2][y2]=enemies_map2[i].face;
    }
    //  room ۵
    for (int i = 30; i < 36; i++) {
        map2[i][94] = '|';
        map2[i][110] = '|';
    }
    for (int i = 94; i <= 110; i++) {
        map2[30][i] = '-';
        map2[35][i] = '-';
    }
    for (int i = 31; i < 35; i++) {
        for (int j = 95; j < 110; j++) {
            map2[i][j] = '.';
        }
    }
    int n5 = rand() % 3 + 3;
    for (int i = 0 ; i < n5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='%';
    }
    int q5 = rand() % 3 + 5;
    for (int i = 0 ; i < q5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map2[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map2[x][y]='R';
        }
        else if(p==1){
            map2[x][y]='H';
        }
        else if(p==2){
            map2[x][y]='8';
        }
    }
    map2[33][108] = '&';
    map2[32][94] = '@';
    map2[34][110] = '+';
    map2[31][99] = 'o';
    map2[33][107] = 'o';
    for (int i = 0 ; i < 2 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='3';
    }
    //  room ۶
    for (int i = 15; i < 23; i++) {
        map2[i][50] = '|';
        map2[i][60] = '|';
    }
    for (int i = 50; i <= 60; i++) {
        map2[15][i] = '-';
        map2[22][i] = '-';
    }
    for (int i = 16; i < 22; i++) {
        for (int j = 51; j < 60; j++) {
            map2[i][j] = '.';
        }
    }
    int n6 = rand() % 3 +2 ;
    for (int i = 0 ; i < n6 ;i++){
        int x = rand() % 6 + 16;
        int y = rand() % 9 + 51;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='%';
    }
    int t3 = rand() % 2 + 1;
    for (int i = 0 ; i < t3 ;i++){
        int x = rand() % 6 + 16;
        int y = rand() % 9 + 51;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='T';
    }
    int q6 = rand() % 3 + 1;
    for (int i = 0 ; i < q6 ;i++){
        int x = rand() % 6 + 16;
        int y = rand() % 9 + 51;
        if(map2[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map2[x][y]='R';
        }
        else if(p==1){
            map2[x][y]='H';
        }
        else if(p==2){
            map2[x][y]='8';
        }
    }
    map2[17][60] = '+';
    map2[20][53] = 'o';
    map2[19][57] = 'o';
    int s6 = rand() % 3 +1;
    for (int i = 0 ; i < s6 ;i++){
        int x = rand() % 6 + 16;
        int y = rand() % 9 + 51;
        if(map2[x][y]!='.'){
            continue;
            i--;
        }
        int p = rand()%2;
        if(p==0){
            map2[x][y]='/';
        }
        else if(p==1){
            map2[x][y]='*';
        }
    }
    for(int i=4 ; i<5 ;i++){
        x2 = rand() % 6 + 16;
        y2 = rand() % 9 + 51;
        enemies_map2[i]=create_random_enemy(x2,y2);
        map2[x2][y2]=enemies_map2[i].face;
    }
    //  room ۷
    for (int i = 28; i < 33; i++) {
        map2[i][11] = '|';
        map2[i][26] = '|';
    }
    for (int i = 11; i <= 26; i++) {
        map2[28][i] = '-';
        map2[32][i] = '-';
    }
    for (int i = 29; i < 32; i++) {
        for (int j = 12; j < 26; j++) {
            map2[i][j] = '.';
        }
    }
    int q7 = rand() % 3 ;
    for (int i = 0 ; i < q7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(map2[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map2[x][y]='R';
        }
        else if(p==1){
            map2[x][y]='H';
        }
        else if(p==2){
            map2[x][y]='8';
        }
    }
    int n7 = rand() % 3 + 2;
    for (int i = 0 ; i < n7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='%';
    }
    map2[28][20] = '+';
    map2[30][12] = 'o';
    map2[29][17] = 'o';
    int s7 = rand() % 3 ;
    for (int i = 0 ; i < s7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(map2[x][y]!='.'){
            i--;
            continue;
        }
        int p = rand()%2 + 1;
        if(p==1){
            map2[x][y]='L';
        }
        else if(p==2){
            map2[x][y]='J';
        }
    }
    for(int i=5 ; i<6 ;i++){
        x2 = rand() % 3 + 29;
        y2 = rand() % 14 + 12;
        enemies_map2[i]=create_random_enemy(x2,y2);
        map2[x2][y2]=enemies_map2[i].face;
    }
    for (int i = 0 ; i < 2 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(map2[x][y]!='.'){
            continue;
        }
        map2[x][y]='3';
    }
    for (int i = 0 ; i < 1 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        map2[x][y]='<';
    }
    draw_path(19, 7, 35, 12,map2);
    draw_path(49, 9, 120, 7,map2);
    draw_path(127, 13, 168, 29,map2);
    draw_path(159, 39, 110, 34,map2);
    draw_path(93, 32, 60, 17,map2);
    draw_path(49, 21, 19, 27,map2);
}
int create_map3() {
    memset(map3, ' ', sizeof(map3));

    //  room ۱
    for (int i = 6; i < 16; i++) {
        map3[i][35] = '|';
        map3[i][41] = '|';
    }
    for (int i = 35; i <= 41; i++) {
        map3[6][i] = '-';
        map3[15][i] = '-';
    }
    for (int i = 7; i < 15; i++) {
        for (int j = 36; j < 41; j++) {
            map3[i][j] = '.';
        }
    }
    int n3 = rand() % 3 + 1;
    for (int i = 0 ; i < n3 ;i++){
        int x = rand() % 8 + 7;
        int y = rand() % 5 + 36;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='%';
    }
    int t3 = rand() % 2+1;
    for (int i = 0 ; i < t3 ;i++){
        int x = rand() % 8 + 7;
        int y = rand() % 5 + 36;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='T';
    }
    int m3 = rand() % 2+1;
    for (int i = 0 ; i < m3 ;i++){
        int x = rand() % 8 + 7;
        int y = rand() % 5 + 36;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='X';
    }
    int q1 = rand() % 4 ;
    for (int i = 0 ; i < q1 ;i++){
        int x = rand() % 8 + 7;
        int y = rand() % 5 + 36;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map3[x][y]='R';
        }
        else if(p==1){
            map3[x][y]='H';
        }
        else if(p==2){
            map3[x][y]='8';
        }
    }
    map3[12][41] = '+';
    map3[11][40] = 'o';
    map3[9][37] = 'o';
    int x2 = rand() % 8 + 7;
    int y2 = rand() % 5 + 36;
    for(int i=0 ; i<1 ;i++){
        enemies_map3[i]=create_random_enemy(x2,y2);
        map3[x2][y2]=enemies_map3[i].face;
    }
    int s1 = rand() % 2+1 ;
    for (int i = 0 ; i < s1 ;i++){
        int x = rand() % 8 + 7;
        int y = rand() % 5 + 36;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%2;
        if(p==0){
            map3[x][y]='J';
        }
        else if(p==1){
            map3[x][y]='*';
        }
    }
    x2 = rand() % 8 + 7;
    y2 = rand() % 5 + 36;
    map3[x2][y2]='<';
    //  room ۲
    for (int i = 12; i < 17; i++) {
        map3[i][70] = '|';
        map3[i][84] = '|';
    }
    for (int i = 70; i <= 84; i++) {
        map3[12][i] = '-';
        map3[16][i] = '-';
    }
    for (int i = 13; i < 16; i++) {
        for (int j = 71; j < 84; j++) {
            map3[i][j] = '.';
        }
    }
    int n9 = rand() % 4 + 2;
    for (int i = 0 ; i < n9 ;i++){
        int x = rand() % 3 + 13;
        int y = rand() % 13 + 71;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='%';
    }
    int t9 = rand() % 4 + 2;
    for (int i = 0 ; i < t9 ;i++){
        int x = rand() % 3 + 13;
        int y = rand() % 13 + 71;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='T';
    }
    int q2 = rand() % 3 + 1;
    for (int i = 0 ; i < q2 ;i++){
        int x = rand() % 3 + 13;
        int y = rand() % 13 + 71;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map3[x][y]='R';
        }
        else if(p==1){
            map3[x][y]='H';
        }
        else if(p==2){
            map3[x][y]='8';
        }
    }
    map3[15][72] = '&';
    map3[13][70] = '@';
    map3[14][84] = '+';
    map3[13][75] = 'o';
    map3[15][80] = 'o';
    for(int i=1 ; i<2 ;i++){
        x2=rand() % 3 + 13;
        y2=rand() % 13 + 71;
        enemies_map3[i]=create_random_enemy(x2,y2);
        map3[x2][y2]=enemies_map3[i].face;
    }
    int s2 = rand() % 2 + 1;
    for (int i = 0 ; i < s2 ;i++){
        int x = rand() % 3 + 13;
        int y = rand() % 13 + 71;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%2;
        if(p==0){
            map3[x][y]='L';
        }
        else if(p==1){
            map3[x][y]='J';
        }
    }
    int b2 = rand() % 3 + 1;
    for (int i = 0 ; i < b2 ;i++){
        int x = rand() % 3 + 13;
        int y = rand() % 13 + 71;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%2;
        if(p==0){
            map3[x][y]='V';
        }
        else if(p==1){
            map3[x][y]='X';
        }
    }
    for (int i = 0 ; i < n9 ;i++){
        int x = rand() % 3 + 13;
        int y = rand() % 13 + 71;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='3';
    }
    //  room ۳
    for (int i = 5; i < 20; i++) {
        map3[i][125] = '|';
        map3[i][145] = '|';
    }
    for (int i = 125; i <= 145; i++) {
        map3[5][i] = '-';
        map3[19][i] = '-';
    }
    for (int i = 6; i < 19; i++) {
        for (int j = 126; j < 145; j++) {
            map3[i][j] = '.';
        }
    }
    int n1 = rand() % 3 + 3;
    for (int i = 0 ; i < n1 ;i++){
        int x = rand() % 13 + 6;
        int y = rand() % 9 + 126;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='%';
    }
    int t1 = rand() % 5 + 3;
    for (int i = 0 ; i < t1 ;i++){
        int x = rand() % 13 + 6;
        int y = rand() % 9 + 126;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='T';
    }
    int m1 = rand() % 2+1;
    for (int i = 0 ; i < t3 ;i++){
        int x = rand() % 13 + 6;
        int y = rand() % 9 + 126;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='X';
    }
    int q3 = rand() % 3 + 1;
    for (int i = 0 ; i < q3 ;i++){
        int x = rand() % 13 + 6;
        int y = rand() % 9 + 126;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map3[x][y]='R';
        }
        else if(p==1){
            map3[x][y]='H';
        }
        else if(p==2){
            map3[x][y]='8';
        }
    }
    //mvprintw(7,125,"+");
    map3[19][132] = '+';
    map3[10][140] = 'o';
    map3[15][136] = 'o';
    map3[18][130] = 'o';
    for(int i=2 ; i<3 ;i++){
        x2=rand() % 13 + 6;
        y2= rand() % 9 + 126;
        enemies_map3[i]=create_random_enemy(x2,y2);
        map3[x2][y2]=enemies_map3[i].face;
    }
    int s3 = rand() % 3 + 1;
    for (int i = 0 ; i < s3 ;i++){
        int x = rand() % 13 + 6;
        int y = rand() % 9 + 126;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map3[x][y]='/';
        }
        else if(p==1){
            map3[x][y]='*';
        }
    }
    //  room ۴
    for (int i = 30; i < 42; i++) {
        map3[i][160] = '|';
        map3[i][175] = '|';
    }
    for (int i = 160; i <= 175; i++) {
        map3[30][i] = '-';
        map3[41][i] = '-';
    }
    for (int i = 31; i < 41; i++) {
        for (int j = 161; j < 175; j++) {
            map3[i][j] = '.';
        }
    }
    int n2 = rand() % 3 + 4;
    for (int i = 0 ; i < n2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='%';
    }
    int t2 = rand() % 5 + 3;
    for (int i = 0 ; i < t2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='T';
    }
    int m2 = rand() % 2 + 1;
    for (int i = 0 ; i < m2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='Z';
    }
    int q4 = rand() % 3;
    for (int i = 0 ; i < q4 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map3[x][y]='R';
        }
        else if(p==1){
            map3[x][y]='H';
        }
        else if(p==2){
            map3[x][y]='8';
        }
    }
    //mvprintw(30,167,"+");
    map3[39][160] = '+';
    map3[35][169] = 'o';
    map3[40][163] = 'o';
    for(int i=3 ; i<5 ;i++){
        x2=rand() % 10 + 31;
        y2= rand() % 14 + 161;
        enemies_map3[i]=create_random_enemy(x2,y2);
        map3[x2][y2]=enemies_map3[i].face;
    }
    for (int i = 0 ; i < 2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='3';
    }
    //  room ۵
    for (int i = 30; i < 36; i++) {
        map3[i][84] = '|';
        map3[i][100] = '|';
    }
    for (int i = 84; i <= 100; i++) {
        map3[30][i] = '-';
        map3[35][i] = '-';
    }
    for (int i = 31; i < 35; i++) {
        for (int j = 85; j < 100; j++) {
            map3[i][j] = '.';
        }
    }
    map3[34][87] = '&';
    map3[32][84] = '+';
    map3[34][100] = '@';
    map3[31][99] = 'o';
    map3[33][86] = 'o';
    int t5 = rand() % 5 + 3;
    for (int i = 0 ; i < t5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 85;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='T';
    }
    int a5 = rand() % 2 + 1;
    for (int i = 0 ; i < a5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 85;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='Z';
    }
    int n5 = rand() % 5 + 3;
    for (int i = 0 ; i < n5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 85;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='%';
    }
    int q5 = rand() % 3+2;
    for (int i = 0 ; i < q5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 85;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map3[x][y]='R';
        }
        else if(p==1){
            map3[x][y]='H';
        }
        else if(p==2){
            map3[x][y]='8';
        }
    }
    int s5 = rand() % 2+3;
    for (int i = 0 ; i < s5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 85;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map3[x][y]='J';
        }
        else if(p==1){
            map3[x][y]='L';
        }
        else if(p==2){
            map3[x][y]='*';
        }
    }
    for(int i=5 ; i<6 ;i++){
        x2=rand() % 4 + 31;
        y2= rand() % 15 + 85;
        enemies_map3[i]=create_random_enemy(x2,y2);
        map3[x2][y2]=enemies_map3[i].face;
    }
    //  room ۶
    for (int i = 21; i < 35; i++) {
        map3[i][12] = '|';
        map3[i][26] = '|';
    }
    for (int i = 12; i <= 26; i++) {
        map3[21][i] = '-';
        map3[34][i] = '-';
    }
    for (int i = 22; i < 34; i++) {
        for (int j = 13; j < 26; j++) {
            map3[i][j] = '.';
        }
    }
    int n7 = rand() % 5 + 4;
    for (int i = 0 ; i < n7 ;i++){
        int x = rand() % 12 + 22;
        int y = rand() % 13 + 13;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='%';
    }
    int t7 = rand() % 3 + 2;
    for (int i = 0 ; i < t7 ;i++){
        int x = rand() % 12 + 22;
        int y = rand() % 13 + 13;
        if(map3[x][y]!='.'){
            continue;
        }
        map3[x][y]='T';
    }
    int q6 = rand() % 7 + 4;
    for (int i = 0 ; i < q6 ;i++){
        int x = rand() % 12 + 22;
        int y = rand() % 13 + 13;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map3[x][y]='R';
        }
        else if(p==1){
            map3[x][y]='H';
        }
        else if(p==2){
            map3[x][y]='8';
        }
    }
    map3[22][26] = '+';
    map3[30][20] = 'o';
    //map3[30][20] = '<';
    int s6 = rand() % 3 + 1;
    for (int i = 0 ; i < s6 ;i++){
        int x = rand() % 12 + 22;
        int y = rand() % 13 + 13;
        if(map3[x][y]!='.'){
            continue;
        }
        int p = rand()%2;
        if(p==0){
            map3[x][y]='/';
        }
        else if(p==1){
            map3[x][y]='*';
        }
    }
    draw_path(27, 22, 84, 32,map3);
    draw_path(101, 34, 160, 39,map3);
    draw_path(167, 29, 131, 20,map3);
    draw_path(124, 7, 84, 14,map3);
    draw_path(69, 13, 41, 12,map3);
}
int create_map4() {
    memset(map4, ' ', sizeof(map4));
    //  room ۱
    for (int i = 6; i < 15; i++) {
        map4[i][10] = '|';
        map4[i][18] = '|';
    }
    for (int i = 10; i <= 18; i++) {
        map4[6][i] = '-';
        map4[14][i] = '-';
    }
    for (int i = 7; i < 14; i++) {
        for (int j = 11; j < 18; j++) {
            map4[i][j] = '.';
        }
    }
    int n0 = rand() % 3+3;
    for (int i = 0 ; i < n0 ;i++){
        int x = rand() % 7 + 7;
        int y = rand() % 7 + 11;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='%';
    }
    int t0 = rand() % 4+4;
    for (int i = 0 ; i < t0 ;i++){
        int x = rand() % 7 + 7;
        int y = rand() % 7 + 11;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='Z';
    }
    int a1 = rand() % 5+6;
    for (int i = 0 ; i < a1 ;i++){
        int x = rand() % 7 + 7;
        int y = rand() % 7 + 11;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='T';
    }
    map4[7][18] = '+';
    map4[10][12] = 'o';
    map4[8][16] = 'o';
    for (int i = 0 ; i < 4 ;i++){
        int x = rand() % 7 + 7;
        int y = rand() % 7 + 11;
        if(map4[x][y]!='.'){
            i--;
            continue;
        }
        int p = rand() % 4;
        if(p==0){
            map4[x][y]='J';
        }
        else if(p==1){
            map4[x][y]='*';
        }
        else if(p==2){
            map4[x][y]='L';
        }
        else if(p==3){
            map4[x][y]='/';
        }
    }
    int x = rand() % 7 + 7;
    int y = rand() % 7 + 11;
    for(int i=0 ; i<1 ;i++){
        enemies_map4[i]=create_random_enemy(x,y);
        map4[x][y]=enemies_map4[i].face;
    }
    map4[10][15]='A';
    //  room ۲
    for (int i = 5; i < 14; i++) {
        map4[i][35] = '|';
        map4[i][48] = '|';
    }
    for (int i = 35; i <= 48; i++) {
        map4[5][i] = '-';
        map4[13][i] = '-';
    }
    for (int i = 6; i < 13; i++) {
        for (int j = 36; j < 48; j++) {
            map4[i][j] = '.';
        }
    }
    int n1 = rand() % 3+3;
    for (int i = 0 ; i < n1 ;i++){
        int x = rand() % 7 + 6;
        int y = rand() % 12 + 36;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='%';
    }
    int t1 = rand() % 2+3;
    for (int i = 0 ; i < t1 ;i++){
        int x = rand() % 7 + 6;
        int y = rand() % 12 + 36;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='T';
    }
    int q2 = rand() % 3 + 2 ;
    for (int i = 0 ; i < q2 ;i++){
        int x = rand() % 7 + 6;
        int y = rand() % 12 + 36;
        if(map4[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map4[x][y]='R';
        }
        else if(p==1){
            map4[x][y]='H';
        }
        else if(p==2){
            map4[x][y]='8';
        }
    }
    map4[6][37] = '&';
    map4[12][35] = '@';
    map4[9][48] = '+';
    map4[11][45] = 'o';
    map4[9][37] = 'o';
    for(int i=1 ; i<2 ;i++){
        x=rand() % 7 + 6;
        y=rand() % 12 + 36;
        enemies_map4[i]=create_random_enemy(x,y);
        map4[x][y]=enemies_map4[i].face;
    }
    //  room ۳
    for (int i = 3; i < 13; i++) {
        map4[i][120] = '|';
        map4[i][135] = '|';
    }
    for (int i = 120; i <= 135; i++) {
        map4[3][i] = '-';
        map4[12][i] = '-';
    }
    for (int i = 4; i < 12; i++) {
        for (int j = 121; j < 135; j++) {
            map4[i][j] = '.';
        }
    }
    int n5 = rand() % 3+4;
    for (int i = 0 ; i < n5 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='%';
    }
    int t5 = rand() % 2+2;
    for (int i = 0 ; i < t5 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='T';
    }
    int m5 = rand() % 2+1;
    for (int i = 0 ; i < m5 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='Z';
    }
    int q3 = rand() % 5 + 5 ;
    for (int i = 0 ; i < q3 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if(map4[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map4[x][y]='R';
        }
        else if(p==1){
            map4[x][y]='H';
        }
        else if(p==2){
            map4[x][y]='8';
        }
    }
    map4[12][127] = '+';
    map4[5][126] = 'o';
    map4[6][131] = 'o';
    map4[11][122] = 'o';
    int s3 = rand() % 2 + 1 ;
    for (int i = 0 ; i < s3 ;i++){
        int x = rand() % 8 + 4;
        int y = rand() % 14 + 121;
        if(map4[x][y]!='.'){
            continue;
        }
        int p = rand()%2;
        if(p==0){
            map4[x][y]='/';
        }
        else if(p==1){
            map4[x][y]='*';
        }
    }
    //  room ۴
    for (int i = 30; i < 42; i++) {
        map4[i][160] = '|';
        map4[i][175] = '|';
    }
    for (int i = 160; i <= 175; i++) {
        map4[30][i] = '-';
        map4[41][i] = '-';
    }
    for (int i = 31; i < 41; i++) {
        for (int j = 161; j < 175; j++) {
            map4[i][j] = '.';
        }
    }
    int n2 = rand() % 3+2;
    for (int i = 0 ; i < n2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='%';
    }
    int t2 = rand() % 2+4;
    for (int i = 0 ; i < t2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='T';
    }
    int m2 = rand() % 2;
    for (int i = 0 ; i < m2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='X';
    }
    int q4 = rand() % 2 + 2 ;
    for (int i = 0 ; i < q4 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map4[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map4[x][y]='R';
        }
        else if(p==1){
            map4[x][y]='H';
        }
        else if(p==2){
            map4[x][y]='8';
        }
    }
    map4[40][174] = '&';
    map4[30][167] = '@';
    map4[39][160] = '+';
    map4[35][169] = 'o';
    map4[40][163] = 'o';
    for(int i=2 ; i<4 ;i++){
        x=rand() % 10 + 31;
        y=rand() % 14 + 161;
        enemies_map4[i]=create_random_enemy(x,y);
        map4[x][y]=enemies_map4[i].face;
    }
    int s4 = rand() % 3 + 2 ;
    for (int i = 0 ; i < s4 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map4[x][y]!='.'){
            continue;
        }
        int p = rand()%2;
        if(p==0){
            map4[x][y]='/';
        }
        else if(p==1){
            map4[x][y]='*';
        }
    }
    for (int i = 0 ; i < 2 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 161;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='3';
    }
    //  room ۵
    for (int i = 30; i < 36; i++) {
        map4[i][94] = '|';
        map4[i][110] = '|';
    }
    for (int i = 94; i <= 110; i++) {
        map4[30][i] = '-';
        map4[35][i] = '-';
    }
    for (int i = 31; i < 35; i++) {
        for (int j = 95; j < 110; j++) {
            map4[i][j] = '.';
        }
    }
    int n3 =rand() % 2 + 3;
    for (int i = 0 ; i < n3 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='%';
    }
    int t3 = rand() % 2;
    for (int i = 0 ; i < t3 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='T';
    }
    int m3 = rand() % 2 + 1;
    for (int i = 0 ; i < m3 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='X';
    }
    int q5 = rand() % 2 + 2 ;
    for (int i = 0 ; i < q5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map4[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map4[x][y]='R';
        }
        else if(p==1){
            map4[x][y]='H';
        }
        else if(p==2){
            map4[x][y]='8';
        }
    }
    map4[32][94] = '+';
    map4[31][99] = 'o';
    map4[33][107] = 'o';
    for(int i=4; i<5 ;i++){
        x=rand() %  4 + 31;
        y=rand() % 15 + 95;
        enemies_map4[i]=create_random_enemy(x,y);
        map4[x][y]=enemies_map4[i].face;
    }
    int s5 = rand() % 3 + 2 ;
    for (int i = 0 ; i < s5 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map4[x][y]!='.'){
            continue;
        }
        int p = rand()%2;
        if(p==0){
            map4[x][y]='*';
        }
        else if(p==1){
            map4[x][y]='/';
        }
    }
    for (int i = 0 ; i < 2 ;i++){
        int x = rand() % 4 + 31;
        int y = rand() % 15 + 95;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='3';
    }
    //  room ۶
    for (int i = 15; i < 23; i++) {
        map4[i][50] = '|';
        map4[i][60] = '|';
    }
    for (int i = 50; i <= 60; i++) {
        map4[15][i] = '-';
        map4[22][i] = '-';
    }
    for (int i = 16; i < 22; i++) {
        for (int j = 51; j < 60; j++) {
            map4[i][j] = '.';
        }
    }
    int t6 = rand() % 3 ;
    for (int i = 0 ; i < t6 ;i++){
        int x = rand() % 6 + 16;
        int y = rand() % 9 + 51;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='T';
    }
    int n6 = rand() % 3 ;
    for (int i = 0 ; i < n6 ;i++){
        int x = rand() % 6 + 16;
        int y = rand() % 9 + 51;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='%';
    }
    int q6 = rand() % 5 + 4 ;
    for (int i = 0 ; i < q6 ;i++){
        int x = rand() % 6 + 16;
        int y = rand() % 9 + 51;
        if(map4[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map4[x][y]='R';
        }
        else if(p==1){
            map4[x][y]='H';
        }
        else if(p==2){
            map4[x][y]='8';
        }
    }
    map4[16][52] = '&';
    map4[17][60] = '@';
    map4[21][50] = '+';
    map4[20][53] = 'o';
    map4[19][57] = 'o';

    // room7
    for (int i = 28; i < 33; i++) {
        map4[i][11] = '|';
        map4[i][26] = '|';
    }
    for (int i = 11; i <= 26; i++) {
        map4[28][i] = '-';
        map4[32][i] = '-';
    }
    for (int i = 29; i < 32; i++) {
        for (int j = 12; j < 26; j++) {
            map4[i][j] = '.';
        }
    }
    int m7 = rand() % 2 + 1 ;
    for (int i = 0 ; i < m7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='Z';
    }
    int t7 = rand() % 3 ;
    for (int i = 0 ; i < t7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='T';
    }
    int n7 = rand() % 3 + 1 ;
    for (int i = 0 ; i < n7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='%';
    }
    int q7 = rand() % 2 + 2 ;
    for (int i = 0 ; i < q7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(map4[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map4[x][y]='R';
        }
        else if(p==1){
            map4[x][y]='H';
        }
        else if(p==2){
            map4[x][y]='8';
        }
    }
    map4[28][20] = '+';
    map4[32][24] = '+';
    map4[30][12] = 'o';
    map4[29][17] = 'o';
    for(int i=5; i<6 ;i++){
        x=rand() % 3 + 29;
        y=rand() % 14 + 12;
        enemies_map4[i]=create_random_enemy(x,y);
        map4[x][y]=enemies_map4[i].face;
    }
    int s7 = rand() % 2 + 3 ;
    for (int i = 0 ; i < s7 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(map4[x][y]!='.'){
            i--;
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map4[x][y]='*';
        }
        else if(p==1){
            map4[x][y]='J';
        }
    }
    for (int i = 0 ; i < 2 ;i++){
        int x = rand() % 3 + 29;
        int y = rand() % 14 + 12;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='3';
    }
    // room 8
    for (int i = 30; i < 42; i++) {
        map4[i][45] = '|';
        map4[i][60] = '|';
    }
    for (int i = 45; i <= 60; i++) {
        map4[30][i] = '-';
        map4[41][i] = '-';
    }
    for (int i = 31; i < 41; i++) {
        for (int j = 46; j < 60; j++) {
            map4[i][j] = '.';
        }
    }
    int m8 = rand() % 2 + 1 ;
    for (int i = 0 ; i < m8 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 46;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='Z';
    }
    int t8 = rand() % 3 + 3 ;
    for (int i = 0 ; i < t8 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 46;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='T';
    }
    int n8 = rand() % 3 + 3 ;
    for (int i = 0 ; i < n8 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 46;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='%';
    }
    int q8 = rand() % 5 + 5 ;
    for (int i = 0 ; i < q8 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 46;
        if(map4[x][y]!='.'){
            continue;
        }
        int p = rand()%3;
        if(p==0){
            map4[x][y]='R';
        }
        else if(p==1){
            map4[x][y]='H';
        }
        else if(p==2){
            map4[x][y]='8';
        }
    }
    map4[33][55] = 'o';
    map4[34][56] = 'o';
    int s8 = rand() % 3 + 2 ;
    for (int i = 0 ; i < s8 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 46;
        if(map4[x][y]!='.'){
            i--;
            continue;
        }
        int p = rand()%2;
        if(p==0){
            map4[x][y]='L';
        }
        else if(p==1){
            map4[x][y]='*';
        }
    }
    int b8 = rand() % 2 + 2 ;
    for (int i = 0 ; i < b8 ;i++){
        int x = rand() % 10 + 31;
        int y = rand() % 14 + 46;
        if(map4[x][y]!='.'){
            continue;
        }
        map4[x][y]='V';
    }
    draw_path(34, 12, 18, 7,map4);
    draw_path(119, 7, 48, 9,map4);
    draw_path(167, 29, 126, 13,map4);
    draw_path(111, 34, 160, 39,map4);
    draw_path(61, 17, 94, 32,map4);
    draw_path(20, 27, 50, 21,map4);
    draw_path(44, 37, 23, 33,map4);
}
int handle_input(Player *player) {
    if(p_user.weapon_bar.arrow<=0 && p_user.weapon_bar.dagger<=0 && p_user.weapon_bar.sword<=0 && p_user.weapon_bar.magic_wand<=0){
        p_user.current_weapon='m';
    }
    night=0;
    int t = telesm(player);
    attroff(COLOR_PAIR(6));
    if(strcmp(current_music,main_music)!=0 && t==0){
        strcpy(current_music,main_music);
        play_music(main_music);
    }
    else if(t==1&&is_music_playing&&cp==0){
        cp=1;
        stop_music();
        play_music("peritune-spook4(chosic.com).mp3");
        strcpy(current_music,"peritune-spook4(chosic.com).mp3");
    }
    else if(t==0&&strcmp(current_music,"peritune-spook4(chosic.com).mp3")==0){
        stop_music();
    }
    
    if(p_user.health<=0){
        clear();
        final_result(0);
    }
    if(p_user.hunger>=100){
        p_user.hunger=100;
        p_user.health=10000;
    }
    if(p_user.level_num==1){
        int ch = getch();
        if(ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='6'||ch=='7'||ch=='8'||ch=='9'){
            enemy_checker2(player);
            if(Gspell==1&&Gspellc<=10){
                Gspellc++;
            }
            else if(Gspellc>10){
                Gspell=0;
            }
            if(Hspell==1&&Hspellc<=10){
                Hspellc++;
            }
            else if(Hspellc>10){
                Hspell=0;
            }
            pace_counter1++;
            if(p_user.difficulty==0){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=5;
                }
                else{
                    p_user.hunger-=1;
                }
            }
            if(p_user.difficulty==1){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=10;
                }
                else{
                    p_user.hunger-=2;
                }
            }
            if(p_user.difficulty==2){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=20;
                }
                else{
                    p_user.hunger-=3;
                }
            }
            
        }
        int new_x = player->x, new_y = player->y;
        if (ch == 's' && pace_counter2<5) {
            pace=2;
            pace_counter1=0;
            pace_counter2++;

        }
        if(pace_counter1>=5){
            pace = 1;
        }
        switch (ch) {
        case '1': new_x -= pace; new_y += pace; break;
        case '2': new_y += pace; break;
        case '3': new_x += pace; new_y += pace; break;
        case '4': new_x -= pace; break;
        case '6': new_x += pace; break;
        case '7': new_x -= pace; new_y -= pace; break;
        case '8': new_y -= pace; break;
        case '9': new_x += pace; new_y -= pace; break;
        case 'e': food_table();
            refresh_map(player,memory_map1,map1);
            break;
        case 'q':
        if(is_logged_in==1){
            save_info();
            save_map(map1);
            main_menu();
        }
        else{
            main_menu();
        }
            
        case 'm':
            show_count++;
            if(show_count>=4){
                break;
            }
            show_full_map_temporarily(player);
            break;
        case 'p': spell_table();
            refresh_map(player,memory_map1,map1);
            break;
        case 'i':weapon_table();
            refresh_map(player,memory_map1,map1);
            break;
        case ' ':
            damage_enemy(p_user.level_num,get_room_id(player->x,player->y),p_user.current_weapon,player);
            break;
        case 127:
            save_map(map1);
        break;
        }

        if (is_valid_move(new_x, new_y,map1) && map1[new_y][new_x]!='<') {
            clear_player(player);

            player->prev_char = map1[new_y][new_x];  
            player->x = new_x;
            player->y = new_y;
            if (new_x == 110 && new_y == 14) {
                map1[14][111]='+';
            }
            else if (new_x == 95 && new_y == 32) {
                map1[32][94]='+'; 
            }
            else if(map1[new_y][new_x]=='&'){
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    map1[28][158] = '.';
                    map1[25][150] = 'Q';
                }
            }

            else if(map1[new_y][new_x]=='%'||map1[new_y][new_x]=='X'||map1[new_y][new_x]=='V'&&night==0)
            {
                if(message(5,40)=='\n'){ 
                    food_manager(map1[new_y][new_x]);
                    if(full_food==0){
                        map1[new_y][new_x]='.';
                    }   
                }
            }

            else if(map1[new_y][new_x]=='T'||map1[new_y][new_x]=='Z'&&night==0)
            {
                gold_manager(map1[new_y][new_x]);
                map1[new_y][new_x]='.';
            }
            else if(map1[new_y][new_x]=='3'){
                start_war();
                clear();
            }
            else if(map1[new_y][new_x]=='H'||map1[new_y][new_x]=='R'||map1[new_y][new_x]=='8'&&night==0){
                if(message(5,40)=='\n'){
                    spell_manager(map1[new_y][new_x]);
                    if(full_spell==0){
                        map1[new_y][new_x]='.';
                    } 
                }
            }
            else if(map1[new_y][new_x]=='L'||map1[new_y][new_x]=='*'||map1[new_y][new_x]=='J'||map1[new_y][new_x]=='/'&&night==0)
            {
                if(message(5,40)=='\n'){ 
                    weapon_manager(map1[new_y][new_x]);
                    map1[new_y][new_x]='.';
                }
            }
            else if(map1[new_y][new_x]=='A')
            {
               start_battle();
            }
            refresh_map(player,memory_map1,map1);  
        }
        else if(map1[new_y][new_x]=='<'){
            p_user.score+=20;
            start_level2();
        }
        
    }
    else if(p_user.level_num==2){
        int ch = getch();
        if(ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='6'||ch=='7'||ch=='8'||ch=='9'){
            enemy_checker2(player);
            if(Gspell==1&&Gspellc<=10){
                Gspellc++;
            }
            else if(Gspellc>10){
                Gspell=0;
            }
            if(Hspell==1&&Hspellc<=10){
                Hspellc++;
            }
            else if(Hspellc>10){
                Hspell=0;
            }
            pace_counter1++;
            if(p_user.difficulty==0){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=5;
                }
                else{
                    p_user.hunger-=1;
                }
            }
            if(p_user.difficulty==1){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=10;
                }
                else{
                    p_user.hunger-=2;
                }
            }
            if(p_user.difficulty==2){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=20;
                }
                else{
                    p_user.hunger-=3;
                }
            }
            
        }
        int new_x = player->x, new_y = player->y;
        if (ch == 's' && pace_counter2<5) {
        pace=2;
        pace_counter1=0;
        pace_counter2++;

        }
        if(pace_counter1>=5){
            pace = 1;
        }
        switch (ch) {
        case '1': new_x -= pace; new_y += pace; break;
        case '2': new_y += pace; break;
        case '3': new_x += pace; new_y += pace; break;
        case '4': new_x -= pace; break;
        case '6': new_x += pace; break;
        case '7': new_x -= pace; new_y -= pace; break;
        case '8': new_y -= pace; break;
        case '9': new_x += pace; new_y -= pace; break;
            case 'e': food_table();
            refresh_map(player,memory_map2,map2);
            break;
            case 'q':
            if(is_logged_in==1){
                save_info();
                save_map(map2);
                main_menu();
            }
            else{
                main_menu();
            }
            case 'm':        
                show_count++;
                if(show_count>=4){
                    break;
                }
                show_full_map_temporarily(player);
            break;
            case 'p': spell_table();
                refresh_map(player,memory_map2,map2);
                break;
            case 'i':weapon_table();
                refresh_map(player,memory_map2,map2);
                break;
            case ' ':
                damage_enemy(p_user.level_num,get_room_id(player->x,player->y),p_user.current_weapon,player);
            break;
            case 127:
                save_map(map2);
            break;
        }

        if (is_valid_move(new_x, new_y,map2) && map2[new_y][new_x]!='<') {
            clear_player(player);

            player->prev_char = map2[new_y][new_x];  
            player->x = new_x;
            player->y = new_y;
            if (new_x == 17 && new_y == 7) {
                map2[7][18]='+';
            }
            else if (new_x == 128 && new_y == 11) {
                map2[12][128]='+';
            }
            else if (new_x == 51 && new_y == 21) {
                map2[21][50]='+';
            }
            else if(map2[new_y][new_x]=='&' && get_room_id(new_x,new_y)==2){
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    map2[6][36] = '.';
                    map2[9][48] = 'Q';
                }
            }
            else if(map2[new_y][new_x]=='&' && get_room_id(new_x,new_y)==5){
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    map2[33][108] = '.';
                    map2[32][94] = 'Q';
                }
            }
            else if((map2[new_y][new_x]=='%'||map2[new_y][new_x]=='X'||map2[new_y][new_x]=='V')&&night==0)
            {
                if(message(5,40)=='\n'){
                    food_manager(map2[new_y][new_x]);
                    if(full_food==0){
                        map2[new_y][new_x]='.';
                    }
                }
            }
            else if(map1[new_y][new_x]=='3'){
                start_war();
                clear();
            }
            else if((map2[new_y][new_x]=='T'||map2[new_y][new_x]=='Z')&&night==0)
            {
                gold_manager(map2[new_y][new_x]);
                map2[new_y][new_x]='.';
            }
            else if(map2[new_y][new_x]=='3'){
                p_user.health-=10;
            }
            else if((map2[new_y][new_x]=='H'||map2[new_y][new_x]=='R'||map2[new_y][new_x]=='8')&&night==0){
                if(message(5,40)=='\n'){
                    spell_manager(map2[new_y][new_x]);
                    if(full_spell==0){
                        map2[new_y][new_x]='.';
                    } 
                }
            }
            else if((map2[new_y][new_x]=='L'||map2[new_y][new_x]=='*'||map2[new_y][new_x]=='J'||map2[new_y][new_x]=='/')&&night==0)
            {
                if(message(5,40)=='\n'){ 
                    weapon_manager(map2[new_y][new_x]);
                    map2[new_y][new_x]='.';
                }
            }
            refresh_map(player,memory_map2,map2);
        }
        else if(map2[new_y][new_x]=='<'){
            p_user.score+=30;
            start_level3();
        }
    }
    else if(p_user.level_num==3){
        int ch = getch();
        if(ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='6'||ch=='7'||ch=='8'||ch=='9'){
            enemy_checker2(player);
            if(Gspell==1&&Gspellc<=10){
                Gspellc++;
            }
            else if(Gspellc>10){
                Gspell=0;
            }
            if(Hspell==1&&Hspellc<=10){
                Hspellc++;
            }
            else if(Hspellc>10){
                Hspell=0;
            }
            pace_counter1++;
            if(p_user.difficulty==0){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=5;
                }
                else{
                    p_user.hunger-=1;
                }
            }
            if(p_user.difficulty==1){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=10;
                }
                else{
                    p_user.hunger-=2;
                }
            }
            if(p_user.difficulty==2){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=20;
                }
                else{
                    p_user.hunger-=3;
                }
            }
            
        }
        int new_x = player->x, new_y = player->y;
        if (ch == 's' && pace_counter2<5) {
        pace=2;
        pace_counter1=0;
        pace_counter2++;

        }
        if(pace_counter1>=5){
            pace = 1;
        }
        switch (ch) {
        case '1': new_x -= pace; new_y += pace; break;
        case '2': new_y += pace; break;
        case '3': new_x += pace; new_y += pace; break;
        case '4': new_x -= pace; break;
        case '6': new_x += pace; break;
        case '7': new_x -= pace; new_y -= pace; break;
        case '8': new_y -= pace; break;
        case '9': new_x += pace; new_y -= pace; break;
        case 'e': food_table();
            refresh_map(player,memory_map3,map3);
            break;
        case 'q':
            if(is_logged_in==1){
                save_info();
                save_map(map3);
                main_menu();
            }
            else{
                main_menu();
            }
        case 'm':            
            show_count++;
            if(show_count>=4){
                break;
            }
            show_full_map_temporarily(player);
            break;
            case 'p': spell_table();
                refresh_map(player,memory_map3,map3);
                break;
            case 'i':weapon_table();
                refresh_map(player,memory_map3,map3);
                break;
            case ' ':
                damage_enemy(p_user.level_num,get_room_id(player->x,player->y),p_user.current_weapon,player);
                break;
            case 127:
                save_map(map3);
                save_info();
            break;
        }
        

        if (is_valid_move(new_x, new_y,map3)&& map3[new_y][new_x]!='<') {
            clear_player(player);

            player->prev_char = map3[new_y][new_x];  
            player->x = new_x;
            player->y = new_y;
            if (new_x == 167 && new_y == 31) {
                map3[30][167]='+';
            }
            else if (new_x == 126 && new_y == 7) {
                map3[7][125]='+';
            }
            else if(map3[new_y][new_x]=='&' && get_room_id(new_x,new_y)==5){
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    map3[34][87] = '.';
                    map3[34][100] = 'Q';
                }
            }
            else if(map3[new_y][new_x]=='&' && get_room_id(new_x,new_y)==2){
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    map3[15][72] = '.';
                    map3[13][70] = 'Q';
                }
            }
            else if(map1[new_y][new_x]=='3'){
                start_war();
                clear();
            }
            else if((map3[new_y][new_x]=='%'||map3[new_y][new_x]=='X'||map3[new_y][new_x]=='V')&&night==0)
            {
                if(message(5,40)=='\n'){
                    food_manager(map3[new_y][new_x]);
                    if(full_food==0){
                        map3[new_y][new_x]='.';
                    }
                }
            }

            else if((map3[new_y][new_x]=='T'||map3[new_y][new_x]=='Z')&&night==0)
            {
                gold_manager(map3[new_y][new_x]);
                map3[new_y][new_x]='.';
            }
            else if(map3[new_y][new_x]=='3'){
                p_user.health-=10;
            }
            else if((map3[new_y][new_x]=='H'||map3[new_y][new_x]=='R'||map3[new_y][new_x]=='8')&&night==0){
                if(message(5,40)=='\n'){
                    spell_manager(map3[new_y][new_x]);
                    if(full_spell==0){
                        map3[new_y][new_x]='.';
                    } 
                }
            }
            else if((map3[new_y][new_x]=='L'||map3[new_y][new_x]=='*'||map3[new_y][new_x]=='J'||map3[new_y][new_x]=='/')&&night==0)
            {
                if(message(5,40)=='\n'){ 
                    weapon_manager(map3[new_y][new_x]);
                    map3[new_y][new_x]='.';
                }
            }
            refresh_map(player,memory_map3,map3);  
        }
        else if(map3[new_y][new_x]=='<'){
            p_user.score+=40;
            start_level4();
        }
    }
    else if(p_user.level_num==4){
        int ch = getch();
        if(ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='6'||ch=='7'||ch=='8'||ch=='9'){
            enemy_checker2(player);
            if(Gspell==1&&Gspellc<=10){
                Gspellc++;
            }
            else if(Gspellc>10){
                Gspell=0;
            }
            if(Hspell==1&&Hspellc<=10){
                Hspellc++;
            }
            else if(Hspellc>10){
                Hspell=0;
            }
            pace_counter1++;
            if(p_user.difficulty==0){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=5;
                }
                else{
                    p_user.hunger-=1;
                }
            }
            if(p_user.difficulty==1){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=10;
                }
                else{
                    p_user.hunger-=2;
                }
            }
            if(p_user.difficulty==2){
                if(p_user.hunger<=0){
                    p_user.hunger=0;
                    p_user.health-=20;
                }
                else{
                    p_user.hunger-=3;
                }
            }
            
        }
        int new_x = player->x, new_y = player->y;
        if (ch == 's' && pace_counter2<5) {
        pace=2;
        pace_counter1=0;
        pace_counter2++;

        }
        if(pace_counter1>=5){
            pace = 1;
        }
        switch (ch) {
        case '1': new_x -= pace; new_y += pace; break;
        case '2': new_y += pace; break;
        case '3': new_x += pace; new_y += pace; break;
        case '4': new_x -= pace; break;
        case '6': new_x += pace; break;
        case '7': new_x -= pace; new_y -= pace; break;
        case '8': new_y -= pace; break;
        case '9': new_x += pace; new_y -= pace; break;
        case 'e':
            food_table();
            refresh_map(player,memory_map4,map4);
            break;
        case 'q':
            if(is_logged_in==1){
                save_info();
                save_map(map4);
                main_menu();
            }
            else{
                main_menu();
            }
        case 'm':
            show_count++;
            if(show_count>=4){
                break;
            }
            show_full_map_temporarily(player);
            break;
            case 'p': spell_table();
                refresh_map(player,memory_map4,map4);
                break;
            case 'i':weapon_table();
                refresh_map(player,memory_map4,map4);
                break;
            case ' ':
                damage_enemy(p_user.level_num,get_room_id(player->x,player->y),p_user.current_weapon,player);
                break;
            case 127:
                save_map(map4);
            break;
        }

        if (is_valid_move(new_x, new_y,map4)) {
            clear_player(player);

            player->prev_char = map4[new_y][new_x];  
            player->x = new_x;
            player->y = new_y;
            if (new_x == 109 && new_y == 34) {
                map4[34][110]='+';
            }
            else if (new_x == 121 && new_y == 7) {
                map4[7][120]='+';
            }
            else if (new_x == 46 && new_y == 37) {
                map4[37][45]='+';
            }
            else if(map4[new_y][new_x]=='&' && get_room_id(new_x,new_y)==6){
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    map4[16][52] = '.';
                    map4[17][60] = 'Q';
                }
            }
            else if(map1[new_y][new_x]=='3'){
                start_war();
                clear();
            }
            else if(map4[new_y][new_x]=='&' && get_room_id(new_x,new_y)==4){
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    map4[40][174] = '.';
                    map4[30][167] = 'Q';
                }
            }
            else if(map4[new_y][new_x]=='&' && get_room_id(new_x,new_y)==2){
                char *code = generate_code();
                show_code(code);
                char *entered_code = enter_code();
                if (check_code(entered_code, code)) {
                    map4[6][37] = '.';
                    map4[12][35] = 'Q';
                }
            }
            else if((map4[new_y][new_x]=='%'||map4[new_y][new_x]=='X'||map4[new_y][new_x]=='V')&&night==0)
            {
                if(message(5,40)=='\n'){
                    food_manager(map4[new_y][new_x]);
                    if(full_food==0){
                        map4[new_y][new_x]='.';
                    } 
                }           
            }
            else if((map4[new_y][new_x]=='T'||map4[new_y][new_x]=='Z')&&night==0)
            {
                gold_manager(map4[new_y][new_x]);
                map4[new_y][new_x]='.';
            }
            else if(map4[new_y][new_x]=='3'){
                p_user.health-=10;
            }
            else if((map4[new_y][new_x]=='H'||map4[new_y][new_x]=='R'||map4[new_y][new_x]=='8')&&night==0){
                if(message(5,40)=='\n'){
                    spell_manager(map4[new_y][new_x]);
                    if(full_spell==0){
                        map4[new_y][new_x]='.';
                    } 
                }
            }
            else if((map4[new_y][new_x]=='L'||map4[new_y][new_x]=='*'||map4[new_y][new_x]=='J'||map4[new_y][new_x]=='/')&&night==0)
            {
                if(message(5,40)=='\n'){ 
                    weapon_manager(map4[new_y][new_x]);
                    map4[new_y][new_x]='.';
                }
            }
            else if(map4[new_y][new_x]=='A')
            {
                p_user.score+=100;
                start_battle();
            }
            refresh_map(player,memory_map4,map4);  
        }
    }
}
void draw_visible_map(int player_x, int player_y,int memory_map[MAP_HEIGHT][MAP_WIDTH],char map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (memory_map[i][j]){
                if (map[i][j] == '@') {
                        attron(COLOR_PAIR(2));
                        mvaddch(i, j, '@');
                        attroff(COLOR_PAIR(2));
                        attroff(COLOR_PAIR(2));
                    }
                else if(map[i][j] == 'Q'){
                        attron(COLOR_PAIR(3));
                        mvaddch(i, j,map[i][j]);
                        attroff(COLOR_PAIR(3));
                    }
                else if(map[i][j] == '|' || map[i][j] == '-'){
                    attron(COLOR_PAIR(7));
                    mvaddch(i, j,map[i][j]);
                    attroff(COLOR_PAIR(7));
                }
                else if(map[i][j] == 'T'||map[i][j] == 'Z'){
                    attron(COLOR_PAIR(8));
                    mvaddch(i, j,map[i][j]);
                    attroff(COLOR_PAIR(8));
                }
                else if(map[i][j] == 'H'||map[i][j] == 'R'||map[i][j] == '8'){
                    attron(COLOR_PAIR(6));
                    mvaddch(i, j,map[i][j]);
                    attroff(COLOR_PAIR(6));
                }
                else if(map[i][j] == '%'||map[i][j] == 'X'||map[i][j]=='V'){
                    attron(COLOR_PAIR(9));
                    mvaddch(i, j,map[i][j]);
                    attroff(COLOR_PAIR(9));
                }
                else if(map[i][j] == '/'||map[i][j] == 'L'||map[i][j] == 'J'||map[i][j] == '*'||map[i][j]=='A'){
                    attron(COLOR_PAIR(10));
                    mvaddch(i, j,map[i][j]);
                    attroff(COLOR_PAIR(10));
                }
                else if(map[i][j] == 'G'||map[i][j] == 'F'||map[i][j] == 'S'||map[i][j] == 'D'||map[i][j] == 'U'){
                    attron(COLOR_PAIR(2));
                    mvaddch(i, j,map[i][j]);
                    attroff(COLOR_PAIR(2));
                }
                else if(map[i][j]=='&'){
                    attron(COLOR_PAIR(1));
                    mvaddch(i, j,map[i][j]);
                    attroff(COLOR_PAIR(1));
                }
                else if(map[i][j]=='3'){
                    mvaddch(i,j,'.');
                }
                else if(map[i][j]=='^'){
                    attron(COLOR_PAIR(3));
                    mvaddch(i,j,map[i][j]);
                    attroff(COLOR_PAIR(3));
                }
                else if(map[i][j]=='<'){
                    attron(COLOR_PAIR(5));
                    mvaddch(i,j,map[i][j]);
                    attroff(COLOR_PAIR(5));
                }
                
                else{
                    mvaddch(i, j,map[i][j]);
                }
            }
        }
    }
}
void refresh_map(Player *player,int memory_map[MAP_HEIGHT][MAP_WIDTH],char map[MAP_HEIGHT][MAP_WIDTH]) {
    int i;
    if(p_user.level_num==1){
        i=6;
    }
    if(p_user.level_num==2){
        i=10;
    }
    if(p_user.level_num==3){
        i=3;
    }
    if(p_user.level_num==4){
        i=2;
    }

    int rows,cols;
    getmaxyx(stdscr, rows, cols);
        attron(COLOR_PAIR(i));
        for (int i = 0; i < rows ; i++) {
            mvprintw(i, 0, "|");
            mvprintw(i, cols -1, "|");
        }
        for (int j = 0; j < cols; j++) {
            mvprintw(0, j, "=");
            mvprintw(rows - 1, j, "=");
        }
        mvprintw(0, 0, "+");
        mvprintw(0, cols - 1, "+");
        mvprintw(rows - 1, 0, "+");
        mvprintw(rows - 1, cols - 1, "+");
    attroff(COLOR_PAIR(i));
    update_memory_map(player->x, player->y,memory_map);
    draw_visible_map(player->x, player->y,memory_map,map);
    draw_player(player);
    mvprintw(LINES-2,2,"                              ");
    mvprintw(LINES-2,20,"                              ");
    mvprintw(LINES-3,62,"                                         ");
    mvprintw(LINES-2, 68, "                                                  ");
    mvprintw(LINES-3, 68, "                                                  ");
    draw_bar(LINES-2, 68, 20, p_user.health, 10000, "Health");
    draw_bar(LINES-3, 68, 20, p_user.hunger, 100, "Power");
    attron(COLOR_PAIR(1));
    mvprintw(LINES-2,14,"Score : %d",p_user.score);
    mvprintw(LINES-2,2,"Gold : %d",p_user.gold);
    mvprintw(LINES-2,26,"Kills : %d",p_user.kills1);
    attroff(COLOR_PAIR(1));
    mvprintw(LINES-6,2,"                              ");
    //attron(COLOR_PAIR(7));
    
    //attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(10));
    
    switch(p_user.current_weapon){
        case 'm':
            mvprintw(LINES-6,2,"current weapon : MACE");
        break;
        case 'd':
            mvprintw(LINES-6,2,"current weapon : DAGGER %d",p_user.weapon_bar.dagger);
        break;
        case 'w':
            mvprintw(LINES-6,2,"current weapon : MAGIC WAND %d",p_user.weapon_bar.magic_wand);
        break;
        case 'a':
            mvprintw(LINES-6,2,"current weapon : ARROWS %d",p_user.weapon_bar.arrow);
        break;
        case 's':
            mvprintw(LINES-6,2,"current weapon : SWORD");
        break;
    }
    attroff(COLOR_PAIR(10));
    attron(COLOR_PAIR(6));
        mvprintw(LINES-5,2,"Health spell : %d",p_user.spell_bar.H);
        mvprintw(LINES-4,2,"Speed  spell : %d",p_user.spell_bar.S);
        mvprintw(LINES-3,2,"Power  spell : %d",p_user.spell_bar.G);
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(9));
        mvprintw(LINES-5,20,"Normal food : %d",p_user.food_bar.normal);
        mvprintw(LINES-4,20,"Speedy food : %d",p_user.food_bar.speed);
        mvprintw(LINES-3,20,"Supreme food : %d",p_user.food_bar.special);
    attroff(COLOR_PAIR(9));
    refresh();  
}
void update_memory_map(int player_x, int player_y,int memory_map[MAP_HEIGHT][MAP_WIDTH]) {
    if(p_user.level_num==1){
        if(is_in_room(player_x,player_y)){
            if (get_room_id(player_x,player_y)==1) {
                for (int i = 3; i <= 9; i++) {
                    for (int j = 3; j <= 23; j++) {
                        memory_map[i][j] = 1;  
                    }
                }
            }
            
            else if (get_room_id(player_x,player_y)==2) {
                for (int i = 7; i <= 20; i++) {
                    for (int j = 50 ; j <= 65 ; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }
            
            else if (get_room_id(player_x,player_y)==3) {
                for (int i = 6; i <= 16; i++) {
                    for (int j = 100; j <= 111; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }
            
            else if (get_room_id(player_x,player_y)==4) {
                for (int i = 20; i <= 29; i++) {
                    for (int j = 150; j <= 159; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }
            
            else if (get_room_id(player_x,player_y)==5) {
                for (int i = 30; i <= 35; i++) {
                    for (int j = 94; j <= 110; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }
            
            else if (get_room_id(player_x,player_y)==6) {
                for (int i = 28; i <= 37; i++) {
                    for (int j = 10; j <= 20; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }
        }
        else{
            int view_distance = 3;  

            for (int y = player_y - view_distance; y <= player_y + view_distance; y++) {
                for (int x = player_x - view_distance; x <= player_x + view_distance; x++) {
                    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
                        memory_map[y][x] = 1;  
                    }
                }
            }
        }
    }
    else if (p_user.level_num == 2) {
        if (is_in_room(player_x, player_y)) {
            if (get_room_id(player_x, player_y) == 1) {
                for (int i = 6; i <= 14; i++) {
                    for (int j = 10; j <= 18; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 2) {
                for (int i = 5; i <= 13; i++) {
                    for (int j = 35; j <= 48; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 3) {
                for (int i = 3; i <= 12; i++) {
                    for (int j = 120; j <= 135; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 4) {
                for (int i = 30; i <= 41; i++) {
                    for (int j = 160; j <= 175; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 5) {
                for (int i = 30; i <= 35; i++) {
                    for (int j = 94; j <= 110; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 6) {
                for (int i = 15; i <= 22; i++) {
                    for (int j = 50; j <= 60; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 7) {
                for (int i = 28; i <= 32; i++) {
                    for (int j = 11; j <= 26; j++) {
                        memory_map[i][j] = 1;
                    }
                }
            }
        }
        else{
            int view_distance = 3;  

            for (int y = player_y - view_distance; y <= player_y + view_distance; y++) {
                for (int x = player_x - view_distance; x <= player_x + view_distance; x++) {
                    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
                        memory_map[y][x] = 1;  
                    }
                }
            }
        }
    }
    else if (p_user.level_num == 3) {
        if (is_in_room(player_x, player_y)) {
            if (get_room_id(player_x, player_y) == 1) {
                for (int i = 6; i <= 15; i++) {  
                    for (int j = 35; j <= 41; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 2) {
                for (int i = 12; i <= 16; i++) {  
                    for (int j = 70; j <= 84; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 3) {
                for (int i = 5; i <= 20; i++) {  
                    for (int j = 125; j <= 145; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 4) {
                for (int i = 30; i <= 41; i++) {  
                    for (int j = 160; j <= 175; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 5) {
                for (int i = 30; i <= 35; i++) {  
                    for (int j = 84; j <= 100; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 6) {
                for (int i = 21; i <= 35; i++) {  
                    for (int j = 12; j <= 26; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }
        }
        else{
            int view_distance = 3;  

            for (int y = player_y - view_distance; y <= player_y + view_distance; y++) {
                for (int x = player_x - view_distance; x <= player_x + view_distance; x++) {
                    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
                        memory_map[y][x] = 1;  
                    }
                }
            }
        }
    }
    else if (p_user.level_num == 4) {
        if (is_in_room(player_x, player_y)) {
            if (get_room_id(player_x, player_y) == 1) {
                for (int i = 6; i <= 14; i++) {  
                    for (int j = 10; j <= 18; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 2) {
                for (int i = 5; i <= 13; i++) {  
                    for (int j = 35; j <= 48; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 3) {
                for (int i = 3; i <= 12; i++) {  
                    for (int j = 120; j <= 135; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 4) {
                for (int i = 30; i <= 41; i++) {  
                    for (int j = 160; j <= 175; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 5) {
                for (int i = 30; i <= 35; i++) {  
                    for (int j = 94; j <= 110; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 6) {
                for (int i = 15; i <= 22; i++) {  
                    for (int j = 50; j <= 60; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 7) {
                for (int i = 28; i <= 32; i++) {  
                    for (int j = 11; j <= 26; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }

            else if (get_room_id(player_x, player_y) == 8) {
                for (int i = 30; i <= 41; i++) {  
                    for (int j = 45; j <= 60; j++) {  
                        memory_map[i][j] = 1;
                    }
                }
            }
        }
        else{
            int view_distance = 3;  

            for (int y = player_y - view_distance; y <= player_y + view_distance; y++) {
                for (int x = player_x - view_distance; x <= player_x + view_distance; x++) {
                    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
                        memory_map[y][x] = 1;  
                    }
                }
            }
        }
    }
    
}
int is_in_room(int x, int y) {
    if(p_user.level_num==1){
        if ((x >= 3 && x <= 23 && y >= 3 && y <= 9) ||  
        (x >= 50 && x <= 65 && y >= 7 && y <= 20) ||  
        (x >= 100 && x <= 111 && y >= 6 && y <= 16) ||  
        (x >= 150 && x <= 159 && y >= 20 && y <= 29) ||  
        (x >= 94 && x <= 110 && y >= 30 && y <= 35) ||  
        (x >= 10 && x <= 20 && y >= 28 && y <= 37)) {
        return 1;
        }
    return 0;
    }
    else if(p_user.level_num==2){
        if ((y >= 6 && y <= 14 && x >= 10 && x <= 18) ||   
        (y >= 5 && y <= 13 && x >= 35 && x <= 48) ||   
        (y >= 3 && y <= 12 && x >= 120 && x <= 135) ||   
        (y >= 30 && y <= 41 && x >= 160 && x <= 175) ||   
        (y >= 30 && y <= 35 && x >= 94 && x <= 110) ||   
        (y >= 15 && y <= 22 && x >= 50 && x <= 60) ||   
        (y >= 28 && y <= 32 && x >= 11 && x <= 26)) {   
        return 1;
    }
    return 0;
    }
    else if(p_user.level_num==3){
        if ((x >= 35 && x <= 41 && y >= 6 && y <= 15) ||   
        (x >= 70 && x <= 84 && y >= 12 && y <= 16) ||   
        (x >= 125 && x <= 145 && y >= 5 && y <= 19) ||   
        (x >= 160 && x <= 175 && y >= 30 && y <= 41) ||   
        (x >= 84 && x <= 100 && y >= 30 && y <= 35) ||   
        (x >= 12 && x <= 25 && y >= 21 && y <= 35)) {   
        return 1;
        }
    return 0;
    }
    else if(p_user.level_num==4){
        if ((x >= 10 && x <= 18 && y >= 6 && y <= 14) ||   
        (x >= 35 && x <= 48 && y >= 5 && y <= 13) ||   
        (x >= 120 && x <= 135 && y >= 3 && y <= 12) ||   
        (x >= 160 && x <= 175 && y >= 30 && y <= 41) ||   
        (x >= 94 && x <= 110 && y >= 30 && y <= 35) ||   
        (x >= 50 && x <= 60 && y >= 15 && y <= 22) ||   
        (x >= 11 && x <= 26 && y >= 28 && y <= 32) ||   
        (x >= 45 && x <= 60 && y >= 30 && y <= 41)) {   
        return 1;
        }
    return 0;
    }
    
}
int get_room_id(int x, int y) {
    if(p_user.level_num==1){
        if (x >= 4 && x <= 23 && y >= 4 && y <= 10) return 1;
        if (x >= 51 && x <= 65 && y >= 7 && y <= 20) return 2;
        if (x >= 101 && x <= 111 && y >= 7 && y <= 16) return 3;
        if (x >= 151 && x <= 159 && y >= 21 && y <= 29) return 4;
        if (x >= 95 && x <= 110 && y >= 31 && y <= 35) return 5;
        if (x >= 11 && x <= 20 && y >= 29 && y <= 37) return 6;
        return 0;
    }
    else if(p_user.level_num==2){
        if (y >= 6 && y <= 14 && x >= 10 && x <= 18) return 1;   
        if (y >= 5 && y <= 13 && x >= 35 && x <= 48) return 2;   
        if (y >= 3 && y <= 12 && x >= 120 && x <= 135) return 3;   
        if (y >= 30 && y <= 41 && x >= 160 && x <= 175) return 4;   
        if (y >= 30 && y <= 35 && x >= 94 && x <= 110) return 5;   
        if (y >= 15 && y <= 22 && x >= 50 && x <= 60) return 6;   
        if (y >= 28 && y <= 32 && x >= 11 && x <= 26) return 7;    
        return 0;
    }
    else if(p_user.level_num==3){
        if (x >= 35 && x <= 41 && y >= 6 && y <= 15) return 1;  
        if (x >= 70 && x <= 84 && y >= 12 && y <= 16) return 2;  
        if (x >= 125 && x <= 145 && y >= 6 && y <= 20) return 3;  
        if (x >= 160 && x <= 175 && y >= 30 && y <= 41) return 4;  
        if (x >= 84 && x <= 100 && y >= 30 && y <= 35) return 5;  
        if (x >= 12 && x <= 26 && y >= 21 && y <= 35) {
            return 6;
            }  
        return 0;
    }
    else if(p_user.level_num==4){
        if (x >= 10 && x <= 18 && y >= 6 && y <= 14) return 1;  
        if (x >= 35 && x <= 48 && y >= 5 && y <= 13) return 2;  
        if (x >= 120 && x <= 135 && y >= 3 && y <= 12) return 3;  
        if (x >= 160 && x <= 175 && y >= 30 && y <= 41) return 4;  
        if (x >= 94 && x <= 110 && y >= 30 && y <= 35) return 5;  
        if (x >= 50 && x <= 60 && y >= 15 && y <= 22) return 6;  
        if (x >= 11 && x <= 26 && y >= 28 && y <= 32) return 7;  
        if (x >= 45 && x <= 60 && y >= 30 && y <= 41)return 8; 
        return 0;
    }
}
void show_full_map_temporarily(Player *player) {
    if(p_user.level_num==1){
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                mvaddch(i, j, map1[i][j]);
            }
        }
        refresh();
        timeout(4000);
        int ch = getch();
        if(ch=='m'){
            clear();
            refresh_map(player,memory_map1,map1);
        }
        else {
            clear();
            refresh_map(player,memory_map1,map1);
        }
        timeout(-1);
    }
    else if(p_user.level_num==2){
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                mvaddch(i, j, map2[i][j]);
            }
        }
        refresh();
        timeout(4000);
        int ch = getch();
        if(ch=='m'){
            clear();
            refresh_map(player,memory_map2,map2);
        }
        else {
            clear();
            refresh_map(player,memory_map2,map2);
        }
        timeout(-1);
    }
    else if(p_user.level_num==3){
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                mvaddch(i, j, map3[i][j]);
            }
        }
        refresh();
        timeout(4000);
        int ch = getch();
        if(ch=='m'){
            clear();
            refresh_map(player,memory_map3,map3);
        }
        else {
            clear();
            refresh_map(player,memory_map3,map3); 
        }
        timeout(-1);
    }
    else if(p_user.level_num==4){
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                mvaddch(i, j, map4[i][j]);
            }
        }
        refresh();
        timeout(4000);
        int ch = getch();
        if(ch=='m'){
            clear();
            refresh_map(player,memory_map4,map4);
        }
        else {
            clear();
            refresh_map(player,memory_map4,map4);
        }
        timeout(-1);
    }
}
char *generate_code() {
    static char code[5];
    const char digits[] = "0123456789";
    for (int i = 0; i < 4; i++) {
        code[i] = digits[rand() % 10];
    }
    code[4] = '\0';
    return code;
}
void show_code(const char *code) {
    attron(COLOR_PAIR(2));
    mvprintw(LINES/2-2,COLS/2-22,"==============================");
    mvprintw(LINES/2+2,COLS/2-22,"==============================");
    for(int i = LINES/2-2 ; i <= LINES/2+2 ;i++){
        mvprintw(i,COLS/2-23,"||");
        mvprintw(i,COLS/2+8,"||");
    }
    attroff(COLOR_PAIR(2));
    mvprintw(LINES/2-1, COLS/2-16, "CODE IS: %s", code);
}
char *enter_code() {
    static char input[5];
    echo();
    curs_set(1);
    mvprintw(LINES/2,COLS/2-16, "ENTER PASS:");
    getstr(input);
    noecho();
    curs_set(0);
    return input;
}
int check_code(const char *entered_code, const char *correct_code) {
    char real_code[5];
    for(int i =3 ; i>=0 ;i--){
        real_code[3-i]=entered_code[i];
    }
    if (strcmp(real_code, correct_code) == 0) {
        mvprintw(LINES/2+1, COLS/2-16, "DOOR OPENED!");
        getch();
        move(LINES/2-2,COLS/2-23);
        clrtoeol();
        move(LINES/2-1,COLS/2-23);
        clrtoeol();
        move(LINES/2,COLS/2-23);
        clrtoeol();
        move(LINES/2+1,COLS/2-23);
        clrtoeol();
        move(LINES/2+2,COLS/2-23);
        clrtoeol();
        return 1;
    } else {
        mvprintw(LINES/2+1, COLS/2-16, "WRONG PASS HAHA!");
        getch();
        getch();
        move(LINES/2-2,COLS/2-23);
        clrtoeol();
        move(LINES/2-1,COLS/2-23);
        clrtoeol();
        move(LINES/2,COLS/2-23);
        clrtoeol();
        move(LINES/2+1,COLS/2-23);
        clrtoeol();
        move(LINES/2+2,COLS/2-23);
        clrtoeol();
        return 0;
    }
}
void draw_bar(int y, int x, int width, int value, int max_value, const char* label) {
    if(strcmp(label,"Power")==0){
        mvprintw(y, x, "%s: ", label);

        int bar_length = (value * width) / max_value;

        attron(COLOR_PAIR(10) | A_REVERSE); 
        for (int i = 0; i < bar_length; i++) {
            mvaddch(y, x + strlen(label) + 3 + i, ' '); 
        }
        attroff(COLOR_PAIR(10) | A_REVERSE);

        for (int i = bar_length; i < width; i++) {
            mvaddch(y, x + strlen(label) + 3 + i, ' '); 
        }
        mvprintw(y, x + strlen(label) + 3 + width + 1, "  %d/%d", value, max_value);
    }
    else{
        mvprintw(y, x, "%s: ", label);

        int bar_length = (value * width) / max_value;

        attron(COLOR_PAIR(3) | A_REVERSE); 
        for (int i = 0; i < bar_length; i++) {
            mvaddch(y, x + strlen(label) + 2 + i, ' '); 
        }
        attroff(COLOR_PAIR(3) | A_REVERSE);

        attron(COLOR_PAIR(2) | A_REVERSE);
        for (int i = bar_length; i < width; i++) {
            mvaddch(y, x + strlen(label) + 2 + i, ' '); 
        }
        attroff(COLOR_PAIR(2) | A_REVERSE);
        mvprintw(y, x + strlen(label) + 2 + width + 1, " %d/%d", value, max_value);
        }
}
int food_manager(char food){
    if(food=='%'){
        if(p_user.food_bar.normal+p_user.food_bar.special+p_user.food_bar.speed>=5){
            full_food=1;
            attron(COLOR_PAIR(2));
            mvprintw(2,2,"not enough space to restore food!");
            attroff(COLOR_PAIR(2));
            getch();
            mvprintw(2,2,"                                 ");
            
        }
        else{
            full_food=0;
            p_user.food_bar.normal += 1;
        }
        
    }
    else if(food=='X'){
        if(p_user.food_bar.normal+p_user.food_bar.special+p_user.food_bar.speed>=5){
            full_food=1;
            attron(COLOR_PAIR(2));
            mvprintw(0,0,"not enough space to restore food!");
            attroff(COLOR_PAIR(2));
            getch();
            mvprintw(0,0,"                                 ");
            
        }
        else{
            full_food=0;
            p_user.food_bar.special += 1;
        }
        
    }
    else if(food=='V'){
        if(p_user.food_bar.normal+p_user.food_bar.special+p_user.food_bar.speed>=5){
            full_food=1;
            attron(COLOR_PAIR(2));
            mvprintw(0,0,"not enough space to restore food!");
            attroff(COLOR_PAIR(2));
            getch();
            mvprintw(0,0,"                                 ");
            
        }
        else{
            full_food=0;
            p_user.food_bar.speed += 1;
        }
        
    }
}
void food_table(){
    clear();

    int height = 10;
    int width = 62;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;

      
    for (int i = start_x; i < start_x + width; i++) {
        mvaddch(start_y, i, ACS_HLINE);   
        mvaddch(start_y + height - 1, i, ACS_HLINE);   
    }
    for (int i = start_y; i < start_y + height; i++) {
        mvaddch(i, start_x, ACS_VLINE);   
        mvaddch(i, start_x + width - 1, ACS_VLINE);   
    }
    mvaddch(start_y, start_x, ACS_ULCORNER);   
    mvaddch(start_y, start_x + width - 1, ACS_URCORNER);   
    mvaddch(start_y + height - 1, start_x, ACS_LLCORNER);   
    mvaddch(start_y + height - 1, start_x + width - 1, ACS_LRCORNER);   

      
    mvprintw(start_y + 2, start_x + 2, "      Speedy  food : %d (press (R) to consume speedy)", p_user.food_bar.speed);
    mvprintw(start_y + 3, start_x + 2, "      Normal  food : %d (press (N) to consume normal food)", p_user.food_bar.normal);
    mvprintw(start_y + 4, start_x + 2, "      Supreme food : %d (press (S) to consume Supreme)", p_user.food_bar.special);
    mvprintw(start_y + 6, start_x + 2, "                  Press any key to quit");

      
    int ch = getch();
    int x = rand() % 5;
    int add1 = 10;
    int add2 = 50;
    if (Hspell == 1 && Hspellc < 10) {
        add1 = 20;
        add2 = 100;
    }

    switch (ch) {
        case 'n':
            if (x) {
                if (p_user.food_bar.normal > 0) {
                    if (p_user.hunger >= 9990 && Hspell == 0 || p_user.hunger >= 9980 && Hspell == 1) {
                        mvprintw(start_y + 8, start_x + 2, "FULL!");
                        getch();
                        clear();
                    } else {
                        p_user.food_bar.normal--;
                        if(p_user.food_bar.normal<=0){
                            p_user.food_bar.normal=0;
                        }
                        p_user.hunger += add1;
                        mvprintw(start_y + 8, start_x + 2, "Yummy!");
                        getch();
                        clear();
                    }
                } else {
                    mvprintw(start_y + 8, start_x + 2, "You have no more normal food");
                    getch();
                    clear();
                }
                break;
            } else {
                p_user.food_bar.normal--;
                if(p_user.food_bar.normal<=0){
                    p_user.food_bar.normal=0;
                }
                p_user.health -= 10;
                mvprintw(start_y + 8, start_x + 2, "HE HE HE HE :o");
                getch();
                clear();
            }
            break;

        case 's':
            if (p_user.food_bar.special > 0) {
                if (p_user.hunger >= 9950 && Hspell == 0 || p_user.hunger >= 9900 && Hspell == 1) {
                    mvprintw(start_y + 8, start_x + 2, "FULL!");
                    getch();
                    clear();
                } else {
                    p_user.food_bar.special--;
                    p_user.hunger += add2;
                    Gspell = 1;
                    Gspellc = 0;
                    mvprintw(start_y + 8, start_x + 2, "Delicous!");
                    getch();
                    clear();
                }
            } else {
                mvprintw(start_y + 8, start_x + 2, "You have no more special food");
                getch();
                clear();
            }
            break;

        case 'r':
            if (p_user.food_bar.speed > 0) {
                if (p_user.hunger >= 9950 && Hspell == 0 || p_user.hunger >= 9900 && Hspell == 1) {
                    mvprintw(start_y + 8, start_x + 2, "FULL!");
                    getch();
                    clear();
                } else {
                    p_user.food_bar.speed--;
                    p_user.hunger += add1;
                    pace =2;
                    pace_counter2=0;
                    pace_counter1 = 0;
                    mvprintw(start_y + 8, start_x + 2, "Run faster!");
                    getch();
                    clear();
                }
            } else {
                mvprintw(start_y + 8, start_x + 2, "You have no more speedy food");
                getch();
                clear();
            }
            break;

        default:
            clear();
            break;
    }
    if(p_user.hunger>=100){
        p_user.hunger=100;
        p_user.health=10000;
    }
}
int gold_manager(char gold){
    if(gold=='T'){
        p_user.gold+=5;
    }
    else{
        p_user.gold+=30;
    }
}
int spell_manager(char spell){
    if(p_user.spell_bar.H+p_user.spell_bar.S+p_user.spell_bar.G>=15){
        full_spell=1;
        attron(COLOR_PAIR(2));
        mvprintw(2,2,"not enough space to restore spell!");
        attroff(COLOR_PAIR(2));
        getch();
        mvprintw(2,2,"                                   ");
    }
    else{
        full_spell=0;
        if(spell=='H'){
            p_user.spell_bar.H++;
        }
        else if(spell=='R'){
            p_user.spell_bar.S++;
        }
        else if(spell=='8'){
            p_user.spell_bar.G++;
        } 
    }
}
int spell_table(){
    clear();
    int height = 8;    
    int width = 60;    
    int start_y = (LINES - height) / 2;    
    int start_x = (COLS - width) / 2;    

    
    for (int i = start_x; i < start_x + width; i++) {
        mvaddch(start_y, i, ACS_HLINE);    
        mvaddch(start_y + height - 1, i, ACS_HLINE);    
    }
    for (int i = start_y; i < start_y + height; i++) {
        mvaddch(i, start_x, ACS_VLINE);    
        mvaddch(i, start_x + width - 1, ACS_VLINE);    
    }
    mvaddch(start_y, start_x, ACS_ULCORNER);    
    mvaddch(start_y, start_x + width - 1, ACS_URCORNER);    
    mvaddch(start_y + height - 1, start_x, ACS_LLCORNER);    
    mvaddch(start_y + height - 1, start_x + width - 1, ACS_LRCORNER);    
    mvprintw(start_y + 2, start_x + 2, "Health spell : %d (press (H) to consume Health spell)", p_user.spell_bar.H);
    mvprintw(start_y + 3, start_x + 2, "Speed  spell : %d (press (R) to consume Speed  spell)", p_user.spell_bar.S);
    mvprintw(start_y + 4, start_x + 2, "Power  spell : %d (press (P) to consume Power  spell)", p_user.spell_bar.G);
    mvprintw(start_y + 6, start_x + 2, "            Press any other key to quit");
    int ch = getch();

    switch (ch) {
        case 'h':
            if (p_user.spell_bar.H <= 0) {
                mvprintw(start_y + 8, start_x + 2, "Not enough spell!");
                getch();
                clear();
                break;
            } else {
                mvprintw(start_y + 8, start_x + 2, "Healthy!");
                p_user.spell_bar.H--;
                Hspell = 1;
                Hspellc = 0;
                getch();
                clear();
                break;
            }

        case 'r':
            if (p_user.spell_bar.S <= 0) {
                mvprintw(start_y + 8, start_x + 2, "Not enough spell!");
                getch();
                clear();
                break;
            } else {
                mvprintw(start_y + 8, start_x + 2, "Speedy!");
                p_user.spell_bar.S--;
                // Sspell = 1;
                // Sspellc = 0;
                pace=2;
                pace_counter1=0;
                pace_counter2=0;
                getch();
                clear();
                break;
            }

        case 'p':
            if (p_user.spell_bar.G <= 0) {
                mvprintw(start_y + 8, start_x + 2, "Not enough spell!");
                getch();
                clear();
                break;
            } else {
                mvprintw(start_y + 8, start_x + 2, "Powerful!");
                p_user.spell_bar.G--;
                Gspell = 1;
                Gspellc = 0;
                getch();
                clear();
                break;
            }
        default:
            clear();
            break;
    }
}
char message(int height, int width){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int startY = (yMax - height) / 2;
    int startX = (xMax - width) / 2;
    if(height==5){
        for (int i = 0; i < width; i++) {
        mvaddch(startY, startX + i, '-');
        mvaddch(startY + height - 1, startX + i, '-');
        }
        for (int i = 0; i < height; i++) {
            mvaddch(startY + i, startX, '|');
            mvaddch(startY + i, startX + width - 1, '|');
        }
        mvaddch(startY, startX, '+');
        mvaddch(startY, startX + width - 1, '+');
        mvaddch(startY + height - 1, startX, '+');
        mvaddch(startY + height - 1, startX + width - 1, '+');
        attron(COLOR_PAIR(4));
        mvprintw(startY, startX + (width - 10) / 2, "CHOOSE :)");
        mvprintw(startY + height / 2 - 1, startX + 2, "                   ");
        mvprintw(startY + height / 2, startX + (width - 18) / 2-5, "   press ENTER to pick");
        mvprintw(startY + height / 2 + 1, startX + 2, "                   ");
        attroff(COLOR_PAIR(4));
        int c = getch();
        if(c=='\n'){
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    mvaddch(startY + i, startX + j, ' ');
                }
            }
            return '\n';
        }
        else{
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    mvaddch(startY + i, startX + j, ' ');
                }
            }
            return 'a';
        }
    }
    else{
        attron(COLOR_PAIR(2));
        for (int i = 0; i < width; i++) {
        mvaddch(startY, startX + i, '-');
        mvaddch(startY + height - 1, startX + i, '-');
        }
        for (int i = 0; i < height; i++) {
            mvaddch(startY + i, startX, '|');
            mvaddch(startY + i, startX + width - 1, '|');
        }
        mvaddch(startY, startX, '+');
        mvaddch(startY, startX + width - 1, '+');
        mvaddch(startY + height - 1, startX, '+');
        mvaddch(startY + height - 1, startX + width - 1, '+');
        mvprintw(startY + height / 2, startX + (width - 18) / 2 + 3, "DAMAGE!!!");
        attroff(COLOR_PAIR(2));
        int c = getch();
        if(c=='\n'){
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    mvaddch(startY + i, startX + j, ' ');
                }
            }
            return '\n';
        }
        else{
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    mvaddch(startY + i, startX + j, ' ');
                }
            }
            return 'a';
        }
    }
    
}
int is_valid_enemy(int y , int x,char map[MAP_HEIGHT][MAP_WIDTH]){
    if((map[y][x]=='.'||map[y][x]=='%'||map[y][x]=='T'||map[y][x]=='Z'||map[y][x]=='X'||
       map[y][x]=='H'||map[y][x]=='R'||map[y][x]=='8')&&map[y][x]!='@'&&
       map[y][x]!='o'&&map[y][x]!='<'&&map[y][x]!='&'){
        return 1;
    }
    else{
        return 0;
    }
}
void clear_enemy(Enemy enemy){
    if(gmsign2==0){
       mvprintw(enemy.y, enemy.x, "%c", '.');
       gmsign2=1;
    }
    else{
        mvprintw(enemy.y, enemy.x, "%c", enemy.perv);
    }
}
void damage_player(Enemy *enemy,Player *player){
    if (abs(player->x - enemy->x) <= enemy->damage_distance && abs(player->y - enemy->y) <= enemy->damage_distance) {
        p_user.health -= enemy->damage;
        int yMax, xMax;
        getmaxyx(stdscr, yMax, xMax);
        int startY = (yMax - 3) / 2;
        int startX = (xMax - 40) / 2;
        
        for (int i = 0; i < 40; i++) {
            mvaddch(startY, startX + i, '-');
            mvaddch(startY + 3 - 1, startX + i, '-');
        }
        for (int i = 0; i < 3; i++) {
            mvaddch(startY + i, startX, '|');
            mvaddch(startY + i, startX + 40 - 1, '|');
        }
        mvaddch(startY, startX, '+');
        mvaddch(startY, startX + 40 - 1, '+');
        mvaddch(startY + 3 - 1, startX, '+');
        mvaddch(startY + 3 - 1, startX + 40 - 1, '+');
        attron(COLOR_PAIR(2));
        mvprintw(startY, startX + (40 - 10) / 2, "DAMAGE!!!");
        mvprintw(startY + 3 / 2, startX + (40 - 18) / 2-6, "   -%d Health,Pay attention",enemy->damage);
        attroff(COLOR_PAIR(2));
        getch();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 40; j++) {
                mvaddch(startY + i, startX + j, ' ');
            }
        }
    }
}
int weapon_manager(char weapon){
    if(weapon=='/'){
        if(sign_d==1){
            p_user.weapon_bar.dagger++;
        }
        else{
            p_user.weapon_bar.dagger+=10;

        }
    }
    else if(weapon=='*'){
        if(sign_d==1){
            p_user.weapon_bar.arrow++;
        }
        else{
            p_user.weapon_bar.arrow+=20;

        }
    }
    else if(weapon=='L'){
        p_user.weapon_bar.dagger=1;;         
    }
    else if(weapon=='J'){
        if(sign_d==1){
            p_user.weapon_bar.magic_wand++;
        }
        else{
            p_user.weapon_bar.magic_wand+=8;

        }
    }
}
int weapon_table(){
    clear();
    int height = 10;
    int width = 62;
    int start_y = (LINES - height) / 2;  
    int start_x = (COLS - width) / 2;   
    for (int i = start_x; i < start_x + width; i++) {
        mvaddch(start_y, i, ACS_HLINE);         
        mvaddch(start_y + height - 1, i, ACS_HLINE);
    }
    for (int i = start_y; i < start_y + height; i++) {
        mvaddch(i, start_x, ACS_VLINE);         
        mvaddch(i, start_x + width - 1, ACS_VLINE); 
    }
    mvaddch(start_y, start_x, ACS_ULCORNER);             
    mvaddch(start_y, start_x + width - 1, ACS_URCORNER); 
    mvaddch(start_y + height - 1, start_x, ACS_LLCORNER);
    mvaddch(start_y + height - 1, start_x + width - 1, ACS_LRCORNER); 
    int center_x = start_x + width / 2;
    for (int i = start_y + 1; i < start_y + height - 1; i++) {
        mvaddch(i, center_x, ACS_VLINE);
    }
    mvprintw(start_y,start_x+9,"SHORT RANGE :");
    mvprintw(start_y+4,start_x+6,"MACE : YOU HAVE IT");
    if(p_user.weapon_bar.sword==1){
        mvprintw(start_y+5,start_x+6,"SWORD :YOU HAVE IT");
    }
    else{
        mvprintw(start_y+5,start_x+6,"SWORD :YOU DON'T HAVE IT");
    }
    mvprintw(start_y,start_x+39,"LOG RANGE :");
    mvprintw(start_y+4,start_x+35,"NUMBER OF MAGIC WANDS : %d",p_user.weapon_bar.magic_wand);
    mvprintw(start_y+5,start_x+35,"NUMBER OF ARROWS : %d",p_user.weapon_bar.arrow);
    mvprintw(start_y+6,start_x+35,"NUMBER OF DAGGERS : %d",p_user.weapon_bar.dagger);
    mvprintw(start_y+11,start_x+3,"                           MACE PRESS m");
    mvprintw(start_y+12,start_x+3,"                           SWORD PRESS s");
    mvprintw(start_y+13,start_x+3,"CHANGE CURRENT WEAPON TO : MAGIC WAND PRESS w");
    mvprintw(start_y+14,start_x+3,"                           ARROWS PRESS a");
    mvprintw(start_y+15,start_x+3,"                           DAGGERS PRESS d");
    mvprintw(start_y+17,start_x+3,"PRESS ANY KEY TO EXIT");
    int ch = getch();
    switch (ch)
    {
    case 'm':
        p_user.current_weapon='m';
        mvprintw(start_y-5,start_x+26,"MACE !");
        getch();
        break;
    case 's':
    if(p_user.weapon_bar.sword==1){
        p_user.current_weapon='s';
        mvprintw(start_y-5,start_x+26,"SWORD !");
    }
    else{
        mvprintw(start_y-5,start_x+14,"YOU DON'T HAVE ENOUGH SWORD");
    }
        getch();
        break;
    case 'w':
    if(p_user.weapon_bar.magic_wand>0){
        p_user.weapon_bar.magic_wand--;
        p_user.current_weapon='w';
        mvprintw(start_y-5,start_x+26,"MAGIC WAND !");
    }
    else{
        mvprintw(start_y-5,start_x+14,"YOU DON'T HAVE ENOUGH MAGIC WAND");
    }
        getch();
        break;
    case 'a':
        if(p_user.weapon_bar.arrow>0){
            p_user.weapon_bar.arrow--;
            p_user.current_weapon='a';
            mvprintw(start_y-5,start_x+26,"ARROWS!");
        }
        else{
            mvprintw(start_y-5,start_x+14,"YOU DON'T HAVE ENOUGH ARROWS");
        }
        getch();
        break;
    case 'd':
        if(p_user.weapon_bar.dagger>0){
            p_user.weapon_bar.dagger--;
            p_user.current_weapon='d';
            mvprintw(start_y-5,start_x+26,"DAGGER !");
        }
        else{
            mvprintw(start_y-5,start_x+14,"YOU DON'T HAVE ENOUGH DAGGER");
        }
        getch();
        break;
    default:
        break;
    }
    clear();
}
int damage_enemy(int level,int room,char weapon,Player *player){
    attron(COLOR_PAIR(3));
    mvprintw(1,COLS/2-10,"ENTER DIRECTION");
    attroff(COLOR_PAIR(3));
    int direction = getch();
    mvprintw(1,COLS/2-10,"               ");
    int aim;
    switch (direction)
    {
    case '8':
        aim=1;
        break;
    case '4':
        aim=2;
        break;
    case '2':
        aim=3;
        break;
    case '6':
        aim=4;
        break;
    default:
        break;
    }
    int damage;
    int damage_distance;
    attron(COLOR_PAIR(10));
    switch(weapon){
        case 'm':
        damage=5;
        damage_distance=1;
        break;
        case 'd':
        if(p_user.weapon_bar.dagger<=0){
            mvprintw(1,2,"NOT ENOUGH DAGGER!!!");
            getch();
            mvprintw(1,2,"                    ");
            return 1;
        }
        wandon=0;
        damage=12;
        damage_distance=5;
        p_user.weapon_bar.dagger--;
        break;
        case 'w':
        if(p_user.weapon_bar.magic_wand<=0){
            mvprintw(1,2,"NOT ENOUGH MAGIC WAND!!!");
            getch();
            mvprintw(1,2,"                       ");
            wandon=0;
            return 1;
        }
        wandon=1;
        damage=15;
        damage_distance=10;
        p_user.weapon_bar.magic_wand--;
        break;
        case 'a':
        if(p_user.weapon_bar.arrow<=0){
            mvprintw(1,2,"NOT ENOUGH ARROW!!!");
            getch();
            mvprintw(1,2,"                    ");
            return 1;
        }
        wandon=0;
        damage=5;
        damage_distance=5;
        p_user.weapon_bar.arrow--;
        break;
        case 's':
        if(p_user.weapon_bar.sword==0){
            mvprintw(1,2,"NOT ENOUGH SWORD!!!");
            getch();
            mvprintw(1,2,"                    ");
            return 1;
        }
        wandon=0;
        damage_distance=1;
        damage=10;
        break;
        attroff(COLOR_PAIR(10));
    }
    if(Gspell==1){
            damage*=2;
    }
    if(level==1){
        for(int i=0 ; i<6 ;i++){
            if(((player->x==enemies_map1[i].x&&player->y >= enemies_map1[i].y&&aim==1)||
            (player->x==enemies_map1[i].x&&player->y <= enemies_map1[i].y&&aim==3)||
            (player->y==enemies_map1[i].y&&player->x >= enemies_map1[i].x&&aim==2)||
            (player->y==enemies_map1[i].y&&player->x <= enemies_map1[i].x&&aim==4))&&
            (abs(player->x-enemies_map1[i].x)<=damage_distance&&abs(player->y-enemies_map1[i].y)<=damage_distance)){
                        enemies_map1[i].health-=damage;
                        attron(COLOR_PAIR(3));
                        mvprintw(2,COLS/2-17,"DAMAGE TO ENEMY,KEEP GOING!");
                        attroff(COLOR_PAIR(3));
                        getch();
                        mvprintw(2,COLS/2-17,"                           ");
                        if(enemies_map1[i].health<=0&&enemies_map1[i].exe==1){
                            map1[enemies_map1[i].y][enemies_map1[i].x]='.';
                            enemies_map1[i].exe=0;
                            attron(COLOR_PAIR(3));
                            mvprintw(2,COLS/2-10,"ELIMINATED!!!");
                            p_user.kills1++;
                            attroff(COLOR_PAIR(3));
                            refresh();
                            napms(1000);
                            mvprintw(2,COLS/2-10,"             ");
                        }
                
                }
        }
    }
    else if(level==2){
        for(int i=0 ; i<6 ;i++){
            if(((player->x==enemies_map2[i].x&&player->y >= enemies_map2[i].y&&aim==1)||
            (player->x==enemies_map2[i].x&&player->y <= enemies_map2[i].y&&aim==3)||
            (player->y==enemies_map2[i].y&&player->x >= enemies_map2[i].x&&aim==2)||
            (player->y==enemies_map2[i].y&&player->x <= enemies_map2[i].x&&aim==4))&&
            (abs(player->x-enemies_map2[i].x)<=damage_distance&&abs(player->y-enemies_map2[i].y)<=damage_distance)){
                        enemies_map2[i].health-=damage;
                        attron(COLOR_PAIR(3));
                        mvprintw(2,COLS/2-17,"DAMAGE TO ENEMY,KEEP GOING!");
                        attroff(COLOR_PAIR(3));
                        getch();
                        mvprintw(2,COLS/2-17,"                           ");
                        if(enemies_map2[i].health<=0&&enemies_map2[i].exe==1){
                            map2[enemies_map2[i].y][enemies_map2[i].x]='.';
                            enemies_map2[i].exe=0;
                            attron(COLOR_PAIR(3));
                            mvprintw(2,COLS/2-10,"ELIMINATED!!!");
                            p_user.kills1++;
                            attroff(COLOR_PAIR(3));
                            refresh();
                            napms(1000);
                            mvprintw(2,COLS/2-10,"             ");
                        }
                
                }
            }
    }
    else if(level==3){
        for(int i=0 ; i<6 ;i++){
            if(((player->x==enemies_map3[i].x&&player->y >= enemies_map3[i].y&&aim==1)||
            (player->x==enemies_map3[i].x&&player->y <= enemies_map3[i].y&&aim==3)||
            (player->y==enemies_map3[i].y&&player->x >= enemies_map3[i].x&&aim==2)||
            (player->y==enemies_map3[i].y&&player->x <= enemies_map3[i].x&&aim==4))&&
            (abs(player->x-enemies_map3[i].x)<=damage_distance&&abs(player->y-enemies_map3[i].y)<=damage_distance)){
                        enemies_map3[i].health-=damage;
                        attron(COLOR_PAIR(3));
                        mvprintw(2,COLS/2-17,"DAMAGE TO ENEMY,KEEP GOING!");
                        attroff(COLOR_PAIR(3));
                        getch();
                        mvprintw(2,COLS/2-17,"                           ");
                        if(enemies_map3[i].health<=0&&enemies_map3[i].exe==1){
                            map3[enemies_map3[i].y][enemies_map3[i].x]='.';
                            enemies_map3[i].exe=0;
                            attron(COLOR_PAIR(3));
                            mvprintw(2,COLS/2-10,"ELIMINATED!!!");
                            p_user.kills1++;
                            attroff(COLOR_PAIR(3));
                            refresh();
                            napms(1000);
                            mvprintw(2,COLS/2-10,"             ");
                        }
                
                }
            }
    }
    else if(level==4){
    for(int i=0 ; i<6 ;i++){
            if(((player->x==enemies_map4[i].x&&player->y >= enemies_map4[i].y&&aim==1)||
            (player->x==enemies_map4[i].x&&player->y <= enemies_map4[i].y&&aim==3)||
            (player->y==enemies_map4[i].y&&player->x >= enemies_map4[i].x&&aim==2)||
            (player->y==enemies_map4[i].y&&player->x <= enemies_map4[i].x&&aim==4))&&
            (abs(player->x-enemies_map4[i].x)<=damage_distance&&abs(player->y-enemies_map4[i].y)<=damage_distance)){
                        enemies_map4[i].health-=damage;
                        attron(COLOR_PAIR(3));
                        mvprintw(2,COLS/2-17,"DAMAGE TO ENEMY,KEEP GOING!");
                        attroff(COLOR_PAIR(3));
                        getch();
                        mvprintw(2,COLS/2-17,"                           ");
                        if(enemies_map4[i].health<=0&&enemies_map4[i].exe==1){
                            map4[enemies_map4[i].y][enemies_map4[i].x]='.';
                            enemies_map4[i].exe=0;
                            attron(COLOR_PAIR(3));
                            mvprintw(2,COLS/2-10,"ELIMINATED!!!");
                            p_user.kills1++;
                            attroff(COLOR_PAIR(3));
                            refresh();
                            napms(1000);
                            mvprintw(2,COLS/2-10,"             ");
                        }
                
                }
            }
    }
}
void create_battle_room(){
    memset(battle_room,' ',sizeof(battle_room));
    for (int i = 5; i < 35; i++) {
        battle_room[i][45]='|';
        battle_room[i][130]='|';
    }
    for (int i = 45; i <= 130; i++) {
        battle_room[5][i]='-';
        battle_room[35][i]='-';
    }
    for (int i = 6; i <= 34; i++) {
        for (int j = 46; j <130; j++) {
            battle_room[i][j]='.';
        }
    }
    for (int i = 0; i < 12; i++) {
        int y = rand() % 29 + 6;  
        int x = rand() % 83 + 46;
        enemies[i] = create_random_enemy(y, x);
        battle_room[y][x]=enemies[i].face;
    }
    // for (int i = 0; i < 12; i++) {
    //     int y = rand() % 29 + 6;  
    //     int x = rand() % 83 + 46;
    //     battle_room[y][x]='^';
    // }
}
Enemy create_random_enemy(int y, int x) {
    Enemy enemy;
    enemy.y = y;
    enemy.x = x;
    enemy.health = 100;  
    enemy.following_distance = 10;  
    enemy.damage_distance = 2;  
    enemy.following = 0;
    enemy.face = 'E';  
    enemy.perv = '.';  
    enemy.exe = 0;

     
    enemy.type = rand() % 5;  

     
    switch (enemy.type) {
        case DEAMON:
            enemy.health = 5;
            enemy.damage_distance = 3;
            enemy.following_distance = 1;
            enemy.exe = 1;
            enemy.damage = 5;
            enemy.face = 'D';
            break;
        case FIRE:
            enemy.health = 10;
            enemy.damage_distance = 2;
            enemy.following_distance = 4;
            enemy.exe = 1;
            enemy.damage = 10;
            enemy.face = 'F';
            break;
        case GIANT:
            enemy.health = 15;
            enemy.damage_distance = 2;
            enemy.following_distance = 4;
            enemy.exe = 1;
            enemy.damage = 15;
            enemy.face = 'G';
            break;
        case SNAKE:
            enemy.health = 20;
            enemy.damage_distance = 3;
            enemy.following_distance = 100;
            enemy.exe = 1;
            enemy.damage = 15;
            enemy.face = 'S';
            break;
        case UNDEAD:
            enemy.health = 30;
            enemy.damage_distance = 2;
            enemy.following_distance = 3;
            enemy.exe = 1;
            enemy.damage = 20;
            enemy.face = 'U';
            break;
    }

    return enemy;
}
void clear_player2(Player *player) {
        if(player->prev_char=='3'){
            battle_room[player->y][player->x]='^';
            p_user.health-=10;
            attron(COLOR_PAIR(2));
            mvprintw(1,80,"     TRAP!");
            attroff(COLOR_PAIR(2));
            refresh();
            napms(1000);
        }
        else{
            battle_room[player->y][player->x]='.';
        } 
    }
int move_player(Player *player) {
        if(p_user.weapon_bar.arrow<=0 && p_user.weapon_bar.dagger<=0 && p_user.weapon_bar.sword<=0 && p_user.weapon_bar.magic_wand<=0){
            p_user.current_weapon='m';
        }
        if(p_user.hunger>=100){
            p_user.hunger=100;
            p_user.health=10000;
        }
        if(inwar==0){
            int ch = getch();
            int x=0;
            for(int i=0 ; i<12 ;i++){
                x+=enemies[i].exe;
            }
            p_user.kills2=12-x;

            p_user.kills1=p_user.kills2+killna;
            if(p_user.kills2>=12){
                final_result(1);
            }
            int new_x = player->x, new_y = player->y;
            if(ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='6'||ch=='7'||ch=='8'||ch=='9'){
                for (int i = 0; i < 12; i++) {
                    if (enemies[i].exe==1) {
                        enemy_checker(player, &enemies[i]);
                    }
                }
                if(Gspell==1&&Gspellc<=10){
                    Gspellc++;
                }
                else if(Gspellc>10){
                    Gspell=0;
                }
                if(Hspell==1&&Hspellc<=10){
                    Hspellc++;
                }
                else if(Hspellc>10){
                    Hspell=0;
                }
                pace_counter1++;
                if(p_user.difficulty==0){
                    if(p_user.hunger<=0){
                        p_user.hunger=0;
                        p_user.health-=5;
                    }
                    else{
                        p_user.hunger-=1;
                    }
                }
                if(p_user.difficulty==1){
                    if(p_user.hunger<=0){
                        p_user.hunger=0;
                        p_user.health-=10;
                    }
                    else{
                        p_user.hunger-=2;
                    }
                }
                if(p_user.difficulty==2){
                    if(p_user.hunger<=0){
                        p_user.hunger=0;
                        p_user.health-=20;
                    }
                    else{
                        p_user.hunger-=3;
                    }
                }
            }
            if (ch == 's' && pace_counter2<5) {
                pace=2;
                pace_counter1=0;
                pace_counter2++;

            }
            if(pace_counter1>=5){
                pace = 1;
            }
            switch (ch) {
            case '1': new_x -= pace; new_y += pace; break;
            case '2': new_y += pace; break;
            case '3': new_x += pace; new_y += pace; break;
            case '4': new_x -= pace; break;
            case '6': new_x += pace; break;
            case '7': new_x -= pace; new_y -= pace; break;
            case '8': new_y -= pace; break;
            case '9': new_x += pace; new_y -= pace; break;
            case 'e':
                food_table();
                break;
            case 'q':main_menu();
            case 'm':
                show_count++;
                if(show_count>=4){
                    break;
                }
                show_full_map_temporarily(player);
                break;
                case 'p': spell_table();
                    break;
                case 'i':weapon_table();
                    break;
                case ' ':
                    damage_enemy2(p_user.current_weapon,player);                
                    break;
            }
            
            wandon=0;
            
            if (p_user.health <= 0) {
                final_result(0);
            }
            if (is_valid_move2(new_x, new_y)) {
                clear_player2(player);
                player->prev_char = mvinch(new_y, new_x) & A_CHARTEXT;
                player->x = new_x;
                player->y = new_y;
                battle_room[player->y][player->x]='@';
                
            }
            refresh_map2(player);
        }
        else if(inwar==1){
            if(enemies_war[0].exe==0 && enemies_war[1].exe==0 && enemies_war[2].exe==0){
                inwar=0;
                return 1;
            }
            int ch = getch();
            int new_x = player->x, new_y = player->y;
            if(ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='6'||ch=='7'||ch=='8'||ch=='9'){
                for (int i = 0; i < 3; i++) {
                if (enemies_war[i].exe==1) {
                    enemy_checker(player, &enemies_war[i]);
                }
            }
                
                if(Gspell==1&&Gspellc<=10){
                    Gspellc++;
                }
                else if(Gspellc>10){
                    Gspell=0;
                }
                if(Hspell==1&&Hspellc<=10){
                    Hspellc++;
                }
                else if(Hspellc>10){
                    Hspell=0;
                }
                pace_counter1++;
                if(p_user.difficulty==0){
                    if(p_user.hunger<=0){
                        p_user.hunger=0;
                        p_user.health-=5;
                    }
                    else{
                        p_user.hunger-=1;
                    }
                }
                if(p_user.difficulty==1){
                    if(p_user.hunger<=0){
                        p_user.hunger=0;
                        p_user.health-=10;
                    }
                    else{
                        p_user.hunger-=2;
                    }
                }
                if(p_user.difficulty==2){
                    if(p_user.hunger<=0){
                        p_user.hunger=0;
                        p_user.health-=20;
                    }
                    else{
                        p_user.hunger-=3;
                    }
                }
            }
            if (ch == 's' && pace_counter2<5) {
                pace=2;
                pace_counter1=0;
                pace_counter2++;

            }
            if(pace_counter1>=5){
                pace = 1;
            }
            switch (ch) {
            case '1': new_x -= pace; new_y += pace; break;
            case '2': new_y += pace; break;
            case '3': new_x += pace; new_y += pace; break;
            case '4': new_x -= pace; break;
            case '6': new_x += pace; break;
            case '7': new_x -= pace; new_y -= pace; break;
            case '8': new_y -= pace; break;
            case '9': new_x += pace; new_y -= pace; break;
            case 'e':
                food_table();
                break;
            case 'q':main_menu();
            case 'p': spell_table();
                break;
            case 'i':weapon_table();
                break;
            case ' ':
                damage_enemy2(p_user.current_weapon,player);                
            break;
            }
            wandon=0;
            
            if (p_user.health <= 0) {
                final_result(0);
            }
            if (is_valid_move2(new_x, new_y)) {
                clear_player(player);
                player->prev_char = mvinch(new_y, new_x) & A_CHARTEXT;
                player->x = new_x;
                player->y = new_y;
                war_house[player->y][player->x]='@';
                
            }
            refresh3(player);
        }
        
} 
int enemy_checker(Player *player, Enemy *enemy) {
    if(inwar==1){
        int distance = abs(player->x - enemy->x) + abs(player->y - enemy->y);
        if (distance <= enemy->following_distance) {
            enemy->following = 1;
            
            if (distance <= enemy->damage_distance&&enemy->exe==1) {
                switch (enemy->type) {
                    case DEAMON:
                        p_user.health -= enemy->damage;
                        break;
                    case FIRE:
                        p_user.health -= enemy->damage;
                        break;
                    case GIANT:
                        p_user.health -= enemy->damage;
                        break;
                    case SNAKE:
                        p_user.health -= enemy->damage;
                        break;
                    case UNDEAD:
                        p_user.health -= enemy->damage;
                        break;
                }
                attron(COLOR_PAIR(2));
                mvprintw(38,85,"DAMAGE!!!");
                getch();
                mvprintw(38,85,"         ");
                attroff(COLOR_PAIR(2));
            } 
            else if(enemy->exe==1&&wandon==0){
                int x =enemy->x;
                int y =enemy->y;
                if (player->x > enemy->x) x++;
                else if (player->x < enemy->x) x--;
                
                if (player->y > enemy->y) y++;
                else if (player->y < enemy->y) y--;
                if(war_house[y][x]=='.'){
                    war_house[enemy->y][enemy->x]='.';
                    enemy->x=x;
                    enemy->y=y;
                    war_house[enemy->y][enemy->x]=enemy->face;
                }
            }
        }
        
            return enemy->following;
    }
    else if(inwar==0){
        int distance = abs(player->x - enemy->x) + abs(player->y - enemy->y);
        if (distance <= enemy->following_distance) {
            enemy->following = 1;
            
            if (distance <= enemy->damage_distance&&enemy->exe==1) {
                switch (enemy->type) {
                    case DEAMON:
                        p_user.health -= enemy->damage;
                        break;
                    case FIRE:
                        p_user.health -= enemy->damage;
                        break;
                    case GIANT:
                        p_user.health -= enemy->damage;
                        break;
                    case SNAKE:
                        p_user.health -= enemy->damage;
                        break;
                    case UNDEAD:
                        p_user.health -= enemy->damage;
                        break;
                }
                attron(COLOR_PAIR(2));
                mvprintw(38,85,"DAMAGE!!!");
                getch();
                mvprintw(38,85,"         ");
                attroff(COLOR_PAIR(2));
            } 
            else if(enemy->exe==1&&wandon==0){
                int x =enemy->x;
                int y =enemy->y;
                if (player->x > enemy->x) x++;
                else if (player->x < enemy->x) x--;
                
                if (player->y > enemy->y) y++;
                else if (player->y < enemy->y) y--;
                if(battle_room[y][x]=='.'){
                    battle_room[enemy->y][enemy->x]='.';
                    enemy->x=x;
                    enemy->y=y;
                    battle_room[enemy->y][enemy->x]=enemy->face;
                }
            }
        }
        
            return enemy->following;
        }
    
}
int is_valid_move2(int x, int y) {
    char ch = mvinch(y, x) & A_CHARTEXT;
    return ch == '.' || ch == '#' || ch == '+'||ch == '<'||ch=='3'||ch=='^';
}
void refresh_map2(Player *player) {
    draw_player(player);
    draw_battle_room();
    mvprintw(LINES-2,2,"                              ");
    mvprintw(LINES-2,20,"                              ");
    mvprintw(LINES-3,62,"                                         ");
    attron(COLOR_PAIR(10));
    mvprintw(0,77,"ZYRUS is watching you :)");
    attroff(COLOR_PAIR(10));
    draw_bar(LINES-2, 62, 20, p_user.health, 10000, "Health");
    draw_bar(LINES-3, 62, 20, p_user.hunger, 100, "Power");
    attron(COLOR_PAIR(1));
    mvprintw(LINES-2,14,"Score : %d",p_user.score);
    mvprintw(LINES-2,2,"Gold : %d",p_user.gold);
    mvprintw(LINES-2,26,"Kills : %d",p_user.kills1);
    attroff(COLOR_PAIR(1));
    mvprintw(LINES-6,2,"                              ");
    //attron(COLOR_PAIR(7));
    pace_counter2=0;
    //attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(10));
    switch(p_user.current_weapon){
        case 'm':
            mvprintw(LINES-6,2,"current weapon : MACE");
        break;
        case 'd':
            mvprintw(LINES-6,2,"current weapon : DAGGER %d",p_user.weapon_bar.dagger);
        break;
        case 'w':
            mvprintw(LINES-6,2,"current weapon : MAGIC WAND %d",p_user.weapon_bar.magic_wand);
        break;
        case 'a':
            mvprintw(LINES-6,2,"current weapon : ARROWS %d",p_user.weapon_bar.arrow);
        break;
        case 's':
            mvprintw(LINES-6,2,"current weapon : SWORD");
        break;
    }
    attroff(COLOR_PAIR(10));
    attron(COLOR_PAIR(6));
        mvprintw(LINES-5,2,"Health spell : %d",p_user.spell_bar.H);
        mvprintw(LINES-4,2,"Speed  spell : %d",p_user.spell_bar.S);
        mvprintw(LINES-3,2,"Power  spell : %d",p_user.spell_bar.G);
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(9));
        mvprintw(LINES-5,20,"Normal food : %d",p_user.food_bar.normal);
        mvprintw(LINES-4,20,"Speedy food : %d",p_user.food_bar.speed);
        mvprintw(LINES-3,20,"Supreme  food : %d",p_user.food_bar.special);
    attroff(COLOR_PAIR(9));
    attron(COLOR_PAIR(11));
    //attron(A_REVERSE);
    attron(A_BOLD);
    mvprintw(3,80,"Final Kills : %d",p_user.kills2);
    attroff(A_BOLD);
    //attroff(A_REVERSE);
    attroff(COLOR_PAIR(11));
    refresh();  
}
int start_battle(){
    clear();
    show_count = 0;
    pace=1;
    pace_counter1=0;
    pace_counter2=0;
    Player player;
    player.x = 70;
    player.y = 25;
    killna = p_user.kills1;
    create_battle_room();
    refresh_map2(&player);  
    while (1) {
        move_player(&player);
    }
}
void draw_battle_room(){
    for(int i=0; i<MAP_HEIGHT ;i++){
        for(int j=0 ; j<MAP_WIDTH ;j++){
            if(battle_room[i][j]=='|'||battle_room[i][j]=='-'){
                attron(COLOR_PAIR(1));
                mvaddch(i,j,battle_room[i][j]);
                attroff(COLOR_PAIR(1));
            }
            else if(battle_room[i][j]=='G'||battle_room[i][j]=='S'||battle_room[i][j]=='F'||battle_room[i][j]=='U'||battle_room[i][j]=='D'){
                attron(COLOR_PAIR(2));
                mvaddch(i,j,battle_room[i][j]);
                attroff(COLOR_PAIR(2));
            }
            // else if(battle_room[i][j]=='3'){
            //     
            //     mvaddch(i,j,'.');
            // }
            else{
                mvaddch(i,j,battle_room[i][j]);
            }
        }
    }
}
int damage_enemy2(char weapon,Player *player){
    attron(COLOR_PAIR(3));
    mvprintw(1,80,"ENTER DIRECTION");
    attroff(COLOR_PAIR(3));
    int direction = getch();
    mvprintw(1,80,"               ");
    int aim;
    switch (direction)
    {
    case '8':
        aim=1;
        break;
    case '4':
        aim=2;
        break;
    case '2':
        aim=3;
        break;
    case '6':
        aim=4;
        break;
    default:
        break;
    }
    int damage;
    int damage_distance;
    attron(COLOR_PAIR(10));
    switch(weapon){
        case 'm':
        wandon=0;
        damage=5;
        damage_distance=1;
        break;
        case 'd':
        if(p_user.weapon_bar.dagger<=0){
            mvprintw(1,2,"NOT ENOUGH DAGGER!!!");
            wandon=0;
            getch();
            mvprintw(1,2,"                    ");
            return 1;
        }
        wandon=0;
        damage=12;
        damage_distance=5;
        p_user.weapon_bar.dagger--;
        break;
        case 'w':
        if(p_user.weapon_bar.magic_wand<=0){
            mvprintw(1,2,"NOT ENOUGH MAGIC WAND!!!");
            getch();
            mvprintw(1,2,"                       ");
            wandon=0;
            return 1;
        }
        wandon=1;
        damage=15;
        damage_distance=10;
        p_user.weapon_bar.magic_wand--;
        break;
        case 'a':
        if(p_user.weapon_bar.arrow<=0){
            mvprintw(1,2,"NOT ENOUGH ARROW!!!");
            wandon=0;
            getch();
            mvprintw(1,2,"                    ");
            return 1;
        }
        wandon=0;
        damage=5;
        damage_distance=5;
        p_user.weapon_bar.arrow--;
        break;
        case 's':
        if(p_user.weapon_bar.sword==0){
            mvprintw(1,2,"NOT ENOUGH SWORD!!!");
            wandon=0;
            getch();
            mvprintw(1,2,"                    ");
            return 1;
        }
        wandon=0;
        damage_distance=1;
        damage=10;
        break;
        attroff(COLOR_PAIR(10));
    }
    if(Gspell==1){
            damage*=2;
    }
    if(inwar==0){
        for(int i=0 ; i<12 ;i++){
            if(((player->x==enemies[i].x&&player->y >= enemies[i].y&&aim==1)||
            (player->x==enemies[i].x&&player->y <= enemies[i].y&&aim==3)||
            (player->y==enemies[i].y&&player->x >= enemies[i].x&&aim==2)||
            (player->y==enemies[i].y&&player->x <= enemies[i].x&&aim==4))&&
            (abs(player->x-enemies[i].x)<=damage_distance&&abs(player->y-enemies[i].y)<=damage_distance)){
                        enemies[i].health-=damage;
                        attron(COLOR_PAIR(3));
                        mvprintw(2,COLS/2-17,"DAMAGE TO ENEMY,KEEP GOING!");
                        attroff(COLOR_PAIR(3));
                        getch();
                        mvprintw(2,COLS/2-17,"                           ");
                        if(enemies[i].health<=0&&enemies[i].exe==1){
                            battle_room[enemies[i].y][enemies[i].x]='.';
                            enemies[i].exe=0;
                            attron(COLOR_PAIR(3));
                            mvprintw(2,COLS/2-10,"ELIMINATED!!!");
                            attroff(COLOR_PAIR(3));
                        }
            }
        }
    }
    else if(inwar==1){
        for(int i=0 ; i<3 ;i++){
            if(((player->x==enemies_war[i].x&&player->y >= enemies_war[i].y&&aim==1)||
            (player->x==enemies_war[i].x&&player->y <= enemies_war[i].y&&aim==3)||
            (player->y==enemies_war[i].y&&player->x >= enemies_war[i].x&&aim==2)||
            (player->y==enemies_war[i].y&&player->x <= enemies_war[i].x&&aim==4))&&
            (abs(player->x-enemies_war[i].x)<=damage_distance&&abs(player->y-enemies_war[i].y)<=damage_distance)){
                        enemies_war[i].health-=damage;
                        attron(COLOR_PAIR(3));
                        mvprintw(2,COLS/2-17,"DAMAGE TO ENEMY,KEEP GOING!");
                        attroff(COLOR_PAIR(3));
                        getch();
                        mvprintw(2,COLS/2-17,"                           ");
                        if(enemies_war[i].health<=0&&enemies_war[i].exe==1){
                            war_house[enemies_war[i].y][enemies_war[i].x]='.';
                            enemies_war[i].exe=0;
                            attron(COLOR_PAIR(3));
                            mvprintw(2,COLS/2-10,"ELIMINATED!!!");
                            p_user.kills1++;
                            attroff(COLOR_PAIR(3));
                        }
            }
        }
    }
    
}
void music(){
    attron(COLOR_PAIR(10));
    const char *musicFolder = "/home/radin-aj/Documents/University/fop/project/functions/musics/";
    const char *musicFiles[] = {
        "eminem-rap_god.mp3",
        "GTA_IV.mp3",
        "Vaveyla _Leyli.mp3"
    };
    int musicCount = sizeof(musicFiles) / sizeof(musicFiles[0]);
    mvprintw(LINES/2 - 6 ,COLS/2 -15,"Available music files:");
    displayMusicList(musicFiles, musicCount);
    mvprintw(LINES/2 -5 + musicCount,COLS/2 -15,"Enter the number of the music file to play: ");
    refresh();
    int choice = getch() - '0';   

    if (choice < 1 || choice > musicCount) {
        mvprintw(LINES/2 - 4+ musicCount,COLS/2 -15,"Invalid choice");
        refresh();
        getch();
        return;
    }
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s%s", musicFolder, musicFiles[choice - 1]); 
    strcpy(main_music ,fullPath);
    strcpy(current_music ,fullPath);
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printw("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        refresh();
        getch();
        endwin();
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printw("SDL_mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
        refresh();
        getch();
        endwin();
        return;
    }
    Mix_Music *music = Mix_LoadMUS(fullPath);
    if (!music) {
        printw("Failed to load music! Mix_Error: %s\n", Mix_GetError());
        refresh();
        getch();
        endwin();
        return;
    }
    Mix_PlayMusic(music, -1);   
    //printw("Playing: %s\n", fullPath);
    mvprintw(LINES/2 -5 + musicCount+1,COLS/2 -15,"Press 'p' to pause/resume, 'q' to quit.");
    refresh();
    bool isPlaying = true;   
    bool quit = false;       
    while (!quit) {
        int ch = getch();   

        switch (ch) {
            case 'p':   
                if (isPlaying) {
                    Mix_PauseMusic();   
                    mvprintw(LINES/2 -5 + musicCount+2,COLS/2 -15,"Music paused. Press 'p' to resume.");
                } else {
                    Mix_ResumeMusic();   
                    mvprintw(LINES/2 -5 + musicCount+2,COLS/2 -15,"Music resumed. Press 'p' to pause.");
                }
                isPlaying = !isPlaying;   
                break;

            case 'q':   
                quit = true;
                break;
        }
        attroff(COLOR_PAIR(10));
        refresh();
    }
    // Mix_FreeMusic(music);
    // Mix_CloseAudio();
    // SDL_Quit();
}
void displayMusicList(const char *musicFiles[], int count) {
    for (int i = 0; i < count; i++) {
        attron(COLOR_PAIR(10));
        mvprintw(LINES/2-5 + i,COLS/2-15,"%d. %s\n", i + 1, musicFiles[i]);
        attroff(COLOR_PAIR(10));
    }
}
void final_result(int x){
    clear();
    int height = 12;
    int width = 50;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;
    
        attron(COLOR_PAIR(7));
        for (int y = start_y; y < start_y + height; y++) {
            for (int x = start_x; x < start_x + width; x++) {
                if (y == start_y || y == start_y + height - 1 || x == start_x || x == start_x + width - 1) {
                    mvaddch(y, x, ACS_CKBOARD);   
                }
            }
        }
        attroff(COLOR_PAIR(7));
        if(x==1){
            p_user.score+=200;
            attron(COLOR_PAIR(3));
            mvprintw(start_y + 2, start_x + (width - 10) / 2, " YOU WON! ");
            attroff(COLOR_PAIR(3));
            attron(COLOR_PAIR(1));
            mvprintw(start_y + 4, start_x + 5, "Gold: %d", p_user.gold);
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(10));
            mvprintw(start_y + 5, start_x + 5, "Score: %d", p_user.score);
            attroff(COLOR_PAIR(10));
            attron(COLOR_PAIR(2));
            mvprintw(start_y + 6, start_x + 5, "Kills: %d", p_user.kills1+p_user.kills2);
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(7));
            mvprintw(start_y + height - 3, start_x + 5, "----------------------------------------");
            attroff(COLOR_PAIR(7));
            attron(COLOR_PAIR(8));
            mvprintw(start_y + height - 2, start_x + (width - 20) / 2-5, "Opportunities don't happen, you create them");
            attroff(COLOR_PAIR(8));
            if(is_logged_in==0){
                refresh();
                napms(10000);
                getch();
                show_table();
                main_menu();
            }
            else{
                save_info();
            }
            
        }
        else{
            attron(COLOR_PAIR(2));
            mvprintw(start_y + 2, start_x + (width - 10) / 2, " YOU LOST! ");
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(1));
            mvprintw(start_y + 4, start_x + 5, "Gold: %d", p_user.gold);
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(10));
            mvprintw(start_y + 5, start_x + 5, "Score: %d", p_user.score);
            attroff(COLOR_PAIR(10));
            attron(COLOR_PAIR(2));
            mvprintw(start_y + 6, start_x + 5, "Kills: %d", p_user.kills1+p_user.kills2);
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(7));
            mvprintw(start_y + height - 3, start_x + 5, "----------------------------------------");
            attroff(COLOR_PAIR(7));
            attron(COLOR_PAIR(8));
            mvprintw(start_y + height - 2, start_x + (width - 20) / 2 -5, "Failure Shouldn't Define You, But It Can Help Shape You");
            attroff(COLOR_PAIR(8));
            if(is_logged_in==0){
                refresh();
                napms(10000);
                getch();
                show_table();
                main_menu();
            }
            else{
                save_info();
            }
        }
        refresh();
        napms(10000);
        getch();
        show_table();
        main_menu();    
}
void draw_robot_art(int start_y, int start_x) {
    attron(COLOR_PAIR(7));
     mvprintw(start_y, start_x, "       _____");
    mvprintw(start_y + 1, start_x, "      /     \\");
    mvprintw(start_y + 2, start_x, "     | () () |");
    mvprintw(start_y + 3, start_x, "     |   ^   |");
    mvprintw(start_y + 4, start_x, "     |  [-]  |");
    mvprintw(start_y + 5, start_x, "     |_______|");
    mvprintw(start_y + 6, start_x, "      /| |\\");
    mvprintw(start_y + 7, start_x, "     / | | \\");
    mvprintw(start_y + 8, start_x, "    /  | |  \\");
    mvprintw(start_y + 9, start_x, "   /   | |   \\");
    mvprintw(start_y + 10, start_x, "  /    | |    \\");
    mvprintw(start_y + 11, start_x, " /     | |     \\");
    mvprintw(start_y + 12, start_x, "/______| |______\\");
    mvprintw(start_y + 13, start_x, "       | |");
    mvprintw(start_y + 14, start_x, "       | |");
    mvprintw(start_y + 15, start_x, "       | |");
    mvprintw(start_y + 16, start_x, "      _| |_");
    mvprintw(start_y + 17, start_x, "     (_____)");

    // Draw the speech cloud to the right of the robot
    mvprintw(start_y + 4, start_x + 15, "         ___________");
    mvprintw(start_y + 5, start_x + 18, " \\   /           \\");
    mvprintw(start_y + 6, start_x + 18, "  \\ |    Hello,   |");
    mvprintw(start_y + 7, start_x + 18, "    |   Welcome!  |");
    mvprintw(start_y + 8, start_x + 18, "     \\___________/");
    mvprintw(start_y + 9, start_x + 15, "        ");
    mvprintw(start_y + 10, start_x + 16, "         ");

    attroff(COLOR_PAIR(7));
}
void save_map(char map[MAP_HEIGHT][MAP_WIDTH]){
    char filename[200];
    snprintf(filename, sizeof(filename), "%s.txt", p_user.username);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            fputc(map[y][x], file);
        }
        fputc('\n', file);
    }
    attron(COLOR_PAIR(3));
    mvprintw(1,80,"       SAVED!");
    attroff(COLOR_PAIR(3));
    refresh();
    napms(2000);
    fclose(file);
    mvprintw(1,80,"             ");
}
int save_info(){
    const char *filename = "users.txt";
    User users[200];
    int num_users = 0;
    if (!read_users(filename, users, &num_users)) {
        return 1;
    }
    char current_username[50];
    strcpy(current_username,l_user.username);
    User *user = find_user(users, num_users, current_username);
    user->gold = l_user.gold;
    user->score = l_user.score;
    user->kills1 = l_user.kills1;
    user->game=l_user.game;
    if (!write_users(filename, users, num_users)) {
        return 1;
    }
    refresh();
}
int read_users(const char *filename, User users[], int *num_users) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return 0;
    }

    *num_users = 0;
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %s %d %d %d %d %d %d %d",
               users[*num_users].username,
               users[*num_users].password,
               users[*num_users].email,
               &users[*num_users].score,
               &users[*num_users].gold,
               &users[*num_users].game,
               &users[*num_users].color,
               &users[*num_users].difficulty,
               &users[*num_users].kills1,
               &users[*num_users].level_num);
        (*num_users)++;
    }

    fclose(file);
    return 1;
}
int write_users(const char *filename, User users[], int num_users) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return 0;
    }

    for (int i = 0; i < num_users; i++) {
        fprintf(file, "%s %s %s %d %d %d %d %d %d %d\n",
                users[i].username,
                users[i].password,
                users[i].email,
                users[i].score,
                users[i].gold,
                users[i].game,
                users[i].color,
                users[i].difficulty,
                users[i].kills1,
                users[i].level_num);
    }

    fclose(file);
    return 1;
}
User* find_user(User users[], int num_users, const char *username) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return &users[i];
        }
    }
    return NULL;
}
int telesm(Player *player){
    attron(COLOR_PAIR(6));
    if(p_user.level_num==1){
        if(get_room_id(player->x,player->y)==5){
            mvprintw(3,74,"YOU ARE IN ENCHANTED ROOM :o");
            strcpy(current_music,"peritune-spook4(chosic.com).mp3");
            p_user.health-=10;
            return 1;
        }
        else{
            mvprintw(3,74,"                            ");
            cp=0;
            return 0;
        }
    }
    else if(p_user.level_num==2){
        if(get_room_id(player->x,player->y)==5||get_room_id(player->x,player->y)==1){
            mvprintw(3,74,"YOU ARE IN ENCHANTED ROOM :o");
            strcpy(current_music,"peritune-spook4(chosic.com).mp3");
            p_user.health-=10;
            return 1;
        }
        else if(get_room_id(player->x,player->y)==3){
            mvprintw(3,74,"YOU ARE IN NIGHTMARE ROOM :o");
            strcpy(current_music,"peritune-spook4(chosic.com).mp3");
            night=1;
            return 1;
        }
        else{
            cp=0;
            mvprintw(3,74,"                            ");
            night=0;
            return 0;
        }
    }
    else if(p_user.level_num==3){
        if(get_room_id(player->x,player->y)==6){
            mvprintw(3,74,"YOU ARE IN ENCHANTED ROOM :o");
            strcpy(current_music,"peritune-spook4(chosic.com).mp3");
            p_user.health-=10;
            return 1;
        }
        else if(get_room_id(player->x,player->y)==2||get_room_id(player->x,player->y)==5){
            mvprintw(3,74,"YOU ARE IN NIGHTMARE ROOM :o");
            strcpy(current_music,"peritune-spook4(chosic.com).mp3");
            night=1;
            return 1;
        }
        else{
            cp=0;
            night=0;
            mvprintw(3,74,"                            ");
            return 0;
        }

    }
    else if(p_user.level_num==4){
        if(get_room_id(player->x,player->y)==3||get_room_id(player->x,player->y)==6||get_room_id(player->x,player->y)==8){
            mvprintw(3,74,"YOU ARE IN ENCHANTED ROOM :o");
            strcpy(current_music,"peritune-spook4(chosic.com).mp3");
            p_user.health-=10;
            return 1;
        }
        else if(get_room_id(player->x,player->y)==7){
            mvprintw(3,74,"YOU ARE IN NIGHTMARE ROOM :o");
            strcpy(current_music,"peritune-spook4(chosic.com).mp3");
            night=1;
            return 1;
        }
        else{
            cp=0;
            night=0;
            mvprintw(3,74,"                            ");
            return 0;
        }
    }
    attroff(COLOR_PAIR(6));
}
int enemy_checker2(Player *player){
    if(p_user.level_num==1){
        for(int i=0 ; i<=4 ; i++){
            int distance = abs(player->x - enemies_map1[i].x) + abs(player->y - enemies_map1[i].y);
                if (distance <= enemies_map1[i].following_distance) {
                enemies_map1[i].following = 1;
            
                if (distance <= enemies_map1[i].damage_distance&&enemies_map1[i].exe==1) {
                    switch (enemies_map1[i].type) {
                        case DEAMON:
                            p_user.health -= enemies_map1[i].damage;
                            break;
                        case FIRE:
                            p_user.health -= enemies_map1[i].damage;
                            break;
                        case GIANT:
                            p_user.health -= enemies_map1[i].damage;
                            break;
                        case SNAKE:
                            p_user.health -= enemies_map1[i].damage;
                            break;
                        case UNDEAD:
                            p_user.health -= enemies_map1[i].damage;
                            break;
                    }
                    message(3,40);
                } 
                else if(enemies_map1[i].exe==1&&wandon==0){
                    int x =enemies_map1[i].x;
                    int y =enemies_map1[i].y;
                    if (player->x > enemies_map1[i].x) x++;
                    else if (player->x < enemies_map1[i].x) x--;
                    
                    if (player->y > enemies_map1[i].y) y++;
                    else if (player->y < enemies_map1[i].y) y--;
                    if(map1[y][x]=='.'){
                        map1[enemies_map1[i].y][enemies_map1[i].x]='.';
                        enemies_map1[i].x=x;
                        enemies_map1[i].y=y;
                        map1[enemies_map1[i].y][enemies_map1[i].x]=enemies_map1[i].face;
                    }
                }
            }
        }
    }
    else if(p_user.level_num==2){
        for(int i=0 ; i<=5 ; i++){
            int distance = abs(player->x - enemies_map2[i].x) + abs(player->y - enemies_map2[i].y);
                if (distance <= enemies_map2[i].following_distance) {
                enemies_map2[i].following = 1;
            
                if (distance <= enemies_map2[i].damage_distance&&enemies_map2[i].exe==1) {
                    switch (enemies_map2[i].type) {
                        case DEAMON:
                            p_user.health -= enemies_map2[i].damage;
                            break;
                        case FIRE:
                            p_user.health -= enemies_map2[i].damage;
                            break;
                        case GIANT:
                            p_user.health -= enemies_map2[i].damage;
                            break;
                        case SNAKE:
                            p_user.health -= enemies_map2[i].damage;
                            break;
                        case UNDEAD:
                            p_user.health -= enemies_map2[i].damage;
                            break;
                    }
                    message(3,40);
                } 
                else if(enemies_map2[i].exe==1&&wandon==0){
                    int x =enemies_map2[i].x;
                    int y =enemies_map2[i].y;
                    if (player->x > enemies_map2[i].x) x++;
                    else if (player->x < enemies_map2[i].x) x--;
                    
                    if (player->y > enemies_map2[i].y) y++;
                    else if (player->y < enemies_map2[i].y) y--;
                    if(map2[y][x]=='.'){
                        map2[enemies_map2[i].y][enemies_map2[i].x]='.';
                        enemies_map2[i].x=x;
                        enemies_map2[i].y=y;
                        map2[enemies_map2[i].y][enemies_map2[i].x]=enemies_map2[i].face;
                    }
                }
            }
        }
    }
    else if(p_user.level_num==3){
        for(int i=0 ; i<=5 ; i++){
            int distance = abs(player->x - enemies_map3[i].x) + abs(player->y - enemies_map3[i].y);
                if (distance <= enemies_map3[i].following_distance) {
                enemies_map3[i].following = 1;
            
                if (distance <= enemies_map3[i].damage_distance&&enemies_map3[i].exe==1) {
                    switch (enemies_map3[i].type) {
                        case DEAMON:
                            p_user.health -= enemies_map3[i].damage;
                            break;
                        case FIRE:
                            p_user.health -= enemies_map3[i].damage;
                            break;
                        case GIANT:
                            p_user.health -= enemies_map3[i].damage;
                            break;
                        case SNAKE:
                            p_user.health -= enemies_map3[i].damage;
                            break;
                        case UNDEAD:
                            p_user.health -= enemies_map3[i].damage;
                            break;
                    }
                    message(3,40);
                } 
                else if(enemies_map3[i].exe==1&&wandon==0){
                    int x =enemies_map3[i].x;
                    int y =enemies_map3[i].y;
                    if (player->x > enemies_map3[i].x) x++;
                    else if (player->x < enemies_map3[i].x) x--;
                    
                    if (player->y > enemies_map3[i].y) y++;
                    else if (player->y < enemies_map3[i].y) y--;
                    if(map3[y][x]=='.'){
                        map3[enemies_map3[i].y][enemies_map3[i].x]='.';
                        enemies_map3[i].x=x;
                        enemies_map3[i].y=y;
                        map3[enemies_map3[i].y][enemies_map3[i].x]=enemies_map3[i].face;
                    }
                }
            }
        }
    }
    else if(p_user.level_num==4){
        for(int i=0 ; i<=5 ; i++){
            int distance = abs(player->x - enemies_map4[i].x) + abs(player->y - enemies_map4[i].y);
                if (distance <= enemies_map4[i].following_distance) {
                enemies_map4[i].following = 1;
            
                if (distance <= enemies_map4[i].damage_distance&&enemies_map4[i].exe==1) {
                    switch (enemies_map4[i].type) {
                        case DEAMON:
                            p_user.health -= enemies_map4[i].damage;
                            break;
                        case FIRE:
                            p_user.health -= enemies_map4[i].damage;
                            break;
                        case GIANT:
                            p_user.health -= enemies_map4[i].damage;
                            break;
                        case SNAKE:
                            p_user.health -= enemies_map4[i].damage;
                            break;
                        case UNDEAD:
                            p_user.health -= enemies_map4[i].damage;
                            break;
                    }
                    message(3,40);
                } 
                else if(enemies_map4[i].exe==1&&wandon==0){
                    int x =enemies_map4[i].x;
                    int y =enemies_map4[i].y;
                    if (player->x > enemies_map4[i].x) x++;
                    else if (player->x < enemies_map4[i].x) x--;
                    
                    if (player->y > enemies_map4[i].y) y++;
                    else if (player->y < enemies_map4[i].y) y--;
                    if(map4[y][x]=='.'){
                        map4[enemies_map4[i].y][enemies_map4[i].x]='.';
                        enemies_map4[i].x=x;
                        enemies_map4[i].y=y;
                        map4[enemies_map4[i].y][enemies_map4[i].x]=enemies_map4[i].face;
                    }
                }
            }
        }
    }
}
int save_info2(){
    const char *filename = "users.txt";
    User users[200];
    int num_users = 0;
    if (!read_users(filename, users, &num_users)) {
        return 1;
    }
    char current_username[50];
    strcpy(current_username,l_user.username);
    User *user = find_user(users, num_users, current_username);
    user->gold += p_user.gold;
    user->score += p_user.score;
    user->color=p_user.color;
    user->difficulty=p_user.difficulty;
    user->kills1=p_user.kills1;
    user->game=l_user.game;
    l_user.level_num=p_user.level_num;
    user->level_num=l_user.level_num;
    if (!write_users(filename, users, num_users)) {
        return 1;
    }
    refresh();
}
char* pass_generator(char *password){
    const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
    const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char numbers[] = "0123456789";
    int length =8; 

    password[0] = lowercase[rand() % (sizeof(lowercase) - 1)];  
    password[1] = uppercase[rand() % (sizeof(uppercase) - 1)];  
    password[2] = numbers[rand() % (sizeof(numbers) - 1)];      

    for (int i = 3; i < length; i++) {
        int choice = rand() % 3;
        if (choice == 0) {
            password[i] = lowercase[rand() % (sizeof(lowercase) - 1)];
        } else if (choice == 1) {
            password[i] = uppercase[rand() % (sizeof(uppercase) - 1)];
        } else {
            password[i] = numbers[rand() % (sizeof(numbers) - 1)];
        }
    }
    for (int i = 0; i < length; i++) {
        int j = rand() % length;
        char temp = password[i];
        password[i] = password[j];
        password[j] = temp;
    }

    password[length] = '\0';  
}
int robot_checker(){
    clear();
    int num1, num2, result;
    char user_answer[100];
    char operator;
    num1 = rand() % 20 + 1;
    num2 = rand() % 20 + 1;
    if (rand() % 2 == 0) {
        operator = '+';
        result = num1 + num2;
    } else {
        operator = '*';
        result = num1 * num2;
    }
    mvprintw(2,80,"What is %d %c %d? ", num1, operator, num2);
    curs_set(1);
    echo();
    getstr(user_answer);
    int number = atoi(user_answer);
    attron(COLOR_PAIR(10));
    if (number == result) {
        noecho();
        curs_set(0);
        mvprintw(19-8, 51, "                         |\\   \\        /        /|");
        mvprintw(20-8, 51, "                        /  \\  |\\__  __/|       /  \\");
        mvprintw(21-8, 51, "                       / /\\ \\ \\ _ \\/ _ /      /    \\");
        mvprintw(22-8, 51, "                      / / /\\ \\ {*}\\/{*}      /  / \\ \\");
        mvprintw(23-8, 51, "                      | | | \\ \\( (00) )     /  // |\\ \\");
        mvprintw(24-8, 51, "                      | | | |\\ \\(V\"\"V)\\    /  / | || \\|");
        mvprintw(25-8, 51, "                      | | | | \\ |^--^| \\  /  / || || ||");
        mvprintw(26-8, 51, "                     / / /  | |( WWWW__ \\/  /| || || ||");
        mvprintw(27-8, 51, "                     | | | | | |  \\______\\  / / || || ||");
        mvprintw(28-8, 51, "                     | | | / | | )|______\\ ) | / | || ||");
        mvprintw(29-8, 51, "                    / / /  / /  /______/   /| \\ \\ || ||");
        mvprintw(30-8, 51, "                   / / /  / /  /\\_____/  |/ /__\\ \\ \\ \\ \\");
        mvprintw(31-8, 51, "                   | | | / /  /\\______/    \\   \\__| \\ \\ \\");
        mvprintw(32-8, 51, "                   | | | | | |\\______ __    \\_    \\__|_| \\");
        mvprintw(33-8, 51, "                   | | ,___ /\\______ _  _     \\_       \\  |");
        mvprintw(34-8, 51, "                   | |/    /\\_____  /    \\      \\__     \\ |    /\\");
        mvprintw(35-8, 51, "                   |/ |   |\\______ |      |        \\___  \\ |__/  \\");
        mvprintw(36-8, 51, "                   v  |   |\\______ |      |            \\___/     |");
        mvprintw(37-8, 51, "                      |   |\\______ |      |                    __/");
        mvprintw(38-8, 51, "                       \\   \\________\\_    _\\               ____/");
        mvprintw(39-8, 51, "                     __/   /\\_____ __/   /   )\\_,      _____/");
        mvprintw(40-8, 51, "                    /  ___/  \\uuuu/  ___/___)    \\______/");
        mvprintw(41-8, 51, "                    VVV  V        VVV  V");
        mvprintw(43-8,68,"| THE GREAT ZYRUS INVITES YOU TO THE GAME PRESS A KEY TO CONTINUE |");
        getch();
        attroff(COLOR_PAIR(10));
        return 1;   
    }
    else
    {
        noecho();
        curs_set(0);
        mvprintw(19-8, 51, "                         |\\   \\        /        /|");
        mvprintw(20-8, 51, "                        /  \\  |\\__  __/|       /  \\");
        mvprintw(21-8, 51, "                       / /\\ \\ \\ _ \\/ _ /      /    \\");
        mvprintw(22-8, 51, "                      / / /\\ \\ {*}\\/{*}      /  / \\ \\");
        mvprintw(23-8, 51, "                      | | | \\ \\( (00) )     /  // |\\ \\");
        mvprintw(24-8, 51, "                      | | | |\\ \\(V\"\"V)\\    /  / | || \\|");
        mvprintw(25-8, 51, "                      | | | | \\ |^--^| \\  /  / || || ||");
        mvprintw(26-8, 51, "                     / / /  | |( WWWW__ \\/  /| || || ||");
        mvprintw(27-8, 51, "                     | | | | | |  \\______\\  / / || || ||");
        mvprintw(28-8, 51, "                     | | | / | | )|______\\ ) | / | || ||");
        mvprintw(29-8, 51, "                    / / /  / /  /______/   /| \\ \\ || ||");
        mvprintw(30-8, 51, "                   / / /  / /  /\\_____/  |/ /__\\ \\ \\ \\ \\");
        mvprintw(31-8, 51, "                   | | | / /  /\\______/    \\   \\__| \\ \\ \\");
        mvprintw(32-8, 51, "                   | | | | | |\\______ __    \\_    \\__|_| \\");
        mvprintw(33-8, 51, "                   | | ,___ /\\______ _  _     \\_       \\  |");
        mvprintw(34-8, 51, "                   | |/    /\\_____  /    \\      \\__     \\ |    /\\");
        mvprintw(35-8, 51, "                   |/ |   |\\______ |      |        \\___  \\ |__/  \\");
        mvprintw(36-8, 51, "                   v  |   |\\______ |      |            \\___/     |");
        mvprintw(37-8, 51, "                      |   |\\______ |      |                    __/");
        mvprintw(38-8, 51, "                       \\   \\________\\_    _\\               ____/");
        mvprintw(39-8, 51, "                     __/   /\\_____ __/   /   )\\_,      _____/");
        mvprintw(40-8, 51, "                    /  ___/  \\uuuu/  ___/___)    \\______/");
        mvprintw(41-8, 51, "                    VVV  V        VVV  V");
        mvprintw(43-8,68,"| YOU MADE THE GREAT ZYRUS ANGRY TRY AGAIN !!!! |");
        getch();
        attroff(COLOR_PAIR(10));
        return 0;   
    }
}
bool init_sdl() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}
void play_music(const char* file_path) {
    Mix_Music *music = Mix_LoadMUS(file_path);
    strcpy(current_music,file_path);
    Mix_PlayMusic(music, -1);

}
void stop_music(){
    Mix_HaltMusic();
}
bool is_music_playing() {
    return Mix_PlayingMusic() == 1 && Mix_PausedMusic() == 0;
}
void start_war(){
    clear();
    inwar=1;
    show_count = 0;
    pace=1;
    pace_counter1=0;
    pace_counter2=0;
    Player player;
    player.x = 70;
    player.y = 25;
    create_war_house();
    refresh3(&player);  
    while (1) {
        int t = move_player(&player);
        if(t==1){
            break;
        }
    }
}
void refresh3(Player *player){
    draw_player(player);
    draw_war_house();
    attron(COLOR_PAIR(10));
    mvprintw(0,77,"ZYRUS is watching you :)");
    attroff(COLOR_PAIR(10));
    mvprintw(LINES-2,2,"                              ");
    mvprintw(LINES-2,20,"                              ");
    mvprintw(LINES-3,62,"                                         ");
    draw_bar(LINES-2, 62, 20, p_user.health, 10000, "Health");
    draw_bar(LINES-3, 62, 20, p_user.hunger, 100, "Power");
    attron(COLOR_PAIR(1));
    mvprintw(LINES-2,14,"Score : %d",p_user.score);
    mvprintw(LINES-2,2,"Gold : %d",p_user.gold);
    mvprintw(LINES-2,26,"Kills : %d",p_user.kills1);
    attroff(COLOR_PAIR(1));
    mvprintw(LINES-6,2,"                              ");
    //attron(COLOR_PAIR(7));
    pace_counter2=0;
    //attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(10));
    switch(p_user.current_weapon){
        case 'm':
            mvprintw(LINES-6,2,"current weapon : MACE");
        break;
        case 'd':
            mvprintw(LINES-6,2,"current weapon : DAGGER %d",p_user.weapon_bar.dagger);
        break;
        case 'w':
            mvprintw(LINES-6,2,"current weapon : MAGIC WAND %d",p_user.weapon_bar.magic_wand);
        break;
        case 'a':
            mvprintw(LINES-6,2,"current weapon : ARROWS %d",p_user.weapon_bar.arrow);
        break;
        case 's':
            mvprintw(LINES-6,2,"current weapon : SWORD");
        break;
    }
    attroff(COLOR_PAIR(10));
    attron(COLOR_PAIR(6));
        mvprintw(LINES-5,2,"Health spell : %d",p_user.spell_bar.H);
        mvprintw(LINES-4,2,"Speed  spell : %d",p_user.spell_bar.S);
        mvprintw(LINES-3,2,"Power  spell : %d",p_user.spell_bar.G);
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(9));
        mvprintw(LINES-5,20,"Normal food : %d",p_user.food_bar.normal);
        mvprintw(LINES-4,20,"Speedy food : %d",p_user.food_bar.speed);
        mvprintw(LINES-3,20,"Supreme  food : %d",p_user.food_bar.special);
    attroff(COLOR_PAIR(9));
    refresh();  
}
int create_war_house(){
    memset(war_house,' ',sizeof(war_house));
    for (int i = 5; i < 35; i++) {
        war_house[i][45]='|';
        war_house[i][130]='|';
    }
    for (int i = 45; i <= 130; i++) {
        war_house[5][i]='-';
        war_house[35][i]='-';
    }
    for (int i = 6; i <= 34; i++) {
        for (int j = 46; j <130; j++) {
            war_house[i][j]='.';
        }
    }
    for (int i = 0; i < 3; i++) {
        int y = rand() % 29 + 6;  
        int x = rand() % 83 + 46;
        enemies_war[i] = create_random_enemy(y, x);
        war_house[y][x]=enemies_war[i].face;
    }
}
void draw_war_house(){
    for(int i=0; i<MAP_HEIGHT ;i++){
        for(int j=0 ; j<MAP_WIDTH ;j++){
            if(war_house[i][j]=='|'||war_house[i][j]=='-'){
                attron(COLOR_PAIR(1));
                mvaddch(i,j,war_house[i][j]);
                attroff(COLOR_PAIR(1));
            }
            else if(war_house[i][j]=='G'||war_house[i][j]=='S'||war_house[i][j]=='F'||war_house[i][j]=='U'||war_house[i][j]=='D'){
                attron(COLOR_PAIR(2));
                mvaddch(i,j,war_house[i][j]);
                attroff(COLOR_PAIR(2));
            }
            else{
                mvaddch(i,j,war_house[i][j]);
            }
        }
    }
}
void guide(){
    clear();
    int starty = 1, startx = 1;
    int height = LINES -3, width = COLS -3;
    attron(COLOR_PAIR(9));
    mvprintw(starty + 1, startx + 2, "Kinds of foods :");
    mvprintw(starty + 2, startx + 2, "Normal  food(%%) : +10 power | Speedy  food(V) : +10 power and fast move on! | Supreme food(X) : +50 power");
    attroff(COLOR_PAIR(9));
    attron(COLOR_PAIR(6));
    mvprintw(starty + 4, startx + 2, "Kinds of spells :");
    mvprintw(starty + 5, startx + 2, "Health spell(H) : x2 foods' power | Speed spell(R) : fast move on! | Power spell(8) x2 weapons' damage");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(8));
    mvprintw(starty + 7, startx + 2, "Kinds of golds :");
    mvprintw(starty + 8, startx + 2, "Golden gold(T) +5 gold number | Black gold(Z) +50 gold number");
    attroff(COLOR_PAIR(8));
    attron(COLOR_PAIR(10));
    mvprintw(starty + 10, startx + 2, "Kinds of weapons :");
    mvprintw(starty + 11, startx + 2, "Mace : damage{5},range{short} | Sword : damage{10},range{short} | Magic wand : damage{15},range{10} | Arrows : damage{5},range{5} | Daggers : damage{12},range{5}");
    attroff(COLOR_PAIR(10));
    attron(COLOR_PAIR(7));
    mvprintw(starty + 13, startx + 2, "Map details :");
    mvprintw(starty + 14, startx + 2, "stair(<) | door(+) | locked door(@) | pillar(o) | corridor(#) | Golden door(A)");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(2));
    mvprintw(starty + 16, startx + 2, "Enemies :");
    mvprintw(starty + 17, startx + 2, "Snake(S) : damage{15} | Deamon(D) damage{5} | Fire Breathing Monster damage{10} | Giant damage{15} | Undeed damage{30}");
    attroff(COLOR_PAIR(2));
    mvaddch(starty, startx, '+');
    mvaddch(starty, startx + width, '+');
    mvaddch(starty + height, startx, '+');
    mvaddch(starty + height, startx + width, '+');

    for (int i = starty + 1; i < starty + height; i++) {
        mvaddch(i, startx, '|');
        mvaddch(i, startx + width, '|');
    }

    for (int i = startx + 1; i < startx + width; i++) {
        mvaddch(starty, i, '-');
        mvaddch(starty + height, i, '-');
    }
    refresh();
    getch();
}