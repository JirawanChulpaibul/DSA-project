#include <iostream>
#include <fstream> // provides the file input/output functions
#include <vector>
#include <algorithm> // for using sort function for packages

using namespace std;

// define the package data stucture 
struct Package {
    double weight;
    double cost;
};


//compare to sort packages based on their cost over weight 
bool cmp(Package a, Package b) {
    return a.cost / a.weight > b.cost / b.weight;
}

int main() {
    ifstream file("data.txt"); //input txt file
    double tCost = 0.00; // total cost of racks that will be displayed at the end
    int outPack = 0, tWaste = 0; // racks that are used and the total storage weight wasted to be printed at the end too

    vector<double> weight_limits(4); // there are 4 max weight limits
    for (int i = 0; i < 4; i++) {
        file >> weight_limits[i]; // store the weight limits in the vector from the file
    }

    vector<double> rack_costs(4);
    for (int i = 0; i < 4; i++) {
        file >> rack_costs[i];
    }

    int package_types;
    file >> package_types;

    vector<Package> packages; // will refer to the data struct that is previous declared 
    for (int i = 0; i < package_types; i++) {
        double weight, cost;
        int count;
        file >> weight >> cost >> count; // store the values of weight, cost and count of each package types from the txt file 
        for (int j = 0; j < count; j++) {
            packages.push_back({ weight, cost }); //push back the weight and cost into the packages vector with package data type that is declared in the struct
        }
        cout << "Number of " << weight << "kg: " << count << " packs" << endl;
        outPack = outPack + count;
    }
    cout << endl;
    sort(packages.begin(), packages.end(), cmp); // sort the packages using the cmp structure which returns a boolean

    vector<double> used_weight(4, 0); // size of the vector to be 4 and all elements are initialized to 0.0.
    vector<double> total_cost(4, 0);
    //the & specifies that package is a reference to the elements in the packages vector(not a copy)
    for (auto& package : packages) 
    { //auto& automatically deduce type as package and the variable will have the same type of parameter = package (from the struct)
        for (int i = 0, x = 3; i < 4 && x > -1 ; i++, x--) 
        {
            if (used_weight[i] + package.weight <= weight_limits[i]) // switch the weight yo highest to lowest
            {
                used_weight[i] += package.weight;
                total_cost[i] += package.cost;
                outPack--;
                break;
            }
        }
    }
    for (int i = 0, x = 3; i < 4 && x > -1; i++, x--) {
        total_cost[i] += rack_costs[i];
        
        if ((weight_limits[i] - used_weight[i]) == 0) {
            cout << "Rack " << i + 1 << "($" << total_cost[i] << ")" << endl;
            tCost = tCost + rack_costs[i];
            
        }
        else if((used_weight[i])== 0 ) {
            cout << "Rack " << i + 1 << "($0)" << endl;
            
        }
        else if((weight_limits[i] - used_weight[i]) != 0){
            cout << "Rack " << i + 1 << "($" << total_cost[i] << ")" << "\t\t (wastage: " << (weight_limits[i] - used_weight[i]) << "kg space)" << endl;
            tCost = tCost + rack_costs[i];
            tWaste = tWaste +  (weight_limits[i] - used_weight[i]);
            
        }

        cout << "==================================================" << endl;
    }

    cout << "\nTotal costs : $" << tCost << endl;
    cout << "Storage wastage: " <<tWaste<< endl;
    cout << "Outstanding packages (racks are full): "<<outPack << endl;
    return 0;
}