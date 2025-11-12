#include "../header/Surface.h"

void tracerLigne(std::vector<std::vector<char>> &grille, int x0, int y0, int x1, int y1)
{
    // Distance verticale
    int lignes = abs(y1 - y0);
    // Si la ligne est horizontale
    if (lignes == 0)
    {
        // On prend distance horizontale
        lignes = abs(x1 - x0);
        for (int i = 0; i <= lignes; ++i)
        {
            // On trace chaque point de la ligne, de gauche à droite ou de droite à gauche selon la direction.
            int x = (x0 < x1) ? x0 + i : x0 - i;
            if (y1 >= 0 && y1 < HAUTEUR && x >= 0 && x < LARGEUR)
                grille[y1][x] = '/';
        }
    }
    else
    {
        // Si la ligne est verticale ou diagonale
        for (int i = 0; i <= lignes; ++i)
        {
            double t = (double)i / lignes;
            // On fait une interpolation lineaire
            int x = round(x0 + t * (x1 - x0));
            int y = round(y0 + t * (y1 - y0));
            if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                grille[y][x] = '/';
        }
    }
}

class Surface
{
public:
    Surface(std::shared_ptr<SurfaceStrategy> sStrategy,
            std::shared_ptr<AffichageStrategy> aStrategy,
            int largeur = LARGEUR, int hauteur = HAUTEUR)
        : surfaceStrategy(sStrategy), affichageStrategy(aStrategy)
    {
        grille.resize(HAUTEUR, std::vector<char>(LARGEUR, ' '));
    }

    void construire(const std::vector<Point> &points)
    {
        for (auto &ligne : grille)
            std::fill(ligne.begin(), ligne.end(), ' ');
        if (surfaceStrategy)
            surfaceStrategy->construire(points, grille, LARGEUR, HAUTEUR);
    }

    void afficher()
    {
        if (affichageStrategy)
            affichageStrategy->afficher(grille);
    }

    void setSurfaceStrategy(std::shared_ptr<SurfaceStrategy> s) { surfaceStrategy = s; }
    void setAffichageStrategy(std::shared_ptr<AffichageStrategy> a) { affichageStrategy = a; }

private:
    std::vector<std::vector<char>> grille;
    std::shared_ptr<SurfaceStrategy> surfaceStrategy;
    std::shared_ptr<AffichageStrategy> affichageStrategy;
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
                    int largeur, int hauteur) override
    {
        if (points.size() < 2)
            return;

        std::vector<Point> sorted = points;
        std::sort(sorted.begin(), sorted.end(), [](const Point &a, const Point &b)
                  { return a.id < b.id; });

        for (size_t i = 0; i < sorted.size() - 1; ++i)
            tracerLigne(grille, sorted[i].x, sorted[i].y, sorted[i + 1].x, sorted[i + 1].y);
        tracerLigne(grille, sorted.back().x, sorted.back().y, sorted.front().x, sorted.front().y);
    }
};

class SurfaceDistance : public SurfaceStrategy
{
    double distance(const Point &a, const Point &b)
    {
        return std::sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    }

public:
    void construire(const std::vector<Point> &points,
                    std::vector<std::vector<char>> &grille,
                    int largeur, int hauteur) override
    {
        if (points.size() < 2)
            return;

        std::vector<bool> visite(points.size(), false);
        int courant = 0;
        visite[0] = true;
        int visites = 1;

        while (visites < points.size())
        {
            double minDist = std::numeric_limits<double>::max();
            int suivant = -1;
            for (size_t i = 0; i < points.size(); ++i)
            {
                if (!visite[i] && distance(points[courant], points[i]) < minDist)
                {
                    minDist = distance(points[courant], points[i]);
                    suivant = i;
                }
            }
            if (suivant != -1)
            {
                tracerLigne(grille, points[courant].x, points[courant].y, points[suivant].x, points[suivant].y);
                visite[suivant] = true;
                courant = suivant;
                ++visites;
            }
        }
        tracerLigne(grille, points[courant].x, points[courant].y, points[0].x, points[0].y);
    }
};

class AffichageStrategy
{
public:
    virtual void afficher(const std::vector<std::vector<char>> &grille) = 0;
    virtual ~AffichageStrategy() = default;
};

class AffichageTexture : public AffichageStrategy
{
public:
    void afficher(const std::vector<std::vector<char>> &grille) override
    {
        for (int y = grille.size() - 1; y >= 0; --y)
        {
            for (int x = 0; x < grille[0].size(); ++x)
                std::cout << grille[y][x];
            std::cout << "\n";
        }
    }
};

class AffichageID : public AffichageStrategy
{
public:
    void afficher(const std::vector<std::vector<char>> &grille) override
    {
        for (int y = grille.size() - 1; y >= 0; --y)
        {
            for (int x = 0; x < grille[0].size(); ++x)
            {
                char c = grille[y][x];
                if (c == ' ')
                    std::cout << ' ';
                else
                    std::cout << (c % 10 + '0'); 
            }
            std::cout << "\n";
        }
    }
};
