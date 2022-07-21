#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cmath>

using namespace std; 

// finsih the operator shit; 6/9/2022

//fix some bugs with variables being on the right side. The function reads it but overpowers it idk why lol 6/20/22

class variableManager
{
    public:
        variableManager(string _type)
        {
            type = _type;
            value = "NULL";
        }

        void setValue(string byteVal)
        {
            value = byteVal;
        }

        string getType()
        {
            return type; 
        }

        string getValue()
        {

            return value;
        }

    private:
        string value; 
        string type; 
};
/*
class functionsManager
{
    public:
        functionsManager(vector<vector<string>> &_params, vector<instructions> &_operations)
        {
            operations = _operations;
            for(int i = 0; i < _params.size(); i++)
            {
                if(_params[i].size() != 2)
                {
                    cout << "error: false function declaration";
                    return;
                }
                if(keywordExist(_params[i][1]))
                {
                    cout << "error: cannot use keyword as variable name";
                    return;
                }
                string type = _params[i][0];

                variableManager* newVar = new variableManager(type);
                localVar.insert(make_pair(_params[i][1],newVar));
                paramNames.push_back(_params[i][1]);
            }
        }

        string operate(vector<vector<string>> inputedParam,unordered_map<string,variableManager*> &varMap, unordered_map<string, instructions*> &functions,bool debug)
        {
            if(inputedParam.size() != paramNames.size()) 
            {
                cout << "error: not enough arguments given";
                return "error";
            }
            for(int i = 0; i < paramNames.size(); i++)
            {
                localVar.find(paramNames[i])->second->setValue(sequenceOperator(localVar.find(paramNames[i])->second->getType(), inputedParam[i],varMap));
            }

            unordered_map<string,variableManager*> updatedVarMap(varMap);

            updatedVarMap.insert(localVar.begin(), localVar.end());

            for(int i = 0; i < operations.size(); i++)
            {
                string returnVal = operations[i].operate(updatedVarMap,functions,debug);
                if(returnVal.length() > 0) return returnVal;
                //this could lowkey be it??
            }


        }

    private:
        string value; 
        string type; 

        vector<string> paramNames;
        vector<instructions> operations;
        unordered_map<string, variableManager*> localVar; 

};
*/

// class functionManager
// {
//     public:
//         functionManager()
// };

#pragma region helperFuncs
bool seperateKeyword(char c)
{
    int chars[] = {'=','+','-','*','/','(',')',',','{','}'};

    for(int i = 0; i < 8; i++)
    {
        if(chars[i] == c) return true; 
    }

    return false; 
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

bool operatorCorrect(string questionKey)
{
    string keywords[] = { "+", "-","*","/"};
    int kLen = 4;
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

void err(string msg)
{
    cout <<"error: "<<msg<<endl;
}

//detect the type
string sequenceOperator(string type, vector<string> parts, unordered_map<string, variableManager* > &varMap)
{

    //string " ->  "\"";
    //keywords
    vector<string> opKeys;
    //variables and values 
    vector<string> opTokens;
    
    bool tokenPhaseToken = true; 

    string posType = "none";


    for(int i = 0; i < parts.size();i++)
    {

        bool tokenOp = true; 
        if(operatorCorrect(parts[i]) )
        {
            tokenOp = false; 
        }
        


        if(tokenOp)
        {
            opTokens.push_back(parts[i]);




            bool debug  = posType == "none";



            if(debug)
            {

                if((int)parts[i][0] == 34)
                {
                    posType = "string"; 
                    
                }
                else if(isNum(parts[i]))
                {
                    posType = "int";
                }
                else if(varMap.find(opTokens[i])!= varMap.end())
                {
                    posType = varMap.find(opTokens[i])->second->getType();
                }
            }
            else 
            {
                if(parts[i][0] == '\"' && posType != "string")
                {
                    cout << "cannot operate string and " <<posType<<endl;
                    return "";
                }
                else if(isNum(parts[i])&& posType != "int")
                {
                    cout << "cannot operate int and " <<posType<<endl;
                    return "";
                }
                else if(varMap.find(opTokens[i])!= varMap.end())
                {
                    if(varMap.find(opTokens[i])->second->getType() != posType)
                    {
                        cout <<"cannot operate "<< varMap.find(opTokens[i])->second->getType() << " and "<<posType<<endl;
                        return "";
                        
                    } 
                }
                
            }
        } 
        else opKeys.push_back(parts[i]);
    }
    if(opKeys.size()!= opTokens.size()-1 )
    {
        cout << "ERROR!!!!";

        return ""; 
    }
    if(posType == "int")
    {

        for(int i = 0; i < opKeys.size(); i++)
        {
            
            if(opKeys[i] == "/" ||opKeys[i] == "*"  )
            {


                //make this also recongize functions
                int prevValue;
                int nextValue; 
                if(isNum(opTokens[i]))
                {
                    prevValue = int32String(opTokens[i]); 

                }
                else 
                {

                    string _type = varMap.find(opTokens[i])->second->getType(); 
                    if(_type != "int")
                    {
                        cout << "cannot combine type "<<_type<< " with type int";
                        return "";
                    }
                    else
                    {

                        string val = varMap.find(opTokens[i])->second->getValue();
                        prevValue = int32String(val);
                    }

                }


                if(isNum(opTokens[i+1]))
                {
                    nextValue = int32String(opTokens[i+1]); 
                }
                else 
                {
                    string _type = varMap.find(opTokens[i+1])->second->getType(); 
                    if(_type != "int")
                    {
                        cout << "cannot combine type "<<_type<< " with type int";
                        return "";
                    }
                    else
                    {

                        string val = varMap.find(opTokens[i+1])->second->getValue();
                        nextValue = int32String(val);
                    }


                }
                if(opKeys[i] == "/")
                {

                    opTokens[i] = to_string(prevValue / nextValue);
                }
                else 
                {
                    opTokens[i] = to_string(prevValue * nextValue);
                }

                opTokens.erase(opTokens.begin()+i+1);
                
                opKeys.erase(opKeys.begin()+i); 

            }
            
            
        }
        for(int i = 0; i < opKeys.size(); i++)
        {
            
            if(opKeys[i] == "+" ||opKeys[i] == "-"  )
            {
                int prevValue;
                int nextValue; 
                if(isNum(opTokens[i]))
                {
                    prevValue = int32String(opTokens[i]); 

                }
                else 
                {
                    string _type = varMap.find(opTokens[i])->second->getType(); 
                    if(_type != "int")
                    {
                        cout << "cannot combine type "<<_type<< " with type int";
                        return "";
                    }
                    else
                    {

                        string val = varMap.find(opTokens[i])->second->getValue();
                        prevValue = int32String(val);
                    }

                }

                if(isNum(opTokens[i+1]))
                {
                    
                    nextValue = int32String(opTokens[i+1]);
                    
                }
                else 
                {
                    string _type = varMap.find(opTokens[i+1])->second->getType(); 
                    if(_type != "int")
                    {
                        cout << "cannot combine type "<<_type<< " with type int";
                        return "";
                        
                    }
                    else
                    {

                        string val = varMap.find(opTokens[i+1])->second->getValue();
                        nextValue = int32String(val);
                    }


                }
                if(opKeys[i] == "+")
                {

                    opTokens[i] = to_string(prevValue + nextValue);

                }
                else 
                {
                    opTokens[i] = to_string(prevValue-nextValue);
                }

                opTokens.erase(opTokens.begin()+i+1);
                
                opKeys.erase(opKeys.begin()+i); 


            }
            
            
        }

        
        if(!isNum(opTokens[0]))
        {
            string _type = varMap.find(opTokens[0])->second->getType(); 
            if(_type != "int")
            {
                cout << "cannot combine type "<<_type<< " with type int";
                return "";
                
            }
            else
            {

                string val = varMap.find(opTokens[0])->second->getValue();
                return val; 
            }

        }
        return opTokens[0];


    }



    if(posType == "string")
    {

        for(int i = 0; i < opKeys.size(); i++)
        {
            
            string prevValue;
            string nextValue; 

            if((int)opTokens[i][0] == 34)
            {
                prevValue = opTokens[i].substr(0, opTokens[i].length() - 1); 

            }
            else 
            {
                string _type = varMap.find(opTokens[i])->second->getType(); 
                if(_type != "string")
                {
                    cout << "cannot combine type "<<_type<< " with type int";
                    return "";
                }
                else
                {

                    string val = varMap.find(opTokens[i])->second->getValue();
                    prevValue = val.substr(0, val.length()-1);
                }

            }

            if(opTokens[i+1][0] == '\"')
            {
                
                nextValue = opTokens[i+1].substr(1,opTokens[i+1].length()-1);
                
            }
            else 
            {
                string _type = varMap.find(opTokens[i+1])->second->getType(); 
                if(_type != "string")
                {
                    cout << "cannot combine type "<<_type<< " with type int";
                    return "";
                }
                else
                {

                    string val = varMap.find(opTokens[i+1])->second->getValue();
                    nextValue = val.substr(1, val.length()-1);
                }


            }
            if(opKeys[i] == "+")
            {

                opTokens[i] = prevValue + nextValue;

            }
            else
            {
                cout <<"error: unexpected token";
                return "";
            }

            opTokens.erase(opTokens.begin()+i+1);
            
            opKeys.erase(opKeys.begin()+i); 



        }
        if((int)opTokens[0][0] != 34 )
        {
            string _type = varMap.find(opTokens[0])->second->getType(); 
            if(_type != "string")
            {
                cout << "cannot combine type "<<_type<< " with type string";
                return "";
                
            }
            else
            {

                string val = varMap.find(opTokens[0])->second->getValue();
                return val; 
            }

        }



        return opTokens[0].substr(1,opTokens[0].length()-2);
        
    }
    else
    {
        cout <<"unrecongized type";
        return "";
    }
    return "";

}

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

#pragma endregion helperFuncs

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
    //remove operation parameter
    public:
        instructions(string _name, string _type, string _value ,string _operation )
        {
            operationType = _operation; 
            type = _type; 
            name = _name; 
            setValue = value(); 
        }

        //assigning and calling
        instructions(string _name, vector<string> _value, string _operation)
        {
            operationType = _operation; 
            name = _name; 
            if(operationType == "assign")
            {
                setValue = value(_value); 
            }
            else if(operationType == "funcCall") 
            {
                funcParametersUnParsed = _value; 
            }

        }

        //declaring functions
        instructions(string _name, vector<instructions> &_ops, vector<string> &parameters,string _operationType)
        {
            name = _name; 
            funcOperations = _ops;
            funcParametersUnParsed = parameters;
            operationType = _operationType; 
            

            
        }



        string operate(unordered_map<string,variableManager*> &variables,unordered_map<string,instructions*> &functions,bool debug)
        {
            if(operationType == "declare")
            {
                variableManager* holder = new variableManager(type); 

                variables.insert(make_pair(name, holder)); 
                if(debug) cout <<  "\nStoring variable with name "<<name<<" with pointer at "<<&holder <<"\n";
               


            }
            else if(operationType == "funcDeclare")
            {
                vector<vector<string> > parasedParameters; 

                vector<string> parameterPart; 
                for(int i = 0; i < funcParametersUnParsed.size(); i++)
                {
                    if(funcParametersUnParsed[i] == ",") 
                    {
                        parasedParameters.push_back(parameterPart);
                        parameterPart.clear();
                    }
                    else 
                    {
                        parameterPart.push_back(funcParametersUnParsed[i]);
                    }

                }
                if(parameterPart.size() == 0)
                {
                    cout << "Expected token";
                    return ""; 
                }
                parasedParameters.push_back(parameterPart);
                parameterPart.clear();
                for(int i = 0; i < parasedParameters.size()-1; i++)
                {
                    if(parasedParameters[i].size() != 2)
                    {
                        cout << "error: false function declaration";
                        return "";
                    }
                    if(keywordExist(parasedParameters[i][1]))
                    {
                        cout << "error: cannot use keyword as variable name";
                        return "";
                    }
                    string type = parasedParameters[i][0];

                    variableManager* newVar = new variableManager(type);
                    localVar.insert(make_pair(parasedParameters[i][1],newVar));
                    paramNames.push_back(parasedParameters[i][1]);
                }

                functions.insert(make_pair(name,this )); 
                //if(debug) cout <<  "\nDeclaring function with name "<<name;
               


            }
            else if(operationType == "assign")
            {
                string _type = variables.find(name)->second->getType(); 
                string finalVal = sequenceOperator(_type, setValue.getValue(),variables);
                variables.find(name)->second->setValue(finalVal); 
                if(debug) cout << "\nvariable "<<name<<" assigned value "<<finalVal<<endl;
                
            }
            else if(operationType == "funcCall")
            {
                vector<vector<string> > parasedParameters; 

                vector<string> parameterPart; 
                for(int i = 0; i < funcParametersUnParsed.size(); i++)
                {
                    if(funcParametersUnParsed[i] == ",") 
                    {
                        parasedParameters.push_back(parameterPart);
                        parameterPart.clear();
                    }
                    else if(funcParametersUnParsed[i] == "+"||funcParametersUnParsed[i] == "-"||funcParametersUnParsed[i] == "*"||funcParametersUnParsed[i] == "/")
                    {
                        parameterPart.push_back(funcParametersUnParsed[i]);
                    }
                    else 
                    {
                        parameterPart.push_back(funcParametersUnParsed[i]);
                    }

                }
                if(parameterPart.size() == 0)
                {
                    cout << "Expected token";
                    return ""; 
                }
                parasedParameters.push_back(parameterPart);
                parameterPart.clear();

                //add the dictionary stuff
                //inbuilt functions

                if(name == "print" && parasedParameters.size() == 1)
                {
                    cout << sequenceOperator("int",parasedParameters[0], variables);
                }
                else if(name == "println" && parasedParameters.size() == 1)
                {
                    cout << sequenceOperator("int",parasedParameters[0], variables)<<endl;
                }
                else if(functions.find(name) != functions.end())
                {
                    functions.find(name)->second->operate(parasedParameters,variables,functions,debug);
                }
                else 
                {
                    cout <<"error: unrecongized function";
                    return ""; 
                }
            }

                return "";
        }


        //only this will be called when operating
        string operate(vector<vector<string>> inputedParam,unordered_map<string,variableManager*> &varMap, unordered_map<string, instructions*> &functions,bool debug)
        {
            if(inputedParam.size()-1 != paramNames.size()) 
            {
                cout << "error: not enough arguments given";
                return "error";
            }
            for(int i = 0; i < paramNames.size(); i++)
            {
                localVar.find(paramNames[i])->second->setValue(sequenceOperator(localVar.find(paramNames[i])->second->getType(), inputedParam[i],varMap));
            }

            unordered_map<string,variableManager*> updatedVarMap(varMap);

            updatedVarMap.insert(localVar.begin(), localVar.end());
            for(int i = 0; i < funcOperations.size(); i++)
            {
                string returnVal = funcOperations[i].operate(updatedVarMap,functions,debug);
                if(returnVal.length() > 0) return returnVal;
                //this could lowkey be it??
            }
            return "";

        }

        void debug()
        {
            if(operationType == "declare")
            {
                cout << "declaring variable " <<  name <<" with type "<<type;
            }
            else if(operationType == "assign")
            {
                cout << "variable " <<  name <<" assigned value of operation "<<setValue.getValuePrint();
            }
            else if(operationType == "funcCall")
            {

                cout << "function  " <<  name <<" called with paramters: ";
                for(int i = 0; i < funcParametersUnParsed.size(); i++)
                {
                    cout << funcParametersUnParsed[i]<<", ";
                }
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


        //add a function
        vector<instructions > funcOperations; 
        vector<instructions> funcParameters; 
        vector<string > funcParametersUnParsed;

        vector<string> paramNames;
        vector<instructions> operations;
        unordered_map<string, variableManager*> localVar; 

        

};




bool LexicalAnalysis(vector<vector<string> > &bAST, vector<instructions> &orderOP,bool debug )
{

    vector<string> cacheTokens; 

    bool functionInstructs = false; 
    string funcName = "";
    vector<instructions> instructFunc;
    vector<string> unparsedParamDeclare; 

    //eZZau
    for(int line = 0; line < bAST.size(); line++)
    { 
        bool paramCheck = false; 
        int parenthesisDepth = 0; 
        vector<instructions> tokenInstructs; 
        string paramQues = ""; 
        vector<string> unparsedTokens; 
        for(int pointer = 0; pointer < bAST[line].size(); pointer++)
        {

            if(paramCheck)
            {
                if(bAST[line][pointer] == "(")
                {
                    parenthesisDepth++; 
                }
                else if(bAST[line][pointer] == ")")
                {
                    parenthesisDepth--; 
                    if (parenthesisDepth == 0)
                    {   
                        unparsedTokens.push_back(paramQues);
                        
                        if(pointer +1 < bAST[line].size())
                        {
                            if(bAST[line][pointer+1] == "=")
                            {
                                if(functionInstructs)
                                {
                                    cout <<"error: cannot define functions within functions";
                                    return false; 
                                }
                                //now creating new func 
                                //change mode to reading function when adding to instruction 
                                funcName =cacheTokens[0];
                                functionInstructs = true; 
                                pointer++;
                                unparsedParamDeclare = unparsedTokens;

                            }
                            else 
                            //do this better later
                            {
                                instructions funcCall(cacheTokens[0], unparsedTokens, "funcCall");
                            //perfect check here lol
                            //check for = token or smth
                                if(functionInstructs)
                                {
                                    instructFunc.push_back(funcCall);
                                }
                                else
                                {
                                    orderOP.push_back(funcCall); 
                                }
                                cacheTokens.clear(); 
                                paramCheck = false;
                                paramQues = "";
                            }
                        }
                        else 
                        {
                            instructions funcCall(cacheTokens[0], unparsedTokens, "funcCall");
                        //perfect check here lol
                        //check for = token or smth
                            if(functionInstructs)
                            {
                                instructFunc.push_back(funcCall);
                            }
                            else
                            {
                                orderOP.push_back(funcCall); 
                            }
                            cacheTokens.clear(); 
                            paramCheck = false;
                            paramQues = "";
                        }
                        
                    }
                    
                }
                if(parenthesisDepth == 1)
                {
                    if(bAST[line][pointer] == ","||bAST[line][pointer] == "+"||bAST[line][pointer] == "-"||bAST[line][pointer] == "/"||bAST[line][pointer] == "*")
                    {
                        if(paramQues.length() == 0) return false; 
                        unparsedTokens.push_back(paramQues);

                        unparsedTokens.push_back(bAST[line][pointer]);
                        paramQues = "";
                        
                    }
                    else 
                    {
                        paramQues += bAST[line][pointer]; 
                    }
                    
                }
                else 
                {
                    paramQues += bAST[line][pointer];
                }
                    
            }
            else if(isNum(bAST[line][pointer]))
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
                if(functionInstructs)
                {
                    instructFunc.push_back(declare);
                }
                else
                {
                    orderOP.push_back(declare);
                }
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
                if(functionInstructs)
                {
                    instructFunc.push_back(assign);
                }
                else
                {
                    orderOP.push_back(assign);
                }
                pointer = bAST[line].size();
                
            }
            else if(bAST[line][pointer] == "endf")
            {
                if(!functionInstructs)
                {
                    cout << "error: no function to end";
                    return false; 
                }
                instructions funcDefine(funcName, instructFunc,unparsedParamDeclare , "funcDeclare");
                orderOP.push_back(funcDefine);
                functionInstructs = false; 
                
            }
            else if(bAST[line][pointer] == "(")
            {
                //check infront
                if(cacheTokens.size() == 0)
                {
                    cout << "error: no token passed for function paramters";
                    return false; 
                }
                if(pointer+1 == bAST[line].size())
                {
                    cout << "error: expected arguments at the end of assignment";
                    return false; 
                }
                parenthesisDepth++; 
                paramCheck = true; 
                cacheTokens.push_back(bAST[line][pointer-1]);
                
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
    if(debug)
    {
        for(int i =  0; i < orderOP.size(); i++)
        {
            orderOP[i].debug();
        }
    }
    return true; 

}


void interpertor(unordered_map<string, variableManager* > &varMap, unordered_map<string, instructions* > &functions,vector<instructions> &orders, bool debug )
{
    for(int i = 0; i < orders.size(); i++)
    {
        orders[i].operate(varMap,functions,debug);
    }
}

int main(int argc, char** argv)
{
    

    bool debug = false; 
    char* inputFile;  

    if(argc == 1)
    {
        cout << "error: no input file found";
        return 1;
    }
    
    if(argc > 1)
    {
        inputFile = argv[1];

        //prob do this better
        string inputBuffer = string(inputFile);
        if(inputBuffer == "-help")
        {
            cout << "Tsant Compiler/Interpreter Syntax:"<<endl;
            cout << "./main [file name || -help] [debug: true or false]"<<endl;
            return 0;
            
        }
        else if(inputBuffer.substr(inputBuffer.length()-3,3) != ".tn")
        {
            cout<<"error: expected file of .tn";
            return 1; 
        }

    }
    if(argc > 2)
    {
        cout << argv[2];
        string arg = string(argv[2]);
        if(arg== "true")
        {
            debug = true;
        }
        else if(arg == "false")
        {
            debug = false;
        }
        else 
        {
            cout <<"error: expected true or false";
            return 1;
        }
    }
    std::ifstream file; 
    file.open(argv[1]);


    vector<vector<string> > lexAnalysis;


    unordered_map<string, variableManager*> variables;

    unordered_map<string, instructions*> functions;

    vector<instructions> instructionList; 
    if(file.is_open())
    {
        char c; 
        int line = 0; 
        vector<string> lineVec;
        string curW = "";
        bool parsingString = false; 

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
                    if(debug)
                    {
                        for(int i = 0; i < lineVec.size(); i++)
                        {
                            cout << lineVec[i] << ",";
                        }
                        cout << "\n";
                    }
                    
                    lineVec.clear();
                }
                break;
            } 
            

            
            if(int(c) == 10 || c ==';') 
            {
                if(parsingString)
                {
                    cout << "error: expected ending \" symbol";
                    return 1;
                }
                if(curW.length() >0) 
                {
                    lineVec.push_back(curW); 
                    curW = "";
                }
                if(lineVec.size() > 0)
                { 
                    lexAnalysis.push_back(lineVec);
                    if(debug)
                    {
                        for(int i = 0; i < lineVec.size(); i++)
                        {
                        cout << lineVec[i] << ",";
                        }
                        cout << "\n";
                    }
                    
                    lineVec.clear();
                }
                
            }
            else if(parsingString)
            {
                if(c == '\"')
                {
                    parsingString = false;
                    curW += '\"'; 
                }
                else
                {
                    curW += c; 
                }
            }
            else if(c == '\"')
            {
                if(curW.length() > 0) 
                {
                    cout << "error: unexpected \" symbol";
                    return 1;
                }
                parsingString = true;
                curW += '\"'; 
            }
            else if(seperateKeyword(c))
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
            
            else 
            {

                curW += c;
            }
        }
        if(!LexicalAnalysis(lexAnalysis, instructionList,debug))
        {
            cout << "\nCompiler Stopped";
            return 1; 
        }
        interpertor(variables,functions, instructionList,debug); 
        
         


    }
    else 
    {
        cout << "error: file does not exist in directory";
    }


}