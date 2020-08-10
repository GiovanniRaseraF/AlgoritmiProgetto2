#pragma once
#include <iostream>
class Lambda
{
public:
	/*
	EFFETTO: Permette di generalizzare l'esecuzione
	*/
	virtual void insert(int key, const std::string& val) { return; }

	/*
	EFFETTO: Resetta l'albero
	*/
	virtual void clear(){return;}

	/*
	EFFETTO: ritorna true se l'elemento è contenuto e false altrimenti
	*/
	virtual bool contains(int key){return false;}
};

