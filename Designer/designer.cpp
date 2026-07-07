#include <iostream>
#include <fstream>
#include <string>
#include "designer.h"
#include <limits>

using namespace std;

/// Construtor especifico
Designer::Designer(int Width, int Height):
  width(Width), height(Height), VS()
{
  if (width<=0 || height<=0)
  {
    width = height = 0;
  }
}

/// Construtor por copia
/* ACRESCENTAR */
Designer::Designer(const Designer& D): width(D.width), height(D.height), VS(D.getNumShapes(), nullptr)
{
    for(int i = 0; i< static_cast<int>(this->getNumShapes()); ++i)
        if (D.VS.at(i) != nullptr) VS.at(i) = D.VS.at(i)->clone();
}
/// Construtor por movimento
/* ACRESCENTAR */
Designer::Designer(Designer&& D): Designer()
{
  swap(this->width,D.width);
  swap(this->height, D.height);
  swap(this->VS,D.VS);
}

/// Atribuicao por copia
Designer& Designer::operator=(const Designer& D)
{
  // Teste de autoatribuicao
  if (this==&D) return *this;

  /* ACRESCENTAR */
  this->clear();
  VS.resize(D.getNumShapes(), nullptr);
  for(int i = 0; i < static_cast<int>(this->getNumShapes()); ++i)
      if(D.VS.at(i) != nullptr) VS.at(i) = D.VS.at(i)->clone();

  this->width = D.width;
  this->height = D.height;

  return *this;
}

/// Atribuicao por movimento
Designer& Designer::operator=(Designer&& D)
{
  // Teste de autoatribuicao
  if (this==&D) return *this;

  /* ACRESCENTAR */
  this->clear();
  swap(this->width, D.width);
  swap(this->height, D.height);
  this->VS.swap(D.VS);

  return *this;
}

/// Limpa o desenho
void Designer::clear()
{
  width = height = 0;
  /* ACRESCENTAR */
  for(auto shape : VS) delete shape;
  VS.clear();
}

/// Inclusao de nova forma no desenho
/* ACRESCENTAR */
void Designer::include(const Shape& S)
{
    VS.push_back(S.clone());
}

/// Leitura de arquivo com as formas
/// Leitura de arquivo com as formas
void Designer::read(const string& fileName)
{
  ifstream arq(fileName);
  if (!arq.is_open())
  {
    string msg = "could not open file " + fileName;
    throw ios_base::failure(msg);
  }

  // Leh o cabecalho
  string texto;
  int W, H;
  arq >> texto >> W >> H;
  if (!arq.good() || texto != "DESIGNER" || W <= 0 || H <= 0)
    throw ios_base::failure("invalid file");

  // Cria um novo Designer temporario, inicialmente vazio (sem formas)
  Designer prov(W, H);

  // Laco de leitura das diversas formas do desenho.
  // Permanece ateh o fim do arquivo.
  bool arquivo_acabou = false;
  char tipo_forma;

  do
  {
    // Leh o tipo de forma (char)
    arq >> tipo_forma;
    // Testa se acabou o arquivo
    if (!arq.good())
    {
      arquivo_acabou = true;
      continue;
    }
    tipo_forma = toupper(tipo_forma);

    // Criamos um ponteiro da classe abstrata base
    Shape* nova_forma = nullptr;

    switch(tipo_forma)
    {
        case '-': nova_forma = new Line();break;
        case 'C': nova_forma = new Circle();break;
        case 'S': nova_forma = new Star();break;
        case 'R': nova_forma = new Rectangle();break;
        case 'L': nova_forma = new Rhombus();break;
        case 'T': nova_forma = new Triangle();break;
        default:
            {
            // Se o caractere nao for reconhecido, ignora o resto da linha
            arq.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
            }
    }

    // Se a nova forma foi alocada com sucesso:
    if (nova_forma != nullptr)
    {
        nova_forma->read(arq);     // Leh os dados especificos da forma do arquivo
        prov.include(*nova_forma); // Acrescenta a forma clonada no Designer temporario

        delete nova_forma;         // Libera o ponteiro temporario para evitar memory leak
    }

  }
  while(!arquivo_acabou);

  // Testa o numero de formas lidas
  if (prov.getNumShapes() == 0) throw ios_base::failure("empty file");

  // Faz *this assumir o conteudo de prov usando a semântica de movimento
  *this = move(prov);
}

/// Salvamento do desenho em formato SVG
void Designer::save(const string& fileName) const
{
  // Nao exporta se o desenho for vazio
  if (getNumShapes()==0 || width<=0 || height<=0) throw logic_error("empty designer");

  // Abre o arquivo SVG para escrita
  ofstream arq(fileName);
  if (!arq.is_open())
  {
    string msg = "could not open file "+fileName;
    throw ios_base::failure(msg);
  }

  // Escreve o cabecalho inicial
  arq << "<svg"
      << " width=" << '"' << width << '"'
      << " height=" << '"' << height << '"'
      << " xmlns=" << '"' << "http://www.w3.org/2000/svg"  << '"'
      << ">\n";

  // Salva as formas
  for (auto S : VS)
  {
    S->save(arq);
    arq << endl;
  }

  // Escreve o rodapeh final
  arq << "</svg>" << endl;
}
