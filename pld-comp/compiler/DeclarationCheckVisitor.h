#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"


class  DeclarationCheckVisitor : public ifccBaseVisitor {
	public:

		virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *context) override;

		virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *context) override;

		virtual antlrcpp::Any visitVar(ifccParser::VarContext *context) override;

    	virtual antlrcpp::Any visitVars(ifccParser::VarsContext *context) override;

		virtual antlrcpp::Any visitInput(ifccParser::InputContext *context) override;
		
		virtual antlrcpp::Any visitArgs(ifccParser::ArgsContext *context) override;

		virtual antlrcpp::Any visitFunc(ifccParser::FuncContext *context) override;

		virtual antlrcpp::Any visitFuncCall(ifccParser::FuncCallContext *context) override;
};

