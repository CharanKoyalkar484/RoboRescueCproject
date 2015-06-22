#include <iostream>
#include <stdexcept>

#include <stdio.h>
#include <iostream>

#include "lines.h"
#include "algorithms.h"

int main(int argc, char *argv[]) {
	
	int maxX = 0;
	int maxY = 0;
	int minX = 0;
	int minY = 0;
	// Initialize lines vector with "random" numbers
    std::vector<Lines<int> > lines;
    Lines<int> line1(-533445, 535435, -23424, 312312);
    Lines<int> line2(343242, 223, 0, -42);
    Lines<int> line3(211, 25454, 44674, 1665432);
    Lines<int> line4(-142421, 4256, 98765432, 7653);
    lines.push_back(line1);
    lines.push_back(line2);
    lines.push_back(line3);
    lines.push_back(line4);
	
	// Normalize lines between -1 and 1 floats
	const std::vector<Lines<float> > normalizedLines = Algorithms::normalizeLines(lines, minX, maxX, minY, maxY);

    for(std::vector<Lines<float> >::const_iterator it = normalizedLines.begin(); it != normalizedLines.end(); ++it) {
        if (it->x1 > 1 || it->x1 < -1) {
			std::cout << "X1 value was out of bounds";
			return -1;
		} else if (it->x2 > 1 || it->x2 < -1) {
			std::cout << "X2 value was out of bounds";
			return -1;
		} else if (it->y1 > 1 || it->y1 < -1) {
			std::cout << "Y1 value was out of bounds";
			return -1;
		} else if (it->y2 > 1 || it->y2 < -1) {
			std::cout << "Y2 value was out of bounds";
			return -1;
		}
    }

    std::cout << "SUCCESSSSS!!";
    return 0;
}