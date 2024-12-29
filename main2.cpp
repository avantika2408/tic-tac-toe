#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>

using namespace std;

const string RED = "\033[31m";      // Red text
    const string BLUE = "\033[34m";     // Blue text
    const string RESET = "\033[0m";     // Reset to default color
    const string YELLOW = "\033[33m";  // Yellow text
    const string GREEN = "\033[32m";   // Green text
    const string PINK = "\033[38;5;200m";
    const string VIOLET = "\033[38;5;93m";

void printMatrix(vector<vector<string>>& matrix) {
    cout<< BLUE <<"  0   1   2" << RESET<< endl;
    for (int i = 0; i < 3; i++) {
        cout<< BLUE << i << RESET ;
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == "X"){cout << YELLOW << " "<< matrix[i][j] <<RESET << " ";}
            else {cout << " " << PINK <<matrix[i][j] << RESET << " ";}
            if(j>=0 && j<2){ cout << "|";}
        }
        cout<<"\n -----------";
        cout << endl;
    }
}

void update(vector<int>& v, int value) {
    v.erase(remove(v.begin(), v.end(), value), v.end());
}

int iIndex(int value) {
    return value / 10;
}

int jIndex(int value) {
    return value % 10;
}
//if l formation occurs by x
int Lformationx(vector<vector<string>>& matrix){
    if (matrix[iIndex(1)][jIndex(1)] == "X" && matrix[iIndex(10)][jIndex(10)] == "X"){
        if(matrix[iIndex(0)][jIndex(0)] == "*"){
            matrix[iIndex(0)][jIndex(0)] = "O";
            
            return 0;
        }
        else if (matrix[iIndex(11)][jIndex(11)] == "*" && matrix[iIndex(0)][jIndex(0)] == "O"){
            return 11;
        }
    }

    else if (matrix[iIndex(21)][jIndex(21)] == "X" && matrix[iIndex(10)][jIndex(10)] == "X"){
        if(matrix[iIndex(20)][jIndex(20)] == "*"){
            matrix[iIndex(20)][jIndex(20)] = "O";
            return 20;
        }
        else if (matrix[iIndex(11)][jIndex(11)] == "*" && matrix[iIndex(20)][jIndex(20)] == "O"){
            return 11;
        }
    }  
    else if (matrix[iIndex(21)][jIndex(21)] == "X" && matrix[iIndex(12)][jIndex(12)] == "X"){
        if(matrix[iIndex(22)][jIndex(22)] == "*"){
            matrix[iIndex(22)][jIndex(22)] = "O";
            return 22;
        }
        else if (matrix[iIndex(11)][jIndex(11)] == "*" && matrix[iIndex(22)][jIndex(22)] == "O"){
            return 11;
        }
    } 
    else if (matrix[iIndex(12)][jIndex(12)] == "X" && matrix[iIndex(1)][jIndex(1)] == "X"){
        if(matrix[iIndex(2)][jIndex(2)] == "*"){
            matrix[iIndex(2)][jIndex(2)] = "O";
            return 2;
        }
        else if (matrix[iIndex(11)][jIndex(11)] == "*" && matrix[iIndex(2)][jIndex(2)] == "O"){
            return 11;
        }
    }
    return -1;
}
//if l formation occurs by O

int Lformationo(vector<vector<string>>& matrix){
    if (matrix[iIndex(1)][jIndex(1)] == "O" && matrix[iIndex(10)][jIndex(10)] == "O"){
        if(matrix[iIndex(0)][jIndex(0)] == "*"){
            
            matrix[iIndex(0)][jIndex(0)] = "O";
            return 0;
        }
        else if (matrix[iIndex(11)][jIndex(11)] == "*" && matrix[iIndex(0)][jIndex(0)] == "O"){
            return 11;
        }
    }

    else if (matrix[iIndex(21)][jIndex(21)] == "O" && matrix[iIndex(10)][jIndex(10)] == "O"){
        if(matrix[iIndex(20)][jIndex(20)] == "*"){
            matrix[iIndex(20)][jIndex(20)] = "O";
            return 20;
        }
        else if (matrix[iIndex(11)][jIndex(11)] == "*" && matrix[iIndex(20)][jIndex(20)] == "O"){
            return 11;
        }
    }  
    else if (matrix[iIndex(21)][jIndex(21)] == "O" && matrix[iIndex(12)][jIndex(12)] == "O"){
        if(matrix[iIndex(22)][jIndex(22)] == "*"){
            matrix[iIndex(22)][jIndex(22)] = "O";
            return 22;
        }
        else if (matrix[iIndex(11)][jIndex(11)] == "*" && matrix[iIndex(22)][jIndex(22)] == "O"){
            return 11;
        }
    } 
    else if (matrix[iIndex(12)][jIndex(12)] == "O" && matrix[iIndex(1)][jIndex(1)] == "O"){
        if(matrix[iIndex(2)][jIndex(2)] == "*"){
            matrix[iIndex(2)][jIndex(2)] = "O";
            return 2;
        }
        else if (matrix[iIndex(11)][jIndex(11)] == "*" && matrix[iIndex(2)][jIndex(2)] == "O"){
            return 11;
        }
    }
    return -1;
}

bool checkWin(const vector<vector<string>>& matrix, const string& player) {
    for (int i = 0; i < 3; i++) {
        //rows
        if (matrix[i][0] == player && matrix[i][1] == player && matrix[i][2] == player) return true;
        // columns
        if (matrix[0][i] == player && matrix[1][i] == player && matrix[2][i] == player) return true;
    }
    // diagonals
    if (matrix[0][0] == player && matrix[1][1] == player && matrix[2][2] == player) return true;
    if (matrix[0][2] == player && matrix[1][1] == player && matrix[2][0] == player) return true;

    return false;
}

bool checkTie(const vector<vector<string>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& cell : row) {
            if (cell == "*") {
                return false;
            }
        }
    }
    return true;
}

bool isFirstMove(vector<vector<string>>& matrix) {
    int emptyCount = 0;
    for (const auto& row : matrix) {
        for (const auto& cell : row) {
            if (cell == "*") {
                emptyCount++;
            }
        }
    }
    return emptyCount == 8;
}

void playMatrix(vector<vector<string>>& matrix) {
    srand(time(NULL));
    vector<int> corner = {0, 2, 20, 22, 11};

    vector<int> Xhori1 = {0, 1, 2};
    vector<int> Xhori2 = {10, 11, 12};
    vector<int> Xhori3 = {20, 21, 22};
    vector<int> Xver1 = {0, 10, 20};
    vector<int> Xver2 = {1, 11, 21};
    vector<int> Xver3 = {2, 12, 22};
    vector<int> Xdia1 = {0, 11, 22};
    vector<int> Xdia2 = {2, 11, 20};

    vector<int> Ohori1 = {0, 1, 2};
    vector<int> Ohori2 = {10, 11, 12};
    vector<int> Ohori3 = {20, 21, 22};
    vector<int> Over1 = {0, 10, 20};
    vector<int> Over2 = {1, 11, 21};
    vector<int> Over3 = {2, 12, 22};
    vector<int> Odia1 = {0, 11, 22};
    vector<int> Odia2 = {2, 11, 20};
    

    

    while (true) {
        int x, y;
        cout << "Enter the coordinates (x y): ";
        cin >> x >> y;

        if (x<0 || x >2 || y<0 || y>2){
            cout << RED << "invalid expression" << RESET << endl;
            continue;
        }

        if (matrix[x][y] != "*") {
            cout << RED <<"Cell already occupied" << RESET << endl;
            continue;
        }
        system("clear");
        

        matrix[x][y] = "X";
        printMatrix(matrix);
        int pos = x * 10 + y;
        update(Xhori1, pos);
        update(Xhori2, pos);
        update(Xhori3, pos);
        update(Xver1, pos);
        update(Xver2, pos);
        update(Xver3, pos);
        update(Xdia1, pos);
        update(Xdia2, pos);

        

        if (checkWin(matrix, "X")) {
            system("clear");
            printMatrix(matrix);
            cout << GREEN << "You WIN!" << RESET << endl;
            break;
        }

        
        if (checkTie(matrix)) {
            system("clear");
            printMatrix(matrix);
            cout << YELLOW << "It's a TIE!"<< RESET << endl;
            break;
        }

        
        bool moveMade = false;

        
        if (isFirstMove(matrix)) {
            vector<pair<int, int>> initialMoves = { {0, 0}, {0, 2}, {2, 0}, {2, 2}, {1, 1} };
            while(true){
                pair<int, int> move = initialMoves[rand() % initialMoves.size()];
                if(matrix[move.first][move.second] == "*"){
                    matrix[move.first][move.second] = "O";
                    pos = move.first * 10 + move.second;
                    update(Ohori1, pos);
                    update(Ohori2, pos);
                    update(Ohori3, pos);
                    update(Over1, pos);
                    update(Over2, pos);
                    update(Over3, pos);
                    update(Odia1, pos);
                    update(Odia2, pos);
                    moveMade = true;
                    break;}
        }}
        
        
        if (!moveMade) {
            vector<vector<int>*> oVectors = { &Ohori1, &Ohori2, &Ohori3, &Over1, &Over2, &Over3, &Odia1, &Odia2 };
            for (auto& vec : oVectors) {
                if (vec->size() == 1) {
                    int oPos = vec->front();
                    if (matrix[iIndex(oPos)][jIndex(oPos)] == "*") {
                        matrix[iIndex(oPos)][jIndex(oPos)] = "O";
                        update(Ohori1, oPos);
                        update(Ohori2, oPos);
                        update(Ohori3, oPos);
                        update(Over1, oPos);
                        update(Over2, oPos);
                        update(Over3, oPos);
                        update(Odia1, oPos);
                        update(Odia2, oPos);
                        moveMade = true;
                        break;
                    }
                }
            }
        }

        // block
        if (!moveMade) {
            vector<vector<int>*> xVectors = { &Xhori1, &Xhori2, &Xhori3, &Xver1, &Xver2, &Xver3, &Xdia1, &Xdia2 };
            for (auto& vec : xVectors) {
                if (vec->size() == 1) {
                    int xPos = vec->front();
                    if (matrix[iIndex(xPos)][jIndex(xPos)] == "*") {
                        matrix[iIndex(xPos)][jIndex(xPos)] = "O";
                        update(Ohori1, xPos);
                        update(Ohori2, xPos);
                        update(Ohori3, xPos);
                        update(Over1, xPos);
                        update(Over2, xPos);
                        update(Over3, xPos);
                        update(Odia1, xPos);
                        update(Odia2, xPos);
                        moveMade = true;
                        break;
                    }
                }
            }
        }
        if (!moveMade){
            if (Lformationo(matrix) != -1){
                if (Lformationx(matrix) == -1){
                int pos = iIndex(Lformationo(matrix)*10 + jIndex(Lformationo(matrix)));
                update(Ohori1, pos);
                update(Ohori2, pos);
                update(Ohori3, pos);
                update(Over1, pos);
                update(Over2, pos);
                update(Over3, pos);
                update(Odia1, pos);
                update(Odia2, pos);
                moveMade = true;
                }
        }}

        if (!moveMade){
            if (Lformationx(matrix) != -1){
                if (Lformationo(matrix) == -1){
                    int pos = iIndex(Lformationo(matrix)*10 + jIndex(Lformationo(matrix)));
                    update(Ohori1, pos);
                    update(Ohori2, pos);
                    update(Ohori3, pos);
                    update(Over1, pos);
                    update(Over2, pos);
                    update(Over3, pos);
                    update(Odia1, pos);
                    update(Odia2, pos);
                    moveMade = true;
        }}}

        // rando
        if (!moveMade) {
            vector<pair<int, int>> emptyCells;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (matrix[i][j] == "*") {
                        emptyCells.push_back({i, j});
                    }
                }
            }

            if (!emptyCells.empty()) {
                pair<int, int> move = emptyCells[rand() % emptyCells.size()];
                matrix[move.first][move.second] = "O";
                pos = move.first * 10 + move.second;
                update(Ohori1, pos);
                update(Ohori2, pos);
                update(Ohori3, pos);
                update(Over1, pos);
                update(Over2, pos);
                update(Over3, pos);
                update(Odia1, pos);
                update(Odia2, pos);
            }
        }

        
        if (checkWin(matrix, "O")) {
            system("clear");
            printMatrix(matrix);
            cout << RED <<"You LOSE"<< RESET << endl;
            break;
        }

        
        if (checkTie(matrix)) {
            system("clear");
            printMatrix(matrix);
            cout <<YELLOW<< "It's a TIE!"<< RESET << endl;
            break;
        }
        this_thread::sleep_for(chrono::seconds(1));
        system("clear");

        printMatrix(matrix);

        cout << VIOLET<< "Next move!"<< RESET << endl;
    }
}

int main() {
    
    
    while(true){
        system("clear");
        vector<vector<string>> matrix(3, vector<string>(3, "*"));
        string x;
        printMatrix(matrix);
        playMatrix(matrix);
        cout << VIOLET << " DO you want to play again? (y/n) " << RESET <<endl;
        cin >>  x ;
        if (x == "n"){
            cout << "ok thanku for playing!!"<< endl;
            break;
        }
    }
    return 0;
}