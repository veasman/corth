#include <iostream>
#include <fstream>
#include "header/compiler.hpp"

#define MEM_CAPACITY 640000

CComplier::CComplier(std::string fileName, std::deque<Token> tokens) {
    // Set m_strFileName to fileName without .corth extension
    this->m_strFileName = fileName.substr(0, fileName.size() - 6);
    this->m_qTokens = tokens;
}

void CComplier::GenerateNasm() {
    std::cout << "[LOG] Generating " << this->m_strFileName << ".asm" << std::endl;

    // Open .asm file and clear contents
    std::ofstream out(this->m_strFileName + ".asm",
        std::ofstream::out | std::ofstream::trunc);

    // Define a print function to make printing easier
    // Source: https://github.com/tsoding/porth/blob/master/porth.py#L1043
    out << "BITS 64\n";
    out << "segment .text\n";
    out << "print:\n";
    out << "\tmov r9, -3689348814741910323\n";
    out << "\tsub rsp, 40\n";
    out << "\tmov BYTE [rsp+31], 10\n";
    out << "\tlea rcx, [rsp+30]\n";
    out << ".L2:\n";
    out << "\tmov rax, rdi\n";
    out << "\tlea r8, [rsp+32]\n";
    out << "\tmul r9\n";
    out << "\tmov rax, rdi\n";
    out << "\tsub r8, rcx\n";
    out << "\tshr rdx, 3\n";
    out << "\tlea rsi, [rdx+rdx*4]\n";
    out << "\tadd rsi, rsi\n";
    out << "\tsub rax, rsi\n";
    out << "\tadd eax, 48\n";
    out << "\tmov BYTE [rcx], al\n";
    out << "\tmov rax, rdi\n";
    out << "\tmov rdi, rdx\n";
    out << "\tmov rdx, rcx\n";
    out << "\tsub rcx, 1\n";
    out << "\tcmp rax, 9\n";
    out << "\tja  .L2\n";
    out << "\tlea rax, [rsp+32]\n";
    out << "\tmov edi, 1\n";
    out << "\tsub rdx, rax\n";
    out << "\txor eax, eax\n";
    out << "\tlea rsi, [rsp+32+rdx]\n";
    out << "\tmov rdx, r8\n";
    out << "\tmov rax, 1\n";
    out << "\tsyscall\n";
    out << "\tadd rsp, 40\n";
    out << "\tret\n";
    out << "global _start\n";
    out << "_start:\n";
    out << "\tmov [args_ptr], rsp\n";

    // Grab the size before looping through so we can reuse it later
    int tokensSize = this->m_qTokens.size();
    int addrNum = 0;

    while (!this->m_qTokens.empty()) {
        out << "addr_" << addrNum << ":\n";
        switch (this->m_qTokens.front().m_Type) {
        case TokenType::INT:
            out << "\t;; -- push int " << this->m_qTokens.front().m_strValue << " --\n";
            out << "\tmov rax, " << this->m_qTokens.front().m_strValue << "\n";
            out << "\tpush rax\n";
            break;
        case TokenType::ADD:
            out << "\t;; -- plus --\n";
            out << "\tpop rax\n";
            out << "\tpop rbx\n";
            out << "\tadd rax, rbx\n";
            out << "\tpush rax\n";
            break;
        case TokenType::SUB:
            out << "\t;; -- minus --\n";
            out << "\tpop rax\n";
            out << "\tpop rbx\n";
            out << "\tsub rbx, rax\n";
            out << "\tpush rbx\n";
            break;
        case TokenType::MUL:
            out << "\t;; -- mul --\n";
            out << "\tpop rax\n";
            out << "\tpop rbx\n";
            out << "\tmul rbx\n";
            out << "\tpush rax\n";
            break;
        case TokenType::DIVMOD:
            out << "\t;; -- mod --\n";
            out << "\txor rdx, rdx\n";
            out << "\tpop rbx\n";
            out << "\tpop rax\n";
            out << "\tdiv rbx\n";
            out << "\tpush rax\n";
            out << "\tpush rdx\n";
            break;
        case TokenType::INTRINSIC:
            switch (this->m_qTokens.front().m_Intrinsic) {
            case Intrinsics::PRINT:
                out << "\t;; -- print --\n";
                out << "\tpop rdi\n";
                out << "\tcall print\n";
                break;
            case Intrinsics::DROP:
                out << "\t;; -- drop --\n";
                out << "\tpop rax\n";
                break;
            case Intrinsics::DUP:
                out << "\t;; -- dup --\n";
                out << "\tpop rax\n";
                out << "\tpush rax\n";
                out << "\tpush rax\n";
                break;
            case Intrinsics::IF:
                out << "\t;; -- if --\n";
                break;
            case Intrinsics::WHILE:
                out << "\t;; -- while --\n";
                break;
            case Intrinsics::DO:
                out << "\t;; -- do --\n";
                out << "\tpop rax\n";
                out << "\ttest rax, rax\n";
                out << "\tjz addr_" << this->m_qTokens.front().m_iConPair << "\n";
                break;
            case Intrinsics::ELSE:
                out << "\t;; -- else --\n";
                out << "\tjmp addr_" << this->m_qTokens.front().m_iConPair << "\n";
                break;
            case Intrinsics::END:
                out << "\t;; -- end --\n";
                break;
            case Intrinsics::EQ:
                out << "\t;; -- equal --\n";
                out << "\tmov rcx, 0\n";
                out << "\tmov rdx, 1\n";
                out << "\tpop rax\n";
                out << "\tpop rbx\n";
                out << "\tcmp rax, rbx\n";
                out << "\tcmove rcx, rdx\n";
                out << "\tpush rcx\n";
                break;
            case Intrinsics::GT:
                out << "\t;; -- gt --\n";
                out << "\tmov rcx, 0\n";
                out << "\tmov rdx, 1\n";
                out << "\tpop rbx\n";
                out << "\tpop rax\n";
                out << "\tcmp rax, rbx\n";
                out << "\tcmovg rcx, rdx\n";
                out << "\tpush rcx\n";
                break;
            case Intrinsics::LT:
                out << "\t;; -- lt --\n";
                out << "\tmov rcx, 0\n";
                out << "\tmov rdx, 1\n";
                out << "\tpop rbx\n";
                out << "\tpop rax\n";
                out << "\tcmp rax, rbx\n";
                out << "\tcmovl rcx, rdx\n";
                out << "\tpush rcx\n";
                break;
            case Intrinsics::GE:
                out << "\t;; -- ge --\n";
                out << "\tmov rcx, 0\n";
                out << "\tmov rdx, 1\n";
                out << "\tpop rbx\n";
                out << "\tpop rax\n";
                out << "\tcmp rax, rbx\n";
                out << "\tcmovge rcx, rdx\n";
                out << "\tpush rcx\n";
                break;
            case Intrinsics::LE:
                out << "\t;; -- le --\n";
                out << "\tmov rcx, 0\n";
                out << "\tmov rdx, 1\n";
                out << "\tpop rbx\n";
                out << "\tpop rax\n";
                out << "\tcmp rax, rbx\n";
                out << "\tcmovle rcx, rdx\n";
                out << "\tpush rcx\n";
                break;
            case Intrinsics::NE:
                out << "\t;; -- ne --\n";
                out << "\tmov rcx, 0\n";
                out << "\tmov rdx, 1\n";
                out << "\tpop rbx\n";
                out << "\tpop rax\n";
                out << "\tcmp rax, rbx\n";
                out << "\tcmovne rcx, rdx\n";
                out << "\tpush rcx\n";
                break;
            default:
                break;
            }
        default:
            break;
        }

        addrNum++;
        this->m_qTokens.pop_front();
    }

    out << "addr_" << tokensSize << ":\n";
    out << "\tmov rax, 60\n";
    out << "\tmov rdi, 0\n";
    out << "\tsyscall\n";
    out << "segment .data\n";
    out << "segment .bss\n";
    out << "args_ptr: resq 1\n";
    out << "mem: resb " << MEM_CAPACITY << "\n";
}

void CComplier::CompileNasm() {
    std::string cmd = "";

    cmd = "nasm -felf64 " + this->m_strFileName + ".asm";
    system(cmd.c_str());
    std::cout << "[CMD] " << cmd << std::endl;

    cmd = "ld -o " + this->m_strFileName + " " + this->m_strFileName + ".o";
    system(cmd.c_str());
    std::cout << "[CMD] " << cmd << std::endl;
}
