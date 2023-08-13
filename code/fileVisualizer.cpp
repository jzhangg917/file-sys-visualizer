#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class FileSystemNode {
public:
    FileSystemNode(const string& name, bool isDirectory) : name(name), isDirectory(isDirectory) {}

    const string& getName() const {
        return name;
    }

    void addChild(FileSystemNode* child) {
        children.push_back(child);
    }

    void display(int depth = 0) {
        cout << string(2 * depth, ' ') << (isDirectory ? "[Dir] " : "[File] ") << name << endl;
        for (FileSystemNode* child : children) {
            child->display(depth + 1);
        }
    }

    const vector<FileSystemNode*>& getChildren() const {
        return children;
    }

private:
    string name;
    bool isDirectory;
    vector<FileSystemNode*> children;
};

class FileSystem {
public:
    FileSystem() {
        root = new FileSystemNode("Root", true);
        currentDirectory = root;
        directoryMap["Root"] = root;
    }

    ~FileSystem() {
        deleteFileSystem(root);
    }

    void createDirectory(const string& name) {
        FileSystemNode* newDirectory = new FileSystemNode(name, true);
        currentDirectory->addChild(newDirectory);
        directoryMap[name] = newDirectory;
    }

    void createFile(const string& name) {
        FileSystemNode* newFile = new FileSystemNode(name, false);
        currentDirectory->addChild(newFile);
    }

    void changeDirectory(const string& name) {
        if (directoryMap.find(name) != directoryMap.end()) {
            currentDirectory = directoryMap[name];
        } else {
            cout << "Directory not found: " << name << endl;
        }
    }

    void displayCurrentDirectory() {
        cout << "Current Directory: " << currentDirectory->getName() << endl;
        currentDirectory->display();
    }

private:
    void deleteFileSystem(FileSystemNode* node) {
        for (FileSystemNode* child : node->getChildren()) {
            deleteFileSystem(child);
        }
        delete node;
    }

    FileSystemNode* root;
    FileSystemNode* currentDirectory;
    unordered_map<string, FileSystemNode*> directoryMap;
};

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
