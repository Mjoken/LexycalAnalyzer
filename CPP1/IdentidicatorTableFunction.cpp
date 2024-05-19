#include "IdentidicatorTable.h"

IdentidicatorTable::IdentidicatorTable(int size)
{
	this->size = size;
	this->count = 0;
	this->item;
	this->collision = new Linked_List * [size];
}

IdentidicatorTable::~IdentidicatorTable()
{
	for (size_t i = 0; i < this->size; i++)
	{
		delete[] collision[i];
	}
	delete[] collision;
}

elementTableElement* IdentidicatorTable::createElem(std::string& name, int& lvl, std::string& type)
{
	elementTableElement* item = new elementTableElement;
	
	item->name_iden = name;
	item->level = lvl;
	item->type = type;

	return item;
}

void IdentidicatorTable::addElem(std::string& name, int& lvl, std::string& type)
{
}

void IdentidicatorTable::handeCollision(unsigned long index, elementTableElement* item)
{
	Linked_List* head = this->collision[index];

	if (head == NULL) 
	{
		head = new Linked_List;
		head->next = NULL;
		head->item = item;
	}
	else if (head->next == NULL) 
	{
		Linked_List* node = new Linked_List;
		node->item = item;
		node->next = NULL;
		head->next = node;
	}
	else 
	{
		Linked_List* temp = head;
		while (temp->next) 
		{
			temp = temp->next;
		}
		Linked_List* node = new Linked_List;
		node->item = item;
		node->next = NULL;
		temp->next = node;
	}
	this->collision[index] = head;
}

elementTableElement* IdentidicatorTable::lookUp(std::string& name_iden)
{
	int index = hash(name_iden);
	elementTableElement* item = *this->item[index];
	Linked_List* head = this->collision[index];
	while (item != NULL) 
	{
		if (item->name_iden == name_iden) 
		{
			return item;
		}
		if (head == NULL)
		{
			return NULL;
		}
		item = head->item;
		head = head->next;
	}
	return nullptr;
}

void IdentidicatorTable::insert(std::string& name_iden, int lvl, std::string& type)
{
	elementTableElement* item = lookUp(name_iden);
	if (item != NULL) 
	{
		for (size_t i = 0; i < identeficatorType->size(); i++)
		{
			if (identeficatorType[i] == type) std::cout << "Repeated declaration in the same scope." << " Level:" << lvl << " Name: " << name_iden << std::endl;;
		}

	}
	item = createElem(name_iden, lvl, type);
	unsigned long index = hash(name_iden);
	elementTableElement* current_item = *this->item[index];

	if (current_item == NULL)
	{
		// Помешаем элемент в это место и увеличиваем количество элементом на 1
		*this->item[index] = item;
		this->count++;
	}
	// Если там занято
	else {
		// Если это тот же ключ, то заменяем ему значения уровня
		if (current_item->name_iden == name_iden)
		{
			//this->item[index]->level = lvl;
			return;
		}
		// Если там лежит другой элемент, обрабатываем коллизию 
		else
		{
			handeCollision(index, item);
			return;
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
