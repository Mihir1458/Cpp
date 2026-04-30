#include <iostream>
using namespace std;

class TicTacToe
{
private:
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}};

    string player1, player2;
    char symbol1, symbol2;
    char player;

public:
    void getData()
    {
        cout << "Enter Player 1 Name : ";
        cin >> player1;

        cout << "Enter Player 2 Name : ";
        cin >> player2;

        while (true)
        {
            cout << player1 << " choose your symbol (X or O) : ";
            cin >> symbol1;

            if (symbol1 == 'X' || symbol1 == 'O')
            {
                break;
            }
            else
            {
                cout << "Please enter only X or O" << endl;
            }
        }

        if (symbol1 == 'X')
        {
            symbol2 = 'O';
        }
        else
        {
            symbol2 = 'X';
        }

        player = symbol1;

        cout << player1 << " is " << symbol1 << endl;
        cout << player2 << " is " << symbol2 << endl;
    }

    void show()
    {
        cout << endl;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << "|  " << board[i][j] << " ";

                if (j < 3)
                    cout << "|";
            }

            cout << endl;

            if (i < 2)
                cout << "--------------------" << endl;
        }

        cout << endl;
    }

    void Turn()
    {
        if (player == 'X')
        {
            player = 'O';
        }
        else
        {
            player = 'X';
        }
    }

    bool Win()
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return true;
        }

        for (int i = 0; i < 3; i++)
        {
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return true;
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return true;

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return true;

        return false;
    }

    bool Draw()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != 'X' && board[i][j] != 'O')
                    return false;
            }
        }

        return true;
    }

    void playGame()
    {
        int choice;
        int row, col;

        while (true)
        {
            show();

            if (player == symbol1)
            {
                cout << player1 << " turn : ";
            }
            else
            {
                cout << player2 << " turn : ";
            }

            cin >> choice;

            if (choice >= 1 && choice <= 3)
            {
                row = 0;
                col = choice - 1;
            }
            else if (choice >= 4 && choice <= 6)
            {
                row = 1;
                col = choice - 4;
            }
            else if (choice >= 7 && choice <= 9)
            {
                row = 2;
                col = choice - 7;
            }
            else
            {
                cout << "Wrong input" << endl;
                continue;
            }

            if (board[row][col] == 'X' || board[row][col] == 'O')
            {
                cout << "Place already used" << endl;
                continue;
            }

            board[row][col] = player;

            if (Win())
            {
                show();

                if (player == symbol1)
                {
                    cout << player1 << " wins the game" << endl;
                }
                else
                {
                    cout << player2 << " wins the game" << endl;
                }

                break;
            }

            if (Draw())
            {
                show();
                cout << "Game Draw" << endl;
                break;
            }

            Turn();
        }
    }
};

int main()
{
    cout << "TIC TAC TOE GAME" << endl;

    TicTacToe t;

    t.getData();
    t.playGame();

    return 0;
}