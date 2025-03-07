#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

int numDoubles = 0;
int numDuplicates = 0;
int totalWords = 0;

struct WordItem
{
    string word;
    int count;
};

void DoubleArraySize(WordItem* &wordArr, int &length)
{
    int newLength = length * 2;
    WordItem* newWordArr = new WordItem[newLength];
    for(int i = 0; i < length; i++)
    {
        newWordArr[i] = wordArr[i];
    }
    wordArr = newWordArr;
    length = newLength;
    numDoubles++;
}

void AddWord(WordItem *&wordArr, int &wordIndex, int &length, string nextWord)
{
    for(int i = 0; i < wordIndex; i++)
    {
        if(wordArr[i].word == nextWord)
        {
            wordArr[i].count++;
            numDuplicates++;
            return;
        }
    }
    if(wordIndex == length)
    {
        DoubleArraySize(wordArr, length);
    }
    wordArr[wordIndex] = *(new WordItem);
    wordArr[wordIndex].count = 1;
    wordArr[wordIndex].word = nextWord;
    wordIndex++;
}

void SortArray(WordItem *&list, int wordIndex)
{
    bool swapped;
    for (int i = 0; i < wordIndex - 1; i++) {
        swapped = false;
        for (int j = 0; j < wordIndex - i - 1; j++) {
            if (list[j].count < list[j + 1].count) {
                WordItem temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void GetTopN(WordItem wordArr[], int TopN)
{
    for(int i = 0; i < TopN; i++)
    {
        cout << wordArr[i].word << ": " << wordArr[i].count << endl;
    }
}

int main()
{
    int wordIndex = 0;
    int length = 1;
    WordItem* wordArr = new WordItem[length];
    int topN = 4;
    string filePath = "shakespeare.txt";
    ifstream fileStream(filePath);
    if(fileStream.is_open())
    {
        string currentLine;
        char delimter = ' ';
        while(getline(fileStream, currentLine))
        {
            string currentWord;
            stringstream lineStream(currentLine);

            while(getline(lineStream, currentWord, delimter))
            {
                totalWords++;
                AddWord(wordArr, wordIndex, length, currentWord);
            }
        }
        SortArray(wordArr, wordIndex);
        GetTopN(wordArr, topN);
        cout << "Array Doubles: " << numDoubles << endl;
        cout << "Unique Words: " << totalWords - numDuplicates << endl;
        cout << "Duplicate Words: " << numDuplicates << endl;
    }
    return 0;
}