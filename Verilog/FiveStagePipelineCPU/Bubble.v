`timescale 1ns / 1ps
//位于ID译码上升沿阶段，当上一条指令是load且出现RAW时
//把本条PC送回PC模块使PC延时
//把功能块工作使能 Mwk(module work)置0，使该指令对后续功能块失效
module Bubble(
        input CLK,  //时钟脉冲
        input in,
        input clear,
        input [6:0] preop,
        input [4:0] prerd,
        input [4:0] rs1,
        input [4:0] rs2,
        output reg Mwk,
        output reg PCdelay
    );
    initial begin
        Mwk <= 0;
        PCdelay <= 0;
    end
    //检测上一条指令是load（I type2指令）
    always @(posedge CLK) begin
        if (in) begin
            if (clear) begin
                Mwk <= 0;
                PCdelay <= 0;
            end
            else begin
                case (preop)
                    //halt
                    7'b1111111:begin
                        Mwk <= 0;
                        PCdelay <= 1;
                    end
                    //R type -> rs1, rs2
                    7'b0110011: 
                    begin
                        if (rs1 == prerd) begin
                            Mwk <= 0;
                            PCdelay <= 1;
                        end
                        else if (rs2 == prerd) begin
                            Mwk <= 0;
                            PCdelay <= 1;
                        end
                        else begin
                            Mwk <= 1;
                            PCdelay <= 0;
                        end
                    end
                    //B type -> rs1, rs2
                    7'b1100011:
                    begin
                        if (rs1 == prerd) begin
                            Mwk <= 0;
                            PCdelay <= 1;
                        end
                        else if (rs2 == prerd) begin
                            Mwk <= 0;
                            PCdelay <= 1;
                        end
                        else begin
                            Mwk <= 1;
                            PCdelay <= 0;
                        end
                    end
                    //default -> rs1
                    default: 
                    begin
                        if (rs1 == prerd) begin
                            Mwk <= 0;
                            PCdelay <= 1;
                        end
                        else begin
                            Mwk <= 1;
                            PCdelay <= 0;
                        end
                    end
                endcase
            end
        end
        else begin 
            Mwk <= 0;
            PCdelay <= 0;
        end
    end
endmodule