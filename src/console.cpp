#include "console.hpp"

#include<iomanip>
#include<ios>
#include<stdio.h>

using namespace Rygen;

using std::string;
using std::stringstream;
using std::list;
using std::setprecision;
using std::ios;
using std::endl;

Console Rygen::console;

#define CONSOLE_MAX_SIZE 1000

// Public data members go here.
Console::Console() // Constructor
{
    print_logs             = 0;
    input                  = "";
    print_on_delete        = 0;
    keep_logs              = 1;
    save_to_file           = 0;
    has_partial_characters = false;

    box_log("Console Initialized");
}

Console::~Console() // Destructor
{
    if(print_on_delete){
        StringList::iterator i;
        for(i = loglines.end(); ;)
        {
            --i;
            printf("%s\n", i->c_str());
            if ( i == loglines.begin()){
                break;
            }
        }
    }
    if(save_to_file){
        out.close();
    }
}

void Console::open_log_file(void)
{
  out.open("console.log", ios::out);
  save_to_file = 1;
}

void Console::log(string line)
{
  if(has_partial_characters) {
    has_partial_characters = false;
    log(partial_line.str());
    partial_line.str("");
  }
  if(keep_logs)
      loglines.push_back(line);
  if(print_logs){
      printf("%s\n", line.c_str());
      fflush(stdout);
  }
  if(save_to_file){
      out << line << endl;
  }
}

void Console::log(int number)
{
    stringstream st;
    st << number;
    log(st.str());
}

void Console::log(double number)
{
    stringstream st;
    st << number;
    log(st.str());
}

void Console::log(long number)
{
    stringstream st;
    st << number;
    log(st.str());
}

void Console::fatal(string line)
{
    log(line);
}

void Console::box_log(string line)
{
    string Border(line.length() + 2, '-');

    log("+" + Border + "+");
    log("| " + line + " |");
    log("+" + Border + "+");
}

/*string Sapien::pointer_to_hex(void *ptr)
{
  stringstream ss;
  ss << std::hex << ptr;
  return ss.str();
}
*/
