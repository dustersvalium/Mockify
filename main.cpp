#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct User {
    string username;
    string password;
};
//Function to diplay playlist songs
void displayPlaylist(const vector<string>& playlist) {
    for (int i = 0; i < playlist.size(); i++) {
        cout << i + 1 << ". " << playlist[i] << endl;
    }
}
//Function to save playlist in file of respective user
void savePlaylist(const string& username, const vector<string>& playlist) {
    string fileName = username + "_playlist.txt";
    ofstream file(fileName);
    if (file.is_open()) {
        for (const string& song : playlist) {
            file << song << endl;
        }
        file.close();
        cout << "Your playlist has been saved to " << fileName << ".\n";
    } else {
        cout << "Error: Unable to save the playlist to a file.\n";
    }
}
//Function to load playlist in respective user's file
void loadPlaylist(const string& username, vector<string>& playlist) {
    string fileName = username + "_playlist.txt";
    ifstream file(fileName);
    if (file.is_open()) {
        string song;
        while (getline(file, song)) {
            playlist.push_back(song);
        }
        file.close();
        cout << "Your playlist has been loaded from " << fileName << ".\n";
    } else {
        cout << "No saved playlist found for " << username << ". Starting with an empty playlist.\n";
    }
}
//Function to shuffle order of songs in playlst
void shufflePlaylist(vector<string>& playlist) {
    random_shuffle(playlist.begin(), playlist.end());
    cout << "Your playlist has been shuffled.\n";
}
//Function to add, remove or shuffle songs in the playlist
void editPlaylist(vector<string>& playlist) {
    char editChoice;
    while (true) {
        cout << "Would you like to edit the playlist ('+' to add a song, '-' to remove a song, 'S' to shuffle, or 'XXX' to save and exit): ";
        cin >> editChoice;
        if (editChoice == '+') {
            cout << "Enter the name of the song you'd like to add: ";
            string song;
            cin.ignore();
            getline(cin, song);
            playlist.push_back(song);
        } else if (editChoice == '-') {
            cout << "Enter the number of the song you'd like to delete: ";
            int place;
            cin >> place;
            if (place >= 1 && place <= playlist.size()) {
                playlist.erase(playlist.begin() + place - 1);
            } else {
                cout << "Invalid song number. No song was removed.\n";
            }
        } else if (editChoice == 'S' || editChoice == 's') {
            shufflePlaylist(playlist);
        } else if (editChoice == 'X' || editChoice == 'x') {
            break;
        }
        displayPlaylist(playlist);
    }
}

int main() {
    const int num_songs = 10;
    vector<string> playlist;

    vector<User> userlist;
    userlist.push_back({ "PrkrVrs24", "2426" });
    userlist.push_back({ "SpheSnt15", "8915" });

    srand(time(nullptr));

    cout << "\nWELCOME TO MOCKIFY, THE ONE-STOP SHOP FOR ALL YOUR MUSIC\n";
    cout << "♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫\n";

    bool logout = true;

    while (logout) {
        string userName;
        string password;

        cout << "Please enter your username: ";
        cin >> userName;

        User* currentUser = nullptr;
        for (User& user : userlist) {
            if (userName == user.username) {
                currentUser = &user;
                break;
            }
        }

        if (currentUser != nullptr) {
            loadPlaylist(userName, playlist); // Load the playlist from a file
            cout << "Please enter your password: ";
            cin >> password;
            if (password == currentUser->password) {
                cout << "Hey " << userName << ", welcome back. Here's a list of all songs on your shared playlist:\n";
                cout << "♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫♩♭♫\n";
                displayPlaylist(playlist);
                editPlaylist(playlist);
                savePlaylist(userName, playlist); // Save the updated playlist to a file
            } else {
                cout << "Sorry, your password is incorrect. Please try again.\n";
            }

            char choice;
            cout << "Do you want to log in as another user (Y/N)? ";
            cin >> choice;
            if (choice == 'N' || choice == 'n') {
                logout = false;
            }
            playlist.clear();
        } else {
            cout << "Incorrect username. Please try again.\n";
        }
    }

    return 0;
}



