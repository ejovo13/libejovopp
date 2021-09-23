#ifndef BATTLESHIP_CLI
#define BATTLESHIP_CLI

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "battleship_board.h"

// sleep for __s seconds
void dsleep(double __s) {

    usleep(1E6 * __s);

}

int index_letters(char c) {

    int index = -1;

    for(int i = 0; i < 10; i ++) {
        if (LETTERS[i] == c) {
            return i;
        }
    }

    return index;

}

uint32_t input_row_index() {
// Get row selection from the human player

    bool is_valid_input = false;

    // printf("Please enter the letter of the row to select\n");

    int index;

    while(!is_valid_input) {

        char c = '0';
        int ret = scanf("%c", &c);

        if (ret != 1) {
            printf("input not recognized, please enter a valid character\n");
            continue;
        }

        if (c == '\n' || c == ' ') {
            continue;
        }

        // printf("Input as char = %c, input as decimal = %d\n", c, c);

        index = index_letters(c);

        if (index == -1) { // Then the input value is NOT in letters
            printf("%c not contained in [A-I], please enter a character in [A-I]\n", c);
            fflush(stdin);
            fflush(stdout);
            continue;
        } else {
            is_valid_input = true;
            break;
        }
    }

    return index;
}

uint32_t input_col_index() {
// get column index from the human player

    bool is_valid_input = false;

    // printf("Please enter the number of the col to select\n");

    int d = 0;

    while(!is_valid_input) {

        int ret = scanf("%d", &d);

        if (ret != 1) {
            printf("input not recognized, please enter a valid integer\n");
            continue;
        }

        if (d < 1 || d > 10) { // Then the input value is NOT in [1-10]
            printf("%d not contained in [1-10], please enter an integer in [1-10]\n", d);
            continue;
        } else {
            is_valid_input = true;
            break;
        }
    }

    return d - 1;
}

void player_turn(DockingStation * ds) {
// Prompt the user for a location in the form of 'A8' and process that information

    uint32_t i = 0;
    uint32_t j = 0;
    uint8_t value = 0;
    bool turn_over = false;

    while(!turn_over) {
        // get guess
        i = input_row_index();
        j = input_col_index();
        value = ds->board[i*10 + j];

        if ( is_attempted(value) ) {
            printf("You already tried this location, try again\n");
            continue;
        } else if ( is_occupied(value) ) { // We got a hit!!!

            printf("Hit. ");
            ds->board[i*10 + j] += (HIT + ATTEMPTED);

            if ( is_carrier(value) ) {
                ds->carrier_lives_left --;

                if ( ds->carrier_lives_left == 0 ) {
                    printf("You've sunk my carrier!!!\n");
                } else {
                    printf("Carrier\n");
                }
            } else if ( is_battleship(value) ) {
                ds->battleship_lives_left --;

                if ( ds->battleship_lives_left == 0 ) {
                    printf("You've sunk my battleship!!!\n");
                } else {
                    printf("Battleship\n");
                }
            } else if ( is_cruiser(value) ) {
                ds->cruiser_lives_left --;

                if ( ds->cruiser_lives_left == 0 ) {
                    printf("You've sunk my cruiser!!!\n");
                } else {
                    printf("Cruiser\n");
                }
            } else if ( is_submarine(value) ) {
                ds->submarine_lives_left --;

                if ( ds->submarine_lives_left == 0 ) {
                    printf("You've sunk my submarine!!!\n");
                } else {
                    printf("Submarine\n");
                }
            } else if ( is_destroyer(value) ) {
                ds->destroyer_lives_left --;

                if ( ds->destroyer_lives_left == 0 ) {
                    printf("You've sunk my destroyer!!!\n");
                } else {
                    printf("Destroyer\n");
                }
            }

        } else { // Then we missed!

            printf("Miss!\n");
            ds->board[i*10 + j] += (MISS + ATTEMPTED);

        }

        turn_over = true;
    }
}

int input_valid_directions(char * valid_directions, int num_valid_directions) {
// get a direction as input from the user and make sure that it appears in the list of valid_directions

    // printf("ENTERED INPUT VALID DIRECTIONS\n");

    char input_char = '0';

    printf("Please choose a direction!!\n");

    fflush(stdin);
    int scanf_ret = scanf("\n%c", &input_char); // ASK ABOUT THIS

    // validate scanf ret
    for (int i = 0; i < num_valid_directions; i ++) {
        if ( input_char == valid_directions[i] ) {
            return i;
        }
    }

    if ( input_char == 'X' ) {
        printf("Cancel placement\n");
        return -1;
    }
}

char * get_valid_directions(uint8_t * board, int irow, int jcol, int ship_length, int * num_valid_directions) {
// implement this please
// When given the size of a ship, and an index irow, jcol, and the address of a var to store the number
// of valid directions, return a character pointer that contains the valid directions



    *num_valid_directions = 0;
    bool valid_directions_long[4] = {false};
    char dummy = 'c';

    // printf("ENTERED GET_VALID_DIRECTIONS...\n");

    // get the number of valid directions
    for(int i = 0; i < 4; i ++) {

        // printf("VALIDATING_PLACEMENT of: %c \n", DIRECTIONS[i]);

        if ( validate_placement(irow, jcol, DIRECTIONS[i], board, ship_length) ) {

            // printf("DIRECTION %c is valid!\n", DIRECTIONS[i]);
            (*num_valid_directions) ++;
            valid_directions_long[i] = true;

        }
    }

    // printf("Validated all directions!!\n");
    // printf("Num valid directions: %d\n", *num_valid_directions);

    // malloc the characters
    char * valid_directions = (char*) malloc( sizeof(dummy) * (*num_valid_directions) ); // allocate 'num_valid_directions' characters
    // if (valid_directions) {
        // printf("valid_directions initialized correctly?\n");
    // }

    int j_valid_direction = 0; // index of valid direction to input
    for(int i = 0; i < 4; i ++) {

        // printf("valid_directions_long[%d]: %d\n", i, valid_directions_long[i]);

        if ( valid_directions_long[i] ) {

            // printf("Storing direction: %c\n", DIRECTIONS[i]);
            valid_directions[j_valid_direction] = DIRECTIONS[i];
            j_valid_direction ++;
        }
    }

    // printf("Finished fetching valid directions!!\n");

    // printf("Address of valid_directions: %x\n", valid_directions);

    // printf("Character at valid_directions[0] = %c\n", valid_directions[0]);
    // printf("Character at valid_directions[1] = %c\n", valid_directions[1]);

    return valid_directions;
}

void get_player_placement(DockingStation * ds) {
// Receive and validate player placement of all 5 ships

    printf("Please select where you would like to place your ships!\n");

    uint32_t irow = 0;
    uint32_t jcol = 0;

    char * valid_directions;
    int num_valid_directions = 0;
    char direction_selected;
    // int dir_selected_int;

    for (int i = 0; i < NUM_SHIPS; i ++) {

        num_valid_directions = 0;
        print_full_board(ds->board);
        printf("Selecting ship type: %s\n", SHIP_FULL_NAMES[i]);


        while(num_valid_directions == 0) {

            irow = input_row_index();
            jcol = input_col_index();
            valid_directions = get_valid_directions(ds->board, irow, jcol, SHIP_LENGTHS[i], &num_valid_directions);

            if ( num_valid_directions == 0 ) {
                fflush(stdout);
                printf("Invalid placement, please choose another position\n");
                continue;
            }

        }

        // get_valid_directions(ds->board, irow, jcol, SHIP_LENGTHS[i], &num_valid_directions);

        printf("Valid directions: ");

        for (int j = 0; j < num_valid_directions; j ++) {

            printf("'%c' ", valid_directions[j]);

        }

        printf("\n");


        // dir_selected_int = input_valid_directions(valid_directions, num_valid_directions);
        direction_selected = valid_directions[ input_valid_directions(valid_directions, num_valid_directions) ];
        place_ship(irow, jcol, direction_selected, ds->board, SHIP_TYPES[i], SHIP_LENGTHS[i]);
        printf("Directions selected: %c\n", direction_selected);


    }
}

void enemy_turn() {

    printf("Waiting for enemy");

    // for (int i = 0; i < 5; i ++) {
    //     printf(".");
    //     dsleep(0.5);
    // }

    printf("\n");


}

bool is_game_over(DockingStation ds) {

    return (ds.carrier_lives_left == 0 && ds.battleship_lives_left == 0 && ds.cruiser_lives_left == 0 &&
            ds.submarine_lives_left == 0 && ds.destroyer_lives_left == 0);
}

void step(DockingStation * ds) {

    print_full_board(ds->board);
    printf("Please make a selection: ");
    player_turn(ds);
    enemy_turn();

}

void play_game(DockingStation * ds) {

    printf("WELCOME TO THE GAME \n\n");

    // print_full_board(ds->board);

    get_player_placement(ds);

    while ( !is_game_over(*ds) ) {

        step(ds);

    }

}



#endif

