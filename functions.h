
#include <iostream>
#include <string>
#include <cstdlib> // for system function

using namespace std; // Add the using directive

class Song {
public:
    string title;
    string artist;
    string file;

    Song()
    {
        title = "Unknown";
        artist = "Unknown";
        file = "guitar.mp3";
    }
    Song(string Title,string Artist,string File)
    {
        title = Title;
        artist = Artist;
        file = File;
    }

    bool operator==(Song& other){
        return title == other.title || artist == other.artist;
    }
    Song& operator=(const Song& other) {
        if (this == &other) {
            return *this;
        }
        title = other.title;
        artist = other.artist;
        file = other.file;

        return *this;
    }

    void play() {
    string command = "mpg123 " + file;
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Playing: " << title << " by " << artist << endl;
    } else {
        cerr << "Error playing the song: " << title << " by " << artist << endl;
    }
}


};


class Node {
public:
    Song song; // Store Song objects
    Node *next;
    Node *prev;


    Node() {
        next = nullptr;
        prev = nullptr;
    }
    static Node *head;
    static Node *tail;
    static Node *current;

    void insert(Song song1) {
        Node* temp = new Node();
        temp->song = song1;

        if (head == nullptr) {
            temp->next = temp;
            temp->prev = temp;
            head = temp;
            tail = temp;
            tail->next = temp;
            current = temp;
        } else {
            temp->next = head;
            temp->prev = tail;
            head->prev = temp;
            tail->next = temp;
            head = temp;
        }
    }

void remove(Song &song1) {
    if (head == nullptr) {
        cout << "The playlist is empty. Cannot remove a song." << endl;
        return;
    }
    Node* temp = head;
    bool found = false;
    while (temp != nullptr) {
        if (temp->song == song1) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;

            if (temp == head) {
                head = temp->next;
            }
            if (temp == tail) {
                tail = temp->prev;
            }
            delete temp; // Deallocate memory
            found = true;
            break;
        }
        temp = temp->next;

        if (temp == head) {
            break;
        }
    }

    if (!found) {
        cout << "The song '" << song1.title << "' by '" << song1.artist << "' is not in the playlist." << endl;
    }
}

void viewPlaylist() {
        if (head == nullptr) {
            cout << "The playlist is empty." << endl;
            return;
        }

        Node* temp = head;
        cout << "Current Playlist:" << endl;
        do {
            cout << temp->song.title << " by " << temp->song.artist << endl;
            temp = temp->next;
        } while (temp != head);
    }

    void playNext() {
        if (current != nullptr) {
            current = current->next;
            cout << "Song playing:" << current->song.title << " by " << current->song.artist << endl;
            current->song.play();
        }
    }

    void playPrevious() {
        if (current != nullptr) {
            current = current->prev;
            cout << "Song playing:" << current->song.title << " by " << current->song.artist << endl;
            current->song.play();
        }
    }

    void playCurrent() {
        if (current != nullptr) {
            cout << "Song playing:" << current->song.title << " by " << current->song.artist << endl;
            current->song.play();
        }
    }


};

Node* Node::head = nullptr;
Node* Node::tail = nullptr;
Node* Node::current= nullptr;

