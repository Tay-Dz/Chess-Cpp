#ifndef CHESS_BOARD
#define CHESS_BOARD
#include<iostream>
#include<string>
#include"Chess_pieces_class.h"
#include"Title.h"

class matrix
{
    //input and output friend functions
    friend std::ostream& operator<<(std::ostream& os, const matrix& mat);
private:
    chess_pieces** matrix_data{ nullptr };
    int rows{ 8 };
    int columns{ 8 };
public:
    matrix();    // Parameterized constructor

    ~matrix() {};    // Destructor
    // Access functions
    int index(int m, int n) const { // Return position in array of element (m,n)
        if (m > 0 && m <= 8 && n > 0 && n <= 8) return (n - 1) + (m - 1) * 8;
        else { std::cout << "Error: out of range" << std::endl; exit(1); }
    }
    std::vector<std::pair<int, int>>  possible_moves(int i,int j) {
        std::vector<std::vector<std::pair<int, int>>> moves;
        moves = matrix_data[index(i, j)]->move();
        std::pair<int, int > move;
        std::vector < std::pair<int, int>> all_moves;
        if (matrix_data[index(i, j)]->pic() == "p") {
            for (int a = 0; a < matrix_data[index(i, j)]->move().size(); a++) {
                int go = 1;
                for (int b = 0; b < moves[a].size(); b++) {
                    int x = moves[a][b].first + i;
                    int y = moves[a][b].second + j;
                    if (a == 0) {
                        if (matrix_data[index(x, y)]->pic() == " " && go == 1) {
                            move.first = x;
                            move.second = y;
                            all_moves.push_back(move);
                        }
                        else {
                            go = 0;
                        }
                    }
                    else if (matrix_data[index(x, y)]->pic() != " " && matrix_data[index(i, j)]->col() != matrix_data[index(x, y)]->col()) {
                        move.first = x;
                        move.second = y;
                        all_moves.push_back(move);
                    }
                }
            }
        }
        else{
            for (int a = 0; a < matrix_data[index(i, j)]->move().size(); a++) {
                int go = 1;      
                for (int b = 0; b < moves[a].size(); b++) {
                    if(go){
                        int x = moves[a][b].first + i;
                        int y = moves[a][b].second + j;
                        if (x > 8 || x < 1 || y > 8 || y < 1||matrix_data[index(i, j)]->col() == matrix_data[index(x, y)]->col()) {
                            go = 0;
                        }
                        else if (matrix_data[index(x, y)]->col() == " ") {
                            move.first = x;
                            move.second = y;
                            all_moves.push_back(move);
                        }
                        else {
                            move.first = x;
                            move.second = y;
                            all_moves.push_back(move);
                            go = 0;
                        }

                    }
                }
            }
        }

        return all_moves;
    }
    bool move_here(int i, int j, int x, int y) {
        std::pair<int, int> location;
        location.first = x;
        location.second = y;
        std::vector<std::pair<int, int>> move = possible_moves(i, j);
        for (int a = 0; a < move.size(); a++) {
            if (move[a].first == x && move[a].second == y) { return true; }
        }
        return false;
    }
    std::string move_here_str(int i, int j , int x, int y) {
        if (move_here(i, j, x, y)) { return "X"; }
        else { return " "; }
    }

    void move_piece(int m, int n, int p, int q) {
        if (matrix_data[index(m, n)]->pic() == "p") { matrix_data[index(m, n)]->has_moved(); }
        std::swap(matrix_data[index(m, n)], matrix_data[index(p, q)]);
        delete matrix_data[index(m, n)];
        matrix_data[index(m, n)] = new empty();
        return;
    } //change values
    void moves_out(int x, int y);
    bool is_empty(int x, int y) {
        if (matrix_data[index(x, y)]->col() == " ") { return true; }
        else{return false;}
    }
    bool right_colour(int x, int y, std::string colour) {
        if ((matrix_data[index(x, y)]->col() == "w" && colour == "White") || (matrix_data[index(x, y)]->col() == "b" && colour == "Black")) {
            return true;
        }
        else { return false; }
    }
};
// member functon definitions
matrix::matrix() {//parameterised constructor 
        matrix_data = new chess_pieces*[64];
        matrix_data[index(1,1)] = new rook("w");
        matrix_data[index(1, 8)] = new rook("w");
        matrix_data[index(1, 2)] = new knight("w");
        matrix_data[index(1, 7)] = new knight("w");
        matrix_data[index(1, 3)] = new bishop("w");
        matrix_data[index(1, 6)] = new bishop("w");
        matrix_data[index(1, 4)] = new king("w");
        matrix_data[index(1, 5)] = new queen("w");
        matrix_data[index(8, 1)] = new rook("b");
        matrix_data[index(8, 8)] = new rook("b");
        matrix_data[index(8, 2)] = new knight("b");
        matrix_data[index(8, 7)] = new knight("b");
        matrix_data[index(8, 3)] = new bishop("b");
        matrix_data[index(8, 6)] = new bishop("b");
        matrix_data[index(8, 4)] = new king("b");
        matrix_data[index(8, 5)] = new queen("b");
        for (int i = 1; i <= 8; i++) {
            matrix_data[index(7,i)] = new pawn("b");
            matrix_data[index(2, i)] = new pawn("w");
            for (int j = 3; j <= 6; j++) {
                matrix_data[index(j, i)] = new empty();
            }
        }
}

std::ostream& operator<<(std::ostream& os, const matrix& mat) { // output matrix
    system("CLS");
    title();
    std::string barrier = "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    std::string next = "||      ||      ||      ||      ||      ||      ||      ||      ||";
    std::string begin = "||  ";
    std::string mid = "  ||  ";
    std::string end = "  ||";
    for (int i = 1; i <= 8; i++) {
        std::cout << barrier << std::endl << next << std::endl;
        std::cout << begin;
        for (int j = 1; j <= 8; j++) {
            if (j == 8) { std::cout << mat.matrix_data[mat.index(i, j)]->piece_out() << end; }
            else { std::cout << mat.matrix_data[mat.index(i, j)]->piece_out() << mid; }
        }

        std::cout << std::endl << next << std::endl;
    }
    std::cout << barrier << std::endl;
    return os;
};
void matrix::moves_out(int x, int y) {
    system("CLS");
    title();
    std::string barrier = "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    std::string next = "||      ||      ||      ||      ||      ||      ||      ||      ||";
    std::string begin = "|| ";
    std::string mid = " || ";
    std::string end = " ||";
    for (int i = 1; i <= 8; i++) {
        std::cout << barrier << std::endl;
        std::cout << begin;
        for (int j = 1; j <= 8; j++) {
            if (j == 8) { std::cout <<" "<<move_here_str(x,y,i,j)<< move_here_str(x, y, i, j)<< " " << end; }
            else { std::cout  <<" " << move_here_str(x, y, i, j)<< move_here_str(x, y, i, j) << " "  << mid; }
        }
        std::cout <<std::endl<<begin;
        for (int j = 1; j <= 8; j++) {
            if (j == 8) { std::cout << move_here_str(x, y, i, j) << matrix_data[index(i, j)]->piece_out() << move_here_str(x, y, i, j) << end; }
            else { std::cout << move_here_str(x, y, i, j) << matrix_data[index(i, j)]->piece_out() << move_here_str(x, y, i, j) << mid; }
        }

        std::cout << std::endl << begin;
        for (int j = 1; j <= 8; j++) {
            if (j == 8) { std::cout << " " << move_here_str(x, y, i, j) << move_here_str(x, y, i, j) << " " << end; }
            else { std::cout << " " << move_here_str(x, y, i, j) << move_here_str(x, y, i, j) << " " << mid; }
        }
         std::cout<< std::endl;
    }
    std::cout << barrier << std::endl;
}
#endif
