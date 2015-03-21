/*
 * Copyright 2015, Matthew Teasdale <m.teasdale@tcd.ie>
 *
 * ped_hom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ped_hom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ped_hom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <boost/algorithm/string.hpp>


void make_hom(std::string ped_line){
  /*
   * Split the line by space or tab
   * Then print the line's header then
   *
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
  int ct = 0;
  // read file
  if (myfile.is_open()){
    // iterating through the file
    while (getline (myfile,line)){

      // Set a counter to update where we are
      ct++;
      if(ct % 100 == 0){
        std::cerr << "Processed " << ct << " samples" <<'\xd';
      };
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
  std::cerr << std::endl;
  std::cerr << "ped_hom v 0.1 (21 March 2015)  github.com/teasdalm/ped_hom" << std::endl;
  std::cerr << "(C) Matthew Teasdale 2015  GNU General Public License v3" << std::endl;
  std::cerr << std::endl;

  if(argc < 2){
    std::cerr << "Error!! - Usage..... ped_hom input.ped" << std::endl << std::endl;
  } else{
    std::cerr << "Starting filtering" << std::endl;
    filter_ped(argv[1]);
  }
  return 0;
}
