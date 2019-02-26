#ifndef __HELLO_H__
#define __HELLO_H__


class Hello : public CBase_Hello {
	Hello_SDAG_CODE
private:
	int size;
	int p;
	int current_p;
	int neighbors;
	int n_received;
	int last_cpu;
 public:

  /// Constructors ///
  Hello(int in_size, int in_phases);
  Hello(CkMigrateMessage *msg);

  void pup(PUP::er &p);

  /// Entry Methods ///
  //void receive(int from, int sender_phase, int direction);
  void receive_impl(int sender_phase, int from, int direction);
  void start_running( void );
  void compute_phase(int left_origin, int left_phase, int left_direction,
			  int right_origin, int right_phase, int right_direction);

  void start_running2( void );
  void start_running3( void );
  void handle_phase( void );
};


#endif //__HELLO_H__
