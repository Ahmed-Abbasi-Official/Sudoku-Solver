#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
using namespace std;

struct Container
{
    unsigned code;
    unsigned size;
    float weight;
};

// Global container yard (vector of stacks)
vector<stack<Container>> yard;

// Function prototypes
void saveToFile(const string &filename);
void loadFromFile(const string &filename);

int main()
{
    system("color 3");

    unsigned numYards;
    cout << "Enter the number of yards (stacks): ";
    cin >> numYards;

    yard.resize(numYards); // Initialize vector with empty stacks

    int choice;
    do
    {
        system("cls");
        cout << "**** CONTAINER YARD SYSTEM ****" << endl;
        cout << "1 - Add Container" << endl;
        cout << "2 - Remove Container" << endl;
        cout << "3 - View Top Container" << endl;
        cout << "4 - Show All Yards" << endl;
        cout << "5 - Save Containers to File" << endl;
        cout << "6 - Load Containers from File" << endl;
        cout << "9 - Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1)
        {
            unsigned yardNum;
            cout << "Enter yard number: ";
            cin >> yardNum;
            if (yardNum >= yard.size())
            {
                cout << "Invalid yard number!" << endl;
                system("pause");
                continue;
            }

            Container c;
            cout << "Enter container code: ";
            cin >> c.code;
            cout << "Enter container size: ";
            cin >> c.size;
            cout << "Enter container weight: ";
            cin >> c.weight;

            yard[yardNum].push(c);
            cout << "Container added successfully!" << endl;
            system("pause");
        }
        else if (choice == 2)
        {
            unsigned yardNum;
            cout << "Enter yard number: ";
            cin >> yardNum;
            if (yardNum >= yard.size() || yard[yardNum].empty())
            {
                cout << "Yard is empty or invalid!" << endl;
                system("pause");
                continue;
            }

            Container c = yard[yardNum].top();
            yard[yardNum].pop();
            cout << "Removed Container:\n";
            cout << "Code: " << c.code << "\nSize: " << c.size << "\nWeight: " << c.weight << endl;
            system("pause");
        }
        else if (choice == 3)
        {
            unsigned yardNum;
            cout << "Enter yard number: ";
            cin >> yardNum;
            if (yardNum >= yard.size() || yard[yardNum].empty())
            {
                cout << "Yard is empty or invalid!" << endl;
            }
            else
            {
                Container c = yard[yardNum].top();
                cout << "Top Container in Yard " << yardNum << ":\n";
                cout << "Code: " << c.code << "\nSize: " << c.size << "\nWeight: " << c.weight << endl;
            }
            system("pause");
        }
        else if (choice == 4)
        {
            for (unsigned i = 0; i < yard.size(); ++i)
            {
                cout << "Yard " << i << ":" << endl;
                if (yard[i].empty())
                {
                    cout << "  Empty yard." << endl;
                }
                else
                {
                    stack<Container> temp = yard[i]; // Copy to iterate
                    while (!temp.empty())
                    {
                        Container c = temp.top();
                        temp.pop();
                        cout << "  Code: " << c.code << ", Size: " << c.size << ", Weight: " << c.weight << endl;
                    }
                }
                cout << endl;
            }
            system("pause");
        }
        else if (choice == 5)
        {
            saveToFile("containers.txt");
            system("pause");
        }
        else if (choice == 6)
        {
            loadFromFile("containers.txt");
            system("pause");
        }
        else if (choice != 9)
        {
            cout << "Invalid option! Try again!" << endl;
            system("pause");
        }

    } while (choice != 9);

    cout << "Exiting the program." << endl;
    return 0;
}

// Save containers to file
void saveToFile(const string &filename)
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cout << "Error opening file for writing." << endl;
        return;
    }

    outFile << yard.size() << endl;
    for (unsigned i = 0; i < yard.size(); ++i)
    {
        outFile << yard[i].size() << endl;
        stack<Container> temp = yard[i];
        vector<Container> reverseStack;

        while (!temp.empty())
        {
            reverseStack.push_back(temp.top());
            temp.pop();
        }

        // Reverse to maintain correct order
        for (int i = reverseStack.size() - 1; i >= 0; --i)
        {
            outFile << reverseStack[i].code << " " << reverseStack[i].size << " " << reverseStack[i].weight << endl;
        }
    }

    cout << "Containers saved successfully to '" << filename << "'." << endl;
}

// Load containers from file
void loadFromFile(const string &filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cout << "Error opening file for reading." << endl;
        return;
    }

    unsigned numYards;
    inFile >> numYards;
    yard.clear();
    yard.resize(numYards);

    for (unsigned i = 0; i < numYards; ++i)
    {
        unsigned stackSize;
        inFile >> stackSize;
        vector<Container> tempStack;

        for (unsigned j = 0; j < stackSize; ++j)
        {
            Container c;
            inFile >> c.code >> c.size >> c.weight;
            tempStack.push_back(c);
        }

        // Push back into stack in correct order
        for (unsigned k = 0; k < tempStack.size(); ++k)
        {
            yard[i].push(tempStack[k]);
        }
    }

    cout << "Containers loaded successfully from '" << filename << "'." << endl;
}
