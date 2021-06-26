#include <vector>

using namespace std;

int main()
{
	cout << "Heap.\n";
	Heap h({4,3,1,7,5});
	h.print();

	h.pop();
	h.print();

	h.push(8);
	h.print();

	h.push(1);
	h.print();

	h.push(9);
	h.print();

	h.pop();
	h.print();
	return 0;
}
