#pragma once
#include <string>
#include <vector>
#include <iostream>
const std::string identeficatorType[] = { "int", "float", "string", "char", "bool" };
struct elementTableElement
{
	std::string name_iden;
	std::string type;
	unsigned int level;
	elementTableElement* collision;
	bool repeatedDeclaration = false;
};
class IdentidicatorTable
{
public:
	IdentidicatorTable(int size);
	~IdentidicatorTable();
	void addElem(std::string& name_iden, unsigned int& level, std::string& type);
	void handleCollision(elementTableElement* place, elementTableElement* curElem);
	elementTableElement* createElement(std::string& name_iden, unsigned int& level, std::string& type);
	elementTableElement* lookUp(std::string& name_iden, unsigned long& index);
	void printElems();
private:
	unsigned long hash(std::string& str);
	elementTableElement** items = nullptr;
	int size = 0;
	int count = 0;
	int id = 0;

};
