#include <string>
#include "board.h"
using namespace std;


void Board::display() const{
    // TOP SECTION

    // MIDDLE SECTION
    for (int i = 0; i < 3; i++) {
    cout << "    | 6|-- 9--| 7|      10       | 8|--10--| 9|      5         |10|--11--|11" << endl;
    cout << "    /            \\              /            \\               /             \\" << endl;
    cout << "   12      3      13           14       4      15            16       5       17" << endl;
    cout << "  /       LAB      \\          /     NETFLIX     \\          /      STUDY       \\" << endl;
    cout << "|12|       4       |13|--18--|14|       0        |15|--19--|16|      10         |17|" << endl;
    cout << " \\                /           \\                /           \\                 /" << endl;
    }

    
}