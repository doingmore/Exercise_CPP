#include <iostream>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
    string input;
    getline(cin, input);
    stringstream stream(input);
    int oneNumber{ 0 };
    set<int> listNumbers;
    int counter{ 0 };
    while (stream >> oneNumber)
    {
        listNumbers.insert(oneNumber);
    }

    set<int>::iterator it = listNumbers.end();
    it--;
    for (unsigned int i=listNumbers.size(); i>0; i--)
    {
        if (counter < 3)
        {
        cout << *it << " " << '\n';
        }
        else
        {
            break;
        }
        counter++;
        it--;
    }
    return 0;
}