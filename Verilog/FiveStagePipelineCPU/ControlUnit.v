`timescale 1ns / 1ps
//Control Unit
module ControlUnit(
        input [7:0] op,         //操作码
        input [2:0] funct3,     //3位功能码
        input [6:0] funct7,     //7位功能码
        output reg[2:0] AluOp,  //ALU操作方式
        output reg Alu1Src,     //ALU1口位选
        output reg Alu2Src,     //ALU2口位选
        output reg[1:0] RegDst, //Rd输入数据来源
        output reg[2:0] ExtSel, //立即数拼接方式
        output reg Sign,        //立即数符号扩展信号
        output reg[1:0] Digit,  //读写位数
        output reg DataWr,      //存储器写使能
        output reg immres       //rd是否选择imm直接作为数据
    );
    initial begin
        AluOp = 3'b000;  //默认ALU加法
        Alu1Src = 0;
        Alu2Src = 0;
        RegDst = 2'b00;  //默认ALU输出为Rd输入
        ExtSel = 3'b000;
        Sign = 1;        //默认带符号扩展
        Digit = 2'b10;   //默认32位读写
        DataWr = 0;      //默认关闭写存储器
    end

    always@(op or funct3 or funct7) 
    begin
        immres = (op == 7'b0110111) ? 1 : 0;   //lui直接让立即数作为rd输入

        case(op)
            //R type
            7'b0110011:
            begin
                case(funct3)
                    //add&sub
                    3'b000:
                    begin
                        //add
                        if (funct7 == 7'b0000000) begin
                            AluOp = 3'b000;
                            Alu1Src = 0;
                            Alu2Src = 0;
                            RegDst = 2'b00;
                            DataWr = 0;
                            Digit = 2'b10;   //默认32位读写
                        end
                        //sub
                        else begin
                            AluOp = 3'b001;
                            Alu1Src = 0;
                            Alu2Src = 0;
                            RegDst = 2'b00;
                            DataWr = 0;
                            Digit = 2'b10;   //默认32位读写
                        end
                    end
                    //xor
                    3'b100:
                    begin
                        AluOp = 3'b010;
                        Alu1Src = 0;
                        Alu2Src = 0;
                        RegDst = 2'b00;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                    //or
                    3'b110:
                    begin
                        AluOp = 3'b011;
                        Alu1Src = 0;
                        Alu2Src = 0;
                        RegDst = 2'b00;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                    //and
                    3'b111:
                    begin
                        AluOp = 3'b100;
                        Alu1Src = 0;
                        Alu2Src = 0;
                        RegDst = 2'b00;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                    //sll
                    3'b001:
                    begin
                        AluOp = 3'b101;
                        Alu1Src = 0;
                        Alu2Src = 0;
                        RegDst = 2'b00;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                    //srl&sra
                    3'b101:
                    begin
                        //srl
                        if (funct7 == 7'b0000000) begin
                            AluOp = 3'b110;
                            Alu1Src = 0;
                            Alu2Src = 0;
                            RegDst = 2'b00;
                            DataWr = 0;
                            Digit = 2'b10;   //默认32位读写
                        end
                        //sra
                        else begin
                            AluOp = 3'b111;
                            Alu1Src = 0;
                            Alu2Src = 0;
                            RegDst = 2'b00;
                            DataWr = 0;
                            Digit = 2'b10;   //默认32位读写
                        end
                    end
                    //slt
                    3'b010:
                    begin
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b11;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                    //sltu
                    3'b011:
                    begin
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b11;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                endcase
            end
            //I type1
            7'b0010011:
            begin
                case(funct3)
                    //addi
                    3'b000:
                    begin
                        AluOp = 3'b000;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b00;
                        ExtSel = 3'b000;
                        Sign = 1;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                    //xori
                    3'b100:
                    begin
                        AluOp = 3'b010;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b00;
                        ExtSel = 3'b000;
                        Sign = 1;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                    //ori
                    3'b110:
                    begin
                        AluOp = 3'b011;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b00;
                        ExtSel = 3'b000;
                        Sign = 1;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                    //andi
                    3'b111:
                    begin
                        AluOp = 3'b100;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b00;
                        ExtSel = 3'b000;
                        Sign = 1;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                    //slli
                    3'b001:
                    begin
                        AluOp = 3'b101;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b00;
                        ExtSel = 3'b101;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                    //srli&srai
                    3'b101:
                    begin
                        //srli
                        if (funct7 == 7'b0000000) begin
                            AluOp = 3'b101;
                            Alu1Src = 0;
                            Alu2Src = 1;
                            RegDst = 2'b00;
                            ExtSel = 3'b101;
                            DataWr = 0;
                            Digit = 2'b10;   //默认32位读写
                        end
                        //srai
                        else begin
                            AluOp = 3'b110;
                            Alu1Src = 0;
                            Alu2Src = 1;
                            RegDst = 2'b00;
                            ExtSel = 3'b101;
                            DataWr = 0;
                            Digit = 2'b10;   //默认32位读写
                        end
                    end
                    //slti
                    3'b010:
                    begin
                        Alu1Src = 0;
                        Alu2Src = 0;
                        RegDst = 2'b11;
                        ExtSel = 3'b000;
                        Sign = 1;
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                    //sltiu
                    3'b011:
                    begin
                        Alu1Src = 0;
                        Alu2Src = 0;
                        RegDst = 2'b11;
                        ExtSel = 3'b000;
                        Sign = 0; //无符号扩展
                        DataWr = 0;
                        Digit = 2'b10;   //默认32位读写
                    end
                endcase
            end
            //I type2
            7'b0000011:
            begin
                case(funct3)
                    //lb
                    3'b000:
                    begin
                        AluOp = 3'b000;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b01;
                        ExtSel = 3'b000;
                        Sign = 1;
                        Digit = 2'b00;
                        DataWr = 0;
                    end
                    //lh
                    3'b001:
                    begin
                        AluOp = 3'b000;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b01;
                        ExtSel = 3'b000;
                        Sign = 1;
                        Digit = 2'b01;
                        DataWr = 0;
                    end
                    //lw
                    3'b010:
                    begin
                        AluOp = 3'b000;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b01;
                        ExtSel = 3'b000;
                        Sign = 1;
                        Digit = 2'b10;
                        DataWr = 0;
                    end
                    //lbu
                    3'b100:
                    begin
                        AluOp = 3'b000;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b01;
                        ExtSel = 3'b000;
                        Sign = 0;
                        Digit = 2'b00;
                        DataWr = 0;
                    end
                    //lhu
                    3'b101:
                    begin
                        AluOp = 3'b000;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b01;
                        ExtSel = 3'b000;
                        Sign = 0;
                        Digit = 2'b01;
                        DataWr = 0;
                    end
                endcase
            end
            //S type
            7'b0100011:
            begin
                case(funct3)
                    //sb
                    3'b000:
                    begin
                        AluOp = 3'b000;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        ExtSel = 3'b001;
                        Sign = 1;
                        Digit = 2'b00;
                        DataWr = 1;
                    end
                    //sh
                    3'b001:
                    begin
                        AluOp = 3'b000;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        ExtSel = 3'b001;
                        Sign = 1;
                        Digit = 2'b01;
                        DataWr = 1;
                    end
                    //sw
                    3'b010:
                    begin
                        AluOp = 3'b000;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        ExtSel = 3'b001;
                        Sign = 1;
                        Digit = 2'b10;
                        DataWr = 1;
                    end
                endcase
            end
            //B type
            7'b1100011:
            begin
                AluOp = 3'b000;
                Sign = 1;
                Digit = 2'b10;   //默认32位读写
                ExtSel = 3'b010;
                DataWr = 0;
                Alu1Src = 1;
                Alu2Src = 1;
            end
            //J type
            7'b1101111:
            begin
                case(funct3)
                    //jal
                    3'b000:
                    begin
                        AluOp = 3'b000;
                        Alu1Src = 1;
                        Alu2Src = 1;
                        RegDst = 2'b10;
                        ExtSel = 3'b100;
                        Sign = 1;
                        Digit = 2'b10;
                        DataWr = 0;
                    end
                endcase
            end
            //I type3
            7'b1100111:
            begin
                case(funct3)
                    //jalr
                    3'b000:
                    begin
                        AluOp = 3'b000;
                        Alu1Src = 0;
                        Alu2Src = 1;
                        RegDst = 2'b10;
                        ExtSel = 3'b000;
                        Sign = 1;
                        Digit = 2'b10;
                        DataWr = 0;
                    end
                endcase
            end
            //U type1
            7'b0110111:
            //lui
            begin
                ExtSel = 3'b011;
                Sign = 1;
                Digit = 2'b10;
                DataWr = 0;
            end
            //U type2
            7'b0010111:
            //auipc
            begin
                AluOp = 3'b000;
                Alu1Src = 1;
                Alu2Src = 1;
                RegDst = 2'b00;
                ExtSel = 3'b011;
                Sign = 1;
                Digit = 2'b10;
                DataWr = 0;
            end
        endcase
    end
endmodule