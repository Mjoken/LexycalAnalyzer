#pragma once
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
const std::string identeficatorType[] = {"int", "float", "string", "char", "bool"};
struct elementTableElement
{
	unsigned int index;
	std::string name_iden;
	std::string type;
	unsigned int level;
};
struct Linked_List
{
	elementTableElement* item;
	Linked_List* next;
};
class IdentidicatorTable
{
public:
	IdentidicatorTable(int size);
	~IdentidicatorTable();
	elementTableElement* createElem(std::string& name, int& lvl, std::string& type);
	void addElem(std::string& name, int& lvl, std::string& type);
	void handeCollision(unsigned long index, elementTableElement* item);
	elementTableElement* lookUp(std::string& name_iden);
	void insert(std::string& name_iden, int lvl, std::string& type);
private:
	unsigned long hash(std::string& str);
	std::vector<elementTableElement**> item;
	Linked_List** collision = nullptr;
	int size = 0;
	int count = 0;
	int id = 0;
	//int level = 0;
};
