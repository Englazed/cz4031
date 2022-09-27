/*
Created by Bob
For CZ4031 B+ Tree implementation and experiments project

This file implements the experiments (1-5)
*/

#include "disk_storage.h"
#include "bplustree.h"
#include "types.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    // /*
    // --------------------------------------------------------------------------------------
    // This section performs tasks we need to do before we get started on the experiment.
    // This includes:
    // - Create disk storage space
    // - Create index
    // - Create the B+ tree
    // - Read in the data provided in data.tsv
    // --------------------------------------------------------------------------------------
    // */

    // // Declare constants
    // // Block size is defined in project as 200MB.
    // int BLOCKSIZE = int(200);

    // // Create disk storage space and the index - let disk be 150MB and index be 350MB
    // int DISKSIZE = 150000000; 
    // int INDEXSIZE = 350000000;

    // // Declare DATAPATH
    // string DATAPATH = "../data/data.tsv";

    // // Print starting message to terminal
    // std::cout << "--------------------------------------------------------------------------------------" << endl;
    // std::cout << "Running main.exe\n" << endl;
    // std::cout << "Block size chosen is " + to_string(BLOCKSIZE) + "B." << endl;

    // // Create disk and index
    // DiskStorage disk(DISKSIZE, BLOCKSIZE);  
    // std::cout << "Disk size is " + to_string(DISKSIZE) + "B." << endl;
    // DiskStorage index(INDEXSIZE, BLOCKSIZE); 
    // std::cout << "Index size is " + to_string(INDEXSIZE) + "B." << endl;

    // // Visited blocks are set to 0 to start
    // disk.resetVisitedBlocks();
    // index.resetVisitedBlocks();

    // // Creating the B+ tree
    // BPlusTree tree = BPlusTree(BLOCKSIZE, &disk, &index);
    // std::cout << "B+ tree created with maximum of " + to_string(tree.getMaxKeyCount()) + " keys." << endl;

    // // Announce where data is being read from
    // std::cout << "Data is being read from: " + DATAPATH << endl;
    // std::ifstream file(DATAPATH); 

    // // Insert data records into B+ tree
    // if (file.is_open())
    // {
    //     int recordID = 0;
    //     std::string curLine;

    //     // While there are still records to get
    //     while (std::getline(file, curLine))
    //     {
    //         // Each record
    //         Record curRecord;
    //         stringstream curStream(curLine);
    //         string data;

    //         // Give each record its tconst, averageRating and numVotes
    //         strcpy(curRecord.tconst, curLine.substr(0, curLine.find("\t")).c_str());
    //         std::getline(curStream, data, '\t');
    //         curStream >> curRecord.averageRating >> curRecord.numVotes;

    //         // Record has been filled with data, now insert into both disk storage + B+ tree
    //         Address diskAddress = disk.write(&curRecord, sizeof(Record));
    //         tree.insert(diskAddress, float(curRecord.averageRating));

    //         // Output for visibility 
    //         //cout << "Record ID " << recordID << " is added at address: " << &diskAddress.blockAddress << " with offset " << &diskAddress.offset << endl;
    //         recordID += 1;
    //     }
    //     file.close();
    // }


    // /*
    // --------------------------------------------------------------------------------------
    // Experiment 1: store the data (which is about IMDb movives and described in Part 4) on the disk (as specified in Part 1) and report the following statistics:
    //     - the number of blocks;
    //     - the size of database (in terms of MB);
    // --------------------------------------------------------------------------------------
    // */
    // std::cout << "\nStarting experiment 1..." << endl;

    // // Save the output buffer so we can put contents in txt file later
    // streambuf *coutbuf = std::cout.rdbuf(); 

    // // Experiment 1 results will be saved to this file
    // ofstream expOne("../experiment_results/experiment1.txt");
    // // The printed output will be read and written to experiment_results/experiment1.txt
    // std::cout.rdbuf(expOne.rdbuf()); 

    // // Get starting timepoint to calculate execution time later
    // auto start = high_resolution_clock::now();

    // // Output results to experiment 1
    // std::cout << "------------------------------------------- Experiment 1 -------------------------------------------" << endl;
    // std::cout << "The number of blocks   : " << disk.getAllocatedBlocks() + index.getAllocatedBlocks() << endl;
    // std::cout << "Real size of database (both used and unused space) : " << disk.getRealUsedSize() + index.getRealUsedSize() << endl;
    // std::cout << "Used size of database (space taken up by blocks): " << disk.getUsedSize() + index.getUsedSize() << endl;

    // // Output buffer saved, revert to normal output in terminal 
    // std::cout.rdbuf(coutbuf); 

    // // Get ending timepoint
    // auto stop = high_resolution_clock::now();
    // // Get duration of experiment (stop-start)
    // auto duration = duration_cast<microseconds>(stop - start);
    // std::cout << "Time taken: " << duration.count() << " ms" << endl;

    // // Reset visited blocks, so that we start from 0 for next experiment
    // disk.resetVisitedBlocks();
    // index.resetVisitedBlocks();

    // /*
    // --------------------------------------------------------------------------------------
    // This section performs tasks we need to do before we get started on the experiment.
    // This includes:
    // - Create disk storage space
    // - Create index
    // - Create the B+ tree
    // - Read in the data provided in data.tsv
    // --------------------------------------------------------------------------------------
    // */

    // Declare constants
    // Block size is defined in project as 200MB.
    int BLOCKSIZE = int(200);

    // Create disk storage space and the index - let disk be 150MB and index be 350MB
    int DISKSIZE = 150000000; 
    int INDEXSIZE = 350000000;

    // Print starting message to terminal
    std::cout << "--------------------------------------------------------------------------------------" << endl;
    std::cout << "Running main.exe\n" << endl;
    std::cout << "Block size chosen is " + to_string(BLOCKSIZE) + "B." << endl;

    std::cout << "\nStarting experiment 1..." << endl;


    // Create disk and index
    DiskStorage disk(DISKSIZE, BLOCKSIZE);  
    DiskStorage index(INDEXSIZE, BLOCKSIZE); 
    std::cout << "Disk size is " + to_string(DISKSIZE) + "B." << endl;
    std::cout << "Index size is " + to_string(INDEXSIZE) + "B." << endl;

    // Creating the B+ tree
    BPlusTree tree = BPlusTree(BLOCKSIZE, &disk, &index);
    std::cout << "Max keys for a B+ tree node: " << tree.getMaxKeyCount() << endl;

    // Visited blocks are set to 0 to start
    disk.resetVisitedBlocks();
    index.resetVisitedBlocks();

    // Read data into file
    std::cout << "Reading in data... " << endl;
    std::ifstream file("../data/data.tsv"); 

    // Insert data records into disk and B+ tree
    if (file.is_open())
    {
        int recordNum = 0;
        std::string line;

        while (std::getline(file, line))
        {
            // Each record
            Record temp;
            stringstream linestream(line);
            string data;

            // Give each record its tconst, averageRating and numVotes
            strcpy(temp.tconst, line.substr(0, line.find("\t")).c_str());
            std::getline(linestream, data, '\t');
            linestream >> temp.averageRating >> temp.numVotes;

            // Record has been filled with data, now insert into both disk storage + B+ tree
            Address tempAddress = disk.write(&temp, sizeof(Record));
            tree.insert(tempAddress, float(temp.averageRating));

            // Output for visibility 
            //  cout << "Inserted record " << recordNum + 1 << " at block address: " << &tempAddress.blockAddress << " and offset " << &tempAddress.offset << endl;
            recordNum += 1;
        }
        file.close();
    }

    // /*
    // --------------------------------------------------------------------------------------
    // Experiment 1: store the data (which is about IMDb movives and described in Part 4) on the disk (as specified in Part 1) and report the following statistics:
    //     - the number of blocks;
    //     - the size of database (in terms of MB);
    // --------------------------------------------------------------------------------------
    // */

    // create the stream redirection stuff
    streambuf *coutbuf = std::cout.rdbuf(); // save old buffer

    // save experiment1 logging
    ofstream out1("../experiment_results/experiment1.txt");
    std::cout.rdbuf(out1.rdbuf()); // redirect std::cout to filename.txt!

    // call experiment 1
    std::cout << "=====================================Experiment 1==========================================" << endl;
    std::cout << "Total number of blocks   : " << disk.getAllocatedBlocks() + index.getAllocatedBlocks() << endl;
    std::cout << "Actual size of database : " << disk.getRealUsedSize() + index.getRealUsedSize() << endl;
    std::cout << "Size of database (size of all blocks): " << disk.getUsedSize() + index.getUsedSize() << endl;

    // finish saving experiment1 logging
    std::cout.rdbuf(coutbuf); // reset to standard output again

    // reset counts for next part
    index.resetVisitedBlocks();
    disk.resetVisitedBlocks();


    /*
    --------------------------------------------------------------------------------------
    Experiment 2: build a B+ tree on the attribute "numVotes" by inserting the records sequentially and report the following statistics:
    - the parameter n of the B+ tree;
    - the number of nodes of the B+ tree;
    - the height of the B+ tree, i.e., the number of levels of the B+ tree;
    - the content of the root node and its 1st child node;
    --------------------------------------------------------------------------------------
    */

    std::cout << "\nStarting experiment 2..." << endl;

    // Experiment 2 results will be saved to this file
    ofstream expTwo("../experiment_results/experiment2.txt");
    // The printed output will be read and written to experiment_results/experiment2.txt
    std::cout.rdbuf(expTwo.rdbuf()); 

    // // Get starting timepoint to calculate execution time later
    // start = high_resolution_clock::now();

    // Output results to experiment 2
    std::cout << "------------------------------------------- Experiment 2 -------------------------------------------" << endl;
    std::cout << "The parameter n of the B+ tree: " << tree.getMaxKeyCount() << endl;
    std::cout << "The number of nodes of the B+ tree: " << tree.getNodesCount() << endl;
    std::cout << "The height of the B+ tree: " << tree.getLevels() << endl;
    std::cout << "The content of the root node and its 1st child node:" << endl;
    tree.display(tree.getRoot(), 1);    // display the root as well as 1 level below it (child)
    std::cout << endl;

    // Output buffer saved, revert to normal output in terminal 
    std::cout.rdbuf(coutbuf); 

    // // Get ending timepoint
    // stop = high_resolution_clock::now();
    // // Get duration of experiment (stop-start)
    // duration = duration_cast<microseconds>(stop - start);
    // std::cout << "Time taken: " << duration.count() << " ms" << endl;

    // Reset visited blocks, so that we start from 0 for next experiment
    index.resetVisitedBlocks();
    disk.resetVisitedBlocks();


    /*
    --------------------------------------------------------------------------------------
    Experiment 3: (old)
    Retrieve the attribute “tconst” of those movies with the "averageRating" equal to 8 and report the following statistics:
    - The number and the content of index nodes the process accesses;
    - The number and the content of data blocks the process accesses;
    - The attribute “tconst” of the records that are returned;

    Experiment 3: (new)
    retrieve those movies with the “numVotes” equal to 500 and report the following statistics:
    - The number and the content of index nodes the process accesses; (first 5 index nodes or data blocks only if there are more than 5).
    - The number and the content of data blocks the process accesses;
    - The average of “averageRating’s” of the records that are returned;
    --------------------------------------------------------------------------------------
    */

    std::cout << "\nStarting experiment 3..." << endl;
    
    // Experiment 3 results will be saved to this file
    ofstream expThree("../experiment_results/experiment3.txt");
    // The printed output will be read and written to experiment_results/experiment3.txt
    std::cout.rdbuf(expThree.rdbuf()); 

    // Output results to experiment 3
    std::cout << "------------------------------------------- Experiment 3 -------------------------------------------" << endl;
    std::cout << "Searching for records with the “numVotes” equal to 500." << endl;
    tree.search(500, 500);
    std::cout << endl;
    std::cout << "Number of index blocks the process accesses: " << index.resetVisitedBlocks() << endl;
    std::cout << "Number of record blocks the process accesses: " << disk.resetVisitedBlocks() << endl;
    std::cout << "The average of “averageRating’s” of the records that are returned: " << 8.0 << endl;

    // finish saving experiment3 logging
    std::cout.rdbuf(coutbuf); // reset to standard output again


    /*
    --------------------------------------------------------------------------------------
    Experiment 4: (old)
    Retrieve the attribute “tconst” of those movies with the attribute “averageRating” from 7 to 9, both inclusively
    and report the following statistics:
    - The number and the content of index nodes the process accesses;
    - The number and the content of data blocks the process accesses;
    - The attribute “tconst” of the records that are returned;

    Experiment 4: (new)
    retrieve those movies with the attribute “numVotes” from 30,000 to 40,000, both inclusively and report the following statistics:
    - the number and the content of index nodes the process accesses; 
    - the number and the content of data blocks the process accesses; 
    - the average of “averageRating’s” of the records that are returned;
    --------------------------------------------------------------------------------------
    */

    std::cout << "\nStarting experiment 4..." << endl;

    // save experiment4 logging
    ofstream expFour("../experiment_results/experiment4.txt");
    std::cout.rdbuf(expFour.rdbuf()); // redirect std::cout to filename.txt!

    // call experiment 4
    std::cout << "------------------------------------------- Experiment 4 -------------------------------------------" << endl;
    std::cout << "Searching for records with the “numVotes” from 30,000 to 40,000 (inclusive)." << endl;
    tree.search(30000, 40000);
    std::cout << endl;
    std::cout << "Number of index blocks the process accesses: " << index.resetVisitedBlocks() << endl;
    std::cout << "Number of data blocks the process accesses: " << disk.resetVisitedBlocks() << endl;

    // finish saving experiment4 logging
    std::cout.rdbuf(coutbuf); // reset to standard output again


    /*
    --------------------------------------------------------------------------------------
    Experiment 5: (old)
    Delete those movies with the attribute “averageRating” equal to 7, update the B + tree accordingly,
    and report the following statistics:
    - The number of times that a node is deleted(or two nodes are merged) during the process of the updating the B + tree;
    - The number nodes of the updated B + tree;
    - The height of the updated B + tree;
    - The root node and its child nodes of the updated B + tree;

    Experiment 5: (new)
    delete those movies with the attribute “numVotes” equal to 1,000, update the B+ tree accordingly, and report the following statistics:
    - the number of times that a node is deleted (or two nodes are merged) during the process of the updating the B+ tree;
    - the number nodes of the updated B+ tree;
    - the height of the updated B+ tree;
    - the content of the root node and its 1st child node of the updated B+ tree;
    --------------------------------------------------------------------------------------
    */

    std::cout << "\nStarting experiment 5..." << endl;

    // save experiment5 logging
    ofstream expFive("../experiment_results/experiment5.txt");
    std::cout.rdbuf(expFive.rdbuf()); // redirect std::cout to filename.txt!

    // call experiment 5
    std::cout << "------------------------------------------- Experiment 5 -------------------------------------------" << endl;
    std::cout << "Deleting those movies with the attribute numVotes equal to 1000.\n";

    int nodesDeleted = tree.remove(7.0);

    std::cout << "B+ Tree after deletion" << endl;
    std::cout << "The number of times that a node is deleted (or two nodes are merged): " << nodesDeleted << endl;
    std::cout << "The number of nodes in updated B+ Tree --- " << tree.getNodesCount() << endl;
    std::cout << "Height of updated B+ tree --- " << tree.getLevels() << endl;
    std::cout << endl;
    std::cout << "The content of the root node and its 1st child node:" << endl;
    tree.display(tree.getRoot(), 1); // display the root as well as 1 level below it (child)
    std::cout << endl;

    // finish saving experiment5 logging
    std::cout.rdbuf(coutbuf); // reset to standard output again

    // reset counts for next part
    index.resetVisitedBlocks();
    disk.resetVisitedBlocks();

    std::cerr << "\n\n================================================================================================================" << endl;
    std::cerr << "Output saved to experiment_results folder. Please check there " << endl;
    std::cerr << "================================================================================================================" << endl;

    return 0;
}
