#pragma once
#include "NuageDePoints.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <cmath>

constexpr int LARGEUR = 30;
constexpr int HAUTEUR = 20;

void tracerLigne(std::vector<std::vector<char>> &grille, int x0, int y0, int x1, int y1);

class AffichageStrategy
{
public:
    virtual void afficher(const std::vector<std::vector<char>> &grille) = 0;
    virtual ~AffichageStrategy() = default;
};

class AffichageTexture : public AffichageStrategy
{
public:
    void afficher(const std::vector<std::vector<char>> &grille) override;
};

class AffichageID : public AffichageStrategy
{
public:
    void afficher(const std::vector<std::vector<char>> &grille) override;
};

class SurfaceStrategy
{
public:
    virtual void construire(const std::vector<Point> &points,
                            std::vector<std::vector<char>> &grille,
                            int largeur, int hauteur) = 0;
    virtual ~SurfaceStrategy() = default;
};

class SurfaceParID : public SurfaceStrategy
{
public:
    void construire(const std::vector<Point> &points,
                    std::vector<std::vector<char>> &grille,
                    int largeur, int hauteur) override;
};

class SurfaceDistance : public SurfaceStrategy
{
public:
    void construire(const std::vector<Point> &points,
                    std::vector<std::vector<char>> &grille,
                    int largeur, int hauteur) override;
};

class Surface
{
public:
    Surface(std::shared_ptr<SurfaceStrategy> sStrategy,
            std::shared_ptr<AffichageStrategy> aStrategy,
            int largeur = LARGEUR, int hauteur = HAUTEUR);

    void construire(const std::vector<Point> &points);
    void afficher();

    void setSurfaceStrategy(std::shared_ptr<SurfaceStrategy> s);
    void setAffichageStrategy(std::shared_ptr<AffichageStrategy> a);

private:
    std::vector<std::vector<char>> grille;
    std::shared_ptr<SurfaceStrategy> surfaceStrategy;
    std::shared_ptr<AffichageStrategy> affichageStrategy;
};