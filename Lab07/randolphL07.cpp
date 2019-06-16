//Bryce Randolph
//Lab07
//randolphL07.cpp
//Standard: C++ 11
//This program emulates an English peg solotaire game and takes a set of peg locations as a txt file input and
//then attempts to solve the board using backtracking as well as with a HashTable.
#include "randolphL07.h"
int main()
{
        vectorLoader(moves);//creates list of moves
        bool quitting(false);
        while(!quitting)
        {
                int choice = 0;
                bool board[49];//initializes and sets board to false
                for(int i = 0; i < 49; ++i)
                        board[i] = false;
                //file input for true pegs here
                cout << "Please enter the starting position filename: ";
                string fileName;
                cin >> fileName;
                ifstream inputFile(fileName.c_str());
                if(inputFile.fail())//error checker for file input
                {
                        cout << "Input failed.\n";
                        exit(-1);
                }
                // test file open
                if (inputFile)
                {
                        int value;
                        // read the elements in the file and turn on specified pegs
                        while ( inputFile >> value )
                        {
                                board[value] = true;
                        }
                }
                inputFile.close();//close file
                cout << "How would you like to solve the puzzle? Choose Backtracking(1) or Hashing(2) or Quit(3): ";
                cin >> choice;
                vector<vector<int> > moveSeq;
                if (choice == 1)//backtracking choice
                {
                        cout << endl;
                        cout << "Starting Board\n";
                        printBoard(board);
                        double finish_time1 = 0;
                        double start_time1 = clock();
                        int count = 0;
                        if(solve(moves,board, moveSeq))
                        {
                                cout << "Solution found successfully!\n\n";
                        }
                        else
                                cout << "No solution found!\n\n";
                        finish_time1 = clock();
                        double time1 = (double) (finish_time1 - start_time1) / CLOCKS_PER_SEC;
                        cout << "Backtracking Finish Time: " << time1 << endl;
                }
                if(choice == 2)//hashing choice
                {
                        HashTable<long long> htable0;
                        HashTable<long long> htable1 (10000);//initializes the three different hashtables
                        HashTable<long long> htable2 (50000);
                        HashTable<long long> htable3 (100000);
                        cout << endl;
                        cout << "Starting Board\n";
                        printBoard(board);
                        double finish_time0 = 0;
                        double start_time0 = clock();
                        int count = 1;
                        if(hsolve(moves,board, moveSeq,htable0,count))
                        {
                                cout << "Solution found successfully!\n\n";
                        }
                        else
                                cout << "No solution found!\n\n";
                        finish_time0 = clock();
                        double time0 = (double) (finish_time0 - start_time0) / CLOCKS_PER_SEC;
                        cout << "Finish Time of Resizing HashTable:  "<< time0 << endl;


                        double finish_time2 = 0;
                        double start_time2 = clock();
                        count = 2;
                        if(hsolve(moves,board, moveSeq,htable1,count));

                        finish_time2 = clock();
                        double time2 = (double) (finish_time2 - start_time2) / CLOCKS_PER_SEC;
                        cout << "Finish Time of HashTable(10000):    "<< time2 << endl;

                        double finish_time3 = 0;
                        double start_time3 = clock();
                        count = 2;
                        if(hsolve(moves,board, moveSeq,htable2,count));
                        finish_time3 = clock();
                        double time3 = (double) (finish_time3 - start_time3) / CLOCKS_PER_SEC;
                        cout << "Finish Time of HashTable(50000):    " << time3 << endl;

                        double finish_time4 = 0;
                        double start_time4 = clock();
                        count = 2;
                        if(hsolve(moves,board, moveSeq,htable3,count));
                        finish_time4 = clock();
                        double time4 = (double) (finish_time4 - start_time4) / CLOCKS_PER_SEC;
                        cout << "Finish Time of HashTable(100000):   " << time4 << endl;
                }
                if (choice == 3)//exit choice
                {
                        quitting == true;
                        cout << "Program terminating\n";
                        exit(0);
                }
                userQ();//asks if user if they would like to continue
        }
        return 0;
}
