#pragma once
#include "Point.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

class NuageDePoints {
public:
    NuageDePoints(const std::string& pointsString, char texture='o');
    void supprimerPoint(int id);
    void deplacerPoint(int id, int x, int y);
    std::vector<Point> getPoints() const;
    std::vector<Point> creerPoints(const std::string& ligne, char texture);
private:
    std::vector<Point> points;
    char texture;
};