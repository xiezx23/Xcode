#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <vector>
#include <map>
#include <bitset>
#include <algorithm>
#include<iomanip>
using namespace std;

// #define add "add"
// #define sub "sub"
// #define xor "xor"
// #define or "or"
// #define and "and"
// #define sll "sll"
// #define srl "srl"
// #define sra "sra"
// #define slt "slt"
// #define sltu "sltu"

class R_type {
    public:
        string opCode = "0110011";
        map<string,string> funct3;
        map<string,string> funct7;
        R_type() {
            funct3["add"] = "000";
            funct3["sub"] = "000";
            funct3["xor"] = "100";
            funct3["or"]  = "110";
            funct3["and"] = "111";
            funct3["sll"] = "001";
            funct3["srl"] = "101";
            funct3["sra"] = "101";
            funct3["slt"] = "010";
            funct3["sltu"]= "011";
            //
            funct7["add"] = "0000000";
            funct7["sub"] = "0100000";
            funct7["xor"] = "0000000";
            funct7["or"]  = "0000000";
            funct7["and"] = "0000000";
            funct7["sll"] = "0000000";
            funct7["srl"] = "0000000";
            funct7["sra"] = "0100000";
            funct7["slt"] = "0000000";
            funct7["sltu"]= "0000000";
        }
}; 
class I_type {
    public:
        string opCode = "0010011";
        map<string,string> funct3;
        I_type() {
            funct3["addi"] = "000";
            funct3["xori"] = "100";
            funct3["ori"]  = "110";
            funct3["andi"] = "111";
            funct3["slli"] = "001";
            funct3["srli"] = "101";
            funct3["srai"] = "101";
            funct3["slti"] = "010";
            funct3["sltiu"]= "011";
        }
};
class L_type {
    public:
    string opCode = "0000011";
    map<string,string> funct3;
    L_type() {
        funct3["lb"] = "000";
        funct3["lh"] = "001";
        funct3["lw"] = "010";
        funct3["lbu"]= "100";
        funct3["lhu"]= "101";
    }
};
class S_type {
    public:
    string opCode = "0100011";
    map<string,string> funct3;
    S_type() {
        funct3["sb"] = "000";
        funct3["sh"] = "001";
        funct3["sw"] = "010";
    }
};

class B_type {
    public:
    string opCode = "1100011";
    map<string,string> funct3;
    B_type() {
        funct3["beq"] = "000";
        funct3["bne"] = "001";
        funct3["blt"] = "100";
        funct3["bge"] = "101";
        funct3["bltu"]= "110";
        funct3["bgeu"]= "111";
    }
};
class J_type{
    public:
    string opCode = "1101111";
    map<string,string> funct3;
    J_type() {}
};
class JI_type{
    public:
        string opCode = "1100111";
        map<string,string> funct3;
        JI_type(){
            funct3["jalr"] = "000";
        }
};
class U_type{
    public:
        map<string,string> opCode;
        U_type(){
            opCode["lui"]  = "0110111";
            opCode["auipc"]= "0010111";
        }
};

class EI_type{
    public:
        string opCode = "1110011";
        map<string,string> funct3;
        EI_type() {
            funct3["ecall"] = "000";
            funct3["ebreak"]= "000";
        }
};


R_type R;
I_type I;
L_type L;
S_type S;
B_type B;
J_type J;
JI_type JI;
U_type U;
EI_type EI;


map<string,string> Type;
map<string,string> Reg;



vector<string> getInsPart(const string s)
{
    vector<string> res;
    int j = 0;
    for(int i = 0; i<s.size(); i++) {
        if(s[i] == ',' || s[i] == ' ' || s[i]== '(' || s[i] == ')') {
            string temp = s.substr(j,i-j);
            j = i+1;
            res.push_back(temp);
        }
    }
    if(j!=s.size()) {
        string temp = s.substr(j);
        res.push_back(temp);
    }
    return res;
}

string R_typeGetCode(vector<string>&  ins) {
    return R.funct7[ins[0]] +"_"+ Reg[ins[3]] +"_"+ Reg[ins[2]]
     +"_"+ R.funct3[ins[0]] +"_"+ Reg[ins[1]] + "_" +R.opCode;
}

string I_typeGetCode(vector<string>& ins) {
    int num = stoi(ins[3]);
    bitset<12> t(num);
    string imm = t.to_string();
    return  imm +"_"+ Reg[ins[2]]+"_"+ I.funct3[ins[0]] 
       +"_" + Reg[ins[1]]+"_"+ I.opCode;
}

string L_typeGetCode(vector<string>& ins) {
    int num = stoi(ins[2]);
    bitset<12> t(num);
    string imm = t.to_string();
    return imm +"_"+ Reg[ins[3]]+"_"+ L.funct3[ins[0]] 
       +"_" + Reg[ins[1]]+"_"+ L.opCode;
}

string S_typeGetCode(vector<string>& ins) {
    string res = "";
    int num = stoi(ins[2]);
    bitset<12> t(num);
    string imm = t.to_string();
    reverse(imm.begin(),imm.end());
    string temp = imm.substr(5);
    reverse(temp.begin(),temp.end());
    res += temp+"_";
    res += Reg[ins[1]]+"_";
    res += Reg[ins[3]]+"_";
    res += S.funct3[ins[0]]+"_";
    temp = imm.substr(0,4+1-0);
    reverse(temp.begin(),temp.end());
    res += temp+"_";
    res += S.opCode;
    return res;
}

string B_typeGetCode(vector<string>& ins) {
    string res = "";
    int num = stoi(ins[3]);
    bitset<13> t(num);
    string imm = t.to_string();
    reverse(imm.begin(),imm.end());
    res += imm.substr(12,12+1-12) + "_";
    string temp = imm.substr(5,10+1-5);
    reverse(temp.begin(),temp.end());
    res += temp+ "_";
    res += Reg[ins[2]]+ "_";
    res += Reg[ins[1]]+ "_";
    res += B.funct3[ins[0]]+ "_";
    temp = imm.substr(1,4+1-1);
    reverse(temp.begin(),temp.end());
    res += temp+ "_";
    res += imm.substr(11,11+1-11)+ "_";
    res += B.opCode;
    return res;
}

string J_typeGetCode(vector<string>& ins) {
    string res = "";
    string temp;
    int num = stoi(ins[2]);
    bitset<21> t(num);
    string imm = t.to_string();
    reverse(imm.begin(),imm.end());
    res += imm.substr(20,20+1-20)+"_";
    temp = imm.substr(1,10+1-1);
    reverse(temp.begin(),temp.end());
    res += temp+"_";
    res += imm.substr(11,11+1-11)+"_";
    temp = imm.substr(12,19+1-12);
    reverse(temp.begin(),temp.end());
    res += temp+"_";
    res += Reg[ins[1]]+"_";
    res += J.opCode;
    return res;
}

string JI_typeGetCode(vector<string>& ins) {
    int num = stoi(ins[3]);
    bitset<12> t(num);
    string imm = t.to_string();
    return imm +"_"+ Reg[ins[2]] +"_"+ JI.funct3[ins[0]]
        +"_"+ Reg[ins[1]] +"_"+ JI.opCode  ; 
}

string U_typeGetCode(vector<string>& ins) {
    int num = stoi(ins[2]);
    num = num << 12;
    bitset<32> t(num);
    string imm = t.to_string();
    reverse(imm.begin(),imm.end());
    string temp = imm.substr(12,31+1-12);
    reverse(imm.begin(),imm.end());
    return  temp +"_"+ Reg[ins[1]] +"_"+ U.opCode[ins[0]] ; 
}

string getCode(vector<string>& ins) {
    if(Type[ins[0]] == "R_type") 
        return R_typeGetCode(ins);
    else if(Type[ins[0]] == "I_type") 
        return I_typeGetCode(ins);
    else if(Type[ins[0]] == "L_type")
        return L_typeGetCode(ins);
    else if(Type[ins[0]] == "S_type")
        return S_typeGetCode(ins);
    else if(Type[ins[0]] == "B_type")
        return B_typeGetCode(ins);
    else if(Type[ins[0]] == "J_type")
        return J_typeGetCode(ins);
    else if(Type[ins[0]] == "JI_type")
        return JI_typeGetCode(ins);
    else if(Type[ins[0]] == "U_type")
        return U_typeGetCode(ins); 
    return "NONE";
}

void init() {
    Type["add"] = Type["sub"] = Type["xor"]
    = Type["or"] = Type["and"] = Type["and"]
    = Type["sll"] = Type["srl"] = Type["sra"]
    = Type["slt"] = Type["sltu"] = "R_type";

    Type["addi"] = Type["xori"] = Type["ori"]
    = Type["andi"] = Type["slli"] = Type["srli"]
    = Type["srai"] = Type["slti"] = Type["sltiu"]
    = "I_type";

    Type["lb"] = Type["lh"] = Type["lw"]
    = Type["lbu"] = Type["lhu"] = "L_type";

    Type["sb"] = Type["sh"] = Type["sw"]
    = "S_type";

    Type["beq"] = Type["bne"] = Type["blt"]
    = Type["bge"] = Type["bltu"] = Type["bgeu"]
    = "B_type";

    Type["jal"] = "J_type";

    Type["jalr"] = "JI_type";

    Type["lui"] = Type["auipc"] = "U_type";

    Type["ecall"] = Type["ebreak"] = "EI_type";

    for(int i = 0; i<32; i++) {
        string num = "x";
        num += to_string(i);
        Reg[num] = bitset<5>(i).to_string();
    }
}


int main()
{
    ifstream ReadFile("C:\\Users\\xiezexi\\Desktop\\Xcode\\input.txt");
    ofstream WriteFile("C:\\Users\\xiezexi\\Desktop\\Xcode\\output.txt");
    string in;
    init();
    int i = 0;
    while(getline(ReadFile,in)) {
        vector<string> temp = getInsPart(in);
        string ins_code = getCode(temp);
        WriteFile << setw(15) << left<< in << "=>";
        string get = "{InsME[" + to_string(i) + "]," + "InsME[" + to_string(i+1)
            + "]," + "InsME[" + to_string(i+2) + "]," + "InsME[" + to_string(i+3)
            + "]}";
        WriteFile << setw(42) << left << get << "= ";
        WriteFile << ins_code << endl;
        i += 4;
    }
    return 0;
}