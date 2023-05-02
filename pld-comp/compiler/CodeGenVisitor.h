#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"


class  CodeGenVisitor : public ifccBaseVisitor {
	public:
		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override ;
		virtual antlrcpp::Any visitUneInst(ifccParser::UneInstContext *ctx) override;
		virtual antlrcpp::Any visitMulInst(ifccParser::MulInstContext *ctx) override;
		// virtual antlrcpp::Any visitBlockInst(ifccParser::BlockInstContext *ctx) override;
		// virtual antlrcpp::Any visitCondInst(ifccParser::CondInstContext *ctx) override;
	    virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *ctx) override;
		virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;
    	virtual antlrcpp::Any visitVars(ifccParser::VarsContext *ctx) override;
		virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override;
		virtual antlrcpp::Any visitAddsub(ifccParser::AddsubContext *ctx) override;		
		virtual antlrcpp::Any visitMuldiv(ifccParser::MuldivContext *ctx) override;
		virtual antlrcpp::Any visitVar(ifccParser::VarContext *ctx) override;
		virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override;
		virtual antlrcpp::Any visitCmp(ifccParser::CmpContext *ctx) override;
		// virtual antlrcpp::Any visitCondition(ifccParser::ConditionContext *ctx) override;
		// virtual antlrcpp::Any visitIf(ifccParser::IfContext *ctx) override;
};

