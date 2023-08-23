#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#define filepath "./docs/"
#define filetype ".txt"

using namespace std;

void doCreate(const string& filename);
void doAppend(const string& filename, const string word);
void doReplace(const string& filename, int idx, const string& word);
vector<string> split(const string& str, char delim);
void handle(const string& command);

const char delim = '\t';

int main()
{
    map<int, string> commands;
    ifstream infile("commands.txt");
    string line;
    
    if(!infile.is_open())
    {
        cerr << "Could not open the file" << endl;
        return EXIT_FAILURE;
    }
    
    while(getline(infile, line))
    {
        int spaceIdx = line.find_first_of(delim);
        if(spaceIdx != string::npos)
        {
            int key = stoi(line.substr(0, spaceIdx));
            string value = line.substr(spaceIdx + 1);
            commands[key] = value;
        }
    }

    infile.close();

    for(auto& pair: commands)
        handle(pair.second);

    return EXIT_SUCCESS;
}

void handle(const string& command)
{
    vector<string> sub = split(command, delim);
    if(sub[0] == "create")
        doCreate(sub[1]);
    if(sub[0] == "append")
        doAppend(sub[1], sub[2]);
    if(sub[0] == "replace")
        doReplace(sub[1], stoi(sub[2]), sub[3]);
}

vector<string> split(const string& str, char delim) {
    vector<string> elems;
    auto lastPos = str.find_first_not_of(delim, 0);
    auto pos = str.find_first_of(delim, lastPos);
    while (pos != string::npos || lastPos != string::npos) {
        elems.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delim, pos);
        pos = str.find_first_of(delim, lastPos);
    }
    return elems;
}

void doCreate(const string& filename)
{
    ofstream outfile;
    outfile.open(filepath + filename + filetype);
    outfile.close();
}

void doAppend(const string& filename, const string word)
{
    ofstream outfile(filepath + filename + filetype, ios::app);
    outfile << word << delim;
    outfile.close();
}

void doReplace(const string& filename, int idx, const string& word)
{
    fstream infile(filepath + filename + filetype, ios::in);
    stringstream buffer;
    buffer << infile.rdbuf();
    string str(buffer.str());
    infile.close();
    
    vector<string> words = split(str, delim);
    if(idx >= words.size())
    {
        cerr << "replace index out of range : " << filename << endl;
        return;
    }

    words[idx] = word;
    fstream outfile(filepath + filename + filetype, ios::out);
    for(int i = 0; i < words.size(); ++i)
    {
        outfile << words[i] << delim;
    }
    outfile.close();
}


