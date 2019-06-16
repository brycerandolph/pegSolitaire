#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> moves;

bool CanPerformMove(const vector<int> & move, const bool board[49])
{
    return board[move[0]] &&
           board[move[1]] &&
           !board[move[2]];
}

void PerformMove(const vector<int> & move, bool board[49])
{
    board[move[0]] = false;
    board[move[1]] = false;
    board[move[2]] = true;
}

void PrintBoard(bool board[49])
{
    for (int row = 0; row < 7; ++row)
    {
        for(int col = 0; col < 7; ++col)
        {
            char c;
            if ((row < 2 || row > 4) && (col < 2 || col > 4))
            {
                c = ' ';
            } else
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

int main()
{
    moves.push_back(vector<int> { 2, 3, 4 });
    moves.push_back(vector<int> { 2, 9, 16 });

    bool board[49];
    for(int i = 0; i < 49; ++i)
        board[i] = false;

    board[2] = true;
    board[3] = true;
    board[9] = true;

    PrintBoard(board);

    for (auto move : moves)
    {
        if (CanPerformMove(move, board))
        {
            bool newBoard[49];
            for(int i = 0; i < 49; ++i)
                newBoard[i] = board[i];
            PerformMove(move, newBoard);
            PrintBoard(newBoard);

        }
    }
    return 0;

}