#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <bitset>
#include "math.h"
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct Labels{
    string name;
    int address;
};

vector<Labels> label;

int token_Size = 0; 
char token; 
vector<char> tokens; 
vector<string> symbls; 
 
string hextoBin(string hex_String)
{
    stringstream temp;
    temp << hex << hex_String;
    unsigned n;
    temp >> n;
    bitset<16> b(n);

    return b.to_string();
}


string bintoHex(string bin_String)
{
    string hex_String;
    bitset<32> b(bin_String);
    unsigned n = b.to_ulong();
    stringstream temp;
    temp << hex << setfill('0') << setw(8) << n;
    hex_String = temp.str();
    transform(hex_String.begin(), hex_String.end(), hex_String.begin(), ::toupper);
    return hex_String;

}

string dectoBin(int value)
{
    stringstream ht;
    ht << hex << value;

    stringstream bt;
    bt << hex << ht.str();
    unsigned n;
    bt >> n;
    bitset<16> b(n);

    return b.to_string();
}

void openFile(char *file_name)
{
    ifstream file;
    file.open(file_name);

    if(!file.is_open())  
    {
        cout << "FILE DOES NOT EXIST/FAILED TO OPEN FILE!" << endl;
        exit(EXIT_FAILURE);
    }

    else
    {
        int i = 0;
        char temp;

        while (!file.eof())
        {
            file.get(temp);
            tokens.push_back(temp);
            i++;
            token_Size++;
        }
        i = 0;
        token_Size--;

        for(int i = 0; i < token_Size; i++)
        {
            cout << tokens[i] << "" ;
        }


        cout << endl;
    }
}


string immediate_Table(int &no_ofSymbols, int &symbol_Counter)
{
    string temp;

    if(symbol_Counter == no_ofSymbols) 
    {
        return "";
    }

    symbol_Counter++; 
    string temp_symbol = symbls[symbol_Counter]; 

    temp = hextoBin(temp_symbol);

    return temp;

}


string branch_Table(int &no_ofSymbols, int &symbol_Counter, string &temp, int &labelsCounter, int &lineCounter)
{

    int offset = 0;
    string bin;

    if(symbol_Counter == no_ofSymbols) 
    {
        return "";
    }

    symbol_Counter++; 
    string temp_symbol = symbls[symbol_Counter]; 

    for(int i = 0; i < labelsCounter; i++) 
    {
        if(label[i].name == temp_symbol)
        {
            if(label[i].address >  lineCounter)
            {
                offset = (label[i].address - lineCounter) - 1;
            }
            else
            {
                offset = -((lineCounter - label[i].address));
            }

            //After finding it we turn it into binary form.
            bin = dectoBin(offset);
            temp = temp + bin;
            break;
        }
    }


    return temp; 
}


string registerTable(int &no_ofSymbols, int &symbol_Counter)
{
    string temp;

    if(symbol_Counter == no_ofSymbols) 
    {
        return "";
    }

    symbol_Counter++; 

    string temp_symbol = symbls[symbol_Counter]; 
        
        if(temp_symbol == "$0") temp = "00000";
        else if(temp_symbol == "$1") temp = "00001";
        else if(temp_symbol == "$2") temp = "00010";
        else if(temp_symbol == "$3") temp = "00011";
        else if(temp_symbol == "$4") temp = "00100";
        else if(temp_symbol == "$5") temp = "00101";
        else if(temp_symbol == "$6") temp = "00110";
        else if(temp_symbol == "$7") temp = "00111";
        else if(temp_symbol == "$8") temp = "01000";
        else if(temp_symbol == "$9") temp = "01001";
        else if(temp_symbol == "$10") temp = "01010";
        else if(temp_symbol == "$11") temp = "01011";
        else if(temp_symbol == "$12") temp = "01100";
        else if(temp_symbol == "$13") temp = "01101";
        else if(temp_symbol == "$14") temp = "01110";
        else if(temp_symbol == "$15") temp = "01111";
        else if(temp_symbol == "$16") temp = "10000";
        else if(temp_symbol == "$17") temp = "10001";
        else if(temp_symbol == "$18") temp = "10010";
        else if(temp_symbol == "$19") temp = "10011";
        else if(temp_symbol == "$20") temp = "10100";
        else if(temp_symbol == "$21") temp = "10101";
        else if(temp_symbol == "$22") temp = "10110";
        else if(temp_symbol == "$23") temp = "10111";
        else if(temp_symbol == "$24") temp = "11000";
        else if(temp_symbol == "$25") temp = "11001";
        else if(temp_symbol == "$26") temp = "11010";
        else if(temp_symbol == "$27") temp = "11011";
        else if(temp_symbol == "$28") temp = "11100";
        else if(temp_symbol == "$29") temp = "11101";
        else if(temp_symbol == "$30") temp = "11110";
        else if(temp_symbol == "$31") temp = "11111";
        else temp = temp + "00000";

        return temp; 




}


string shiftTable(int &no_ofSymbols, int &symbol_Counter)
{
    string temp_symbol;
    string shift_amt;

    if(symbol_Counter == no_ofSymbols) 
    {
        return "";
    }

    symbol_Counter++;
    temp_symbol = symbls[symbol_Counter]; 

    
    int decimal = atoi(temp_symbol.c_str());

    stringstream ht;
    ht << hex << decimal;

    stringstream bt;
    bt << hex << ht.str();
    unsigned n;
    bt >> n;
    bitset<5> b(n);

    shift_amt = b.to_string();



    return shift_amt;

}

string jump_Table(int &no_ofSymbols, int &symbol_Counter, int &labelsCounter, int &lineCounter, string &temp)
{
    string temp_symbol;
    int offset; //Although I named this variable offset, it really is just the jump address.
    string bin;

    if(symbol_Counter == no_ofSymbols)
    {
        return "";
    }

    symbol_Counter++;
    temp_symbol = symbls[symbol_Counter]; 

    for(int i = 0; i < labelsCounter; i++) 
    {
        if(label[i].name == temp_symbol)
        {
            offset = label[i].address;

            stringstream ht;    

            ht << hex << offset;

            stringstream bt;
            bt << hex << ht.str();
            unsigned n;
            bt >> n;
            bitset<26> b(n);

            bin = b.to_string();

            temp = temp + bin;
            break;
        }
    }


    return temp; 
}

string loadWordTable(int &no_ofSymbols, int &symbol_Counter)
{
    string temp_symbol;
    string temp;
    string bin;

    if(symbol_Counter == no_ofSymbols) 
    {
        return "";
    }

    symbol_Counter++;
    temp_symbol = symbls[symbol_Counter]; 

    signed decimal = atoi(temp_symbol.c_str());

        stringstream ht;    
        ht << hex << decimal;

        stringstream bt;
        bt << hex << ht.str();
        signed n;
        bt >> n;
        bitset<16> b(n);

        bin = b.to_string();

        temp = bin;


    return temp;
}


string symbol_Print(int &addr, int &no_ofSymbols, int &symbol_Counter, int &labelsCounter, int&lineCounter)
{
        string temp;
        string temp_symbol;
        //Src = source1, Tmp = source2, Dst = destination (Registers). Sft = shift ammount. Imm = immediate value amount. Lof = load word offset.
        string Src;
        string Tmp;
        string Dst;
        string Sft;
        string Imm;
        string Lof;

        if(symbol_Counter == no_ofSymbols) 
        {
            return "";
        }

        temp_symbol = symbls[symbol_Counter]; 


        if(temp_symbol == "add")
        {
            temp = "000000";
            Dst = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Dst + "00000100000";
        }
        else if(temp_symbol == "addu")
        {
            temp = "000000";
            Dst = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Dst + "00000100001";
        }
        else if(temp_symbol == "addi")
        {
            temp = "001000";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Imm = immediate_Table(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "addiu")
        {
            temp = "001001";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Imm = immediate_Table(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "and")
        {
            temp = "000000";
            Dst = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Dst + "00000100100";
        }
        else if(temp_symbol == "andi")
        {
            temp = "001100";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Imm = immediate_Table(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "beq")
        {
            temp = "000100";
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp;
            branch_Table(no_ofSymbols, symbol_Counter, temp, labelsCounter, lineCounter);
        }
        else if(temp_symbol == "bne")
        {
            temp = "000101";
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp;
            branch_Table(no_ofSymbols, symbol_Counter, temp, labelsCounter, lineCounter);
        }
        else if(temp_symbol == "nor")
        {
            temp = "000000";
            Dst = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Dst + "00000100111";
        }
        else if(temp_symbol == "or")
        {
            temp = "000000";
            Dst = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Dst + "00000100101";
        }
        else if(temp_symbol == "ori")
        {
            temp = "001101";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Imm = immediate_Table(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "lui")
        {
            temp = "00111100000";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Imm = immediate_Table(no_ofSymbols, symbol_Counter);
            temp = temp + Tmp + Imm;
        }
        else if(temp_symbol == "lw")
        {
            temp = "100011";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Lof = loadWordTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Lof;
        }
        else if(temp_symbol == "lhu")
        {
            temp = "100101";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Lof = loadWordTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Lof;
        }
        else if(temp_symbol == "lbu")
        {
            temp = "100100";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Lof = loadWordTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Lof;
        }
        else if(temp_symbol == "j")
        {
            temp = "000010";
            jump_Table(no_ofSymbols, symbol_Counter, labelsCounter, lineCounter, temp);
        }
        else if(temp_symbol == "jal")
        {
            temp = "000011";
            jump_Table(no_ofSymbols, symbol_Counter, labelsCounter, lineCounter, temp);
        }
        else if(temp_symbol == "jr")
        {
            temp = "000000";
            Src = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + "000000000000000001000";
        }
        else if(temp_symbol == "sb")
        {
            temp = "101000";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Lof = loadWordTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Lof;
        }
        else if(temp_symbol == "sh")
        {
            temp = "101001";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Lof = loadWordTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Lof;
        }
        else if(temp_symbol == "sub")
        {
            temp = "000000";
            Dst = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Dst + "00000100010";
        }
        else if(temp_symbol == "subu")
        {
            temp = "000000";
            Dst = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Dst + "00000100011";
        }
        else if(temp_symbol == "slt")
        {
            temp = "000000";
            Dst = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Dst + "00000101010";
        }
        else if(temp_symbol == "sltu")
        {
            temp = "000000";
            Dst = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Dst + "00000101011";
        }
        else if(temp_symbol == "slti")
        {
            temp = "001010";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Imm = immediate_Table(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "sltiu")
        {
            temp = "001011";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            Imm = immediate_Table(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "sw")
        {
            temp = "101011";
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Imm = immediate_Table(no_ofSymbols, symbol_Counter);
            Src = registerTable(no_ofSymbols, symbol_Counter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "srl")
        {
            temp = "00000000000";
            Dst = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Sft = shiftTable(no_ofSymbols, symbol_Counter);
            temp = temp + Tmp + Dst + Sft + "000010";
        }
        else if(temp_symbol == "sll")
        {
            temp = "00000000000";
            Dst = registerTable(no_ofSymbols, symbol_Counter);
            Tmp = registerTable(no_ofSymbols, symbol_Counter);
            Sft = shiftTable(no_ofSymbols, symbol_Counter);
            temp = temp + Tmp + Dst + Sft + "000000";
        }
        else
        {
            
            symbol_Counter++;
            temp = symbol_Print(addr,no_ofSymbols, symbol_Counter, labelsCounter, lineCounter);
            return temp;
        }

    symbol_Counter++;
    lineCounter++;
    temp = bintoHex(temp);
    return temp;
}

void firstPass(int &no_ofSymbols, int &symbols_Counter, int &lineCounter, int &labelsCounter)
{
    if(no_ofSymbols == symbols_Counter)
    {
        return;
    }
    string temp_symbol = symbls[symbols_Counter];

    if(temp_symbol == "add")    symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "addi") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "addiu") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "addu") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "and") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "andi") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "beq") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "bne") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "j") symbols_Counter = symbols_Counter + 2;
    else if(temp_symbol == "jal") symbols_Counter = symbols_Counter + 2;
    else if(temp_symbol == "jr") symbols_Counter = symbols_Counter + 2;
    else if(temp_symbol == "lbu") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "lhu") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "lui") symbols_Counter = symbols_Counter + 3;
    else if(temp_symbol == "lw") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "nor") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "or") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "ori") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "slt") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "slti") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "sltiu") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "sltu") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "sll") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "srl") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "sb") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "sh") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "sw") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "sub") symbols_Counter = symbols_Counter + 4;
    else if(temp_symbol == "subu") symbols_Counter = symbols_Counter + 4;
    else
    {
            
            Labels newLabel; 
            newLabel.name = temp_symbol; 
            newLabel.address = lineCounter; 
            label.push_back(newLabel); 
            
            labelsCounter++; 
            symbols_Counter++; 
            return;
    }

    lineCounter++; }



void printFile() 
{

    ofstream oFile;
    oFile.open("f.txt");

    
    oFile << "WIDTH=32;" << endl;
    oFile << "DEPTH=256;" << endl;
    oFile << endl;
    oFile << "ADDRESS_RADIX=HEX;" << endl;
    oFile << "DATA_RADIX=HEX;" << endl;
    oFile << endl;
    oFile << "CONTENT BEGIN" << endl;

    int lineCounter = 0; 
    int no_ofSymbols = symbls.size(); 

    int symbol_Counter = 0; 
    string instruction; 
    int labelsCounter = 0; 

    for(int i = 0; i < no_ofSymbols; i++) 
    {
        firstPass(no_ofSymbols, symbol_Counter, lineCounter, labelsCounter);
    }

    symbol_Counter = 0; 
    lineCounter = 0;

    for(int i = 0; i < 255; i++) 
    {

        if((symbol_Counter == no_ofSymbols) && (lineCounter != 255))
        {
            oFile << "   [";
            oFile << setw(3) << setfill('0') << hex << lineCounter;
            oFile << "..";
            oFile << setw(3) << setfill('0') << hex << 255;
            oFile << "]" << "  :   00000000;" << endl;
            break;
        }

        oFile << "   ";
        oFile << setw(3) << setfill('0') << hex << lineCounter << "  :   ";
        instruction = symbol_Print(i,no_ofSymbols, symbol_Counter, labelsCounter, lineCounter);
        oFile << instruction << ";" << endl;

    }
    oFile << endl;
    oFile << "END;";
    oFile.close();

}

void printSymbols()
{
    for(int i = 0; i < symbls.size(); i++)
    {
        cout << symbls[i] << endl;
    }
}


void identifiers(char &value, int &i)
{
    string temp;

    while(islower(value))
    {
        if(i == token_Size)
        {
            break;
        }

        temp += value;
        i++;
        value = tokens[i];
    }

    symbls.push_back(temp);
}


void registers(char &value, int &i)
{
    string temp;
    temp += value;
    i++;
    value = tokens[i];

    while(isdigit(value))
    {
        if(i == token_Size)
        {
            break;
        }

        temp += value;
        i++;
        value = tokens[i];
    }

    symbls.push_back(temp);
}


void digits(char &value, int &i)
{
    string temp;

    if(value == '0' && tokens[i+1] == 'x')
    {
        i = i + 2;
    }

    if(value == '-')
    {
        temp = value;
        i = i + 1;
    }

    value = tokens[i];

    while(isdigit(value) || islower(value))
    {
        if(i == token_Size)
        {
            break;
        }

        temp += value;
        i++;
        value = tokens[i];
    }

    symbls.push_back(temp);

}


void compareTokens() 
{

    for(int i = 0; i < token_Size; i++)
    {
            token = tokens[i];

            if(islower(token))
            {
                identifiers(token, i);
            }
            if(token == '$')
            {
                registers(token, i);
            }
            if(isdigit(token) || token == '-')
            {
                digits(token, i);
            }

    }
}



#endif 
