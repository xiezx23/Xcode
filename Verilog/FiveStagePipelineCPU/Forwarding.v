`timescale 1ns / 1ps
//转发模块
//在EXE阶段的上升沿开始工作
module Forwarding(
        input CLK,  //时钟脉冲
        input [4:0] rs1,
        input [4:0] rs2,
        input [31:0] ReadData1,
        input [31:0] ReadData2,
        input preMwk, //pre
        input preRegWr,
        input [1:0] preRegDst,
        input [4:0] prerd,
        input [1:0] precmp,
        input [31:0] preAluOutput,
        input ppreMwk,//ppre
        input ppreRegWr,
        input [1:0] ppreRegDst,
        input [4:0] pprerd,
        input [1:0] pprecmp,
        input [31:0] ppreAluOutput,
        input [31:0] ppreDataOut,

        output reg [31:0] RD1,
        output reg [31:0] RD2
    );
    initial begin
        RD1 <= 0;
        RD2 <= 0;
    end
    always @(posedge CLK) begin
        //处理rs1冒险
        RD1 = ReadData1;
        if (ppreMwk) begin
            if (pprerd == rs1) begin
                if(ppreRegWr)begin
                    case (ppreRegDst)
                        2'b00: begin
                            RD1 = ppreAluOutput;
                        end 
                        2'b01: begin
                            RD1 = ppreDataOut;
                        end 
                        2'b10: begin
                            // RD1 = PC+4;
                            RD1 = ReadData1;
                        end 
                        2'b11: begin
                            RD1[31:1] = 0;
                            RD1[0] = pprecmp[0];
                        end
                    endcase
                end
            end
        end

        if (preMwk) begin
            if (prerd == rs1) begin
                if(preRegWr)begin
                    case (preRegDst)
                        2'b00: begin
                            RD1 = preAluOutput;
                        end 
                        2'b10: begin
                            // RD1 = PC+4;
                            RD1 = ReadData1;
                        end 
                        2'b11: begin
                            RD1[31:1] = 0;
                            RD1[0] = precmp[0];
                        end
                    endcase
                end
            end
        end
        //处理rs2冒险
        RD2 = ReadData2;
        if (ppreMwk) begin
            if (pprerd == rs2) begin
                if(ppreRegWr)begin
                    case (ppreRegDst)
                        2'b00: begin
                            RD2 = ppreAluOutput;
                        end 
                        2'b01: begin
                            RD2 = ppreDataOut;
                        end 
                        2'b10: begin
                            // RD2 = PC+4;
                            RD2 = ReadData2;
                        end 
                        2'b11: begin
                            RD2[31:1] = 0;
                            RD2[0] = pprecmp[0];
                        end
                    endcase
                end
            end
        end

        if (preMwk) begin
            if (prerd == rs2) begin
                if(preRegWr)begin
                    case (preRegDst)
                        2'b00: begin
                            RD2 = preAluOutput;
                        end 
                        2'b10: begin
                            // RD2 = PC+4;
                            RD2 = ReadData2;
                        end 
                        2'b11: begin
                            RD2[31:1] = 0;
                            RD2[0] = precmp[0];
                        end
                    endcase
                end
            end
        end
    end
endmodule