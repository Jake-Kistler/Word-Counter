#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <map>

using namespace std;

string prepareWord(const string &word);

int main(int argc, char **argv)
{
    string fileName;

    cout << "Welcome to the word counter, using a map!" << endl;

    if (argc == 2)
    {
        fileName = argv[1];
        cout << "Input file name collected off the command line." << endl;
    }
    else
    {
        cout << "Input file was not on the command line, please enter a file name: ";
        getline(cin, fileName);
    }

    map<string, int> wordCountMap;

    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "Unable to open file " << fileName << endl;
        return -1;
    }

    string data;
    clock_t start = clock();

    while (file >> data)
    {
        string preparedWord = prepareWord(data);
        wordCountMap[preparedWord]++;
    }

    file.close();
    clock_t end = clock();

    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken to parse was " << duration << " seconds" << endl;

    string outputFileName = "Map_OUT.txt";
    ofstream outputFile(outputFileName);

    if (!outputFile.is_open())
    {
        cout << "Unable to open output file " << outputFileName << endl;
        return -1;
    }

    for (const auto &pair : wordCountMap)
    {
        outputFile << pair.first << "(" << pair.second << ")" << endl;
    }

    return 0;
}

string prepareWord(const string &word)
{
    string temp = "";

    for (int i = 0; i < word.length(); i++)
    {
        if (isalnum(word[i]))
        {
            temp += tolower(word[i]);
        }
    }
    return temp;
}
