`timescale 1ns / 1ps
module ALU(
        input ALUSrc1,
        input ALUSrc2,
        input [31:0] ReadData1,
        input [31:0] ReadData2,
        input [31:0] extend,
        input [31:0] PC,
        input [2:0] AluOp,
        output reg[31:0] AluOutput
    );

    reg [31:0] A;
    reg [31:0] B;

    always@(ReadData1 or ReadData2 or ALUSrc1 or ALUSrc2 or AluOp or PC or extend) 
    begin
        //为两个输入端口赋值
        A = (ALUSrc1 == 0) ? ReadData1 : PC;
        B = (ALUSrc2 == 0) ? ReadData2 : extend;
        case(AluOp)
            3'b000: AluOutput = A + B;
            3'b001: AluOutput = A - B;
            3'b010: AluOutput = A ^ B;
            3'b011: AluOutput = A | B;
            3'b100: AluOutput = A & B;
            3'b101: AluOutput = A << B;
            3'b110: AluOutput =  A >> B; //逻辑右移
            3'b111: AluOutput = ( $signed(A) ) >>> B; //算术右移
        endcase;
    end 
endmodule
