
#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"
#include "../AtenderSignal.h"


class SIGINT_Handler : public EventHandler {

private:
	AtenderSignal *atender;
public:

		SIGINT_Handler () : atender(NULL) {
		}

		~SIGINT_Handler () {
		}

		void setAtenderSignal(AtenderSignal *atender) {

			this->atender = atender;

		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGINT );
			if(atender!=NULL)
				this->atender->atenderSenial();
			return 0;
		}

};

#endif /* SIGINT_HANDLER_H_ */
