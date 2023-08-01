// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
//  mySQL.hpp
//  p3
//
//  Created by Star is cute AF on 10/30/20.
//  Copyright © 2020 Sida Zhong. All rights reserved.
//

#ifndef mySQL_hpp
#define mySQL_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <getopt.h>
#include <fstream>
#include <unordered_map>
#include "TableEntry.h"
#include "xcode_redirect.hpp"

using namespace std;
#endif /* mySQL_hpp */

//class of comparator for delete
//In the 3-way split, would you like to write almost identical code 3 times, or write a helper?  What would you pass to the helper?  A functor!  That final helper would have to be templated, because it might receive one of three different functor types, one each for <, =, and >.  Why not have one and have it remember the character?  Because then your functor would always first have to do a split on the character, which makes is slower than any of my 3 functors that are each written for a specific operation.  Why have functors at all?  Because you want the STL to help you delete rows, and it needs a functor to help it do it's job.

//4 way split--int double bool string
//3 way split-- > = <
// if you're a Less Than functor, you do <.
//template <typename T>
class compare_less {
public:
    compare_less(TableEntry val_in, int col_in): val(val_in), col_loc(col_in) { }
    
    bool operator() (vector<TableEntry> &v) {
        return v[(size_t)col_loc] < val;
        }
        
private:
     TableEntry val;
    int col_loc;
};

class compare_great {
public:
    compare_great(TableEntry val_in, int col_in): val(val_in),
    col_loc(col_in) { }
    
    bool operator() (vector<TableEntry> &v) {
        return v[(size_t)col_loc] > val;
        }
        
private:
     TableEntry val;
        int col_loc;
};

class compare_equal {
public:
    compare_equal(TableEntry val_in, int col_in): val(val_in),
    col_loc(col_in) { }
    
    bool operator() (vector<TableEntry> &v) {
        return v[(size_t)col_loc] == val;
        }
        
private:
     TableEntry val;
        int col_loc;
      
};


class table {
public:
    table(): num_col(0), num_row(0), has_gen(false), has_bst_col(-1), has_hash_col(-1){
        
    }
    
    //create
    void create_table(string t_name);
    
    //insert into
    void insert_into();
    
    //delete from
    void delete_from(unordered_map<string, table>& hashing);
    
    int find_col_num (const string &colname,const string & table_name,unordered_map<string, table>& hashing) {
        
        if (hashing[table_name].col_each.find(colname)
            == hashing[table_name].col_each.end()) {
            cout << "Error: " << colname << " does not name a column in " << table_name <<"\n";
            string temp;
            getline(cin, temp);
            return -1;
        }
        else {
            size_t cole
            = hashing[table_name].col_each[colname];
            return (int)cole;
        }
        
    }
    
    void op_helper(char op,TableEntry val, int which_col);
    
    //generate index
    void generate_index(const string &indextype, const string & colname,unordered_map<string, table>& hashing, bool is_update);
    
    void clear_it();
    
    //print
    void print(bool is_quiet,unordered_map<string, table>& hashing);
    
    void p_row(vector<size_t> &col_p, TableEntry en, const char &op, size_t which_col,bool is_quie);
    
    void p_match_row(size_t row, vector<size_t> &col_p,bool is_join);
    
    //join
    void join(const string &t_name,unordered_map<string, table>& hashing,bool is_quiet);
    
    void print_join(const string &t_name1, const string &t_name2,unordered_map<string, table>& hashing, vector<size_t> &which_tab);
    
    //remove
    void remove(unordered_map<string, table>& hashing);
    
    //quit
    void quit();
    
    //comment,what is this
    void comment();
    
    void resize_table_graph(int row, int col);
    //private
    
    void helper_func_for_test(unordered_map<string, table>& hashing);
    
private:
    string table_name;
    int num_col;
    int num_row;
    vector<vector<TableEntry>> table_graph;
    vector<EntryType> col_type;
//    vector<string> col_name;
    unordered_map<string, size_t> col_each;
    //unordered_map<string, size_t> col_each;
    
    bool has_gen;
    int has_bst_col;
    int has_hash_col;
    string gen_col_name;
    
    //delete and insert need to change
    unordered_map<TableEntry, vector<size_t>> gen_hash;
    map<TableEntry, vector<size_t>> gen_bst;
};

//bool quit_it = false;
void read_command(string mode, bool is_quiet, unordered_map<string, table>& hashing);

