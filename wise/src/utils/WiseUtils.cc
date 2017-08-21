#include <opencv.hpp>
#include "WiseUtils.h"

// Returns the erf() of a value (not super precice, but ok)
double erf(double x)
{
 double y = 1.0 / ( 1.0 + 0.3275911 * x);
 return 1 - (((((
        + 1.061405429  * y
        - 1.453152027) * y
        + 1.421413741) * y
        - 0.284496736) * y
        + 0.254829592) * y)
        * exp (-x * x);
}

// Returns the probability of x, given the distribution described by mu and sigma.
double pdf(double x, double mu, double sigma)
{
  //Constants
  static const double pi = 3.14159265;
  return exp( -1 * (x - mu) * (x - mu) / (2 * sigma * sigma)) / (sigma * sqrt(2 * pi));
}

// Returns the probability of [-inf,x] of a gaussian distribution
double cdf(double x, double mu, double sigma)
{
    return 0.5 * (1 + erf((x - mu) / (sigma * sqrt(2.))));
}

template<typename T>
T limit_precision(T val, int precision) {
    return std::floor((val * std::pow(10, precision) + 0.5)) / std::pow(10, precision);
}

float customPrecision(float in)
{
     char buffer[15];
     int bufLen = sprintf(buffer, "%.2f", in);

     if (bufLen > 0)
         return atof(buffer);
     else
         return 0.0;
}

cv::Mat mat2vec(cv::Mat mat)
{
    cv::Mat mat_inv;
    if (mat.cols == 1)
        cv::transpose(mat, mat_inv);
    else
        mat.copyTo(mat_inv);

    mat_inv.convertTo(mat_inv, CV_32F);

    for (int y = 0; y < mat_inv.rows; ++y)
      for (int x = 0;x < mat_inv.cols; ++x)
          mat_inv.at<float>(y, x) = customPrecision(mat_inv.at<float>(y, x));

    return mat_inv;
}

//using namespace WiseUtils;
std::vector<std::string> split(const std::string& s, const std::string& delim, bool keep_empty) {
    keep_empty = true;
    std::vector<std::string> result;
    if (delim.empty()) {
        result.push_back(s);
        return result;
    }
    std::string::const_iterator substart = s.begin(), subend;
    while (true) {
        subend = search(substart, s.end(), delim.begin(), delim.end());
        std::string temp(substart, subend);
        if (keep_empty || !temp.empty()) {
            result.push_back(temp);
        }
        if (subend == s.end()) {
            break;
        }
        substart = subend + delim.size();
    }
    return result;
}

// Serialize a cv::Mat to a stringstream
void serialize(cv::Mat input, std::stringstream* output)
{
    // We will need to also serialize the width, height, type and size of the matrix
    int width = input.cols;
    int height = input.rows;
    int type = input.type();
    size_t size = input.total() * input.elemSize();


    // Initialize a stringstream and write the data
    output->write((char*)(&width), sizeof(int));
    output->write((char*)(&height), sizeof(int));
    output->write((char*)(&type), sizeof(int));
    output->write((char*)(&size), sizeof(size_t));

    // Write the whole image data
    output->write((char*)input.data, size);
}

// Deserialize a Mat from a stringstream
cv::Mat deserialize(std::stringstream& input)
{
    // The data we need to deserialize
    int width = 0;
    int height = 0;
    int type = 0;
    size_t size = 0;

    // Read the width, height, type and size of the buffer
    input.read((char*)(&width), sizeof(int));
    input.read((char*)(&height), sizeof(int));
    input.read((char*)(&type), sizeof(int));
    input.read((char*)(&size), sizeof(size_t));

    // Allocate a buffer for the pixels
    char* data = new char[size];
    // Read the pixels from the stringstream
    input.read(data, size);

    // Construct the image (clone it so that it won't need our buffer anymore)
    cv::Mat m = cv::Mat(height, width, type, data).clone();

    // Delete our buffer
    delete[]data;

    // Return the matrix
    return m;
}

/* EXAMPLE PROGRAM
void main()
{
    // Read a test image
    Mat input = imread("D:\\test\\test.jpg");

    // Serialize the input image to a stringstream
    stringstream serializedStream = serialize(input);

    // Base64 encode the stringstream
    base64::encoder E;
    stringstream encoded;
    E.encode(serializedStream, encoded);

    // Base64 decode the stringstream
    base64::decoder D;
    stringstream decoded;
    D.decode(encoded, decoded);

    // Deserialize the image from the decoded stringstream
    Mat deserialized = deserialize(decoded);

    // Show the retrieved image
    imshow("Retrieved image", deserialized);
    waitKey(0);
}*/


// actualizar tabla de frecuencias con los caracteres leidos desde s
void count_symbols(SymbolCount& freq_table, std::istream& s) {
    while (1) {
        char c(s.get());
        if (s.eof())
            break;
        freq_table[c]++;
    }
}


void print_huffman_tree(Node_huff *node, unsigned int depth) {
    if (node == NULL)
        return;
    std::string indent(4 * depth, ' ');
    if (node->is_leaf())
        std::cout << indent << node->symbol << " (" << node->frequency << ")" << std::endl;
    else
        std::cout << indent << '*' << " (" << node->frequency << ")" << std::endl;
    print_huffman_tree(node->left_child,  depth + 1);
    print_huffman_tree(node->right_child, depth + 1);
}


// crear arbol de huffman y retornar puntero a la raiz;
// obs:  los nodos hoja residen en el vector referenciado en el argumento,
//       (posiblemente en memoria de stack), mientras los nodos intermedios
//       son creados en el heap.
Node_huff *create_huffman_tree(std::vector<Node_huff>& leaves) {
    // cola de punteros a nodos, ordenada por frecuencia
    typedef std::priority_queue<Node_huff *, std::vector<Node_huff *>, DereferenceLess> NodePtrQueue;
    NodePtrQueue nodes;

    // inicializar cola con los nodos hoja disponibles
    std::vector<Node_huff>::iterator p;
    for (p = leaves.begin(); p != leaves.end(); ++p)
        nodes.push(&(*p));

    // combinar nodos hasta crear el arbol;
    while (nodes.size() > 1) {
        Node_huff *first = nodes.top();
        nodes.pop();
        Node_huff *second = nodes.top();
        nodes.pop();
        Node_huff *combined_node = new Node_huff(first, second);
        nodes.push(combined_node);
    }

    return nodes.top();
}


void update_huffman_code(HuffmanCode& code, Node_huff *node, const std::string& prefix) {
    if (node == NULL)
        return;
    if (node->is_leaf())
        code[node->symbol] = prefix;
    else {
        update_huffman_code(code, node->left_child,  prefix + "0");
        update_huffman_code(code, node->right_child, prefix + "1");
    }
}


void free_huffman_tree(Node_huff *node) {
    if (node == NULL || node->is_leaf())
        return;
    free_huffman_tree(node->left_child);
    free_huffman_tree(node->right_child);
    delete node;
}


int encode_huffman(std::stringstream& text_stream) {
    //ifstream entrada("in.txt");

    // guardar la entrada estandar
    //stringstream text_stream;
    //text_stream << cin.rdbuf();
    //text_stream << entrada.rdbuf();

    // crear tabla de frecuencias
    SymbolCount frequencies;
    count_symbols(frequencies, text_stream);

    // saco del map los caracteres especiales @ # *
    // para que no formen parte del arbol de huffman
    //unsigned int arroba  = frequencies['@'];  frequencies.erase('@');
    //unsigned int gato = frequencies['#'];     frequencies.erase('#');
    //unsigned int asterisco = frequencies['*'];frequencies.erase('*');

    // crear nodos hoja con las frecuencias
    std::vector<Node_huff> leaves;
    SymbolCount::iterator sym;
    for (sym = frequencies.begin(); sym != frequencies.end(); ++sym) {
        Node_huff n(sym->first, sym->second);
        leaves.push_back(n);
    }

    // crear arbol
    Node_huff *root = create_huffman_tree(leaves);

    // ir creando el codigo de Huffman recursivamente
    HuffmanCode code;
    update_huffman_code(code, root, "11");

    // meter al map code de regreso los 3 codigos especiales
    code['@'] = "0";
    code['*'] = "101";
    code['#'] = "1001";

    free_huffman_tree(root);

    // codificar el mensaje
    std::vector<unsigned char> encoded_msg;
    std::string text(text_stream.str());
    std::string::iterator symbol;
    unsigned int bit_count = 0;
    int bits_in_byte = 0;
    unsigned char c = 0;

    for (symbol = text.begin(); symbol != text.end(); ++symbol) {
        std::string current_code(code[*symbol]);
        std::string::iterator bit;

        // util para debuguear el decodificador
        //cout << code[*symbol];

        for (bit = current_code.begin(); bit != current_code.end(); ++bit) {
            if (*bit == '1')
                c = (c << 1) + 1;
            else if (*bit == '0')
                c = c << 1;
            else
                std::cerr << "ERROR" << std::endl;
            bit_count++;
            bits_in_byte++;
            if (bits_in_byte == 8) {
                encoded_msg.push_back(c);
                bits_in_byte = 0;
            }
        }
    }
    // meter el ultimo byte si quedo a medio construir
    if (bits_in_byte != 0) {
        c <<= 8 - bits_in_byte;
        encoded_msg.push_back(c);
    }

    // preparar el archivo de salida
    std::ofstream salida("out.txt");

    // imprimir la tabla de simbolos
    HuffmanCode::iterator codeword;
    for (codeword = code.begin(); codeword != code.end(); ++codeword){
        salida << codeword->first << "-" << codeword->second << std::endl;
    }
    salida << "--" << std::endl;

    salida << bit_count << std::endl;
    salida << "--" << std::endl;

    copy(encoded_msg.begin(), encoded_msg.end(),
            std::ostream_iterator<unsigned char>(salida));

    //salida.seekp(0,ios_base::beg);
    salida.close();

    //cout << endl;

    return bit_count;
}

std::string seps(std::string& s) {
    if (!s.size()) return "";
    std::stringstream ss;
    ss << s[0];
    for (int i = 1; i < (int)s.size(); i++) {
        ss << '|' << s[i];
    }
    return ss.str();
}

void Tokenize(std::string& str, std::vector<std::string>& tokens, const std::string& delimiters)
{
    seps(str);

    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}
