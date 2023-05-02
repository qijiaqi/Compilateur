<<<<<<< HEAD
#include "CFGVisitor.h"
#include <string>
#include <map>
#include "IR.h"
//std::map<std::string, int> map;
std::list<std::string> listeVarsCFG;
int compteurCFG=0;
CFG* cfg = new CFG();

antlrcpp::Any CFGVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
	
	BasicBlock* bb = new BasicBlock(cfg, "entry");
	cfg->add_bb(bb);

	if(ctx->code()) visit(ctx->code());
	std::string res = visit(ctx->expr());
	IRInstrRetour* instr = new IRInstrRetour(cfg->current_bb, res);
	cfg->current_bb->add_IRInstr(instr);

	cfg->gen_asm(std::cout);


	return 0;
}

antlrcpp::Any CFGVisitor::visitBlock(ifccParser::BlockContext *ctx) {
	if (ctx->code()) visit(ctx->code());
	return 0;
}

antlrcpp::Any CFGVisitor::visitWhileInst(ifccParser::WhileInstContext *ctx) {
	BasicBlock* cond_block = new BasicBlock(cfg, "testWhile" + std::to_string(compteurCFG));
	cfg->current_bb->exit_true = cond_block;
	cfg->add_bb(cond_block);

	std::string res_test = visit(ctx->expr());
	compteurCFG += 4;
	std::string tmp_test = "_tmp"+std::to_string(compteurCFG);
	cfg->add_SymbolIndex(tmp_test,-compteurCFG);

	compteurCFG+=4;
	std::string tmp = "_tmp_"+std::to_string(compteurCFG);
	cfg->add_SymbolIndex(tmp,-compteurCFG);
	IRInstrLdconst* instr0 = new IRInstrLdconst(cfg->current_bb,tmp,0);
	cfg->current_bb->add_IRInstr(instr0);

	IRInstrCmp_eq* instr = new IRInstrCmp_eq(cfg->current_bb,tmp_test,res_test,tmp);
	cfg->current_bb->add_IRInstr(instr);

	BasicBlock* body_block = new BasicBlock(cfg, "bodyWhile" + std::to_string(compteurCFG));
	cond_block->exit_true = body_block;
	body_block->exit_true = cond_block;
	cfg->add_bb(body_block);
	visit(ctx->code()[0]);

	BasicBlock* afterWhile = new BasicBlock(cfg, "afterWhile" + std::to_string(compteurCFG));
	cond_block->exit_false = afterWhile;
	
	
	
	cfg->add_bb(afterWhile);

	if (ctx->code()[1]) {
		visit(ctx->code()[1]);
	}
	return 0;
}

antlrcpp::Any CFGVisitor::visitIfInst(ifccParser::IfInstContext *ctx) {
	BasicBlock* cond_block = new BasicBlock(cfg, "testIf" + std::to_string(compteurCFG));
	cfg->current_bb->exit_true = cond_block;
	cfg->add_bb(cond_block);
	
	std::string res_test = visit(ctx->expr());
	compteurCFG += 4;
	std::string tmp_test = "_tmp"+std::to_string(compteurCFG);
	cfg->add_SymbolIndex(tmp_test,-compteurCFG);

	compteurCFG+=4;
	std::string tmp = "_tmp_"+std::to_string(compteurCFG);
	cfg->add_SymbolIndex(tmp,-compteurCFG);
	IRInstrLdconst* instr0 = new IRInstrLdconst(cfg->current_bb,tmp,0);
	cfg->current_bb->add_IRInstr(instr0);

	IRInstrCmp_eq* instr = new IRInstrCmp_eq(cfg->current_bb,tmp_test,res_test,tmp);
	cfg->current_bb->add_IRInstr(instr);

	BasicBlock* bodyif_block = new BasicBlock(cfg, "bodyIf" + std::to_string(compteurCFG));
	cfg->add_bb(bodyif_block);
	cond_block->exit_true = bodyif_block;
	visit(ctx->code()[0]);

	BasicBlock* endIf = new BasicBlock(cfg, "endIf" + std::to_string(compteurCFG));
	bodyif_block->exit_true = endIf;
	cond_block->exit_false = endIf;
	

	
	
	if (ctx->ELSE()) 
	{
		BasicBlock* bodyelse_block = new BasicBlock(cfg, "bodyElse" + std::to_string(compteurCFG));
		cfg->add_bb(bodyelse_block);
		cond_block->exit_false = bodyelse_block;
		bodyelse_block->exit_true = endIf;
		visit(ctx->code()[1]);
		
		cfg->add_bb(endIf);
		if (ctx->code()[2]) {
			visit(ctx->code()[2]);
		}
	} 
	else 
	{
		cfg->add_bb(endIf);
		if (ctx->code()[1]) {
			visit(ctx->code()[1]);
		}
	}
	return 0;
}

antlrcpp::Any CFGVisitor::visitUneInst(ifccParser::UneInstContext *ctx) 
{
	visit(ctx->instruction());
	return 0;
}

antlrcpp::Any CFGVisitor::visitMulInst(ifccParser::MulInstContext *ctx) 
{
	visit(ctx->instruction());
	visit(ctx->code());
	return 0;
}

antlrcpp::Any CFGVisitor::visitAffectation(ifccParser::AffectationContext *ctx) 
{
	visit(ctx->vars());
	string res = visit(ctx->expr());

	for(std::string var:listeVarsCFG){
		IRInstrCopy* instr = new IRInstrCopy(cfg->current_bb,var,res);
		cfg->current_bb->add_IRInstr(instr);
		
	}
	listeVarsCFG.clear();
	return 0;
}

antlrcpp::Any CFGVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) 
{
	std::string type = (ctx->TYPE()->getText());
	visit(ctx->vars());
	for(std::string var:listeVarsCFG){
        compteurCFG+=4;
		cfg->add_SymbolIndex(var,-compteurCFG);
    }
	if(ctx->expr()){	
		string res = visit(ctx->expr());
		for(std::string var:listeVarsCFG){
			IRInstrCopy* instr = new IRInstrCopy(cfg->current_bb,var,res);
			cfg->current_bb->add_IRInstr(instr);
			
		}	
	}
	listeVarsCFG.clear();
	return 0;
}

antlrcpp::Any CFGVisitor::visitVars(ifccParser::VarsContext *ctx) {
	listeVarsCFG.push_back(ctx->VAR()->getText());
	if(ctx->vars()){
		visit(ctx->vars());
	}
	return 0;
}

antlrcpp::Any CFGVisitor::visitPar(ifccParser::ParContext *ctx) 
{
	string res = visit(ctx->expr());
	return res;
}

antlrcpp::Any CFGVisitor::visitAddsub(ifccParser::AddsubContext *ctx) 
{
	char op=ctx->OPP()->getText()[0];
	string res_gauche = visit(ctx->expr()[0]);
	string res_droite = visit(ctx->expr()[1]); 
	compteurCFG += 4;
	std::string tmp = "_tmp"+std::to_string(compteurCFG);
	cfg->add_SymbolIndex(tmp,-compteurCFG);
	IRInstr* instr;
	if(op=='+'){
		instr = new IRInstrAdd(cfg->current_bb,tmp,res_gauche,res_droite);
	}
	else if(op=='-'){
		instr = new IRInstrSub(cfg->current_bb,tmp,res_gauche,res_droite);
		
	}
	cfg->current_bb->add_IRInstr(instr);
	return tmp;
}
antlrcpp::Any CFGVisitor::visitMuldiv(ifccParser::MuldivContext *ctx) 
{
	char op=ctx->OPM()->getText()[0];
	string res_gauche = visit(ctx->expr()[0]);
	string res_droite = visit(ctx->expr()[1]);
	std::string tmp = "";
	
	if(op=='*'){
		compteurCFG += 4;
		tmp = "_tmp"+std::to_string(compteurCFG);
		cfg->add_SymbolIndex(tmp,-compteurCFG);
		IRInstrMul* instr = new IRInstrMul(cfg->current_bb,tmp,res_gauche,res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else {
		compteurCFG += 4;
		tmp = "_tmp"+std::to_string(compteurCFG);
		cfg->add_SymbolIndex(tmp,-compteurCFG);
		IRInstrDiv* instr = new IRInstrDiv(cfg->current_bb,tmp,res_gauche,res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	return tmp;
}

antlrcpp::Any CFGVisitor::visitVar(ifccParser::VarContext *ctx) {
	return ctx->VAR()->getText();
}

antlrcpp::Any CFGVisitor::visitConst(ifccParser::ConstContext *ctx) {
	compteurCFG+=4;
	std::string tmp = "_tmp"+std::to_string(compteurCFG);
	cfg->add_SymbolIndex(tmp,-compteurCFG);
	int cst = stoi(ctx->CONST()->getText());
	IRInstrLdconst* instr = new IRInstrLdconst(cfg->current_bb,tmp,cst);
	cfg->current_bb->add_IRInstr(instr);
	return tmp;
}

antlrcpp::Any CFGVisitor::visitCmp(ifccParser::CmpContext *ctx) {
	std::string op = ctx->CMPOP()->getText();
	string res_gauche = visit(ctx->expr()[0]);
	string res_droite = visit(ctx->expr()[1]);
	compteurCFG += 4;
	std::string	tmp = "_tmp"+std::to_string(compteurCFG);
	cfg->add_SymbolIndex(tmp,-compteurCFG);
	
	if(op.compare("==")==0) {
		IRInstrCmp_eq* instr = new IRInstrCmp_eq(cfg->current_bb,tmp,res_gauche,res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else if (op.compare("!=")==0) {
		IRInstrCmp_ne* instr = new IRInstrCmp_ne(cfg->current_bb,tmp,res_gauche,res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else if (op.compare("<")==0) {
		IRInstrCmp_lt* instr = new IRInstrCmp_lt(cfg->current_bb,tmp,res_gauche,res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else if (op.compare(">")==0) {
		IRInstrCmp_gt* instr = new IRInstrCmp_gt(cfg->current_bb,tmp,res_gauche,res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else if (op.compare("<=")==0) {
		IRInstrCmp_le* instr = new IRInstrCmp_le(cfg->current_bb,tmp,res_gauche,res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else if (op.compare(">=")==0) {
		IRInstrCmp_ge* instr = new IRInstrCmp_ge(cfg->current_bb,tmp,res_gauche,res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	return tmp;
}
=======
#include "CFGVisitor.h"
#include <string>
#include <map>
#include "IR.h"

std::list<std::string> listeVarsCFG;
std::vector<std::string> vectorInput;

int compteurCFG = 0;
CFG *cfg = new CFG();
std::string funcActuelle = "";

antlrcpp::Any CFGVisitor::visitProg(ifccParser::ProgContext *ctx)
{
	if (ctx->func())
	{
		visit(ctx->func());
	}
	funcActuelle = "main";
	BasicBlock *bb = new BasicBlock(cfg, "main","main");
	cfg->add_bb(bb);
	bb->set_is_func(true);

	int stack_pointer = cfg->get_stack_pointer();
	IRInstrPrologue *instrPro = new IRInstrPrologue(cfg->current_bb, stack_pointer);
	cfg->current_bb->add_IRInstr(instrPro);

	if (ctx->code())
	{
		visit(ctx->code());
	}
	cfg->gen_asm(std::cout);
	return 0;
}

antlrcpp::Any CFGVisitor::visitFunc(ifccParser::FuncContext *ctx)
{

	funcActuelle = ctx->VAR()->getText();
	BasicBlock *bb = new BasicBlock(cfg, ctx->VAR()->getText(),funcActuelle);
	cfg->add_bb(bb);
	bb->set_is_func(true);
	//prologue avec debut au stack_pointer pour délimiter l'espace de la fct
	int stack_pointer = cfg->get_stack_pointer();
	IRInstrPrologue *instrPro = new IRInstrPrologue(cfg->current_bb, stack_pointer);
	cfg->current_bb->add_IRInstr(instrPro);

	if (ctx->args())
	{
		visit(ctx->args());
	}
	if (ctx->code())
	{
		visit(ctx->code());
	}
	if (ctx->func())
	{
		visit(ctx->func());
	}
	return 0;
}

antlrcpp::Any CFGVisitor::visitReturn(ifccParser::ReturnContext *ctx)
{
	std::string res = visit(ctx->expr());
	IRInstrRetour *instr = new IRInstrRetour(cfg->current_bb, res);
	cfg->current_bb->add_IRInstr(instr);
	IRInstrEpilogue *instrEpi = new IRInstrEpilogue(cfg->current_bb);
	cfg->current_bb->add_IRInstr(instrEpi);
	return res;
}

int compteurArgs = 0;
//registre disponibles pour les arguments
std::vector<std::string> vectorName = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d", "%r10d", 
				"%r11d", "%r12d", "%r13d", "%r14d", "%r15d"};

antlrcpp::Any CFGVisitor::visitArgs(ifccParser::ArgsContext *ctx)
{

	//on ajoute à la liste des symboles et à la map l'argument de la fonction
	compteurCFG += 4;
	string name=ctx->VAR()->getText();
	cfg->add_SymbolIndex(funcActuelle, name , -compteurCFG);
	//ajout de l'instruction de l'argument au bloc courrant avec le registre du numéro d'argument
	IRInstrArg *instr = new IRInstrArg(cfg->current_bb, vectorName[compteurArgs], -compteurCFG);
	cfg->current_bb->add_IRInstr(instr);

	//visite des prochains arguments
	if (ctx->args())
	{
		compteurArgs++;
		visit(ctx->args());
	}
	// on remet à 0 s'il y'a une prochaine fonction
	compteurArgs = 0;
	return 0;
}

antlrcpp::Any CFGVisitor::visitBlock(ifccParser::BlockContext *ctx)
{
	visit(ctx->code());
	return 0;
}

antlrcpp::Any CFGVisitor::visitWhileInst(ifccParser::WhileInstContext *ctx)
{
	BasicBlock *cond_block = new BasicBlock(cfg, "testWhile" + std::to_string(compteurCFG),funcActuelle);
	BasicBlock *body_block = new BasicBlock(cfg, "bodyWhile" + std::to_string(compteurCFG),funcActuelle);
	BasicBlock *afterWhile = new BasicBlock(cfg, "afterWhile" + std::to_string(compteurCFG),funcActuelle);
	//on ajoute le bloc de condition
	cfg->add_bb (cond_block);	

	//on enregistre le flag de la condition
	std::string res_test = visit(ctx->expr());
	compteurCFG += 4;
	std::string tmp_test = "_tmp" + std::to_string(compteurCFG);
	cfg->add_SymbolIndex(funcActuelle,tmp_test, -compteurCFG);

	//on declare une variable à 0
	compteurCFG+=4;
	std::string tmp = "_tmp_"+std::to_string(compteurCFG);
	cfg->add_SymbolIndex(funcActuelle,tmp,-compteurCFG);
	IRInstrLdconst* instr0 = new IRInstrLdconst(cfg->current_bb,tmp,0);
	cfg->current_bb->add_IRInstr(instr0);
	//on compare le flag à la variable à 0
	IRInstrCmp_eq* instr = new IRInstrCmp_eq(cfg->current_bb,tmp_test,res_test,tmp);
	cfg->current_bb->add_IRInstr(instr);

	//si le flag vaut 0 (=la condition n'est pas vraie), on fait un saut vers le bloc afterWhile (= on quitte le while)
	IRInstrEJump *instrCond = new IRInstrEJump(cfg->current_bb, afterWhile->label);
	cfg->current_bb->add_IRInstr(instrCond);

	//si le flag vaut 1 , on fait un saut pour faire le body_block
	IRInstrUncoJump *instrUnco2 = new IRInstrUncoJump(cfg->current_bb, body_block->label);
	cfg->current_bb->add_IRInstr(instrUnco2);

	//on ajoute le bodybloc
	cfg->add_bb(body_block);
	//on ajoute le code du bodybloc
	visit(ctx->code()[0]);

	//saut vers le bloc de condition (condition dans le while(condition))
	IRInstrUncoJump *instrUnco = new IRInstrUncoJump(cfg->current_bb, cond_block->label);
	cfg->current_bb->add_IRInstr(instrUnco);

	//on ajoute le bloc afterWhile
	cfg->add_bb(afterWhile);
	if (ctx->code()[1])
	{
		visit(ctx->code()[1]);
	}
	return 0;
}

antlrcpp::Any CFGVisitor::visitIfInst(ifccParser::IfInstContext *ctx)
{
	BasicBlock *bodyif_block = new BasicBlock(cfg, "bodyIf" + std::to_string(compteurCFG),funcActuelle);
	BasicBlock *bodyelse_block = new BasicBlock(cfg, "bodyElse" + std::to_string(compteurCFG),funcActuelle);
	BasicBlock *endIf_block = new BasicBlock(cfg, "endIf" + std::to_string(compteurCFG),funcActuelle);

	//recupere le flag
	std::string res_test = visit(ctx->expr());
	compteurCFG += 4;
	std::string tmp_test = "_tmp"+std::to_string(compteurCFG);
	cfg->add_SymbolIndex(funcActuelle,tmp_test,-compteurCFG);

	//declaration var à 0
	compteurCFG+=4;
	std::string tmp = "_tmp_"+std::to_string(compteurCFG);
	cfg->add_SymbolIndex(funcActuelle,tmp,-compteurCFG);
	IRInstrLdconst* instr0 = new IRInstrLdconst(cfg->current_bb,tmp,0);
	cfg->current_bb->add_IRInstr(instr0);

	//comparaison du flag avec la variable à 0
	IRInstrCmp_eq* instr = new IRInstrCmp_eq(cfg->current_bb,tmp_test,res_test,tmp);
	cfg->current_bb->add_IRInstr(instr);

	//si on a un else, et que le flag est nul, on saute vers le bodyelse
	if (ctx->ELSE())
	{
		IRInstrEJump *instrE = new IRInstrEJump(cfg->current_bb, bodyelse_block->label);
		cfg->current_bb->add_IRInstr(instrE);
	}
	else{
		IRInstrEJump *instrE = new IRInstrEJump(cfg->current_bb, endIf_block->label);
		cfg->current_bb->add_IRInstr(instrE);
	}

	//ajout du bloc if
	cfg->add_bb(bodyif_block);
	
	//on visite le code et on l'ajoute au bodyif
	visit(ctx->code()[0]);

	//Après le code du bodyif, on jump au endif (= on saute le bodyelse)
	IRInstrUncoJump *instrUnco = new IRInstrUncoJump(cfg->current_bb, endIf_block->label);
	cfg->current_bb->add_IRInstr(instrUnco);

	//si on a un else, on ajoute le bodyelse
	if (ctx->ELSE())
	{
		cfg->add_bb(bodyelse_block);
		visit(ctx->code()[1]);
		//après le code du else, on ajoute le bloc endif
		cfg->add_bb(endIf_block);
		//on ajoute le code suivant le if..else
		if (ctx->code()[2])
		{
			visit(ctx->code()[2]);
		}
	}
	//si on a pas de else, on ajoute le bloc endif et le code suivant le if
	else
	{	
		cfg->add_bb(endIf_block);
		if (ctx->code()[1])
		{
			visit(ctx->code()[1]);
		}
	}
	
	return 0;
}

antlrcpp::Any CFGVisitor::visitUneInst(ifccParser::UneInstContext *ctx)
{
	visit(ctx->instruction());
	return 0;
}

antlrcpp::Any CFGVisitor::visitMulInst(ifccParser::MulInstContext *ctx)
{
	visit(ctx->instruction());
	visit(ctx->code());
	return 0;
}

antlrcpp::Any CFGVisitor::visitAffectation(ifccParser::AffectationContext *ctx)
{
	visit(ctx->vars());
	string res = visit(ctx->expr());

	for (std::string var : listeVarsCFG)
	{
		IRInstrCopy *instr = new IRInstrCopy(cfg->current_bb, var, res);
		cfg->current_bb->add_IRInstr(instr);
	}
	listeVarsCFG.clear();
	return 0;
}

antlrcpp::Any CFGVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx)
{
	std::string type = (ctx->TYPE()->getText());
	visit(ctx->vars());
	for (std::string var : listeVarsCFG)
	{
		compteurCFG += 4;
		cfg->add_SymbolIndex(funcActuelle,var, -compteurCFG);
	}
	if (ctx->expr())
	{
		string res = visit(ctx->expr());
		for (std::string var : listeVarsCFG)
		{
			IRInstrCopy *instr = new IRInstrCopy(cfg->current_bb, var, res);
			cfg->current_bb->add_IRInstr(instr);
		}
	}
	listeVarsCFG.clear();
	return 0;
}

antlrcpp::Any CFGVisitor::visitVars(ifccParser::VarsContext *ctx)
{
	listeVarsCFG.push_back(ctx->VAR()->getText());
	if (ctx->vars())
	{
		visit(ctx->vars());
	}
	return 0;
}

antlrcpp::Any CFGVisitor::visitPar(ifccParser::ParContext *ctx)
{
	string res = visit(ctx->expr());
	return res;
}

antlrcpp::Any CFGVisitor::visitAddsub(ifccParser::AddsubContext *ctx)
{
	char op = ctx->OPP()->getText()[0];
	string res_gauche = visit(ctx->expr()[0]);
	string res_droite = visit(ctx->expr()[1]);
	compteurCFG += 4;
	std::string tmp = "_tmp" + std::to_string(compteurCFG);
	cfg->add_SymbolIndex(funcActuelle,tmp, -compteurCFG);

	IRInstr *instr;
	if (op == '+')
	{
		instr = new IRInstrAdd(cfg->current_bb, tmp, res_gauche, res_droite);
	}
	else if (op == '-')
	{
		instr = new IRInstrSub(cfg->current_bb, tmp, res_gauche, res_droite);
	}
	cfg->current_bb->add_IRInstr(instr);

	return tmp;
}

antlrcpp::Any CFGVisitor::visitMuldiv(ifccParser::MuldivContext *ctx)
{
	char op = ctx->OPM()->getText()[0];
	string res_gauche = visit(ctx->expr()[0]);
	string res_droite = visit(ctx->expr()[1]);
	compteurCFG += 4;
	std::string tmp = "_tmp" + std::to_string(compteurCFG);
	cfg->add_SymbolIndex(funcActuelle,tmp, -compteurCFG);

	if (op == '*')
	{
		IRInstrMul *instr = new IRInstrMul(cfg->current_bb, tmp, res_gauche, res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else
	{
		IRInstrDiv *instr = new IRInstrDiv(cfg->current_bb, tmp, res_gauche, res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	return tmp;
}

antlrcpp::Any CFGVisitor::visitVar(ifccParser::VarContext *ctx)
{
	return ctx->VAR()->getText();
}

antlrcpp::Any CFGVisitor::visitConst(ifccParser::ConstContext *ctx)
{
	compteurCFG += 4;
	std::string tmp = "_tmp" + std::to_string(compteurCFG);
	cfg->add_SymbolIndex(funcActuelle,tmp, -compteurCFG);
	int cst = stoi(ctx->CONST()->getText());
	IRInstrLdconst *instr = new IRInstrLdconst(cfg->current_bb, tmp, cst);
	cfg->current_bb->add_IRInstr(instr);
	return tmp;
}

antlrcpp::Any CFGVisitor::visitCmp(ifccParser::CmpContext *ctx)
{
	std::string op = ctx->CMPOP()->getText();
	string res_gauche = visit(ctx->expr()[0]);
	string res_droite = visit(ctx->expr()[1]);
	compteurCFG += 4;
	std::string tmp = "_tmp" + std::to_string(compteurCFG);
	cfg->add_SymbolIndex(funcActuelle,tmp, -compteurCFG);

	if (op.compare("==") == 0)
	{
		IRInstrCmp_eq *instr = new IRInstrCmp_eq(cfg->current_bb, tmp, res_gauche, res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else if (op.compare("!=") == 0)
	{
		IRInstrCmp_ne *instr = new IRInstrCmp_ne(cfg->current_bb, tmp, res_gauche, res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else if (op.compare("<") == 0)
	{
		IRInstrCmp_lt *instr = new IRInstrCmp_lt(cfg->current_bb, tmp, res_gauche, res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else if (op.compare(">") == 0)
	{
		IRInstrCmp_gt *instr = new IRInstrCmp_gt(cfg->current_bb, tmp, res_gauche, res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else if (op.compare("<=") == 0)
	{
		IRInstrCmp_le *instr = new IRInstrCmp_le(cfg->current_bb, tmp, res_gauche, res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	else if (op.compare(">=") == 0)
	{
		IRInstrCmp_ge *instr = new IRInstrCmp_ge(cfg->current_bb, tmp, res_gauche, res_droite);
		cfg->current_bb->add_IRInstr(instr);
	}
	return tmp;
}

antlrcpp::Any CFGVisitor::visitFuncCall(ifccParser::FuncCallContext *ctx)
{
	std::string func_name = ctx->VAR()->getText();
	compteurCFG += 4;
	std::string tmp = "_tmp" + std::to_string(compteurCFG);
	cfg->add_SymbolIndex(funcActuelle,tmp, -compteurCFG);
	if (ctx->input())
	{
		visit(ctx->input());
		IRInstrFuncCall *instr = new IRInstrFuncCall(cfg->current_bb, func_name, tmp, vectorInput);
		cfg->current_bb->add_IRInstr(instr);
	}
	else
	{
		IRInstrFuncCall *instr = new IRInstrFuncCall(cfg->current_bb, func_name, tmp, {});
		cfg->current_bb->add_IRInstr(instr);
	}
	vectorInput.clear();
	return tmp;
}

antlrcpp::Any CFGVisitor::visitInput(ifccParser::InputContext *ctx)
{
	vectorInput.push_back(ctx->expr()->getText());
	visit(ctx->expr());
	if (ctx->input())
	{
		visit(ctx->input());
	}
	return 0;
}
>>>>>>> FONCTIOSNFIX
