#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct district{
  string name;
  string type;
  int num_resident;
  int power;
  bool has_power;
  int num_technician;
  string technicians[100];

};

void save(string fname, district districts[], int num, int power){
  ofstream fout(fname);
  if(!fout.is_open()){
    cout << "File not found!";
  }
  fout << power << endl;
  fout << num << endl;
  for(int i = 0; i < num; i++){
        fout << districts[i].name << endl;
        fout << districts[i].type << endl;
        fout << districts[i].num_resident << endl;
        fout << districts[i].power << endl;
        fout << districts[i].has_power << endl;
    
        fout << districts[i].num_technician << endl;
          for(int j = 0; j < districts[i].num_technician; j++){
              fout << districts[i].technicians[j] << endl;
              }
            
          }
  
  fout.close();
  
} 



void print_all(string fname, district districts[], int num, int power){
  int current_power = 0;

  int current_max[num];
  for(int i = 0; i < num; i++){
    current_max[i] = districts[i].num_resident;
  }
  int temp;
  for(int k = 0; k < num; k++){
    for (int i = k + 1; i < num; i++){
      if(current_max[k] >= current_max[i]){
        temp = current_max[k];
        current_max[k] = current_max[i];
        
        current_max[i] = temp;
        
      }
      
    }
    }
  
  
  
  for(int i = 0; i < num; i++){
    if(districts[i].has_power == 1){
    current_power += districts[i].power;
      }
  }
  
      cout << "The current power supply is " << power << "MW." << endl;  
      for(int k = 0; k < num; k++){
      for(int i = 0; i < num; i++){
        if(districts[i].num_resident == current_max[k]){
          if(k == num - 2 && num > 2){
            break;
          }
        cout << districts[i].name << endl;
        cout << "District type: " << districts[i].type << endl;
        cout << "Number of residents: " << districts[i].num_resident        << endl;
        if(districts[i].has_power == 1){
        cout << "Power use: " << districts[i].power << "MW"<< endl;
          }
          else{
            cout << "Power use: " << 0 << "MW"<< endl;
          }
        cout << "Has power: " << districts[i].has_power << endl;
        if(districts[i].num_technician > 0){
          cout << "Technicians: ";
          for(int j = 0; j < districts[i].num_technician; j++){
            if(j < districts[i].num_technician - 1){
              cout << districts[i].technicians[j] << ", ";
              }
            else{
              cout << districts[i].technicians[j];
            }
          }
          cout << endl;
        }
        cout << "---" << endl;
      }
        }
        
    }
  if(power < current_power){
    cout << "Critical Error! The current power supply of " << power << "MW is insufficient to supply " << current_power << "MW of power demand. Please shut off one or more districts." << endl;
    cout << "---" << endl;
    }
  current_power = 0;
  
}

void assign_technician(string tech_name, string district_name, district districts[], int num_district){
  bool technician_exist = false;
  for(int i = 0; i < num_district; i++){

    if(district_name == districts[i].name){
      districts[i].technicians[districts[i].num_technician] = tech_name;
      districts[i].num_technician += 1;
      cout << "Technician assigned!" << endl;
      technician_exist = true;
      break;
    }
  }
  
  if(!technician_exist){
    cout << "Error! The district with that name doesn't exist." << endl;
  }
  
}

void load(string fname, district districts[], int &num, int &power){
  
  ifstream input(fname);
  if(!input.is_open()){
    cout << "File not found!";
  }
  input >> power;
  input >> num;
  input.ignore();
  for(int i = 0; i < num; i++){
    getline(input, districts[i].name);
    input >> districts[i].type;
    input >> districts[i].num_resident;
    input >> districts[i].power;
    input >> districts[i].has_power;
    input >> districts[i].num_technician;
    input.ignore();
    for(int j = 0; j < districts[i].num_technician; j++){
      getline(input, districts[i].technicians[j]);
    }
  }
  
  
  input.close();
}
bool cut_power(string change_haspower, district districts[], int num){
  for(int i = 0; i <= num; i++){
        if(change_haspower == districts[i].name){
          districts[i].has_power = 0;
          return true;
        }
        if(i == num){
          return false;
        }
        
      }
}
bool restore_power(string change_haspower, district districts[], int num){
  for(int i = 0; i <= num; i++){
        if(change_haspower == districts[i].name){
          districts[i].has_power = 1;
          return true;
        }
        if(i == num){
          return false;
        }
        
      }
}


int main() {
  string filename = "test2.txt";
  district districts[100];
  int num;
  int power;
  string tech_name;
  string district_name;
  string newFilename = "example.txt";
  
  cout << "Please enter the name of the file to load:" << endl;
  cin >> filename;
  load(filename, districts, num, power);
  print_all(filename, districts, num, power);

  int option = 0;
  string change_haspower;

  while(option != 8){
    cout << "Main Menu" << endl
    << "1- Status" << endl
    << "2- Set Power Supply" << endl
    << "3- Shutoff Power" << endl
    << "4- Restore Power" << endl
    << "5- Assign Technician" << endl
    << "6- Save" << endl
    << "7- Load" << endl
    << "8- Exit" << endl
    << "Please enter your choice:" << endl;
    cin >> option;
    if(option < 1 || option > 8){
      cout << "Invalid option!" << endl;
    }
    else if(option == 1){
      print_all(filename, districts, num, power);
    }
    else if(option == 2){
      cout << "Enter the updated power supply in megawatts:" << endl;
      cin >> power;
    }
    else if(option == 3){
      cout << "Enter the name of the district:" << endl;
      cin.ignore();
      getline(cin, change_haspower);
      cut_power(change_haspower, districts, num);
      if(cut_power(change_haspower, districts, num)){
          cout << "The district's power has been successfully turned off." << endl;
        }
        else{
          cout << "Error! The district with that name doesn't exist." << endl;
        }
      
      
      
    }
    else if(option == 4){
      cout << "Enter the name of the district:" << endl;
      cin.ignore();
      getline(cin, change_haspower);
      restore_power(change_haspower, districts, num);
        if(restore_power(change_haspower, districts, num)){
          cout << "The district's power has been successfully turned back on." << endl;
        }
        else{
          cout << "Error! The district with that name doesn't exist." << endl;
        }
        
      
      
    }
    else if(option == 5){
      cin.ignore();
      cout << "Enter the name of the technician:" << endl;
      getline(cin, tech_name);
      cout << "Enter the name of the district to assign them to:" << endl;
      getline(cin, district_name);
  
      assign_technician(tech_name, district_name, districts, num);
    }
    else if(option == 6){
      cout << "Enter the file name to save to:" << endl;
      cin >> newFilename;
      save(newFilename, districts, num, power);
    }
    else if(option == 7){
      cout << "Enter the file name to load from:" << endl;
      cin >> newFilename;
      load(newFilename, districts, num, power);
      print_all(filename, districts, num, power);
    }
    else{
      break;
    }
  }
  
  return 0;
}
