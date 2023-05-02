#include "CodeGenVisitor.h"
#include <string>
#include <map>

std::map<std::string, int> map;
std::list<std::string> listeVars;
int compteur=0;

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
	//std::string retour = ctx->expr()->getText();
	std::cout<<"\n.globl	main\n"
		" main: \n\n"
		"# prologue\n"
		" pushq %rbp 		# save %rbp on the stack\n"
		" movq %rsp, %rbp 	# define %rbp for the current function\n";
	if(ctx->code()) visit(ctx->code());
	int res = visit(ctx->expr());
	std::cout<< "retour : \n"<<"movl	"<< res <<"(%rbp), %eax\n\n";
	std::cout<<	"# epilogue\n"
			" popq %rbp 			# restore %rbp from the stack\n"	
			" 	ret\n";

	return 0;
}
antlrcpp::Any CodeGenVisitor::visitUneInst(ifccParser::UneInstContext *ctx) 
{
	visit(ctx->instruction());
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitMulInst(ifccParser::MulInstContext *ctx) 
{
	visit(ctx->instruction());
	visit(ctx->code());
	return 0;
}

// antlrcpp::Any CodeGenVisitor::visitBlockInst(ifccParser::BlockInstContext *ctx) 
// {
// 	visit(ctx->code());
// 	return 0;
// }

// antlrcpp::Any CodeGenVisitor::visitCondInst(ifccParser::CondInstContext *ctx) 
// {
// 	visit(ctx->instruction());
// 	return 0;
// }

antlrcpp::Any CodeGenVisitor::visitAffectation(ifccParser::AffectationContext *ctx) 
{
	visit(ctx->vars());

	int res = visit(ctx->expr());
	for(std::string var:listeVars){
		std::cout<<
		"\n# affectation de "<<var<<" à "<<res<<"\n"
		" movl	"<<res<<"(%rbp),%eax\n"
		" movl	%eax, "<<map[var]<<"(%rbp)\n\n"
		;
	}
	listeVars.clear();
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) 
{
	std::string type = (ctx->TYPE()->getText());

	visit(ctx->vars());
	for(std::string var:listeVars){
        compteur+=4;
		map[var]=-compteur;
    }
	if(ctx->expr()){	
		int res = visit(ctx->expr());
		for(std::string var:listeVars){
			std::cout<<
			"\n# declaration de "<<var<<" dans "<<(-compteur)<<"\n"
			" movl	"<<res<<"(%rbp),%eax\n"
			" movl	%eax, "<<map[var]<<"(%rbp)\n\n"
			;
		}	
	}
	listeVars.clear();
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVars(ifccParser::VarsContext *ctx) {
	listeVars.push_back(ctx->VAR()->getText());
	if(ctx->vars()){
		visit(ctx->vars());
	}
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitPar(ifccParser::ParContext *ctx) 
{
	int res = visit(ctx->expr());
	return res;
}

antlrcpp::Any CodeGenVisitor::visitAddsub(ifccParser::AddsubContext *ctx) 
{
	char op=ctx->OPP()->getText()[0];
	int res_gauche = visit(ctx->expr()[0]);
	int res_droite = visit(ctx->expr()[1]); 

	compteur += 4;
	std::string tmp = "_tmp"+std::to_string(compteur);
	map[tmp]=-compteur;
	if(op=='+'){
		std::cout<<
			"\n# addiction de "<<res_gauche<<" * "<<res_droite<<" -> "<<-compteur<<"\n"
			" movl	"<<res_gauche<<"(%rbp), %eax\n"
			" addl	"<<res_droite<<"(%rbp), %eax\n" 
			" movl  %eax, "<<map[tmp]<<"(%rbp)\n\n"
			;
	}
	else if(op=='-'){
		std::cout<<
			"\n# soustraction de "<<res_gauche<<" / "<<res_droite<<" -> "<<-compteur<<"\n"
			" movl	"<<res_gauche<<"(%rbp), %eax\n"
			" subl	"<<res_droite<<"(%rbp), %eax\n" 
			" movl  %eax, "<<map[tmp]<<"(%rbp)\n\n"
			;
	}
	return map[tmp];
}

antlrcpp::Any CodeGenVisitor::visitMuldiv(ifccParser::MuldivContext *ctx) 
{
	char op=ctx->OPM()->getText()[0];
	int res_gauche = visit(ctx->expr()[0]);
	int res_droite = visit(ctx->expr()[1]); 
	
	compteur += 4;
	std::string tmp = "_tmp"+std::to_string(compteur);
	map[tmp]=-compteur;
	if(op=='*'){
		std::cout<<
			"\n# multiplication de "<<res_gauche<<" * "<<res_droite<<" -> "<<-compteur<<"\n"
			" movl	"<<res_gauche<<"(%rbp), %eax\n"
			" imull	"<<res_droite<<"(%rbp), %eax\n" 
			" movl  %eax, "<<map[tmp]<<"(%rbp)\n\n"
			;
	}
	else if(op=='/'){
		std::cout<<
			"\n# division de "<<res_gauche<<" / "<<res_droite<<" -> "<<-compteur<<"\n"
			" movl	"<<res_gauche<<"(%rbp), %eax\n"
			" idivl	"<<res_droite<<"(%rbp)\n" 
			" movl  %eax, "<<map[tmp]<<"(%rbp)\n\n"
			;
	}
	return map[tmp];
}

antlrcpp::Any CodeGenVisitor::visitVar(ifccParser::VarContext *ctx) {
	return map[ctx->VAR()->getText()];
	}

antlrcpp::Any CodeGenVisitor::visitConst(ifccParser::ConstContext *ctx) {
	compteur+=4;
	std::string tmp = "_tmp"+std::to_string(compteur);
	map[tmp]=-compteur;
	int cst = (int)stoi(ctx->CONST()->getText());
	std::cout<<
		"\n# mise de "<<"$"<<cst<<" dans "<<-compteur<<"\n"
		" movl	$"<<cst<<", "<<map[tmp]<<"(%rbp)\n\n"
		;
	return map[tmp];
}

antlrcpp::Any CodeGenVisitor::visitCmp(ifccParser::CmpContext *ctx) 
{
	std::string op =ctx->CMPOP()->getText();
	int res_gauche = visit(ctx->expr()[0]);
	int res_droite = visit(ctx->expr()[1]); 
	
	compteur += 4;
	std::string tmp = "_tmp"+std::to_string(compteur);
	map[tmp]=-compteur;
	if(op == "=="){
		std::cout<<
			"# comparaison ==\n"
			" movl	"<<res_gauche<<"(%rbp), %eax\n"
			" cmpl	"<<res_droite<<"(%rbp), %eax\n" 
			" sete   %al\n"
			" movzbl %al, %eax\n"
			" movl   %eax, "<<map[tmp]<<"(%rbp)\n\n"
			;
	}
	else if(op=="!="){
		std::cout<<
		    "# comparaison !=\n"
			" movl	"<<res_gauche<<"(%rbp), %eax\n"
			" cmpl	"<<res_droite<<"(%rbp), %eax\n" 
			" setne   %al\n"
			" movzbl  %al, %eax\n"
			" movl    %eax, "<<map[tmp]<<"(%rbp)\n\n"
			;
	}
	else if(op==">="){
		std::cout<<
		    "# comparaison >=\n"
			" movl	"<<res_gauche<<"(%rbp), %eax\n"
			" cmpl	"<<res_droite<<"(%rbp), %eax\n" 
			" setge    %al\n"
			" movzbl  %al, %eax\n"
			" movl    %eax, "<<map[tmp]<<"(%rbp)\n\n"
			;
	}
	else if(op==">"){
		std::cout<<
			"# comparaison >\n"
			" movl	"<<res_gauche<<"(%rbp), %eax\n"
			" cmpl	"<<res_droite<<"(%rbp), %eax\n" 
			" setg    %al\n"
			" movzbl  %al, %eax\n"
			" movl    %eax, "<<map[tmp]<<"(%rbp)\n\n"
			;
	}
	else if(op=="<"){
		std::cout<<
			"# comparaison <\n"
			" movl	"<<res_gauche<<"(%rbp), %eax\n"
			" cmpl	"<<res_droite<<"(%rbp), %eax\n" 
			" setl    %al\n"
			" movzbl  %al, %eax\n"
			" movl    %eax, "<<map[tmp]<<"(%rbp)\n\n"
			;
	}
	else if(op=="<="){
		std::cout<<
			"# comparaison <=\n"
			" movl	"<<res_gauche<<"(%rbp), %eax\n"
			" cmpl	"<<res_droite<<"(%rbp), %eax\n" 
			" setle   %al\n"
			" movzbl  %al, %eax\n"
			" movl    %eax, "<<map[tmp]<<"(%rbp)\n\n"
			;   
	}                                                                                                          
	return map[tmp];
}

/*antlrcpp::Any CodeGenVisitor::visitCondition(ifccParser::ConditionContext *ctx) 
{
	visit(ctx->cond());
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitIf(ifccParser::IfContext *ctx) 
{
	int res = visit(ctx->expr());
	if(ctx->ELSE()) { 
		std::cout<<
				" cmpl $0, " << res << "(%rbp)\n"
				" je .L1\n"  
			;
		visit(ctx->code()[0]);
		std::cout<<
				" jmp .L2\n"
				" .L1:\n"
			;
		visit(ctx->code()[1]);
		std::cout<<
				" .L2:\n"
			;
	} else {
		std::cout<<
				" cmpl $0, " << res << "(%rbp)\n"
				" je .L1\n"
			;
		visit(ctx->code()[0]);
		std::cout<<
				" .L1:\n"
			;
	}
	return 0;
} */





