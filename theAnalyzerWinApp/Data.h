#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>

using namespace System;
using namespace System::Xml;
using namespace System::Collections::Generic;

#define MaxKeys 14 //макимально число ключевых слов (с учетом сторожа, т.е. реально на 1 меньше)
#define MaxLbl 101 //макимально число меток (с учетом сторожа, т.е. реально на 1 меньше)
#define MaxId 201 //Макс. размер таблицы идентификаторов (с учетом сторожа, т.е. реально на 1 меньше)
#define KolLexClass 23 //число лексических классов
#define MaxSymLR 300
#define MaxStateLR 300

//именованные костанты кодов простых типов
#define cNoCat 0 //осутсвие типа
#define cInt 1 //целый тип
#define cFloat 2 //вещественный тип
#define cBool 3 //булевский тип

//именованные константы категорий идентификаторов
#define cVoid 0 //осутсвие типа
#define cCatType 3  //Имя типа (integer, float, Boolean)

#define lrErr  0 //элемент ошибки
#define lrShift  1 //элемент переноса
#define lrReduct  2 //элемент свертки
#define lrStop  3 //элемент останова

extern int countLines;
extern int countChar;
extern int colorErrorPos;
extern int KolLbl;
extern int KolId;
extern int NomStr;
extern int NextAddr;
extern int NumNeTerm;
extern int NumColLR;
extern int f, r; //f-первый символ лексемы, r-перемещение от f до конца лексемы

extern enum TypeCod;
extern enum tCatId;
extern enum tOperCode;
extern enum tLexCode {
	lcAnd,
	lcBeginB,
	lcEnd,
	lcEndB,
	lcEndModule,
	lcFalse,
	lcIf,
	lcOr,
	lcStartModule,
	lcTrue,
	lcComma,
	lcOpParSq,
	lcClParSq,
	lcAdd,
	lcMult,
	lcAss,
	lcRel,
	lcVoskl,
	lcLbl,
	lcId,
	lcOpPar,
	lcClPar,
	lcDotDot,
	lcErr
};

extern std::string tokenLine;
extern std::string errorSost;
extern std::string errorPositionInLine;
extern std::string memory;
extern std::string StrProg; //буфер - копия теста

extern char Bukvy[];
extern char Cyfry[];
extern int TP[25][18];

extern struct tElemKey{
	std::string Lex;
	std::string Name;
};

extern struct tElSp {
	int Info;
	tElSp* Next;
};

extern struct tElemLbl {
	std::string Lex;
	int Index;
	tElSp* Lst;
};

extern struct tElemIde {
	std::string Lex;
	int Cat;
	int Tip;
	int Size;
	int Addr;
};

extern struct tType {
	TypeCod TypeCode;
	int Width;
};

extern struct PntElTblIde {
	tCatId cat;
	tType tip;
	int addr;
	std::string nameToken;
	tOperCode opCode;
	bool isArr = false;
	int cDemension = 0;
	std::queue<int> high;
};

extern struct tToken {
	int Code, Attr;
	std::string Name;
	int LexBeg, LexEnd;
	PntElTblIde dop;
	std::string nameT;
};

extern struct tElemLR {
	int ElType;
	int ElPar;
	int Left;
	int Act;
};

extern struct tElLexClass {
	std::string LexName;
	tLexCode LexCode;
};

extern std::string SymsLR[MaxSymLR];
extern tElemLR LRTbl[MaxStateLR][MaxSymLR];
extern int LexCodeLR[1000];
extern tElLexClass LexClass[KolLexClass];

extern tToken Scaner();
extern bool SUT_LR();
extern void initDataType();
void errorPosition();
//Возвращает номер строки в таблице переходов TP для символа Sym
extern int NomStrOfTP(char Sym);
//Поиск ключевого слова. Возвращает номер строки или 0, если не найдено.
extern int BinarySearchLexKey(std::string Lex);
//Поиск метки и, при необходимости, вставка. Возвращает номер строки
extern int SearchLexLbl(std::string Lex);
//Поиск идентификатора и, при необходимости, вставка. Возвращает номер строки
extern int SearchLexId(std::string Lex);
