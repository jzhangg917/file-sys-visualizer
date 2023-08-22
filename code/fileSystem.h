#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>
#include <unordered_map>
#include <ctime> // Include for time_t

using namespace std;

class FileSystemNode {
public:
    FileSystemNode(const string& name, bool isDirectory);

    const string& getName() const;

    void addChild(FileSystemNode* child);

    void display(int depth = 0);

    const vector<FileSystemNode*>& getChildren() const;

    bool isDirectoryNode() const;

    // Define a method to set the last modified time
    void setLastModifiedTime(time_t lastModified);

private:
    string name;
    bool isDirectory;
    vector<FileSystemNode*> children;
    time_t lastModifiedTime; // Store last modified time
};

class FileSystem {
public:
    FileSystem();

    ~FileSystem();

    void createDirectory(const string& name);

    void createFile(const string& name);

    void changeDirectory(const string& name);

    void displayCurrentDirectory();

    void copyFile(const string& sourceName, const string& destinationName);
    void moveFile(const string& sourceName, const string& destinationName);
    void deleteNode(const string& name);
    vector<FileSystemNode*> search(const string& name);

    // Define a method to set file metadata, including creation time and last modified time
    void setFileMetadata(const string& name, time_t creationTime, time_t lastModifiedTime);

    // Define a method to update file metadata, specifically the last modified time
    void updateFileMetadata(const string& name, time_t lastModifiedTime);

    // Define a method to get the current directory name
    string getCurrentDirectoryName() const;

private:
    void deleteFileSystem(FileSystemNode* node);

    FileSystemNode* root;
    FileSystemNode* currentDirectory;
    unordered_map<string, FileSystemNode*> directoryMap;
};

#endif // FILESYSTEM_H
