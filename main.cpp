#include <iostream>
#include <sstream>
#include <locale>
#include <string>
#include <vector>

void printUsage();
std::string toLower(std::string input);
std::vector<int> encode(std::string input);
const char* decode(int num);
std::string encrypt(const char* key = NULL, const char* msg = NULL);
std::string decrypt(const char* key = NULL, const char* msg = NULL);

int main(int argc, char** argv)
{
  if(argc < 3)
    {
      printUsage();
      return EXIT_FAILURE;
    }

  if(argc == 4) // Encrypt / Decrypt
    {
      std::string mode(argv[2]);
      if(mode.compare("-e") == 0) // Encrypt
	{
	  std::string key(argv[1]);
	  std::string msg(argv[3]);

	  if(key.empty() || msg.empty())
	    {
	      printUsage();
	      return EXIT_FAILURE;
	    }
	  
	  std::cout << encrypt(key.c_str(), msg.c_str()) << std::endl;
	}
      else if(mode.compare("-d") == 0) // Decrypt
	{
	  std::string key(argv[1]);
	  std::string msg(argv[3]);
	  
	  if(key.empty() || msg.empty())
	    {
	      printUsage();
	      return EXIT_FAILURE;
	    }
	  
	  std::cout << decrypt(key.c_str(), msg.c_str()) << std::endl;
	}
    }
  else if(argc == 3) // Generate Keys
    {
      std::string mode(argv[1]);
      if(mode.compare("-g") == 0) // Generate Key
	{
	  std::string data = toLower(argv[2]);
	  
	  if(data.empty())
	    {
	      printUsage();
	      return EXIT_FAILURE;
	    }
      
	  auto key = encode(data);
      
	  std::cout << "<KEY>" << std::endl;
	  
	  for(int i = 0; i < key.size(); i++)
	    std::cout << key[i] << " ";
	  
	  std::cout << std::endl;
	}
    }
			     
  return EXIT_SUCCESS;
}

std::string toLower(std::string input)
{
  std::locale loc;
  for(int i = 0; i < input.size(); i++)
    input[i] = std::tolower(input[i], loc);
  return input;
}

void printUsage()
{
  std::cout << "USAGE\nsubmarine -g KEY\n" <<
    "submarine KEY -e MSG\n" <<
    "submarine KEY -d MSG" << std::endl; 
}

std::string encrypt(const char* key, const char* msg)
{
  if(!key || !msg)
    return "ERROR";

  std::vector<int> msgVec = encode(msg); // ALPHABET TO INTEGERS
  std::vector<int> keyVec;

  // Transform keystring into vector with space delimiter
  std::stringstream ss(key);
  std::string substr;
  while (std::getline(ss, substr, ' ')) {    
    keyVec.push_back(std::atoi(substr.c_str()));
    substr.clear();
  }
  
  if(msgVec.size() > keyVec.size())
    return "MESSAGE TOO LONG. HAS TO MATCH THE KEY";

  std::stringstream out;

  for(int i = 0; i < msgVec.size(); i++) // MODULAR ADDITION
    {
      int digit = keyVec[i] + msgVec[i];
      digit = digit % 26; // MOD 26
      out << decode(digit) << " "; // Convert back to ALPHABET
    }
  
  return out.str();
}

std::string decrypt(const char* key, const char* msg)
{
  if(!key || !msg)
    return "ERROR";

  std::vector<int> msgVec = encode(msg);
  std::vector<int> keyVec;

  // Transform keystring into vector with space delimiter
  std::stringstream ss(key);
  std::string substr;
  while (std::getline(ss, substr, ' ')) {    
    keyVec.push_back(std::atoi(substr.c_str()));
    substr.clear();
  }
  
  if(msgVec.size() > keyVec.size())
    return "MESSAGE TOO LONG. HAS TO MATCH THE KEY";

  std::stringstream out;
  
  for(int i = 0; i < msgVec.size(); i++) // MODULAR SUBSTRACTION
    {
      int digit = msgVec[i] - keyVec[i];
      if(digit < 0)
	digit += 26;
      else
	digit = digit % 26; // MOD 26
      
      out << decode(digit) << " "; // Convert back to ALPHABET
    }
  
  return out.str();
}

std::vector<int> encode(std::string input)
{
  std::vector<int> out;
  for(int i = 0; i < input.size(); i++)
    {
      switch(input[i])
	{	  
	case 'a': // 0 
	  out.push_back(0);
	  break;
	  
	case 'b': // 1
	  out.push_back(1);
	  break;
	  
	case 'c': // 2
	  out.push_back(2);
	  break;
	  
	case 'd': // 3
	  out.push_back(3);
	  break;
	  
	case 'e': // 4
	  out.push_back(4);
	  break;
	  
	case 'f': // 5
	  out.push_back(5);
	  break;
	  
	case 'g': // 6
	  out.push_back(6);
	  break;
	  
	case 'h': // 7
	  out.push_back(7);
	  break;
	  
	case 'i': // 8
	  out.push_back(8);
	  break;
	  
	case 'j': // 9
	  out.push_back(9);
	  break;
	  
	case 'k': // 10
	  out.push_back(10);
	  break;
	  
	case 'l': // 11
	  out.push_back(11);
	  break;
	  
	case 'm': // 12
	  out.push_back(12);
	  break;
	  
	case 'n': // 13
	  out.push_back(13);
	  break;
	  
	case 'o': // 14
	  out.push_back(14);
	  break;
	  
	case 'p': // 15
	  out.push_back(15);
	  break;
	  
	case 'q': // 16
	  out.push_back(16);
	  break;
	  
	case 'r': // 17
	  out.push_back(17);
	  break;
	  
	case 's': // 18
	  out.push_back(18);
	  break;
	  
	case 't': // 19
	  out.push_back(19);
	  break;
	  
	case 'u': // 20
	  out.push_back(20);
	  break;
	  
	case 'v': // 21
	  out.push_back(21);
	  break;
	  
	case 'w': // 22
	  out.push_back(22);
	  break;
	  
	case 'x': // 23
	  out.push_back(23);
	  break;

	case 'y': // 24
	  out.push_back(24);
	  break;

	case 'z': // 25
	  out.push_back(25);
	  break;	  
	default: // Numerical
	  const char digit = input.at(i);
	  if(std::isdigit(digit))
	    out.push_back(std::atoi(&digit));
	  break;
	}
    }
  return out;
}

const char* decode(int num)
{
  switch(num)
    {
    case 0: // A
      return "a";
      break;
      
    case 1: // B
      return "b";
      break;
      
    case 2: // C
      return "c";
      break;
      
    case 3: // D
      return "d";
      break;
      
    case 4: // E
      return "e";
      break;
      
    case 5: // F
      return "f";
      break;
      
    case 6: // G
      return "g";
      break;
      
    case 7: // H
      return "h";
      break;
      
    case 8: // I
      return "i";
      break;
      
    case 9: // J
      return "j";
      break;
      
    case 10: // K
      return "k";
      break;
      
    case 11: // L
      return "l";
      break;
      
    case 12: // M
      return "m";
      break;
      
    case 13: // N
      return "n";
      break;
      
    case 14: // O
      return "o";
      break;
      
    case 15: // P
      return "p";
      break;
      
    case 16: // Q
      return "q";
      break;
      
    case 17: // R
      return "r";
      break;
      
    case 18: // S
      return "s";
      break;
      
    case 19: // T
      return "t";
      break;
      
    case 20: // U
      return "u";
      break;
      
    case 21: // V
      return "v";
      break;
      
    case 22: // W
      return "w";
      break;
      
    case 23: // X
      return "x";
      break;
      
    case 24: // Y
      return "y";
      break;
      
    case 25: // Z
      return "z";
      break;
      
    default:
      return "";
    }
}
