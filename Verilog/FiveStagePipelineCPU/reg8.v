`timescale 1ns / 1ps
module reg8(
        input CLK,  //ζΆιθε²
        input [7:0] datain,
        output reg[7:0] dataout
    );
    initial begin
        dataout = 0;
    end
    always @(negedge CLK) begin
        dataout <= datain;
    end
endmodule