#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cmath>

using namespace std; 

// finsih the operator shit; 6/9/2022

bool seperateKeyword(char c)
{
    int chars[] = {'=','+','-','*','/'};

    for(int i = 0; i < 5; i++)
    {
        if(chars[i] == c) return true; 
    }
    return false; 
}

class variableManager
{
    public:
        variableManager(string _type)
        {
            type = _type;
            char placeHolder[1] = {'0'};
            value = placeHolder;
        }

        void setValue(char* byteVal)
        {
            value = byteVal;
        }

    private:
        char* value; 
        string type; 
};
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
        if(decC>57 || decC < 48)  
        {
            cout << "error: char is not a number" << endl;
            return 0;
        } //make this reference a variab;e 
        value+=(decC-48) * pow(10, (input.length()-1-i));

    }
    return value; 
}

vector<string> subVector(vector<string> &line, int start, int end)
{
    vector<string> returnVec;
    for(int i = start; i < end; i++)
    {
        returnVec.push_back(line[i]);
    }
    return returnVec; 
}

char* byteConverter(string type, vector<string> parts, unordered_map<string, variableManager* > &varMap)
{

    //keywords
    vector<string> opKeys;
    //variables and values 
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
    if(opKeys.size()== opTokens.size()-1 )
    {
        cout << "ERROR!!!!";
        return NULL; 
    }
    if(type == "int")
    {
        int value = 0; 

    }
    char* dog = NULL; 
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

        string getValuePrint() 
        {
            string x = "";
            for(int i = 0; i < equation.size(); i++)
            {
                x+= equation[i];
            }
            return x; 
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
                char* byteVal = byteConverter(type, setValue.getValue(),variables);
            }
        }

        void debug()
        {
            if(operationType == "declare")
            {
                cout << "declaring variable " <<  name <<" with type "<<type;
            }
            else if(operationType == "assign")
            {
                cout << "variable " <<  name <<" with operation "<<setValue.getValuePrint();
            }
            cout <<"\n";
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

bool LexicalAnalysis(vector<vector<string> > &bAST, vector<instructions> &orderOP )
{

    vector<string> cacheTokens; 
    for(int line = 0; line < bAST.size(); line++)
    { 
        for(int pointer = 0; pointer < bAST[line].size(); pointer++)
        {
            if(isNum(bAST[line][pointer]))
            {
                cout << "error: expected token!";
                return false; 
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
                    cout <<"error, name contains keyword!";
                    return false; 
                }
                instructions declare(bAST[line][pointer+1], bAST[line][pointer], "none", "declare");
                orderOP.push_back(declare);
            }
            else if(bAST[line][pointer] == "=")
            {
                //check infront
                if(cacheTokens.size() == 0)
                {
                    cout << "error: no token passed for assignment";
                    return false; 
                }
                if(pointer+1 == bAST[line].size())
                {
                    cout << "error: expected arguments at the end of assignment";
                    return false; 
                }
                instructions assign(bAST[line][pointer-1], subVector(bAST[line], pointer+1, bAST[line].size()) , "assign");
                orderOP.push_back(assign);
                pointer = bAST[line].size();
            }
            else if(!keywordExist(bAST[line][pointer]))
            {
                if(cacheTokens.size() == 1) 
                {
                    cout <<"error: unexpected token";
                    return false; 
                }
                cacheTokens.push_back(bAST[line][pointer]);
            }
        }
        cacheTokens.clear();
    }
    for(int i =  0; i < orderOP.size(); i++)
    {
        orderOP[i].debug();
    }
    return true; 

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
    

    std::ifstream file; 
    file.open("main.tn");

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
            if((int)c == -1)
            {
                if(curW.length() >0) lineVec.push_back(curW); 
                curW = "";
                if(lineVec.size() > 0)
                { 
                    lexAnalysis.push_back(lineVec);

                    for(int i = 0; i < lineVec.size(); i++)
                    {
                        cout << lineVec[i] << ",";
                    }
                    cout << "\n";
                    lineVec.clear();
                }
                break;
            } 
            

            if(seperateKeyword(c))
            {
                
                if(curW.length() >0) lineVec.push_back(curW); 
                curW="";
                string t = "";
                
                lineVec.push_back(t+c);
            }
            else if(c == ' ')
            {
                if(curW.length() >0) lineVec.push_back(curW); 
                curW = "";
            }
            else if(int(c) == 10) 
            {
                if(lineVec.size() > 0)
                { 
                    lexAnalysis.push_back(lineVec);

                    for(int i = 0; i < lineVec.size(); i++)
                    {
                        cout << lineVec[i] << ",";
                    }
                    cout << "\n";
                    lineVec.clear();
                }
                
            }
            else 
            {

                curW += c;
            }
        }
        if(!LexicalAnalysis(lexAnalysis, instructionList))
        {
            cout << "\nCompiler Stopped";
            return 1; 
        }
        
         


    }
    else 
    {
        cout << "error reading file!";
    }


}