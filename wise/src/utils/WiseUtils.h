#ifndef __WISEUTILS_H__
#define __WISEUTILS_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <iterator>
#include <iomanip>
#include <string>
#include <vector>

#include <opencv.hpp>

//using namespace std;
//namespace WiseUtils {

//#define to_string( x ) dynamic_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()
//#define to_string_( x , prec) dynamic_cast< std::ostringstream & >( ( std::ostringstream() << std::setfill('0') << std::setw(prec) << x ) ).str()
#define to_string_( x , prec) static_cast< std::ostringstream & >( ( std::ostringstream() << std::setfill('0') << std::setw(prec) << x ) ).str()
#define RECT_IN_MAT(ROI, img) ( (ROI.area() > 0) && (ROI.br().y -1 < img.rows) && (ROI.br().x - 1 < img.cols) )

//Equivalences between common datatypes and bytes
typedef enum {
    WISE_BYTES_UINT8 = 1,
    WISE_BYTES_INT = 4, //single precision (32bit)
    WISE_BYTES_FLOAT = 4, //single precision (32bit)
    WISE_BYTES_DOUBLE = 8, //double precision (64bit)
} bytelength_type_t;

std::vector<std::string> split(const std::string& s, const std::string& delim, bool keep_empty);
cv::Mat mat2vec(cv::Mat mat);

// Returns the erf() of a value (not super precice, but ok)
double erf(double x);

// Returns the probability of x, given the distribution described by mu and sigma.
double pdf(double x, double mu, double sigma);

// Returns the probability of [-inf,x] of a gaussian distribution
double cdf(double x, double mu, double sigma);

template<typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    out << "[";
    std::size_t last = v.size() - 1;
    for(std::size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last)
            out << ", ";
    }
    out << "]";
    return out;
}

inline std::string print_vector(const std::vector<std::string> &v)
{
    using namespace std;
    ostringstream os;
    os << "[ ";
    vector<string>::const_iterator s;
    for (s = v.begin(); s != v.end(); ++s)
        os << *s << " ";
    os << "]";
    return os.str();
}

inline std::string print_vector(const std::vector<int> &v)
{
    using namespace std;
    ostringstream os;
    os << "[ ";
    vector<int>::const_iterator s;
    for (s = v.begin(); s != v.end(); ++s)
        os << *s << " ";
    os << "]";
    return os.str();
}

inline std::string get_time_filename(const char *st, const char *ext)
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%Y%m%d_%I%M%S",timeinfo);

    std::string str(st);
    str.append(buffer);
    str.append(ext);
    return str;
}

// Serialize a cv::Mat to a stringstream
void serialize(cv::Mat input, std::stringstream *output);
void Tokenize(std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ");

// Deserialize a Mat from a stringstream
cv::Mat deserialize(std::stringstream& input);

typedef std::map<char, unsigned int> SymbolCount;
typedef std::map<char, std::string> HuffmanCode;

// nodo de un arbol de Huffman
struct Node_huff {
    char symbol;
    unsigned int frequency;
    Node_huff *left_child;
    Node_huff *right_child;

    // constructor para nodos hoja
    Node_huff(char s, unsigned int f) {
        symbol = s;
        frequency = f;
        left_child = NULL;
        right_child = NULL;
    }

    // constructor para nodos intermedios
    Node_huff(Node_huff* l, Node_huff* r) {
        symbol = 0;
        frequency = l->frequency + r->frequency;
        left_child = l;
        right_child = r;
    }

    // un nodo es hoja cuando no tiene hijos
    bool is_leaf() const {
        return left_child == NULL && right_child == NULL;
    }

    // comparacion util para ordenar nodos por frecuencia
    bool operator <(Node_huff &other) {
#if 0
        // con esto se obtiene una codificacion
        // casi igual a la del ejemplo
        if ((*this).frequency == other.frequency) {
            if ((*this).is_leaf() && !other.is_leaf())
                return true;
            if (!(*this).is_leaf() && other.is_leaf())
                return false;
        }
#endif
        return (*this).frequency > other.frequency;
    }
};


// funcion auxiliar para comparar nodos convenientemente a traves de punteros
// (http://www-staff.it.uts.edu.au/~ypisan/programming/stl50.html, tip 20)
struct DereferenceLess {
    template <typename T>
    bool operator ()(T& p1, T& p2) const {
        return *p1 < *p2;
    }
};

int encode_huffman(std::stringstream& text_stream);

// actualizar tabla de frecuencias con los caracteres leidos desde s
void count_symbols(SymbolCount& freq_table, std::istream& s);

void print_huffman_tree(Node_huff *node, unsigned int depth = 0);

// crear arbol de huffman y retornar puntero a la raiz;
// obs:  los nodos hoja residen en el vector referenciado en el argumento,
//       (posiblemente en memoria de stack), mientras los nodos intermedios
//       son creados en el heap.
Node_huff *create_huffman_tree(std::vector<Node_huff>& leaves);


//void update_huffman_code(HuffmanCode& code, Node *node, const string& prefix);
void free_huffman_tree(Node_huff *node) ;

//}; // namespace WiseUtils

#endif // __WISEUTILS_H__

