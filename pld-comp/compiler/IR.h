#ifndef IR_H
#define IR_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <initializer_list>

using namespace std;

class BasicBlock;
class CFG;
class DefFonction;

//Instructions
class IRInstr
{

public:
	
	typedef enum
	{
		ldconst,
		copy,
		add,
		sub,
		mul,
		div,
		cmp_eq,
		cmp_ne,
		cmp_gt,
		cmp_ge,
		cmp_lt,
		cmp_le,
		func_call,
		arg_call,
		prologue,
		epilogue,
		unconditional_jump,
		conditional_jump,
		not_equal_jump,
		equal_jump,
		retour,
	} Operation;

	IRInstr(BasicBlock *bb_, Operation op, vector<string> params);

	//Génération de l'assembleur
	virtual void gen_asm(ostream &o); 

	//Génération du pseudo code
	virtual void gen_PseudoCode(); 

protected:
	//BasicBlock auquelle l'instruction appartient
	BasicBlock *bb; 
	//Type d'instruction
	Operation op;
	//paramètres
	vector<string> params; 
						  
};

//prologue du programme
class IRInstrPrologue : public IRInstr
{
public:
	IRInstrPrologue(BasicBlock *bb_, int stack_pointer);
	void gen_asm(ostream &o) override;
private:
	int stack_pointer;
};
//epilogue du programme
class IRInstrEpilogue : public IRInstr
{
public:
	IRInstrEpilogue(BasicBlock *bb_);
	void gen_asm(ostream &o) override;
};
//argument d'une fonction
class IRInstrArg : public IRInstr
{
public:
	IRInstrArg(BasicBlock *bb_, string nom_var, int offset);
	void gen_asm(ostream &o) override;
private:
	string nom_var;
	int offset;
};
//appel d'une fonction
class IRInstrFuncCall : public IRInstr
{
public:
	IRInstrFuncCall(BasicBlock *bb_, string label, string tmp, vector<string> params);
	void gen_asm(ostream &o) override;
	void gen_PseudoCode() override;
private:
	string label;
	string tmp;
	vector<string> params;
};
//return
class IRInstrRetour : public IRInstr
{
public:
	IRInstrRetour(BasicBlock *bb_, string var);
	void gen_asm(ostream &o) override;
	void gen_PseudoCode() override;
private:
	string var;
};
//constante
class IRInstrLdconst : public IRInstr
{
public:
	IRInstrLdconst(BasicBlock *bb_, string var, int cst);
	void gen_asm(ostream &o) override;
	void gen_PseudoCode() override;
private:
	string var;
	int cst;
};
//affectation
class IRInstrCopy : public IRInstr
{
public:
    IRInstrCopy(BasicBlock *bb_, string var, string res);
    void gen_asm(ostream &o) override;
	void gen_PseudoCode() override;
private:
	string var;
	string res;
};
//addition
class IRInstrAdd : public IRInstr
{
public:
	IRInstrAdd(BasicBlock *bb_, string tmp, string res_gauche, string res_droite);
	void gen_asm(ostream &o) override;
	void gen_PseudoCode() override;
private:
	string tmp;
	string res_gauche;
	string res_droite;
};
//soustraction
class IRInstrSub : public IRInstr
{
public:
	IRInstrSub(BasicBlock *bb_, string tmp, string res_gauche, string res_droite);
	void gen_asm(ostream &o) override;
	void gen_PseudoCode() override;
private:
	string tmp;
	string res_gauche;
	string res_droite;
};
//multiplication
class IRInstrMul : public IRInstr
{
public:
	IRInstrMul(BasicBlock *bb_, string tmp, string res_gauche, string res_droite);
	void gen_asm(ostream &o) override;
	void gen_PseudoCode() override;
private:
	string tmp;
	string res_gauche;
	string res_droite;
};
//division
class IRInstrDiv : public IRInstr
{
public:
	IRInstrDiv(BasicBlock *bb_, string tmp, string res_gauche, string res_droite);
	void gen_asm(ostream &o) override;
	void gen_PseudoCode() override;
private:
	string tmp;
	string res_gauche;
	string res_droite;
};
//égalité
class IRInstrCmp_eq : public IRInstr
{
public:
	IRInstrCmp_eq(BasicBlock *bb_, string tmp, string res_gauche, string res_droite);
	void gen_asm(ostream &o) override;
private:
	string tmp;
	string res_gauche;
	string res_droite;
};
//inégalité
class IRInstrCmp_ne : public IRInstr
{
public:
	IRInstrCmp_ne(BasicBlock *bb_, string tmp, string res_gauche, string res_droite);
	void gen_asm(ostream &o) override;
private:
	string tmp;
	string res_gauche;
	string res_droite;
};
//>
class IRInstrCmp_gt : public IRInstr
{
public:
	IRInstrCmp_gt(BasicBlock *bb_, string tmp, string res_gauche, string res_droite);
	void gen_asm(ostream &o) override;
private:
	string tmp;
	string res_gauche;
	string res_droite;
};
//>=
class IRInstrCmp_ge : public IRInstr
{
public:
	IRInstrCmp_ge(BasicBlock *bb_, string tmp, string res_gauche, string res_droite);
	void gen_asm(ostream &o) override;
private:
	string tmp;
	string res_gauche;
	string res_droite;
};
//<
class IRInstrCmp_lt : public IRInstr
{
public:
	IRInstrCmp_lt(BasicBlock *bb_, string tmp, string res_gauche, string res_droite);
	void gen_asm(ostream &o) override;
private:
	string tmp;
	string res_gauche;
	string res_droite;
};
//<=
class IRInstrCmp_le : public IRInstr
{
public:
	IRInstrCmp_le(BasicBlock *bb_, string tmp, string res_gauche, string res_droite);
	void gen_asm(ostream &o) override;
private:
	string tmp;
	string res_gauche;
	string res_droite;
};
//saut inconditionnel
class IRInstrUncoJump : public IRInstr
{
public:
	IRInstrUncoJump(BasicBlock *bb_, string label);
	void gen_asm(ostream &o) override;
private:
	string label;
};
//saut conditionnel
class IRInstrCondJump : public IRInstr
{
public:
	IRInstrCondJump(BasicBlock *bb_, string label);
	void gen_asm(ostream &o) override;
private:
	string label;
};
//saut si flag inégalité levé
class IRInstrNEJump : public IRInstr
{
public:
	IRInstrNEJump(BasicBlock *bb_, string label);
	void gen_asm(ostream &o) override;
private:
	string label;
};
//saut si flag égalité levé
class IRInstrEJump : public IRInstr
{
public:
	IRInstrEJump(BasicBlock *bb_, string label);
	void gen_asm(ostream &o) override;
private:
	string label;
};
//Classe des blocs contenant les instructions
class BasicBlock
{
public:
	BasicBlock(CFG *cfg, string label,string func);
	//appel des gen_asm de ses instructions
	void gen_asm(ostream &o); 
	//savoir si le bloc est une fonction
	void set_is_func(bool is_func);
	//ajouter une instruction au bloc
	void add_IRInstr(IRInstr *instr);
	//appel des gen_pseudo_code de ses instructions
	void gen_PseudoCode();
	//Nom du bloc
	string label;	
	//CFG auquel le bloc appartient
	CFG *cfg;	
	//Liste des instructions du bloc
	vector<IRInstr *> instrs; 
	//fonction d'appartenance
	string func;
protected:
	bool is_func = false;
};


class CFG
{
public:

	CFG();
	//ajouter une un bloc au CFG
	void add_bb(BasicBlock *bb);
	//appel des gen_pseudo_code de ses blocs
	void gen_PseudoCode();
	//appel des gen_asm de ses blocs
	void gen_asm(ostream &o);
	//ajouter une variable à la liste des variables
	void add_SymbolIndex(string func,string name, int t);
	//avoir l'index d'une variable (pour connaître le registre)
	int get_var_index(string func,string name);
	int get_stack_pointer();
	//bloc courrant pour l'ajout des instructions au bloc courrant dans CFGVisitor
	BasicBlock *current_bb;

protected:
	//liste des variables par fonctions
	// function, pair<var, var_index>
	std::map<std::string, std::map<std::string, int>> mapCFG;
	//liste des blocs du CFG
	vector<BasicBlock *> bbs; 
};

#endif
