#include <iostream>
#include <ctime>
#include <string>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;

//Preloaded function
void startGameLoop();
void clearInput();
void bet();
void pickNumberColor();
void roulettePlay(const short &playerValue, short factor);
void roulettePlay(const string &playerValue, short factor);
string blackOrRed(short value);

// A player struct to keep the values centered and organized everything regarding the player.
struct Player {
    short player_money{1000}; // initialization money
    short player_current_pricemoney{0}; // the money the player wins
    short player_bet{0}; // what player bet
};
// instance variables
bool gameLoop{true};
Player player;

// The Main function that starts the program. Calling the startGameLoop function to start the whole application.
int main() {
    startGameLoop();
    return 0;
}

/* Start the main infinite gaming loop where player can chose if he want to play or quit the application.
 * If player chose to quit he have to accept that he wants to quit by pressing y/Y.
 * Using a bool for the gameLoop that will be set to false which cancel the infinite loop if player press y.
 * Also using a input security loop for protect against bad inputs. calls a clearInput function.
 * If the player chose playing the next function "bet()" will be called. To place the bets.
 * But must have at least 100 sek otherwise he will not be allowed to play. */
void startGameLoop() {
    srand(time(nullptr)); // init current time as seed everytime the application is restarted.
    short choice;
    cout << "Hello Player!\nAnd welcome to this game of classic Roulette.\n"
            "As a present you will get 1000 sek to play for, now go and win some money!" << endl;
    /* infinite gameLoop and prints out a menu for the player
    Shows the total amount of money and current wins/losses*/
    while (gameLoop) {
        cout << "\n********** MAIN MENU ********\n";
        cout << "Current Money: " << player.player_money << endl;
        cout << "Money Win: " << player.player_current_pricemoney << endl;
        cout << "*****************************\n";
        cout << "1. Play a game\n";
        cout << "2. Quit application" << endl;
        cout << ">>";
        cin >> choice;
        //Input security loop. Switch case for handling menu inputs
        while (cin.fail()) {
            clearInput();
            cin >> choice;
        }
        switch (choice) {
            case 1:
                // checks if the player has more money then or equal to 100, or denies the player to play.
                if (player.player_money >= 100) {
                    bet();
                } else {
                    cout << "You don't have enough money to play, come back another day" << endl;
                }
                break;
            case 2:
                // player inputs if he wants to quit or not, if yes the gameLoop are set to false and breaks the application loop
                char confirm;
                cout << "OK, Do you want to close the application? (y/n)" << endl;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    cout << "Welcome back and play again!" << endl;
                    gameLoop = false;
                }
                break;
            default:
                cout << "Please enter a number from the menu." << endl;
                break;
        }
    }
    // Make so the console don´t directly closes.
    cout << "Press enter to close application!" << endl;
    cin.get();
    cin.get();
}

/* Most of this function to the same as before displaying a menu and players current money/wins.
Other changes explained in the code. */
void bet() {
    short choice;
    cout << "\n********** BETTING **********\n";
    cout << "Current Money: " << player.player_money << endl;
    cout << "Money Win: " << player.player_current_pricemoney << endl;
    cout << "*****************************\n";
    cout << "1. 100 sek\n";
    cout << "2. 300 sek\n";
    cout << "3. 500 sek" << endl;
    cout << ">>";
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 3) {
        clearInput();
        cin >> choice;
    }
    switch (choice) {
        case 1:
            //set the betting to 100 and calls next function
            player.player_bet = 100;
            pickNumberColor();
            break;
        case 2:
            /* checks if the player has more money then or equal to 300.
                set the betting to 300 and call next function
                or denies the player to play and make him pick a lower value*/
            if ((player.player_money - 300) >= 0) {
                player.player_bet = 300;
                pickNumberColor();
            } else {
                cout << "You don't have enough money to play this bet, come back another day or pick a lower." << endl;
            }
            break;
        case 3:
            /*  checks if the player has more money then or equal to 500.
                set the betting to 500 and call next function
                or denies the player to play and make him pick a lower value */
            if ((player.player_money - 500) >= 0) {
                player.player_bet = 500;
                pickNumberColor();
            } else {
                cout << "You don't have enough money to play this bet, come back another day or pick a lower." << endl;
            }
            break;
        default:
            cout << "Should not happened!" << endl;
            break;
    }
}

/* Most of this function to the same as before displaying a menu and players current money/wins.
Other changes explained in the code. */
void pickNumberColor() {
    short choice;
    short value{0};
    cout << "\n********** Chose ***********" << endl;
    cout << "Current Money: " << player.player_money << endl;
    cout << "Money Win: " << player.player_current_pricemoney << endl;
    cout << "*****************************" << endl;;
    cout << "1. Bet on a Number\n";
    cout << "2. Bet on a Color" << endl;
    cout << ">>";
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 2) {
        clearInput();
        cin >> choice;
    }
    switch (choice) {
        case 1:
            /* Here the player inputs a integer number between 1 and 36. If it's outside this range he need to input it again.
             Then sends the number player picked and a multiplication factor for the price money if the answer is correct. */
            cout << "Enter a integer number between 1 and 36." << endl;
            cin >> value;
            while (cin.fail() || value > 36 || value < 1) {
                choice = 0;
                clearInput();
                cin >> value;
            }
            roulettePlay(value, 10);
            break;
        case 2:
            /*player makes a choice if he want to bet on red or black.
            the color will then be sent as a parameter with the factor to and overloaded function of roulettePlay*/
            short player_color_value;
            cout << "1. Bet on a Red\n";
            cout << "2. Bet on a Black" << endl;
            cout << ">>";
            cin >> player_color_value;
            while (cin.fail() || player_color_value > 2 || player_color_value < 1) {
                clearInput();
                cin >> player_color_value;
            }
            switch (player_color_value) {
                case 1:
                    roulettePlay("Red", 2);
                    break;
                case 2:
                    roulettePlay("Black", 2);
                    break;
            }
            break;
        default:
            cout << "Please enter a number from the menu." << endl;
            break;
    }
}

/* playerValue is made of pass by reference ans const because the value is not going to change.
but will not sent to pass by copy to create unnecessary copying. Same is done in the overloaded function. */
void roulettePlay(const short &playerValue, short factor) {
    cout << "Rolling wheel!" << endl;
    /*Randomize a number between 1-36 and save it in a variable.
    To get the color the function blackOrRed will be called. It will take the randomNumber as parameter,
    It will pass this as a "pass by value". Do a modules calculation to see if it even or odd and then return the color.*/
    int randomNumber = (rand() % 36) + 1;
    string color = blackOrRed(randomNumber);
    cout << "Wheel stops at: " << color << " " << randomNumber << ", You bet on: " << playerValue << endl;
    /* checks if the players number value is equal the wheels number.
    If it is true it will add this to the players price money and total amount.
    will also display how much he won. If he fails it will remove money from the player and display he lost. */
    if (playerValue == randomNumber) {
        short result = player.player_bet * factor;
        player.player_current_pricemoney += result;
        player.player_money += result;
        cout << "You won " << result << "!" << endl;
    } else {
        player.player_money -= player.player_bet;
        player.player_current_pricemoney -= player.player_bet;
        cout << "You lose!" << endl;
    }
    cout << "Play again?" << endl;
    /*From here everything will end in the first loop and will return to the "MAIN MENU"
    If the player want to play again or quit the game.*/
}

/*Overloaded function that takes a string instead of a short,
and is that it compare colors instead of a number in the if statement*/
void roulettePlay(const string &playerValue, short factor) {
    cout << "Rolling wheel!" << endl;
    int randomNumber = (rand() % 36) + 1;
    string color = blackOrRed(randomNumber);
    cout << "Wheel stops at: " << color << " " << randomNumber << ", You bet on: " << playerValue << endl;
    // compare players color choice is the same as the wheels
    if (playerValue == color) {
        short result = player.player_bet * factor;
        player.player_current_pricemoney += result;
        player.player_money += result;
        cout << "You won " << result << "!" << endl;
    } else {
        player.player_money -= player.player_bet;
        player.player_current_pricemoney -= player.player_bet;
        cout << "You lose!" << endl;
    }
    cout << "Play again?" << endl;
}

/*Does a modulus operation to get if a value is even or odd and then return a string value.
 If even = Black and odd = red*/
string blackOrRed(short value) {
    if (value % 2 == 0) {
        return "Black";
    } else {
        return "Red";
    }
}

// Clears a wrong input from the user, With cin.clear the clears fail flag. Other one discard rest of the input
void clearInput() {
    cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input, please enter your choice again.\n";
}
