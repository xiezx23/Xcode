`timescale 1ns / 1ps
//位于ID译码上升沿阶段，当上一条指令是load且出现RAW时
//把本条PC送回PC模块使PC延时
//把功能块工作使能 Mwk(module work)置0，使该指令对后续功能块失效
module Bubble(
        input CLK,  //时钟脉冲
        input clear,
        input [6:0] preop,
        input [4:0] prerd,
        input [4:0] rs1,
        input [4:0] rs2,
        output reg Mwk,
        output reg PCdelay
    );
    reg Mwktmp;
    initial begin
        Mwk <= 0;
        PCdelay <= 0;
    end
    always @(negedge CLK) begin
        Mwk <= Mwktmp;
    end
    //检测上一条指令是load（I type2指令）
    always @(preop or clear) begin
        if (clear) begin
            Mwktmp <= 0;
            PCdelay <= 0;
        end
        else begin
            if (preop == 7'b0000011) begin
                if (rs1 == prerd) begin
                    Mwktmp <= 0;
                    PCdelay <= 1;
                end
                else if (rs2 == prerd) begin
                    Mwktmp <= 0;
                    PCdelay <= 1;
                end
                else begin
                    Mwktmp <= 1;
                    PCdelay <= 0;
                end
            end
            else begin
                Mwktmp <= 1;
                PCdelay <= 0;
            end
        end
    end
endmodule