#include <cmath>
#include "shape.h"

#define MEU_PI 3.14159265358979323846

using namespace std;

///
/// LEITURA DE FORMAS DO ARQUIVO
///

/// Faz os passos comuns para ler qualquer forma.
/// Leh cor e largura do contorno.
void Shape::read(istream& X)
{
  X >> r >> g >> b >> width;
  if (!X.good() || r<0 || r>255 || g<0 || g>255 || b<0 || b>255 || width<=0)
    throw ios_base::failure("invalid shape parameters");
}

/// Faz os passos comuns para ler qualquer forma preenchivel.
/// Leh cor e largura do contorno (usando Shape::read) e depois se eh preenchida.
void FilledShape::read(istream& X)
{
  Shape::read(X); // Gera excecao se houver erro
  int Filled;
  X >> Filled;
  if (!X.good())
    throw ios_base::failure("invalid filled shape parameters");
  filled = (Filled != 0);
}

/// Leh uma linha de uma stream.
/// Leh cor e largura do contorno (usando Shape::read) e depois os 2 pontos.
/* ACRESCENTAR */
void Line::read(istream& X)
{
    Shape::read(X);
    X >> x1 >> y1 >> x2 >> y2;
    if(!X.good()) throw ios_base::failure("invalid line parameters");
    if(x1<0 || y1<0 || x2<0 || y2<0) throw ios_base::failure("negative coordinates not allowed for Line");
}
/// Leh um circulo de uma stream.
/// Leh cor, largura do contorno e se eh preenchida (usando FilledShape::read)
/// e depois o centro e o raio.
/* ACRESCENTAR */
void Circle::read(istream& X)
{
    FilledShape::read(X);
    X >> xc >> yc >> raioC;
    if(!X.good()) throw ios_base::failure("invalid circle parameters");
    if(xc<0 || yc<0 || raioC<0) throw ios_base::failure("negative coordinates or radius not allowed for Circle");
}
/// Leh um retangulo de uma stream.
/// Leh cor, largura do contorno e se eh preenchida (usando FilledShape::read)
/// e depois os limites.
/* ACRESCENTAR */
void Rectangle::read(istream& X)
{
    FilledShape::read(X);
    X >> xmin >> xmax >> ymin >> ymax;
    if(!X.good()) throw ios_base::failure("invalid rectangle parameters");
    if(xmin<0 || xmax<0 || ymin<0 || ymax<0) throw ios_base::failure("negative coordinates not allowed for Rectangle");
    if(xmin>xmax) swap(xmin, xmax);
    if(ymin>ymax) swap(ymin, ymax);
}
/// Leh um triangulo de uma stream.
/// Leh cor, largura do contorno e se eh preenchida (usando FilledShape::read)
/// e depois os 3 pontos.
/* ACRESCENTAR */
void Triangle::read(istream& X)
{
    FilledShape::read(X);
    X >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    if(!X.good()) throw ios_base::failure("invalid triangle parameters");
    if(x1<0 || y1<0 || x2<0 || y2<0 || x3<0 || y3<0) throw ios_base::failure("negative coordinates not allowed for Triangle");
}
/// Leh um losango de uma stream.
/// Leh cor, largura do contorno e se eh preenchida (usando FilledShape::read)
/// e depois os limites.
/* ACRESCENTAR */
void Rhombus::read(istream& X)
{
    FilledShape::read(X);
    X >> xmin >> xmax >> ymin >> ymax;
    if(!X.good()) throw ios_base::failure("invalid rhombus parameters");
    if(xmin<0 || xmax<0 || ymin<0 || ymax <0) throw ios_base::failure("negative coordinates not allowed for Rhombus");
    if(xmin > xmax) swap(xmin, xmax);
    if(ymin > ymax) swap(ymin, ymax);
}
/// Leh uma estrela de uma stream.
/// Leh cor, largura do contorno e se eh preenchida (usando FilledShape::read)
/// e depois o centro e o raio.
/* ACRESCENTAR */
void Star::read(istream& X)
{
    FilledShape::read(X);
    X >> xc >> yc >> raioS;
    if(!X.good()) throw ios_base::failure("invalid star parameters");
    if(xc<0 || yc<0 || raioS<0) throw ios_base::failure("negative coordinates or radius not allowed for Star");
}

///
/// SALVAMENTO DAS FIGURAS
///

/// Faz os passos comuns para salvar qualquer forma.
/// Salva cor e largura da linha.
void Shape::save(ostream& X) const
{
  X << " stroke=" << '"' << "rgb("
    << r << ',' << g << ',' << b << ')' << '"';
  X << " stroke-width=" << '"' << width << '"';
}
/// Faz os passos comuns para salvar qualquer forma preenchivel.
/// Usa Shape::save e depois salva cor do preenchimento.
void FilledShape::save(ostream& X) const
{
  Shape::save(X);
  if (filled)
  {
    X << " fill=" << '"' << "rgb("
      << r << ',' << g << ',' << b << ')' << '"';
  }
  else
  {
    X << " fill=" << '"' << "transparent" << '"';
  }
}
/// Salva uma linha.
/// Salva o inicio "<line" e os parametros do elemento;
/// depois, salva os parametros de estilo, usando Shape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Line::save(ostream& X) const
{
    X << "<line x1=" << '"' << x1 << '"' << " y1=" <<  '"' << y1 << '"' << " x2=" << '"' << x2 << '"' << " y2=" << '"' << y2 << '"';
    Shape::save(X);
    X << " />";
}
/// Salva um circulo.
/// Salva o inicio "<circle" e os parametros do elemento;
/// depois, salva os parametros de estilo, usando FilledShape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Circle::save(ostream& X) const
{
    X << "<circle r=" << '"' << raioC << '"' << " cx=" << '"' << xc << '"' << " cy=" << '"' << yc << '"';
    FilledShape::save(X);
    X << " />";
}
/// Salva um retangulo
/// Salva o inicio "<rect" e os parametros do elemento;
/// depois, salva os parametros de estilo, usando FilledShape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Rectangle::save(ostream& X) const
{
    int w = xmax - xmin + 1;
    int h = ymax - ymin + 1;
    X << "<rect width=" << '"' << w << '"' << " height=" << '"' << h << '"' << " x=" << '"' << xmin << '"' << " y=" << '"' << ymin << '"';
    FilledShape::save(X);
    X << " />";
}
/// Salva um triangulo
/// Salva o inicio "<polygon" e os parametros (3 pontos) do elemento;
/// depois, salva os parametros de estilo, usando FilledShape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Triangle::save(ostream& X) const
{
    X << "<polygon points=" << '"' << x1 << "," << y1 << " " << x2 << "," << y2 << " " << x3 << "," << y3 << '"';
    FilledShape::save(X);
    X << " />";
}
/// Salva um losango
/// Salva o inicio "<polygon" e os parametros (4 pontos) do elemento;
/// depois, salva os parametros de estilo, usando FilledShape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Rhombus::save(ostream& X) const
{
    int xmed = (xmin + xmax)/2;
    int ymed = (ymin + ymax)/2;
    X << "<polygon points=" << '"' << xmin << "," << ymed << " " << xmed << "," << ymin << " " << xmax << "," << ymed << " " << xmed << "," << ymax << '"';
    FilledShape::save(X);
    X << " />";
}
/// Salva uma estrela
/// Salva o inicio "<polygon" e os parametros (10 pontos) do elemento;
/// depois, salva os parametros de estilo, usando FilledShape::save;
/// depois, salva o final "/>" do elemento.
/* ACRESCENTAR */
void Star::save(ostream& X) const
{
    X << "<polygon points=" << '"';
    for(int i = 0; i<10; ++i)
    {
        double thetaP = MEU_PI*((i/5.0) + (1.0/2.0));
        double rP = (i%2 == 0)? raioS :(raioS/2.5);
        int xP = static_cast <int>(xc + (rP * cos(thetaP)));
        int yP = static_cast<int>(yc - (rP * sin(thetaP)));

        X << xP << "," << yP;
        if (i<9) X << " ";
    }

    X << '"';
    FilledShape::save(X);
    X << " />";
}

