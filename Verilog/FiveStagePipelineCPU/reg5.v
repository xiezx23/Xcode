`timescale 1ns / 1ps
module reg5(
        input CLK,  //时钟脉冲
        input [4:0] datain,
        output reg[4:0] dataout
    );
    initial begin
        dataout = 0;
    end
    always @(negedge CLK) begin
        dataout <= datain;
    end
endmodule