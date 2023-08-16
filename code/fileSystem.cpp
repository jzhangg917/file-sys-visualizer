#include "fileSystem.h"
#include <iostream>

using namespace std;

// FileSystemNode methods
FileSystemNode::FileSystemNode(const string& name, bool isDirectory)
    : name(name), isDirectory(isDirectory) {}

const string& FileSystemNode::getName() const {
    return name;
}

void FileSystemNode::addChild(FileSystemNode* child) {
    children.push_back(child);
}

void FileSystemNode::display(int depth) {
    cout << string(2 * depth, ' ') << (isDirectory ? "[Dir] " : "[File] ") << name << endl;
    for (FileSystemNode* child : children) {
        child->display(depth + 1);
    }
}

const vector<FileSystemNode*>& FileSystemNode::getChildren() const {
    return children;
}

// FileSystem methods
FileSystem::FileSystem() {
    root = new FileSystemNode("Root", true);
    currentDirectory = root;
    directoryMap["Root"] = root;
}

FileSystem::~FileSystem() {
    deleteFileSystem(root);
}

void FileSystem::createDirectory(const string& name) {
    FileSystemNode* newDirectory = new FileSystemNode(name, true);
    currentDirectory->addChild(newDirectory);
    directoryMap[name] = newDirectory;
}

void FileSystem::createFile(const string& name) {
    FileSystemNode* newFile = new FileSystemNode(name, false);
    currentDirectory->addChild(newFile);
}

void FileSystem::changeDirectory(const string& name) {
    if (directoryMap.find(name) != directoryMap.end()) {
        currentDirectory = directoryMap[name];
    } else {
        cout << "Directory not found: " << name << endl;
    }
}

void FileSystem::displayCurrentDirectory() {
    cout << "Current Directory: " << currentDirectory->getName() << endl;
    currentDirectory->display();
}

void FileSystem::deleteFileSystem(FileSystemNode* node) {
    for (FileSystemNode* child : node->getChildren()) {
        deleteFileSystem(child);
    }
    delete node;
}
