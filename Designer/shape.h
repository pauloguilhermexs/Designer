#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <iostream>

class Shape;
typedef Shape* pShape;

/// Classe base de todas as formas
class Shape
{
public:
  // Construtor (especifico e default)
  Shape(int R=0, int G=0, int B=0, int W=1):
    r(R),
    g(G),
    b(B),
    width(W)
  {}

  /* ACRESCENTAR */
  virtual ~Shape(){}
  virtual pShape clone() const = 0;
  // Leh uma forma generica de uma stream.
  // Leh a cor da forma e a largura do contorno.
  virtual void read(std::istream& X);

  // Salva a cor da forma e a largura do contorno em formato SVG
  virtual void save(std::ostream& X) const;

protected:
  // A cor da forma.
  // Precisa ser consultado pela FilledShape (por isso eh protegido).
  int r,g,b;

private:
  // Largura do contorno da forma
  int width=1;
};

/// Classe base de todas as formas que podem ser preenchidas ou nao
class FilledShape: public Shape
{
public:
  // Construtor (especifico e default)
  FilledShape(int R=0, int G=0, int B=0, int W=1, bool F=true):
    Shape(R,G,B,W),
    filled(F)
  {}

  // Leh uma forma preenchivel generica de uma stream.
  // Leh cor e largura (usando Shape::read) e depois se eh preenchida ou nao.
  virtual void read(std::istream& X);

  // Salva a forma preenchivel em formato SVG.
  // Salva a cor e largura (usando Shape::save) e o depois se eh preenchida ou nao.
  virtual void save(std::ostream& X) const;

private:
  // forma preenchida ou nao
  bool filled=false;
};

/// Classe que representa linhas
/* ACRESCENTAR */
class Line: public Shape
{
private:
    int x1, y1, x2, y2;
public:
    Line(int R=0, int G=0, int B=0, int W=1, int X1=0, int Y1=0, int X2=0, int Y2=0): Shape(R,G,B,W), x1(X1), y1(Y1), x2(X2), y2(Y2) {}
    virtual pShape clone() const override{return new Line(*this);}
    virtual void read(std::istream& X) override;
    virtual void save(std::ostream& X) const override;
};
/// Classe que representa circulos
/* ACRESCENTAR */
class Circle: public FilledShape
{
private:
    int xc, yc, raioC;
public:
    Circle(int R=0, int G=0, int B=0, int W=1, bool F=true, int XC=0, int YC=0, int Raio=0): FilledShape(R,G,B,W,F), xc(XC), yc(YC), raioC(Raio) {}
    virtual pShape clone() const override {return new Circle(*this);}
    virtual void read(std::istream& X) override;
    virtual void save(std::ostream& X) const override;
};
/// Classe que representa retangulos
/* ACRESCENTAR */
class Rectangle: public FilledShape
{
private:
    int xmin, xmax, ymin, ymax;
public:
    Rectangle(int R=0, int G=0, int B=0, int W=1, bool F=true, int X_min=0, int X_max=0, int Y_min=0, int Y_max=0): FilledShape(R,G,B,W,F), xmin(X_min), xmax(X_max), ymin(Y_min), ymax(Y_max){}
    virtual pShape clone() const override {return new Rectangle(*this);}
    virtual void read(std::istream& X) override;
    virtual void save(std::ostream& X) const override;
};
/// Classe que representa triangulos
/* ACRESCENTAR */
class Triangle: public FilledShape
{
private:
    int x1, y1, x2, y2, x3, y3;
public:
    Triangle(int R=0, int G=0, int B=0, int W=1, bool F=true, int X1=0, int Y1=0, int X2=0, int Y2=0, int X3=0, int Y3=0): FilledShape(R,G,B,W,F), x1(X1), y1(Y1), x2(X2), y2(Y2), x3(X3), y3(Y3){}
    virtual pShape clone() const override {return new Triangle(*this);}
    virtual void read(std::istream& X) override;
    virtual void save(std::ostream& X) const override;
};

/// Classe que representa losangos
/* ACRESCENTAR */
class Rhombus: public FilledShape
{
private:
    int xmin, xmax, ymin, ymax;
public:
    Rhombus(int R=0, int G=0, int B=0, int W=1, bool F=true, int X_min=0, int X_max=0, int Y_min=0, int Y_max=0): FilledShape(R,G,B,W,F),xmin(X_min), xmax(X_max), ymin(Y_min), ymax(Y_max){}
    virtual pShape clone() const override {return new Rhombus(*this);}
    virtual void read(std::istream& X) override;
    virtual void save(std::ostream& X) const override;
};
/// Classe que representa estrelas
/* ACRESCENTAR */
class Star: public FilledShape
{
private:
    int xc, yc, raioS;
public:

    Star(int R=0, int G=0, int B=0, int W=1, bool F=true, int XC=0, int YC=0, int Raio=0): FilledShape(R,G,B,W,F),  xc(XC), yc(YC), raioS(Raio){}
    virtual pShape clone() const override {return new Star(*this);}
    virtual void read(std::istream& X) override;
    virtual void save(std::ostream& X) const override;
};


#endif // _SHAPE_H_
