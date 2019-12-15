#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <iomanip>

#define DEBUG

using namespace std;

static int VILLAGES, START, FINISH, TIME = 0;



struct Path
{
	struct Village* start;
	struct Village* finish;
	int cost;
};

struct Village
{
	int tourist_index;
	int visit_time;
	int label;
	vector<Path*>* paths;

	Village()
	{
		this->paths = new vector<Path*>();
	}

	Path* getPathToVillage(Village* destination)
	{
		vector<Path*>::iterator it = this->paths->begin();
		Path* reti = new Path();
		while (it != this->paths->end())
		{
			if ((*it)->finish->label == destination->label)
			{
				delete reti;
				reti = *it;
				break;
			}
			it++;
		}
		return reti;
	}
};

int main(int argc, char* argv[])
{
	int reti = EXIT_SUCCESS;



	//Load first line of input
	cin >> VILLAGES >> START >> FINISH >> TIME;
#ifdef DEBUG
	cout << "V: " << VILLAGES << "; S: " << START << "; F: " << FINISH << "; T: " << TIME << endl;
	cout << "--- Loading tourist indexes ---" << endl;
#endif // DEBUG
	Village** villages = new Village*[VILLAGES];

	//Load tourist index
	for (int label = 0; label < VILLAGES; label++)
	{
		villages[label] = new Village();
		villages[label]->label = label;
		cin >> villages[label]->tourist_index;
#ifdef DEBUG
		cout << "\t [" << setw(to_string(VILLAGES).length()) << label << "]" << ": " << villages[label]->tourist_index << endl;
#endif // DEBUG
	}

	//Load visit time
#ifdef DEBUG
	cout << "--- Loading visit times ---" << endl;
#endif // DEBUG

	for (int label = 0; label < VILLAGES; label++)
	{
		cin >> villages[label]->visit_time;
#ifdef DEBUG
		cout << "\t [" << setw(to_string(VILLAGES).length()) << label << "] : " << villages[label]->visit_time << endl;
#endif // DEBUG

	}

	//Load paths
#ifdef DEBUG
	cout << "--- Loading paths --- " << endl;
#endif // DEBUG

	for (int i = 0; i < VILLAGES - 1; i++)
	{
		int start, finish, cost;
		cin >> start >> finish >> cost;
		Path* p = new Path();
		p->start = villages[start];
		p->finish = villages[finish];
		p->cost = cost;
		villages[start]->paths->push_back(p);

		Path* reverse = new Path();
		reverse->start = villages[finish];
		reverse->finish = villages[start];
		reverse->cost = cost;
		villages[finish]->paths->push_back(reverse);

#ifdef DEBUG
		cout << "\t[" << setw(to_string(VILLAGES).length()) << p->start->label << "] <--> [" << setw(to_string(VILLAGES).length()) << p->finish->label << "] @ " << p->cost << endl;
#endif // DEBUG
	}

	//Find shortest path between start and finish
#ifdef DEBUG
	cout << "--- Finding shortest path between [" << setw(to_string(VILLAGES).length()) << START << "] and [" << setw(to_string(VILLAGES).length()) << FINISH << "] ---" << endl;
#endif // DEBUG

	bool found = false;

	vector<Village*>* situation = new vector<Village*>();
	situation->push_back(villages[START]);

	vector<Village*>* final_path = 0;
	queue<vector<Village*>*>* tree_queue = new queue<vector<Village*>*>();
	tree_queue->push(situation);
	while (found == false && tree_queue->empty() == false)
	{
		vector<Village*>* actual = tree_queue->front();
		if (actual->back()->label == villages[FINISH]->label)
		{
			final_path = actual;
#ifdef DEBUG
			cout << "\tFINISH!" << endl;
#endif // DEBUG
			found = true;
		}
		else
		{
#ifdef DEBUG
			cout << "\t checking: [" << setw(to_string(VILLAGES).length()) << actual->back()->label << "]; remaining: " << tree_queue->size() << endl;
#endif // DEBUG

			vector<Path*>::iterator it = actual->back()->paths->begin();
			while (it != actual->back()->paths->end())
			{
				if (find(actual->begin(), actual->end(), (*it)->finish) == actual->end())
				{
					vector<Village*>* next_situation = new vector<Village*>(*actual);
					next_situation->push_back((*it)->finish);
					tree_queue->push(next_situation);
				}
				it++;
			}
			
		}
		tree_queue->pop();
	}
#ifdef DEBUG
	vector<Village*>::iterator it = final_path->begin();
	cout << "\t --- Found path ----" << endl;
	cout << "\t";
	while (it != final_path->end())
	{
		cout << "[" << setw(to_string(VILLAGES).length()) << (*it)->label << "] ";
		it++;
	}
	cout << endl;
	cout << "\t Time needed: ";
	int time = 0;
	for (unsigned int i = 0; i < final_path->size(); i++)
	{
		time += final_path->at(i)->visit_time;
		if (i < final_path->size() - 1)
		{
			time += final_path->at(i)->getPathToVillage(final_path->at(i + 1))->cost;
		}
	}
	cout << time << endl;
	cout << "\t Maximal time: " << TIME << endl;
	int tourist_points = 0;
	for (unsigned int i = 0; i < final_path->size(); i++)
	{
		tourist_points += final_path->at(i)->tourist_index;
	}
	cout << "\t Tourist points: " << tourist_points << endl;

#endif // DEBUG

	return reti;
}