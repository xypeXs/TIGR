#include "Unit.h"


Unit::Unit(int hp, int vel, int dmg, int cost, int armor, int distance, int i, int j)
{
	this->hp = hp;
	this->velocity = vel;
	this->dmg = dmg;
	this->unit_cost = cost;
	this->armor = armor;
	this->atack_distance = distance;
	this->unit_i = i;
	this->unit_j = j;
	react_to_enemy = 0; // Игнорировать врага
	target = NULL;
	selected = false;
	is_atacked = false;
	way_length = 0;
}

void Unit::FindTheWay(int** a, int n, int m, int start_i, int start_j, int finish_i, int finish_j)
{
	refs inz;
	int i, j, counter = 0;
	int prev_val = 1; // Значение на "предыдущей клетке"
	bool flag = false; // Путь не найден
	a[start_i][start_j] = 1;
	InitPriorityQueue(inz);
	AddPriorityQueue(inz, start_i, start_j, 0, prev_val);
	while ((CheckPriorityQueue(inz)) && (!flag))
	{
		PopPriorityQueue(inz, i, j, prev_val);
		way[/*a[i][j]*/prev_val - 1].i = i;
		way[/*a[i][j]*/prev_val - 1].j = j;
		way_length = /*a[i][j]*/prev_val;
		if ((i == finish_i) && (j == finish_j))
			flag = true;
		else
		{
			//if ((i - 1 > 0) && (a[i - 1][j] == 0))
			if ((i - 1 > 0) && (a[i - 1][j] == 0))
			{
				//a[i - 1][j] = a[i][j] + 1;
				a[i - 1][j] = prev_val +1;
				AddPriorityQueue(inz, i - 1, j, distance(i - 1, j, finish_i, finish_j) /*+ distance(i - 1, j, start_i, start_j)*/, prev_val + 1);
			}
			if ((j - 1 > 0) && (a[i][j - 1] == 0))
			{
				//a[i][j - 1] = a[i][j] + 1;
				a[i][j - 1] = prev_val + 1;
				AddPriorityQueue(inz, i, j - 1, distance(i, j - 1, finish_i, finish_j) /*+ distance(i, j - 1, start_i, start_j)*/, prev_val + 1);
			}
			if ((i + 1 < n) && (a[i + 1][j] == 0))
			{
				//a[i + 1][j] = a[i][j] + 1;
				a[i + 1][j] = prev_val + 1;
				AddPriorityQueue(inz, i + 1, j, distance(i + 1, j, finish_i, finish_j)/* + distance(i + 1, j, start_i, start_j)*/, prev_val + 1);
			}
			if ((j + 1 < m) && (a[i][j + 1] == 0))
			{
				//a[i][j + 1] = a[i][j] + 1;
				a[i][j + 1] = prev_val + 1;
				AddPriorityQueue(inz, i, j + 1, distance(i, j + 1, finish_i, finish_j) /*+ distance(i, j + 1, start_i, start_j)*/, prev_val + 1);
			}
		}
	}

	// Освобождаем память
	while (CheckPriorityQueue(inz))
		PopPriorityQueue(inz, i, j, prev_val);
}

void Unit::PrintWay()
{
	for (int ic = 0; ic < way_length; ic++)
		std::cout << std::setw(3) << way[ic].i << ' ' << way[ic].j << std::endl;
}

int Unit::distance(int start_i, int start_j, int finish_i, int finish_j)
{
	return (abs(start_i - finish_i) + abs(start_j - finish_j));
}

void Unit::InitPriorityQueue(refs& q)
{
	q = new priority_queue;
	q->next = NULL;
}

bool Unit::CheckPriorityQueue(refs q)
{
	return (q->next != NULL);
}

void Unit::AddPriorityQueue(refs q, int i, int j, int key, int prev_val)
{
	priority_queue* temp,* tz = q;
	while ((tz->next != NULL) && (tz->next->key <= key))
		tz = tz->next;
	temp = new priority_queue;
	temp->next = tz->next;
	temp->i = i;
	temp->j = j;
	temp->key = key;
	temp->prev_cell_value = prev_val;
	tz->next = temp;
}

void Unit::PopPriorityQueue(refs q, int& i, int& j, int &prev_val)
{
	// Оставляем проверку на пустоту на совести пользователя
	priority_queue* tz = q->next;
	i = tz->i;
	j = tz->j;
	prev_val = tz->prev_cell_value;
	q->next = tz->next;
	delete tz;
}