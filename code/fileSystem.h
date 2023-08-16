#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class FileSystemNode {
public:
    FileSystemNode(const string& name, bool isDirectory);

    const string& getName() const;

    void addChild(FileSystemNode* child);

    void display(int depth = 0);

    const vector<FileSystemNode*>& getChildren() const;

private:
    string name;
    bool isDirectory;
    vector<FileSystemNode*> children;
};

class FileSystem {
public:
    FileSystem();

    ~FileSystem();

    void createDirectory(const string& name);

    void createFile(const string& name);

    void changeDirectory(const string& name);

    void displayCurrentDirectory();

private:
    void deleteFileSystem(FileSystemNode* node);

    FileSystemNode* root;
    FileSystemNode* currentDirectory;
    unordered_map<string, FileSystemNode*> directoryMap;
};

#endif // FILESYSTEM_H
