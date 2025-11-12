#pragma once

struct Point {
    Point(int x, int y, int id, char texture='o');
    int x, y, id;
    char texture;
}; 

class PointDecorator {
public:
    PointDecorator(Point& p, char texture = ' ', char previousTexture = ' ');
    void appliquerTexture();
    void retirerTexture();
    void supprimerTexture();
private:
    Point& point;        
    char texture;   
    char previousTexture;      
};