
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>



using namespace std;

float best_overall_accuracy = 0; //global variable to keep track of best accuraccy overall

float leave_one_out_cross_validation(vector<vector<float> >tree, vector<float> current_set_of_features, string search, float best_so_far_accuracy) { // k is 
    //cout << "The current set of features has " << current_set_of_features.size() - 1 << endl;

    float label_object_to_classify; // the class of the object to classify 
    float nearest_neighbor_distance; // the distance between object to classify and tis nearest neighbor 
    float nearest_neighbor_location; // loation of nearest neighbor in dataset 
    float nearest_neighbor_label; // class of nerest neighbor 
    float number_correctly_classified = 0;
    vector<float> object_to_classify; // the object we are trying to classify 
    float distance; 
    for (float i = 1; i < tree.size(); i++) { //this is a datapoint with all the features and the class label, we will compare this to all other datapoints in the dataset to see which one is closest to it and if they are in the same class. we use either forward or backward 
        object_to_classify = {}; //reset object to classify 
        nearest_neighbor_distance = INFINITY; 
        nearest_neighbor_location = INFINITY;
        nearest_neighbor_label = INFINITY; 
        //cout << "Ask if " << i << " is the nearest neighbor with " << k << endl;
        for (float j = 1; j < tree[0].size(); j++) { //literally every feature of every datapoint in the dataset, so we can compare it to the object we are trying to classify. We start with the first feature and then more features (columns)
            object_to_classify.push_back(tree[i][j]); //add the j which is the column and i is the row. this is every feature of the object we are trying to classify. we want to compare this to every other object in the dataset and see which one is closest to it.
    
        }
        for (float n = 1; n < tree.size(); n++){ //row so one datapoint 
            float sum = 0.0;
            if (n != i) { //make sure we do not compare the object to classify with itself 
                if (current_set_of_features.size() != 0){
                    for (float m = 0; m < current_set_of_features.size(); m++){ //column, so at this column we compare this specific feature of the dataset with all of the other same feature just each has different values 
                        sum += pow((object_to_classify[current_set_of_features[m] - 1] - tree[n][(current_set_of_features[m])]), 2); // Euclidean calculation between the feature we are trying to classify with the the same feature from each datapoint 
                    }
                }
                // if (search == "forward") { //
                //     sum += pow((object_to_classify[k - 1] - tree[n][k]), 2); // add the feature we are considering adding to the current set of features to the distance calculation
                // }
                distance = sqrt(sum); 
                if (distance < nearest_neighbor_distance) {
                        nearest_neighbor_distance = distance; 
                        nearest_neighbor_location = n;
                        nearest_neighbor_label = tree[nearest_neighbor_location][0];
                }
            }
        }
        label_object_to_classify = tree[i][0]; //see if they are in the same group 
        if(label_object_to_classify == nearest_neighbor_label) { //does it belong to the same class as nearest neighbor? 
            //cout << "Object " << i << " correctly classified as class " << label_object_to_classify << endl;
            number_correctly_classified = number_correctly_classified + 1;
        }
        //if (search == "forward") {
        //     if (best_overall_accuracy > (number_correctly_classified + float(tree.size() - i))/float(tree.size())) {
        //     //  cout << "Early abandoning: best_overall_accuracy = " << best_overall_accuracy 
        //     // << " number_correctly_classified = " << number_correctly_classified 
        //     // << " tree.size() = " << tree.size() 
        //     // << " i = " << i 
        //    // cout << " max possible = " << (number_correctly_classified + (float)(tree.size() - i)) / (float)tree.size() << endl;
        //     return -1;
        // // }
        // // else if (search == "backward") {
        // //     if (best_overall_accuracy > (number_correctly_classified + float(tree.size() - i))/float(tree.size())) {
        // //      cout << "Early abandoning: best_overall_accuracy = " << best_overall_accuracy 
        // //     << " number_correctly_classified = " << number_correctly_classified 
        // //     << " tree.size() = " << tree.size() 
        // //     << " i = " << i 
        // //     << " max possible = " << (number_correctly_classified + (float)(tree.size() - i)) / (float)tree.size() << endl;
        // //     return -1;
        // }

        }
         return number_correctly_classified/tree.size();
    }
//     return number_correctly_classified/tree.size();
// }

bool intersect(vector<float> a, float b) {
    for (float i = 0; i < a.size(); i++) {
            if (a[i] == b) {
                return true; // Intersection found
            }
        }
    return false; // Replace with actual intersection check
}

void feature_search_forward(vector<vector<float> >tree) {
    string forward = "forward";
    float stub = 0; 
    vector<float> current_set_of_features; // Start with an empty set of features 
    vector<float> best_overall_set_of_features; 
    float accuracy; 
    cout << "The dataset has " << tree.size() - 1 << " objects and " << tree[0].size() - 1 << " features (not counting the class label)." << endl;

    cout << "Running nearest neighbor with all features, using leave-one-out cross validation, to get a baseline accuracy: " << endl;
    accuracy = leave_one_out_cross_validation(tree, current_set_of_features, forward, stub);
    cout << "Baseline accuracy with no features: " << accuracy * 100 << "%" << endl;



    cout << "Feature search demo:\n";
    for (float i = 1; i < tree[0].size(); i++) { // search through all the features in the dataset, start with the first feature and then more features (columns)
        cout << "On the " << i  << "th level of the search tree" << endl; 
        float feature_to_add_at_this_level = -1; // the best feature at this level 
        float best_so_far_accuracy = 0; // the best accuracy at this level 
        for (float j = 1; j < tree[0].size(); j++) { // for every column in the dataset, check if it is in the current set of features
            //cout << current_set_of_features.size() << endl;
            if (intersect(current_set_of_features, j) == false) { // if not, then add it to current set of features 
               // cout << "--Considering adding the " << j << " feature" << endl;
                vector<float> temp_set_feat = current_set_of_features; //test vector
                temp_set_feat.push_back(j); //add j to the test vector
                accuracy = leave_one_out_cross_validation(tree, temp_set_feat, forward, best_so_far_accuracy); //calculate the accruacy of the model using nearest neighbor 
                //cout << "----Accuracy with feature " << j  << " added: " << accuracy << endl;         
                //cout << accuracy << " ACCURACY" << endl;
               // if (accuracy != -1) {
                cout << "Using feature(s) {";
                    for (float m = 0; m < temp_set_feat.size(); m++) {
                    cout << temp_set_feat[m] << " ";
                }
                    cout << "} , accuracy is " << accuracy * 100 << "%" << endl;
              //  }
                
                
                if (accuracy > best_so_far_accuracy) { //update the best accuracy at this level if true 
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = j; // Add the feature to the list
                }
            }
        }
       // if (feature_to_add_at_this_level != -1) {
            current_set_of_features.push_back(feature_to_add_at_this_level); 
            cout << "feature set {";
            for (float m = 0; m < current_set_of_features.size(); m++) {
                cout << current_set_of_features[m] << " ";
            }
            cout << "}, best so far accuracy is " << best_so_far_accuracy * 100 << "%" << endl;
     //   }

        if (best_so_far_accuracy > best_overall_accuracy) {
            best_overall_accuracy = best_so_far_accuracy; 
            best_overall_set_of_features = current_set_of_features; 
            cout << "Best feature(s): ";
             for (float m = 0; m < best_overall_set_of_features.size(); m++) {
                cout << best_overall_set_of_features[m] << " ";
            }
            cout << "Best overall accuracy so far: " << best_overall_accuracy * 100 << "%" << endl;
        }

        // cout << "On level " << i << " I added feature " << feature_to_add_at_this_level << " to current set\n";
         //cout << "Using feature(s) " << feature_to_add_at_this_level << ", accuracy is " << best_so_far_accuracy * 100 << "%" << endl;

    }
    cout << "Winning feature(s): ";
    for (float m = 0; m < best_overall_set_of_features.size(); m++) {
        cout << best_overall_set_of_features[m] << " ";
    }
    cout << endl;
}


void feature_backward_elim(vector<vector<float> >tree) {
    cout << "Best Overall: " << best_overall_accuracy << endl;
    float backwardBest = 0; 
    string search = "backward";
    vector<float> current_set_of_features; // Start with an empty set of features 
    vector<float> best_overall_set_of_features; //this stores the best set of features/node overall and gets updated every time we find a better set of features
    cout << "The dataset has " << tree.size() - 1 << " objects and " << tree[0].size() - 1 << " features (not counting the class label)." << endl;
    float accuracy; 
    // cout << current_set_of_features.size() << " HELLO" << endl;


    cout << "Running nearest neighbor with all features, using leave-one-out cross validation, to get a baseline accuracy: " << endl;
    accuracy = leave_one_out_cross_validation(tree, current_set_of_features, search, backwardBest);
    cout << "Baseline accuracy with all features: " << accuracy * 100 << "%" << endl;


    for (float k = 1; k < tree[0].size(); k++) { // for every column in the dataset, add it to current set of features 
        current_set_of_features.push_back(k); //all features are now here 
    }

    cout << "Running nearest neighbor with all features, using leave-one-out cross validation, to get a baseline accuracy: " << endl;
    accuracy = leave_one_out_cross_validation(tree, current_set_of_features, search, backwardBest);
    cout << "Baseline accuracy with all features: " << accuracy * 100 << "%" << endl;





    cout << "Feature backward elimination:\n";
    for (float i = 1; i < tree[0].size(); i++) { // search through all the features in the dataset, start with the first feature and then more features (columns)
          cout << "current set of features size: " << current_set_of_features.size() << endl;
        float feature_to_remove_at_this_level = -1;
        float best_so_far_accuracy = 0; // the best accuracy at this level 
        for (float j = 1; j < tree[0].size(); j++) { // each feature will be compared with the current set of features 
            float indice = 0;
            if (intersect(current_set_of_features, j) == true) { // if it is in the current set of features, then consider removing it
                for (float m = 0; m < current_set_of_features.size(); m++) { //find the index of the feature we are considering removing 
                    if (current_set_of_features[m] == j) { //since we erase, we want to know whee the feature j is in the current set and get the indices of it in the current set
                        indice = m;
                       // cout << "Considering removing feature " << j << " which is at index " << indice << " in the current set of features\n";
                    }
                }
                //cout << "--Considering removing the " << j << " feature" << endl;
                vector<float> temp_set_feat = current_set_of_features; //test vector 
                temp_set_feat.erase(temp_set_feat.begin() + indice); //remove j 
                accuracy = leave_one_out_cross_validation(tree, temp_set_feat, search, backwardBest); //calculate the accruacy of the model using nearest neighbor
                //cout << "ACCURACY: " << accuracy << endl;
                if (accuracy != -1) {
                    cout << "Using feature(s) {";
                    for (float m = 0; m < temp_set_feat.size(); m++) {
                        cout << temp_set_feat[m] << " ";
                    }
                    cout << "}, accuracy is " << accuracy * 100 << "%" << endl;
                } 

                if (accuracy > best_so_far_accuracy) { //update the best accuracy at this level if true 
                    //cout << "----Accuracy with feature " << j  << " removed: " << accuracy << endl;
                    best_so_far_accuracy = accuracy;
                    feature_to_remove_at_this_level = indice; // Add the feature to the list
                }
            }
        }
    //cout << "On level " << i << " I removed feature " << current_set_of_features.at(feature_to_remove_at_this_level) << " from current set\n";
    if (feature_to_remove_at_this_level != -1) {
       // cout << "Removing feature " << current_set_of_features.at(feature_to_remove_at_this_level) << " from current set\n";
        current_set_of_features.erase(current_set_of_features.begin() + feature_to_remove_at_this_level);
        cout << "Using feature(s) { ";
        for (float m = 0; m < current_set_of_features.size(); m++) {
            cout << current_set_of_features[m] << " ";
        }
        cout << "}, best so far accuracy is " << best_so_far_accuracy * 100 << "%" << endl;
        //best_overall_set_of_features = current_set_of_features;
    }
    // else {
    //     break; 
    // }

        if (best_so_far_accuracy > best_overall_accuracy) {
            cout << "Best overall accuracy improved from " << best_overall_accuracy * 100 << "% to " << best_so_far_accuracy * 100 << "%" << endl;
            best_overall_accuracy = best_so_far_accuracy; 
            best_overall_set_of_features = current_set_of_features; 
            cout << "Best feature(s): ";
             for (float m = 0; m < best_overall_set_of_features.size(); m++) {
                cout << best_overall_set_of_features[m] << " ";
            }
            cout << "Best overall accuracy so far: " << best_overall_accuracy * 100 << "%" << endl;
        }

        if (best_so_far_accuracy == 0) {
            cout << "No improvement in accuracy, stopping search.\n";
            if (i > current_set_of_features.size() -1) {
                cout << "No features were removed. Final feature set is the same as the original set of features.\n";
                break;
            }
            current_set_of_features.erase(current_set_of_features.begin() + i); 
            }
        // else {
        //         break;
        //     }


        }
    cout << "Winning feature(s): ";
    for (float m = 0; m < best_overall_set_of_features.size(); m++) {
        cout << best_overall_set_of_features[m] << " ";
    }
    cout << endl;
}
    




    
vector<vector<float> > loadMatrix(const std::string& filename) {
    std::vector<std::vector<float> > matrix;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return matrix;
    }

    while (getline(file, line)) {
        istringstream iss(line); // Create a string stream from the line because we want to parse the line into individual float values 
        std::vector<float> row;
        float value;

        while (iss >> value) {
            row.push_back(value);
        }

        if (!row.empty()) {
            matrix.push_back(row);
        }
    }

    file.close();
    return matrix;
}   




int main ()
{
    int dataset_choice;
    vector<vector<float> > tree;
    cout << "Pick Small (1) or Big dataset (2): "; 
    cin >> dataset_choice; 
    if(dataset_choice == 1) {
        cout << "You picked the small dataset\n";
        tree = loadMatrix("CS170_Small_DataSet__45.txt");
    }
    else if (dataset_choice == 2) {
        cout << "You picked the big dataset\n";
        tree = loadMatrix("CS170_Large_DataSet__97.txt");
    }
    else {
        cout << "Invalid choice, defaulting to small dataset\n";
        dataset_choice = 1;
    }
    //vector<vector<float> > tree = loadMatrix("SanityCheck_DataSet__1.txt");
    //vector<vector<float> > tree = loadMatrix("SanityCheckDataSet__2.txt");
    //vector<vector<float> > tree = loadMatrix("CS170_Small_DataSet__45.txt");
    //vector<vector<float> > tree = loadMatrix("CS170_Large_DataSet__97.txt");
    
    cout << "Forward or Backward feature selection? (Enter 1 for forward, 2 for backward): ";
    int search_choice;
    cin >> search_choice;

    if (search_choice == 1) {
        feature_search_forward(tree);
    }
    else if (search_choice == 2) {
        feature_backward_elim(tree);
    }
    else {
        cout << "Invalid choice, defaulting to forward selection\n";
        tree = loadMatrix("CS170_Small_DataSet__45.txt");

    //feature_search_forward(tree);
    //feature_backward_elim(tree);
    return 0;


    // int count;
    // double tmp;

    // ifstream data("test.data", ios::in);

    

    // for(int i = 0; i<RR; i++){
    //     for(int j = 0; j<CC; j++)
    //     {
    //     cout<<"Enter the number for Matrix 1";
    //         cin>>tree[i][j];
    //     }
    // }





    // // for(int i = 0; i < count; i++) {
    // //     data >> tmp;
    // //     tree.push_back(tmp);
    // // }

    // cout << "Numbers:\n";
    // cout << tree.size();
    // ifstream data("data.txt");
    // if (!data.is_open()) {
    //     cerr << "Error opening file!" << endl;
    //     return 1;
    // }
    // else {
    //     cout << "File opened successfully!" << endl;
    //     readfile(data);
    //     data.close();
    // }
}


