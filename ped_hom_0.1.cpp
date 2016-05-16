
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <boost/algorithm/string.hpp>


void make_hom(std::string ped_line){
  /*
   * Split the line by space or tab
   * then print the line's header then
   * print homozygous genotypes
   */
  std::vector<std::string> cols;
  boost::split(cols, ped_line, boost::is_any_of(" \t"));

  // print start of header
  std::cout << cols[0]; // fam ID
  std::cout << ' ' <<cols[1]; // sample ID
  std::cout << ' ' <<cols[2]; // parents
  std::cout << ' ' <<cols[3]; // parents
  std::cout << ' ' <<cols[4]; // sex
  std::cout << ' ' <<cols[5]; // status

  // print genotypes
  for(int j=6; j < cols.size(); j +=2){
    int v1 = rand() % 2;
    if(v1 == 0){
      std::cout << ' ' << cols[j] << ' ' << cols[j];
    } else{
      std::cout << ' ' << cols[j+1] << ' ' << cols[j+1];
    }
  }
  // newline beween samples
  std::cout << std::endl;
}


void filter_ped(std::string file_name){
  /*
   * Read the file, check for empty lines
   * and print some errors
   */

  // some input file things
  std::string line;
  std::ifstream myfile(file_name);

  // set random number
  srand(time(NULL));

  // set counter
  int ct = 0;
  // read file
  if (myfile.is_open()){
    // iterating through the file
    while (getline (myfile,line)){

      // Set a counter to update where we are
      ct++;
      if(ct % 100 == 0){
        std::cerr <<"Processed " << ct << " samples" <<'\xd';
      }
      // trim string
      boost::trim(line);
      //Check the line isn't empty
      if(line.empty()){
        continue;
      } else{
        make_hom(line);
      }
    }
    // close file
    myfile.close();
  // can't open file
  } else {
    std::cerr << "Unable to open file \n";
  }
  // all is well
  // print final count and tell user we're done
  std::cerr << "Processed " << ct << " samples" <<'\xd';
  std::cerr << std::endl << "Finished filtering" << std::endl;
}


int main (int argc, char* argv[]) {
  /*
   * Simple main statement to show programs name and collect commands
  */
  std::cerr << "ped_hom v0.1 (22 April 2015)  https://github.com/teasdalm/ped_hom" << std::endl;
  std::cerr << "(C) 2016 Matthew Teasdale BSD 3-Clause" << std::endl;

  if(argc < 2){
    std::cerr << "Error!! - Usage..... ped_hom input.ped" << std::endl;
  } else{
    std::cerr << "Starting filtering" << std::endl;
    filter_ped(argv[1]);
  }
  return 0;
}
