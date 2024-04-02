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
        // This is how you read off the command line, not asked for but a nice feature to add
        fileName = argv[1];
        cout << "Input file name collected off the command line." << endl;
    }
    else
    {
        cout << "Input file was not on the command line, please enter a file name: ";
        getline(cin, fileName);
    }

    // Create the map of type string, int
    map<string, int> wordCountMap;

    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "Unable to open file " << fileName << endl;
        return -1;
    }

    string data;
    clock_t start = clock();

    // While there is data to be read in the file this loop will run
    while (file >> data)
    {
        //Each word will be sent though prepareWord and returned 
        string preparedWord = prepareWord(data);
        wordCountMap[preparedWord]++; // increment the count of the word occurrence
    }

    file.close();
    clock_t end = clock();

    // Return the time taken for this entire operation
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken to parse was " << duration << " seconds" << endl;

    // Create a ofstream file object 
    string outputFileName = "Map_OUT.txt";
    ofstream outputFile(outputFileName);

    if (!outputFile.is_open())
    {
        cout << "Unable to open output file " << outputFileName << endl;
        return -1;
    }

    // Showcasing how this extended for loop works similar to python if you've messed with it
    for (const auto &pair : wordCountMap)
    {
        outputFile << pair.first << "(" << pair.second << ")" << endl;
    }

    return 0;
}

string prepareWord(const string &word)
{
    string temp = "";

    // This for loop will run across the read in word, each letter(if it's an alphanumeric[0-9 V A-Z]) will be converted to it's lower case form, that way the words "wood" and "wood" appear as the same string value in the map
    for (int i = 0; i < word.length(); i++)
    {
        if (isalnum(word[i]))
        {
            temp += tolower(word[i]);
        }
    }
    return temp;
}
