#include "hello.decl.h"

#include "hello.h"
#include "main.decl.h"

#include <cassert>


extern /* readonly */ CProxy_Main mainProxy;


Hello::Hello(int in_size, int in_phases) {
  // Nothing to do when the Hello chare object is created.
  //   This is where member variables would be initialized
  //   just like in a C++ class constructor.
  this->size = in_size;
  this->p = in_phases;
  this->current_p = 0;
  this->neighbors = (thisIndex == 0 || thisIndex == in_size-1) ? 1 : 2;
  this->n_received = 0;
}


// Constructor needed for chare object migration (ignore for now)
// NOTE: This constructor does not need to appear in the ".ci" file
Hello::Hello(CkMigrateMessage *msg) { }


void Hello ::receive_impl(int from, int sender_phase, int direction) {

  // Have this chare object say hello to the user.
  CkPrintf("Element  %d (phase %d) on processor %d received from %d (p=%d) in direction %d.\n",
           thisIndex, this->current_p, CkMyPe(), from, sender_phase, direction);

  CkAssert(sender_phase == this->current_p);
  assert(sender_phase == this->current_p);

}

void Hello ::start_running() {
  this->current_p = -1;

  compute_phase(0,0,0,0,0,0);
  thisProxy[thisIndex].run_until_done();
}

void Hello ::compute_phase(int left_origin, int left_phase, int left_direction,
			int right_origin, int right_phase, int right_direction) {


  if(this->current_p > this->p){
	  //done
	  mainProxy.done();
	  return;
  }


  this->n_received = 0;
  // Have this chare object say hello to the user.
  CkPrintf("Element  %d on processor %d starting phase %d.\n",
           thisIndex, CkMyPe(), this->current_p);

  //Signal my neighbors
  int left_neighbor = (thisIndex+this->size-1)%(this->size);
  int right_neighbor = (thisIndex+1)%(this->size);

  thisProxy[left_neighbor].receive(this->current_p+1, thisIndex, -1);
  thisProxy[right_neighbor].receive(this->current_p+1, thisIndex, 1);

}

void Hello ::start_running2() {
  this->current_p = -1;

  handle_phase( );
  thisProxy[thisIndex].run_until_done2();
}

void Hello ::start_running3() {
  this->current_p = -1;

  handle_phase( );
  thisProxy[thisIndex].run_until_done2();
}

void Hello ::handle_phase( void ) {


  if(this->current_p >= this->p){
	  //done
	  mainProxy.done();
	  return;
  }


  this->n_received = 0;
  // Have this chare object say hello to the user.
  CkPrintf("Element  %d on processor %d starting phase %d.\n",
           thisIndex, CkMyPe(), this->current_p);

	//Signal my neighbors, without wrapping boundary conditions
	if(thisIndex > 0){
		int left_neighbor = (thisIndex+this->size-1)%(this->size);
		thisProxy[left_neighbor].receive(this->current_p+1, thisIndex, -1);
	}

	if(thisIndex < this->size){
		int right_neighbor = (thisIndex+1)%(this->size);
		thisProxy[right_neighbor].receive(this->current_p+1, thisIndex, 1);
	}

}

#include "hello.def.h"
