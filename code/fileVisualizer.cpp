#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class FileSystemNode {
public:
    FileSystemNode(const string& name, bool isDirectory) : name(name), isDirectory(isDirectory) {}

    void addChild(FileSystemNode* child) {
        children.push_back(child);
    }

    void display(int depth = 0) {
        cout << string(2 * depth, ' ') << (isDirectory ? "[Dir] " : "[File] ") << name << endl;
        for (FileSystemNode* child : children) {
            child->display(depth + 1);
        }
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
    FileSystemNode* root;
    FileSystemNode* currentDirectory;
    unordered_map<string, FileSystemNode*> directoryMap;
};

int main() {
    FileSystem fileSystem;

    fileSystem.createDirectory("Documents");
    fileSystem.createFile("Resume.pdf");
    fileSystem.changeDirectory("Documents");
    fileSystem.createDirectory("Reports");
    fileSystem.changeDirectory("Reports");
    fileSystem.createFile("AnnualReport.pdf");

    fileSystem.changeDirectory("Root");
    fileSystem.createDirectory("Pictures");
    fileSystem.changeDirectory("Pictures");
    fileSystem.createDirectory("Vacation");
    fileSystem.changeDirectory("Vacation");
    fileSystem.createFile("Beach.jpg");
    fileSystem.createFile("Mountains.jpg");

    fileSystem.displayCurrentDirectory();

    // Clean up memory (not shown in detail)

    return 0;
}
