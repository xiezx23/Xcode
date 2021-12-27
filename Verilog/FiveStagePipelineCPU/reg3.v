`timescale 1ns / 1ps
module reg3(
        input CLK,  //时钟脉冲
        input [2:0] datain,
        output reg[2:0] dataout
    );
    initial begin
        dataout = 0;
    end
    always @(negedge CLK) begin
        dataout <= datain;
    end
endmodule