`timescale 1ns / 1ps

module InsMEM(
        input [31:0] curPC,
        output reg[7:0] op,
        output reg[2:0] funct3,
        output reg[6:0] funct7,
        output reg[4:0] rs1,
        output reg[4:0] rs2,
        output reg[4:0] rd,
        output reg[24:0] imm
    );
    reg [7:0] rom[128:0];  //存储器定义必须用reg类型，存储器存储单元8位长度，共128个存储单元，可以存32条指令
    reg [31:0] instr;

    // 加载数据到存储器rom
    initial begin
        //$readmemb("地址\\rom.txt", rom);
        op = 7'b0000000;
        funct3 = 3'b000;
        funct7 = 7'b0000000;
        rs1 = 5'b00000;
        rs2 = 5'b00000;
        imm = 20'b00000000000000000000;
    end

    //小端模式,PC改变就取指令
    always@(curPC)
    begin
        //取指令
        begin
            instr[7:0] = rom[curPC];
            instr[15:8] = rom[curPC + 1];
            instr[23:16] = rom[curPC + 2];
            instr[31:24] = rom[curPC + 3];
        end 
    end
    //切割指令
    always@(instr) 
    begin
        op = instr[6:0];
        rs1 = instr[19:15];
        rs2 = instr[24:20];
        rd = instr[11:7];
        funct3 = instr[14:12];
        funct7 = instr[31:26];
        imm = instr[31:7];
    end

endmodule