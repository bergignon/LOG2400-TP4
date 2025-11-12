#include "../header/NuageDePoints.h"

class NuageDePoints {
public:
    NuageDePoints(const std::string& pointsString, char texture) {
        texture = texture;
        points = creerPoints(pointsString, texture);
    }
    void supprimerPoint(int id) {
        for (size_t i = 0; i < points.size(); ++i) {
            if (points[i].id == id) {
                points.erase(points.begin() + i);
                return;
            }
        }
    }

    void deplacerPoint(int id, int x, int y) {
        for (Point& p : points) {
            if (p.id == id) {
                p.x = x;
                p.y = y;
                return; 
            }
        }
    }

    std::vector<Point> getPoints() const {
        return points;
    }

    std::vector<Point> creerPoints(const std::string& ligne, char texture='o') {
        std::vector<Point> points;
        // On crée un flux de lecture (istringstream) à partir de la chaîne ligne.
        std::istringstream iss(ligne);
        std::string token;
        int id = 0;
        // On lit chaque point de la ligne (séparé par des espaces).
        while (iss >> token) {
            // On vérifie que le point est entre parenthèses
            if (token.size() >= 3 && token.front() == '(' && token.back() == ')') {
                // On enlève les parenthèses au début et à la fin.
                token = token.substr(1, token.size() - 2);
                // On remplace la virgule par un espace.
                replace(token.begin(), token.end(), ',', ' ');
                // On crée un flux de lecture pour chaque point
                std::istringstream pair(token);
                int x, y;
                // On ajoute un point {x, y} au vecteur de points.
                if (pair >> x >> y) {
                    points.push_back(Point(x, y, id++, texture));
                }
            }
        }
        return points;
    }

private:
    std::vector<Point> points;
    char texture;
};