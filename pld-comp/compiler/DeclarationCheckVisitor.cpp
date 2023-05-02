#include "DeclarationCheckVisitor.h"
#include <string>
#include <map>
#include <list>

std::list<std::string> listeDeclarations;
std::list<std::string> listeLigne;

// sauvegarder key: function et value: leurs parametres
std::map<std::string, std::list<std::string>> mapFunctions; 
std::list<std::string> listeParams;
std::list<std::string> listInput;

antlrcpp::Any DeclarationCheckVisitor::visitInput(ifccParser::InputContext *ctx) {
    std::cout << "# input parametre " << ctx->expr()->getText() << "\n" ;
    listInput.push_back(ctx->expr()->getText());
    visit(ctx->expr());
    if (ctx->input()) {
        visit(ctx->input());
    }
    return 0;
}

antlrcpp::Any DeclarationCheckVisitor::visitArgs(ifccParser::ArgsContext *ctx)
{
    visit(ctx->VAR());
    listeParams.push_back(ctx->VAR()->getText());
    if(ctx->args()){
        visit(ctx->args());
    }
    return 0;
}

antlrcpp::Any DeclarationCheckVisitor::visitFunc(ifccParser::FuncContext *ctx)
{
    std::cout << "# fonction " << ctx->VAR()->getText() << "\n" ;
    if (ctx->args()) {
        visit(ctx->args());
    }
    if (ctx->code()) {
        visit(ctx->code());
    }
    mapFunctions[ctx->VAR()->getText()] = listeParams;
    listeParams.clear();
    listeDeclarations.clear();
    if (ctx->func()) {
        visit(ctx->func());
    }
    return 0;
}

antlrcpp::Any DeclarationCheckVisitor::visitFuncCall(ifccParser::FuncCallContext *ctx)
{
    std::cout << "# appel de fonction " << ctx->VAR()->getText() << "\n" ;
    try {
        mapFunctions.at(ctx->VAR()->getText());
    } catch (const std::out_of_range& oor) {
        std::cerr << "# fonction " << ctx->VAR()->getText() << " non déclarée\n" ;
        exit(3);
    }

    if (ctx->input()) {
        visit(ctx->input());
    }
    std::list<std::string> listeParamsFonction = mapFunctions[ctx->VAR()->getText()];
    if (listInput.size() != listeParamsFonction.size()) {
        std::cerr << "# nombre de paramètres incorrects\n" ;
        exit(3);
    }
    listInput.clear();
    return 0;
}

antlrcpp::Any DeclarationCheckVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx)
{
    visit(ctx->vars());
    for(std::string var:listeLigne){
        std::cout << "# declaration de " << var << "\n" ;
        bool found = (std::find(listeDeclarations.begin(), listeDeclarations.end(), var) != listeDeclarations.end()
        || std::find(listeParams.begin(), listeParams.end(), var) != listeParams.end());
        if(found){
            std::cerr << "# var " << var << " déjà déclarée\n" ;
            exit(3);
        }
        listeDeclarations.push_back(var);
    }
   
    if(ctx->expr()){
        visit(ctx->expr());
    }
    listeLigne.clear();
    return 0;
}

antlrcpp::Any DeclarationCheckVisitor::visitAffectation(ifccParser::AffectationContext *ctx)
{

    visit(ctx->vars());
    for(std::string var:listeLigne){
        bool found = (std::find(listeDeclarations.begin(), listeDeclarations.end(), var) != listeDeclarations.end()
        || std::find(listeParams.begin(), listeParams.end(), var) != listeParams.end());
        if(!found){
            std::cerr << "# var " << var << " non déclarée\n" ;
            exit(3);
        }
        std::cout << "# affectation de " << var << "\n" ;
    }
    visit(ctx->expr());
    listeLigne.clear();
    return 0;
}

antlrcpp::Any DeclarationCheckVisitor::visitVar(ifccParser::VarContext *ctx)
{
    if(ctx->VAR()){
        bool found = (std::find(listeDeclarations.begin(), listeDeclarations.end(), ctx->VAR()->getText()) != listeDeclarations.end()
        || std::find(listeParams.begin(), listeParams.end(), ctx->VAR()->getText()) != listeParams.end());
        if(!found){
            std::cerr << "# var " << ctx->VAR()->getText() << " non déclarée\n" ;
            exit(3);
        }
        std::cout << "# expression avec " << ctx->VAR()->getText() << "\n" ;
    }
    return 0;
}
		
antlrcpp::Any DeclarationCheckVisitor::visitVars(ifccParser::VarsContext *ctx){
    listeLigne.push_back(ctx->VAR()->getText());
    if(ctx->vars()){
        visit(ctx->vars());
    }
    return 0;
}
