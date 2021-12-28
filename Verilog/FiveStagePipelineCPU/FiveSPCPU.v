`timescale 1ns / 1ps

module FiveSPCPU(
        input CLK,                //时钟信号
        input Reset,              //复位信号
        output [31:0] curPC,      //当前地址
        output [4:0] rs1,         //rs1地址
        output [31:0] ReadData1,  //rs1内数据
        output [4:0] rs2,         //rs2地址
        output [31:0] ReadData2,  //rs2内数据
        output [31:0] AluOutput,  //alu计算结果
        output [31:0] DB,         //DB总线数据

        output [31:0] instr,      //指令
        output [7:0] op,          //操作码
        output [4:0] rd           //rd地址
    );

    wire[24:0] imm;        //指令分割imm段
    wire [31:0] extend;    //立即数
    wire [2:0] funct3;
    wire [6:0] funct7;
    wire [31:0] DataOut;   //存储器读数据
    wire [1:0] cmp;      //比较器输出
    //控制信号
    wire PCSrc;
    wire [2:0] AluOp;
    wire AluSrc1;
    wire AluSrc2;
    wire RegWr;
    wire [1:0]RegDst;
    wire [2:0] ExtSel;
    wire Sign;
    wire [1:0] Digit;
    wire DataWr;
    wire immres;
    wire PCdelay;

    wire [31:0] curPC_1;
    wire Mwk_0;

    wire [31:0] RD1, RD2, extend_2, ReadData1_2, ReadData2_2, curPC_2;
    wire [2:0] AluOp_2, ExtSel_2, funct3_2;
    wire  Mwk_2,AluSrc1_2,AluSrc2_2,Sign_2,DataWr_2,immres_2; 
    wire [1:0] RegDst_2, Digit_2;
    wire [4:0] rs1_2, rs2_2, rd_2;
    wire [7:0] op_2, op_3, op_4;

    wire [31:0] AluOutput_3, extend_3, ReadData2_3, curPC_3;
    wire Mwk_3, DataWr_3, immres_3, RegWr_3; 
    wire [1:0] RegDst_3, Digit_3, cmp_3;
    wire [4:0] rs1_3, rs2_3, rd_3;

    
    wire [31:0] AluOutput_4, extend_4, curPC_4;
    wire Mwk_4, immres_4, RegWr_4; 
    wire [1:0] RegDst_4, Digit_4, cmp_4;
    wire [4:0] rs1_4, rs2_4, rd_4;
    wire clear;
    reg zero;
    initial begin
        zero = 0;
    end

    //IF取指令阶段
    //上升沿更新PC，下降沿取指令
    PC pc1(
        .CLK(CLK),       //时钟
        .Reset(Reset),   //是否重置地址
        .PCSrc(PCSrc),   //数据选择器输入
        .AluOutput(AluOutput_3), //ALU计算结果
        .PCdelay(PCdelay),
        .prePC(curPC_1),
        .curPC(curPC)    //当前指令的地址
    );
    InsMEM insmem(
        .CLK(CLK),
        .curPC(curPC),   //PC值
        .op(op),         //操作码位段
        .funct3(funct3), //3位功能码位段
        .funct7(funct7), //7位功能码位段
        .rs1(rs1),       //rs2地址位段
        .rs2(rs2),       //rs2地址位段
        .rd(rd),         //rd地址位段
        .imm(imm),       //立即数位段传给extend模块拼接扩展
        .instr(instr)    //读取得到32位指令
    );
    reg32 r32_0(
        .CLK(CLK),
        .datain(curPC),
        .dataout(curPC_1)
    );

    //ID译码阶段
    //上升沿检测load-use
    //下降沿把read1,read2,rd,extend,控制信号写入寄存器
    Bubble bb(
        .CLK(CLK),
        .clear(clear),
        .preop(op_2),
        .prerd(rd_2),
        .rs1(rs1),
        .rs2(rs2),
        .Mwk(Mwk),  //IF-ID间工作信号
        .PCdelay(PCdelay)
    );

    Extend ext(
        .imm(imm),        //立即数字段
        .Sign(Sign),      //扩展符号
        .ExtSel(ExtSel),  //扩展方式
        .extend(extend)   //扩展后立即数
    );
    // RegisterFile regfile(
    //     .CLK(CLK),         //时钟
    //     .immres(immres_4),   //立即数直接写入信号
    //     .rs1(rs1),         //rs1寄存器地址输入端口
    //     .rs2(rs2),         //rs2寄存器地址输入端口
    //     .WriteReg(rd_4),
    //     .AluOutput(immres_4), //ALU输出
    //     .extend(extend_4),       //imm扩展器输出
    //     .Datain(DataOut),      //存储器输出
    //     .PC(curPC_4),            //当前PC值
    //     .cmp(cmp_4),             //比较器输出
    //     .RegDst(RegDst_4),       //输入具体数据位选
    //     .RegWr(RegWr_4),         //写使能信号，为1时在时钟边沿触发写入
    //     .DB(DB),               //输入总线数据
    //     .ReadData1(ReadData1), //rs1寄存器数据输出端口
    //     .ReadData2(ReadData2)  //rs2寄存器数据输出端口
    // );
    ControlUnit control(
        .op(op),          //操作码
        .funct3(funct3),  //3位功能码
        .funct7(funct7),  //7位功能码
        .AluOp(AluOp),    //ALU操作
        .Alu1Src(AluSrc1),   //ALU1口
        .Alu2Src(AluSrc2),   //ALU2口
        .RegDst(RegDst),  //Rd位选
        .ExtSel(ExtSel),  //立即数扩展式
        .Sign(Sign),      //立即数符号扩展
        .Digit(Digit),    //读写位数
        .DataWr(DataWr),  //存储器写使能
        .immres(immres)   //rd是否选择imm直接作为数据
    );
    controlReg cr_1(
        .CLK(CLK),
        .AluOpIn(AluOp),
        .Alu1SrcIn(AluSrc1),
        .Alu2SrcIn(AluSrc2),
        .RegDstIn(RegDst),
        .ExtSelIn(ExtSel),
        .SignIn(Sign),
        .DigitIn(Digit),
        .DataWrIn(DataWr),
        .immresIn(immres),

        .AluOpOut(AluOp_2),
        .Alu1SrcOut(AluSrc1_2),
        .Alu2SrcOut(AluSrc2_2),
        .RegDstOut(RegDst_2),
        .ExtSelOut(ExtSel_2),
        .SignOut(Sign_2),
        .DigitOut(Digit_2),
        .DataWrOut(DataWr_2),
        .immresOut(immres_2)
    );
    AddressReg ar_1(
        .clear(clear | PCdelay),
        .CLK(CLK),
        .rs1In(rs1),
        .rs2In(rs2),
        .rdIn(rd),
        .MwkIn(Mwk),
        .rs1Out(rs1_2),
        .rs2Out(rs2_2),
        .rdOut(rd_2),
        .MwkOut(Mwk_2) //ID-EXE间工作信号
    );
    reg32 r32_1(
        .CLK(CLK),
        .datain(extend),
        .dataout(extend_2)
    );
    reg32 r32_2(
        .CLK(CLK),
        .datain(ReadData1),
        .dataout(ReadData1_2)
    );
    reg32 r32_3(
        .CLK(CLK),
        .datain(ReadData2),
        .dataout(ReadData2_2)
    );
    reg32 r32_4(
        .CLK(CLK),
        .datain(curPC_1),
        .dataout(curPC_2)
    );
    reg8 r8_1(
        .CLK(CLK),
        .datain(op),
        .dataout(op_2)
    );
    reg3 r3_1(
        .CLK(CLK),
        .datain(funct3),
        .dataout(funct3_2)
    );

    //EXE阶段
    //下降沿把alu结果写入寄存器，把PCSrc送回PC模块
    Transmit fw(  //转发技术模块
        .CLK(CLK),
        .rs1(rs1_2),
        .rs2(rs2_2),
        .ReadData1(ReadData1_2),
        .ReadData2(ReadData2_2),
        .preMwk(Mwk_3),
        .preRegWr(RegWr_3),
        .preRegDst(RegDst_3),
        .preop(op_3),
        .prerd(rd_3),
        .precmp(cmp_3),
        .preAluOutput(AluOutput_3),
        .ppreMwk(Mwk_4),
        .ppreRegWr(RegWr_4),
        .ppreRegDst(RegDst_4),
        .ppreop(op_4),
        .pprerd(rd_4),
        .pprecmp(cmp_4),
        .ppreAluOutput(AluOutput_4),
        .ppreDataOut(DataOut),
        .RD1(RD1),
        .RD2(RD2)   
    );

    ALU alu1(
        .CLK(CLK),
        .Mwk(Mwk_2),
        .op(op_2),
        .funct3(funct3_2),
        .ALUSrc1(AluSrc1_2),     //输入端1位选
        .ALUSrc2(AluSrc2_2),     //输入端2位选
        .ReadData1(RD1), //rs1寄存器读取数据
        .ReadData2(RD2), //rs2寄存器读取数据
        .extend(extend_2),       //扩展后立即数
        .PC(curPC_2),            //当前地址用于计算跳转地址
        .AluOp(AluOp_2),         //ALU功能码
        .cmp(cmp),             //比较器输出结果
        .AluOutput(AluOutput),  //ALU计算结果
        .PCSrc(PCSrc),
        .RegWr(RegWr),
        .clear(clear)
    );
    reg8 r8_2(
        .CLK(CLK),
        .datain(op_2),
        .dataout(op_3)
    );
    reg32 r32_5(
        .CLK(CLK),
        .datain(AluOutput),
        .dataout(AluOutput_3)
    );
    reg32 r32_6(
        .CLK(CLK),
        .datain(curPC_2),
        .dataout(curPC_3)
    );
    reg32 r32_7(
        .CLK(CLK),
        .datain(RD2),
        .dataout(ReadData2_3)
    );
    reg32 r32_8(
        .CLK(CLK),
        .datain(extend_2),
        .dataout(extend_3)
    );
    AddressReg ar_2(
        .clear(zero),
        .CLK(CLK),
        .rs1In(rs1_2),
        .rs2In(rs2_2),
        .rdIn(rd_2),
        .MwkIn(Mwk_2),
        .rs1Out(rs1_3),
        .rs2Out(rs2_3),
        .rdOut(rd_3),
        .MwkOut(Mwk_3) //EXE-MEM间工作信号
    );
    MEMreg mr_1(
        .CLK(CLK),
        .RegDstIn(RegDst_2),
        .RegWrIn(RegWr),
        .DigitIn(Digit_2),
        .DataWrIn(DataWr_2),
        .immresIn(immres_2),
        .cmpIn(cmp),

        .RegDstOut(RegDst_3),
        .RegWrOut(RegWr_3),
        .DigitOut(Digit_3),
        .DataWrOut(DataWr_3),
        .immresOut(immres_3),
        .cmpOut(cmp_3)
    );

    //MEM阶段
    //上升沿把数据写入MEM，下降沿读出数据写入寄存器
    DataMEM datamem(
        .Mwk(Mwk_3),
        .DataWr(DataWr_3), //存储器写使能
        .Digit(Digit_3), //读写位数，00为8位，01为16位，10为32位
        .CLK(CLK),     //时钟下降沿写入数据
        .DAddr(AluOutput_3),  //写入地址
        .DataIn(ReadData2_3), //写入数据
        .DataOut(DataOut) //输出数据
    );
    WBreg wr_1(
        .CLK(CLK),
        .RegDstIn(RegDst_3),
        .RegWrIn(RegWr_3),
        .DigitIn(Digit_3),
        .immresIn(immres_3),
        .cmpIn(cmp_3),
        .AluOutputIn(AluOutput_3),
        .PCIn(curPC_3),
        .extendIn(extend_3),

        .RegDstOut(RegDst_4),
        .RegWrOut(RegWr_4),
        .DigitOut(Digit_4),
        .immresOut(immres_4),
        .cmpOut(cmp_4),
        .AluOutputOut(AluOutput_4),
        .PCOut(curPC_4),
        .extendOut(extend_4)
    );
    AddressReg ar_3(
        .clear(zero),
        .CLK(CLK),
        .rs1In(rs1_3),
        .rs2In(rs2_3),
        .rdIn(rd_3),
        .MwkIn(Mwk_3),
        .rs1Out(rs1_4),
        .rs2Out(rs2_4),
        .rdOut(rd_4),
        .MwkOut(Mwk_4) //MEM-WB间工作信号
    );
    reg8 r8_3(
        .CLK(CLK),
        .datain(op_3),
        .dataout(op_4)
    );

    //WB阶段
    RegisterFile regfile(
        .CLK(CLK),         //时钟
        .Mwk(Mwk_4),       //工作使能
        .immres(immres_4),   //立即数直接写入信号
        .rs1(rs1),         //rs1寄存器地址输入端口
        .rs2(rs2),         //rs2寄存器地址输入端口
        .WriteReg(rd_4),
        .AluOutput(AluOutput_4), //ALU输出
        .extend(extend_4),       //imm扩展器输出
        .Datain(DataOut),      //存储器输出
        .PC(curPC_4),            //当前PC值
        .cmp(cmp_4),             //比较器输出
        .RegDst(RegDst_4),       //输入具体数据位选
        .RegWr(RegWr_4),         //写使能信号，为1时在时钟边沿触发写入
        .DB(DB),               //输入总线数据
        .ReadData1(ReadData1), //rs1寄存器数据输出端口
        .ReadData2(ReadData2)  //rs2寄存器数据输出端口
    );

endmodule
