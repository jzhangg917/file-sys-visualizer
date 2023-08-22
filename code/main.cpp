#include "fileSystem.h"
#include <iostream>
#include <vector> // Include for vector

using namespace std;

int main() {
    FileSystem fileSystem;

    while (true) {
        cout << "File System Simulation\n";
        cout << "-----------------------\n";
        cout << "1. Create Directory\n";
        cout << "2. Create File\n";
        cout << "3. Change Directory\n";
        cout << "4. Display Current Directory\n";
        cout << "5. Copy a File\n";
        cout << "6. Move a File\n";
        cout << "7. Delete a Node (File/Directory)\n";
        cout << "8. Search for Files/Directories\n";
        cout << "9. Set File Metadata (Define this method in FileSystem class)\n";
        cout << "10. Update File Metadata (Define this method in FileSystem class)\n";
        cout << "11. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(); // Consume the newline character

        string name, destination;
        vector<FileSystemNode*> results; // Moved this declaration here

        switch (choice) {
            case 1:
                cout << "Enter directory name: ";
                getline(cin, name);
                fileSystem.createDirectory(name);
                cout << "Directory '" << name << "' created.\n";
                break;
            case 2:
                cout << "Enter file name: ";
                getline(cin, name);
                fileSystem.createFile(name);
                cout << "File '" << name << "' created.\n";
                break;
            case 3:
                cout << "Enter directory name: ";
                getline(cin, name);
                fileSystem.changeDirectory(name);
                cout << "Changed directory to '" << fileSystem.getCurrentDirectoryName() << "'.\n";
                break;
            case 4:
                cout << "Current Directory: " << fileSystem.getCurrentDirectoryName() << endl;
                fileSystem.displayCurrentDirectory();
                break;
            case 5:
                cout << "Enter the name of the source file: ";
                getline(cin, name);
                cout << "Enter the name of the destination directory: ";
                getline(cin, destination);
                fileSystem.copyFile(name, destination);
                cout << "File '" << name << "' copied to '" << destination << "'.\n";
                break;
            case 6:
                cout << "Enter the name of the source file: ";
                getline(cin, name);
                cout << "Enter the name of the destination directory: ";
                getline(cin, destination);
                fileSystem.moveFile(name, destination);
                cout << "File '" << name << "' moved to '" << destination << "'.\n";
                break;
            case 7:
                cout << "Enter the name of the node to delete: ";
                getline(cin, name);
                fileSystem.deleteNode(name);
                cout << "Node '" << name << "' deleted.\n";
                break;
            case 8:
                cout << "Enter the search term: ";
                getline(cin, name);
                results = fileSystem.search(name); // Assign search results to the vector
                cout << "Matching files/directories:\n";
                for (const FileSystemNode* node : results) {
                    cout << node->getName() << endl;
                }
                break;
            case 9:
                // Implement the setFileMetadata method in the FileSystem class
                // Then use it here
                cout << "Enter the name of the file to set metadata: ";
                getline(cin, name);
                time_t creationTime, fileLastModifiedTime;
                cout << "Enter the creation time (UNIX timestamp): ";
                cin >> creationTime;
                cout << "Enter the last modified time (UNIX timestamp): ";
                cin >> fileLastModifiedTime;
                fileSystem.setFileMetadata(name, creationTime, fileLastModifiedTime);
                cout << "Metadata for '" << name << "' updated.\n";
                break;
            case 10:
                // Implement the updateFileMetadata method in the FileSystem class
                // Then use it here
                cout << "Enter the name of the file to update metadata: ";
                getline(cin, name);
                time_t updatedLastModifiedTime;
                cout << "Enter the new last modified time (UNIX timestamp): ";
                cin >> updatedLastModifiedTime;
                fileSystem.updateFileMetadata(name, updatedLastModifiedTime);
                cout << "Metadata for '" << name << "' updated.\n";
                break;
            case 11:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }

    return 0;
}
