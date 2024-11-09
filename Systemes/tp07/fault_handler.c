/*
 * fault_handler.c
 *
 *  Created on: 1 nov. 2008
 *      Author: lescouarnecn
 */
#include "mmu.h"
#include "physical_memory.h"
#include "swap.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

// Page fault handler
//     Free one page if needed
//     Get free page
//     Load
//     Update MMU

enum state_page {SWAPPED, ALLOCATED, NOTMAPPED};

#define PRECLEAN

struct page_table_entry{
	enum state_page status;
	page_phys pp;
};

// Page table
struct page_table_entry* page_table;
int page_table_size;

// List of allocated pages
page_virt* allocated_pages;
int allocated_pages_capacity;
int allocated_pages_size;
int allocated_pages_first;




void init_faultHandler(int nb_pages_virt, int nb_pages_phys){
	int i;
	page_table=(struct page_table_entry*)malloc(sizeof(struct page_table_entry)*nb_pages_virt);
	page_table_size=nb_pages_virt;
	for(i=0;i<nb_pages_virt;i++){
		page_table[i].pp=INVALID;
		page_table[i].status=NOTMAPPED;
	}

	allocated_pages=(page_virt*)malloc(sizeof(page_virt)*nb_pages_phys);
	allocated_pages_capacity=nb_pages_phys;
	for(i=0;i<nb_pages_phys;i++){
		allocated_pages[i]=INVALID;
	}

}

void unloadAPage();
void loadAPage(page_virt pv);

void page_fault_handler(page_virt pv){



	// Get a Free block
	if(pm_isFull()){
		printf("PF: Unload a page\n");
		unloadAPage();
	}
	page_phys pp = pm_getFreePage();

	// Mark page as loaded
	printf("PF: Load a page (%d)\n",pv);
	loadAPage(pv);

	// Read from Swap
	if(page_table[pv].status == SWAPPED){
		swap_read(pv,pp);
	}

	// Update page table
	page_table[pv].pp=pp;
	page_table[pv].status=ALLOCATED;

	// Write to MMU
	mmu_addTranslation(pv,pp);

	// That's all
}

#ifdef POLICY_FIFO
void unloadAPage(){

    // Take the first page
    page_virt pv = allocated_pages[allocated_pages_first];
    int chosen_page = allocated_pages_first;
    allocated_pages_first++;
    allocated_pages_first = allocated_pages_first % allocated_pages_capacity;


    // Write it to swap if accessed
    page_phys pp = page_table[pv].pp;
    if(mmu_isDirty(pv)){
        swap_write(pv, pp);
    }

    // Update the page table
    page_table[pv].status = SWAPPED;

    // Update the physical memory
    pm_freePage(pp);

    // Invalidate the page in the MMU
    mmu_invalidatePage(pv);
    page_table[pv].pp = INVALID;

    // Update the list of allocated pages
    allocated_pages[chosen_page] = allocated_pages[allocated_pages_size - 1];
    allocated_pages_size--;
}

void loadAPage(page_virt pv){
    // Add the page to the list of allocated pages
    allocated_pages[allocated_pages_size] = pv;
    allocated_pages_size++;
}
#endif

#ifdef POLICY_RANDOM
void unloadAPage(){
    srand(time(NULL));
	// Take a random page
    int chosen_page = rand() % allocated_pages_size;
    page_virt pv = allocated_pages[chosen_page];


    // Write it to swap if accessed
    page_phys pp = page_table[pv].pp;
    if(mmu_isDirty(pv)){
        swap_write(pv, pp);
    }

    // Update the page table
    page_table[pv].status = SWAPPED;

    // Update the physical memory
    pm_freePage(pp);

    // Invalidate the page in the MMU
    mmu_invalidatePage(pv);
    page_table[pv].pp = INVALID;

    // Update the list of allocated pages
    allocated_pages[chosen_page] = allocated_pages[allocated_pages_size - 1];
    allocated_pages_size--;

}

void loadAPage(page_virt pv){
    // Add the page to the list of allocated pages
    allocated_pages[allocated_pages_size] = pv;
    allocated_pages_size++;

}
#endif
#ifdef POLICY_CLOCK
int last_unloaded_page = 0;
void unloadAPage(){
    // Loop through the pages until we find one that is not accessed
    while(1){
        page_virt pv = allocated_pages[last_unloaded_page];
        if(mmu_isAccessed(pv)){
            mmu_clearAccessedBit(pv);
        }else{
            break;
        }
        last_unloaded_page++;
        last_unloaded_page = last_unloaded_page % allocated_pages_size;
    }
    int chosen_page = last_unloaded_page;
    page_virt pv = allocated_pages[chosen_page];

    // Write it to swap if accessed
    page_phys pp = page_table[pv].pp;
    if(mmu_isDirty(pv)){
        swap_write(pv, pp);
    }

    // Update the page table
    page_table[pv].status = SWAPPED;

    // Update the physical memory
    pm_freePage(pp);

    // Invalidate the page in the MMU
    mmu_invalidatePage(pv);
    page_table[pv].pp = INVALID;

    // Update the list of allocated pages
    allocated_pages[chosen_page] = allocated_pages[allocated_pages_size - 1];
    allocated_pages_size--;
}

void loadAPage(page_virt pv){
    // Add the page to the list of allocated pages
    allocated_pages[allocated_pages_size] = pv;
    allocated_pages_size++;
}
#endif


