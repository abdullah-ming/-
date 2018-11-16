#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <map>


using namespace std;


char tempstr[255] = {};

bool temp = false;

char word[255] = {};

string keyword[16] =
{
    "main",   "if",       "then",    "while",  "do",  "defualt",
    "do",     "break",    "else",    "swtich", "case",
    "typedf", "return",   "continue","for",    "sizeof"
};

string symbol[14] = {"+", "-", "*", "/", "=", ";", "#","<",">",">=","<=","+=","-=","++"};
char symbol_single[8] = {'+', '-', '*', '/', '=','<','>','#'};



string type[10] =
{
    "int","double","float","char","short","void","static","const","long","struct",
};

char bracket[6] = {'(',')','{','}','[',']'};

//判断是否为字母
bool IsLetter(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return true;
    else return false;
}

bool isbracket(char ch)
{
    for(int i = 0; i<6; i++)
    {
        if(ch == bracket[i])
            return true;

    }
    return false;
}

//判断是否为数字
bool IsDigit(char ch)
{
    if (ch >= '0' && ch <= '9' || ch == '.')
        return true;
    return false;
}

bool isSymbol(char ch)
{
    for (int i = 0; i < 8; i++)
    {
        if (ch == symbol_single[i])
            return true;

    }
    return false;
}
//判断是否为定界符等
bool IsSymbol(string str)
{
    for (int i = 0; i < 14; i++)
    {
        if (str == symbol[i])
            return true;

    }
    return false;
}


bool IsKeyword(string str)
{
    for (int i = 0; i < 16; i++)
    {
        if (str == keyword[i])
        {
            return true;
        }

    }

    return false;
}
bool IsType(string str)
{
    for (int i = 0; i < 10; i++)
    {
        if (str == type[i])
        {
            return true;
        }

    }

    return false;
}

//空格处理
void HandleSpace(char a[])
{
    int j = 0;
    memset(word, 0, 255); //需要清空
    temp = false;
    for (int i = 0; i < strlen(a); i++)
    {

        if (a[i] != ' ' && a[i] != '\t')
        {
            word[j++] = a[i];
            temp = false;
        }
        else
        {

            if (!temp && a[i] != '\t')
            {
                word[j++] = a[i];
                temp = true;
            }
        }
    }
}

//处理注释
void prePro()
{
    int j = 0;
    memset(tempstr, 0, 255);
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == '/' && word[i + 1] == '/')
        {
            while (i < strlen(word))
            {
                i++;
            }
        }

        else
        {
            tempstr[j++] = word[i];
        }
    }
}

int main()
{
    char instr[255] = {};
    bool flag = false;    //多行注释标志,false为未处于注释区域
    string Token;         //存放字符串
    char *str = NULL;     //存放每行的字符串
    char delims[] = " ";  //分割标志
    int num = 1;
    int num_array[100] = {};
    map<string,string> Map;
  //  int[] num_array[100] = {};
    bool isBracket = false;
    int suffix = 0;
    string output[100] = {};
    //freopen("text.txt", "r", stdin);
    //freopen("result.txt", "w", stdout); //此行注释后，控制台输出，

    while ((gets(instr)) != NULL)
    {

        HandleSpace(instr);
        prePro();

        str = strtok(tempstr, delims);

        while (str != NULL)
        {



            for (int i = 0; i < strlen(str); i++)
            {
                if (*(str + i) == '/')
                {
                    if (*(str + i + 1) == '*')
                    {
                        flag = true;
                        break;
                    }
                }

                if (*(str + i) == '*' && flag)
                {
                    if (*(str + i + 1) == '/')
                    {
                        flag = false;
                        i++;
                        break;
                    }
                }

                if (IsLetter(*(str + i)) && (!flag))
                {

                    while (IsLetter(*(str + i)) || IsDigit(*(str + i)) ||
                            *(str + i) == '_')
                    {
                        Token += *(str + i);
                        i++;
                    }


                    if(IsType(Token))
                    {
                        output[suffix] = Token.c_str();
                        num_array[suffix] = num;
                        suffix ++;
                        Map[Token.c_str()] = "type";


                    }
                    else
                    {
                        output[suffix] = Token.c_str();
                        num_array[suffix] = num;
                        suffix ++;

                        Map[Token.c_str()] = "identify";


                    }


                    Token = "";

                }
                if(isbracket(*(str + i))&& (!flag))
                {
                    if(*(str + i) == '}'){
                        string ch1(1,*(str + i));
                        Token = "\"" + ch1 + "\"";
                        isBracket = true;
                        output[suffix] = Token.c_str();
                        num_array[suffix] = num;
                        suffix ++;
                        Map[Token] = "bracket";
                        Token = "";
                    }
                    else{
                    string ch1(1,*(str + i));
                    Token = "\"" + ch1 + "\"";
                    output[suffix] = Token.c_str();
                    num_array[suffix] = num;
                    suffix ++;

                    Map[Token] = "bracket";
                    Token = "";
                    }


                }

                if (IsDigit(*(str + i)) && (!flag))
                {

                    bool isInteger = true;
                    bool isFloat = false;

                    while (IsDigit(*(str + i)) || *(str + i) == 'e'|| *(str + i) == '-')
                    {
                        if((*(str + i) == '.'))
                        {
                            int index;
                            isInteger = false;

                        }
                        Token += *(str + i);
                        i++;
                    }
                    if(isInteger)
                    {
                        output[suffix] = Token.c_str();
                        num_array[suffix] = num;
                        suffix ++;
                        Map[Token.c_str()] = "integer";

                    }
                    else
                    {
                        i--;
                        int j;
                        for(j = 0; j< Token.length(); j++){
                            if(Token[j] == 'e')
                                isFloat = true;
                        }
                        if(isFloat){
                            if(Token[j-1] == 'e'){

                                output[suffix] = Token.c_str();
                                num_array[suffix] = num;
                                suffix ++;
                                Map[Token.c_str()] = "Error";



                            }
                            else{
                                output[suffix] = Token.c_str();
                                num_array[suffix] = num;
                                suffix ++;
                                Map[Token.c_str()] = "float";

                            }


                        }
                        else{
                                output[suffix] = Token.c_str();
                                num_array[suffix] = num;
                                suffix ++;
                                Map[Token.c_str()] = "decimal";

                        }
                    }
                    Token = "";
                }
                if(isSymbol(*(str + i)))
                {
                    if(*(str + i) == '-' && IsDigit(*(str + i+1)))
                    {
                        bool isInteger = true;
                        while (IsDigit(*(str + i+1)))
                        {
                            if((*(str + i) == '.'))
                            {
                                isInteger = false;
                            }
                            Token += *(str + i+1);
                            i++;
                        }
                        if(isInteger)
                        {

                            output[suffix] = Token.c_str();
                            num_array[suffix] = num;
                            suffix ++;
                            Map[Token.c_str()] = "integer";

                        }
                        else
                        {
                            i--;
                            output[suffix] = Token.c_str();
                            num_array[suffix] = num;
                            suffix ++;
                            Map[Token.c_str()] = "decimal";

                        }
                        Token = "";
                    }

                    while (isSymbol(*(str + i)))
                    {
                        Token += *(str + i);
                        i++;
                    }
                    if(IsSymbol(Token))
                    {
                        i--;
                            output[suffix] = Token.c_str();
                            num_array[suffix] = num;
                            suffix ++;
                            Map[Token.c_str()] = "OPT";

                    }
                    else
                    {
                        i--;
                            output[suffix] = Token.c_str();
                            num_array[suffix] = num;
                            suffix ++;
                            Token += *(str + i - 1);

                            Map[Token] = "OPT";
                            Token = "";

                            output[suffix] = Token.c_str();
                            num_array[suffix] = num;
                            suffix ++;
                            Token += *(str + i);

                            Map[Token] = "OPT";
                            Token = "";

                    }


                    Token = "";
                }
            }

            str = strtok(NULL, delims);
        }
        num++;
        if(isBracket) break;
    }
    for(int i = 0; i<100; i++){
        if(num_array[i] == 0)
            break;
        if(Map[output[i]] == "Error"){
            cout<<"Error type A at Line "<< num_array[i] <<": Illegal floating point number \""<<output[i]<<"\".";
            exit(0);
        }
    }
    for(int i = 0; i<100; i++){
        if(num_array[i] == 0)
            break;
        if(Map[output[i]] != "Error"){
            cout<<"line"<<num_array[i]<<":";
            cout<<"("<<Map[output[i]]<<", "<<output[i]<<")"<<endl;
        }

    }

    return 0;
}
