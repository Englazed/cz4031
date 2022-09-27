/*
Created by Bob
For CZ4031 B+ Tree implementation and experiments project

This file implements the experiments 
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

using namespace std;

int main()
{
    int BLOCKSIZE = int(200);
    std::cout << "==========================================================================================" << endl;
    std::cout << "Starting main..." << endl;
    std::cout << "" << endl;
    std::cout << "Block size is " + to_string(BLOCKSIZE) + "B." << endl;

    std::cout << "\nStarting experiment 1..." << endl;
    // create the stream redirection stuff
    streambuf *coutbuf = std::cout.rdbuf(); // save old buffer

    // save experiment1 logging
    ofstream out1("../experiment_results/experiment1.txt");
    std::cout.rdbuf(out1.rdbuf()); // redirect std::cout to filename.txt!

    /*
    =============================================================
    Experiment 1: store the data (which is about IMDb movives and described in Part 4) on the disk (as specified in Part 1) and report the following statistics:
        - the number of blocks;
        - the size of database (in terms of MB);
    =============================================================
    */

    // Create memory pools for the disk and the index, total 500MB
    // The split is determined empirically. We split so that we can have a contiguous disk address space for records
    int DISKSIZE = 150000000; 
    int INDEXSIZE = 350000000;
    std::cout << "creating the disk on the stack for records, index" << endl;
    DiskStorage disk(DISKSIZE, BLOCKSIZE);  
    DiskStorage index(INDEXSIZE, BLOCKSIZE); 
    std::cout << "Disk size is " + to_string(DISKSIZE) + "B." << endl;
    std::cout << "Index size is " + to_string(INDEXSIZE) + "B." << endl;

    // // Creating the tree
    BPlusTree tree = BPlusTree(BLOCKSIZE, &disk, &index);
    std::cout << "Max keys for a B+ tree node: " << tree.getMaxKeyCount() << endl;

    // // Reset the number of blocks accessed to zero
    disk.resetVisitedBlocks();
    index.resetVisitedBlocks();
    std::cout << "Number of record blocks accessed in search operation reset to: 0" << endl;
    std::cout << "Number of index blocks accessed in search operation reset to: 0" << endl;

    // Open test data
    std::cout << "Reading in data ... " << endl;
    std::ifstream file("../data/data.tsv"); // actual data
    // std::ifstream file("../data/testdata.tsv"); // testing data

    // Insert data into database and populate list of addresses
    if (file.is_open())
    {
        std::string line;
        int recordNum = 0;

        while (std::getline(file, line))
        {
            // temporary struct Record
            Record temp;
            stringstream linestream(line);
            string data;

            // assigning temp.tconst value
            strcpy(temp.tconst, line.substr(0, line.find("\t")).c_str());
            std::getline(linestream, data, '\t');

            // assigning temp.averageRating & temp.numVotes values
            linestream >> temp.averageRating >> temp.numVotes;

            // insert this record into the database
            Address tempAddress = disk.write(&temp, sizeof(Record));

            // build the bplustree as we insert records
            tree.insert(tempAddress, float(temp.averageRating));

            // logging
            //  cout << "Inserted record " << recordNum + 1 << " at block address: " << &tempAddress.blockAddress << " and offset " << &tempAddress.offset << endl;
            recordNum += 1;
        }
        file.close();
    }

    // call experiment 1
    std::cout << "=====================================Experiment 1==========================================" << endl;
    std::cout << "Number of records per record block --- " << BLOCKSIZE / sizeof(Record) << endl;
    std::cout << "Number of keys per index block --- " << tree.getMaxKeyCount() << endl;
    std::cout << "Number of record blocks --- " << disk.getAllocatedBlocks() << endl;
    std::cout << "Number of index blocks --- " << index.getAllocatedBlocks() << endl;
    std::cout << "Size of actual record data stored --- " << disk.getRealUsedSize() << endl;
    std::cout << "Size of actual index data stored --- " << index.getRealUsedSize() << endl;
    std::cout << "Size of record blocks --- " << disk.getUsedSize() << endl;
    std::cout << "Size of index blocks --- " << index.getUsedSize() << endl;
    std::cout << "Total number of blocks   : " << disk.getAllocatedBlocks() + index.getAllocatedBlocks() << endl;
    std::cout << "Actual size of database : " << disk.getRealUsedSize() + index.getRealUsedSize() << endl;
    std::cout << "Size of database (size of all blocks): " << disk.getUsedSize() + index.getUsedSize() << endl;

    // finish saving experiment1 logging
    std::cout.rdbuf(coutbuf); // reset to standard output again

    // reset counts for next part
    index.resetVisitedBlocks();
    disk.resetVisitedBlocks();

    /*
    =============================================================
    Experiment 2:
    Build a B+ tree on the attribute "averageRating" by inserting the records sequentially and report the following statistics:
    - The parameter n of the B + tree;
    - The number of nodes of the B + tree;
    - The height of the B + tree, i.e., the number of levels of the B + tree;
    - The root node and its child nodes(actual content);
    =============================================================
    */

    std::cout << "\nStarting experiment 2..." << endl;

    // save experiment2 logging
    ofstream out2("../experiment_results/experiment2.txt");
    std::cout.rdbuf(out2.rdbuf()); // redirect std::cout to filename.txt!

    // call experiment 2
    std::cout << "=====================================Experiment 2==========================================" << endl;
    std::cout << "Parameter n of the B+ tree    : " << tree.getMaxKeyCount() << endl;
    std::cout << "Number of nodes of the B+ tree: " << tree.getNodesCount() << endl;
    std::cout << "Height of the B+ tree         : " << tree.getLevels() << endl;
    std::cout << "Root nodes and child nodes :" << endl;
    tree.display(tree.getRoot(), 1);
    std::cout << endl;

    // finish saving experiment2 logging
    std::cout.rdbuf(coutbuf); // reset to standard output again

    // reset counts for next part
    index.resetVisitedBlocks();
    disk.resetVisitedBlocks();

    /*
    =============================================================
    Experiment 3:
    Retrieve the attribute “tconst” of those movies with the "averageRating" equal to 8 and report the following statistics:
    - The number and the content of index nodes the process accesses;
    - The number and the content of data blocks the process accesses;
    - The attribute “tconst” of the records that are returned;
    =============================================================
    */

    std::cout << "\nStarting experiment 3..." << endl;
    
    // save experiment3 logging
    ofstream out3("../experiment_results/experiment3.txt");
    std::cout.rdbuf(out3.rdbuf()); // redirect std::cout to filename.txt!

    // call experiment 3
    std::cout << "=====================================Experiment 3==========================================" << endl;
    std::cout << "Retrieving the attribute tconst of those movies with averageRating equal to 8..." << endl;
    tree.search(8.0, 8.0);
    std::cout << endl;
    std::cout << "Number of index blocks the process accesses: " << index.resetVisitedBlocks() << endl;
    std::cout << "Number of record blocks the process accesses: " << disk.resetVisitedBlocks() << endl;
    std::cout << "\nNo more records found for range " << 8.0 << " to " << 8.0 << endl;

    // finish saving experiment3 logging
    std::cout.rdbuf(coutbuf); // reset to standard output again

    /*
    =============================================================
    Experiment 4:
    Retrieve the attribute “tconst” of those movies with the attribute “averageRating” from 7 to 9, both inclusively
    and report the following statistics:
    - The number and the content of index nodes the process accesses;
    - The number and the content of data blocks the process accesses;
    - The attribute “tconst” of the records that are returned;
    =============================================================
    */

    std::cout << "\nStarting experiment 4..." << endl;

    // save experiment4 logging
    ofstream out4("../experiment_results/experiment4.txt");
    std::cout.rdbuf(out4.rdbuf()); // redirect std::cout to filename.txt!

    // call experiment 4
    std::cout << "=====================================Experiment 4==========================================" << endl;
    std::cout << "Retrieving the attribute tconst of those movies with averageRating from 7 to 9 (inclusively)..." << endl;
    tree.search(7, 9);
    std::cout << endl;
    std::cout << "Number of index blocks the process accesses: " << index.resetVisitedBlocks() << endl;
    std::cout << "Number of data blocks the process accesses: " << disk.resetVisitedBlocks() << endl;

    // finish saving experiment4 logging
    std::cout.rdbuf(coutbuf); // reset to standard output again

    /*
    =============================================================
    Experiment 5:
    Delete those movies with the attribute “averageRating” equal to 7, update the B + tree accordingly,
    and report the following statistics:
    - The number of times that a node is deleted(or two nodes are merged) during the process of the updating the B + tree;
    - The number nodes of the updated B + tree;
    - The height of the updated B + tree;
    - The root node and its child nodes of the updated B + tree;
    =============================================================
    */

    std::cout << "\nStarting experiment 5..." << endl;

    // save experiment5 logging
    ofstream out5("../experiment_results/experiment5.txt");
    std::cout.rdbuf(out5.rdbuf()); // redirect std::cout to filename.txt!

    // call experiment 5
    std::cout << "=====================================Experiment 5==========================================" << endl;
    std::cout << "Deleting those movies with the attribute averageRating equal to 7...\n";

    int nodesDeleted = tree.remove(7.0);

    std::cout << "B+ Tree after deletion" << endl;
    std::cout << "Number of times that a node is deleted (or two nodes are merged): " << nodesDeleted << endl;
    std::cout << "Number of nodes in updated B+ Tree --- " << tree.getNodesCount() << endl;
    std::cout << "Height of updated B+ tree --- " << tree.getLevels() << endl;
    std::cout << endl;
    tree.display(tree.getRoot(), 1);
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
