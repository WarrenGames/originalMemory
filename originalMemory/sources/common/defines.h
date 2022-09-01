#ifndef H_DEFINES
#define H_DEFINES

#define SCREENW 1080
#define SCREENH 740

#define ARIAL_FONT_PATH "fonts/arial.ttf"

enum{RECTO, VERSO};
enum{ENLARGE, SHRINK};

#define SQUARE_SIZE 64

#define MARGIN 64
#define INTERSTICECARDS 4
#define CARDSBYROW 14

enum{ EASY_SKILL, MEDIUM_SKILL, HARD_SKILL, SKILL_MAX };
#define EASY_PAIR_NUMBER 21 // * 2 = 42  = 3 * 14
#define MEDIUM_PAIR_NUMBER 42  //* 2 =  84 = 6 * 14
#define HARD_PAIR_NUMBER 63 // * 2 = 126 = 9 * 14

//To know how to display a card (back side, image side, or not displaying at all)
enum{CARD_HIDDEN, CARD_REVEAL, CARD_PAIRFOUND};

//the current step
enum{WAIT_CARD1_CHOICE, WAIT_CARD2_CHOICE, TEST_IF_CARDS_TWINS, GAME_WON};

//Is it the chsoen card 1 or the second
enum{CARD1 , CARD2};

//to know which hint text to display
enum{WHAT_A_PITY, WELL_DONE, GAME_FINISHED, PUSH_SPACE, DISPLAY_MAX};

#endif // H_DEFINES
