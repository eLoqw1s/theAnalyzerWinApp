#include "Data.h"

int countLines = 1;
int countChar = 1;
int colorErrorPos = 0;
int KolLbl = -1;
int KolId = 2;
int NomStr;
int f = 0, r; //f-первый символ лексемы, r-перемещение от f до конца лексемы
int NumNeTerm = 0;
int NumColLR = 0;
int NextAddr = 0;

int LexCodeLR[1000];
char Bukvy[59] = { 'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ё', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я',
'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
char Cyfry[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
std::string SymsLR[MaxSymLR];
tElemLR LRTbl[MaxStateLR][MaxSymLR] = {};
tElemLbl Lbls[MaxLbl];
tElemIde Idents[MaxId];

std::vector<tToken> tokenVec;
std::stack<int> ParserSt; // Стек состояния анализатора
std::queue<std::string> Lines; // Стек ошибок
std::stack<PntElTblIde>AttrSt;

std::string tokenLine = "";
std::string errorSost = "Анализ успешно завершен";
std::string errorPositionInLine = "Ошибок не обнаружено";
std::string memory = "";
std::string StrProg; //буфер - копия теста

enum tOperCode{ opAdd , opSub, opMult, opDiv, opAss , opOr, opAnd , opRel };
enum TypeCod { typeVoid, typeInt, typeFloat, typeBool };
enum tCatId { catNoCat, catProgName, catVarName, catTypeName }; // категории

tElLexClass LexClass[KolLexClass] = {
	{"and", lcAnd},
	{"beginB", lcBeginB},
	{"end", lcEnd},
	{"endB", lcEndB},
	{"endModule", lcEndModule},
	{"false", lcFalse},
	{"if", lcIf},
	{"or", lcOr},
	{"startModule", lcStartModule},
	{"true", lcTrue},
	{",", lcComma},
	{"[", lcOpParSq},
	{"]", lcClParSq},
	{"+", lcAdd},
	{"*", lcMult},
	{"ass", lcAss},
	{"rel", lcRel},
	{"!", lcVoskl},
	{"lbl", lcLbl},
	{"id", lcId},
	{"(", lcOpPar},
	{")", lcClPar},
	{"..", lcDotDot},
};

//Таблица ключевых слов
struct tElemKey KeyWords[MaxKeys] = {
	{"and", "*"},
	{"beginB", "beginB"},
	{"end", "end" },
	{"endB", "endB"},
	{"endModule", "endModule" },
	{"false", "false"},
	{"if", "if" },
	{"or", "+"},
	{"startModule", "startModule" },
	{"true", "true"},
	{"Y", "YYY" }
};

//Таблица переходов как константа.
//Для вычисления номера строки, сответствующей символу, нужна спец. функция NomStrOfTP
int TP[25][18] = {
	{},
	{  -2,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{  -3,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{  -4,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{  -5,  -9, -11, -13, -15, -28, -28, 13,  -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{  -6,  -9, -11, -13, -15, -28, -28, 13,  -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{  -7,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{  -8,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{   1, -10, -12, -14, -16, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{   2,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{   3,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{   4,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{   5,  -9, -11, -13, -15, -17, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{   6,  -9, -11, -13, -15, -28, -18, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{ -28,  -9, -11, -13, -15, -28, -28, -28, -28, -22,   7,  11, -27, -28, -19,   7, -28, -25 },
	{  16,  -9, -11, -13, -15, -28, -28, -28,  17, -22,   8,  11, -27, -28, -19, -21,  17, -25 },
	{   9,  -9, -11, -13, -15, -28, -28, -28, -28,   9, -20,  11, -27, -28, -19, -21, -28, -25 },
	{  10,  -9, -11, -13, -15, -28, -28,  14,  15,   9,  10,  11, -27,  14,  14,  15, -28, -25 },
	{  11,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20, -26, -27, -28, -19, -21, -28, -25 },
	{  12,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11,  12, -28, -19, -21, -28, -25 },
	{  12,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11,  12, -28, -19, -21, -28, -25 },
	{  12,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11,  12, -28, -19, -21, -28, -25 },
	{ -23,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{ -24,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 },
	{ -28,  -9, -11, -13, -15, -28, -28, -28, -28, -22, -20,  11, -27, -28, -19, -21, -28, -25 }
};

//таблица соответствий конечного сотояния и лексемы
//доступ к элементу: -Номер конечного состояния, т.к. оно отрицательное
struct tToken SostAndToken[28] = {
	{},
	{11, 0, ","},		 // {-2} ,
	{12, 0, "["},	     // {-3} ]
	{13, 0, "]"},		 // {-4} [
	{14, 0, "+"},		 // {-5} +
	{14, 0, "+"},		 // {-6} -
	{15, 0, "*"},		 // {-7} *
	{15, 0, "*"},		 // {-8} /
	{16, 0, "ass"},		 // {-9} =
	{17, 0, "rel"},		 // {-10} ==
	{17, 0, "rel"},		 // {-11} <
	{17, 0, "rel"},		 // {-12} <=
	{17, 0, "rel"},		 // {-13} >
	{17, 0, "rel"},		 // {-14} >=
	{18, 0, "!"},		 // {-15} !
	{17, 0, "rel"},		 // {-16} !=
	{14, 0, "+"},		 // {-17} ||
	{15, 0, "*"},		 // {-18} &&
	{19, 0, "lbl"},		 // {-19} lbl e
	{19, 0, "lbl"},		 // {-20} lbl celoe
	{19, 0, "lbl"},		 // {-21} lbl float
	{20, 0, "id"},		 // {-22} id
	{21, 0, "("},		 // {-23} (
	{22, 0, ")"},		 // {-24} )
	{23, 0, ".."}		 // {-25} ..
};


void errorPosition() {
	if (StrProg[r] == '\n') {
		countLines++;
		countChar = 1;
	}
	else {
		countChar++;
	}
}

int NomStrOfTP(char Sym) {
	char CharUp;
	int Result;
	bool FindBukvy = false;
	bool FindCyfry = false;

	CharUp = toupper(Sym);

	FindBukvy = std::find(Bukvy, Bukvy + 59, CharUp) != std::end(Bukvy);
	FindCyfry = std::find(Cyfry, Cyfry + 10, CharUp) != std::end(Cyfry);

	if (r != 0 && CharUp == 'E' && std::find(Cyfry, Cyfry + 10, std::toupper(StrProg[r - 1])) != std::end(Cyfry)) {
		Result = 15;
	}

	else if (FindBukvy) { Result = 17; }
	else if (FindCyfry) { Result = 18; }
	else {
		switch (Sym)
		{
		case ',': Result = 2; break;
		case '[': Result = 3; break;
		case ']': Result = 4; break;
		case '+': Result = 5; break;
		case '-': Result = 6; break;
		case '*': Result = 7; break;
		case '/': Result = 8; break;
		case '=': Result = 9; break;
		case '<': Result = 10; break;
		case '>': Result = 11; break;
		case '!': Result = 12; break;
		case '|': Result = 13; break;
		case '&': Result = 14; break;
		case '.': Result = 16; break;
		case '#': Result = 19; break;
		case ' ': Result = 20; break;
		case '\t': Result = 21; break;
		case '\n': Result = 22; break;
		case '(': Result = 23; break;
		case ')': Result = 24; break;
		default:
			Result = 25;
		}
	}
	return Result;
}

int BinarySearchLexKey(std::string Lex) {
	int low = 0;
	int high = MaxKeys - 1;
	int result = 0;

	for (auto& c : Lex) {
		c = toupper(c);
	}

	while (low <= high) {
		int mid = low + (high - low) / 2;

		for (auto& c : KeyWords[mid].Lex) {
			c = toupper(c);
		}

		if (KeyWords[mid].Lex == Lex) {
			result = mid + 1;
			break;
		}
		else if (Lex < KeyWords[mid].Lex) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	return result;
}

int SearchLexLbl(std::string Lex) {
	int i = 0, Result;
	Lbls[KolLbl + 1].Lex = Lex; //Запись лексемы в конец таблицы
	for (auto& c : Lex) {
		c = toupper(c);
	}
	for (int i = 0; i < std::size(Lbls); i++) {
		for (auto& c : Lbls[i].Lex) {
			c = toupper(c);
		}
	}
	while (Lex != Lbls[i].Lex) {
		i++;
	}
	if (i > KolLbl) {
		KolLbl++;
		Lbls[KolLbl].Index = -1;
		Lbls[KolLbl].Lst = nullptr;
		Result = KolLbl;
	}
	else { Result = i; }
	return Result;
}

int SearchLexId(std::string Lex) {
	int i = 0, Result;
	Idents[KolId + 1].Lex = Lex; //Запись лексемы в конец таблицы
	for (auto& c : Lex) {
		c = toupper(c);
	}
	for (int i = 0; i < std::size(Idents); i++) {
		for (auto& c : Idents[i].Lex) {
			c = toupper(c);
		}
	}
	while (Lex != Idents[i].Lex) {
		i++;
	}
	if (i > KolId) {
		KolId++;
		Idents[KolId].Cat = cNoCat;
		Idents[KolId].Tip = cVoid;
		Idents[KolId].Size = 0;
		Idents[KolId].Addr = -1;
		Result = KolId;
	}
	else { Result = i; }
	return Result;
}

tToken Scaner() {
	int StrTP, Sost, i;
	bool NoToken;
	std::string Lex;

	tToken Result;

	Sost = 0; //Начальное состояние автомата
	r = f; //первый символ лексемы
	NoToken = true;

	while (NoToken) {
		while (Sost >= 0) {
			StrTP = NomStrOfTP(StrProg[r]); //номер строки табл. переходов
			Sost = TP[StrTP - 1][Sost]; //Следующее состояние
			if (Sost >= 0) {
				errorPosition();

				r++; //Следующий входной символ
			}
		}
		if (Sost == -27) { //Обработка пробелов и т.п.
			f = r; //первый символ следующей лексемы с учетом возврата одного символа
			r = f;
			Sost = 0;
		}
		else if (Sost == -26) { //Обработка комментариев
			if (r == StrProg.length()-1) {
				f = r;// Последний символ в тексте кода
				return Result;
			}
			else {
				countChar++;
				f = r + 1;
			}
			r = f + 1;
			Sost = 0;
		}
		else { NoToken = false; }
	}
	Sost = -Sost; //позиция в массиве конечных состояний и соответствующих токенов

	Result.dop.cat = catNoCat;

	switch (Sost)
	{
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:

		case 23:
		case 24:
		case 25:

			countChar++;
			Result.Code = SostAndToken[Sost - 1].Code;
			Result.Attr = SostAndToken[Sost - 1].Attr;
			Result.Name = SostAndToken[Sost - 1].Name;
			Result.LexBeg = f;

			if (Sost == 9 || Sost == 11 || Sost == 13 || Sost == 15 ) {
				Result.LexEnd = r - 1;
				f = r;
			}
			else {
				Result.LexEnd = r;
				f = r + 1;
			}
			break;
		case 22: //Идентификатор
			Lex = "";
			for (i = f;i <= r - 1;i++) {
				Lex = Lex + StrProg[i];
			}
			NomStr = BinarySearchLexKey(Lex);
			if (NomStr > 0) { //Ключевое слово
				Result.Code = NomStr;
				Result.Attr = 0;
				Result.Name = KeyWords[NomStr - 1].Name;
				Result.LexBeg = f;
				Result.LexEnd = r - 1;
			}
			else { //Идентификатор
				NomStr = SearchLexId(Lex);
				if (NomStr == 0) { // int
					Result.dop.tip.TypeCode = typeInt;
					Result.dop.tip.Width = 4;
					Result.dop.cat = catTypeName;
				}
				else if (NomStr == 1) { // float
					Result.dop.tip.TypeCode = typeFloat;
					Result.dop.tip.Width = 8;
					Result.dop.cat = catTypeName;
				}
				else if (NomStr == 2) { // bool
					Result.dop.tip.TypeCode = typeBool;
					Result.dop.tip.Width = 1;
					Result.dop.cat = catTypeName;
				}

				Result.Code = SostAndToken[Sost - 1].Code;
				Result.Attr = NomStr;
				Result.Name = SostAndToken[Sost - 1].Name;
				Result.LexBeg = f;
				Result.LexEnd = r - 1;
			}
			f = r;
			break;
		case 19: // e
		case 20: // int
		case 21: // float

			Lex = "";
			for (i = f;i <= r - 1;i++) {
				Lex = Lex + StrProg[i];
			}
			NomStr = SearchLexLbl(Lex);
			Result.Code = SostAndToken[Sost - 1].Code;
			Result.Attr = NomStr;
			Result.Name = SostAndToken[Sost - 1].Name;
			Result.LexBeg = f;
			Result.LexEnd = r - 1;
			f = r;

			if (Sost == 19) 
			{
				Result.dop.tip.TypeCode = typeFloat;
			}
			else if (Sost == 20)
			{
				Result.dop.tip.TypeCode = typeInt;
			}
			else if (Sost == 21)
			{
				Result.dop.tip.TypeCode = typeFloat;
			}

			break;
		case 28:
			Result.Code = 55; // Lex error
			std::cout << "\n   Обнаружена лексическая ошибка LexErr_1: Лексема не может начинаться"
				<< " с символа " << "\"" << StrProg[f] << "\"" << "\n" << "   Номер строки: "
				<< countLines << "\n   Номер символа в строке: " << countChar << std::endl;
		
			errorSost = "Обнаружена лексическая ошибка LexErr_1: Лексема не может начинаться"
				" с символа \"" + std::string(1, StrProg[f]) + "\"\n";

			errorPositionInLine = "Номер строки: " + std::to_string(countLines) +
				"   Номер символа в строке: " + std::to_string(countChar);

			f = StrProg.length();

			return Result;
			break;
		default:
			break;
	}

	std::string tokenDopName = "";
	for (int c = Result.LexBeg; c <= Result.LexEnd; c++) {
		tokenDopName += StrProg[c];
	}

	if (tokenDopName == "=")
	{
		Result.dop.opCode = opAss;
	}
	else if (tokenDopName == "-")
	{
		Result.dop.opCode = opSub;
	} 
	else if (tokenDopName == "+")
	{
		Result.dop.opCode = opAdd;
	} 
	else if (tokenDopName == "*")
	{
		Result.dop.opCode = opMult;
	} 
	else if (tokenDopName == "/")
	{
		Result.dop.opCode = opDiv;
	}
	else if (tokenDopName == "&&" || tokenDopName == "and")
	{
		Result.dop.opCode = opAnd;
	}
	else if (tokenDopName == "||" || tokenDopName == "or")
	{
		Result.dop.opCode = opOr;
	}
	else if (tokenDopName == "<" || tokenDopName == ">" || tokenDopName == "<=" || tokenDopName == ">=")
	{
		Result.dop.opCode = opRel;
	}

	if (tokenDopName == "true" || tokenDopName == "false")
	{
		Result.dop.tip.TypeCode = typeBool;
	}

	Result.dop.nameToken = tokenDopName;
	Result.nameT = tokenDopName;

	tokenLine += "<" + Result.Name + ", " + std::to_string(Result.Attr) + ">";

	std::cout << "<" << Result.Name << ", " << Result.Attr << "> ";
	if (!BinarySearchLexKey(Lex) && (Sost == 19 || Sost == 20 || Sost == 21 || Sost == 22 || Sost == 28)) {

		tokenLine += "      Лексема: ";
		
		std::cout << "\t# Лексема: ";
		for (int c = Result.LexBeg; c <= Result.LexEnd; c++) {
			tokenLine += std::string(1, StrProg[c]);

			std::cout << StrProg[c];
		}
		tokenLine += " ";

		std::cout << " #";
	}
	std::cout << std::endl;

	tokenLine += "\n";

	return Result;
}

void initDataType() {
	for (auto i : Idents) {
		i = {};
	}
	for (auto l : Lbls) {
		l = {};
	}

	Idents[0].Lex = "int";
	Idents[0].Cat = cCatType;
	Idents[0].Tip = cInt;
	Idents[0].Size = 4;
	Idents[0].Addr = -1;

	Idents[1].Lex = "float";
	Idents[1].Cat = cCatType;
	Idents[1].Tip = cFloat;
	Idents[1].Size = 8;
	Idents[1].Addr = -1;

	Idents[2].Lex = "bool";
	Idents[2].Cat = cCatType;
	Idents[2].Tip = cBool;
	Idents[2].Size = 1;
	Idents[2].Addr = -1;

	KolLbl = -1;
	KolId = 2;
}

void Syntax_Error_LR(int State, tToken Token) {
	std::string Soob, LstSym;

	while (!Lines.empty()) {
		Lines.pop(); // Удаляем верхний элемент
	}
	LstSym = "";

	// Генерация сообщения
	for (int i = NumNeTerm + 1; i <= 35; ++i) {
		if (LRTbl[State][i].ElType != lrErr) {
			if (!LstSym.empty())
				LstSym += ", «" + SymsLR[i] + "»";
			else
				LstSym = "«" + SymsLR[i] + "»";
		}
	}

	Soob = "Допустимые символы: " + LstSym;
	Lines.push("Обнаружена синтаксическая ошибка SynErr: Недопустимый символ!");
	Lines.push(Soob);

	errorSost = "";

	for (int i = 0; i <= Lines.size(); i++) {
		std::string line = Lines.front();
		Lines.pop();
		std::cout << line << "\n";

		errorSost += line;
	}
}


void Type_Error(int code, const std::string& token) {
	std::cerr << "Semantic Error (" << code << "): " << token << std::endl;

	errorSost = "Semantic Error (" + std::to_string(code) + "): " + token + "\n";
}

void AddType(PntElTblIde &Pnt, tCatId Cat, tType Typ) {
	Pnt.cat = Cat;  // установка категории
	Pnt.tip = Typ;  // установка типа
	if (Cat == catVarName) {
		while (NextAddr % Typ.Width != 0) NextAddr++;
		if (Pnt.isArr == true) 
		{
			NextAddr -= Typ.Width;
			Pnt.tip.Width *= Pnt.cDemension;
		}
		Pnt.addr = NextAddr; // установка адреса памяти
		NextAddr += Pnt.tip.Width; // адрес очередной свободной памяти
		
	}
	else {
		Pnt.addr = -1; // нет адреса памяти
	}
}

bool A1(tToken& token) {
	if (token.dop.cat != catNoCat) {
		Type_Error(1, "Duplicate declaration");
		return false;
	}
	tType t{ typeVoid, 4 };
	AddType(token.dop, catProgName, t);
	return true;
}

bool A2(tToken& Token) {
	if (Token.dop.cat != catNoCat) {
		Type_Error(1, "Duplicate declaration");
		return false;
	}
	AttrSt.push(Token.dop);
	return true;
}

void A3(tToken& Token) {
	PntElTblIde t1 = AttrSt.top();
	AttrSt.pop();
	PntElTblIde t2 = AttrSt.top();
	AttrSt.pop();
	AddType(t1, catVarName, t2.tip);
	Token.dop = t1;
}

void A4(tToken& Token) {
	PntElTblIde t1 = AttrSt.top();
	AttrSt.pop();
	PntElTblIde t2 = AttrSt.top();
	AttrSt.pop();
	AddType(t1, catVarName, t2.tip);
	AttrSt.push(t1);
	Token.dop = t1;
}

bool A5(tToken& Token) {
	if (Token.dop.cat != catTypeName) {
		Type_Error(2, "Not a type name");
		return false;
	}
	auto pt = Token.dop;
	AttrSt.push(pt);
	return true;
}

bool A6(tToken& Token) {
	if (Token.dop.cat == catNoCat) {
		Type_Error(5, "Identifier not declared");
		return false;
	}
	if (Token.dop.cat != catVarName) {
		Type_Error(3, "Not a variable name");
		return false;
	}
	AttrSt.push(Token.dop);
	return true;
}

bool A7(tToken& Token) {
	PntElTblIde t1 = AttrSt.top(); // Фактор адрес
	AttrSt.pop();
	PntElTblIde t2 = AttrSt.top(); // Тип выражения
	AttrSt.pop();
	PntElTblIde t3 = AttrSt.top(); // Идентификатор
	AttrSt.pop();

	if (t3.tip.TypeCode != t2.tip.TypeCode) {
		Type_Error(4, "Type mismatch");
		return false;
	}

	return true;
}

void A8(tToken token) {
	AttrSt.push(token.dop); // атрибут оператора
}

bool A9(tToken token) {
	PntElTblIde t1 = AttrSt.top();  // адрес терма
	AttrSt.pop();
	PntElTblIde t2 = AttrSt.top(); // тип терма
	AttrSt.pop();
	PntElTblIde t3 = AttrSt.top();  // оператор +
	AttrSt.pop();
	PntElTblIde t4 = AttrSt.top(); // адрес первого выражения
	AttrSt.pop();
	PntElTblIde t5 = AttrSt.top(); // тип первого выражения
	AttrSt.pop();

	if (t3.opCode == opRel)
	{
		t5.tip.TypeCode = typeBool;
		t2.tip.TypeCode = typeBool;
	}

	if (t5.tip.TypeCode != t2.tip.TypeCode) {
		Type_Error(4, "Type mismatch");
		return false;
	}

	AttrSt.push(t2); // атрибут Expr.type
	auto t6 = t2; // Атрибуты как у t2
	AttrSt.push(t6); // атрибут Expr.addr

	return true;
}

void A12(tToken& Token) {
	PntElTblIde p = Token.dop; // атрибут фактора
	auto pt = p;
	AttrSt.push(pt); // атрибут Factor.type
	AttrSt.push(p); // атрибут Factor.addr
}

bool A13(tToken& Token) {
	if (Token.dop.cat == catNoCat) {
		Type_Error(5, "Identifier not declared");
		return false;
	}
	if (Token.dop.cat != catVarName) {
		Type_Error(3, "Not a variable name");
		return false;
	}
	auto pt = Token.dop;
	AttrSt.push(pt); // атрибут Factor.type
	AttrSt.push(Token.dop); // атрибут Factor.addr
	return true;
}

bool A14(tToken& Token) {
	if (Token.dop.tip.TypeCode != typeInt)
	{
		Type_Error(4, "Demension must be int");
		return false;
	}
	PntElTblIde t1 = AttrSt.top();
	AttrSt.pop();
	tToken tkn = tokenVec.back();
	tokenVec.pop_back();
	t1.cDemension++;
	t1.high.push(std::stoi(Token.dop.nameToken));
	AttrSt.push(t1);
	tkn.dop = t1;
	tokenVec.push_back(tkn);
	return true;
}

void A16() {
	PntElTblIde t1 = AttrSt.top();
	AttrSt.pop(); 
	tToken tkn = tokenVec.back();
	tokenVec.pop_back();
	t1.isArr = true;
	AttrSt.push(t1);
	tkn.dop = t1;
	tokenVec.push_back(tkn);
}

bool A17(tToken& Token) {
	if (Token.dop.isArr == false)
	{
		Type_Error(6, "This var is not array");
		return false;
	}
	AttrSt.push(Token.dop);
	return true;
}

bool A18(tToken& Token) {
	if (Token.dop.tip.TypeCode != typeInt)
	{
		Type_Error(7, "Index of array must be int");
		return false;
	}
	PntElTblIde t1 = AttrSt.top();
	AttrSt.pop();

	t1.cDemension = t1.cDemension - 1;
	if (t1.cDemension < 0)
	{
		Type_Error(11, "The dimension of this array is greater than the specified one");
		return false;
	}

	if (t1.high.front() < std::stoi(Token.dop.nameToken))
	{
		Type_Error(10, "Going beyond the boundaries of the array");
		return false;
	}
	t1.high.pop();

	AttrSt.push(t1);

	return true;
}

void A19() {
	PntElTblIde t1 = AttrSt.top();
	AddType(t1, catVarName, t1.tip);
	AttrSt.pop();

	tToken tkn = tokenVec.back();
	tokenVec.pop_back();
	tkn.dop = t1;
	tokenVec.push_back(tkn);
}

bool A20(tToken& Token) {
	PntElTblIde t1 = AttrSt.top();
	AttrSt.pop();
	if (t1.cDemension != 0) 
	{
		Type_Error(12, "The dimension of this array is less than the specified one");
		return false;
	}
	
	return true;
}


bool Semantic_Action(int ActionCode, tToken& Token) { // true - успешно, false - ошибка
	bool result = true;

	switch (ActionCode) {
	case 1:
		if (!A1(Token)) result = false;
		break;
	case 2:
		if (!A2(Token)) result = false;
		break;
	case 3:
		A3(Token);
		tokenVec.push_back(Token);
		break;
	case 4:
		A4(Token);
		tokenVec.push_back(Token);
		break;
	case 5:
		if (!A5(Token)) result = false;
		break;
	case 6:
		if (!A6(Token)) result = false;
		break;
	case 7:
		if (!A7(Token)) result = false;
		break;
	case 8:
		A8(Token);
		break;
	case 9:
		if (!A9(Token)) result = false;
		break;
	case 10:
		A8(Token);
		break;
	case 11:
		if (!A9(Token)) result = false;
		break;
	case 12:
		A12(Token);
		break;
	case 13:
		if (!A13(Token)) result = false;
		break;
	case 14:
		if (!A14(Token)) result = false;
		break;
	case 16:
		A16();
		break;
	case 17:
		if (!A17(Token)) result = false;
		break;
	case 18:
		if (!A18(Token)) result = false;
		break;
	case 19:
		A19();
		break;
	case 20:
		if (!A20(Token)) result = false;
		break;
	case 21:
		if (!A9(Token)) result = false;
		break;
	case 22:
		A8(Token);
		break;

	default:
		std::cerr << "Unknown Action Code: " << static_cast<int>(ActionCode) << std::endl;
		result = false;
		break;
	}

	return result;
}



bool SUT_LR() {
	tokenVec.clear();
	std::cout << "NumNeTerm = " << NumNeTerm << std::endl;
	r = 0;
	f = 0;
	while (!ParserSt.empty()) {
		ParserSt.pop();
	}
	tToken Token, PredToken;
	tElemLR ElemLR;
	int i, Sym; // Sym - входной символ парсера (либо код токена, либо код нетерминала)
	int State, tmp;
	int Lex; // tLexCode
	bool Result;
	if (StrProg.length() == 0) {
		exit(1);
	}
	
	initDataType();

	ParserSt.push(1);
	Token = Scaner();
	PredToken = Token;
	if (Token.Code != 55)
	{
		ElemLR.ElType = 0;
		Lex = Token.Code;

		Sym = LexCodeLR[Lex - 1];
		while (ElemLR.ElType != lrStop) { // пока не элемент останова
			State = ParserSt.top(); // текущее состояние анализатора
			ElemLR = LRTbl[State][Sym];

			switch (ElemLR.ElType) {
			case lrErr: { // синтаксическая ошибка
				Syntax_Error_LR(State, Token);
				Result = false;
				ElemLR.ElType = lrStop; // чтобы выйти из цикла
				return false;
				break;
			}

			case lrShift: { // элемент переноса
				ParserSt.push(ElemLR.ElPar); // состояние в стек
				if (Sym > NumNeTerm) { // терминал, принять его
					bool found = false;
					for (size_t k = tokenVec.size(); k > 0; --k) { // Проход по вектору в обратном порядке
						if (tokenVec[k - 1].dop.nameToken == Token.nameT) {
							PredToken = tokenVec[k - 1]; // Присваиваем последнее вхождение Token
							found = true;
							break; // Прерываем цикл после нахождения
						}
					}
					if (!found) {
						PredToken = Token;
					}
					else {
						found = false;
					}
					

					Token = Scaner(); // получение следующего токена
					Lex = Token.Code; // Lex - очередной входной символ

					// сопоставление терминала и столбца в табл. разбора
					Sym = LexCodeLR[Lex-1];

					if (Token.Code == 55) { // Лексическая ошибка
						Result = false;
						ElemLR.ElType = lrStop; // чтобы выйти из цикла
						return false;
					}
				}
				else {
					Lex = Token.Code;
					// сопоставление терминала и столбца в табл. разбора
					Sym = LexCodeLR[Lex-1];
				}
				break;
			}

			case lrReduct: { // элемент свертки
				for (int i = 0; i < ElemLR.ElPar; i++) {
					tmp = ParserSt.top(); // удаление верхних элементов стека
					ParserSt.pop();
				}
				Sym = ElemLR.Left; // нетерминал левой части как новый входной символ
				if (ElemLR.Act != 0) { // есть действие
					if (!Semantic_Action(ElemLR.Act, PredToken)) { // выполнить действия
						Result = false;
						ElemLR.ElType = lrStop; // чтобы выйти из цикла
						return false;
					}
				}
				break;
			}
			}
		}

		for (int index = 0; index < tokenVec.size(); index++)
		{
			std::string addres = std::to_string(tokenVec[index].dop.addr);

			while (addres.size() % 3 != 0)
			{
				addres = "0" + addres;
			}

			memory += addres + ": " + tokenVec[index].dop.nameToken + " Width: " +
				std::to_string(tokenVec[index].dop.tip.Width) + "\n";

			std::cout << memory;
		}

		return true;
	}
}




