`timescale 1ns / 1ps
module controlReg(
        input CLK,            //时钟脉冲
        input [2:0] AluOpIn,  //ALU操作方式
        input  Alu1SrcIn,     //ALU1口位选
        input  Alu2SrcIn,     //ALU2口位选
        input [1:0] RegDstIn, //Rd输入数据来源
        input [2:0] ExtSelIn, //立即数拼接方式
        input  SignIn,        //立即数符号扩展信号
        input [1:0] DigitIn,  //读写位数
        input  DataWrIn,      //存储器写使能
        input  immresIn,      //rd是否选择imm直接作为数据

        output reg[2:0] AluOpOut,  //ALU操作方式
        output reg Alu1SrcOut,     //ALU1口位选
        output reg Alu2SrcOut,     //ALU2口位选
        output reg[1:0] RegDstOut, //Rd输入数据来源
        output reg[2:0] ExtSelOut, //立即数拼接方式
        output reg SignOut,        //立即数符号扩展信号
        output reg[1:0] DigitOut,  //读写位数
        output reg DataWrOut,      //存储器写使能
        output reg immresOut      //rd是否选择imm直接作为数据
    );

    always @(negedge CLK) begin
        AluOpOut <= AluOpIn;
        Alu1SrcOut <= Alu1SrcIn;
        Alu2SrcOut <= Alu2SrcIn;
        RegDstOut <= RegDstIn;
        ExtSelOut <= ExtSelIn;
        SignOut <= SignIn;
        DigitOut <= DigitIn;
        DataWrOut <= DataWrIn;
        immresOut <= immresIn;
    end
endmodule