# Connect4-Programming1
Connect-4 Report
Asser Osama Elsayed Hassan Elsayed Elzeki 21010241
Mohamed Tarek Hussien Hassan Ibrahim 21011161

#	Description:
Our game is a connect 4 game which will end when the board is full and then the player with more connected fours will win (or tie will take place).
First, the main game parameters are the boards height, width and highscores list size which the program will read from an xml file and check for its validity, if the xml file is invalid we will ask for another path for 3 times then our program will load the default values.
Then the main menu will appear and the user can choose between : 1.easy single player game,2.hard single playe,3.multiplayer game,4.load a previous game (if any),5.show leaderboard,6.exit .
For the playing mode the player is called initially player 1 and the computer(or the other player) as player 2 , player 1 will play with symbol ‘X’ in red and player 2 will play with symbol ‘o’ ,If we are in a multiplayer mode the program will ask for the user input in each round to ask for the column to be played in or another sub-menu option , but in the single player mode our program will ask only for the player 1 input but the computer will play its round in a valid random column .
Our program’s in_game UI is so simple to understand and contains all the info that a user may need  like :the score and moves for each player colored with that player color(red for player 1 and yellow for player 2),time passed since the start of the game (if the game is loaded time will continue on the last play when the game was saved) and the in game menu which is: -1 for undo,-2 for redo , -3 to save ,-4 to quit to main menu ,0 to quit the game and -5 to show best move (in easy mode only). When a human player wins our program will ask for the players name and shows the leaderboard.
For the load menu our game supports up to 3 slots if you save a game for the first slot the the game in slot 1 will go to slot 2 and the game in slot2 will go to slot 3 and the game in slot 3 will be erased. If you save multiple time in the same game it will be saved in the same slot where it has been saved (either the game is loaded or not).
For the high scores leader board our program supports up to 100 -(assumption but we can increase it)- players, you show from them X players where X is the parameter of high scores size read from configurations file, the board shows the X top players with their names and scores next to them where the names are case insensitive and we save only the highest score for each player.
#	Features
The features of our connect four game are:
1-you can choose the dimentions and the number of displayed highscores as you want but becareful there are restrictions!!
2-you can play single player and you can chose between two levels easy and hard.
3-you can play multiplayer with your friends.
4-you can save up to 3 different games to load them whenever you want.
5-you can display the highscores recorded for the game and also it is automaticallydisplayed at the end of every game
#	Design Overview
Our game flow goes from trying to load game parameters from a configuration file and  if it fails in all trials, default values will be loaded. Then the main menu appears to select the game mode or loading a game or showing leaderboard or quitting, in the game we will show the board and the main info like scores, moves, current round, time and sub_menu which include undo, redo, save, quit to main menu or quit the game or show the best move, Loading a game will ask you to choose which slot to load if any, leader board appear after each game and when it is chosen from the main menu.
Our program design is separated in 3 independent header files and the main , the three headers are : gameloop.h , XMLConfig.h and HighScores.h , we use three main typdef structs player_t, game_t and config_t . these wil be explained in detail in the Description of the important functions/modules section.
#	Assumptions 
1.	We assumed that the maximum High Scores size, Width and Height is 100(it is defined as constant but we can increase it in the code)
2.	We assumed that the maximum number of character in the configuration file is 2048 about 1 kilobyte (but it can be increased)
3.	We assumed that the winner player will enter his username which must be composed of one word only of size less than 10 and doesn’t contain any spaces because any character after the space will be neglected .If it’s larger a warning message will appear and the player entered more than one word we will neglect that word
4.	We assume to neglect any whitespaces or new line in the configuration file and neglect any irrelevant text not included in the height or width or high scores tags
5.	Game board is 1 based matrix and actions,topscores,saves array are the same.
6.	Name in the leaderboard will be showed by the case of the first log in.
#	Data Structures
We used a bunch of arrays and structures like:
Arrays : 
1.	topsscores array which is of type player_t of size 100 and stores players’ structs’ objects which include their names and scores.
2.	 saves array which is of type game_t and stores the saved games’ structs’ objects that includes the board, current round,  width, height, time in hours, minutes and seconds and the game mode(single or multi).
3.	Actions array defined in gameloop function to store the game moves  for the undo and redo functionality. It’s of type int to store the played columns throughout the game.
Matrices:
1.	Board matrix which is updated with player moves , it’s of type int and stores three numbers either 1 for player 1 or 2 player 2 or 0 for a free cell .
Structures:
1.	game_t : it stores the game board, height, width, current round, mode and time, it’s mainly used to save the current game info to be stored in the saves array and then written in the save.bin .
2.	player_t : it stores the winners name and score, it’s mainly used for saving data in leaderboard.
3.	config_t : it stores the Height , width and high scores size to be used easily throughout the program.
#	Description of the important functions/modules:
In main.c : we include here all the other header files there is only one function here which is :
Void main_menu((game_t* saves,player_t* topscores)) : it takes the saves and topscores arrays as parameters and shows the main menu which is considered the main navigator in our program which can either print the leaderboard or call the gameloop function with the suitable parameters for each mode (single(easy or hard) or multi , new or loaded)

in gameloop.h : it’s an independent header which contains the main functionality for saving and loading , calculating scores , printing the board , time calculation , random selection and 3 validation functions(for the player name , board check and user input check) playing functions like : play(), undo() and redo() .
It includes game_t struct definition.
Some of the important functions here:
void timecalculate(int hours_i,int minutes_i,int seconds_i) : it prints the current time given the initial game time which is 0,0,0 for a new game and other values for a loaded game and also access the start time variable which stores the the time at which the program started.
void update_save(game_t* saves,game_t game,int load_number,int saved_now): it applies the saving logic of shifting game slots in case of a new game or saving in the same slot in case of a saved or loaded game ,it changes the saves array only without writing to or reading from the binary file.
void write_save(game_t* saves) / void read_save(game_t* saves) : thes are the function that opens the saves.bin to write the updated saves array in it or to read the array from the file, the read_saves() also states how many loaded games are there in the file.
int score(int h,int w,int* board[h],int player) : It is the function that calculates the scores in the board for a specific player in all direction (vertical , horizontal , ascending diagonal , descending diagonal ) using for loops
int random_col_selection(int y) : it return a random column between 1 and y which is the board’s width
bool checkvalid(int x,int y,int* connect[y],int col,int mode) : it check if the selected column is valid and prints a warning message for wrong columns for human players only and just returns false if the computer chose a wring column.
int integercheck() : it is the function that asks the player to input the column number or sub menu option and validates that input restrictly and prints the suitable warning message.
void print_board(int h,int w,int* board[h]) : the function that prints the board of integers and display it in a ‘X’ and ‘o’ colored way.
void play(int*actions,int col,int h,int w,int* board[h],int playern,int* curr_round,int* max_round) : it’s the play function called for any player either human or computer it plays the chip in the specified validated column and updates the actions array , increments current round and max_round variables
void undo(int col,int h,int w,int* board[h],int playern,int* curr_round,int max_round) : it removes the last play and decrements the current_round and prints a warning message if the user can’t undo
void redo(int col,int h,int w,int* board[h],int playern,int* curr_round,int max_round) : it plays the next saved play in actions and increments the current_round and prints a warning message if the user can’t redo if the current_round will exceed max_round.
int med_comp_move(int h,int w,int* board[h]) : it’s an advancement in the computer turn action as it calculates the best move by looking first for the play that will increase both the comp score and human score, then it would look for will increase either the comp score or human score or just play random.
int calc_row(int col,int h,int w,int* board[h]) : it calculates the upmost free row.


void game_loop(int h,int w,int mode,int Load_number,game_t* saves) : It‘s the main function in this headers which is called in the main.c file, it perform the game loop logic, it defines a game_t object called game which will be used in case of saving the game and be sent to saves array, it intializes the board and actions arrays with zeros , checks for the game  loading whether to initialize all the variable to the default ones in case of new game or loaded values in case of a loaded game , starts the game while loop, checks for the game mode (single or multi) to call the suitable function for asking for the column(random_col_selection() or Integercheck() or med_comp_move())  , it prints the game info like scores ,moves ,time and current round , it shows also the in game menu for undo , redo , save , quit to main menu, show the best move (in easy mode) or quit the game and when the game ends it asks the winner for their name and validates it then it stores the player’s name and score to be processed in the HighScores logic in main.c , It will show also if you lost the game or if the game ended up as a tie.
In HighScores.h:  
We define here the player_t struct that stores the winner player’s name and score and some other important functions
void InsertionSort(player_t* arr) : it’s a normal insertion sort function but an array of player_t type , it sorts this array according to the players’ scores.
** we preferred to use the insertion sort rather than merge sort because this array will always be very near to the best case (almost sorted) and the number of players will not be too large anyway
int check_names_similarity(char* name1,char*name2) : it check if the two names are the same neglecting case sensitivity which is useful to know if the incoming name is already saved or not.
void update_highscores(char* name,int score,player_t* arr) : it updates the topscores array without opening any files but only puts the new player in the first place in the array topscores[0] if its score is higher than the player in this place (if there was a player there) and if the player already exists it will just update its high score and then sorts the array by calling the InsertionSort function
void print_highscores(player_t* topscores,int n) : it prints the topscores array form the end to the start (to show the top players first) 
void read_highscores(player_t* topscores)/ void write_highscores(player_t* topscores) : these are the functions that open the HighScores file to save the topscores in it or read it form the file or to create the file if it isn’t there
XMLConfig.h
In this header we perform the logic of xml validation logic , Here we define the config_t struct that stores  the height , width and high scores size of the game and declare my_config object which will be used in the main function and here the headers functions
int convert_int(char* s,int len):  it converts the string and checks if it represent a number and return 0 a warning message if the string doesn’t represent an integer or if the integer’s value is too big ,else it returns the integer value.
int getVal(char*s,char*s1,char*s2): it searches for the two words s1 and s2 (which will be height , width , highscore tags) and returns if the text between them represent a number or not using the conver_int function and prints a meaningful error message.
int ValidateXML(char*s) : it searches for the configuration tags in the xml text and takes the text between the two tags and send it to the get_val function 3 times (one for each of the Height, Width, Highscores) and if one of these 3 values is wrong or undefined it returns 0 and prints a warning message but if the values are correct the it it will assign it to  my_config and returns 1.
void Load_Config() : it’s the function called in the main.c , it initializes the my_config parameters with the default values then tries to open the default config.xml to read the game parameters , if it failed to find it or the data inside it is invalid then it will the user to type a correct path to a valid configurations file 3 times then if it failed in the 3 times to load the data it will terminate with the default values as they are.
#	User manual:
First : Reading configurations: 
1.White space and any irrelevant text outside the tags of Height ,Width or High Scores will never affect the reading behavior.
2.If  you receive a warning message then you may have entered an invalid path or non integer value for one of the game parameters or you may have mistaken the tags opening and closing  or the values are too big eg. value>100.
3. Take care of the spelling of <Configuration> , <Height>, <Width>, <HighScores> and they must be written in the same case like that.
4.If your input files failed 3 times the default values will be loaded Height=9,Width=7,HighScores =10.
5.Don’t worry most of the error message are meaningful and will guide you to the error place.
Second : Main menu:
1.	The UI here is so simple just choose the action you want (1 for easy mode,2 for hard mode, 3. For multiplayer,4.to load a game,5.to display high scores 6. To quit)
2.	If you mistaken the input a meaningful warning message will appear
Third : Display High Scores
1.	The first X winners will appear with their scores sorted (X is the HighScores parameter passed from xml).
2.	The program will create automatically the HighScores.bin but if you like to import an external one make sure that it’s made by our program(either the same copy or a different one) and the high scores games will be displayed normally
3.	In case you added an external corrupted binary file then unexpected scores will appear but DO NOT WORRY THE PROGRAM WILL NOT CRASH but you have to remove the corrupted file from the directory to make the leaderboard functionality return.  
Fourth : Load Games
1.	The loaded games will appear (<=3) choose the game you want to continue and it will load with its loaded parameters whatever the program parameters are and with all the old data loaded like score, time and current round.
2.	The program will create automatically the save.bin but if you like to import an external one make sure that it’s made by our program(either the same copy or a different one) and the loaded games will be displayed.
3.	In case you added an external corrupted binary file then  DO NOT WORRY THE PROGRAM WILL NOT CRASH but you have to remove the corrupted file from the directory to make the loading functionality return because it may add a garbage slot.
Fifth : Multiplayer 
1.	In each round it will be displayed whose turn is the current turn and all the data like the scores, moves, time, current round and in game menu.
2.	You will be asked for your input whether it should be a valid column or a in game menu option, otherwise, a meaningful warning message will appear and we will ask for your input again
3.	The winner will be asked for their name and then the leaderboard will be printed
Sixth : Single 
1.	In each all the data like the scores, moves, time, current round and in game menu and showing best move in easy mode only.
2.	You will be asked for your name only if you wins.
Seventh : in game menu
1.	It ‘s a very simple menu you can type -1 to undo ,-2 to redo , -3 to save , -4 to quit to main menu , 0 to exit and -5 to show best move in easy single mode only.
2.	All your inputs are validated.
Eighth : Validations
All inputs are validated in the main and in game menu , path , name, and columns so DO NOT WORRY if you mistaken an input the program will not crash
