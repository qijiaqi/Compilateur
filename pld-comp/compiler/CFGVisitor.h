#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "IR.h"


class  CFGVisitor : public ifccBaseVisitor {
	public:
		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override ;
		virtual antlrcpp::Any visitFunc(ifccParser::FuncContext *ctx) override;
		virtual antlrcpp::Any visitArgs(ifccParser::ArgsContext *ctx) override;
		virtual antlrcpp::Any visitUneInst(ifccParser::UneInstContext *ctx) override;
		virtual antlrcpp::Any visitMulInst(ifccParser::MulInstContext *ctx) override;
	    virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *ctx) override;
		virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;
    	virtual antlrcpp::Any visitVars(ifccParser::VarsContext *ctx) override;
		virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override;
		virtual antlrcpp::Any visitAddsub(ifccParser::AddsubContext *ctx) override;	
		virtual antlrcpp::Any visitMuldiv(ifccParser::MuldivContext *ctx) override;
		virtual antlrcpp::Any visitVar(ifccParser::VarContext *ctx) override;
		virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override;

		virtual antlrcpp::Any visitReturn(ifccParser::ReturnContext *ctx) override;

		virtual antlrcpp::Any visitCmp(ifccParser::CmpContext *ctx) override;
		virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx) override;
		
		virtual antlrcpp::Any visitWhileInst(ifccParser::WhileInstContext *ctx) override;
		virtual antlrcpp::Any visitIfInst(ifccParser::IfInstContext *ctx) override;

		virtual antlrcpp::Any visitFuncCall(ifccParser::FuncCallContext *ctx) override;
		virtual antlrcpp::Any visitInput(ifccParser::InputContext *ctx) override;
};

