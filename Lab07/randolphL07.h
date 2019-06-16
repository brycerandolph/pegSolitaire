//Bryce Randolph
//Lab07
//Standard: C++ 11
//randolphL07.h
#ifndef RANDOLPHL07_H
#define RANDOLPHL07_H
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include "SeparateChaining.cpp"
#include "SeparateChaining.h"
using namespace std;
vector<vector<int> > moves;//declaring global hardcoded moves 2d vector
//this function takes a gameboard, and the list of all moves
//it exists to check what moves are currently possible, and then to push and return those moves in the form of a 2d vector
vector<vector<int> > nextMoves(vector<vector<int> > & moves, bool board[49])
{
        vector<vector<int> > curMoves;
        for(int i = 0; i < moves.size(); i++)
        {
                if(board[moves[i][0]] && board[moves[i][1]] && !board[moves[i][2]])
                        curMoves.push_back(moves[i]);
        }
        return curMoves;
}
//takes the inner moves vector and an input and the copied board
//this function moves pegs and changes the values of slots in the board
void makeMove(const vector<int> & move, bool board[49], bool newboard[49])
{
        for(int i = 0; i < 49; i++)
                newboard[i] = board[i];
        newboard[move[0]] = false;
        newboard[move[1]] = false;
        newboard[move[2]] = true;
}
//this function takes a board input and prints it out in a visual format
void printBoard(bool board[49])
{
        for (int row = 0; row < 7; ++row)
        {
                for(int col = 0; col < 7; ++col)
                {
                        char c;
                        if ((row < 2 || row > 4) && (col < 2 || col > 4))
                                c = ' ';
                        else
                        {
                                int index = row * 7 + col;
                                c = board[index] ? '*' : '.';
                        }
                        cout << c << ' ';
                }
                cout << endl;
        }
        cout << endl;
}
//returns a bool value and takes a board and count as input, the count is to determine
bool solved(bool board[49], int count)
{
        int add = 0;
        for(int i = 0; i < 49; i++)
        {
                if(board[i] == true)
                        add++;
        }
        if(add == 1)
        {
                if(count == 0) {
                        cout << "Winning Sequence without hashing" << endl;
                        cout << "--------------------------------" << endl;
                }
                if(count == 1) {
                        cout << "Winning Sequence using hashing" << endl;
                        cout << "------------------------------" << endl;
                }
                return true;
        }
        else
                return false;
}
//Backtracking DFS function that takes the list of moves, board, and final move sequence vector(which is later returned)
//iterates through all possible current moves and creates a set of moves that solve the board, then outputs those moves
bool solve(vector<vector<int> > & moveList, bool board[49], vector<vector<int> > & moveSeq)
{
        int count = 0;
        if(solved(board,count))
                return true;
        vector<vector<int> > curMoves = nextMoves(moveList,board);
        for(int i = 0; i < curMoves.size(); i++)
        {
                bool newboard[49];
                makeMove(curMoves[i], board, newboard);
                if(solve(moveList,newboard,moveSeq))
                {
                        moveSeq.push_back(curMoves[i]);
                        cout <<"(";
                        for(int j = 0; j < 2; j++)
                        {
                                cout << curMoves[i][j] << " ";
                        }
                        cout << curMoves[i][2] << ")\n";
                        return true;
                }
        }
        return false;
}
//DFS using HashTable for quicker execution, takes the list of moves, board, and final move sequence vector(which is later returned), as well as a count for the solved function
//iterates through all possible current moves and creates a set of moves that solve the board, then outputs those moves
bool hsolve(vector<vector<int> > & moveList, bool board[49], vector<vector<int> > & moveSeq, HashTable<long long> & H, int count)
{
        if(solved(board, count))
                return true;
        vector<vector<int> > curMoves = nextMoves(moveList,board);
        for(int i = 0; i < curMoves.size(); i++)
        {
                bool newboard[49];
                long long int boardNum = 0;
                makeMove(curMoves[i], board, newboard);
                for(int j = 0; j < 49; j++)
                        if(newboard[j])
                                boardNum |= 1LL << j;
                if(!H.contains(boardNum))
                {
                        if(hsolve(moveList,newboard,moveSeq,H,count))
                        {
                                moveSeq.push_back(curMoves[i]);
                                if(count == 1)
                                {
                                        cout << "(";

                                        for(int j = 0; j < 2; j++)
                                        {
                                                cout << curMoves[i][j] << " ";
                                        }
                                        cout << curMoves[i][2] << ")\n";
                                }
                                return true;
                        }
                        else
                                H.insert(boardNum);
                }
        }
        return false;
}
//this function allows the user to loop and solve multiple files without exiting the program
void userQ()
{
        cout << "Would you like to continue? Yes(y) or No(n): ";
        char key;
        cin >> key;
        if (key == 'y');
        else if(key == 'n')
        {
                cout << "Program terminating\n";
                exit(0);
        }
        else
        {
                cout << "Error: Unexpected Input\n";
                userQ();
        }
}
//tales an empty moves list and populates it with the hardcoded information
void vectorLoader(vector<vector<int> > & moves)
{
        moves.push_back(vector<int> {14, 21, 28});
        moves.push_back(vector<int> {15, 22, 29});
        moves.push_back(vector<int> {19, 26, 33});
        moves.push_back(vector<int> {20, 27, 34});
        moves.push_back(vector<int> {2, 9, 16});
        moves.push_back(vector<int> {9, 16, 23});
        moves.push_back(vector<int> {16, 23, 30});
        moves.push_back(vector<int> {23, 30, 37});
        moves.push_back(vector<int> {30, 37, 44});
        moves.push_back(vector<int> {3, 10, 17});
        moves.push_back(vector<int> {10, 17, 24});
        moves.push_back(vector<int> {17, 24, 31});
        moves.push_back(vector<int> {24, 31, 38});
        moves.push_back(vector<int> {31, 38, 45});
        moves.push_back(vector<int> {4, 11, 18});
        moves.push_back(vector<int> {11, 18, 25});
        moves.push_back(vector<int> {18, 25, 32});
        moves.push_back(vector<int> {25, 32, 39});
        moves.push_back(vector<int> {32, 39, 46});
        moves.push_back(vector<int> {2, 3, 4});
        moves.push_back(vector<int> {9, 10, 11});
        moves.push_back(vector<int> {37, 38, 39});
        moves.push_back(vector<int> {44, 45, 46});
        moves.push_back(vector<int> {14, 15, 16});
        moves.push_back(vector<int> {15, 16, 17});
        moves.push_back(vector<int> {16, 17, 18});
        moves.push_back(vector<int> {17, 18, 19});
        moves.push_back(vector<int> {18, 19, 20});
        moves.push_back(vector<int> {21, 22, 23});
        moves.push_back(vector<int> {22, 23, 24});
        moves.push_back(vector<int> {23, 24, 25});
        moves.push_back(vector<int> {24, 25, 26});
        moves.push_back(vector<int> {25, 26, 27});
        moves.push_back(vector<int> {28, 29, 30});
        moves.push_back(vector<int> {29, 30, 31});
        moves.push_back(vector<int> {30, 31, 32});
        moves.push_back(vector<int> {31, 32, 33});
        moves.push_back(vector<int> {32, 33, 34});
        moves.push_back(vector<int> {28, 21, 14});
        moves.push_back(vector<int> {29, 22, 15});
        moves.push_back(vector<int> {33, 26, 19});
        moves.push_back(vector<int> {34, 27, 20});
        moves.push_back(vector<int> {16, 9, 2});
        moves.push_back(vector<int> {23, 16, 9});
        moves.push_back(vector<int> {30, 23, 16});
        moves.push_back(vector<int> {37, 30, 23});
        moves.push_back(vector<int> {44, 37, 30});
        moves.push_back(vector<int> {17, 10, 3});
        moves.push_back(vector<int> {24, 17, 10});
        moves.push_back(vector<int> {31, 24, 17});
        moves.push_back(vector<int> {38, 31, 24});
        moves.push_back(vector<int> {45, 38, 31});
        moves.push_back(vector<int> {18, 11, 4});
        moves.push_back(vector<int> {25, 18, 11});
        moves.push_back(vector<int> {32, 25, 18});
        moves.push_back(vector<int> {39, 32, 25});
        moves.push_back(vector<int> {46, 39, 32});
        moves.push_back(vector<int> {4, 3, 2});
        moves.push_back(vector<int> {11, 10, 9});
        moves.push_back(vector<int> {39, 38, 37});
        moves.push_back(vector<int> {46, 45, 44});
        moves.push_back(vector<int> {16, 15, 14});
        moves.push_back(vector<int> {17, 16, 15});
        moves.push_back(vector<int> {18, 17, 16});
        moves.push_back(vector<int> {19, 18, 17});
        moves.push_back(vector<int> {20, 19, 18});
        moves.push_back(vector<int> {23, 22, 21});
        moves.push_back(vector<int> {24, 23, 22});
        moves.push_back(vector<int> {25, 24, 23});
        moves.push_back(vector<int> {26, 25, 24});
        moves.push_back(vector<int> {27, 26, 25});
        moves.push_back(vector<int> {30, 29, 28});
        moves.push_back(vector<int> {31, 30, 29});
        moves.push_back(vector<int> {32, 31, 30});
        moves.push_back(vector<int> {33, 32, 31});
        moves.push_back(vector<int> {34, 33, 32});
}
#endif
