#include "Join.hpp"

#include <vector>

using namespace std;

/*
 * Input: Disk, Memory, Disk page ids for left relation, Disk page ids for right relation
 * Output: Vector of Buckets of size (MEM_SIZE_IN_PAGE - 1) after partition
 */
vector<Bucket> partition(Disk* disk, Mem* mem, pair<uint, uint> left_rel, pair<uint, uint> right_rel) {
	// TODO: implement partition phase
	vector<Bucket> partitions(MEM_SIZE_IN_PAGE - 1, Bucket(disk));
	mem->reset();

    //mem->loadFromDisk(disk, 0, 0);

	// mem->mem_page(0)->print();

	for (uint i = left_rel.first; i < left_rel.second; ++i) {

        mem->loadFromDisk(disk, i, MEM_SIZE_IN_PAGE-1);
        uint page_size = mem->mem_page(MEM_SIZE_IN_PAGE-1)->size();
		// mem->mem_page(0)->print();

        for (uint record_id = 0; record_id < page_size; ++record_id) {
            // mem->mem_page(0)->print();

			Record left_record = mem->mem_page(MEM_SIZE_IN_PAGE - 1)->get_record(record_id);
            uint hash = left_record.partition_hash() % (MEM_SIZE_IN_PAGE - 1);
            if (mem->mem_page(hash)->full()) {
                uint disk_page_id = mem->flushToDisk(disk, hash);
                partitions[hash].add_left_rel_page(disk_page_id);
            }
            mem->mem_page(hash)->loadRecord(left_record);
			// mem->mem_page(hash)->print();
        }
    }


	
    // Flush any remaining output buffers to disk
    for (uint i = 0; i < MEM_SIZE_IN_PAGE - 1; ++i) {
        if (!mem->mem_page(i)->empty()) {
            uint disk_page_id = mem->flushToDisk(disk, i);
            partitions[i].add_left_rel_page(disk_page_id);
        }
    }


	mem->reset();
	// RIGHT RELATION

    for (uint i = right_rel.first; i < right_rel.second; ++i) {

        mem->loadFromDisk(disk, i, MEM_SIZE_IN_PAGE-1);
        uint page_size = mem->mem_page(MEM_SIZE_IN_PAGE - 1)->size();
		// mem->mem_page(0)->print();

        for (uint record_id = 0; record_id < page_size; ++record_id) {
            //mem->mem_page(0)->print();

			Record right_record = mem->mem_page(MEM_SIZE_IN_PAGE - 1)->get_record(record_id);
            uint hash = right_record.partition_hash() % (MEM_SIZE_IN_PAGE - 1);
            if (mem->mem_page(hash)->full()) {
                uint disk_page_id = mem->flushToDisk(disk, hash);
                partitions[hash].add_right_rel_page(disk_page_id);
            }
            mem->mem_page(hash)->loadRecord(right_record);
			//mem->mem_page(hash)->print();
        }
    }

    // Flush any remaining output buffers to disk
    for (uint i = 0; i < MEM_SIZE_IN_PAGE - 1; ++i) {
        if (!mem->mem_page(i)->empty()) {
            uint disk_page_id = mem->flushToDisk(disk, i);
            partitions[i].add_right_rel_page(disk_page_id);
        }
    }

    return partitions;




}

/*
 * Input: Disk, Memory, Vector of Buckets after partition
 * Output: Vector of disk page ids for join result
 */
vector<uint> probe(Disk* disk, Mem* mem, vector<Bucket>& partitions) {
	// TODO: implement probe phase
	//find smaller using vector of left/right rel in bucket

	/*uint countleft = 0;
	uint countright = 0;
	for (uint i = 0; i < partitions.size(); i++) {
		countleft += partitions[i].num_left_rel_record;
		countright += partitions[i].num_right_rel_record;
	}*/


	vector<uint> disk_pages;
	mem->reset();


	for (uint k = 0; k < MEM_SIZE_IN_PAGE - 1; k++) {
		if (partitions[k].num_left_rel_record < partitions[k].num_right_rel_record) {
			Page* out = mem->mem_page(MEM_SIZE_IN_PAGE - 2);
			//left record hashing
			for (uint p1 = 0; p1 < partitions[k].get_left_rel().size(); p1++) {
				//loads page from left relation in partition k into second to last page in memory

				mem->loadFromDisk(disk, partitions[k].get_left_rel()[p1], MEM_SIZE_IN_PAGE-1);

				for (uint r1 = 0; r1 < mem->mem_page(MEM_SIZE_IN_PAGE-1)->size(); r1++) {
					Record curr = mem->mem_page(MEM_SIZE_IN_PAGE-1)->get_record(r1);
					uint keyleft = curr.probe_hash() % (MEM_SIZE_IN_PAGE - 2);
					mem->mem_page(keyleft)->loadRecord(curr);
				}
			}

			for (uint p2 = 0; p2 < partitions[k].get_right_rel().size(); p2++) {
				mem->loadFromDisk(disk, partitions[k].get_right_rel()[p2], MEM_SIZE_IN_PAGE-1);
				//right record hashing
				for (uint j = 0; j < mem->mem_page(MEM_SIZE_IN_PAGE-1)->size(); j++) {
					Record right = mem->mem_page(MEM_SIZE_IN_PAGE-1)->get_record(j);
					uint keyright = right.probe_hash() % (MEM_SIZE_IN_PAGE - 2);
					for (uint l = 0; l < mem->mem_page(keyright)->size(); l++) {
						Record left = mem->mem_page(keyright)->get_record(l);
						if (left == right) {
							if (out->full()) {
								uint id = mem->flushToDisk(disk,MEM_SIZE_IN_PAGE-2);
								disk_pages.push_back(id);
							}
							out->loadPair(left, right);
						}
					}
				}
			}

		} else {
		
			Page* out = mem->mem_page(MEM_SIZE_IN_PAGE - 2);
			//left record hashing
			for (uint p1 = 0; p1 < partitions[k].get_right_rel().size(); p1++) {
				mem->loadFromDisk(disk, partitions[k].get_right_rel()[p1], MEM_SIZE_IN_PAGE-1);
				for (uint r1 = 0; r1 < mem->mem_page(MEM_SIZE_IN_PAGE-1)->size(); r1++) {
					Record curr = mem->mem_page(MEM_SIZE_IN_PAGE-1)->get_record(r1);
					uint keyright = curr.probe_hash() % (MEM_SIZE_IN_PAGE - 2);
					mem->mem_page(keyright)->loadRecord(curr);
				}
			}

			for (uint p2 = 0; p2 < partitions[k].get_left_rel().size(); p2++) {
				mem->loadFromDisk(disk, partitions[k].get_left_rel()[p2], MEM_SIZE_IN_PAGE-1);
				//right record hashing
				for (uint j = 0; j < mem->mem_page(MEM_SIZE_IN_PAGE-1)->size(); j++) {
					Record left = mem->mem_page(MEM_SIZE_IN_PAGE-1)->get_record(j);
					uint keyleft = left.probe_hash() % (MEM_SIZE_IN_PAGE - 2);
					for (uint l = 0; l < mem->mem_page(keyleft)->size(); l++) {
						Record right = mem->mem_page(keyleft)->get_record(l);
						if (left == right) {
							if (out->full()) {
								uint id = mem->flushToDisk(disk,MEM_SIZE_IN_PAGE-2);
								disk_pages.push_back(id);
							}
							out->loadPair(left,right);
						}
					}
				}
			}
		}
		for (uint r = 0; r < MEM_SIZE_IN_PAGE - 2; r++) {
			mem->mem_page(r)->reset();
		}
		mem->mem_page(MEM_SIZE_IN_PAGE - 1)->reset();
	}

	if (!mem->mem_page(MEM_SIZE_IN_PAGE - 2)->empty()) {
		uint id = mem->flushToDisk(disk,MEM_SIZE_IN_PAGE - 2);
		disk_pages.push_back(id);
	}


	return disk_pages;
}



