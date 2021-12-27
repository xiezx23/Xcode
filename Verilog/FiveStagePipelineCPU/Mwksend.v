`timescale 1ns / 1ps
module Mwksend(
        input CLK,  //时钟脉冲
        input clear,
        output reg out
    );
    initial begin
        out = 0;
    end
    always @(negedge CLK) begin
        if (clear) begin
            out <= 0;
        end
        else begin
            out <= 1;
        end
    end
endmodule