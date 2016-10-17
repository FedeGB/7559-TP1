
#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"
#include "../AtenderSignal.h"


class SIGINT_Handler : public EventHandler {

private:
	sig_atomic_t gracefulQuit;
	AtenderSignal *atender;
public:

		SIGINT_Handler () : gracefulQuit(0) , atender(NULL) {
		}

		~SIGINT_Handler () {
		}

		void setAtenderSignal(AtenderSignal *atender) {

			this->atender = atender;

		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGINT );
			this->gracefulQuit = 1;
			if(atender!=NULL)
				this->atender->atenderSenial();
			return 0;
		}

		sig_atomic_t getGracefulQuit () const {
			return this->gracefulQuit;
		}

};

#endif /* SIGINT_HANDLER_H_ */
