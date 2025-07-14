/*
#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Member.h"


int main()
{
	std::cout << "Hi" << std::endl;

	LinkedList list;

	LinkedList_Initialize(&list);


	Member member = { 1, "HiImFromC" };
	LinkedList_InsertFront(&list, &member);

	Member member1 = { 1, NULL };
	LinkedList_Node* node = LinkedList_Search(&list, &member1, Member_NoCmp);

	

	std::cout << node->data.name << std::endl;
}
*/