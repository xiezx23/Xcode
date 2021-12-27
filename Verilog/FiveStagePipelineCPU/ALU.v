`timescale 1ns / 1ps
module ALU(
        input CLK,
        input Mwk,
        input [7:0] op,         //操作码
        input [2:0] funct3,     //3位功能码
        input ALUSrc1,          //输入端1位选
        input ALUSrc2,          //输入端2位选
        input [31:0] ReadData1, //rs1寄存器读取数据
        input [31:0] ReadData2, //rs2寄存器读取数据
        input [31:0] extend,    //扩展后立即数
        input [31:0] PC,        //当前地址用于计算跳转地址
        input [2:0] AluOp,      //ALU功能码
        output reg[1:0] cmp,    //比较器输出结果
        output reg[31:0] AluOutput, //ALU计算结果
        output reg PCSrc,
        output reg RegWr,
        output reg clear
    );
    reg PCSrctmp;
    reg [31:0] A;
    reg [31:0] B;
    reg [31:0] C;

    initial begin
        RegWr <= 0;
        RegWr <= 0;
        PCSrctmp <= 0;
        PCSrc <= 0;
        clear <= 0;
    end

    always @(negedge CLK) begin
        if (Mwk) begin
            PCSrc <= PCSrctmp;
        end
        else begin
            PCSrc <= 0;
            RegWr <= 0;
        end
    end

    always@(ReadData1 or ReadData2 or ALUSrc1 or ALUSrc2 or AluOp or PC or extend) 
    begin
        //为两个输入端口赋值
        A = (ALUSrc1 == 0) ? ReadData1 : PC;
        B = (ALUSrc2 == 0) ? ReadData2 : extend;
        C = (ALUSrc2 == 1) ? ReadData2 : extend;
        //比较器部分
        //00 -> "=="     01 ->  "<"     10 ->  ">"
        //当cmp[0] == 0时代表>=，当cmp[1] == 0时代表<=
        if ($signed(ReadData1) == $signed(C)) begin
            cmp <= 2'b00;
        end
        else begin
            if ($signed(ReadData1) < $signed(C)) begin
                cmp <= 2'b01;
            end
            else begin
                cmp <= 2'b10;
            end
        end
        // $display("cmp:%d r1:%d c:%d",cmp,$signed(ReadData1),C);
        //ALU部分
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
        // $display("aluop: %d // A(%d): %d // B(%d): %d",AluOp,ALUSrc1,A,ALUSrc2,B);
        // $display("aluoutput: %d\n",AluOutput);
    end 

    always @(cmp or op or funct3) begin
        if (Mwk) begin
            clear = 0;
            if (op == 7'b1111111) begin
                RegWr <= 0;
                PCSrctmp <= 0;
                clear <= 0;
            end
            else begin
                if(op == 7'b1100011) begin
                    RegWr <= 0;
                    case(funct3)
                        //beq
                        3'b000:
                        begin
                            if (cmp == 2'b00)
                            begin
                                PCSrctmp = 1;
                                clear = 1;
                            end
                            else 
                                PCSrctmp = 0;
                        end
                        //bne
                        3'b001:
                        begin
                            if (cmp != 2'b00) begin
                                PCSrctmp = 1;
                                clear = 1;
                            end
                            else 
                                PCSrctmp = 0;
                        end
                        //blt
                        3'b100:
                        begin
                            if (cmp == 2'b01) begin
                                PCSrctmp = 1;
                                clear = 1;
                            end
                            else
                                PCSrctmp = 0;
                        end
                        //bge
                        3'b101:
                        begin
                            if (cmp == 2'b10) begin
                                PCSrctmp = 1;
                                clear = 1;
                            end
                            else
                                PCSrctmp = 0;
                        end
                        //bltu
                        3'b110:
                        begin
                            if (cmp == 2'b01) begin
                                PCSrctmp = 1;
                                clear = 1;
                            end
                            else
                                PCSrctmp = 0;
                        end
                        //bgeu
                        3'b111:
                        begin
                            if (cmp == 2'b10) begin
                                PCSrctmp = 1;
                                clear = 1;
                            end
                            else
                                PCSrctmp = 0;
                        end
                    endcase
                end
                else begin
                    if (op == 7'b0100011) begin
                        RegWr <= 0;
                        PCSrctmp <= 0;
                    end
                    else begin
                        //jal
                        if (op == 7'b1101111) begin
                            PCSrctmp <= 1;
                            clear <= 1;
                            RegWr <= 1;
                        end
                        else begin
                            if (op == 7'b1100111) begin
                                PCSrctmp <= 1;
                                clear <= 1;
                                RegWr <= 1;
                            end
                            else begin
                                PCSrctmp <= 0;
                                RegWr <= 1;
                                clear <= 0;
                            end
                        end
                    end
                end
            end
        end
        else clear <= 0;
    end
endmodule
