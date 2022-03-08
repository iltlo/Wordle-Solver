#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "wordle.hpp"

using namespace std;

void getResult(string attempt, string result, char (&exactpo)[5], vector< vector<char> > &eChar, vector<char> &nChar, vector<char> &ylDupe){
    for (int i=0; i<5; i++){
        if  (result[i] == 'g')
            exactpo[i] = attempt[i];
        if (result[i] == 'y')
            eChar[i].push_back(attempt[i]);
        if (result[i] == 'b')
            nChar.push_back(attempt[i]);
    }

    map< string, int> mymap;
    for (int i=0; i<5; i++)
        mymap[string(1,attempt[i])+result[i]]++; //string constructer function, then combine 2 char into a string
    char rptMpChar; //repeated map char
    map<string, int>::iterator it; 
    for (it = mymap.begin(); it != mymap.end(); it++){
        if (it->second > 1){ //if the map repeats
            rptMpChar = it->first[0]; //get the repeated attempt char
            if (it->first[1]=='y') ylDupe.push_back(rptMpChar);
        }
    }
    
}

void green(int count, vector<string> &psblWords, char (&exactpo)[5]){
    int status=0;
    if (count == 1){
        for (int i=0; i<5; i++){ //psblWords initialized
            if (exactpo[i] != 0){
                for (int k=0; k<5390; k++){
                    if (exactpo[i] == Dict[k][i])
                        psblWords.push_back(Dict[k]);
                }
                status=i;
                break;
            }
        }
    }
    if (status != 4){ //erase from psblWords after initialized
        for (int i=status; i<5; i++){
            if (exactpo[i] != 0){
                for (int k=0; k<psblWords.size(); k++){
                    if (exactpo[i] != psblWords[k][i]){
                        psblWords.erase(psblWords.begin()+k);
                        if (k>=0) --k;
                    }
                }
            }
        }
    }
    if (psblWords.size() == 0 && count == 1) psblWords=Dict;
}

void yellow(vector<string> &psblWords, vector< vector<char> > &eChar){
    for (int i=0; i<5; i++){ //i is the index of that char in a 5-chars word
        for (int k=0; k<eChar[i].size(); k++){
            for (int x=0; x<psblWords.size(); x++){
                if (eChar[i][k] == psblWords[x][i] || psblWords[x].find(eChar[i][k]) == string::npos){ //char at same wrong position, or does not exist
                    psblWords.erase(psblWords.begin()+x);
                    if (x>=0) --x;
                }
            }
        }
    }
}

void black(vector<string> &psblWords, vector<char> &nChar, string &result){
    for (int i=0; i<nChar.size(); i++){
        for (int k=0; k<psblWords.size(); k++){
            size_t findChar = psblWords[k].find(nChar[i]);
            if ( findChar!=string::npos && result[findChar]!='g'){ //using string::find(), shouldnt delete positions in green
                psblWords.erase(psblWords.begin()+k);
                if (k>=0) --k;
            }
        }
    }
}

void yellowDupe(vector<string> &psblWords, vector<char> &ylDupe){
    for (int i=0; i<ylDupe.size(); i++){
        for (int k=0; k<psblWords.size(); k++){
            string str=psblWords[k];
            size_t firstOcc = str.find(ylDupe[i]); //size_t: unsigned int type
            size_t secondOcc = (firstOcc!=string::npos ? str.find(ylDupe[i], firstOcc+1) : string::npos );
            if (secondOcc==string::npos){
                psblWords.erase(psblWords.begin()+k); //only psblWords with 2 occurance of ylDupe char left
                if (k>=0) --k;
            }
        }
    }
}

void showStat(const string attempt, const char (exactpo)[5], const vector< vector<char> > eChar, const vector<char> nChar, const vector<char> ylDupe){
    cout << "\nattempt ";
    for (int i=0; i<5; i++)
        cout << i << ":" << attempt[i] << ' ';
    cout << endl;

    cout << "exactpo ";
    for (int i=0; i<5; i++)
        if (exactpo[i]!=0)
            cout << i << ":" << exactpo[i] << ' ';
    cout << endl;

    cout << "eChar   ";
    for (int i=0; i<5; i++)
        for (int k=0; k<(eChar[i]).size(); k++)
            cout << i << ":" << eChar[i][k] << ' ';
    cout << endl;

    cout << "nChar   ";
    for (int i=0; i<nChar.size(); i++)
        cout << i << ":" << nChar[i] << ' ';
    cout << endl;

    cout << "ylDupe  ";
    for (int i=0; i<ylDupe.size(); i++)
        cout << i << ":" << ylDupe[i] << ' ';
    cout << "\n\n";
}

void showSuggestions(const vector<string> psblWords){
    cout << "\nSuggestions:" << endl;
    for (int i=0; i<psblWords.size(); i++)
        cout << psblWords[i] << endl;
    cout << psblWords.size() << " choices\n" << endl;
}

int main(){
    string attempt, result;
    char exactpo[5] = {0};
    vector<string> psblWords;
    vector<char> nChar; //nChar is the char shown black
    vector< vector<char> > eChar(5); //eChar is char shown yellow
    vector<char> ylDupe; //ylDupe is duplicates chars both shown yellow
    int count=1;

    cout << "Your attempt: ";
    cin >> attempt;
    cout << "Result: ";
    while (cin>>result && result!="ggggg"){

        getResult(attempt, result, exactpo, eChar, nChar, ylDupe);

        green(count, psblWords, exactpo); 
        count++;
        yellow(psblWords, eChar);
        black(psblWords, nChar, result);
        yellowDupe(psblWords, ylDupe);

        // showStat(attempt, exactpo, eChar, nChar, ylDupe);
        showSuggestions(psblWords);

        cout << "Your attempt: ";
        cin>>attempt;
        cout << "Result: ";
    }
    cout << "\nCongratulations!!! Your solved this Wordle in " << count << " attempts~\n" << endl;
}