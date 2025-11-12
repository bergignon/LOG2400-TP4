#include "../header/point.h"

struct Point {
    Point(int x, int y, int id, char texture) : x(x), y(y), id(id), texture(texture) {}
    int x, y, id;
    char texture;
};

class PointDecorator {
public:
    PointDecorator(Point& p, char texture, char previousTexture) : point(p), texture(texture), previousTexture(previousTexture) {}

    void appliquerTexture() {
        previousTexture = point.texture;
        point.texture = texture;
    }

    void retirerTexture() {
        point.texture = previousTexture;
    }

    void supprimerTexture() {
        point.texture = ' ';
    }

private:
    Point& point;        
    char texture;   
    char previousTexture;      
};