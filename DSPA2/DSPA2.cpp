#include<iostream>
#include<sstream>
#include<string>
#include<queue>

using namespace std;

struct node {
	string name;
	node* next;
};
class list {
private:
	node * head;
public:
	list()
	{
		head = NULL;
	}
	void insertEnd(string textToInsert);
	void print();
	bool searchTerms(string textToSearch);
	void firstNode(string textToInsert);
	int getSize();
	int searchIndex(string textToSearch);
	string searchByIndex(int index);
};
int list::getSize() {
	int number = 0;
	node* temp = head;
	while (temp != NULL) {
		temp = temp->next;
		number++;
	}
	return number;
}
void list::firstNode(string textToInsert) {
	node *temp = new node;
	temp->name = textToInsert;
	temp->next = head;
	head = temp;
}
void list::insertEnd(string textToInsert) {//insert given text at the end of the document

	if (head == NULL) {
		this->firstNode(textToInsert);
	}
	else {
		node *temp = head;
		while (temp->next != NULL)//iterate to the last node in the list
		{
			temp = temp->next;
		}
		node *temp3 = new node;
		temp3->next = NULL;
		temp3->name = textToInsert;
		temp->next = temp3;
	}
}
void list::print() {//print the entire document, with line numbers
	node *temp = new node;
	temp = head;
	int counter = 1;
	while (temp != NULL) {
		cout << temp->name << endl;
		temp = temp->next;
	}
}
bool list::searchTerms(string textToSearch) {
	node* temp = head;
	int size = this->getSize();
	bool notFound = true;
	for (int i = 0; i < size; i++) {
		if (temp->name.find(textToSearch) < 1024) {
			notFound = false;
		}
		temp = temp->next;
	}

	if (notFound) {
		return false;
	}
	return true;
}
int list::searchIndex(string textToSearch) {
	node* temp = head;
	int size = this->getSize();
	int index = 0;
	for (int i = 0; i < size; i++) {
		if (temp->name.find(textToSearch) < 1024) {
			index = i;
			i = size;
		}
		temp = temp->next;
	}

	return index;
}
string list::searchByIndex(int index) {
	node* temp = head;
	int counter = 0;
	while (temp != NULL) {
		if (counter == index) {
			return temp->name;
		}
		temp = temp->next;
		counter++;
	}
	return "";
}

void printRanks(double* ranks, int dimension);
void insertEdge(double** graph, queue<string> in, queue<string> out, list unique, int numEdges);
void printGraph(double** graph, int dimension);
void division(double** graph, int dimension);
void multiplication(double** graph, int dimension, int score, double* ranks);
void firstMultiplication(double** graph, int dimension, double* ranks);
void finalPrint(double* ranks, list unique, int dimension);

void printRanks(double* ranks, int dimension) {
	for (int i = 0; i < dimension; i++){
		cout << i + 1 << ". " << ranks[i] << endl;
	}
}

void insertEdge(double** graph, queue<string> in, queue<string> out, list unique, int numEdges) {
	int inIndex = 0;//these two indexes will be obtained from the positions of the strings in unique
	int outIndex = 0;
	cout << endl;
	for (int i = 0; i < numEdges; i++) {
		inIndex = unique.searchIndex(in.front());
		outIndex = unique.searchIndex(out.front());
		cout <<"in " << in.front() << " out " << out.front() << endl;
		in.pop();
		out.pop();

		graph[inIndex][outIndex] = 1;
	}
	cout << endl;
}

void printGraph(double** graph, int dimension) {
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}

}

void division(double** graph, int dimension) {
	for (int i = 0; i < dimension; i++) {
		int count = 0;
		for (int j = 0; j < dimension; j++) {
			if (graph[j][i] == 1) {
				count++;
			}
		}
		for (int k = 0; k < dimension; k++) {
			graph[k][i] = graph[k][i] / count;
		}
	}
}

void multiplication(double** graph, int dimension, int score, double* ranks) {
	queue<double> temp;
	for (int i = 0; i < score; i++) {//power
		double sumRow = 0;
		for (int j = 0; j < dimension; j++) {//row
			for (int k = 0; k < dimension; k++) {//column
				sumRow += graph[j][k] * ranks[k];
			}
			temp.push(sumRow);
		}
		for (int j = 0; j < dimension; j++) {
			ranks[j] = temp.front();
			temp.pop();
		}
	}
}

void firstMultiplication(double** graph, int dimension, double* ranks) {
	for (int i = 0; i < dimension; i++) {
		double sumRow = 0;
		for (int j = 0; j < dimension; j++) {
			sumRow += graph[i][j];
		}
		sumRow /= dimension;

		ranks[i] = sumRow;//fixme
	}
}

void finalPrint(double* ranks, list unique, int dimension) {
	for (int i = 0; i < dimension; i++) {
		cout << i + 1<< ". " << unique.searchByIndex(i) << " " << ranks[i] << endl;
	}
}




int main() {
	int numEdges, inVert, outVert;
	int numScore = 0;
	list uniqueNames;
	queue<string> inQueue;
	queue<string> outQueue;

	string t;
	getline(cin, t);
	istringstream iss(t);
	string word;
	int counter = 0;
	while ((iss >> word) && (counter != 2)) {//passes the first line and gets the two numbers
		counter++;
		switch (counter) {
		case 1:
			numEdges = stoi(word);
			break;
		case 2:
			numScore = stoi(word);
			break;
		}
	}

	for (int i = 0; i < numEdges; i++) {//each time it passes a line 
		string t, in, out;
		getline(cin, t);
		istringstream iss(t);
		string word;
		int counter = 0;
		bool flag = false;
		while (iss >> word) {//each time it passes a word in a line
			counter++;
			if (!uniqueNames.searchTerms(word)) {
				uniqueNames.insertEnd(word);//this stores all of the unique names and its size indicates the dimension of the matrix
			}
			switch (counter) {
			case 1:
				out = word;
				outQueue.push(out);//this stores all of the out vertices
				break;
			case 2:
				in = word;
				inQueue.push(in);
				break;
			}
		}
	}

	const static int numDimension = uniqueNames.getSize();
	double** matrix = new double*[numDimension];//this is the adjacency matrix

	for (int i = 0; i < numDimension; i++) {//dynamic allocation
		matrix[i] = new double[numDimension];
	}

	for (int i = 0; i < numDimension; ++i) {//fill
		for (int j = 0; j < numDimension; ++j) {
			matrix[i][j] = 0;
		}
	}

	cout << endl;
	cout << "unique" << endl;
	cout << uniqueNames.searchByIndex(0) << endl;
	cout << uniqueNames.searchByIndex(1) << endl;
	cout << uniqueNames.searchByIndex(2) << endl;
	cout << uniqueNames.searchByIndex(3) << endl;
	cout << uniqueNames.searchByIndex(4) << endl;

	insertEdge(matrix, inQueue, outQueue, uniqueNames, numEdges);
	printGraph(matrix, numDimension);
	division(matrix, numDimension);
	cout << endl;
	printGraph(matrix, numDimension);

	double* ranks = NULL;
	ranks = new double[numDimension];//ranks stores the result after each cross product
	for (int i = 0; i < numDimension; ++i) {
		ranks[i] = 0;
	}

	firstMultiplication(matrix, numDimension, ranks);//cross products 1/size
	cout << endl;
	cout << "firstMulti" << endl;
	printRanks(ranks, numDimension);

	if (numScore > 1) {
		multiplication(matrix, numDimension, numScore - 2, ranks);
	}

	cout << endl;
	printRanks(ranks, numDimension);

	cout << endl;
	finalPrint(ranks, uniqueNames, numDimension);

	for (int i = 0; i < numDimension; ++i) {//deletion
		delete[] matrix[i];
	}
	delete[] matrix;//deletion

	cin >> t;
}