//
//  sudoku.h
//  PS2
//
//  Created by Yitian Fu on 9/7/17.
//  Copyright © 2017 Yitian Fu. All rights reserved.
//

#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
#include<string>
using std::vector;
using namespace std;
class Sudoku
{
    // Private
    int puzzle[9][9];
    
    // Private member function that checks if the named row is valid
    bool row_valid(int row)
    {
        // write code that checks if "row" is valid
        for(int i=0;i<9;i++)
        {
            for(int j=i+1;j<9;j++)
            {
                if((puzzle[row][i]==puzzle[row][j])&&(puzzle[row][i]!=0)&&(puzzle[row][j]!=0))
                    return false;
            }
        }
        return true;
    }
    
    // Private member function that checks if the named column is valid
    bool col_valid(int col)
    {
        // check validity of "col"
        for(int i=0;i<9;i++)
        {
            for(int j=i+1;j<9;j++)
            {
                if(puzzle[i][col]==puzzle[j][col]&&puzzle[i][col]!=0&&puzzle[j][col]!=0)
                 return false;
            }
        }
        return true;
    }
    
    // Private member function that checks if the named 3x3 block is valid
    bool block_valid(int row, int col)
    {
        // check 3 x 3 block validity
        int row1=row/3;
        int col1=col/3;
        for(int i=row1*3;i<(row1*3+3);i++)
        {
            for(int j=col1*3;j<(col1*3+3);j++)
            {
                if(!(i==row&&j==col))
                {
                    if(puzzle[row][col]==puzzle[i][j])
                     return false;
                }
            }
        }
        return true;
    }
    
public:
    // Public member function that reads the incomplete puzzle
    // we are not doing any checks on the input puzzle -- that is,
    // we are assuming they are indeed valid
    void read_puzzle(int argc, char * const argv[])
    {
        // write code that reads the input puzzle using the
        // guidelines of figure 23 of the bootcamp material
        
        vector<int> P;
        int a;
        string s;
        cout<<"input file"<<endl;
        cin>>s;
        ifstream input_file(s);
        if (input_file.is_open()) // If "Data.txt" exists in the local directory
        {
            while(input_file >> a) // As long as your are not at the "end-of-file"
            {
                P.push_back(a);
            }
        }
        else
        {cout << "Input file does not exist in PWD" << endl;}
        
        int b=0;
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                puzzle[i][j]=P[b];
                b++;
            }
        }
                
        
        
    }
    
    // Public member function that prints the puzzle when called
    void print_puzzle()
    {
        std::cout << std::endl << "Board Position" << std::endl;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                // check if we have a legitimate integer between 1 and 9
                if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
                {
                    // printing initial value of the puzzle with some formatting
                    std::cout << puzzle[i][j] << " ";
                }
                else {
                    // printing initial value of the puzzle with some formatting
                    std::cout << "X ";
                }
            }
            std::cout << std::endl;
        }
    }
    
    // Public member function that (recursively) implements the brute-force
    // search for possible solutions to the incomplete Sudoku puzzle
    
    bool Solve(int row, int col)
    {
        // this part of the code identifies the row and col number of the
        // first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
        // no zeros, the variable row will be 9 => the puzzle is done, as 
        // each entry is row-, col- and block-valid..
        // use the pseudo code of figure 3 of the description
        bool flag=true;
        //find a solution
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            { if(puzzle[i][j]==0)
                {   row=i;
                    col=j;
                    i=9;
                    j=9;
                    flag=false;
                }
            }
        }
        
        if(flag==true)
        {   cout<<endl;
            static int a=0;
            cout<<"Solution"<<a+1;
            a++;
            print_puzzle();
            return true;
        }
        
        for(int k=1;k<=9;k++)
            {
                puzzle[row][col]=k;
                if(row_valid(row)&&col_valid(col)&&block_valid(row,col))
                        {
                            Solve(row,col);//do not skip forloop of K,try next k value for the first puzzle[i][j]=0
                           
                        }
                        
            }
          puzzle[row][col]=0;
          return false;
        
        
}
    
};

#endif
