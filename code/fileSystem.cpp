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

bool FileSystemNode::isDirectoryNode() const {
    return isDirectory;
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

void FileSystem::copyFile(const string& sourceName, const string& destinationName) {
    if (directoryMap.find(sourceName) != directoryMap.end() && directoryMap.find(destinationName) != directoryMap.end()) {
        FileSystemNode* sourceNode = directoryMap[sourceName];
        FileSystemNode* destinationNode = directoryMap[destinationName];

        if (destinationNode->isDirectoryNode() && sourceNode != destinationNode) {
            FileSystemNode* copyNode = new FileSystemNode(sourceNode->getName(), sourceNode->isDirectoryNode());
            destinationNode->addChild(copyNode);

            if (sourceNode->isDirectoryNode()) {
                for (FileSystemNode* child : sourceNode->getChildren()) {
                    copyFile(child->getName(), copyNode->getName());
                }
            }
        } else {
            cout << "Invalid destination. It should be a directory and not the same as the source." << endl;
        }
    } else {
        cout << "Source or destination not found." << endl;
    }
}

void FileSystem::moveFile(const string& sourceName, const string& destinationName) {
    copyFile(sourceName, destinationName);
    deleteNode(sourceName);
}

void FileSystem::deleteNode(const string& name) {
    if (directoryMap.find(name) != directoryMap.end()) {
        FileSystemNode* node = directoryMap[name];
        if (node != root) {
            deleteFileSystem(node);
            directoryMap.erase(name);
        } else {
            cout << "Cannot delete the root directory." << endl;
        }
    } else {
        cout << "Node not found." << endl;
    }
}

vector<FileSystemNode*> FileSystem::search(const string& name) {
    vector<FileSystemNode*> results;
    for (auto const& pair : directoryMap) {
        if (pair.first.find(name) != string::npos) {
            results.push_back(pair.second);
        }
    }
    return results;
}

void FileSystem::deleteFileSystem(FileSystemNode* node) {
    for (FileSystemNode* child : node->getChildren()) {
        deleteFileSystem(child);
    }
    delete node;
}
