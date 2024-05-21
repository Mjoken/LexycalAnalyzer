#include "IdentidicatorTable.h"

IdentidicatorTable::IdentidicatorTable(int size)
{
	this->size = size;
	this->count = 0;
	this->items = new elementTableElement*[size];
	for (size_t i = 0; i < size; i++)
	{
		this->items[i] = nullptr;
	}
}

IdentidicatorTable::~IdentidicatorTable()
{
	
}

void IdentidicatorTable::addElem(std::string& name_iden, unsigned int& level, std::string& type)
{
	unsigned long index = hash(name_iden);
	elementTableElement* repeatedElement = lookUp(name_iden, index);
	elementTableElement* ElementPlace = this->items[index];
	elementTableElement* curElem = createElement(name_iden, level, type);
	if (repeatedElement != nullptr)
	{
		for (size_t i = 0; i < identeficatorType->size(); i++)
		{
			if (identeficatorType[i] == type) curElem->repeatedDeclaration = true;
		}
	}
	
	

	if (ElementPlace == nullptr) 
	{
		this->items[index] = curElem;
		this->count++;
	}
	else 
	{
		if (ElementPlace->name_iden == name_iden) 
		{
			this->items[index]->level = level;
			this->items[index]->repeatedDeclaration = true;
			return;
		}
		else 
		{
			handleCollision(ElementPlace, curElem);
			return;
		}
	}
}

void IdentidicatorTable::handleCollision(elementTableElement* place, elementTableElement* curElem)
{
	elementTableElement* head = place->collision;
	if (head == nullptr) 
	{
		head = curElem;
	}
	else if (head->collision == nullptr) 
	{
		head->collision = curElem;
	}
	else 
	{
		elementTableElement* temp = head;
		while (temp->collision) 
		{
			temp = temp->collision;
		}
		temp->collision = curElem;
	}

}


elementTableElement* IdentidicatorTable::createElement(std::string& name_iden, unsigned int& level, std::string& type)
{
	elementTableElement* TableElement = new elementTableElement;
	TableElement->name_iden = name_iden;
	TableElement->level = level;
	TableElement->type = type;
	TableElement->collision = nullptr;
	return TableElement;
}

elementTableElement* IdentidicatorTable::lookUp(std::string& name_iden, unsigned long& index)
{
	elementTableElement* curitem = this->items[index];
	elementTableElement* head = nullptr;
	if (curitem != nullptr) head = curitem->collision;
	while (curitem != nullptr) 
	{
		if (curitem->name_iden == name_iden) 
		{
			return curitem;
		}
		if (head == nullptr) 
		{
			return nullptr;
		}
		curitem = curitem->collision;
		head = head->collision;
	}

	return nullptr;
}

void IdentidicatorTable::printElems()
{
	std::cout << "\t\t IDENTEFICATORS TABLE" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "Identeficators name " << " \t| levels " << " \t| types " << std::endl;
	for (size_t i = 0; i < this->size; i++) 
	{
		elementTableElement* curElem = this->items[i];
		if (curElem != nullptr) {
			if (curElem->collision == nullptr)
			{
				std::cout << "Identeficator name: " << curElem->name_iden << "\t| level: " << curElem->level << "\t| type: " << curElem->type;
				//std::cout << "\t\t" << curElem->name_iden << "\t\t " << curElem->level << "\t\t" << curElem->type;
				if (curElem->repeatedDeclaration) std::cout << "| <reapeted declaration>";
				std::cout << std::endl;
			}
			else if (curElem->collision != nullptr)
			{
				elementTableElement* curCollision = curElem->collision;
				while (curCollision != nullptr) {
					std::cout << "Identeficator name: " << curElem->name_iden << "| level: " << curElem->level << "| type" << curElem->type;
					//std::cout << "\t\t" << curElem->name_iden << "\t\t " << curElem->level << "\t\t" << curElem->type;
					if (curElem->repeatedDeclaration) std::cout << "| <reapeted declaration>";
					std::cout << std::endl;
					curElem = curCollision;
					curCollision = curCollision->collision;
				}
			}
		}
	}
}

unsigned long IdentidicatorTable::hash(std::string& str)
{
	unsigned long i = 0;
	for (int j = 0; str[j]; j++)
		i += str[j];
	return  i % this->size;
}

