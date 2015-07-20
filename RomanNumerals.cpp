#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream> 
using namespace std;


/*
Rules for subtraction:

I can only be subtracted from V and X.
X can only be subtracted from L and C.
C can only be subtracted from D and M.
V, L, D and M can't be subtracted from any symbol.
At most one symbol can be subtracted from another symbol.
*/

string oneth(int num){
    string answer="";
    if(num<4){
        for(int i=0;i<num;i++)
            answer=answer+"I";
    }else if(num==4){
        answer="IV";
    }else if(num==5){
        answer="V";
    }else if(num<9){
        answer="V";
        for(int i=0; i<(num-5);i++){
            answer= answer+"I";
        }
    }else{
        answer = "IX";
    }
    return answer;
}

string tenth(int num){
    string answer="";
    if(num<40){
        for(int i=0;i<num;i=i+10)
            answer=answer+"X";
    }else if(num==40){
        answer="XL";
    }else if(num==50){
        answer="L";
    }else if(num<90){
        answer="L";
        for(int i=0; i<(num-50);i=i+10){
            answer= answer+"X";
        }
    }else{
        answer = "XC";
    }
    return answer;
}

string hundredth(int num){
    string answer="";
    if(num<400){
        for(int i=0;i<num;i=i+100)
            answer=answer+"C";
    }else if(num==400){
        answer="CD";
    }else if(num==500){
        answer="D";
    }else if(num<900){
        answer="D";
        for(int i=0; i<(num-500);i=i+100){
            answer= answer+"C";
        }
    }else{
        answer = "CM";
    }
    return answer;
}
 
string thousandth(int num){
    string answer = "";
    for (int i =0; i<=(num-1000);i=i+1000){
        answer = answer + "M";
    }
    return answer;
}


// converts each group to its approp. Roman value 
string toRoman(int number){
    string roman = ""; 
    
    if(number<10){
        roman = oneth(number);
    }else if(number < 100){
        roman = tenth(number);
    }else if(number < 1000){
        roman = hundredth(number);
    }else{
        roman = thousandth(number);
    }
    
    return roman;
}

// accepts a string, ie number.
// break number down appropriatly.
// EX: n=13004. returns 10000,3000,4 as string vector
vector<string> getVectorOfStrings(string n){
    vector<string> answer;
    string zeros = "";
    stringstream ss;

    for (int i =n.length()-1; i>-1; i--){ 
        while(n[i]=='0'){
            i--;
            zeros+="0";
        }
        string number = n.substr(i, 1);//
        number=number + zeros;
        zeros=zeros+"0";
        answer.push_back(number);
    }
    
    reverse(answer.begin(),answer.end());
    return answer;
}

// converts number to string
string numberToString(int number){
    ostringstream convert;
    convert << number;
    return convert.str();
}

//accepts a number and returns vector of numbers that sum up to the original number
vector<int> breakNumber(int number){
    vector<int> brokenNumber;
    
    //Converts number to string.
    string n = numberToString(number);
    //returns string vector cointaing: 900, 90, 9
    vector<string> stringOfNumbers = getVectorOfStrings(n);
    
    //converts the string vector to int vector
    for(int i=0; i<stringOfNumbers.size();i++){
        int num = stoi(stringOfNumbers[i]);
        brokenNumber.push_back(num);
    }
    
    
    return brokenNumber;
}

//returns Roman numerals
string convertToRoman(int number){
    string answer = "";
    
    //Returns vector of ints that add up to the original number. ie, if number was 999, returns 900, 90, 9
    vector<int> brokenNumber = breakNumber(number);  
    
    //Converts each number from vector to Roman and adds it to a string
    for (int i =0; i< brokenNumber.size(); i++){
        string romanNum = toRoman(brokenNumber[i]);
        answer += romanNum;
    }
    
    return answer;
}

//returns translated Latin number
int calculateNumber(vector<char> array){
    int sum=0;
    for (int i=0; i<array.size(); i++){
        if(array[i]=='I') sum+=1;
        else if (array[i]=='V') sum+=5;
        else if (array[i]=='X') sum+=10;
        else if (array[i]=='L') sum+=50;
        else if (array[i]=='C') sum+=100;
        else if (array[i]=='D') sum+=500;
        else if (array[i]=='M') sum+=1000;
    }
    return sum;
}

//breaks string into vector char
vector<char> split(string line){
    vector<char> answer;
    for(int i =0; i<line.length(); i++){
        answer.push_back(line[i]);
    }
    return answer;
}

//Translates Roman to Latin and converts the number to Roman
string solver(string line){
    vector<char> array; 
    array = split(line);
    int number = calculateNumber(array);
    string answer = convertToRoman(number);
    return answer;
}

//Calls solver on each test case
int main() {
    int T;
    cin >>T;
    for (int i=0; i<T; i++){
        string line;
        cin >> line;
        cout << solver(line) <<endl;
    }
    return 0;
}
