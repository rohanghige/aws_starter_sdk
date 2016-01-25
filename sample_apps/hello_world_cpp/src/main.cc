/*
 *  Copyright (C) 2008-2015 Marvell International Ltd.
 *  All Rights Reserved.
 */
/*
 * Hello World Application written in C++
 *
 * Summary:
 *
 * Prints Hello World every 5 seconds on the serial console.
 * The serial console is set on UART-0.
 *
 * A serial terminal program like HyperTerminal, putty, or
 * minicom can be used to see the program output.
 */

#include <iostream>
#include <string>
#include <new>

extern "C" {
#include <wmstdio.h>
#include <wm_os.h>
}

/* The extern "C" linkage is necessary as main() will be called from a "C"
 * application */
extern "C" int main(void);


class HelloWorld
{
public:
	HelloWorld(std::string p_initMsg) {
		initMsg = p_initMsg;
	}

	~HelloWorld() {
		wmprintf("Bye Bye world (%s)!\r\n", initMsg.c_str());
	}

	void PrintMsg(void);
private:
	std::string initMsg;
};

void HelloWorld::PrintMsg()
{
	wmprintf("Hello World C++ (%s) !\r\n", initMsg.c_str());
}

// This destructor won't be called as we loop infinitely in main()
static HelloWorld gHW("Global Data");

static void testCPPObjects()
{
	// Destructor will be called when this function returns.
	HelloWorld lHW("Local Stack");

	// Destructor will be called when we delete the object
	HelloWorld *nHW = new HelloWorld("Heap");

	gHW.PrintMsg();
	lHW.PrintMsg();
	nHW->PrintMsg();

	delete nHW;
}

/*
 * The application entry point is main(). At this point, minimal
 * initialization of the hardware is done, and also the RTOS is
 * initialized.
 */

typedef void (*funcp_t)(void);
typedef funcp_t *funcpp_t;

/**
 * @brief   Constructors table start.
 * @pre     The symbol must be aligned to a 32 bits boundary.
 */
extern funcp_t __init_array_start;

/**
 * @brief   Constructors table end.
 * @pre     The symbol must be aligned to a 32 bits boundary.
 */
extern funcp_t __init_array_end;

/**
 * @brief   Destructors table start.
 * @pre     The symbol must be aligned to a 32 bits boundary.
 */
extern funcp_t __fini_array_start;

/**
 * @brief   Destructors table end.
 * @pre     The symbol must be aligned to a 32 bits boundary.
 */
extern funcp_t __fini_array_end;
int main()
{
	/*
	 * These constructors and destructors are needed for C++. Can be
	 * removed if using custom linker script without these linker
	 * variables. Default SDK linker script has these variables even
	 * for pure C apps.
	 */
	/* Constructors invocation.*/
	funcpp_t fpp = &__init_array_start;
	while (fpp < &__init_array_end) {
		(*fpp)();
		fpp++;
	}

	/* Initialize Operating System */

	int count = 0;

	/* Initialize console on uart0 */
	wmstdio_init(UART0_ID, 0);

	testCPPObjects();

	while (1) {
		count++;
		wmprintf("Hello World: iteration %d\r\n", count);

		/* Sleep  5 seconds */
		os_thread_sleep(os_msec_to_ticks(5000));
	}
	/* Destructors invocation.*/
	fpp = &__fini_array_start;
	while (fpp < &__fini_array_end) {
		(*fpp)();
		fpp++;
	}
	return 0;
}
