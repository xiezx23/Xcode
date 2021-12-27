`timescale 1ns / 1ps
module PC(
        input CLK,               //时钟
        input Reset,             //是否重置地址。1-初始化PC，否则接受新地址
        input PCSrc,             //数据选择器输入
        input [31:0] AluOutput,  //ALU计算结果
        input PCdelay,
        input [31:0] prePC,
        output reg[31:0] curPC  //当前指令的地址
    );

    initial begin
        curPC <= -4; //初始值为-4
    end

    
    //检测时钟上升沿计算新指令地址 
    always@(posedge CLK or posedge Reset)
    begin
        if(Reset) //复位置1时把PC归零
        begin
            curPC <= 0;
        end
        else begin
            if (PCdelay) begin
                curPC <= prePC;
            end
            else begin
                case(PCSrc)   //仿真时
                    1'b0:   curPC <= curPC + 4;
                    1'b1:   curPC <= AluOutput;
                endcase
            end
        end
    end

endmodule
