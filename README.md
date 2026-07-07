# SVG Shape Designer 🎨

A command-line C++ application that reads text files containing geometric shape specifications and renders them into **Scalable Vector Graphics (SVG)** files. 

This project heavily utilizes **Object-Oriented Programming (OOP)** principles, applying inheritance and polymorphism to dynamically manage, store, and draw different types of geometric shapes.

---

## 🚀 Features

* **Multiple Geometries Supported:** Renders Lines, Circles, Rectangles, Triangles, Rhombuses, and Stars.
* **Custom Styling:** Full control over RGB color codes, stroke widths, and fill properties (solid colors or transparent).
* **Dynamic Memory Management:** Utilizes abstract base classes (`Shape`, `FilledShape`) and pointers to process shapes dynamically at runtime.
* **Native SVG Generation:** Outputs standard `.svg` files that can be viewed in any modern web browser or edited in vector graphics software (like Inkscape or Adobe Illustrator).

## 📁 Project Structure

* `designer-main.cpp`: The application's entry point. Handles user I/O in the terminal and exception management.
* `designer.h` / `designer.cpp`: Defines the `Designer` class, responsible for managing the canvas dimensions, holding the collection of shapes (`std::vector<pShape>`), parsing the input file, and writing the SVG output.
* `shape.h` / `shape.cpp`: Contains the core OOP shape hierarchy:
  * `Shape`: Abstract base class handling common stroke attributes.
  * `FilledShape`: Inherits from `Shape`, adding fill logic.
  * **Derived Classes:** `Line`, `Circle`, `Rectangle`, `Triangle`, `Rhombus`, `Star`.
* `brasil.txt`: A sample input file containing the exact coordinates and shapes to draw the Brazilian flag.
* `Designer.cbp` / `.depend` / `.layout`: Code::Blocks IDE project files.

## 🛠️ Getting Started

You can compile and run this project using a standard terminal or the Code::Blocks IDE. A compiler that supports **C++11** or higher is required.

### Compiling via Terminal (GCC/G++)
Navigate to the project directory and compile the source files:

```bash
# Compile the code
g++ -Wall -std=c++11 designer-main.cpp designer.cpp shape.cpp -o designer

# Run the executable
./designer       # On Linux/macOS
.\designer.exe   # On Windows
