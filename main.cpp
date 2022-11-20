#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


void display_word_to_screen(string word) {
    string border = "=";

    for(auto i : word) {
        border += "=";
    }

    cout << border << endl;
    cout << word << endl;
    cout << border << endl;
}

string get_magical_word_from_user() {
    string magical_word = "";

    cout << "Enter word for Player to guess: ";
    getline(cin, magical_word);
    cout << endl;

    return magical_word;
}

int get_max_num_tries() {
    int max_num_tries = 0;

    cout << "How many guesses does the player get? ";
    cin >> max_num_tries;
    cout << endl;

    return max_num_tries;

}

string setup_hidden_word(int length, string word) {
    // Will return the word with missing letters
    string hidden_word = "";
    
    for(int i = 0; i < length; i++) {
        if(word[i] == ' ') {
            hidden_word += ' ';
            continue;
        }

        hidden_word += "-";
    }

    return hidden_word;
}

map<char, vector<int>> setup_letter_index_mapping(string word) {
    // Gathers map of where each letter is based off of index
    // Ignores cases
    // Example:
    
    map<char, vector<int>> letter_to_index = {};
    
    // Populate initial mapping
    for(int i = 0; i < 1; i++) {
        vector<int> indexes = {};
        indexes.push_back(i);
        letter_to_index[tolower(word[i])] = indexes;
    }

    // Fill in rest of mapping
    for(int i = 1; i < word.size(); i++) {
        letter_to_index[tolower(word[i])].push_back(i);
    }

    return letter_to_index;
}

bool letter_exists_in_word(char letter, map<char, vector<int>> mapping) {
    if(mapping.find(tolower(letter)) == mapping.end()) {
        return false;
    }

    return true;
}

bool letter_already_found(char letter, string word) {
    if(word.find(letter) == string::npos) {
        return false;
    }

    return true;
}
string new_display_word(char correct_guess, string display_word, map<char, vector<int>> letter_map) {
    // Adds letter to the word hidden word
    // EX: --zz-a

    for(int index : letter_map[tolower(correct_guess)]) {
        display_word[index] = correct_guess;
    }

    return display_word;
}

int calculate_attempts_left(string hidden_word, string secret_word) {
    // Determines how many attempts are left to guess all the letters
    // based off of how many '-' are left
    int letters_left = 0;
    vector<char> letters_found = {};

    for(int i = 0; i < hidden_word.size(); i++) {
        if(hidden_word[i] == ' ' || hidden_word[i] == '-') {
            if(find(letters_found.begin(), letters_found.end(), secret_word[i]) == letters_found.end()) {
                letters_found.push_back(secret_word[i]);
                letters_left++;
            }
        }
    }

    return letters_left;
}
int main() {

    string secret_word = get_magical_word_from_user();
    string display_word = setup_hidden_word(secret_word.size(), secret_word);
    int MAX_NUM_TRIES = get_max_num_tries();

    map<char, vector<int>> letter_mapping = setup_letter_index_mapping(secret_word);
    
    while(calculate_attempts_left(display_word, secret_word) != 0) {
        //clear screen
        // Start loop
        char user_guess = '0';

        display_word_to_screen(display_word);
        cout << "Letter's left >> " << calculate_attempts_left(display_word, secret_word) << endl;
        
        cout << "Player guess: ";
        cin >> user_guess;

        cout << endl;

        if(letter_exists_in_word(user_guess, letter_mapping)) {
            if(letter_already_found(user_guess,display_word)) {
                cout << "**********************\n";
                cout << "LETTER ALREADY FOUND!" << endl;
                cout << "**********************\n";
            } else {
                cout << "****************************\n";
                cout << "CONGRATS YOU FOUND A LETTER!" << endl;
                cout << "****************************\n";
            }

            display_word = new_display_word(user_guess, display_word, letter_mapping); 
        }else {
            cout << "******************************\n";
            cout << "LETTER DOESN'T EXIST IN WORD!" << endl;
            cout << "******************************\n";
        }
    }

    return 0;
}
