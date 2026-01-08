#include <bits/stdc++.h>
using namespace std;

class Game{

private:
    int score;
    vector<vector<int>> board;

    mt19937 gen; // mersenne twister engine for random number generation
    uniform_int_distribution<> idx; // random number(between 0 and 3 inclusive) for rows and columns
    uniform_int_distribution<> prob; // random number(between 0 and 9 inclusive) for spawning logic(whether to spawn a '4' or a '2')

public:
    Game():
        gen(random_device{}()), idx(0, 3), prob(0, 9) // seed the generator engine with a hardware seed
        {
            score = 0;
            board = vector<vector<int>>(4, vector<int>(4, 0));
            randSpawn(); randSpawn(); // the rules of the game suggest spawning two random numbers at first
        }

    bool hasGameEnded(){

        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(board[i][j] == 0){
                    return false;
                }
            }
        }

        for(int i=0; i<4; i++){ // iterate to check the neighbour elements as they may overlap
            for(int j=0; j<4; j++){
                if(j < 3 && board[i][j] == board[i][j+1]){ // check for horizontal overlap
                    return false;
                }
                if(i < 3 && board[i][j] == board[i+1][j]){ // check for vertical overlap
                    return false;
                }
            }
        }

        return true;
    }

    void randSpawn(){

        vector<pair<int, int>> zeroSpaces;

        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(board[i][j] == 0){
                    zeroSpaces.push_back({i, j});
                }
            }
        }

        int sz = zeroSpaces.size();

        if(!zeroSpaces.empty()){
            uniform_int_distribution<> dist(0, sz-1); // pick a random coordinate from the above vector
            pair<int, int> loc = zeroSpaces[dist(gen)]; // store the selected pair in random manner
            if(prob(gen) == 0){ // 10% chance for a '4' to be spawned, to make the game more challenging :P
                board[loc.first][loc.second] = 4;
            }else{ // 90% chance for a '2' to be spawned
                board[loc.first][loc.second] = 2;
            }
        }
    }

    // single swipe right logic is used to avoid repitition of code due to multiple movements, reduces chances of errors
    bool swipeRight(vector<int>& vec){

        int tgtIdx = 3; // target index is chosen as right most because we first need to fill the last index before processing any previous elements
        bool tracker = false; // keeps track if any valid moves are being made or not

        for(int i=3; i>=0; i--){
            if(vec[i] == 0){
                continue;
            }
            int curr = vec[i];
            if(i != tgtIdx || vec[tgtIdx] == 0){ // pick up the current tile if it is already not zero and not in its target position
                if(i != tgtIdx){
                    vec[i] = 0;
                    tracker = true; // we made changes to the board, so a valid move happened
                }
            }
            if(vec[tgtIdx] == 0){
                /*target spot is already empty so shift the tile to that position,
                  don't decrement the index as another number might get merged with current one later*/
                vec[tgtIdx] = curr;
            }else if(vec[tgtIdx] == curr && i != tgtIdx){
                vec[tgtIdx] *= 2; // simply double the current spot as target spot = current spot
                score += vec[tgtIdx];
                tgtIdx--; // decrement index as merging has already taken place
                tracker = true;
            }else{
                if(i == tgtIdx){
                    continue;
                }
                tgtIdx--; // none of the previous events occurred, try to find a new index
                vec[tgtIdx] = curr;
                if(i != tgtIdx){ // register a move if we couldn't find a target index
                    tracker = true;
                }
            }
        }

        return tracker;
    }

    bool up(){ // for 'up' movement

        bool tracker = false;

        for(int j=0; j<4; j++){ // iterate over the columns first
            vector<int> vec(4); // declare a vector store the extracted elements from the loops
            for(int i=0; i<4; i++){
                vec[3-i] = board[i][j]; // extract the elements in reverse order
            }
            if(swipeRight(vec)){
                tracker = true; // register a move if swipe right was successful
            }
            for(int i=0; i<4; i++){ // put new values into the board
                board[i][j] = vec[3-i];
            }
        }

        // spawn a random element only if something moved
        if(tracker){
            randSpawn();
        }

        return tracker;
    }

    bool down(){ // for 'down' movement

        bool tracker = false;

        for(int j=0; j<4; j++){
            vector<int> vec(4);
            for(int i=0; i<4; i++){
                vec[i] = board[i][j]; // extract the elements in natural order
            }
            if(swipeRight(vec)){
                tracker = true;
            }
            for(int i=0; i<4; i++){
                board[i][j] = vec[i];
            }
        }

        if(tracker){
            randSpawn();
        }

        return tracker;
    }

    bool left(){ // for 'left' movement

        bool tracker = false;

        for(int i=0; i<4; i++){
            vector<int> vec(4);
            for(int j=0; j<4; j++){
                vec[3-j] = board[i][j];
            }
            if(swipeRight(vec)){
                tracker = true;
            }
            for(int j=0; j<4; j++){
                board[i][j] = vec[3-j];
            }
        }

        if(tracker){
            randSpawn();
        }

        return tracker;
    }

    bool right(){ // for 'right' movement

        bool tracker = false;

        for(int i=0; i<4; i++){
            vector<int> vec(4);
            for(int j=0; j<4; j++){
                vec[j] = board[i][j];
            }
            if(swipeRight(vec)){  
                tracker = true;
            }
            for(int j=0; j<4; j++){
                board[i][j] = vec[j];
            }
        }

        if(tracker){
            randSpawn();
        }

        return tracker;
    }

    void display(){

        // clear screen command; \033[2J clears the entire screen; \033[1;1H moves cursor to top left position
        cout << "\033[2J\033[1;1H";

        cout << "\n2048 GAME\n";
        cout << "Score: " << score << "\n\n";

        cout << "+------+------+------+------+\n";

        for(int i=0; i<4; i++){
            cout << "|";
            for(int j=0; j<4; j++){
                if(board[i][j] == 0){
                    cout << "      |";
                }else{
                    cout << setw(5) << board[i][j] << " |";
                }
            }
            cout << "\n+------+------+------+------+\n";
        }

        cout << "\nControls: W(up) A(left) S(down) D(right) Q(quit)\n";
    }

    int scoreVal(){
        return score;
    }
};

int main(){

    Game newGame; // creates a new game ^_^

    char input;
    bool isValid;

    newGame.display();

    while(true){
        
        cout << "\nEnter move: ";
        cin >> input;

        if(input >= 'a' && input <= 'z'){
            input = input-32; // converts uppercase to lowercase
        }

        isValid = false;

        if(input == 'W'){
            isValid = newGame.up();
        }else if(input == 'A'){
            isValid = newGame.left();
        }else if(input == 'S'){
            isValid = newGame.down();
        }else if(input == 'D'){
            isValid = newGame.right();
        }else if(input == 'Q'){
            cout << "\nThanks for playing! Final Score: " << newGame.scoreVal() << "\n\n";
            break;
        }else{
            cout << "\nInvalid input! Use W/A/S/D to move or Q to quit.\n";
            continue;
        }

        if(!isValid){
            cout << "\nInvalid move! Try a different direction.\n";
            cout << "Press Enter to continue...";
            cin.ignore(); // clears input buffer
            cin.get(); // pauses the program until the user hits a key
        }

        newGame.display();

        if(newGame.hasGameEnded()){
            cout << "\n*** GAME OVER ***\n";
            cout << "Final Score: " << newGame.scoreVal() << "\n\n";
            break;
        }
    }

    return 0;
}