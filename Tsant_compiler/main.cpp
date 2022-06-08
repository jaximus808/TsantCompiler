#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include "tokens.h"


using namespace std; 

//LOI = Line of interest
unsigned char* valueCalculator(vector<string > LOI)
{

    

}

class value
{
    public:
        value(vector<string > _equation)
        {
            equation = _equation; 
        }
    private:
        vector<string> equation; 

};


class instructions
{
    public:
        instructions(string _name, string _type, string _value ,string _operation )
        {
            operationType = _operation; 
            type = _type; 
            name = _name; 
        }

        instructions(string _name, vector<string> _value, string _operation)
        {
            operationType = _operation; 
            name = _name; 
            setValue = value(_value); 

        }

        void operate(map<string,unsigned char[]> &variables)
        {

        }

    private:

        //for assigning
        value setValue; 

        string operationType;
        
        //for declartion 
        string name;
        string type; 

};
vector<string> subVec(vector<string> baseVec, int start, int end)
{
    vector<string> subbed; 

    for(int _i = start; _i < end; _i++)
    {
        subbed.push_back(baseVec[_i]);
    }

    return subbed; 
}

bool isNum(string sOI)
{
    for(int i = 0; i < sOI.length(); i++)
    {
        int x = (int)sOI[i];
        if(x < 48 || x > 57 ) return false;
    }
    return true; 
}

bool keywordExist(string questionKey)
{
    string keywords[] = {"int", "string", "char", "+", "-", "float"};
    int kLen = 6;
    for(int i =0; i < kLen; i++)
    {
        if(keywords[i] == questionKey) return true;
    }
    return false; 
}

void throwExpected()
{
    throw "Expected Variable Name";
}

void LexicalAnalysis(vector<vector<string> > &bAST, vector<instructions> &orderOP )
{

    vector<string> cacheTokens; 
    for(int line = 0; line < bAST.size(); line++)
    { 
        for(int pointer = 0; pointer < bAST[line].size(); pointer++)
        {

            if(isNum(bAST[line][pointer]))
            {
                throw "Expected Token";
            }
            else if(bAST[line][pointer] == "int")
            {
                //check infront
                if(pointer+1 == bAST[line].size())
                {
                    throwExpected();
                }
                if(keywordExist(bAST[line][pointer+1]))
                {
                    throw "cannot set varaible name to key word";
                }
                instructions declare(bAST[line][pointer+1], bAST[line][pointer], "none", "declare");
                orderOP.push_back(declare);
            }
            else if(bAST[line][pointer] == "=")
            {
                //check infront
                if(cacheTokens.size())
                {
                    throwExpected();
                }
                if(pointer+1 == bAST[line].size())
                {
                    throwExpected();
                }
                instructions assign(bAST[line][pointer+1], bAST[line][pointer], "none", "declare");
                orderOP.push_back(assign);
                pointer = bAST[line].size();
            }
            else if(!keywordExist(bAST[line][pointer]))
            {
                if(cacheTokens.size() == 1) throw "expected expression"; 
                cacheTokens.push_back(bAST[line][pointer]);
            }
        }
        cacheTokens.clear();
    }


}


int main()
{

    

    std::ifstream file; 
    file.open("main.ch");

    vector<vector<string> > lexAnalysis;


    map<string, unsigned char[] > variables;

    vector<instructions> instructionList; 
    if(file.is_open())
    {
        char c; 
        int line = 0; 
        vector<string> lineVec;
        string curW = "";
        while(file)
        {

            c = file.get(); 
            if((int)c == -1) break;
            if(c == ' ')
            {
                lineVec.push_back(curW); 
            }
            if(int(c) == 10) 
            {
                if(lineVec.size() > 0)
                { 
                    lexAnalysis.push_back(lineVec);
                    lineVec.clear();
                }
                
            }

            curW += c;
        }
        LexicalAnalysis(lexAnalysis, instructionList); 


    }
    else 
    {
        cout << "error reading file!";
    }


}