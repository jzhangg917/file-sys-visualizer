#include "fileSystem.h"
#include <iostream>

using namespace std;

int main() {
    FileSystem fileSystem;

    while (true) {
        cout << "1. Create Directory\n";
        cout << "2. Create File\n";
        cout << "3. Change Directory\n";
        cout << "4. Display Current Directory\n";
        cout << "5. Exit\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        string name;
        switch (choice) {
            case 1:
                cout << "Enter directory name: ";
                cin >> name;
                fileSystem.createDirectory(name);
                break;
            case 2:
                cout << "Enter file name: ";
                cin >> name;
                fileSystem.createFile(name);
                break;
            case 3:
                cout << "Enter directory name: ";
                cin >> name;
                fileSystem.changeDirectory(name);
                break;
            case 4:
                fileSystem.displayCurrentDirectory();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }

    return 0;
}
