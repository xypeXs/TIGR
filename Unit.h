#pragma once
#include "stddef.h"
#include <cmath>
#include <iomanip>
#include <iostream>
class Unit
{
private:
	// Единицы здоровья, скорость, урон, стоимость, броня, дистанция атаки
	int hp, velocity, dmg, unit_cost, armor, atack_distance;
	// Коорлинаты юнита в сетке карты i, j
	int unit_i, unit_j;
	// Реакция на врага
	short int react_to_enemy;
	// Атакуемая цель
	Unit* target;
	// Флаг выбора юнита, флаг атаки врагом
	bool selected, is_atacked;
	// Расстояние до конечной точки при прокладывании пути
	int distance(int start_i, int start_j, int finish_i, int finish_j);
	//Реализация очереди с приоритетами
	struct priority_queue;
	typedef priority_queue* refs;
	struct priority_queue
	{
		int i, j, key;
		int prev_cell_value;
		refs next;
	};
	//Инициализация очереди
	void InitPriorityQueue(refs& q); 
	// Проверка очереди на пустоту, true - что-то есть
	bool CheckPriorityQueue(refs q); 
	// Добавить элемент в очередь, отсортирована по возрастанию поля key
	void AddPriorityQueue(refs q, int i, int j, int key, int prev_val); 
	// Извлечь элемент из очереди
	void PopPriorityQueue(refs q, int &i, int &j, int &prev_val);
protected:
	// Массив пути, содержит координаты шагов i, j
	struct way_to_target
	{
		int i, j;
	}way[500];
	int way_length;
public:
	Unit(int hp, int vel, int dmg, int cost, int armor, int distance, int i, int j);
	~Unit();
	// Поиск пути жадным алгоритмом
	void FindTheWay(int** a, int n, int m, int start_i, int start_j, int finish_i, int finish_j);
	void PrintWay();
};

