`timescale 1ns / 1ps
module reg32(
        input CLK,  //时钟脉冲
        input [31:0] datain,
        output reg[31:0] dataout
    );
    initial begin
        dataout = 0;
    end
    always @(negedge CLK) begin
        dataout <= datain;
    end
endmodule