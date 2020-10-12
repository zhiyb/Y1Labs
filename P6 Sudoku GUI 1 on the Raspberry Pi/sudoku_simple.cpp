#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;
#define S 3 // sub square size
#define N 9 // size of the board

class node {
    public:
        int size; // number of 1s in the column
        int name; // symbolic identifier for printing the answers
        int row; // use row to derive the position and number
        node* up;
        node* down;
        node* left;
        node* right;
        node* C;
        node(int name, int row) {
            this -> name = name;
            this->row = row;
            size = 0;
            up = NULL;
            down = NULL;
            left = NULL;
            right = NULL;
            C = NULL;
            }
};

class doublylist{
    public:
        node* h; // special object, only left and right field are used
        // node* head = NULL;
        doublylist() {
            h = new node(-1,-1);
        }
        int num_row;
        int num_col;
        vector<node*> O; // array of pointers

    void generate(int (*graph)[324], int num_row, int num_col) {
        // build the list header
        node* iter_head = h;
        for (int i = 0; i < num_col; i++) {
            int name = num_col-i-1;
            // cout << name << " ";
            node* temp = new node(name,-1);
            temp -> right = iter_head;
            iter_head -> left = temp;
            iter_head = temp;
            // connect h and iter_head
        }
        h->right = iter_head;
        iter_head -> left = h;
        // cout << endl;

        // generate 2D list using the exact cover matrix
        // a easy but space inefficient way: set a node at each cross point
        // then removes connection if matrix element equals to 0
        // below is the time consuming way
        // first iteration for connecting the columns
        node* col_ptr = h;
        node* row_ptr = h;
        for (int i = 0; i < num_col; i++) {
                    col_ptr = col_ptr->right;
                    node* end_col = col_ptr;
                    // node* col_down = col_ptr;
            for (int j = 0; j < num_row; j++) {
                // add new object downwards
                if (graph[j][i] == 1) {
                    // size of the column header increase by one
                    (col_ptr -> size) = (col_ptr -> size) + 1;
                    // cout << "number of 1s:" << col_ptr -> size << endl;
                    node* temp = new node(i,j);
                    temp -> C = col_ptr;
                    end_col -> down = temp;
                    temp -> up = end_col;
                    end_col = temp;
                }
                // last object warps around to the header
                if (j == (num_row-1)) {
                    end_col -> down = col_ptr;
                    col_ptr -> up = end_col;
                }
            }
        }

        // second iteration for connecting the rows
        // reset col and row pointers
        col_ptr = h;
        row_ptr = h;
        node* prev = NULL;
        node* next = NULL;
        node* current = NULL;
        node* head = NULL;
        int array[num_col] = {0}; // similar to the S field in the header object
        int count = 0;
        for (int a = 0; a < num_row; a++) {
            col_ptr = h;
            for (int b = 0; b < num_col; b++) {
                col_ptr = col_ptr -> right;
                // cout << "current column: " << col_ptr -> name << endl;
                // cout << "a = " << a << " b = " << b << endl;
                if (graph[a][b] != 0) {
                    // cout << "been here" << endl;
                    current = col_ptr -> down;
                    for (int c = array[b]; c > 0; c--) {
                        current = current -> down;
                    }
                    if (count == 0) {
                        prev = current; // prev and current point to the first 1
                        head = current;
                    }
                    else {
                        current -> left = prev;
                        prev -> right = current;
                        prev = current;
                    }
                    count = 1; // only use to check if it is the first 1 in the array
                    array[b] = array[b]+1; // stores the number of 1s appeared in the column
                }
                else {} // do nothing
            }
            if (count != 0) {
                // circular linked list complete
                head -> left = current;
                current -> right = head;
                count = 0;
            }
            else {} // no 1s are found in the current row
        }
    }

    // make sure the chosen column to cover is only covered in the header
    // change the handler from int to node pointer to skip a step
    void cover(node* column) { // think, is it better to pass a pointer to the column rather than a name
        node* ptr = NULL;
        node* head = NULL;
        node* temp = NULL;
        head = column;
        ptr = head;
        // bypass column header
        head -> right -> left = head -> left;
        head -> left -> right = head -> right;
        while (ptr -> down != head) {
            ptr = ptr -> down;
            temp = ptr;
            while (temp -> right != ptr) {
                temp = temp -> right;
                temp -> up -> down = temp -> down;
                temp -> down -> up = temp -> up;
                // cout << "#1s remain in col: " << temp -> C << endl;
                temp -> C -> size = temp -> C -> size - 1;
            }
        }
        // return (ptr -> C);
    }

    void uncover(node* column) {
        // uncover column -> C
        node* ptr = NULL;
        node* head = NULL;
        node* temp = NULL;
        head = column;
        ptr = head;
                    // cout << "hello" << endl;
        while (ptr -> up != head){
            ptr = ptr -> up;
            temp = ptr;
            while (temp -> left != ptr) {
                temp = temp -> left;
                temp -> up -> down = temp;
                temp -> down -> up = temp;
                temp -> C -> size = temp -> C -> size + 1;
            }
        }
        // re-connect column header
        head -> left -> right = head;
        head -> right -> left = head;
    }

    void print_sol_new() {
        int result[N][N] = {0};
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                result[i][j] = 0;
            }
        }
        int row, pos, val;
        // cout << O.size() << endl;
        // cout << "result has row: ";
        for (node* n : O) {
            if (n != NULL) {
                int row = n -> row;
                int val = (row / (N*N)) + 1;
                int pos = row % (N*N);
                result[pos/N][pos%N] = val;
                cout << n->row << " " ;
            }
        }
        cout << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << " " << result[i][j];
            }
            cout << endl;
        }
    }

    int search(int k) { // recursive with backtrack
        // loop from the first column to the last to make sure all possible solutions are found
        if (h -> right == h) {
            cout << "result found" << endl;
            print_sol_new();
            return 1;
        }
        else {
            // cout << "been here" << endl;
            node* ptr = NULL;
            node* Col = NULL;
            Col = h -> right;
            // cout << "searching with column: " << Col -> name << endl;
            ptr = Col;
            cover(Col);

            while (ptr -> down != Col){
                ptr = ptr -> down;
                O.push_back(ptr);
                // cout << "store column O["<< O.size()-1 <<"] with: " << O[O.size()-1]->row << endl;
                node* temp = NULL;
                temp = ptr;
                while (temp -> right != ptr){
                    // cout << temp -> row << " --";
                    temp = temp -> right;
                    // cout << "column to cover: " << temp -> C -> name << endl;
                    cover(temp -> C);
                }
                // cout << "next search k = " << k+1 << " " << endl;
                search(k+1);

                ptr = O[k];
                node* un_ptr = ptr;
                // node* col = ptr -> C;
                // cout << col -> name << endl;
                while (un_ptr -> left != ptr) {
                    un_ptr = un_ptr -> left;
                    uncover(un_ptr->C);
                }
                O.pop_back();
            }
            // cout << "answer not found, roll back" << endl;
            uncover(Col);
            return 0;
        }
    }

    void complete_cover (int col) {
        node* ptr = h;
        node* head = NULL;
        node* temp = NULL;
        while (ptr -> name != col) {
            ptr = ptr -> right;
        }
        head = ptr;
        // bypass column header
        head -> right -> left = head -> left;
        head -> left -> right = head -> right;
        while (ptr -> down != head) {
            ptr = ptr -> down;
            temp = ptr;
            while (temp -> right != ptr) {
                temp = temp -> right;
                temp -> up -> down = temp -> down;
                temp -> down -> up = temp -> up;
                // cout << "#1s remain in col: " << temp -> C << endl;
                temp -> C -> size = temp -> C -> size - 1;
            }
        }
        // return (ptr -> C);
    }
};


int mx_build_new (int puzzle[N][N], int num_row, int num_col, int (*graph)[324]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int val = puzzle[i][j];
            int pos = i*N+j;
            // int row = N*N*i;
            int block = S*(i/S) + j/S;
            if (val == 0) {
                for (int k = 0; k < N; k++) {
                    int row = N*N*k;
                    // k*N: which number
                    graph[pos+row][i*N+k] = 1;
                    graph[pos+row][N*N+j*N+k] = 1;
                    graph[pos+row][2*N*N+block*N+k] = 1;
                    graph[pos+row][3*N*N+pos]=1;
                }
            }
            else { // absolutely correct
                int row = N*N*(val-1);
                graph[pos+row][i*N+(val-1)] = 1;
                graph[pos+row][N*N+j*N+(val-1)] = 1;
                graph[pos+row][2*N*N+block*N+(val-1)] = 1;
                graph[pos+row][3*N*N+pos] = 1;
            }
        }
    }
    // cover rows that are in collision with the puzzle
    // method one: correct
    for (int a = 0; a < N; a++) {
        for (int b = 0; b < N; b++) {
            if (puzzle[a][b] != 0) {
                int val = puzzle[a][b];
                int pos = a*N+b;
                int row = pos + N*N*(val-1);
                // find_row() in graph;
                for (int c = 0; c < num_col; c++) {
                    if (graph[row][c] != 0) {
                        // remove rows that are in collision
                        for (int l = 0; l < num_row; l++) {
                            if ((l != row) && (graph[l][c] != 0)) {
                                // set row l to zero
                                for (int m = 0; m < num_col; m++) {
                                    graph[l][m] = 0;
                                }
                            }
                            else {}
                        }
                    }
                    else {}
                }
            }
            else {}
        }
    }
    return 0;
}


int main() {
    int puzzle[N][N] =    {{5,3,0,0,7,0,0,0,0},
                           {6,0,0,1,9,5,0,0,0},
                           {0,9,8,0,0,0,0,6,0},
                           {8,0,0,0,6,0,0,0,3},
                           {4,0,0,8,0,3,0,0,1},
                           {7,0,0,0,2,0,0,0,6},
                           {0,6,0,0,0,0,2,8,0},
                           {0,0,0,4,1,9,0,0,5},
                           {0,0,0,0,8,0,0,7,9}};
    int num_row = 729;
    // pow(S,6);
    int num_col =  324;
    // 4*pow(S,4);
    int graph[729][324] = {0};
    ofstream file;
    file.open("result.txt");
    file << "number of rows: " << num_row << endl;
    file << "number of columns: " << num_col << endl;

    mx_build_new(puzzle, num_row, num_col, graph);

    for (int i = 0; i < num_row; i++) {
        file << "row " << i << ":";
        for (int j = 0; j < num_col; j++) {
            if (j%N == 0)
                file << "|" << graph[i][j];
            else
                file << graph[i][j];
        }
        file << endl;
    }
    file.close();
    doublylist dl;

    dl.generate(graph, num_row, num_col);
    dl.search(0);

    return 0;
}
