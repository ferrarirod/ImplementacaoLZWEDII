#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> lzwCompression(string str)
{
    unordered_map<string,int> dictionary;
    for(int i = 0;i < 256;i++)
    {
        char ch = i;
        string character(1,ch);
        dictionary[character] = i;
    }
    vector<int> codification;

    string previousChar = "";
    previousChar += str[0];
    for(int i = 0; i < str.length();i++)
    {
        string nextChar = "";
        if(i + 1 < str.length())
        {
            nextChar = str[i + 1];
        }

        if(dictionary.find(previousChar + nextChar) != dictionary.end())
        {
            previousChar += nextChar;
        }
        else
        {
            int newCode = dictionary.size();
            codification.push_back(dictionary[previousChar]);
            dictionary[previousChar + nextChar] = newCode;
            previousChar = nextChar;
        }
    }
    codification.push_back(dictionary[previousChar]);
    return codification;
}

string lzwDecompression(vector<int> codes)
{
    unordered_map<int,string> dictionary;
    for(int i = 0;i < 256;i++)
    {
        char ch = i;
        string character(1,ch);
        dictionary[i] = character;
    }

    int previousCharCode = codes[0];
    string previousChar = dictionary[previousCharCode];
    string nextChar = ""; 
    nextChar += previousChar[0];
    string tranlatedStr = previousChar;
    for(int i = 1;i < codes.size();i++)
    {
        int nextCharCode = codes[i];
        if(dictionary.find(nextCharCode) == dictionary.end())
        {
            previousChar = dictionary[previousCharCode];
            previousChar += nextChar;
        }
        else
        {
            previousChar = dictionary[nextCharCode];
        }

        tranlatedStr += previousChar;

        nextChar = ""; 
        nextChar += previousChar[0];

        int newChar = dictionary.size();
        dictionary[newChar] = dictionary[previousCharCode] + nextChar;

        previousCharCode = nextCharCode;
    }

    return tranlatedStr;
}

int main()
{
    cout << "Codificando bananabanabofana" << endl;
    vector<int> codes = lzwCompression("bananabanabofana");
    cout << "Codigos" << endl;
    for(int i = 0;i < codes.size();i++)
    {
        cout << codes[i] << endl;
    }

    cout << "Decodificando esses codigos" << endl;
    string translated = lzwDecompression(codes);

    cout << translated << endl;

    return 0;
}