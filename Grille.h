#ifndef DEF_GRILLE_MEJ
#define DEF_GRILLE_MEJ


#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

struct Grille : public sf::Drawable
{
	int width, height;
	std::vector<bool> checked;
	mutable std::vector<bool> result;

	Grille(int w = 5, int h = 5) : width(w), height(h), checked(w*h, false), result(w*h, false) {}
	~Grille(){}


	friend std::ostream& operator<<(std::ostream& os, const Grille& Grille);

	/* Contrats : */
	// Invariant 1 : checked.size() == result.size() == width*height
	// Invariant 2 : Pour tout i : 0 < i < width*height, result[i] correspond au XOR des checked alentours si il faut représenter la grille ou la résoudre

	private:
	bool getChecked(int x, int y) const; //Accès type matriciel. Retourne false si en dehors des limites
	bool getResult(int x, int y) const; //Accès type matriciel. Retourne false si en dehors des limites
	bool checkDimensions() const;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	public:
	void synchroniserResult() const;


	//Résolution
	public:
	void computeLine(int j);
	void computeRange(int j, int n);
};

#endif
