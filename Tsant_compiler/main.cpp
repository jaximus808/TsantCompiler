#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cmath>

using namespace std; 

//LOI = Line of interest
// unsigned char* valueCalculator(vector<string > LOI)
// {

    

// }



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

bool operatorCorrect(string questionKey)
{
    string keywords[] = { "+", "-"};
    int kLen = 2;
    for(int i =0; i < kLen; i++)
    {
        if(keywords[i] == questionKey) return true;
    }
    return false; 
}

int int32String(string input)
{
    int value = 0;
    for(int i = input.length()-1; i >= 0 ; i--)
    {
        int decC = (int)input[i];
        cout << decC << endl;
        if(decC>57 || decC < 48)  
        {
            cout << "error" << endl;
            return 0;
        } //make this reference a variab;e 
        value+=(decC-48) * pow(10, (input.length()-1-i));

    }
    return value; 
}

unsigned char* byteConverter(string type, vector<string> parts)
{

    vector<string> opKeys;
    vector<string> opTokens;
    
    bool tokenPhaseToken = true; 

    for(int i = 0; i < parts.size();i++)
    {
        bool tokenOp = true; 
        if(operatorCorrect(parts[i]) )
        {
            tokenOp = false; 
        }

        if (tokenPhaseToken != tokenOp) cout<<"wtf";
        if(tokenOp) opTokens.push_back(parts[i]);
        else opKeys.push_back(parts[i]);
    }
    if(type == "int")
    {


    }
    unsigned char* dog = NULL; 
    return dog;

}




class value
{
    public:
        value(vector<string > _equation)
        {
            equation = _equation; 
        }
        value()
        {
            equation = vector<string>(); 
        }
        
        vector<string > getValue()
        {
            return equation; 
        }

    private:
        vector<string> equation; 

};

class variableManager
{
    public:
        variableManager(string _type)
        {
            type = _type;
            unsigned char placeHolder[1] = {'0'};
            value = placeHolder;
        }

        void setValue(unsigned char* byteVal)
        {
            value = byteVal;
        }

    private:
        unsigned char* value; 
        string type; 
};

class instructions
{
    public:
        instructions(string _name, string _type, string _value ,string _operation )
        {
            operationType = _operation; 
            type = _type; 
            name = _name; 
            setValue = value(); 
        }

        instructions(string _name, vector<string> _value, string _operation)
        {
            operationType = _operation; 
            name = _name; 
            setValue = value(_value); 

        }

        void operate(unordered_map<string,variableManager*> &variables)
        {
            if(operationType == "declare")
            {
                variableManager holder = variableManager(type); 
                variables.insert(make_pair(name, &holder)); 
            }
            else if(operationType == "assign")
            {
                unsigned char* byteVal = byteConverter(type, setValue.getValue());
            }
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



void throwExpected()
{
    cout << "error";
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
                cout << "error";
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
                    cout <<"error";
                }
                instructions declare(bAST[line][pointer+1], bAST[line][pointer], "none", "declare");
                orderOP.push_back(declare);
            }
            else if(bAST[line][pointer] == "=")
            {
                //check infront
                if(cacheTokens.size())
                {
                    cout << "error";
                }
                if(pointer+1 == bAST[line].size())
                {
                    cout << "error";
                }
                instructions assign(bAST[line][pointer+1], bAST[line][pointer], "none", "assign");
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


void interpertor(unordered_map<string, variableManager* > &varMap,vector<instructions> &orders )
{
    for(int i = 0; i < orders.size(); i++)
    {
        orders[i].operate(varMap);
    }
}
int main()
{
    
    cout << int32String("124") << endl; 

    std::ifstream file; 
    file.open("main.ch");

    vector<vector<string> > lexAnalysis;


    unordered_map<string, variableManager*> variables;

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