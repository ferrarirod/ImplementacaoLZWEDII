#include <iostream>
#include <fstream>
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

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        cout << "ERRO: Esperando os seguinte parametros: ./<nome do executavel> <diretorio do .txt com string>" << endl;
    }
    else
    {
        cout << "Lendo arquivo..." << endl;
        ifstream file;
        file.open(argv[1]);
        if(file.is_open())
        {
            string str;
            while (getline(file,str))
            {
                cout << "Codificando " << str << "..." << endl;
                vector<int> codes = lzwCompression(str);
                bool archive;
                cout << "Imprimir em:" << endl << "0 - Console" << endl << "1 - Arquivo" << endl;
                cout << "Opcao: ";
                cin >> archive;
                if(archive)
                {
                    ofstream outfile("codigos.txt",ios::app);
                    outfile << str << ": ";
                    for(int i = 0;i < codes.size();i++)
                    {
                        if(i != codes.size() - 1)
                        {
                            outfile << codes[i] << " ";
                        }
                        else
                        {
                            outfile << codes[i] << endl;
                        }
                    }
                    cout << "Codigos salvos em codigos.txt na pasta do projeto" << endl;
                    outfile.close();
                }
                else
                {
                    cout << str << ": ";
                    for(int i = 0;i < codes.size();i++)
                    {
                        if(i != codes.size() - 1)
                        {
                            cout << codes[i] << " ";
                        }
                        else
                        {
                            cout << codes[i] << endl;
                        }
                    }   
                }

                bool decode;
                cout << "Decodificar?" << endl << "1 - Sim" << endl << "0 - Nao" << endl;
                cout << "Resposta: ";
                cin >> decode;
                if(decode)
                {
                    string decoded = lzwDecompression(codes);
                    cout << "Codigos decodificados se converteram em:" << endl << decoded << endl;
                } 
            }

            file.close();
        }
        else
        {
            cout << "Arquivo nao aberto..." << endl;
        }
    }
    return 0;
}