#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Struct to store each item from the garage sale file
struct Item
{
    public:
        string type;
        int price;
        // true if for sale; false if wanted
        bool forSale;
};

int main()
{
    // Array for storing the item structs
    Item itemList[100];

    // initializing variables for the file stream, the length of the array, and each line from the file
    string line;
    int currentArrayEnd = -1;
    ifstream garageSale("garageSale.txt");

    // checking if the file is open
    if(garageSale.is_open())
    {
        cout << "Items Sold:" << endl;
        // looping over all the lines in the garage sale file
        while(getline(garageSale, line))
        {
            // cout << line << endl;
            // cout << "Items Sold" << endl;
            // Parses through and finds each comma and stores each section of data in the associated variables
            string type = line.substr(0,line.find(","));
            line.erase(0,line.find(",") + 1);
            bool forSale;
            if(line.substr(0,line.find(",")) == "for sale")
            {
                forSale = true;
            }else
            {
                forSale = false;
            }
            line.erase(0,line.find(",") + 1);
            float price = stoi(line);
            bool matchFound = false;
            // loops through all the existing items in the items array
            if(currentArrayEnd != -1)
            {
                // cout << currentArrayEnd << endl;
                for(int i = 0; i <= currentArrayEnd; i++)
                {
                    // cout << type << " " << price << endl;
                    // cout << itemList[i].type << " " << itemList[i].price << endl;
                    // checks if the current item from the array matches the current item from the file
                    if(itemList[i].forSale)
                    {
                        // cout << "For Sale" << endl;
                        if(!forSale && itemList[i].type == type && itemList[i].price <= price)
                        {
                            matchFound = true;
                        }
                    }else
                    {
                        // cout << "wanted" << endl;
                        if(forSale && itemList[i].type == type && itemList[i].price >= price)
                        {
                            matchFound = true;
                        }
                    }
                    // if a match is found the current item is removed from the array using the algorithm in the homework
                    // and breaks from the current loop
                    if (matchFound)
                    {
                        // cout << type << " " << price << endl;
                        // determines which item to print in the output based on weather or not it's for sale
                        if(forSale == true)
                        {
                            cout << currentArrayEnd << endl;
                        }else
                        {
                            cout << itemList[i].type << " " << itemList[i].price << endl;
                        }
                        
                        for(int j = i; j <= currentArrayEnd - 1; j++)
                        {
                            // cout << "removing " << itemList[j].type << " " << itemList[j].price << endl;
                            itemList[j] = itemList[j+1];
                        }
                        currentArrayEnd -= 1;
                        break;
                    }
                }
            }
            // if no match is found then the current line from the file is added to the end of the array
            if(!matchFound)
            {
                currentArrayEnd++;
                // cout << type << " adding " << price << endl;
                // cout << currentArrayEnd << endl;
                itemList[currentArrayEnd] = Item();
                itemList[currentArrayEnd].type = type;
                itemList[currentArrayEnd].forSale = forSale;
                itemList[currentArrayEnd].price = price;
            }
        }
        // Once all the lines in the file are read, all items still in the array are looped through and printed out
        cout << "Items remaining on the message board after reading all lines in the file:" << endl;
        // cout << currentArrayEnd << endl;
        for (int i = 0; i <= currentArrayEnd; i++)
        {
            
            if(itemList[i].forSale)
            {
                cout << itemList[i].type << ", " << "For Sale, " << itemList[i].price << endl;
            }else
            {
                cout << itemList[i].type << ", " << "Wanted, " << itemList[i].price << endl;
            }
        }
        // closing the garage sale file
        garageSale.close();
    }
    return 0;
}